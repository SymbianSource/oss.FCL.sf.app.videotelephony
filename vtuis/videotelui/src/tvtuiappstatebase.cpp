/*
* Copyright (c) 2007 - 2008 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  base class for application states
*
*/


#include "tvtuiappstates.h"
#include "videotelui.hrh"
#include "tvtuistates.h"
#include "cvtuiappshutter.h"
#include "mvtuistatecontext.h"
#include <videotelui.rsg>
#include <AknQueryDialog.h>
#include <StringLoader.h>
#include <cvtlogger.h>
#include <cvtengmodel.h>
#include <vtengevents.h>
#include <mvtengcommandhandler.h>
#include <coreapplicationuisdomainpskeys.h>

// By default call ending command is allowed to send to call handling.

// Initially no shutdown request
TBool TVtUiAppStateBase::iShutdownRequested = EFalse;

// -----------------------------------------------------------------------------
// c++ constructor
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TVtUiAppStateBase(
    MVtUiStateContext& aCtx,
    TVtUiStates& aUiStates ) : iCtx(aCtx), iUiStates( aUiStates )
    {
    }

// -----------------------------------------------------------------------------
// Destructor
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::~TVtUiAppStateBase()
    {
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::AppUiStartupPhase1DoneL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::AppUiStartupPhase1DoneL()
    {
    // no default behavior
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::AppUiStartupPhase2DoneL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::AppUiStartupPhase2DoneL()
    {
    // no default behavior
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::ShutdownDoneL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::ShutdownDoneL()
    {
    // no default behavior
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::HandleForegroundChangedL
// -----------------------------------------------------------------------------
//
TBool TVtUiAppStateBase::HandleForegroundChangedL(
    const TBool /*aIsForegroung*/ )
    {
    // no default behavior
    return EFalse;
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::PreHandleForegroundChangedL
// -----------------------------------------------------------------------------
//
TBool TVtUiAppStateBase::PreHandleForegroundChangedL(
    const TBool /*aIsForegroung*/ )
    {
    // no default behavior
    return EFalse;
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::StartDtmfTone
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::StartDtmfTone( const TChar& /*aTone*/ )
    {
    // no default behavior
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::StopDtmfTone
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::StopDtmfTone()
    {
    // no default behavior
    }


// -----------------------------------------------------------------------------
// TVtUiAppStateBase::SetInitialStateL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::SetInitialStateL(
    MVtUiStateContext& aCtx,
    TVtUiStates& aUiStates )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.SetInitialState" )
    TVtUiAppStateBase* initialState =
        TVtUiStateStarting::InstanceL( aCtx, aUiStates );
    aCtx.ChangeState( initialState );
    initialState->OpenL();
    __VTPRINTEXIT( "TVtUiAppStateBase.SetInitialState" )
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::AppUiStartupFailedL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::AppUiStartupFailedL()
    {
    __VTPRINTENTER( "TVtUiAppStateBase.AppUiStartupFailedL" )
    // Shutdown
    ChangeStateL( *TVtUiStateResetting::InstanceL( iCtx, iUiStates ) );
    __VTPRINTEXIT( "TVtUiAppStateBase.AppUiStartupFailedL" )
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::OpenL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::OpenL()
    {
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::Close
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::Close()
    {
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::ChangeStateL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::ChangeStateL( TVtUiAppStateBase& aNewState )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.ChangeStateL" )

    // Check for transition to already active state.
    TVtUiAppStateBase* state = &aNewState;
    if ( state == this )
        {
        __VTPRINTEXITR( "TVtUiAppStateBase.ChangeStateL %d", 0 )
        return;
        }
    const TVtEngCommandId pending =
        iCtx.Model().CommandHandler().PendingCommand();
    if ( pending !=  KVtEngCommandNone &&
         state == TVtUiStateResetting::InstanceL( iCtx, iUiStates ) )
        {
        // delay shutdown until engine command completes
        __VTPRINT2( DEBUG_GEN, "TVtUiAppStateBase.ChangeStateL, pengind command is: %d", pending );
        TVtUiAppStateBase::iShutdownRequested = ETrue;

        if ( pending == KVtEngInitializeShareImage )
            {
            iCtx.Model().CommandHandler().CancelCommand( pending );
            }

        __VTPRINTEXITR( "TVtUiAppStateBase.ChangeStateL %d", KErrNotReady )
        return;
        }
    __VTPRINT( DEBUG_GEN,
        " TVtUiAppStateBase.ChangeStateL !! STATE TRANSITION !!" )
    iCtx.ChangeState( &aNewState );
    Close();
    // perform entry action for new state
    aNewState.OpenL();
    __VTPRINTEXITR( "TVtUiAppStateBase.ChangeStateL %d", 1 )
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::CleanupResetPushL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::CleanupResetPushL()
    {
    // Shutdown if leave occurs in critical ops.
    CleanupStack::PushL(
        TCleanupItem( TransitionToReset, this ) );
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::TransitionToReset
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::TransitionToReset( TAny* aAny )
    {
    TVtUiAppStateBase* state = reinterpret_cast< TVtUiAppStateBase* >( aAny );
    TRAP_IGNORE( state->ChangeStateL( *TVtUiStateResetting::InstanceL(
        state->iCtx, state->iUiStates ) ) );
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::HandleVTCommandPerformedL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiAppStateBase::HandleVTCommandPerformedL(
            TVtEngCommandId /*aCommand*/,
            const TInt /*aError*/ )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.HandleVTCommandPerformedL" )
    // By default all UI is allowed to handle all command completions.
    TEventResponse handled = EEventNotHandled;

    // check if shutdown requested while command was pending
    const TVtEngCommandId pending = iCtx.Model().CommandHandler().PendingCommand();
    if ( pending == KVtEngCommandNone &&
          TVtUiAppStateBase::iShutdownRequested )
        {
        __VTPRINT( DEBUG_GEN, "Handling delayed shutdown" );
        ChangeStateL( *TVtUiStateResetting::InstanceL(
            iCtx, iUiStates ) );
        }
    __VTPRINTEXIT( "TVtUiAppStateBase.HandleVTCommandPerformedL" )
    return handled;
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::HandleVtEventL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiAppStateBase::HandleVtEventL(
    const TInt aEvent )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.HandleVtEventL" )
    TEventResponse handled = EEventHandled;
    switch ( aEvent )
        {
    case KVtEngDeviceLockOn:
    case KVtEngDeviceLockOff:
        HandleDeviceLockEventL( aEvent == KVtEngDeviceLockOn );
        break;
    case KVtEngRemoteDisconnect:
        /** Don't allow sending of end active call command to call handling
         *  because requesting disconnect from the network after NW originated
         *  termination violates standards.
         */
        break;
    default:
        handled = EEventNotHandled;
        break;
        }
    __VTPRINTEXIT( "TVtUiAppStateBase.HandleVtEventL" )
    return handled;
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::HandleCommandL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiAppStateBase::HandleCommandL(
    const TInt /*aCommand*/ )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.HandleCommandL" )
    TEventResponse handled = EEventNotHandled;
    __VTPRINTEXITR( "TVtUiAppStateBase.HandleCommandL %d", handled )
    return handled;
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::HandleLayoutChangedL
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::HandleLayoutChangedL( )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.HandleLayoutChangedL" )
    // By default only indicate that layout change needs to be handled.
    iUiStates.SetLayoutChangeNeeded( ETrue );
    __VTPRINTEXIT( "TVtUiAppStateBase.HandleLayoutChangedL" )
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::HandleShutdownReady
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::HandleShutdownReady()
    {
     __VTPRINTENTER( "TVtUiAppStateBase.HandleShutdownReady" )
    // forwarded to AppUi which handles UI framework exit
    iCtx.HandleShutdownReady();
    iCtx.ChangeState( NULL );
    // deletes current state
    Close();
     __VTPRINTEXIT( "TVtUiAppStateBase.HandleShutdownReady" )
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::HandleDeviceLockEventL
//
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::HandleDeviceLockEventL( const TBool aDeviceIsLocked )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.HandleDeviceLockEventL" )
    iUiStates.SetDeviceLockOn( aDeviceIsLocked );
    if ( aDeviceIsLocked )
        {
        iCtx.ChangeApplicationFocus( EFalse );
        }
    __VTPRINTEXITR( "TVtUiAppStateBase.HandleDeviceLockEventL lock state=%d",
        aDeviceIsLocked )
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::CheckEndActiveCallL
// -----------------------------------------------------------------------------
//
TBool TVtUiAppStateBase::CheckEndActiveCallL()
    {
    __VTPRINTENTER( "TVtUiAppStateBase.CheckEndActiveCallL" )
    const MVtEngSessionInfo::TSessionState state = SessionState( EFalse );
    TBool shutdownStarted( EFalse );
    if ( state == MVtEngSessionInfo::EIdle )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.Release bearer" )
        // h.245 session is ended
        ChangeStateL( *TVtUiStateResetting::InstanceL( iCtx, iUiStates ) );        
        shutdownStarted = ETrue;
        }
    __VTPRINTEXITR( "TVtUiAppStateBase.CheckEndActiveCallL %d",
        shutdownStarted )
    return shutdownStarted;
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::SessionState
// -----------------------------------------------------------------------------
//
MVtEngSessionInfo::TSessionState TVtUiAppStateBase::SessionState(
    const TBool aUpdate ) const
    {
    const CVtEngModel& model = iCtx.Model();
    const MVtEngSessionInfo& session = model.Session();
    return session.State( aUpdate );
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::SetLightsState
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::SetLightsState( const TBool aOn )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.SetLightsState" )
    const TInt value = aOn ? EForcedLightsOn : EForcedLightsOff;
    RProperty::Set(
            KPSUidCoreApplicationUIs,
            KLightsVTForcedLightsOn,
            value );
    __VTPRINTEXIT( "TVtUiAppStateBase.SetLightsState" )
    }

// -----------------------------------------------------------------------------
// TVtUiAppStateBase::SetExecState
// -----------------------------------------------------------------------------
//
void TVtUiAppStateBase::SetExecState( const TVtUiStates::TVtUiExecState aState )
    {
    __VTPRINTENTER( "TVtUiAppStateBase.SetExecState" )
    iUiStates.SetExecState( aState );
    __VTPRINTEXITR( "TVtUiAppStateBase.SetExecState %d", aState )
    }

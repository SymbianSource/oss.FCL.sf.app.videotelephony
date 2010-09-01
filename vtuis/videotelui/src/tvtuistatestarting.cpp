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
* Description:  waiting details application state
*
*/


#include "tvtuistates.h"
#include "tvtuiappstates.h"
#include "mvtuistatecontext.h"
#include "videotelui.hrh"
#include "cvtuiappshutter.h"
#include <cvtlogger.h>
#include <vtengevents.h>
#include <vtengcommands.h>
#include <cvtengmodel.h>
#include <mvtengsessioninfo.h>


TVtUiStateStarting* TVtUiStateStarting::iInstance = NULL;

// c++ constructor
TVtUiStateStarting::TVtUiStateStarting(
    MVtUiStateContext& aCtx, TVtUiStates& aUiStates ) 
    : TVtUiAppStateBase( aCtx, aUiStates )
    {
    iPreconditions.Set( EWaitingCLI );
    iPreconditions.Set( EWaitingPhase1ToComplete );
    }

// Destructor
TVtUiStateStarting::~TVtUiStateStarting()
    {
    delete iStartCallback;
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::InstanceL
//
// -----------------------------------------------------------------------------
//
TVtUiStateStarting * TVtUiStateStarting::InstanceL(
    MVtUiStateContext& aCtx, TVtUiStates& aUiStates )
    {
    __VTPRINTENTER( "TVtUiStateStarting.InstanceL" )
    if ( iInstance == NULL )
        {
        iInstance = new ( ELeave ) TVtUiStateStarting( aCtx, aUiStates );
        }
    __VTPRINTEXIT( "TVtUiStateStarting.InstanceL" )
    return iInstance;
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::AppUiStartupPhase1DoneL
//
// Phase 1 of application startup is completed, check if we can proceed to
// phase 2.
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::AppUiStartupPhase1DoneL()
    {
    __VTPRINTENTER( "TVtUiStateStarting.AppUiStartupPhase1DoneL" )
    // From startup phase point of view we're ready to proceed
    // to phase 2. Clear that precondition and proceed if otherwise ready.
    CheckPhase2StartupL( EWaitingPhase1ToComplete );
    __VTPRINTEXIT( "TVtUiStateStarting.AppUiStartupPhase1DoneL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::AppUiStartupPhase2DoneL
//
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::AppUiStartupPhase2DoneL()
    {
    __VTPRINTENTER( "TVtUiStateStarting.AppUiStartupPhase2DoneL" )
    // Phase 2 completed, proceed to next state
    ChangeStateL( *TVtUiStateRunning::InstanceL( iCtx, iUiStates ) );
    __VTPRINTEXIT( "TVtUiStateStarting.AppUiStartupPhase2DoneL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::HandleVtEventL
//
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiStateStarting::HandleVtEventL(
    const TInt aEvent )
    {
    __VTPRINTENTER( "TVtUiStateStarting.HandleVtEventL" )
    TEventResponse handled = EEventHandled;
    switch ( aEvent )
        {
    case KVtEngRemoteDisconnect:
        // base class handles this.
        handled = TVtUiAppStateBase::HandleVtEventL( aEvent );
        break;
    case KVtEngSessionStateChanged:
        {
        // check if session state is proper for proceeding to next phase
        // in startup.
        CheckSessionStateL();
        }
        break;
    case KVtEngRemoteVideoStarted:
        // allow to start remote video rendering
    case KVtEngSourceChanged:
        // allow handling of source changed event
        handled = EEventNotHandled; 
        break;
    case KVtEngCLIAvailable:
        HandleCLIReceivedL();
        break;
        
    case KVtEngRemoteUIIIA5StringSupport:
        break;
    case KVtEngDeviceLockOn:
    case KVtEngDeviceLockOff:
    default:
        handled = TVtUiAppStateBase::HandleVtEventL( aEvent );
        break;
        }
    __VTPRINTEXIT( "TVtUiStateStarting.HandleVtEventL" )
    return handled;
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::HandleCommandL
//
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiStateStarting::HandleCommandL(
    const TInt /*aCommand*/ )
    {
    __VTPRINTENTER( "TVtUiStateStarting.HandleCommandL" )
    __VTPRINTEXIT( "TVtUiStateStarting.HandleCommandL" )
    return EEventNotHandled;
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::HandleForegroundChangedL
//
// -----------------------------------------------------------------------------
//
TBool TVtUiStateStarting::HandleForegroundChangedL( const TBool aIsForeground )
    {
    __VTPRINTENTER( "TVtUiStateStarting.HandleForegroundChangedL" )
        
    SetLightsState( aIsForeground );
    iCtx.RefreshL( MVtUiStateContext::ENaviPane );
    
    // behave as in background if CLI (=details) has not yet received
    TBool handleAsForeground( aIsForeground && iUiStates.IsDetailsReceived() ); 
    TVtUiAppStateBase::ExecuteEngineCommand( KVtEngSetUIForeground, 
        handleAsForeground );
    
    __VTPRINTEXIT( "TVtUiStateStarting.HandleForegroundChangedL" )
    return handleAsForeground;
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::OpenL
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::OpenL()
    {
    __VTPRINTENTER( "TVtUiStateStarting.OpenL" )
    iStartCallback = new ( ELeave ) CAsyncCallBack (
            TCallBack( &AsynchOpen, this ),
            CActive::EPriorityStandard );
    iStartCallback->CallBack();  
    __VTPRINTEXIT( "TVtUiStateStarting.OpenL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::AsynchOpen
// asynchronous entry to the state.
// -----------------------------------------------------------------------------
//
TInt TVtUiStateStarting::AsynchOpen( TAny* aAny )
    {
    __VTPRINTENTER( "TVtUiStateStarting.AsynchOpen" )
    TVtUiStateStarting* state = reinterpret_cast<TVtUiStateStarting*>( aAny );
    delete state->iStartCallback;
    state->iStartCallback = NULL;
    TRAPD( res, state->DoOpenL() );
    __VTPRINTEXITR( "TVtUiStateStarting.AsynchOpen err=%d>", res )
    return res;
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::DoOpenL
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::DoOpenL()
    {
    __VTPRINTENTER( "TVtUiStateStarting.DoOpenL" )
    if ( !CheckEndActiveCallL() )
        {
        // not shutting down, proceed to phase 1
        iCtx.StartupPhase1L();
        }
    __VTPRINTEXIT( "TVtUiStateStarting.DoOpenL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::CheckSessionStateL
// Resolve action based on session state change in the engine.
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::CheckSessionStateL()
    {
    __VTPRINTENTER( "TVtUiStateStarting.CheckSessionStateL" )
    const MVtEngSessionInfo::TSessionState state = SessionState( EFalse );
    switch ( state )
        {
    case MVtEngSessionInfo::EConnected:
    case MVtEngSessionInfo::ENegotiating:
    case MVtEngSessionInfo::EOpen:
        // From session state point of view we're ready to proceed.
        // Clear precondition and proceed if otherwise ready.
        CheckPhase2StartupL( EWaitingSessionState );
        break;
    default:
        // Is session state such that we need to shutdown?
        CheckEndActiveCallL();
        break;
        }
    __VTPRINTEXIT( "TVtUiStateStarting.CheckSessionStateL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::CheckPhase2StartupL
//
// mark precondition passed and if no more preconditions exist proceed
// in startup.
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::CheckPhase2StartupL(
    const TPreconditions aCond )
    {
    __VTPRINTENTER( "TVtUiStateStarting.CheckPhase2StartupL" )
    // First check that at least one precondition holds
    if ( iPreconditions.Value() )
        {
        iPreconditions.Clear( aCond );
        if ( !iPreconditions.Value() )
            {
            CleanupResetPushL();  // start shutdown if StartupPhase2L leaves
            iCtx.StartupPhase2L();
            CleanupStack::Pop(); // CleanupResetPushL
            }
        }
#ifdef VTDEBUG
    else {
        __VTPRINT( DEBUG_GEN, "TVtUiStateStarting.CheckPhase2StartupL NoOp!" )
        }
#endif // VTDEBUG
    __VTPRINTEXITR( "TVtUiStateStarting.CheckPhase2StartupL cond=%d",
        (TInt) iPreconditions.Value() )
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::HandleCLIReceivedL
// CLI reception from engine is one of the two preconditions for proceeding
// to phase2 startup.
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::HandleCLIReceivedL()
    {
    __VTPRINTENTER( "TVtUiStateStarting.HandleCLIReceivedL" )
    const MVtEngSessionInfo& session = iCtx.Model().Session();
    MVtEngSessionInfo::TCLI cli;
    if ( session.GetCLI( cli ) == KErrNone )
        {
        iUiStates.SetDetailsReceived( ETrue );
        iUiStates.SetCLIReceived( cli.iVoiceCallPossible );
        iCtx.SetCallIdL( cli.iCallId );
        iCtx.SetCallNameL( cli.iName );
        }
    CheckPhase2StartupL( EWaitingCLI );
    __VTPRINTEXIT( "TVtUiStateStarting.HandleCLIReceivedL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateStarting::Close
// -----------------------------------------------------------------------------
//
void TVtUiStateStarting::Close()
    {
    __VTPRINTENTER( "TVtUiStateStarting.Close" )
    if ( TVtUiStateStarting::iInstance )
        {
        delete TVtUiStateStarting::iInstance;
        TVtUiStateStarting::iInstance = NULL;
        }
    __VTPRINTEXIT( "TVtUiStateStarting.Close" )
    }

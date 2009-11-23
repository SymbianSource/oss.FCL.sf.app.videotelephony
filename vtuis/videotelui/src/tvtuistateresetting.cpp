/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
#include "cvtuiappshutter.h"
#include <cvtlogger.h>
#include <vtengevents.h>

TVtUiStateResetting* TVtUiStateResetting::iInstance = NULL;

// c++ constructor
TVtUiStateResetting::TVtUiStateResetting( 
    MVtUiStateContext& aCtx, 
    TVtUiStates& aUiStates, 
    const TVtEngCommandId aCommand )
    : TVtUiAppStateBase( aCtx, aUiStates ), 
      iCommand( aCommand )
    {
    	__VTPRINT2( DEBUG_GEN, "TVtUiStateResetting.ctr iCommand=%d", iCommand )
    }

// Destructor
TVtUiStateResetting::~TVtUiStateResetting()
    {
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::
// -----------------------------------------------------------------------------
//
TVtUiStateResetting* TVtUiStateResetting::InstanceL( 
    MVtUiStateContext& aCtx, 
    TVtUiStates& aUiStates,
    const TVtEngCommandId aCommand )
    {
    __VTPRINTENTER( "TVtUiStateResetting.InstanceL" )
    if ( iInstance == NULL )
        {
        iInstance = new ( ELeave ) TVtUiStateResetting( 
            aCtx, aUiStates, aCommand );
        }
    else if ( aCommand != KVtEngCommandNone )
        { // if call ending is UI originated, command is given
        iInstance->iCommand  = aCommand;
        __VTPRINT2( DEBUG_GEN, "TVtUiStateResetting.InstanceL iCommand=%d", 
            iInstance->iCommand )
        }
    __VTPRINTEXIT( "TVtUiStateResetting.InstanceL" )
    return iInstance;
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::ShutdownDoneL
// AppUi has finished its own shutdown steps. Notify app shutter that it may 
// proceed.
// 
// -----------------------------------------------------------------------------
//
void TVtUiStateResetting::ShutdownDoneL()
    {
    __VTPRINTENTER( "TVtUiStateResetting.ShutdownDone" )
    CVtUiAppShutter* shutter = CVtUiAppShutter::InstanceL( *this );
    if ( shutter )
        {
        shutter->StartShutdown();
        }
    __VTPRINTEXIT( "TVtUiStateResetting.ShutdownDone" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::AppUiStartupFailedL
// -----------------------------------------------------------------------------
//
void TVtUiStateResetting::AppUiStartupFailedL()
    {
    __VTPRINTENTER( "TVtUiStateResetting.AppUiStartupFailedL" )
    // no-op (overrides default behavior)
    __VTPRINTEXIT( "TVtUiStateResetting.AppUiStartupFailedL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::HandleVTCommandPerformedL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiStateResetting::HandleVTCommandPerformedL
    ( 
    TVtEngCommandId aCommand,
    const TInt /*aError*/ )
    {
    __VTPRINTENTER( "TVtUiStateResetting.HandleVTCommandPerformedL" )
    // By default responses to commands are ignored while resetting
    TEventResponse handled = EEventHandled;
    switch ( aCommand )
        {
        case KVtEngResetEngine:
            // Allow UI to process reset command response        
            handled = EEventNotHandled;
            break;
        case KVtEngTerminateSession:
        case KVtEngSwitchToVoice:
            // 
            iCtx.ShutdownL();
            break;
        default:
            break;            
        }
    __VTPRINTEXIT( "TVtUiStateResetting.HandleVTCommandPerformedL" )
    return handled;
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::HandleVtEventL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiStateResetting::HandleVtEventL(
    const TInt aEvent )
    {
    __VTPRINTENTER( "TVtUiStateResetting.HandleVtEventL" )
    TEventResponse handled = EEventHandled;
    switch ( aEvent )
        {
    // While resetting appUi should not handle these events.
    case KVtEngSourceChanged:
    case KVtEngCameraChanged:
    case KVtEngSourceCapsChanged:
    case KVtEngSessionStateChanged:
    case KVtEngDurationSettingChanged:
    case KVtEngAudioOutputVolumeChanged:
    case KVtEngAudioRoutingAvailabilityChanged:
    case KVtEngAudioRoutingChanged:
    case KVtEngAudioMuted:
    case KVtEngAudioUnmuted:
    case KVtEngRemoteVideoStopped:
    case KVtEngSessionWaitingCallActive:
    case KVtEngSessionWaitingCallInactive:
        break;
    default:
        // allow appUi to handle other events
        handled = EEventNotHandled;
        break;
        }
    __VTPRINTEXIT( "TVtUiStateResetting.HandleVtEventL" )
    return handled;
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::HandleCommandL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiStateResetting::HandleCommandL(
    const TInt /*aCommand*/ )
    {
    __VTPRINTENTER( "TVtUiStateResetting.HandleCommandL" )
    /* All commands ignored while resetting. CAknAppUi::Exit() is called
       when shutdown is completed with asistance of CVtUiAppShutter */
    __VTPRINTEXIT( "TVtUiStateResetting.HandleCommandL" )
     return EEventHandled;
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::HandleForegroundChangedL
// -----------------------------------------------------------------------------
//
TBool TVtUiStateResetting::HandleForegroundChangedL(
    const TBool /*aIsForeground*/ )
    {
    __VTPRINTENTER( "TVtUiStateResetting.HandleForegroundChangedL" )
    __VTPRINTEXIT( "TVtUiStateResetting.HandleForegroundChangedL" )
    // not on "foreground" while resetting
    return EFalse;
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::HandleLayoutChangedL
// -----------------------------------------------------------------------------
//
void TVtUiStateResetting::HandleLayoutChangedL()
    {
    __VTPRINTENTER( "TVtUiStateResetting.HandleLayoutChangedL" )
    // no-op (overrides default behavior)
    __VTPRINTEXIT( "TVtUiStateResetting.HandleLayoutChangedL" )
    }
        
// -----------------------------------------------------------------------------
// TVtUiStateResetting::OpenL
// -----------------------------------------------------------------------------
//
void TVtUiStateResetting::OpenL()
    {
    __VTPRINTENTER( "TVtUiStateResetting.OpenL" )
    SetExecState( TVtUiStates::EExecStateResetting );
    iCtx.StopDtmfTone();
    iCtx.ChangeApplicationFocus( EFalse );
    
    if ( iCommand != KVtEngCommandNone )
        {        
        // Command is either KVtEngTerminateSession or KVtEngSwitchToVoice
        // Need to wait for callback before ShutdownL can be called on context.
        iCtx.DoExecuteCmdL( iCommand, NULL );
        }
    else
        {
        // This branch is executed when resetting state is opened due
        // to emergency call or state change to one causing shutdown.
        // No need to wait for any callbacks (emergency call callback
        // handled by CVtUiAppShutter).
        iCtx.ShutdownL();
        }
    __VTPRINTEXIT( "TVtUiStateResetting.OpenL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateResetting::Close
// -----------------------------------------------------------------------------
//
void TVtUiStateResetting::Close()
    {
    __VTPRINTENTER( "TVtUiStateResetting.Close" )
    SetExecState( TVtUiStates::EExecStateFinalized );
    if ( TVtUiStateResetting::iInstance )
        {
        delete TVtUiStateResetting::iInstance;
        TVtUiStateResetting::iInstance = NULL;
        }
    __VTPRINTEXIT( "TVtUiStateResetting.Close" )
    }

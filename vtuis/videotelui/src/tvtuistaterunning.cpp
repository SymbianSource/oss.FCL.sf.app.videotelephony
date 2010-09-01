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
* Description:  running (normal operation) application state
*
*/


#include "tvtuistates.h"
#include "tvtuiappstates.h"
#include "mvtuistatecontext.h"
#include "cvtuiappshutter.h"
#include "videotelui.hrh"
#include <cvtlogger.h>
#include <vtengevents.h>
#include <StringLoader.h>
#include <AknQueryDialog.h>
#include <videotelui.rsg>

TVtUiStateRunning* TVtUiStateRunning::iInstance = NULL;

// c++ constructor
TVtUiStateRunning::TVtUiStateRunning(
    MVtUiStateContext& aCtx, TVtUiStates& aUiStates )
    : TVtUiAppStateBase( aCtx, aUiStates ), iCreateVoiceCallDlg( NULL )
    {
    }

// Destructor
TVtUiStateRunning::~TVtUiStateRunning()
    {
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::InstanceL
// -----------------------------------------------------------------------------
//
TVtUiStateRunning * TVtUiStateRunning::InstanceL(
    MVtUiStateContext& aCtx,
    TVtUiStates& aUiStates )
    {
    __VTPRINTENTER( "UiStateRunning.InstanceL" )
    if ( iInstance == NULL )
        iInstance = new ( ELeave ) TVtUiStateRunning( aCtx, aUiStates );
    __VTPRINTEXIT( "UiStateRunning.InstanceL" )
    return iInstance;
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::HandleVtEventL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiStateRunning::HandleVtEventL(
    const TInt aEvent )
    {
    __VTPRINTENTER( "UiStateRunning.HandleVtEventL" )
    // let TVtUiAppStateBase base class do common tasks
    TEventResponse handled = TVtUiAppStateBase::HandleVtEventL( aEvent );
    switch ( aEvent )
        {
    case KVtEngDeviceLockOn:
    case KVtEngDeviceLockOff:
        TVtUiAppStateBase::HandleVtEventL( aEvent );
        if ( aEvent == KVtEngDeviceLockOff )
            {
            iCtx.ChangeApplicationFocus( ETrue );
            }
        break;
    case KVtEngSessionStateChanged:
        if ( CheckEndActiveCallL() )
            {
            // At this point shutdown is in progress. Don't allow
            // appUi to do actions due to this event.
            handled = EEventHandled;
            }
        break;
    default:
        break;
        }
    __VTPRINTEXIT( "UiStateRunning.HandleVtEventL" )
    return handled;
    }


// -----------------------------------------------------------------------------
// TVtUiStateRunning::HandleCommandL
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase::TEventResponse TVtUiStateRunning::HandleCommandL(
    const TInt aCommand )
    {
    __VTPRINTENTER( "UiStateRunning.HandleCommandL" )
    /** By default all commands are enabled by running state.
      * Other details command validations are done elsewhere
      */
    TEventResponse handled = EEventHandled;
    switch ( aCommand )
        {
    case EVtUiCmdEndActiveCall:
        {
        const MVtEngSessionInfo::TSessionState state = SessionState( EFalse );
        if ( state == MVtEngSessionInfo::EOpen )
            {
            ShutdownWithEngineCommandL( KVtEngTerminateSession );
            }
        }
        break;
    case EVtUiCmdCreateVoice:
        CreateVoiceCallL();
        break;
    case EVtUiCmdDialEmergency:
        // Attempt emergency call. Note that emergency number check is done
        // after calling DialEmergencyCallL and if supplied number is not
        // emergency leave occurs.
        TRAP_IGNORE( DialEmergencyCallL() );
        break;
    default:
        handled = TVtUiAppStateBase::HandleCommandL( aCommand );
        break;
        }
    __VTPRINTEXITR( "UiStateRunning.HandleCommandL %d", handled )
    return handled;
    }


// -----------------------------------------------------------------------------
// TVtUiStateRunning::HandleForegroundChangedL
// -----------------------------------------------------------------------------
//
TBool TVtUiStateRunning::HandleForegroundChangedL( const TBool aIsForeground )
    {
    __VTPRINTENTER( "UiStateRunning.HandleForegroundChangedL" )

    // Closes create voice call dialog if it is open
    delete iCreateVoiceCallDlg; iCreateVoiceCallDlg = NULL;

    SetLightsState( aIsForeground );

    iCtx.RefreshL( MVtUiStateContext::ENaviPane );

    TBool handleAsForeground( aIsForeground );
    TPtrC8 params( reinterpret_cast< TUint8* >( &handleAsForeground ),
        sizeof( TBool ) );
    iCtx.DoExecuteCmdL( KVtEngSetUIForeground, &params );
    __VTPRINTEXIT( "UiStateRunning.HandleForegroundChangedL" )
    return handleAsForeground;
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::PreHandleForegroundChangedL
// -----------------------------------------------------------------------------
//
TBool TVtUiStateRunning::PreHandleForegroundChangedL( const TBool aIsForeground )
    {
    __VTPRINTENTER( "UiStateRunning.PreHandleForegroundChangedL" )
    TBool handleAsForeground( aIsForeground );
    TPtrC8 params( reinterpret_cast< TUint8* >( &handleAsForeground ), sizeof( TBool ) );
    iCtx.DoExecuteCmdL( KVtEngSetUIForeground, &params );
    __VTPRINTEXIT( "UiStateRunning.PreHandleForegroundChangedL" )
    return handleAsForeground;
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::HandleLayoutChangedL
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::HandleLayoutChangedL( )
    {
    __VTPRINTENTER( "UiStateRunning.HandleLayoutChangedL" )
    iUiStates.SetLayoutChangeNeeded( EFalse );
    iCtx.DoHandleLayoutChangedL();
    __VTPRINTEXIT( "UiStateRunning.HandleLayoutChangedL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::StartDtmfTone
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::StartDtmfTone( const TChar& aTone )
    {
    iCtx.StartDtmfTone( aTone );
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::StopDtmfTone
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::StopDtmfTone()
    {
    iCtx.StopDtmfTone();
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::CreateVoiceCallL
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::CreateVoiceCallL()
    {
    __VTPRINTENTER( "TVtUiStateRunning.CreateVoiceCallL" )
    HBufC* prompt =
    	StringLoader::LoadLC( R_VIDEOTELUI_QTN_QUERY_CREATE_VOICE_CALL );

    // Create and initialize query dialog
    CAknQueryDialog* createVoiceCallDlg = CAknQueryDialog::NewL();
    CleanupStack::PushL( createVoiceCallDlg );
    createVoiceCallDlg->SetPromptL( *prompt );
    CleanupStack::Pop(); // createVoiceCallDlg

    iCreateVoiceCallDlg = createVoiceCallDlg;
    TInt result( KErrNone );
    TRAPD( error, result = iCreateVoiceCallDlg->ExecuteLD(
        R_VIDEOTELUI_CREATE_VOICE_QUERY ) );
    // Just set to NULL because ExecuteLD() deletes instance
    iCreateVoiceCallDlg = NULL;
    // Leave if ExecuteLD() left
    User::LeaveIfError( error );
    CleanupStack::PopAndDestroy( ); // prompt
    if ( result )
        {
        //user answered yes
		iCtx.DoExecuteCmdL( KVtEngSwitchToVoice, NULL );
        }
    __VTPRINTEXITR( "TVtUiAppStateBase.CreateVoiceCallL %d", result )
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::ShutdownWithEngineCommandL
// Starts shutdown with command to engine.
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::ShutdownWithEngineCommandL( const TInt aCommand )
    {
    __VTPRINTENTER(
        "TVtUiStateRunning.ShutdownWithEngineCommandL" )
    TVtUiAppStateBase* resetState =
        TVtUiStateResetting::InstanceL( iCtx, iUiStates, aCommand ); 
    CVtUiAppShutter* shutter = CVtUiAppShutter::InstanceL( *resetState );
    if ( shutter )
        {
        // open resetting state, handles engine command request/reply
        ChangeStateL( *resetState );
#ifdef _DEBUG
        __VTPRINTEXIT(
            "TVtUiStateRunning.ShutdownWithEngineCommandL 1" )
        return;
#endif
        }    
       
    __VTPRINTEXIT(
        "TVtUiStateRunning.ShutdownWithEngineCommandL 0" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::DialEmergencyCallL
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::DialEmergencyCallL()
    {
    __VTPRINTENTER(
        "TVtUiStateRunning.DialEmergencyCallL" )
    TVtUiAppStateBase* resetState =
        TVtUiStateResetting::InstanceL( iCtx, iUiStates );
    CVtUiAppShutter* shutter = CVtUiAppShutter::InstanceL( *resetState );
    if ( shutter )
        {
        // Make emergency call and proceed when 1) state has given permission 
        // and 2) callback from emergency call api is received
        shutter->ShutdownWithEmergencyCallL( iCtx );
        ChangeStateL( *resetState );
        }
    __VTPRINTEXIT( "TVtUiStateRunning.DialEmergencyCallL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::OpenL
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::OpenL()
    {
    __VTPRINTENTER( "TVtUiStateRunning.OpenL" )
    SetExecState( TVtUiStates::EExecStateRunning );
    iCtx.RefreshStatesL();
    __VTPRINTEXIT( "TVtUiStateRunning.OpenL" )
    }

// -----------------------------------------------------------------------------
// TVtUiStateRunning::Close
// -----------------------------------------------------------------------------
//
void TVtUiStateRunning::Close()
    {
    __VTPRINTENTER( "TVtUiStateRunning.Close" )
    if ( TVtUiStateRunning::iInstance )
        {
        delete TVtUiStateRunning::iInstance;
        TVtUiStateRunning::iInstance = NULL;
        }
    __VTPRINTEXIT( "TVtUiStateRunning.Close" )
    }

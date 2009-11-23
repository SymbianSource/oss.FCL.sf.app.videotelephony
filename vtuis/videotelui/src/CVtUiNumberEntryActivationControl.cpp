/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiNumberEntryActivationControl
*                control class.
*
*/



// INCLUDE FILES
#include    "CVtUiNumberEntryActivationControl.h"
#include    "CVtUiAppUi.h"
#include    "VtUiUtility.h"

#include    <aknutils.h>
#include    <aknsutils.h>
#include    <eikenv.h>
#include    <cvtlogger.h>

// CONSTANTS

// Control priority for the forwarder control. Above all other controls.
extern const TInt KVtUiNumberEntryActivationPriority =
    ECoeStackPriorityEnvironmentFilter + 100;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::CVtUiNumberEntryActivationControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiNumberEntryActivationControl::CVtUiNumberEntryActivationControl(
        CVtUiAppUi& aAppUi )
    : iAppUi( aAppUi ), iIsActive ( ETrue )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryActivationControl::ConstructL( const TRect& aRect )
    {
    // Create invisible control.
    CreateWindowL();
    MakeVisible( EFalse );
    SetRect( aRect );

    iAppUi.AddToStackL(
        this,
        KVtUiNumberEntryActivationPriority,
        ECoeStackFlagRefusesFocus );
    iAddedToStack = ETrue;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::~CVtUiNumberEntryActivationControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiNumberEntryActivationControl::~CVtUiNumberEntryActivationControl()
    {
    AknsUtils::DeregisterControlPosition( this );

    if ( iAddedToStack )
        {
        iAppUi.RemoveFromStack( this );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::Draw
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryActivationControl::Draw( const TRect& /*aRect*/ ) const
    {
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryActivationControl::SizeChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::PositionChanged
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryActivationControl::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CVtUiNumberEntryActivationControl::OfferKeyEventL(
        const TKeyEvent& aKeyEvent,
        TEventCode aType )
    {
    __VTPRINTENTER( "VtUiNumberEntryAC.OfferKeyEvent" )
    TBool numberEntryOpen = EFalse;
    TChar dtmfTone;
    TBool playDtmfTone = EFalse;
    TKeyResponse keyResponse = EKeyWasNotConsumed;
    if ( aKeyEvent.iScanCode == EStdKeyYes )
        {
        // send key is always consumed to prevent event forwarding to telephony
        // EStdKeyYes is scan code for send key, iCode cannot be used because
        // it is valid only when event type is EEventKey (not in up/down events)
        keyResponse = EKeyWasConsumed;
        }    
    if ( !iIsActive )
        {
        return keyResponse;
        }

    if ( !aKeyEvent.iRepeats )
        {
        if ( VtUiUtility::IsDTMFEvent( aKeyEvent, dtmfTone ) )
            {
            numberEntryOpen = iAppUi.OpenNumberEntryL();
            playDtmfTone = ( aType == EEventKey );
            }
        else if ( aKeyEvent.iCode == EKeyPhoneSend )
            {
            keyResponse = iAppUi.HandlePhoneSendKeyL( aKeyEvent, aType );
            }
        }

    if ( numberEntryOpen )
        {
        iEikonEnv->SyncNotifyFocusObserversOfChangeInFocus();
        }

    // Tone actions are delegated to current state for validation.
    if ( playDtmfTone )
        {        
        iAppUi.State().StartDtmfTone( dtmfTone );
        }
    else if ( aType == EEventKeyUp )
        {
        iAppUi.State().StopDtmfTone();
        } 
    __VTPRINTEXITR( "VtUiNumberEntryAC.OfferKeyEvent %d", keyResponse )
    return keyResponse;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryActivationControl::SetActive
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryActivationControl::SetActive( TBool aIsActive )
    {
    iIsActive = aIsActive;
    }

//  End of File

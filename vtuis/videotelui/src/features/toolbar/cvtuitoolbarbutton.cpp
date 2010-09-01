/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CVtUiToolbarButton implementation.
*
*/


// INCLUDE FILES
#include    <cvtlogger.h>
#include    "cvtuitoolbarbutton.h"
#include    "CVtUiAppUi.h"
#include    "videotelui.hrh"

// -----------------------------------------------------------------------------
// CVtUiNaviPane::NewL
// -----------------------------------------------------------------------------
//
CVtUiToolbarButton* CVtUiToolbarButton::NewL( TInt aResourceId,
	CVtUiAppUi& aAppUi, TInt aCmdId  )
    {
    __VTPRINTENTER( "CVtUiToolbarButton.NewL" )
    CVtUiToolbarButton* self = CVtUiToolbarButton::NewLC( aResourceId, aAppUi,
        aCmdId );
    CleanupStack::Pop( self );
    __VTPRINTEXIT( "CVtUiToolbarButton.NewL" )
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::NewLC
// -----------------------------------------------------------------------------
//
CVtUiToolbarButton* CVtUiToolbarButton::NewLC( TInt aResourceId,
	CVtUiAppUi& aAppUi, TInt aCmdId  )
    {
    __VTPRINTENTER( "CVtUiToolbarButton.NewLC" )
    CVtUiToolbarButton* self = new ( ELeave ) CVtUiToolbarButton( aAppUi,
        aCmdId );
    CleanupStack::PushL( self );
    self->ConstructL();
    self->ConstructFromResourceL( aResourceId );
    __VTPRINTEXIT( "CVtUiToolbarButton.NewLC" )
    return self;
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::~CVtUiToolbarButton
// ----------------------------------------------------------------------------
//
CVtUiToolbarButton::~CVtUiToolbarButton()
    {
    __VTPRINTENTER( "CVtUiToolbarButton.~" )
    __VTPRINTEXIT( "CVtUiToolbarButton.~" )
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::CVtUiToolbarButton
// ----------------------------------------------------------------------------
//
CVtUiToolbarButton::CVtUiToolbarButton( CVtUiAppUi& aAppUi, TInt aCmdId )
: CAknButton( 0 ), iAppUi( aAppUi ), iCmdId ( aCmdId ),
    iIsBlockingKeyEvents ( EFalse ), iIsBlockingPointerEvents( EFalse )
    {
    __VTPRINTENTER( "CVtUiToolbarButton.CVtUiToolbarButton" )
    __VTPRINTEXIT( "CVtUiToolbarButton.CVtUiToolbarButton")
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::ShowHelpL
// ----------------------------------------------------------------------------
//
void CVtUiToolbarButton::ShowHelpL()
    {
    __VTPRINTENTER( "CVtUiToolbarButton.ShowHelpL" )
    CAknButton::ShowHelpL();
    __VTPRINTEXIT( "CVtUiToolbarButton.ShowHelpL")
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::CmdId
// ----------------------------------------------------------------------------
//
TInt CVtUiToolbarButton::CmdId() const
    {
    __VTPRINTENTER( "CVtUiToolbarButton.CmdId" )
    __VTPRINTEXIT( "CVtUiToolbarButton.CmdId")
    return iCmdId;
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::BlockPointerEvents
// ----------------------------------------------------------------------------
//
void CVtUiToolbarButton::BlockPointerEvents( TBool aIsBlocking )
    {
    __VTPRINTENTER( "CVtUiToolbarButton.BlockPointerEvents" )
    iIsBlockingPointerEvents = aIsBlocking;
    __VTPRINTEXITR( "CVtUiToolbarButton.BlockPointerEvents=%d", aIsBlocking )
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::BlockKeyEvents
// ----------------------------------------------------------------------------
//
void CVtUiToolbarButton::BlockKeyEvents( TBool aIsBlocking )
    {
    __VTPRINTENTER( "CVtUiToolbarButton.BlockKeyEvents" )
    iIsBlockingKeyEvents = aIsBlocking;
    __VTPRINTEXITR( "CVtUiToolbarButton.BlockKeyEvents=%d", aIsBlocking )
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CVtUiToolbarButton::OfferKeyEventL( const TKeyEvent& aKeyEvent,
    TEventCode aType )
    {
    __VTPRINTENTER( "CVtUiToolbarButton.OfferKeyEventL" )
    if ( IsCommandActive() && iIsBlockingKeyEvents )
        {
         __VTPRINTEXIT( "CVtUiToolbarButton.OfferKeyEventL.Blocked" )
        return EKeyWasConsumed;
        }
 	__VTPRINTEXIT( "CVtUiToolbarButton.OfferKeyEventL" )
    return CAknButton::OfferKeyEventL( aKeyEvent, aType);
   }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CVtUiToolbarButton::HandlePointerEventL( const
    TPointerEvent& aPointerEvent )
    {
    __VTPRINTENTER( "CVtUiToolbarButton.HandlePointerEventL" )
    if ( IsCommandActive() && iIsBlockingPointerEvents )
        {
        __VTPRINTEXIT( "CVtUiToolbarButton.HandlePointerEventL.Blocked" )
        return;
        }
    __VTPRINTEXIT( "CVtUiToolbarButton.HandlePointerEventL.To.AknButton" )
    return CAknButton::HandlePointerEventL( aPointerEvent );
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::StatesCount
// ----------------------------------------------------------------------------
//
TInt CVtUiToolbarButton::StatesCount() const
    {
    return iStates->Count();
    }

// ----------------------------------------------------------------------------
// CVtUiToolbarButton::IsCommandActive
// ----------------------------------------------------------------------------
//
TBool CVtUiToolbarButton::IsCommandActive() const
    {
    __VTPRINTENTER( "CVtUiToolbarButton.IsCommandActive" )
    TBool value( EFalse );
    value = ( iAppUi.IsActiveCommand( EVtUiCmdDisableVideo ) ||
              iAppUi.IsActiveCommand( EVtUiCmdEnableVideo ) ||
              iAppUi.IsActiveCommand( EVtUiCmdEnableAudio ) ||
              iAppUi.IsActiveCommand( EVtUiCmdDisableAudio ) ||
              iAppUi.IsActiveCommand( EVtUiCmdUsePrimaryCamera ) ||
              iAppUi.IsActiveCommand( EVtUiCmdUseSecondaryCamera ) ||
              // Audio routing to blocking
              iAppUi.IsActiveCommand( EVtUiCmdActivateBT ) ||
              iAppUi.IsActiveCommand( EVtUiCmdSwitchFromBTToIHF ) ||
              iAppUi.IsActiveCommand( EVtUiCmdActivateLoudspeaker ) ||
              iAppUi.IsActiveCommand( EVtUiCmdDeactivateLoudspeaker )
              );

    __VTPRINTEXITR( "CVtUiToolbarButton.IsCommandActive=%d", value )
    return value;
    }
//  End of File


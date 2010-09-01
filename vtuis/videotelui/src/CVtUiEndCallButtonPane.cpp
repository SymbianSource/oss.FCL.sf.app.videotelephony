/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies). 
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
* Description:  The container pane of end button.
*
*/

#include    <aknenv.h>
#include    <aknlayoutscalable_apps.cdl.h>
#include    <AknsBasicBackgroundControlContext.h>
#include    <AknsDrawUtils.h>
#include    <AknsSkinInstance.h>
#include    <videotelui.rsg>
#include    <cvtlogger.h>
#include    <featmgr.h>

#include    "CVtUiEndCallButton.h"
#include    "CVtUiEndCallButtonPane.h"
#include    "videotelui.hrh"
#include    "CVtUiAppUi.h"

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::CVtUiEndCallButtonPane
// -----------------------------------------------------------------------------
//
CVtUiEndCallButtonPane::CVtUiEndCallButtonPane()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::NewL
// -----------------------------------------------------------------------------
//
CVtUiEndCallButtonPane* CVtUiEndCallButtonPane::NewL( const TRect& aRect )
    {
    CVtUiEndCallButtonPane* self =
            new (ELeave) CVtUiEndCallButtonPane();
    CleanupStack::PushL(self);
    self->ConstructL( aRect );
    CleanupStack::Pop(); // self;
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButtonPane::ConstructL( const TRect& aRect )
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.ConstructL" )
    // Create a window for this application view
    CreateWindowL();
    
    // Set the windows size
    SetRect( aRect );

    CreateButtonUsingResourceL();
    GetButtonLayoutData();
    

    iBgContext = CAknsBasicBackgroundControlContext::NewL(
            KAknsIIDQsnBgAreaMain, Rect(), ETrue );
    
    // Activate the window, which makes it ready to be drawn
    ActivateL();
    
    // For set non focus and recieve all point event
    SetNonFocusing();
    ClaimPointerGrab( ETrue );

    __VTPRINTEXIT( "CVtUiEndCallButtonPane.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::CVtUiEndCallButtonPane
// -----------------------------------------------------------------------------
//
CVtUiEndCallButtonPane::~CVtUiEndCallButtonPane()
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.~" )
    if ( iEndButton )
        {
        delete iEndButton;
        }
    
    if ( iBgContext )
        {
        delete iBgContext;
        }
    __VTPRINTEXIT( "CVtUiEndCallButtonPane.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CVtUiEndCallButtonPane::CountComponentControls() const
    {
    return iEndButton ? 1 : 0;
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CVtUiEndCallButtonPane::ComponentControl(TInt aIndex) const
    {
    return iEndButton;
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::Draw
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButtonPane::Draw(const TRect& aRect) const
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.Draw" )
    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, cc, this, gc, Rect() );
    __VTPRINTEXIT( "CVtUiEndCallButtonPane.Draw" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButtonPane::SizeChanged()
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.SizeChanged" )
    if( iEndButton )
        {
        GetButtonLayoutData();
        }
    if( iBgContext )
        {
        TRect bgRect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, bgRect );
        iBgContext->SetRect( bgRect );
        }
    __VTPRINTEXIT( "CVtUiEndCallButtonPane.SizeChanged" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::MopSupplyObject
// -----------------------------------------------------------------------------
//
TTypeUid::Ptr CVtUiEndCallButtonPane::MopSupplyObject(TTypeUid aId)
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.MopSupplyObject" )
    // Required during rendering of the background skin in Draw()
    if (aId.iUid == MAknsControlContext::ETypeId)
        {
         __VTPRINTEXIT( "CVtUiEndCallButtonPane.MopSupplyObject.1" )
        return MAknsControlContext::SupplyMopObject( aId, iBgContext );
        }
    __VTPRINTEXIT( "CVtUiEndCallButtonPane.MopSupplyObject.2" )
    return CCoeControl::MopSupplyObject( aId );
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::HandleControlEventL
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButtonPane::HandleControlEventL( CCoeControl* aControl, 
                                                  TCoeEvent aEventType )
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.HandleControlEventL" )
    if ( aEventType != EEventStateChanged )
        {
        __VTPRINTEXIT( "CVtUiEndCallButtonPane.HandleControlEventL" )
        return;
        }
    CVtUiAppUi* appUi = STATIC_CAST( CVtUiAppUi*, CCoeEnv::Static()->AppUi() );
    appUi->HandleCommandL( EVtUiCmdEndActiveCall );
    __VTPRINTEXIT( "CVtUiEndCallButtonPane.HandleControlEventL" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::CreateButtonUsingResourceL
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButtonPane::CreateButtonUsingResourceL()
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.CreateButtonUsingResourceL" )
    iEndButton = CVtUiEndCallButton::NewL();
    iEndButton->ConstructFromResourceL( R_VIDEOTELUI_END_CALL_BUTTON );
    iEndButton->SetContainerWindowL( *this );
    iEndButton->SetRect( Rect() );
    iEndButton->SetObserver( this );
    iEndButton->MakeVisible( ETrue );
    iEndButton->ActivateL();
    __VTPRINTEXIT( "CVtUiEndCallButtonPane.CreateButtonUsingResourceL" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::GetButtonLayoutData
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButtonPane::GetButtonLayoutData()
    {
    __VTPRINTENTER( "CVtUiEndCallButtonPane.GetButtonLayoutData" )
    AknLayoutUtils::LayoutControl( 
            iEndButton, 
            Rect(), 
            AknLayoutScalable_Apps::bg_button_pane_cp034( 0, 0, 0) );

    
    TAknLayoutText text;
    text.LayoutText( Rect(), 
            AknLayoutScalable_Apps::vidtel_button_pane_t1( 
                    0 ).LayoutLine());

    TAknLayoutRect icon;
    icon.LayoutRect( Rect(), 
            AknLayoutScalable_Apps::vidtel_button_pane_g1( 
                    0 ).LayoutLine());
    
    iEndButton->SetIconSize( icon.Rect().Size() );

    iEndButton->SetLayout( text, icon.Rect() );
     __VTPRINTEXIT( "CVtUiEndCallButtonPane.GetButtonLayoutData" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButtonPane::SetEnabled
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButtonPane::SetEnabled( TBool aEnabled )
    {
    iEndButton->SetDimmed( !aEnabled );
    DrawNow();
    }

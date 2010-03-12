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
* Description:  Button of ending call.
*
*/


#include    <AknsConstants.h>
#include    <AknsSkinInstance.h>
#include    <data_caging_path_literals.hrh>
#include    <AknsFrameBackgroundControlContext.h>
#include    <aknlayoutscalable_avkon.cdl.h>
#include    <AknsDrawUtils.h>
#include    <gulicon.h>
#include    <AknIconUtils.h>
#include    <AknBidiTextUtils.h>
#include    <cvtlogger.h>

#include    "CVtUiEndCallButton.h"
#include    "VtUiLayout.h"


// -----------------------------------------------------------------------------
// CVtUiEndCallButton::CVtUiEndCallButton
// -----------------------------------------------------------------------------
//
CVtUiEndCallButton::CVtUiEndCallButton(): CAknButton( 0 )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::NewL
// -----------------------------------------------------------------------------
//
CVtUiEndCallButton* CVtUiEndCallButton::NewL()
    {
    CVtUiEndCallButton* self = new (ELeave) CVtUiEndCallButton();
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(); // self;
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::ConstructL()
    {
    CAknButton::ConstructL();
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::~CVtUiEndCallButton
// -----------------------------------------------------------------------------
//
CVtUiEndCallButton::~CVtUiEndCallButton()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::ConstructFromResourceL
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::ConstructFromResourceL( const TInt aResourceId )
    {    
    CAknButton::ConstructFromResourceL( aResourceId );
    
    // function button text color
    SetTextColorIds( KAknsIIDQsnTextColors, 
                              EAknsCIQsnTextColorsCG65 );
    
    // Customize icons
    LoadButtonIcon( EVtUiBitmap_qgn_indi_button_end_active_call,
                    EVtUiBitmap_qgn_indi_button_end_active_call_mask );
    
    if ( State()->Icon() )
        {
        SetIconScaleMode( EAspectRatioPreserved );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::SetLayout
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::SetLayout( const TAknLayoutText aLayoutText,
                                        const TRect aIconRect ) 
    {
    iLayoutText = aLayoutText;
    iIconRect = aIconRect;
    } 

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::Draw
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::Draw(const TRect& aRect) const
    {
    __VTPRINTENTER( "CCVtUiEndCallButton::Draw" )
    TAknLayoutRect centerLayout;
    centerLayout.LayoutRect( aRect,
        AknLayoutScalable_Avkon::toolbar_button_pane_g1().LayoutLine() );
    TRect innerRect = centerLayout.Rect();
    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();

    TAknsItemID frameId = KAknsIIDQsnFrButtonNormalReject;
    
    if ( iButtonPressed )
        {
        frameId = KAknsIIDQsnFrButtonPressedReject;
        }
    else if ( IsDimmed() )
        {
        frameId = KAknsIIDQsnFrButtonInactiveReject;
        }    
    
    iBgContext->SetFrame( frameId );
    iBgContext->SetCenter( KAknsIIDQsnFrButtonCenterNormal );
    iBgContext->SetFrameRects( aRect, innerRect );
    
    if ( !AknsDrawUtils::Background( skin, 
                                    iBgContext, 
                                    NULL, 
                                    gc, 
                                    aRect, 
                                    KAknsDrawParamNoClearUnderImage ) )
        {
        gc.SetBrushColor( KRgbRed );
        gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
        gc.DrawRect( aRect );
        }
    
    LayoutIconAndText( gc );
    __VTPRINTEXIT( "CCVtUiEndCallButton::Draw" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::HandleResourceChange( TInt aType )
    {
    __VTPRINTENTER( "CCVtUiEndCallButton::HandleResourceChange" )
    CAknButton::HandleResourceChange( aType );
    
    if ( aType == KAknsMessageSkinChange )
        {
        LoadButtonIcon( EVtUiBitmap_qgn_indi_button_end_active_call,
                        EVtUiBitmap_qgn_indi_button_end_active_call_mask );
        }
    __VTPRINTEXIT( "CCVtUiEndCallButton::HandleResourceChange" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::GetTextColors
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::GetTextColors( TRgb& aPenColor ) const
    {
    __VTPRINTENTER( "CCVtUiEndCallButton::GetTextColors" )
    if ( IsDimmed() ) 
        {
        aPenColor = iEikonEnv->ControlColor( EColorButtonTextDimmed, *this ); 
        }
    else if ( iButtonPressed )
        {
        aPenColor = iEikonEnv->ControlColor( EColorButtonTextPressed, *this );
        }
    else
        {
        aPenColor = iEikonEnv->ControlColor( EColorButtonText, *this );
        }
    __VTPRINTEXIT( "CCVtUiEndCallButton::GetTextColors" )
    } 

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::LoadButtonIcon
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::LoadButtonIcon( TVtUiBitmapId aIconId, TVtUiBitmapId aMaskId )
    {
    __VTPRINTENTER( "CCVtUiEndCallButton::LoadButtonIcon" )
    CGulIcon* icon = NULL;
    TFileName fileName;
    TInt fileIndex;
    TInt maskIndex;
    TAknsItemID skinId = 
        VtUiLayout::MapBitmapToSkinId( aIconId );
    VtUiLayout::Resolve( aIconId, fileName, fileIndex );
    VtUiLayout::Resolve( aMaskId, fileName, maskIndex );
        
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    icon = AknsUtils::CreateGulIconL( skin, 
                                      skinId, 
                                      fileName, 
                                      fileIndex,
                                      maskIndex );
    
    if ( icon )       
        {
        CAknButtonState* state = State();
        // State takes ownership of icon
        state->SetIcon( icon );
        }
        __VTPRINTEXIT( "CCVtUiEndCallButton::LoadButtonIcon" )
    }

// -----------------------------------------------------------------------------
// CVtUiEndCallButton::LayoutIconAndText
// -----------------------------------------------------------------------------
//
void CVtUiEndCallButton::LayoutIconAndText( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "CCVtUiEndCallButton::LayoutIconAndText" )
    CAknButtonState* state = State();
    if ( !state  ||       
         !state->Icon() ||
         !state->Text().Length() )
        {
        return;
        } 
    TRgb penColor;
    TRgb brushColor;
    GetTextColors( penColor ); 
    
    iLayoutText.DrawText( aGc, state->Text(), EFalse, penColor );
    
    const CGulIcon* icon = GetCurrentIcon();

    if ( icon )
        {
        CFbsBitmap* buttonBmp = icon->Bitmap();
        CFbsBitmap* buttonMask = icon->Mask();
        
        if( buttonBmp && buttonMask )
            {
            aGc.BitBltMasked( iIconRect.iTl, buttonBmp,
                    iIconRect.Size(), buttonMask, EFalse );
            }
        }
    __VTPRINTEXIT( "CCVtUiEndCallButton::LayoutIconAndText" )
    }

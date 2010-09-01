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
* Description:  Transparent camera setting page.
*
*/



#include "cvtuitransparentsettingpage.h"
#include "mvtuisettingpageobserver.h"
#include "VtUiLayout.h"
#include <cvtlogger.h>
#include <aknsettingpage.h>
#include <aknlayoutscalable_apps.cdl.h>
#include <layoutmetadata.cdl.h>


/**
*  CVtUiTransparentSettingPage
*
*  Transparent camera setting page. Extends class CAknTransparentCameraSettingPage
*  with position related functionality.
*
*  @since S60 v3.2
*/
void CVtUiTransparentSettingPage::HandleLayoutChangeL()
    {
    GetTheLayoutData();
    }

// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::CVtUiTransparentSettingPage
// -----------------------------------------------------------------------------
//
CVtUiTransparentSettingPage::CVtUiTransparentSettingPage( TInt aResourceID, 
     TInt& aCurrentSelectionIndex, const MDesCArray* aItemArray) :
     CAknTransparentCameraSettingPage( aResourceID,
     aCurrentSelectionIndex, aItemArray )
     {
     }

// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::ConstructL
// -----------------------------------------------------------------------------
//            
void CVtUiTransparentSettingPage::ConstructL()
    {
    CAknTransparentCameraSettingPage::ConstructL();
    }
    

// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::~CVtUiTransparentSettingPage
// -----------------------------------------------------------------------------
//            
CVtUiTransparentSettingPage::~CVtUiTransparentSettingPage()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::SetNumberEntryControlObserver
// -----------------------------------------------------------------------------
//
void CVtUiTransparentSettingPage::SetSettingPageEventStateObserver( 
    MVtUiSettingPageObserver* aObserver )
    {
    iSettingPageObserver = aObserver;
    }

// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::GetTheLayoutData
// -----------------------------------------------------------------------------
//
void CVtUiTransparentSettingPage::GetTheLayoutData()
    {
    // Varieties
    TInt labelVariety = 6;
    TInt listboxVariety = 6;

    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        labelVariety = 5;
        listboxVariety = 5;
        }
       
    // Rect for label and shadow text   
    TRect labelRect = RectFromLayout( AknLayoutScalable_Apps::
       aid_placing_vt_set_title( labelVariety ) );
    
    // Rect for listbox control
    TRect listBoxRect = RectFromLayout( AknLayoutScalable_Apps::
        aid_placing_vt_set_content( listboxVariety ) );
   
     // Get text label from parent class
    CEikLabel* textLabel = TextLabel();
   
    // Set label's new positions
    if ( textLabel )
    	{
    	textLabel->SetPosition( labelRect.iTl );	
    	}
    
    // Get shadow text from parent class
    CEikLabel* shadowText = ShadowText();
   
    // Set shadow text's new positions if shadow text exists
    if( shadowText )
        {
        // This information should come from layout, but
        // also AknSettingPage does the positioning in this way.
        labelRect.Move( 1, 1 );
        shadowText->SetPosition( labelRect.iTl );
        }
    
    // Set new rect for listbox control
    ListBoxControl()->SetRect( listBoxRect );
    }
    
// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::DynamicInitL
// -----------------------------------------------------------------------------
//
void CVtUiTransparentSettingPage::DynamicInitL()
  {
  	GetTheLayoutData();
  }

// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::HandleControlEventL
// -----------------------------------------------------------------------------
//
void CVtUiTransparentSettingPage::HandleControlEventL( CCoeControl* /*aControl*/,
    TCoeEvent aEventType )
    {
    __VTPRINTENTER( "CVtUiTransparentSettingPage.HandleControlEventL" )
     if ( aEventType == EEventStateChanged )
        {
        if ( iSettingPageObserver )
            {
            iSettingPageObserver->ListStateChangedL();
            }
        __VTPRINT( DEBUG_GEN, " CVtUiTransparentSettingPage.EEventStateChanged" )
        }
    
    __VTPRINTEXIT( "CVtUiTransparentSettingPage.HandleControlEventL" )
    }

// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CVtUiTransparentSettingPage::HandleResourceChange(TInt aType)
    {
    CAknTransparentCameraSettingPage::HandleResourceChange(aType);
    GetTheLayoutData();
    }

// -----------------------------------------------------------------------------
// CVtUiTransparentSettingPage::RectFromLayout
// -----------------------------------------------------------------------------
// 
TRect CVtUiTransparentSettingPage::RectFromLayout(
    const TAknWindowComponentLayout& aComponentLayout ) const
    {
    __VTPRINTENTER( "CVtUiTransparentSettingPage.RectFromLayout" )
      
    TInt main_pane_variety( 0 );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
            {
            main_pane_variety = 4;
            }

    TAknWindowComponentLayout layout1 =
        AknLayoutScalable_Apps::main_pane( main_pane_variety );
    TAknWindowComponentLayout layout2 =
        AknLayoutScalable_Apps::main_video_tele_pane();

    TAknWindowLineLayout layout =
        TAknWindowComponentLayout::Compose(
         TAknWindowComponentLayout::Compose( layout1, layout2 ), aComponentLayout ).
            LayoutLine();
    
    TRect screen;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screen );
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( screen, layout );
    
    // setting page is window owning control and its position is relative to mainpane
    // layotdata is instead relative to screen
    TRect rect( layoutRect.Rect() ); 
    rect.Move( -PositionRelativeToScreen() );
    
    __VTPRINTEXIT( "CVtUiTransparentSettingPage.RectFromLayout" ) 
    return rect;
   }

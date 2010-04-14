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
* Description:  Softkey UI feature implementation.
*
*/


#include    <cvtengmodel.h>
#include    <mvtengcamerapreferences.h>
#include    <eikenv.h>
#include    <cvtlogger.h>
#include    <avkon.hrh>

#include    "cvtuiprefsettinglistbase.h"
#include    "CVtUiAppUi.h"
#include    "cvtuitransparentsettingpage.h"
#include    "CVtUiMainControl.h"
#include    "CVtUiContextControl.h"
#include    "CVtUiRemoteVideoControl.h"
#include    "cvtuifeaturemanager.h"
#include    "VtUiLayout.h"
#include    "CVtUiEndCallButtonPane.h"

#include    <layoutmetadata.cdl.h>

// constants
static const TInt KMaxNumberOfArrayItems = 5;
static const TInt KMaxNumberOfActiveItems = 5;
static const TInt KOrdinalPositionBase = 3;

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::~CVtUiPrefSettingListBase
// ---------------------------------------------------------------------------
// 
CVtUiPrefSettingListBase::~CVtUiPrefSettingListBase()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.~CVtUiPrefSettingListBase" )
    delete iViewfinderBitmap;
    delete iSettingPage;
    iActiveItems.Close();
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.~CVtUiPrefSettingListBase" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::InitFeatureL
// ---------------------------------------------------------------------------
// 
void CVtUiPrefSettingListBase::InitFeatureL()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.InitFeatureL" )
    ResizeBackroundBitmapRect();
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::IsPendingCmd
// ---------------------------------------------------------------------------
//
TBool CVtUiPrefSettingListBase::IsPendingCmd()
    {
    return iPendingSettingChangeCmd;
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::HandlePendingCmd
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::HandlePendingCmdL()
    {
    SettingPageItemChangedL( iOriginalSelection );
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::HandleSettingPageEventL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::HandleSettingPageEventL(
    CAknSettingPage* /*aSettingPage*/, TAknSettingPageEvent aEventType )
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.HandleSettingPageEventL" )
    const TInt currentItem = iSettingPage->ListBoxControl()->CurrentItemIndex();      
    switch ( aEventType )
        {
        case EEventSettingCancelled:
             {
             if ( iOriginalSelection != currentItem )
                {
                // Set back to orginal selection
                SettingPageItemChangedL( iOriginalSelection );
                iCurrentSelection = iOriginalSelection;
                }
             Stop();
             break;   
             }     
         case EEventSettingChanged:
             {
             SettingPageItemChangedL( currentItem );
             iOriginalSelection = currentItem;
             Stop();
             break;
             }
         case EEventSettingOked:
             {
             // Check if the current selection has changed
             if ( iOriginalSelection != currentItem )
                 {       
                 SettingPageItemChangedL( currentItem );
                 iOriginalSelection = currentItem;
                 iCurrentSelection = currentItem;
                 }                 
             Stop();                 
             break;
             }
         default:
             break;
        }
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.HandleSettingPageEventL" )        
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::ListStateChangedL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::ListStateChangedL()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.ListStateChangedL" )
    // Check if new item is focused in the selection list
    
    const TInt currentItem = iSettingPage->ListBoxControl()->CurrentItemIndex();
    if ( iCurrentSelection != currentItem )
        {
        // Update current selection
        iCurrentSelection = currentItem;
        // Adjust frame
        SettingPageItemChangedL( currentItem );    
        }    
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.ListStateChangedL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::StartSettingPageL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::StartSettingPageL()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.StartSettingPageL" )
    // Swap image places if needed
    iAppUi.SwitchViewFinderToMainPaneL();
    
    // Get context control's window priority and position
    iContextControlWindowPriority = iAppUi.ContextControl().DrawableWindow()
        ->OrdinalPriority();
    iContextControlWindowPosition = iAppUi.ContextControl().DrawableWindow()
        ->OrdinalPosition();
    
    // Get main control's window priority
    iMainControlWindowPriority= iAppUi.MainControl().DrawableWindow()
        ->OrdinalPriority();
    
    // Get remote video control's window priority and position
    iRemoteVideoControlWindowPriority = 
            iAppUi.RemoteVideoControl().DrawableWindow()->OrdinalPriority();
    iRemoteVideoControlWindowPosition = 
            iAppUi.RemoteVideoControl().DrawableWindow()->OrdinalPosition();
    
    // Get end call button pane priority and position
    iEndCallButtonPanePriority = 
            iAppUi.EndCallButtonPane().DrawableWindow()->OrdinalPriority();
    iEndCallButtonPanePosition = 
            iAppUi.EndCallButtonPane().DrawableWindow()->OrdinalPosition();
    
    // Rise context control's window priority othwerwise setting page will be
    // drawn partially over the context control window.
    iAppUi.ContextControl().DrawableWindow()->SetOrdinalPosition( 
        iContextControlWindowPosition, 
        iContextControlWindowPriority + 1 );
    
    // Rise remote video control's window priority othwerwise setting page 
    // will be drawn partially over the context control window.
    iAppUi.RemoteVideoControl().DrawableWindow()->SetOrdinalPosition(
        iRemoteVideoControlWindowPosition, 
        iRemoteVideoControlWindowPriority + 2 );
    
    // Rise end call button pane priority othwerwise setting page 
    // will be drawn partially over the context control window.
    iAppUi.EndCallButtonPane().DrawableWindow()->SetOrdinalPosition(
        iEndCallButtonPanePosition, 
        iEndCallButtonPanePriority + 1 );

    // Creates setting page
    CreateSettingPageL();
    // Launch setting page.
    iSettingPage->ExecuteLD( CAknSettingPage::EUpdateWhenAccepted, EFalse );
    iSettingPage = NULL;
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.StartSettingPageL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::StopSettingPageL
//    
//
void CVtUiPrefSettingListBase::StopSettingPageL()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.StopSettingPageL" )
    // Swap image places if needed  
    iAppUi.RestoreViewFinderL();
    
    if ( iSettingPage)
        {
        // Cancell the setting page
        TKeyEvent keyEvent;
        keyEvent.iCode =  EKeyEscape;
        iSettingPage->OfferKeyEventL( keyEvent, EEventKey );
        }
    
    TInt ordinalPos = KOrdinalPositionBase;
    
    // Set main control priority and position back to 
    // orginal value.
    iAppUi.MainControl().DrawableWindow()->SetOrdinalPosition( 
    		ordinalPos--, iMainControlWindowPriority );
      
    // Set end call button pane priority and position back to 
    // orginal value.
    iAppUi.EndCallButtonPane().DrawableWindow()->SetOrdinalPosition( 
    		ordinalPos--, iEndCallButtonPanePriority );
    
    // Set context control's window priority and position back to 
    // orginal value.
    iAppUi.ContextControl().DrawableWindow()->SetOrdinalPosition( 
    		ordinalPos--, iContextControlWindowPriority );
    
    // Set remote video control's window priority and position back to 
    // orginal value.
    iAppUi.RemoteVideoControl().DrawableWindow()->SetOrdinalPosition(
    		ordinalPos--, 
            iRemoteVideoControlWindowPriority );
    
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.StopSettingPageL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::SizeChanged
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::SizeChanged()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.SizeChanged" )
    ResizeBackroundBitmapRect();
    // Set new coordinates and size
    iSettingPage->SetBitmapPositionAndClipRect( iBitmapTopLeftCorner,
        iBitmapClippingRect );
    iSettingPage->HandleLayoutChangeL();
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.SizeChanged" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::UpdateBackground
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::UpdateBackground( CFbsBitmap* aFrame )
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.UpdateBackground" )
    if ( aFrame )
        {
        // aFrame is valid only in this callback, the bitmap
        // must be copied for use as the setting page background
        iViewfinderBitmap->Duplicate( aFrame->Handle() );
        if ( iSettingPage )
            {
            // Update background
            iSettingPage->ChangeBackground( iViewfinderBitmap );
            }
        }
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.UpdateBackground" )        
    }
    
// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::UpdateSettingL
// ---------------------------------------------------------------------------
// 
void CVtUiPrefSettingListBase::UpdateSettingL()
    {
    // if no active items do nothing
    if ( iActiveItems.Count() > 0 )
        {
        // user change the focuse in the list but not
        // select it indeed
        if( iOriginalSelection != iCurrentSelection )  
            SettingPageItemChangedL( iCurrentSelection );
        else
        // yes,user has tapped down the OK button to choose a item
            SettingPageItemChangedL( iOriginalSelection );        
        }
    }
        
// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::CVtUiPrefSettingListBase
// ---------------------------------------------------------------------------
//
CVtUiPrefSettingListBase::CVtUiPrefSettingListBase( CVtUiFeatureManager&
    aFeatureManager,  TVtUiFeatureId aFeatureId ) : CVtUiFeatureBase(
    aFeatureId, aFeatureManager ), iActiveItems( KMaxNumberOfActiveItems ), 
    iBitmapTopLeftCorner( 0, 0 ), iAppUi( aFeatureManager.AppUi() ),iPendingSettingChangeCmd( EFalse )
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.CVtUiPrefSettingListBase" )   
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.CVtUiPrefSettingListBase" )
    }


// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::ConstructL()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.ConstructL" )
    BaseConstructL();
    // Get camera preferences extension.
    iCameraPref = static_cast<MVtEngCameraPreferences*> (iFeatureManager.
        AppUi().Model().Extension( KVtEngExtensionCameraPreferences ) );
    // Create backgound bitmap
    iViewfinderBitmap = new ( ELeave ) CFbsBitmap();
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.ConstructL" )
    }
     
// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::ReadAndAppendItemL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::ReadAndAppendItemL( CDesCArray& aItems,
    TInt aResId )
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.ReadAndAppendItemL" )
    HBufC* text = iAppUi.GetEikonEnv()->AllocReadResourceLC( aResId );
    aItems.AppendL( *text );
    CleanupStack::PopAndDestroy(); // text
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.ReadAndAppendItemL" )
    }    
    
// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::CreateSettingPageL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSettingListBase::CreateSettingPageL()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.CreateSettingPageL" )
    CDesCArray* selectionArray = new ( ELeave ) 
        CDesCArraySeg( KMaxNumberOfArrayItems );
    CleanupStack::PushL( selectionArray );
    // Set items must be called before CurrentSelection function
    // Otherwise iActiveItems array is not populated
    iActiveItems.Reset();
    SetItemsL( *selectionArray );
    TInt resourceId = SettingPageResId();
    
    // Current selection is needed when a new item is focused in the list
    iCurrentSelection = iOriginalSelection;
    TInt current( CurrentSelection() );
    if ( !iSettingPage )
        {
        iSettingPage = new ( ELeave ) CVtUiTransparentSettingPage( resourceId,
            iCurrentSelection, selectionArray );
        iSettingPage->ConstructL();
        iSettingPage->SetSettingPageObserver( this );
        iSettingPage->SetSettingPageEventStateObserver( this );
        }
     CleanupStack::PopAndDestroy(); // selectionArray        
     ResizeBackroundBitmapRect();
     iSettingPage->SetBitmapPositionAndClipRect( iBitmapTopLeftCorner, 
        iBitmapClippingRect );            
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.CreateSettingPageL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSettingListBase::ShrinkBackroundBitmapRect
// ---------------------------------------------------------------------------
//    
void CVtUiPrefSettingListBase::ResizeBackroundBitmapRect()
    {
    __VTPRINTENTER( "CVtUiPrefSettingListBase.ResizeBackroundBitmapRect" )
    TRect parent( iAppUi.MainControl().Size() );
    TAknWindowLineLayout rect;
    TAknLayoutRect iStreamLayout;
    VtUiLayout::GetSecondWindowStreamLayout( rect, ETrue );
    iStreamLayout.LayoutRect( parent, rect );
    
    // In landscape rect from layout doesn't work 
    // for some reason
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        iBitmapClippingRect = parent;
        }
    else
        {
        iBitmapClippingRect = iStreamLayout.Rect();
        }
    
    iBitmapTopLeftCorner = iStreamLayout.Rect().iTl;
    __VTPRINTEXIT( "CVtUiPrefSettingListBase.ResizeBackroundBitmapRect" )
    }

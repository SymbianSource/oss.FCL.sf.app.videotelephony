/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Floating toolbar UI feature implementation.
*
*/


// INCLUDE FILES

#include    "cvtuifloatingtoolbar.h"
#include    "cvtuifeaturemanager.h"
#include    "mvtuicomponentmanager.h"
#include    "mvtuicommandmanager.h"
#include 	"cvtuitoolbarbutton.h"
#include    "videotelui.hrh"
#include 	"tVtuifeaturevariation.h"
#include    "tvtuistates.h"
#include    "cvtuitoolbarcmdpolicy.h"
#include    "cvtuitoolbarskmodifier.h"
#include    "CVtUiAppUi.h"
#include    <videotelui.rsg>
#include    <cvtlogger.h>
#include    <akntoolbar.h>
#include    <AknUtils.h>
#include    <aknlayoutscalable_apps.cdl.h>
#include    <layoutmetadata.cdl.h>
#include    <gfxtranseffect/gfxtranseffect.h>

// CONSTANTS
static const TInt KThreeToolbarbuttons = 3;
static const TInt KFourToolbarbuttons = 4;
static const TInt KFiveToolbarbuttons = 5;
static const TInt KSixToolbarbuttons = 6;
static const TInt KSevenToolbarbuttons = 7;


// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::NewL
// -----------------------------------------------------------------------------
//
CVtUiFloatingToolbar* CVtUiFloatingToolbar::NewL( CVtUiFeatureManager&
     aFeatureManager )
    {
    __VTPRINTENTER( "FloatingToolbar.NewL" )
        TVtUiSideVolumeKeysVariation svkvariation;
    if ( !svkvariation.IsSideVolumeKeysSupported() )
        {
        // User of this class should notice that newl could return null,
        // even if no leave happened.
        __VTPRINT(DEBUG_GEN, "Toolbar.NewL.NULL" )
        return NULL;
        }
    CVtUiFloatingToolbar* self = new ( ELeave ) CVtUiFloatingToolbar( 
        aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    __VTPRINTEXIT( "FloatingToolbar.NewL" )
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::CVtUiFloatingToolbar
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiFloatingToolbar::CVtUiFloatingToolbar( CVtUiFeatureManager& 
    aFeatureManager ) : CVtUiToolbarBase( aFeatureManager )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiFloatingToolbar::ConstructL()
    {
    __VTPRINTENTER( "FloatingToolbar.ConstructL" )
    BaseConstructL();
    
    // fixed toolbar is always visible ( defined in resource) hide it
    iFeatureManager.AppUi().CurrentFixedToolbar()->SetToolbarVisibility( EFalse );
    
    // create toolbar
    iToolbar = CAknToolbar::NewL( R_VIDEOTELUI_FLOATING_TOOLBAR );

    GfxTransEffect::Register( iToolbar, KNullUid, EFalse );
    
    // create and add items into the toolbar
    CreateToolbarButtonsL();

    iFeatureManager.UiStates().SetIsFloatingToolbarVisible( EFalse );
    
    // layout toolbar
    LayoutToolbarL();
    
    User::LeaveIfError(
        iFeatureManager.ComponentManager().ChangeResourceChangeRegistration(
        *this, MVtUiComponentManager::ERegister ) );
    
    __VTPRINTEXIT( "FloatingToolbar.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::~CVtUiFloatingToolbar
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiFloatingToolbar::~CVtUiFloatingToolbar()
    {
    __VTPRINTENTER( "FloatingToolbar.~" )
    // unregister resource change registration
    iFeatureManager.ComponentManager().ChangeResourceChangeRegistration(
        *this, MVtUiComponentManager::EUnregister );
    delete iToolbar;
    iToolbar = NULL;
    __VTPRINTEXIT( "FloatingToolbar.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::PopulateCmdsIdsL
// -----------------------------------------------------------------------------
//
void CVtUiFloatingToolbar::PopulateCmdsIdsL()
    {
    __VTPRINTENTER( "FloatingToolbar.PopulateCmdsIdsL" )
    CVtUiAppUi& appUi = iFeatureManager.AppUi();
    
    // Default commands populated in base clase
    CVtUiToolbarBase::PopulateCmdsIdsL();
    
    iCmdIds.AppendL( EVtUiCmdZoom );
    
    switch( iNumberOfToolbarButtons )
        {
        case KFourToolbarbuttons:
            iCmdIds.AppendL( EVtUiCmdUsePrimaryCamera );
            iCmdIds.AppendL( EVtUiCmdUseSecondaryCamera );
            break;

        case KFiveToolbarbuttons:
            iCmdIds.AppendL( EVtUiCmdUsePrimaryCamera );
            iCmdIds.AppendL( EVtUiCmdUseSecondaryCamera );
            iCmdIds.AppendL( EVtUiCmdSwapImagesPlaces );
            break;

        case KSixToolbarbuttons:
            iCmdIds.AppendL( EVtUiCmdUsePrimaryCamera );
            iCmdIds.AppendL( EVtUiCmdUseSecondaryCamera );
            iCmdIds.AppendL( EVtUiCmdSwapImagesPlaces );
            iCmdIds.AppendL( EVtUiCmdShareObjectImage );
            break;
        /*
        case KSevenToolbarbuttons:
            iCmdIds.AppendL( EVtUiCmdUsePrimaryCamera );
            iCmdIds.AppendL( EVtUiCmdUseSecondaryCamera );
            iCmdIds.AppendL( EVtUiCmdSwapImagesPlaces );
            iCmdIds.AppendL( EVtUiCmdShareObjectImage );
            iCmdIds.AppendL( EVtUiCmdSnapshot );
            break;
         */
        default:
            break;
        }

    __VTPRINTEXIT( "FloatingToolbar.PopulateCmdsIdsL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::CreateToolbarButtons
// -----------------------------------------------------------------------------
//
void CVtUiFloatingToolbar::CreateToolbarButtonsL()
    {
    __VTPRINTENTER( "FloatingToolbar.CreateToolbarButtons" )
    
    // Default buttons created in base clase
    CVtUiToolbarBase::CreateToolbarButtonsL(); 
    
    CVtUiAppUi& appUi = iFeatureManager.AppUi();

    // activate zoom mode
    CreateToolbarItemL( R_AVKONBUTTON_ACTIVATE_ZOOM_MODE_BUTTON,
        EVtUiCmdZoom, appUi );
    // disable tooltip from button's latched state
    // because tooltip needs to be shown only when
    // button gets focus not then when button is selected
    FindToolbarItemByCommandId( EVtUiCmdZoom )->State( 1 )
        ->SetHelpTextL( KNullDesC() );

    switch( iNumberOfToolbarButtons )
        {
        case KFourToolbarbuttons:
            // toggle camera
            CreateToolbarItemL( R_AVKONBUTTON_TOGGLE_CAMERA_BUTTON,
                EVtUiCmdToolbarToggleCamera, appUi );
            break;

        case KFiveToolbarbuttons:
             // toggle camera
             CreateToolbarItemL( R_AVKONBUTTON_TOGGLE_CAMERA_BUTTON,
                EVtUiCmdToolbarToggleCamera, appUi );

            // swap images
            CreateToolbarItemL( R_AVKONBUTTON_SWAP_IMAGES_BUTTON,
                EVtUiCmdSwapImagesPlaces, appUi );
            break;

        case KSixToolbarbuttons:
            // toggle camera
             CreateToolbarItemL( R_AVKONBUTTON_TOGGLE_CAMERA_BUTTON,
                EVtUiCmdToolbarToggleCamera, appUi );

            // swap images
            CreateToolbarItemL( R_AVKONBUTTON_SWAP_IMAGES_BUTTON,
                EVtUiCmdSwapImagesPlaces, appUi );

            // share file
            CreateToolbarItemL(R_AVKONBUTTON_SHARE_FILE_BUTTON,
                EVtUiCmdShareObjectImage, appUi );
            break;
        /*
        case KSevenToolbarbuttons:
            // toggle camera
             CreateToolbarItemL( R_AVKONBUTTON_TOGGLE_CAMERA_BUTTON,
                EVtUiCmdToolbarToggleCamera, appUi );

            // swap images
            CreateToolbarItemL( R_AVKONBUTTON_SWAP_IMAGES_BUTTON,
                EVtUiCmdSwapImagesPlaces, appUi );

            // share file
            CreateToolbarItemL(R_AVKONBUTTON_SHARE_FILE_BUTTON,
                EVtUiCmdShareObjectImage, appUi );

            CreateToolbarItemL( R_AVKONBUTTON_SNAPSHOT_BUTTON,
                EVtUiCmdSnapshot, appUi );

            break;
        */
        default:
            break;
        }

    __VTPRINTEXIT( "FloatingToolbar.CreateToolbarButtons" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::DoActivateL
// -----------------------------------------------------------------------------
//
void CVtUiFloatingToolbar::DoActivateL()
    {
    __VTPRINTENTER( "FloatingToolbar.DoActivateL" )
    // start blocking key events
    BlockKeyEvents( ETrue );
    // make toolbar visible
    if ( !iToolbar->IsVisible() ||
            !iFeatureManager.UiStates().IsFloatingToolbarVisible() )
        {
        // Show toolbar
        iToolbar->SetToolbarVisibility( ETrue );
        }
    else
        {
        // Undim toolbar
        DimToolbar( EFalse, EFalse );
        if ( iCmdFocus != KErrNotFound )
            {
            // Set focus item
            iToolbar->SetItemDimmed( iCmdFocus, EFalse, ETrue );
            iToolbar->SetFocusedItemL( iCmdFocus );
            iCmdFocus = KErrNotFound;
            }
        }
    iFeatureManager.UiStates().SetIsFloatingToolbarVisible( EFalse );
    CVtUiToolbarBase::DoActivateL();
    __VTPRINTEXIT( "FloatingToolbar.DoActivateL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::DoDeactivateL
// -----------------------------------------------------------------------------
//
void CVtUiFloatingToolbar::DoDeactivateL()
    {
    __VTPRINTENTER( "FloatingToolbar.DoDeactivateL" )
     // stop blocking key events
    BlockKeyEvents( EFalse );
    if ( iToolbar )
        {
        // Save foces item;
        if ( iToolbar->FocusedItem() != KErrNotFound )
            {
            iCmdFocus = iToolbar->FocusedItem();
            }
        TVtUiStates& uiStates = iFeatureManager.UiStates();
        if ( !uiStates.IsFloatingToolbarVisible() )
            {
            __VTPRINT( DEBUG_GEN, "FloatingToolbar.DoDeactivateL.Vs" )
            iToolbar->SetToolbarVisibility( EFalse );
            }
        else
            {
            // Dim toolbar
            __VTPRINT( DEBUG_GEN, "FloatingToolbar.DoDeactivateL.Dim ETrue" )
            DimToolbar( ETrue, EFalse );
            }
        CVtUiAppUi& appUi = iFeatureManager.AppUi();
        const TBool isZoomModeOn( uiStates.IsZoomModeOn() );
        if ( isZoomModeOn )
            {
            // set zoom indicator to be hidden
            appUi.SetZoomModeL( EFalse );
            }
        }
    CVtUiToolbarBase::DoDeactivateL();
    __VTPRINTEXIT( "FloatingToolbar.DoDeactivateL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::HandleResourceChangeL
// -----------------------------------------------------------------------------
//
void CVtUiFloatingToolbar::HandleResourceChangeL( TInt /*aType*/ )
    {
    __VTPRINTENTER( "FloatingToolbar.HandleResourceChangeL" )
    // akntoolbar should allways be in the control stack
    // no need to call
    // iToolbar->HandleResourceChange
    LayoutToolbarL();
    __VTPRINTEXIT( "FloatingToolbar.HandleResourceChangeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::RectFromLayout
// -----------------------------------------------------------------------------
//
TRect CVtUiFloatingToolbar::RectFromLayout(
   const TAknWindowComponentLayout& aComponentLayout ) const
   {
   __VTPRINTENTER( "FloatingToolbar.RectFromLayout" )
   TRect mainPaneRect;
   AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPaneRect );

   TAknWindowLineLayout lineLayout = aComponentLayout.LayoutLine();
   TAknLayoutRect layoutRect;
   layoutRect.LayoutRect( mainPaneRect, lineLayout );
   __VTPRINTEXIT( "FloatingToolbar.RectFromLayout" )
   return layoutRect.Rect();
   }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::LayoutToolbarL
// -----------------------------------------------------------------------------
//
void CVtUiFloatingToolbar::LayoutToolbarL()
    {
    __VTPRINTENTER( "FloatingToolbar.LayoutToolbarL" )

    // Get variety
    TInt variety = GetVariety( Layout_Meta_Data::IsLandscapeOrientation() );
    // get toolbar rect from layout
    TRect toolbarRect = RectFromLayout( AknLayoutScalable_Apps::
        popup_toolbar_window_cp04( variety ).LayoutLine() );
    //set top left coordinates i.e. placeholder
    iToolbar->SetPosition( toolbarRect.iTl );

    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        __VTPRINT( DEBUG_GEN, "Toolbar.LayoutToolbarL.LS" )
        iToolbar->SetOrientation( EAknOrientationVertical );
        }
    else
        {
        __VTPRINT( DEBUG_GEN, "Toolbar.LayoutToolbarL.PR" )
        iToolbar->SetOrientation( EAknOrientationHorizontal );
        }
    __VTPRINTEXIT( "FloatingToolbar.LayoutToolbarL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFloatingToolbar::GetVariety
// -----------------------------------------------------------------------------
//
TInt CVtUiFloatingToolbar::GetVariety( TBool aIsLandscapeOrientation )
    {
    __VTPRINTENTER( "FloatingToolbar.GetVariety" )
    TInt variety = 0;
    switch ( iNumberOfToolbarButtons )
        {
        case KThreeToolbarbuttons:
            if( aIsLandscapeOrientation )
                {
                variety = 5;
                }
            else
                {
                variety = 9;
                }
            break;

        case KFourToolbarbuttons:
            if( aIsLandscapeOrientation )
                {
                variety = 4;
                }
            else
                {
                variety = 8;
                }
            break;

        case KFiveToolbarbuttons:
            if( aIsLandscapeOrientation )
                {
                variety = 3;
                }
            else
                {
                variety = 7;
                }
            break;

        case KSixToolbarbuttons:
            if( aIsLandscapeOrientation )
                {
                variety = 2;
                }
            else
                {
                variety = 6;
                }
            break;

        case KSevenToolbarbuttons:
            if( aIsLandscapeOrientation )
                {
                variety = 1;
                }
            else
                {
                variety = 4;
                }
            break;

        default:

            break;
        }
    __VTPRINTEXITR( "FloatingToolbar.GetVariety =%d",variety )
    return variety;
    }
//  End of File


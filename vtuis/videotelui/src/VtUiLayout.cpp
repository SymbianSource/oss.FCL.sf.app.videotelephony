/*
* Copyright (c) 2004, 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the VtUiLayout class.
*
*/



// INCLUDE FILES
#include    "VtUiLayout.h"
#include    "VtUiPanic.h"
#include    <fbs.h>
#include    <avkon.mbg>
#include    <videotelui.mbg>
#include    <AknsConstants.h>
#include    <aknconsts.h>
#include    <AknIconUtils.h>
#include    <AknUtils.h>

#include    <aknlayout.cdl.h>
#include    <applayout.cdl.h>
#include    <aknlayoutscalable_apps.cdl.h>
#include    <aknlayoutscalable_avkon.cdl.h>
#include    <layoutmetadata.cdl.h>


// DATA TYPES

// Enumerates files in which there can be bitmaps.
enum TVtUiBitmapFiles
    {
    // Video Telephone bitmap file.
    EVtUiVideoBitmapFile,
    // AVKON bitmap file.
    EVtUiAvkonBitmapFile
    };

// Video Telephone application bitmaps
_LIT( KVtUiVideoBitmapFileName,
    "z:\\resource\\apps\\videotelui.mbm" );
// Minimum step for zoom.
const TInt KVtUiZoomMinStep = 1;

// Maximum step for zoom.
const TInt KVtUiZoomMaxStep = 11;

// ============================ LOCAL FUNCTIONS ===============================

inline TAknWindowComponentLayout DoCompose( TAknWindowComponentLayout aLine1,
    TAknWindowComponentLayout aLine2 )
    {
    return TAknWindowComponentLayout::Compose( aLine1, aLine2 );
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// VtUiLayout::GetApplicationParentRect
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetApplicationParentRect(
        TRect& aRect )
    {
    // Calculate screen rectangle.
    TSize screenSize = CCoeEnv::Static()->ScreenDevice()->SizeInPixels();
    TRect screenRect( screenSize );

    // Calculate application window.
    TAknLayoutRect appRect;
    appRect.LayoutRect(
        screenRect,
        AknLayout::application_window( screenRect ) );
    aRect = appRect.Rect();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetMainPaneLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetMainPaneLayout(
        TAknWindowLineLayout& aLayout )
    {
    TRect parent;
    GetApplicationParentRect( parent );
    // Calculate main pane layout.
    // First 1 = normal status pane, second 1 = control pane.
    aLayout = AknLayout::main_pane( parent, 0, 1, 1 );
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetFirstWindowBackgroundLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetFirstWindowBackgroundLayout(
        TAknWindowLineLayout& aLayout )
    {
    //aLayout = AppLayout::Uplink_video_image__large__Line_1();
    TInt main_pane_variety( 0 );
    TInt vid_upl_variety( 18 );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        main_pane_variety = 4;
        vid_upl_variety = 17;
        }

    TAknWindowComponentLayout layout1 =
        AknLayoutScalable_Apps::main_pane( main_pane_variety );
    TAknWindowComponentLayout layout2 =
        AknLayoutScalable_Apps::main_video_tele_pane();
    TAknWindowComponentLayout layout3 =
        AknLayoutScalable_Apps::
            call_video_uplink_pane_cp1( vid_upl_variety );
    TAknWindowComponentLayout layout4 =
        AknLayoutScalable_Apps::call_video_uplink_pane_g1();
    aLayout =
        DoCompose(
            DoCompose( layout1, layout2 ),
                DoCompose( layout3, layout4 ) ).LayoutLine();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetFirstWindowStreamLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetFirstWindowStreamLayout(
        TAknWindowLineLayout& aLayout )
    {
    TInt main_pane_variety( 0 );
    TInt vid_upl_variety( 18 );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        main_pane_variety = 4;
        vid_upl_variety = 17;
        }

    TAknWindowComponentLayout layout1 =
        AknLayoutScalable_Apps::main_pane( main_pane_variety );
    TAknWindowComponentLayout layout2 =
        AknLayoutScalable_Apps::main_video_tele_pane();
    TAknWindowComponentLayout layout3 =
        AknLayoutScalable_Apps::
            call_video_uplink_pane_cp1( vid_upl_variety );
    TAknWindowComponentLayout layout4 =
        AknLayoutScalable_Apps::video_uplink_pane();
    aLayout =
        DoCompose(
            DoCompose( layout1, layout2 ),
                DoCompose( layout3, layout4 ) ).LayoutLine();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetFirstWindowStreamDisabledIconLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetFirstWindowStreamDisabledIconLayout(
        TAknWindowLineLayout& aLayout )
    {
    //aLayout = AppLayout::Uplink_video_image__large__Line_3();
    TInt main_pane_variety( 0 );
    TInt vid_upl_variety( 18 );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        main_pane_variety = 4;
        vid_upl_variety = 17;
        }

    TAknWindowComponentLayout layout1 =
        AknLayoutScalable_Apps::main_pane( main_pane_variety );
    TAknWindowComponentLayout layout2 =
        AknLayoutScalable_Apps::main_video_tele_pane();
    TAknWindowComponentLayout layout3 =
        AknLayoutScalable_Apps::
            call_video_uplink_pane_cp1( vid_upl_variety );
    TAknWindowComponentLayout layout4 =
        AknLayoutScalable_Apps::call_video_uplink_pane_g2();
    aLayout =
        DoCompose(
            DoCompose( layout1, layout2 ),
                DoCompose( layout3, layout4 ) ).LayoutLine();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetSecondWindowBackgroundLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetSecondWindowBackgroundLayout(
        TAknWindowLineLayout& aLayout )
    {
    aLayout = AppLayout::Downlink_video_image_Line_1();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetSecondWindowStreamLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetSecondWindowStreamLayout(
    TAknWindowLineLayout& aLayout, TBool aIsToolbar, TBool aIsSubQCIF )
    {
    if( aIsSubQCIF )
        {
        aLayout = AppLayout::video_down_subqcif_pane();
        }
    else
        {
        if ( aIsToolbar )
            {
            TInt varietyPr = 27; // portrait
            TInt varietyLs = 26; // landscape

            TInt varietyIndex = Layout_Meta_Data::IsLandscapeOrientation()
	           ? varietyLs : varietyPr ;
            TAknWindowComponentLayout layout1 = AknLayoutScalable_Apps::
                main_video_tele_pane();
            TAknWindowComponentLayout layout2 = AknLayoutScalable_Apps::
                video_down_crop_pane( varietyIndex );
            aLayout = TAknWindowComponentLayout::Compose( layout1, layout2 ).
                LayoutLine();

            }
        else
            {
            aLayout = AppLayout::downlink_stream();
            }
        }
    }


// -----------------------------------------------------------------------------
// VtUiLayout::GetSecondWindowStreamWholeLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetSecondWindowStreamWholeLayout(
    TAknWindowLineLayout& aLayout, TBool aIsToolbar, TBool aIsSubQCIF )
    {
    if( aIsSubQCIF )
        {
        aLayout = AppLayout::video_down_subqcif_pane();
        }
    else
        {
        if ( aIsToolbar )
            {
            TInt varietyPr = 24; // portrait
            TInt varietyLs = 22; // landscape

            TInt varietyIndex = Layout_Meta_Data::IsLandscapeOrientation()
	           ? varietyLs : varietyPr;
            TAknWindowComponentLayout layout1 = AknLayoutScalable_Apps::
                main_video_tele_pane();
            TAknWindowComponentLayout layout2 = AknLayoutScalable_Apps::
                video_down_pane( varietyIndex );
            aLayout = TAknWindowComponentLayout::Compose( layout1, layout2 )
                .LayoutLine();
            }
        else
            {
            aLayout = AppLayout::downlink_stream_area();
            }
        }
    }
// -----------------------------------------------------------------------------
// VtUiLayout::GetSecondWindowDisabledIconLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetSecondWindowDisabledIconLayout(
        TAknWindowLineLayout& aLayout )
    {
    TInt blind_icon_variety( 4 );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        blind_icon_variety = 3;
        }

    TAknWindowComponentLayout layout2 =
        AknLayoutScalable_Apps::main_video_tele_pane();
    TAknWindowComponentLayout layout4 =
        AknLayoutScalable_Apps::
        call_video_g2( blind_icon_variety );
    
    aLayout =
        DoCompose( layout2 , layout4 ).LayoutLine();
    
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetSecondWindowWaitingTextLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetSecondWindowWaitingTextLayout(
        TAknTextLineLayout& aLayout,
        const TBool aFirstLine )
    {
    TBool layoutFound = EFalse;
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        layoutFound = ETrue;

        TAknWindowComponentLayout layout1 =
            AknLayoutScalable_Apps::main_video_tele_pane();

        TAknTextComponentLayout layout2 =
            aFirstLine ?
                AknLayoutScalable_Apps::call_video_pane_t1(2) :
                AknLayoutScalable_Apps::call_video_pane_t2(2);

        aLayout =
            TAknWindowComponentLayout::ComposeText(
                layout1, layout2 ).LayoutLine();
        }

    if ( !layoutFound )
        {
        const TInt line( ( aFirstLine ) ? 0 : 1 );
        TAknWindowComponentLayout l1 = AknLayoutScalable_Apps::
            main_video_tele_pane();
        TAknTextComponentLayout l2;
        if ( !line )
            {
            l2 = AknLayoutScalable_Apps::call_video_pane_t1( 3 );
            }
        else
            {
            l2 = AknLayoutScalable_Apps::call_video_pane_t2( 3 );
            }
        aLayout = TAknWindowComponentLayout::ComposeText( l1, l2 );
        }
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetNumberEntryAreaLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetNumberEntryAreaLayout(
        TAknWindowLineLayout& aLayout )
    {
    TInt variety = Layout_Meta_Data::IsLandscapeOrientation() ? 2 : 0;

    TAknWindowComponentLayout layout1 =
        AknLayoutScalable_Apps::main_call_pane();
    TAknWindowComponentLayout layout2 =
        AknLayoutScalable_Apps::popup_number_entry_window( variety );

    aLayout =
        TAknWindowComponentLayout::Compose( layout1, layout2 ).LayoutLine();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetAudioRoutingIconLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetAudioRoutingIconLayout(
        TAknWindowLineLayout& aLayout )
    {
    aLayout = AppLayout::Navipane_elements_and_descendant_panes_Line_1();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetCallDurationTextLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetCallDurationTextLayout(
        TAknTextLineLayout& aLayout )
    {
    aLayout = AppLayout::Navipanetexts_Line_1();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetMutedTextLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetMutedTextLayout(
        TAknTextLineLayout& aLayout )
    {
    aLayout = AppLayout::Navipanetexts_Line_2();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetZoomPaneLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetZoomPaneLayout(
        TAknWindowLineLayout& aLayout )
    {
    aLayout = AppLayout::zooming_pane();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetZoomDirLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetZoomDirLayout(
        TAknWindowLineLayout& aLayout )
    {
    aLayout = AppLayout::Zooming_pane_elements_Line_1();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetZoomAreaLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetZoomAreaLayout(
        TAknWindowLineLayout& aLayout )
    {
    aLayout = AppLayout::Zooming_pane_elements_Line_2();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetZoomStepLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetZoomStepLayout(
        TAknWindowLineLayout& aLayout,
        TInt aZoomStep )
    {
    aZoomStep = Max( Min( aZoomStep, KVtUiZoomMaxStep ), KVtUiZoomMinStep );
    aZoomStep--; // 1 .. 11 is mapped to 0 .. 10.

    // Function pointer table would be more efficient, but AppLayout methods
    // are inline.

    switch ( aZoomStep )
        {
        case 0:
            aLayout = AppLayout::Zooming_steps_sizes_Line_1();
            break;

        case 1:
            aLayout = AppLayout::Zooming_steps_sizes_Line_2();
            break;

        case 2:
            aLayout = AppLayout::Zooming_steps_sizes_Line_3();
            break;

        case 3:
            aLayout = AppLayout::Zooming_steps_sizes_Line_4();
            break;

        case 4:
            aLayout = AppLayout::Zooming_steps_sizes_Line_5();
            break;

        case 5:
            aLayout = AppLayout::Zooming_steps_sizes_Line_6();
            break;

        case 6:
            aLayout = AppLayout::Zooming_steps_sizes_Line_7();
            break;

        case 7:
            aLayout = AppLayout::Zooming_steps_sizes_Line_8();
            break;

        case 8:
            aLayout = AppLayout::Zooming_steps_sizes_Line_9();
            break;

        case 9:
            aLayout = AppLayout::Zooming_steps_sizes_Line_10();
            break;

        case 10:
        default:
            aLayout = AppLayout::Zooming_steps_sizes_Line_11();
            break;
        }
    }

// -----------------------------------------------------------------------------
// VtUiLayout::MapBitmapToSkinId
// -----------------------------------------------------------------------------
//
TAknsItemID VtUiLayout::MapBitmapToSkinId( TVtUiBitmapId aId )
    {
    TAknsItemID skinId = KAknsIIDNone;

    switch ( aId )
        {
        case EVtUiBitmap_qgn_graf_call_video_out_bg:
            skinId = KAknsIIDQgnGrafCallVideoOutBg;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_in:
            skinId = KAknsIIDQgnIndiCallVideoBlindIn;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_out:
            skinId = KAknsIIDQgnIndiCallVideoBlindOut;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_in_mask_icon:
            skinId = KAknsIIDQgnIndiCallVideoBlindInMaskIcon;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_out_mask_icon:
            skinId = KAknsIIDQgnIndiCallVideoBlindOutMaskIcon;
            break;

        case EVtUiBitmap_qgn_indi_earpiece:
            skinId = KAknsIIDQgnIndiEarpiece;
            break;

        case EVtUiBitmap_qgn_indi_speaker:
            skinId = KAknsIIDQgnIndiSpeaker;
            break;

        case EVtUiBitmap_qgn_indi_zoom_dir:
            skinId = KAknsIIDQgnIndiZoomDir;
            break;

        case EVtUiBitmap_qgn_graf_zoom_area:
            skinId = KAknsIIDQgnGrafZoomArea;
            break;

        case EVtUiBitmap_qgn_indi_zoom_min:
            skinId = KAknsIIDQgnIndiZoomMin;
            break;

        case EVtUiBitmap_qgn_indi_zoom_max:
            skinId = KAknsIIDQgnIndiZoomMax;
            break;

        case EVtUiBitmap_qgn_prop_sub_current:
        case EVtUiBitmap_qgn_prop_sub_current_mask:
            skinId = KAknsIIDQgnPropSubCurrent;
            break;
            
        case EVtUiBitmap_qgn_indi_button_end_active_call:
        case EVtUiBitmap_qgn_indi_button_end_active_call_mask:
            skinId = KAknsIIDQgnIndiButtonEndCall;
            break;

        default:
            // Default value is OK.
            break;
        }

    return skinId;
    }

// -----------------------------------------------------------------------------
// VtUiLayout::MapBitmapToColorId
// -----------------------------------------------------------------------------
//
TBool VtUiLayout::MapBitmapToColorId(
        TVtUiBitmapId aId,
        TAknsItemID& aColorId,
        TInt& aColorIndex )
    {
    TBool result = EFalse;

    aColorId = KAknsIIDNone;
    aColorIndex = KErrNotFound;

    switch ( aId )
        {
        case EVtUiBitmap_qgn_indi_earpiece:
        case EVtUiBitmap_qgn_indi_earpiece_mask:
        case EVtUiBitmap_qgn_indi_speaker:
        case EVtUiBitmap_qgn_indi_speaker_mask:
        case EVtUiBitmap_qgn_indi_zoom_dir:
        case EVtUiBitmap_qgn_indi_zoom_dir_mask:
            result = ETrue;
            aColorId = KAknsIIDQsnIconColors;
            aColorIndex = EAknsCIQsnIconColorsCG7;
            break;

        default:
            // Default value is OK.
            break;
        }

    return result;
    }

// -----------------------------------------------------------------------------
// VtUiLayout::Resolve
// -----------------------------------------------------------------------------
//
void VtUiLayout::Resolve(
        TVtUiBitmapId aId,
        TFileName& aFileName,
        TInt& aIndex )
    {
    TInt index = KErrNotFound;
    TVtUiBitmapFiles file = EVtUiVideoBitmapFile;

    switch ( aId )
        {
        case EVtUiBitmap_qgn_graf_call_video_out_bg:
            index = EMbmVideoteluiQgn_graf_call_video_out_bg;
            break;

        case EVtUiBitmap_qgn_graf_call_video_out_bg_mask:
            index = EMbmVideoteluiQgn_graf_call_video_out_bg_mask;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_in:
            index = EMbmVideoteluiQgn_indi_call_video_blind_in;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_out:
            index = EMbmVideoteluiQgn_indi_call_video_blind_out;
            break;

        case EVtUiBitmap_qgn_indi_earpiece:
            file = EVtUiAvkonBitmapFile;
            index = EMbmAvkonQgn_indi_earpiece;
            break;

        case EVtUiBitmap_qgn_indi_earpiece_mask:
            file = EVtUiAvkonBitmapFile;
            index = EMbmAvkonQgn_indi_earpiece_mask;
            break;

        case EVtUiBitmap_qgn_indi_speaker:
            file = EVtUiAvkonBitmapFile;
            index = EMbmAvkonQgn_indi_speaker;
            break;

        case EVtUiBitmap_qgn_indi_speaker_mask:
            file = EVtUiAvkonBitmapFile;
            index = EMbmAvkonQgn_indi_speaker_mask;
            break;

        case EVtUiBitmap_qgn_graf_zoom_area:
            index = EMbmVideoteluiQgn_graf_zoom_area;
            break;

        case EVtUiBitmap_qgn_indi_zoom_dir:
            index = EMbmVideoteluiQgn_indi_zoom_dir;
            break;

        case EVtUiBitmap_qgn_indi_zoom_dir_mask:
            index = EMbmVideoteluiQgn_indi_zoom_dir_mask;
            break;

        case EVtUiBitmap_qgn_indi_zoom_min:
            index = EMbmVideoteluiQgn_indi_zoom_min;
            break;

        case EVtUiBitmap_qgn_indi_zoom_max:
            index = EMbmVideoteluiQgn_indi_zoom_max;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_in_mask_icon:
            index = EMbmVideoteluiQgn_indi_call_video_blind_in_mask_icon;
            break;

        case EVtUiBitmap_qgn_indi_call_video_blind_out_mask_icon:
            index = EMbmVideoteluiQgn_indi_call_video_blind_out_mask_icon;
            break;

        case EVtUiBitmap_qgn_prop_sub_current:
            file = EVtUiAvkonBitmapFile;
            index = EMbmAvkonQgn_prop_sub_current;
            break;

        case EVtUiBitmap_qgn_prop_sub_current_mask:
            file = EVtUiAvkonBitmapFile;
            index = EMbmAvkonQgn_prop_sub_current_mask;
            break;
        case EVtUiBitmap_qgn_indi_button_end_active_call:
            index = EMbmVideoteluiQgn_indi_button_end_active_call;
            break;
            
        case EVtUiBitmap_qgn_indi_button_end_active_call_mask:
            index = EMbmVideoteluiQgn_indi_button_end_active_call_mask;
            break;

        default:
            VtUiPanic::Panic( EVtUiPanicInvalidBitmapId );
            break;
        }

    aIndex = index;
    switch ( file )
        {
        case EVtUiVideoBitmapFile:
            aFileName = KVtUiVideoBitmapFileName;
            break;

        case EVtUiAvkonBitmapFile:
            aFileName = AknIconUtils::AvkonIconFileName();
            break;

        default:
            VtUiPanic::Panic( EVtUiPanicInvalidBitmapFile );
            break;
        }
    }

// -----------------------------------------------------------------------------
// VtUiLayout::IsLandscapeOrientation
// -----------------------------------------------------------------------------
//
TBool VtUiLayout::IsLandscapeOrientation()
    {
    return Layout_Meta_Data::IsLandscapeOrientation();
    }

// -----------------------------------------------------------------------------
// VtUiLayout::GetButtonPaneLayout
// -----------------------------------------------------------------------------
//
void VtUiLayout::GetButtonPaneLayout( TAknWindowLineLayout& aLayout )
    {
//    TInt main_pane_variety = IsLandscapeOrientation() ? 1 : 2;
    TInt main_pane_variety( 0 );
    TInt vid_btn_variety( 2 );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        main_pane_variety = 4;
        vid_btn_variety = 1;
        }
    
    
    TAknWindowComponentLayout layout1 = AknLayoutScalable_Apps::main_pane( main_pane_variety );
    
    TAknWindowComponentLayout layout2 = AknLayoutScalable_Apps::vidtel_button_pane( vid_btn_variety );
    
    aLayout = DoCompose( layout1, layout2 ).LayoutLine();
    }
//  End of File

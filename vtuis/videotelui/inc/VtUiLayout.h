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
* Description:  Layout related accessory methods for Video Telephone
*                application.
*
*/



#ifndef VTUILAYOUT_H
#define VTUILAYOUT_H

//  INCLUDES
#include    "videotelui.hrh"
#include    <e32base.h>
#include    <aknutils.h>

// FORWARD DECLARATIONS
class TAknsItemID;

// CLASS DECLARATION

/**
*  Layout related accessory methods for Video Telephone application.
*
*  @since Series 60 2.6
*/
class VtUiLayout
    {
    public: // New functions

        /**
        * Returns application window rectangle.
        * @param aRect rectangle to be filled.
        */
        static void GetApplicationParentRect(
            TRect& aRect );

        // ELEMENTS RELATIVE TO APPLICATION WINDOW:

        /**
        * Returns main pane layout.
        * @param aLayout main pane layout.
        */
        static void GetMainPaneLayout(
            TAknWindowLineLayout& aLayout );

        // ELEMENTS RELATIVE TO APPLICATION WINDOW:

        /**
        * Returns layout for uplink video stream background.
        * @param aLayout layout of qgn_graf_call_video_out_bg.
        */
        static void GetFirstWindowBackgroundLayout(
            TAknWindowLineLayout& aLayout );

        /**
        * Returns layout for uplink video stream.
        * @param aLayout layout of uplink video stream relative.
        */
        static void GetFirstWindowStreamLayout(
            TAknWindowLineLayout& aLayout );

        /**
        * Returns layout of uplink video disabled icon.
        * @param aLayout layout of qgn_indi_call_video_blind_out.
        */
        static void GetFirstWindowStreamDisabledIconLayout(
            TAknWindowLineLayout& aLayout );

        // ELEMENTS RELATIVE TO MAIN PANE:

        /**
        * Returns layout of background rectangle.
        * @param aLayout layout of background rectangle.
        */
        static void GetSecondWindowBackgroundLayout(
            TAknWindowLineLayout& aLayout );

        /**
        * Returns layout of downlink video stream.
        * @param aLayout layout of downlink video stream.
        * @param aUseSQCif ETrue if SQCIF layout is to be used.
        */
        static void GetSecondWindowStreamLayout(
            TAknWindowLineLayout& aLayout,
            TBool aIsToolbar,
            TBool aIsSubQCIF = EFalse );

        /**
        * Returns layout of downlink video stream (the whole picture).
        * @param aLayout layout of downlink video stream.
        * @param aUseSQCif ETrue if SQCIF layout is to be used.
        */
        static void GetSecondWindowStreamWholeLayout(
            TAknWindowLineLayout& aLayout,
            TBool aIsToolbaraIsToolbar,
            TBool aIsSubQCIF = EFalse );

        /**
        * Returns layout of downlink video disabled icon.
        * @param aLayout layout of qgn_indi_call_video_blind_in.
        */
        static void GetSecondWindowDisabledIconLayout(
            TAknWindowLineLayout& aLayout );

        /**
        * Returns layout of waiting text.
        * @param aLayout layout.
        * @param aFirstLine ETrue if first line, EFalse if second.
        */
        static void GetSecondWindowWaitingTextLayout(
            TAknTextLineLayout& aLayout,
            const TBool aFirstLine );

        /**
        * Returns number entry area layout.
        * @param aLayout layout.
        */
        static void GetNumberEntryAreaLayout(
            TAknWindowLineLayout& aLayout );

        // ELEMENTS RELATIVE TO NAVI PANE:

        /**
        * Returns layout of audio routing indicator.
        * @param aLayoutlayout of qgn_indi_<ref>_[muted].
        */
        static void GetAudioRoutingIconLayout(
            TAknWindowLineLayout& aLayout );

        /**
        * Returns layout of call duration text.
        * @param aLayout layout of call duration text.
        */
        static void GetCallDurationTextLayout(
            TAknTextLineLayout& aLayout );

        /**
        * Returns layout of muted text.
        * @param aLayout layout of muted text.
        */
        static void GetMutedTextLayout(
            TAknTextLineLayout& aLayout );

        /**
        * Gets zooming pane layout.
        * @param aLayout layout of zooming pane.
        */
        static void GetZoomPaneLayout(
            TAknWindowLineLayout& aLayout );

        // ELEMENTS RELATIVE TO ZOOMING PANE:

        /**
        * Gets zoom direction icon layout.
        * @param aLayout layout of zoom direction icon.
        */
        static void GetZoomDirLayout(
            TAknWindowLineLayout& aLayout );

        /**
        * Gets zoom area layout.
        * @param aLayout layout of zoom area.
        */
        static void GetZoomAreaLayout(
            TAknWindowLineLayout& aLayout );

        /**
        * Gets zoom step layout.
        * @param aLayout layout of a zoom step.
        * @param aZoomStep zoom step, 1 .. 11.
        */
        static void GetZoomStepLayout(
            TAknWindowLineLayout& aLayout,
            TInt aZoomStep );

        // OTHER UTILITY METHODS

        /**
        * Returns skin identifier corresponding to the bitmap.
        *
        * @param aId identifier of the bitmap.
        * @return skin identifier or KAknsIIDNone if no skin for this bitmap.
        */
        static TAknsItemID MapBitmapToSkinId( TVtUiBitmapId aId );

        /**
        * Determines color skin identifier corresponding to the bitmap.
        *
        * @param aId bitmap identifier.
        * @param aColorId it will contain color skin id.
        * @param aColorIndex it will contain color index.
        * @return ETrue if bitmap has color skin, EFalse otherwise.
        */
        static TBool MapBitmapToColorId(
            TVtUiBitmapId aId,
            TAknsItemID& aColorId,
            TInt& aColorIndex );

        /**
        * Resolves file name and index from bitmap identifier.
        * @param aId bitmap identifier.
        * @param aFileName it will contain the name of the file.
        * @param aIndex it will contain the index.
        */
        static void Resolve(
            TVtUiBitmapId aId,
            TFileName& aFileName,
            TInt& aIndex );

        /**
        * Can be used for checking current orientation.
        * @return ETrue if current application orientation is landscape,
        * EFalse otherwise.
        */
        static TBool IsLandscapeOrientation();

    };

#endif      // VTUILAYOUT_H

// End of File

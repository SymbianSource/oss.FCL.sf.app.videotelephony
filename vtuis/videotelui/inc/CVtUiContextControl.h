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
* Description:  Context pane control for Video Telephone application.
*
*/



#ifndef CVTUICONTEXTCONTROL_H
#define CVTUICONTEXTCONTROL_H

//  INCLUDES
#include    <AknWsEventObserver.h>
#include    "cvtuivideocontrolbase.h"

// FORWARDS
class CVtUiAppUi;
class TVtUiStates;

/**
*  Context pane control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiContextControl : public CVtUiVideoControlBase,
    public MAknWsEventObserver
    {

    public: // Constructors and destructor

        /**
        * C++ constructor.
        * @param aBitmapManager bitmap manager.
        * @param aLargeViewfinder ETrue if large viewfinder wanted.
        * @param aAppUi application UI.
        * @param aUiStates UI states.
        */
        static CVtUiContextControl* NewL(
            CVtUiBitmapManager& aBitmapManager,
            CVtUiAppUi& aAppUi,
            TVtUiStates& aUiStates );

        /**
        * C++ destructor.
        */
        ~CVtUiContextControl();

        /**
        * LayoutRemoteVideo
        */
       void LayoutRemoteVideo();
       
    public: // from CCoeControl

        /**
        * @see CCoeControl::HandlePointerEventL
        */
        void HandlePointerEventL( const TPointerEvent& aPointerEvent );

    private: // from CVtUiVideoControlBase

        /**
        * @see CVtUiVideoControlBase::HandleSizeChanged
        */
        void HandleSizeChanged();

        /**
        * @see CVtUiVideoControlBase::DrawColoredBackground
        */
        void DrawColoredBackground( CWindowGc& aGc ) const;

        /**
        * @see CVtUiVideoControlBase::StreamBlitPosition
        */
        TPoint StreamBlitPosition() const;

        /**
        * @see CVtUiVideoControlBase::StreamBlitPosition
        */
        TRect StreamClippingRect() const;

        /**
        * @see CVtUiVideoControlBase::BlindImage
        */
        CFbsBitmap* BlindImage() const;

        /**
        * @see CVtUiVideoControlBase::BlindMask
        */
        CFbsBitmap* BlindMask() const;

        /**
        * @see CVtUiVideoControlBase::BlindBlitPosition
        */
        TPoint BlindBlitPosition() const;

    public: // from MAknWsEventObserver

        /**
        * @see MAknWsEventObserver::HandleWsEventL
        */
        void HandleWsEventL( const TWsEvent& aEvent,
            CCoeControl* aDestination );

    private:

        /**
        * C++ constructor.
        */
        CVtUiContextControl(
            CVtUiBitmapManager& aBitmapManager,
            CVtUiAppUi& aAppUi,
            TVtUiStates& aUiStates );

        /**
        * Symbian constructor.
        */
        void ConstructL();

    private:

        // Background icon identifier.
        TVtUiBitmapPoolId iBackgroundId;

        // Blind icon identifier.
        TVtUiBitmapPoolId iBlindId;

        // Blind icon mask identifier.
        TVtUiBitmapPoolId iBlindMaskId;

        // Reference to application UI.
        CVtUiAppUi& iAppUi;

        // Reference to UI states.
        TVtUiStates& iUiStates;

        // Background bitmap layout.
        TAknLayoutRect iBackGround;

        // Blind icon rect
        TRect iBlindRect;

        // Stream rect
        TRect iStreamRect;

        // ETrue if it is ok to swap images on button up
        TBool iOkToSwapOnButtonUp;

        // ETrue if the pointer down inside of context control window
        TBool iPointerButton1DownInside;

    };

#endif      // CVTUICONTEXTCONTROL_H

// End of File

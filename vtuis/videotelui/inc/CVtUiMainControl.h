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
* Description:  Main pane control for Video Telephone application.
*
*/



#ifndef CVTUIMAINCONTROL_H
#define CVTUIMAINCONTROL_H

//  INCLUDES
#include    "cvtuivideocontrolbase.h"

// CLASS DECLARATION
class CVtUiAppUi;
class TVtUiStates;
class TAknTextLineLayout;

/**
*  Main pane control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiMainControl : public CVtUiVideoControlBase
    {

    public: // Constructors and destructor

        /**
        * Constructor.
        * @param aBitmapManager bitmap manager.
        * @param aUiStates Ui states class.
        */
        static CVtUiMainControl* NewL( CVtUiBitmapManager& aBitmapManager,
                CVtUiAppUi& aAppUi,
                TVtUiStates& aUiStates );

        /**
        * C++ destructor.
        */
        ~CVtUiMainControl();

    public: // New functions.

        /**
        * Sets SQCif mode on/off.
        * @param aIsSupported whether on/off
        */
        void SupportSQCif( TBool aIsSupported );

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
        * @see CVtUiContextControl::HandleSizeChanged
        */
        void HandleSizeChanged();

        /**
        * @see CVtUiContextControl::DrawWaitingText
        */
        TBool DrawWaitingText( CWindowGc& aGc ) const;

        /**
        * @see CVtUiContextControl::StreamBlitPosition
        */
        TPoint StreamBlitPosition() const;

        /**
        * @see CVtUiContextControl::StreamClippingRect
        */
        TRect StreamClippingRect() const;

        /**
        * @see CVtUiContextControl::BlindImage
        */
        CFbsBitmap* BlindImage() const;

        /**
        * @see CVtUiContextControl::BlindMask
        */
        CFbsBitmap* BlindMask() const;

        /**
        * @see CVtUiContextControl::BlindBlitPosition
        */
        TPoint BlindBlitPosition() const;

        /**
        * @see CVtUiContextControl::WaitingTextLayout
        */
        TAknTextLineLayout WaitingTextLayout( TInt aLine );

    private:

        /**
        * Private constructor.
        */
        CVtUiMainControl( CVtUiBitmapManager& aBitmapManager,
                CVtUiAppUi& aAppUi,
                TVtUiStates& aUiStates );

        /**
        * C++ constructor.
        * @param aBitmapManager bitmap manager.
        */
        CVtUiMainControl();

        /**
        * Symbian constructor.
        */
        void ConstructL();

    private:

        // Background layout.
        TAknLayoutRect iBackgroundLayout;

        // Blind icon identifier.
        TVtUiBitmapPoolId iBlindId;

        // Blind icon mask identifier.
        TVtUiBitmapPoolId iBlindMaskId;

        // Blind icon layout.
        TAknLayoutRect iBlindLayout;

        // Stream layout.
        TAknLayoutRect iStreamLayoutRect;

        // ETrue if sqcif is used in remote video.
        TBool iSQCifRemote;

        // Reference to application UI.
        CVtUiAppUi& iAppUi;

        // reference to uistates
        TVtUiStates& iUiStates;

    };

#endif      // CVTUIMAINCONTROL_H

// End of File

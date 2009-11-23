/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Interface for controlling a video window
*                for Video Telephone application.
*
*/



#ifndef MVTUIVIDEOWINDOW_H
#define MVTUIVIDEOWINDOW_H

//  INCLUDES
#include    <e32base.h>

// FORWARD DECLARATIONS
class CFbsBitmap;

// CLASS DECLARATION

/**
*  Interface for controlling a video window (uplink / downlink) for Video
*  Telephone application.
*
*  @since Series 60 2.6
*/
class MVtUiVideoWindow
    {
    public: // New functions

        /**
        * Resets blind, stream bitmap and waiting image statuses.
        */
        virtual void Reset() = 0;

        /**
        * Changes blind status.
        * @param aStatus new status, ETrue - on, EFalse - off.
        */
        virtual void SetBlind( TBool aStatus ) = 0;

        /**
        * Sets stream bitmap.
        * @param aStreamBitmap bitmap. Ownership not transferred.
        */
        virtual void SetStreamBitmap( CFbsBitmap* aStreamBitmap ) = 0;

        /**
        * Sets stream bitmap for reserve, when Draw() routine is called.
        * (e.g. when opening and closing menu)
        * @param aStreamBitmap bitmap. Ownership not transferred.
        */
        virtual void SetStreamBitmapReserve( CFbsBitmap* aStreamBitmap ) = 0;

        /**
        * Sets waiting image status.
        * @param aShowWaitingText ETrue if waiting text should be shown.
        */
        virtual void SetWaiting( TBool aShowWaitingText ) = 0;

        /**
        * Redraws image.
        */
        virtual void Redraw() = 0;
        
        /**
         * Set remote video control 
         */
        virtual void SetRemoteVideoControl( CCoeControl* aRemoteControl ) = 0;
        
        /**
         * Layout the postion and the size of the remote video control
          */
        virtual void LayoutRemoteVideo() = 0;    
        
        /**
         * Returns pointer to remote video control  or NULL if no remote video control  is present.
         */
        virtual CCoeControl * RemoteVideoControl() = 0;
                       
    };

#endif      // CVTUICONTEXTCONTROL_H

// End of File

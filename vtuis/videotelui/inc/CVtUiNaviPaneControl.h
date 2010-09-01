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
* Description:  Navi pane control for Video Telephone application.
*
*/



#ifndef CVTUINAVIPANECONTROL_H
#define CVTUINAVIPANECONTROL_H

//  INCLUDES
#include    <coecntrl.h>
#include    <AknUtils.h>

// CONSTANTS

// Maximum length of call duration buffer.
const TInt KVtUiCallDurationBufferLength = 16;

// FORWARD DECLARATIONS
class CVtUiNaviPane;

// CLASS DECLARATION

/**
*  Navi pane control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiNaviPaneControl
    : public CCoeControl
    {
    public: // Constructors and destructor

        /**
        * C++ constructor.
        * @param aNaviPane eference to navipane.
        */
        CVtUiNaviPaneControl( CVtUiNaviPane& aNaviPane ); 

        /**
        * Symbian constructor.
        */
        void ConstructL();

        /**
        * C++ destructor.
        */
        ~CVtUiNaviPaneControl();

    public: // New functions

        /**
        * Sets call duration.
        * @param aDuration call duration.
        * @param aEnabled ETrue if enabled.
        */
        void SetCallDuration( 
            const TTimeIntervalSeconds& aDuration,
            const TBool aEnabled );

        /**
        * Updates screen to reflect changes.
        */
        void CommitL();

    protected: // Functions from base classes

        /**
        * From CCoeControl, draws the control.
        * @param aRect area to be drawn.
        */
        virtual void Draw( const TRect& aRect ) const;

        /**
        * From CCoeControl, handles size changes.
        */
        virtual void SizeChanged();

        /**
        * From CCoeControl, handles position changes.
        */
        virtual void PositionChanged();

    private:

        /**
        * Gets call duration text.
        * @return reference to text.
        */
        const TDesC& GetCallDurationText() const;

        /**
        * Appends character to the buffer.
        * @param aBuffer buffer.
        * @param aChar character.
        */
        static void AppendChar( 
            TDes& aBuffer,
            const TChar& aChar );

        /**
        * Appends a number to the buffer.
        * @param aBuffer buffer.
        * @param aNumber number, 0 .. 99.
        */
        static void AppendNum(
            TDes& aBuffer,
            const TInt aNumber );

    private:

        // Call duration layout.
        TAknLayoutText iCallDurationLayout;

        // ETrue if call duration is enabled.
        TBool iCallDurationEnabled;

        // Duration in seconds.
        TTimeIntervalSeconds iCallDuration;

        // Buffer for call duration.
        mutable TBuf< KVtUiCallDurationBufferLength > iCallDurationBuffer;

        // Current speaker, ETrue if loudspeaker, EFalse if handset.
        TBool iLoudspeaker;
        
        // Reference to navipane.
        CVtUiNaviPane& iNaviPane;

    };

#endif      // CVTUINAVIPANECONTROL_H
            
// End of File

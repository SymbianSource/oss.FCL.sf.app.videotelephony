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
* Description:  Blank control for Video Telephone application.
*
*/



#ifndef CVTUIBLANKCONTROL_H
#define CVTUIBLANKCONTROL_H

//  INCLUDES
#include    <coecntrl.h>

// CLASS DECLARATION

/**
*  Blank control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiBlankControl
    : public CCoeControl
    {
    public: // Constructors and destructor
        
        /**
        * C++ constructor.
        */
        CVtUiBlankControl();

        /**
        * Symbian constructor.
        * @param aRect control rectangle.
        */
        void ConstructL( const TRect& aRect );

        /**
        * C++ destructor.
        */
        ~CVtUiBlankControl();

    public: // New functions

        /**
        * Sets blanker active / inactive.
        * @param aStatus ETrue if to be activated.
        */
        void SetActive( TBool aStatus );

    protected: // Functions from base classes

        /**
        * From CCoeControl, handles key events.
        * @param aKeyEvent key event.
        * @param aType type of event.
        */
        virtual TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

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

        // ETrue if blanker is active.
        TBool iBlankerActive;

    };

#endif      // CVTUIBLANKCONTROL_H
            
// End of File

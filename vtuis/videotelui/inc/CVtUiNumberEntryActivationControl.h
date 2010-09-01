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
* Description:  Number entry activation control for 
*                Video Telephone application.
*
*/



#ifndef CVTUINUMBERENTRYACTIVATIONCONTROL_H
#define CVTUINUMBERENTRYACTIVATIONCONTROL_H

//  INCLUDES
#include    <coecntrl.h>

// FORWARD DECLARATIONS
class CVtUiAppUi;

// CLASS DECLARATION

/**
*  Number entry activation control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiNumberEntryActivationControl
    : public CCoeControl
    {
    public: // Constructors and destructor
        
        /**
        * C++ constructor.
        * @param aAppUi application ui.
        */
        CVtUiNumberEntryActivationControl( CVtUiAppUi& aAppUi );

        /**
        * Symbian constructor.
        * @param aRect initial area.
        */
        void ConstructL( const TRect& aRect );

        /**
        * C++ destructor.
        */
        ~CVtUiNumberEntryActivationControl();

    public: // Functions from base classes
        
        /**
        * @see CCoeControl::SizeChanged.
        */
        virtual void SizeChanged();

        /**
        * @see CCoeControl::PositionChanged.
        */
        virtual void PositionChanged();

        /**
        * @see CCoeControl::Draw.
        */
        virtual void Draw( const TRect& aRect ) const;
    
        /**
        * @see CCoeControl::OfferKeyEventL.
        */
        virtual TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
            TEventCode aType );

    public: // New functions
        
        /**
        * Set control's activation status.
        * @param aIsActive ETrue if key events should 
        * be handled oterherwise EFalse.
        */
        void SetActive( TBool aIsActive );
  
    private:

        /**
        * Checks if event should open number entry.
        * @param aKeyEvent event.
        * @param aDtmfTone event as character tone.
        * @return ETrue if number entry should be opened.
        */
        static TBool IsNumericEvent( 
            const TKeyEvent& aKeyEvent,
            TChar& aDtmfTone );

    private:

        // Reference to application ui.
        CVtUiAppUi& iAppUi;

        // ETrue if this control has been added to stack.
        TBool iAddedToStack;
        
        // ETrue if key events should be handled oterherwise EFalse.
        TBool iIsActive;

    };

#endif      // CVTUINUMBERENTRYACTIVATIONCONTROL_H
            
// End of File

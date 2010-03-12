/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  End call button pane definition.
*
*/


#ifndef C_VTUIENDCALLBUTTONPANE_H
#define C_VTUIENDCALLBUTTONPANE_H

// INCLUDES

// CLASS DECLARATION
class CVtUiEndCallButton;

/**
 *  CCVtUiEndCallButtonPane 
 */
class CVtUiEndCallButtonPane : public CCoeControl,
                               public MCoeControlObserver
    {
    public: // Constructors and destructor
        
        /**
         * Static construction method.
         * @param aRect The intialized rectangle of container window 
         * @return Pointer to newly created instance of CVtUiEndCallButtonPane.
         */
        static CVtUiEndCallButtonPane* NewL( const TRect& aRect );
    
        /**
        * C++ destructor.
        */
        ~CVtUiEndCallButtonPane();
  
    public: //from base class CCoeControl
    
        /**
         * From CCoeControl. 
         * Gets the number of controls contained in a compound control.
         * @return The number of controls in the container
         */
        TInt CountComponentControls() const;
    
        /**
         * From CCoeControl. 
         * Gets an indexed component of a compound control.
         */
        CCoeControl* ComponentControl( TInt aIndex ) const;
    
        /**
         * From CCoeControl. 
         * Draws the control.
         */
        void Draw(const TRect& aRect) const;
    
        /**
         * From CCoeControl. 
         * Responds to changes to the size and position of the 
         * contents of this control.
         */
        void SizeChanged();
    
        /**
         * From CCoeControl. 
         * Retrieves an object of the same type as that encapsulated in aId.
         */
        TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
        
    public: //From MCoeControlObserver
    
        /**
         * Handles an event from an observed control.
         */
        void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );
    
    private:
    
        /**
         * C++ constructor for the end call button container.
         */
        CVtUiEndCallButtonPane();
    
        /**
         * Symbian 2nd phase constructor.
         * 
         * @param aRect The intialized rectangle of container window
         */
        void ConstructL( const TRect& aRect );
    
    private: // New functions
        /**
         * Creating button from resource.
         */
        void CreateButtonUsingResourceL();
    
        /**
         * Getting the button layout data for the text and icon.
         */
        void GetButtonLayoutData();

    private:
    
        /**
         * Owned: End button
         */
        CVtUiEndCallButton* iEndButton;
        
        /**
         * Owned: background context.
         */ 
        CAknsBasicBackgroundControlContext* iBgContext;
    };

#endif // C_VTUIENDCALLBUTTONCONTAINER_H

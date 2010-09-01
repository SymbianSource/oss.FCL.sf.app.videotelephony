/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CVtUiToolbarButton class definition.
*
*/


#ifndef C_VTUITOOLBARBUTTON_H
#define C_VTUITOOLBARBUTTON_H

#include <aknbutton.h> 

class CVtUiAppUi;

/**
*  CVtUiToolbarButton
*
*  Toolbar button class definition.
*
*  @since S60 3.2
*/
class CVtUiToolbarButton : public CAknButton
    {
    public:
    
        /**
        * Static constructor.
        * @param aResourceId Resource id.
        * @param aAppUi Reference to appui.
        * @param aCmdId Reference to command id.
        */
    	static CVtUiToolbarButton* NewL( TInt aResourceId, 
		    CVtUiAppUi& aAppUi, TInt aCmdId );
		
		 /**
        * Static constructor.
        * @param aResourceId Resource id.
        * @param aAppUi Reference to appui.
        * @param aCmdId Reference to command id.
        */
    	static CVtUiToolbarButton* NewLC( TInt aResourceId, 
		    CVtUiAppUi& aAppUi, TInt aCmdId );
		
        /**
        * C++ destructor.
        */
		~CVtUiToolbarButton();
		
        /*  
        * Shows help text for a certain period of time.              	
        */
        void ShowHelpL(); 
          
        /*  
        * Return commmand id
        */           
        TInt CmdId() const;   
        
        /*
        * Starts or stops to block pointer events
        * @param aIsBlocking ETrue if events are blocked
        * otherwise EFalse
        */
        void BlockPointerEvents( TBool aIsBlocking );
           
        /*
        * Starts or stops to block key events
        * @param aIsBlocking ETrue if events are blocked
        * otherwise EFalse
        */
        void BlockKeyEvents( TBool aIsBlocking );      
        
        
        /* @see CAknButton::OfferKeyEventL */
        TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
            TEventCode aType );
        
        /* @see CAknButton::HandlePointerEventL */
        void HandlePointerEventL( const TPointerEvent&
            aPointerEvent );                                  	

        /* @see CAknButton::StatesCount */
        TInt StatesCount() const;

    private:
    
        /**
        * Constructor
        */
        CVtUiToolbarButton( CVtUiAppUi& aAppUi, TInt aCmdId );
        	 
    private:
        
        /**
        * Checks whether key events should be blocked.
        */
        TBool IsCommandActive() const;  
        
    private: 
         
         // reference to appui
         CVtUiAppUi& iAppUi;
         
         // command id
         TInt iCmdId;
         
         // Flag to indicate is key event  blocking on
         TBool iIsBlockingKeyEvents;
         
         // Flag to indicate is pointer event blocking on
         TBool iIsBlockingPointerEvents;
         
         // time stamp to limit pointerevents
         TTime iTimeStamp;
         
         TBool isLimitingPointers;
         
    };

#endif // C_VTUITOOLBARBUTTON_H

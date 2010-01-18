/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  CVtUiTransparentSettingPage API definition.
*
*/


#ifndef CVTUITRANSPARENTSETTINGPAGE_H
#define CVTUITRANSPARENTSETTINGPAGE_H

#include <AknTransparentCameraSettingPage.h>

class MVtUiSettingPageObserver;
class CAknsBasicBackgroundControlContext;

/**
*  CVtUiTransparentSettingPage
*
*  CVtUiTransparentSettingPage API definition.
*
*  @since S60 v3.2
*/   
class CVtUiTransparentSettingPage : public CAknTransparentCameraSettingPage
{
public: // public methods
    /**
    * handle layoutChange
     */
    void HandleLayoutChangeL();

    /**
    * Constructor.
    * @param aResourceID Setting Page to use.
    * @param aCurrentSelectionIndex The currently selected index.
    * @param aItemArray List of option texts and their selection states.
    * @param aAppUi Reference to AppUi.
    * @return Newly created instance of CVtUiTransparentSettingPage class.
    */
    CVtUiTransparentSettingPage(
        TInt aResourceID, 
        TInt& aCurrentSelectionIndex, 
        const MDesCArray* aItemArray );
     
    /**
    * 2nd constructor
    */   
    void ConstructL();
        
    /**
    * Destructor
    */        
    ~CVtUiTransparentSettingPage();

    /**
    * Adds setting page observer.
    * @param aObserver Observer for setting page.
    */
    void SetSettingPageEventStateObserver(
        MVtUiSettingPageObserver* aObserver );

private: // from aknsettinpage

     /**
     * @see CAknSettinPage::DynamicInitL
     */
     void  DynamicInitL();
     
     /**
     * @get the layout data in portrait or landscape mode
     */
		 void		GetTheLayoutData();
		 
     /**
     * @see CAknSettinPage::HandleControlEventL
     */
     void HandleControlEventL( CCoeControl* aControl,TCoeEvent aEventType );
     
private: // new functions
        
        /*
        * Gets rect from layout data.
        */
        TRect RectFromLayout( const TAknWindowComponentLayout&
            aComponentLayout ) const;
                 
private:
    
    // Setting page observer
    MVtUiSettingPageObserver* iSettingPageObserver;
}; 

#endif // CVTUITRANSPARENTSETTINGPAGE_H

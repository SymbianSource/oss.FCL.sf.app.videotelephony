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
* Description:  Base class for video preference popups
*
*/


#ifndef     C_VTUIPREFPOPUPBASE_H
#define     C_VTUIPREFPOPUPBASE_H


#include    "cvtuipopupbase.h"

class MVtEngCameraPreferences;
class CVtUiFeatureManager;
/*
*  CVtUiPrefPopupBase
*
*  Base class for video preference popups
*
*  @since S60 v3.2
*/
class CVtUiPrefPopupBase : public CVtUiPopupBase
    {
    
public:

    /**
    * Destructor
    */
    ~CVtUiPrefPopupBase();


public: // from CVtUiPopupBase

    /**
    * @see CVtUiPopupBase::HandleControlEventL
    */
    void HandleControlEventL( 
        CCoeControl* aControl,TCoeEvent aEventType );
    
    /**
    * @see CVtUiPopupBase::UpdatePopupL
    */    
    void UpdatePopupL();
    
private: // from base class
    
    /**
    * @see CVtUiPopupBase::OfferKeyEventL
    */  
    TKeyResponse OfferKeyEventL( const TKeyEvent& aEvent, 
            TEventCode aCode );

protected: // new functions
    
    // Does the actual viewfinder adjusting
    void AdjustVideoL( TInt aValue );
    
    // from base class CVtUiPopupBase::DoActivateL()
    void DoActivateL();
    
    // Gets current adjustvalue
    virtual TInt CurrentValue() = 0;
    
protected:

    /**
    * Constructor
    */
    CVtUiPrefPopupBase( CVtUiFeatureManager& aFeatureManager,
        TVtUiBlockListBitField aBitField, TComponentId aComponentId,
         TInt aCmdId );

     /**
     * 2nd constructor
     */
    void BaseConstructL();

protected:    
    
    // Pointer to camera preferences
    MVtEngCameraPreferences* iCameraPref;
    
    // Reference to feature manager
    CVtUiFeatureManager& iFeatureManager;
    
    // Engine command id
    TInt iEngineCommandId;
    
    // Current value
    TInt iCurrent;
    };

#endif // C_VTUIPREFPOPUPBASE_H

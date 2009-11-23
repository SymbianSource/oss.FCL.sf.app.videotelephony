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
* Description:  White balance feature.
*
*/


#ifndef C_VTUIWHITEBALANCE_H
#define C_VTUIWHITEBALANCE_H

#include    <mvtengcamerapreferences.h>
#include    "cvtuiprefsettinglistbase.h"
#include    "tvtuicomponentstate.h"
#include    "mvtuicomponent.h"
#include    "mvtuilayoutchangeobserver.h"

/**
*  TVtUiWhiteBalanceComponentState
*
* Video quality componentstate definition.
*
*  @since S60 v3.2
*/
class TVtUiWhiteBalanceComponentState : public TVtUiComponentState
    {

public:

    /**
    * Constructor
    * @param aComponent Reference to component.
    */
    TVtUiWhiteBalanceComponentState( MVtUiComponent& aComponent );
    
    };
    
/**
*  CVtUiWhiteBalance
*
*  White balance UI feature definition.
*
*  @since S60 v3.2
*/
class CVtUiWhiteBalance : public CVtUiPrefSettingListBase,
    public MVtUiComponent, public MVtUiLayoutChangeObserver 
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiWhiteBalance* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiWhiteBalance();

public: // from MVtUiFeature

    /** 
    * @see MVtUiFeature::StartL 
    */
    void StartL();

    /** 
    * @see MVtUiFeature:Stop
    */
    void Stop();
    
    /** 
    * @see MVtUiFeature::InitFeatureL 
    */
    void InitFeatureL();

public: // from MVtUiComponent

    /**
    * @see MVtUiComponent::ComponentId
    */
    MVtUiComponent::TComponentId ComponentId() const;

    /**
    * @see MVtUiComponent::ComponentAsControl
    */
    CCoeControl* ComponentAsControl();

    /**
    * @see MVtUiComponent::DoActivateL
    */
    void DoActivateL();

    /**
    * @see MVtUiComponent::DoDeactivateL
    */
    void DoDeactivateL();

public: // from MVtUiComponentManager

    /**
    * @see MVtUiComponentManager::HandleLayoutChangeL
    */
    void HandleLayoutChangeL();
    
protected: // from base class
   
   	/**
    * @see CVtUiPrefSettingListBase::CurrentSelection
    */
    virtual TInt CurrentSelection();
    
    /**
    * @see CVtUiPrefSettingListBase::SetItemsL
    */
    virtual void SetItemsL( CDesCArray& aArray );
    
    /**
    * @see CVtUiPrefSettingListBase::SettingPageResId
    */
    virtual TInt SettingPageResId() const;
    
    /**
    * @see CVtUiPrefSettingListBase::SettingPageItemChangedL
    */
    virtual void SettingPageItemChangedL( TInt aIndex );

private:

    /**
    * Constructor
    */
    CVtUiWhiteBalance( CVtUiFeatureManager& aFeatureManager );

    // Maps white balance enum to array index
    TInt MapWBEnumToArrayIndex( MVtEngCameraPreferences::TWhiteBalance&
        aWhiteBalance ) const;
    
    // Maps arrya index to white balance enum 
    MVtEngCameraPreferences::TWhiteBalance MapArrayIndexToWBEnum( TInt aIndex) const;        

    // Callback function that stops the feature.
    static TInt DoStopL( TAny* aAny );
    
    // Callback function that starts the feature.
    static TInt DoStartL( TAny* aAny );    
    
private:

    // Component state
    TVtUiWhiteBalanceComponentState iComponentState;

    };

#endif // CVTUIWHITEBALANCE_H

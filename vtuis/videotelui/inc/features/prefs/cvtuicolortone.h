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
* Description:  Color tone feature.
*
*/


#ifndef C_VTUICOLORTONE_H
#define C_VTUICOLORTONE_H

#include    <mvtengcamerapreferences.h>
#include    "cvtuiprefsettinglistbase.h"
#include    "cvtuifeaturebase.h"
#include    "tvtuicomponentstate.h"
#include    "mvtuicomponent.h"
#include    "mvtuilayoutchangeobserver.h"

/**
*  TVtUiColorToneComponentState
*
* Video quality componentstate definition.
*
*  @since S60 v3.2
*/
class TVtUiColorToneComponentState : public TVtUiComponentState
    {

public:

    /**
    * Constructor
    * @param aComponent Reference to component.
    */
    TVtUiColorToneComponentState( MVtUiComponent& aComponent );
    
    };
    
/**
*  CVtUiColorTone
*
*  Color tone UI feature definition.
*
*  @since S60 v3.2
*/
class CVtUiColorTone : public CVtUiPrefSettingListBase,
    public MVtUiComponent, public MVtUiLayoutChangeObserver
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiColorTone* NewL( CVtUiFeatureManager& aFeatureManager );
    
    /**
    * Destructor
    */
    ~CVtUiColorTone();

public: // from MVtUiFeature

    /** 
    * @see MVtUiFeature::StartL
    */
    void StartL();

     /** 
    * @see MVtUiFeature::Stop
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
    CVtUiColorTone( CVtUiFeatureManager& aFeatureManager );

    // Maps color tone enum to array index
    TInt MapCTEnumToArrayIndex( MVtEngCameraPreferences::TColorTone&
        aColorTone ) const;
    
    // Maps arrya index to color tone enum 
    MVtEngCameraPreferences::TColorTone MapArrayIndexToCTEnum(
        TInt aIndex) const;        

    // Callback function that stops the feature.
    static TInt DoStopL( TAny* aAny );
    
    // Callback function that starts the feature.
    static TInt DoStartL( TAny* aAny );    

private:

    // Component state
    TVtUiColorToneComponentState iComponentState;
  
    };

#endif // CVTUICOLORTONE_H

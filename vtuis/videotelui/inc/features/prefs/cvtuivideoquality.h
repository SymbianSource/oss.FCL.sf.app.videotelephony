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
* Description:  Video quality feature.
*
*/


#ifndef C_VTUIVIDEOQUALITY_H
#define C_VTUIVIDEOQUALITY_H

#include    <gulicon.h>
#include    "cvtuifeaturebase.h"
#include    "mvtuicomponent.h"
#include    "tvtuicomponentstate.h"
#include    "videotelui.hrh"

/**
*  TVtUiVideoQualityComponentState
*
* Video quality componentstate definition.
*
*  @since S60 v3.2
*/
class TVtUiVideoQualityComponentState : public TVtUiComponentState
    {

public:

    /**
    * Constructor
    * @param aComponent Reference to component.
    */
    TVtUiVideoQualityComponentState( MVtUiComponent& aComponent );
    
    };

/**
*  CVtUiVideoQuality
*
*  Video quality UI feature definition.
*
*  @since S60 v3.2
*/
class CVtUiVideoQuality : public CVtUiFeatureBase,
    public MVtUiComponent
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiVideoQuality* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiVideoQuality();

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

private:
    
    // Creates icons for list
    CGulIcon* CreateIconLC( TVtUiBitmapId aIconId, TVtUiBitmapId aMaskId );

    // Shows the selection list
    void ShowSelectionListL();
    
    // Async the selection list
    static TInt AsyncShowSelectionList( TAny* aPtr );
    
    // Reads items from source to target array and updates the selection icon
    // if needed.
    void SetItemsL( CDesCArray& aTarget,const CDesCArray& aSource );
    
    // Return curretly active item.
    TInt ActiveItem() const;
    
    // Item selected, adjust video quality.
    void ItemSelectedL( TInt aItemIndex );
    
private:

    /**
    * Constructor
    */
    CVtUiVideoQuality( CVtUiFeatureManager& aFeatureManager );

    /**
    * 2nd constructor
    */
    void ConstructL();
    
    /**
    * Callback function that stops the feature.
    * @param aAny pointer to an instance of the class.
    * @return always KErrNone.
    */
    static TInt DoStop( TAny* aAny );

private:

    // Component state
    TVtUiVideoQualityComponentState iComponentState;
    
    // Async callback for selection list
    CAsyncCallBack* iShowSelectionListCallback;
    };

#endif // CVTUIVIDEOQUALITY_H

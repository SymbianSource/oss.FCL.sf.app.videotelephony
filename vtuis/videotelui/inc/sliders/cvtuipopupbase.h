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
* Description:  Base class for video telephone popups
*
*/


#ifndef     C_VTUIPOPUPBASE_H
#define     C_VTUIPOPUPBASE_H

#include    <coecobs.h>

#include    "mvtuicomponent.h"
#include    "tvtuicomponentstate.h"
#include    "tvtuifeatureids.h"
#include    "mvtuiresourcechangeobserver.h"
#include    "mvtuikeyeventobserver.h"

class CAknVolumePopup;
class MVtUiComponentManager;
class MVtUiComponentStateObserver;
class CFbsBitmap;

/**
*  TVtUiBaseComponentState
*
*  Base componentstate definition.
*
*  @since S60 v3.2
*/
class TVtUiBaseComponentState : public TVtUiComponentState
    {

public:
    /**
    * Constructor
    * @param aComponent Reference to component.
    */
    TVtUiBaseComponentState( MVtUiComponent& aComponent,
        TVtUiBlockListBitField aBitField  );
    };

/**
*  CVtUiPopupBase
*
*  Base class for vide telephone  popups
*
*  @since S60 v3.2
*/
class CVtUiPopupBase : public CBase, public MVtUiComponent,
    public MVtUiResourceChangeObserver, public MCoeControlObserver,
    public MVtUiKeyEventObserver
    {

public:

    /**
    * Destructor
    */
    ~CVtUiPopupBase();

public: // from MVtUiComponent

    /**
    * @see MVtUiComponent::ComponentId
    */
    TComponentId ComponentId() const;

    /**
    * @see MVtUiComponent::ComponentAsControl
    */
    CCoeControl* ComponentAsControl();

    /**
    * @see MVtUiComponent::DoActivateL
    */
    virtual void DoActivateL();

    /**
    * @see MVtUiComponent::DoDeactivateL
    */
    virtual void DoDeactivateL();

public: // from MVtUiComponentManager

    /**
    * @see MVtUiComponentManager::HandleResourceChangeL
    */
    void HandleResourceChangeL( TInt aType );

public: // from MCoeControlObserver

   /**
   * @see MCoeControlObserver::HandleControlEventL
   */
   virtual void HandleControlEventL(
        CCoeControl* aControl,TCoeEvent aEventType ) = 0;

public: // from MVtUiKeyEventObserver

    /**
    * @see CCoeControl::MVtUiKeyEventObserver
    */
   TKeyResponse OfferKeyEventL( const TKeyEvent& aEvent, TEventCode aCode );

public: // new functions
   
    /**
    * Set popup to be pemanently visible i.e. tapping outside
    * the control doesn't close the control.
    * @param aPermanent If Etrue popup will be visible all the time,
    * otherwise popup is closed and next time will obey timeout.
    */
    void SetPermanenVisibility( TBool aPermanent );
    
    /**
    * Set new component observer
    * @param iCompStateObserver New observer
    */
    void SetObserver( MVtUiComponentStateObserver& aCompStateObserver );
    
    /**
    * Gets slider control value.
    * @return value within slider control's value range
    */
    TInt Value() const;

    /**
    * update popup itself
    */
    virtual void UpdatePopupL();
    
protected: // new functions
   
    /**
    * Set new value to slider control.
    * @param aValue value within slider control's value range.
    */
    void SetValue( TInt aValue );
    
    /**
    * Scales the given value to slider control's value range
    * and sets it to the slider control
    * @param aValue value within popup control's value range.
    */
    void ScaleAndSetValue( TInt aValue );
    
    /**
    * Gets value from the slider control and scales it
    * @return value within popup control's value range
    */ 
    TInt ScaledValue() const;
    
    /**
    * Gets value from the slider control and scales it
    * @param aValue value in popup control's value range.
    * @return value within slider control's value range
    */ 
    TInt SliderValueWithScaling( TInt aValue ) const;
    
    /**
    * Set new end point values popup control
    * These values are not same as slider's range
    */
    void SetMinAndMaxValues( TInt aMax, TInt aMin );
   
    /*
    * Set adjust range of the slider
    */
    void SetAdjustRange( TInt aMinimumValue, TInt aMaximumValue,
        TInt aStepCount );

    /**
    * Set value type for vertical slider control
    */
    void SetValueType( TInt aValueType );
    
    /**
    * Shows popup.
    */
    void ShowPopupL();

    /**
    * Opens popup.
    */
    void OpenPopupL();

    /**
    * Closes popup
    */
    void ClosePopup();
    
    /**
    * Set time out time in seconds
    */
    void SetTimeOut( TInt aTime );
    
    /**
    * Checks whether popup is visible
    */
    TBool IsPopUpVisible();
    
protected:    
    
    /**
    * Constructor
    */
    CVtUiPopupBase( MVtUiComponentManager& aComponentManager,
        TVtUiBlockListBitField aBitField, TComponentId aComponentId );

     /**
     * 2nd constructor
     */
    void BaseConstructL();

private:

    /**
    * Position of the popup
    */
    TPoint PopupPosition() const;
    
    /**
    * Sets popup controls's value
    */
    void SetPopupValue( TInt aValue );

protected: // Set in child constructor

    // Reference to component manager
    MVtUiComponentManager& iComponentManager;

    // Component state
    TVtUiBaseComponentState iComponentState;

    // Component id
    TComponentId iComponentId;

private:

    // class for slider handling
    CAknVolumePopup* iPopup;

    // Interface for component state observing
    MVtUiComponentStateObserver* iCompStateObserver;

    // Maximum value
    TInt iMax;

    // Minimum value
    TInt iMin;

    // Number of steps
    TInt iStepCount;
    
    // Time out for showing popup
    TInt iTimeOutTime;
    
    // Scaling constant
    TInt iScalingConstant;
    
    };

#endif // CVTUIPEFSLIDERBASE_H

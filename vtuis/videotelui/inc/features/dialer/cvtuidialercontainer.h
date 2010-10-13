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
* Description:  Dialer container class.
*
*/


#ifndef C_VTUIDIALERCONTAINER_H
#define C_VTUIDIALERCONTAINER_H

#include    <coecntrl.h>
#include    <CPhCltEmergencyCall.h>
#include    <RPhCltServer.h>
#include    <MPhCltEmergencyCallObserver.h>
#include    "CVtUiAppUi.h"
#include    "mvtuicomponent.h"
#include    "mvtuiresourcechangeobserver.h"
#include    "mvtuikeyeventobserver.h"
#include    "mvtuinumbersource.h"
#include    "tvtuicomponentstate.h"
#include    "cvtuidtmfbuffer.h"

// FORWARD DECLARATIONS
class MVtUiVideoWindow;
class MVtUiComponentManager;
class CVtUiBitmapManager;
class CVtUiDialerVideoControl;
class CVideoDTMFDialer;
class TVtUiStates;
class CVtUiDialerSKModifier;
class CVtUiFeatureManager;
class CAknsBasicBackgroundControlContext;

// CONSTANTS
const TInt KVtUiDigitBufferSize = 128;

/**
 *  TVtUiMiniDialerComponentState
 *
 *  Mini dialer component state definition.
 *
 *  @since S60 v5.0
 */
class TVtUiDialerComponentState : public TVtUiComponentState
    {

public:

    /**
     * Constructor
     */
    TVtUiDialerComponentState( MVtUiComponent& aComponent );

    };

/**
 *  CVtUiDialerContainer
 *
 *  Mini dialer UI feature definition.
 *
 *  @since S60 v5.0
 */
class CVtUiDialerContainer : public CCoeControl,
                             public MVtUiResourceChangeObserver, 
                             public MVtUiComponent,
                             public MVtUiNumberSource, 
                             public MVtUiKeyEventObserver,
                             public MVtUiDTMFBufferObserver,
                             private MPhCltEmergencyCallObserver
    {

public:

    /**
     * Static constructor
     * @param aFeatureManager Reference to feature manager.
     * @param aComponentManager Reference to component manager.
     * @param aBitmapManager Reference to bitmap manager.
     * @return Newly created instance of CVtUiDialerContainer.
     */
    static CVtUiDialerContainer*
        NewL( CVtUiFeatureManager& aFeatureManager );

    /**
     * Destructor
     */
    ~CVtUiDialerContainer();

    /**
     * Registers component to component manager's event handling mechanism.
     * @exception May leave with error KErrAlreadyExists, if the component
     * has already been registered.
     */
    void RegisterComponentL();

    /**
     * Unregisters component from component manager's event handling mechanism.
     */
    void UnregisterComponent();

    /**
    * Returns video window.
    * @return Pointer to video window.
    */
    MVtUiVideoWindow* ComponentAsVideoWindow();
    
    /**
    * @see CCoeControl::MopSupplyObject
    */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

private: // from MVtUiResourceChangeObserver

    /**
    * @see MVtUiResourceChangeObserver::HandleResourceChangeL
    */
    void HandleResourceChangeL( TInt aType );


private: // from MVtUiComponent

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
    void DoActivateL();

    /**
    * @see MVtUiComponent::DoDeactivateL
    */
    void DoDeactivateL();

private: // from MVtUiNumberSource

    /**
     * @see MVtUiNumberSource::GetContents
     */
    void GetContents( TDes& aContents ) const;

private: // from MVtUiKeyEventObserver

    /**
     * @see MVtUiNumberSource::OfferKeyEventL
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aEvent,
        TEventCode aCode );
    
private: // from MPhCltEmergencyCallObserver       
    /**
     * @see  MPhCltEmergencyCallObserver::HandleEmergencyDialL
     */
    virtual void HandleEmergencyDialL( const TInt aStatus );
    
private: // from MVtUiDTMFBufferObserver
    /**
     * @see MVtUiDTMFBufferObserver::NotifyDTMFBufferChanged
     */
    virtual void NotifyDTMFBufferChangedL();

private: // from CCoeControl

    /**
    * @see CCoeControl::Draw
    */
    void Draw( const TRect& aRect ) const;

    /**
    * @see CCoeControl::SizeChanged
    */
    void SizeChanged();

    /**
    * @see CCoeControl::PositionChanged
    */
    void PositionChanged();

    /**
    * @see CCoeControl::CountComponentControls
    */
    TInt CountComponentControls() const;

    /**
    * @see CCoeControl::ComponentControl
    */
    CCoeControl* ComponentControl( TInt aIndex ) const;

private:

    /**
     * Constructor
     */
    CVtUiDialerContainer( CVtUiFeatureManager& aFeatureManager );

    /**
     * 2nd constructor
     */
    void ConstructL( CVtUiBitmapManager& aBitmapManager );

    /**
    * Layouts this control.
    */
    void LayoutDialerContainer();

    /**
    * Returns dialer's rect (wrapper to VtUiLayout).
    */
    TRect DialerRect() const;

    /**
    * Resets digit buffer.
    */
    void Reset();

    /**
    * Appends new digit to digit buffer. If buffer is full, oldest digit is
    * deleted.
    */
    void AppendDigit( TChar aDigit );

    /**
    * Static callback method for deactivating dialer asynchronously.
    */
    static TInt ASyncDoDeactivate( TAny* aSelf );

private:

    // Component state
    TVtUiDialerComponentState iComponentState;

    // Feature manager instance
    CVtUiFeatureManager* iFeatureManager;

    // Component manager
    MVtUiComponentManager* iComponentManager;

    // UI states
    TVtUiStates& iUiStates;

    // Video control instance
    CVtUiDialerVideoControl* iVideoControl;

    // Dialer instance
    CVideoDTMFDialer* iDialer;

    // Buffer for digits
    CVtUiDTMFBuffer* iInputBuffer;

    // Rendering mode
    CVtUiAppUi::TRenderingMode iMode;

    // Softkey modifier for dialer feature
    CVtUiDialerSKModifier* iSKModifier;

    // Asynccallback instance for handling asynchronous deactivation.
    CAsyncCallBack* iAsyncDeactivate;

    // Owned: background context.
    CAknsBasicBackgroundControlContext* iBgContext;
    
    // Phone Server session
    RPhCltServer          iServer;
    
    // Emergency call handler
    CPhCltEmergencyCall*  iEmergency;

    };

#endif // C_VTUIDIALERCONTAINER_H

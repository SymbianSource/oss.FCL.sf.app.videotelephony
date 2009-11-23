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
* Description:  Number entry control for Video Telephone application.
*
*/



#ifndef CVTUINUMBERENTRYCONTROL_H
#define CVTUINUMBERENTRYCONTROL_H

//  INCLUDES
#include    <coecntrl.h>
#include    <aknutils.h>

#include    "mvtuicomponent.h"
#include    "tvtuicomponentstate.h"
#include    "mvtuinumbersource.h"

// FORWARD DECLARATIONS
class MVtUiFeature;
class MVtUiComponentManager;
class TVtUiStates;
class MVtUiNumberEntryControlObserver;
class CVtUiDTMFBuffer;

// CLASS DECLARATION

/**
* TVtUiNumberEntryComponentState
*
* Component state implementation for Number Entry control. Component state is
* used by the Component Manager.
*
* @since S60 3.2
*/
class TVtUiNumberEntryComponentState : public TVtUiComponentState
    {

public:

    /**
     * Constructor.
     */
    TVtUiNumberEntryComponentState( MVtUiComponent& aComponent );

    };

/**
*  Number entry control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiNumberEntryControl
    : public CCoeControl, public MVtUiComponent
    {
    public: // Constructors and destructor

        /**
        * C++ constructor.
        * @param aAppUi application ui.
        * @param aUiStates ui states
        */
        CVtUiNumberEntryControl( MVtUiFeature& aFeature,
            TVtUiStates& aUiStates );

        /**
        * Symbian constructor.
        * @param aRect initial area.
        */
        void ConstructL( const TRect& aRect );

        /**
        * C++ destructor.
        */
        ~CVtUiNumberEntryControl();

    public: // New functions

        /**
        * Opens number entry.
        * @return ETrue if number entry was opened, EFalse otherwise.
        */
        TBool OpenNumberEntry();

        /**
        * Returns ETrue if number entry is open.
        * @return ETrue if number entry is open.
        */
        TBool IsNumberEntryOpen() const;

        /**
        * Closes number entry.
        */
        void CloseNumberEntry();

        /**
         * Register component to component manager.
         */
        void RegisterComponentL( MVtUiComponentManager& aComponentManager );

        /**
         * Unregister component to component manager.
         */
        void UnregisterComponent( MVtUiComponentManager& aComponentManager );

        /**
         * Adds number entry control observer.
         */
        void SetNumberEntryControlObserver(
            MVtUiNumberEntryControlObserver* aObserver );

    public: // Functions from base classes

        /**
        * @see CCoeControl::OfferKeyEventL.
        */
        virtual TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
            TEventCode aType );

    private:

        /**
        * Callback function to close number entry.
        * @param aAny pointer to an instance of this class.
        * @return KErrNone.
        */
        static TInt DoCloseNumberEntry( TAny* aAny );

        /**
        * Called from DoCloseNumberEntry when number entry needs to be closed.
        */
        void HandleTimeoutCloseNumberEntry();

        /**
        * Return ETrue if menu or dialog is being displayed.
        */
        TBool IsDisplayingMenuOrDialog() const;

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

    private:

        // Reference to feature that owns this control.
        MVtUiFeature& iFeature;

        // Number entry area layout.
        TAknLayoutRect iNumberEntryAreaLayout;

        // Component state
        TVtUiNumberEntryComponentState iComponentState;

        // UI States
        TVtUiStates& iUiStates;

        // Number entry control observer
        MVtUiNumberEntryControlObserver* iControlObserver;

        // Buffer for digits
        CVtUiDTMFBuffer* iInputBuffer;
    };

#endif      // CVTUINUMBERENTRYCONTROL_H

// End of File

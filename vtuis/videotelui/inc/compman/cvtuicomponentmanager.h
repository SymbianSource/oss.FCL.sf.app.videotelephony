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
* Description:  Component manager implementation.
*
*/


#ifndef C_VTUICOMPONENTMANAGER_H
#define C_VTUICOMPONENTMANAGER_H

#include <coeaui.h>

#include "mvtuicomponentmanager.h"
#include "mvtuicomponent.h"
#include "tvtuicomponentstate.h"

/**
 *  CVtUiComponentManager
 *
 *  Component manager implementation.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiComponentManager )
    : public CBase, public MVtUiComponentManager
    {

public: // public methods

    /**
     * Static constructor.
     *
     * @return Newly created instance of CVtUiComponentManager class.
     */
    static CVtUiComponentManager* NewL();

    /**
     * Destructor.
     */
    ~CVtUiComponentManager();

    /**
     * Called when a Ws event is delivered.
     *
     * @param aEvent Window server event.
     * @param aDestination Event destination control.
     */
    void HandleWsEventL( const TWsEvent& aEvent, CCoeControl *aDestination );

    /**
     * Called when a resource change is informed.
     *
     * @param aType Type of change.
     */
    void HandleResourceChangeL( TInt aType );

    /**
     * Called when a keyevent needs handling.
     *
     * @param aKeyEvent Key event structure.
     * @param aCode Event code.
     */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType);

    /**
     * Called when a layout change is informed.
     *
     */
    void HandleLayoutChangeL();

public: // from MVtUiComponentManager

    /**
     * @see MVtUiComponentManager::ChangeWsEventRegistration
     */
    TInt ChangeWsEventRegistration( MVtUiWindowServerEventObserver& aObserver,
        TAction aAction );

    /**
     * @see MVtUiComponentManager::ChangeResourceChangeRegistration
     */
    TInt ChangeResourceChangeRegistration(
        MVtUiResourceChangeObserver& aObserver,
        TAction aAction );

    /**
     * @see MVtUiComponentManager::ChangeKeyEventRegistration
     */
    TInt ChangeKeyEventRegistration( MVtUiKeyEventObserver& aComponent,
        TAction aAction );

    /**
     * @see MVtUiComponentManager::ChangeLayoutChangeRegistration
     */
    TInt ChangeLayoutChangeRegistration( MVtUiLayoutChangeObserver& aComponent,
        TAction aAction );

    /**
     * @see MVtUiComponentManager::ChangeComponentRegistration
     */
    TInt ChangeComponentRegistration( TVtUiComponentState& aComponentState,
        TAction aAction );

    /**
     * @see MVtUiComponentManager::RequestActivation
     */
    void RequestActivationL( MVtUiComponent::TComponentId aId );

    /**
     * @see MVtUiComponentManager::DeActivateComponentL
     */
    void DeActivateComponentL( MVtUiComponent::TComponentId aId );

private: // private classes

    /**
     * TStateListItem
     *
     * Contains one component's state in state list.
     */
    class TStateListItem
        {

    public: // public type definitions

		/**
		 * Compare by key type definition.
		 */
        typedef TInt (*TKeyCmpFunc)
            ( const MVtUiComponent::TComponentId*, const TStateListItem& );

    public: // public methods

		/**
		 * Constructor
		 *
		 * @param aState Constant reference to component state.
		 */
        TStateListItem( const TVtUiComponentState& aState );

		/**
		 * Returns component id.
		 *
		 * @return Component's id.
		 */
        MVtUiComponent::TComponentId ComponentId() const;

		/**
		 * Returns component's state.
		 *
		 * @return Component's state.
		 */
        TVtUiComponentState::TState State() const;

		/**
		 * Sets component's state.
		 *
		 * @param aState Component's new state.
		 */
        void SetState( TVtUiComponentState::TState aState );

		/**
		 * Returns const reference to block list.
		 *
		 * @return Constant reference to block list.
		 */
        const TVtUiBlockList& BlockList() const;

		/**
		 * Sets this object as root.
		 */
        void SetRoot();

		/**
		 * Returns ETrue if this object is root.
		 *
		 * @return ETrue if this item is root, EFalse otherwise.
		 */
        TBool IsRoot() const;

		/**
		 * Sets this object as visited.
		 */
        void SetVisited();

		/**
		 * Returns ETrue if this object is visited.
		 *
		 * @return ETrue if this item has been visited, EFalse otherwise.
		 */
        TBool IsVisited() const;

    public: // static public methods

		/**
		 * Returns TLinearOrder for RArray operations. Ordered by component id.
		 *
		 * @return TLinearOrder insntace for RArray operations. Ordering will
		 * be done based on component Id.
		 */
        static TLinearOrder< TStateListItem > LinearOrder();

		/**
		 * Returns key order function for RArray operations.
		 *
		 * @return Key compare method pointer for RArray operations.
		 */
        static TKeyCmpFunc KeyOrder();

		/**
		 * Returns TLinearOrder for RArray operations. Ordered by component
		 * state.
		 *
		 * @return TLinearOrder instance for RArray operations. Ordering will
		 * be done based on component state.
		 */
        static TLinearOrder< TStateListItem > StateOrder();

    private: // static private methods

		/**
		 * StateListItem compare method.
		 */
        static TInt ItemCmpFunc( const TStateListItem& aItem1,
            const TStateListItem& aItem2 );

		/**
		 * StateListItem vs key compare method.
		 */
        static TInt KeyCmpFunc( const MVtUiComponent::TComponentId* aKey,
            const TStateListItem& aItem );

		/**
		 * StateListItem by state compare method.
		 */
        static TInt StateCmpFunc( const TStateListItem& aItem1,
            const TStateListItem& aItem2 );

    private: // data

        // Component's ID
        MVtUiComponent::TComponentId iComponentId;

        // Component's state
        TVtUiComponentState::TState iState;

        // Block mask (IDs which will be blocked by this component)
        TVtUiBlockListBitField iBlockList;

        // ETrue if this component is the root compoent, EFalse otherwise
        TBool iIsRoot;

        // ETrue if this component has been already visited (i.e. evaluated)
        TBool iIsVisited;

        };

    /**
     * TStateList
     *
     * Contains list of component states. This list can be modified and when all
     * modifications are ready, the whole list can be commited at once.
     *
     */
    class TStateList
        {

    public: // public methods

		/**
		 * Constructor.
		 */
        TStateList();

		/**
		 * Destructor.
		 */
        ~TStateList();

		/**
		 * Add new item to state list.
		 *
		 * @param aItem Reference to item to be added to the list.
		 */
        void AddItemL( TStateListItem& aItem );

		/**
		 * Returns number of items in state list.
		 *
		 * @return Number of items on list.
		 */
        TInt ItemCount() const;

		/**
		 * Find state list item by component id.
		 *
		 * @param aComponentId Id of component that will be searched.
		 * @return Index of the component or KErrNotFound if component with
		 * given Id could not be found.
		 */
        TInt FindItem( MVtUiComponent::TComponentId aComponentId ) const;

		/**
		 * Returns reference to state list item at given index.
		 *
		 * @param aIndex Index of the item to be fetched.
		 * @return Reference to item at given index.
		 */
        TStateListItem& At( TInt aIndex );

		/**
		 * Returns const reference to state list item at given index.
		 *
		 * @param aIndex Index of the item to be fetched.
		 * @return Constant reference to item at given index.
		 */
        const TStateListItem& At( TInt aIndex ) const;

		/**
		 * Sorts list using given linear order.
		 *
		 * @param aOrder TLinearObject that will be used in sorting.
		 */
        void Sort(
            TLinearOrder< CVtUiComponentManager::TStateListItem > aOrder );

    private: // data

        // List items
        RArray< TStateListItem > iItems;

        };

private: // enumerations

    /**
     * Activation actions
     */
    enum TActivationAction
        {
        /** Hide component */
        EHide,
        /** Show component */
        EShow
        };

private:

    /**
     * Constructor
     */
    CVtUiComponentManager();

    /**
     * 2nd constructor, may leave
     */
    void ConstructL();

    /**
     * Adds or removes component from given array.
     */
    template < class T >
    TInt AddOrRemoveComponent( RPointerArray< T >& aArray, T* aComponent,
        TAction aAction );

    /**
     * Returns linear order object for array operations.
     */
    static TLinearOrder< MVtUiComponent > ComponentOrder();

    /**
     * Returns linear order object for array operations.
     */
    static TLinearOrder< TVtUiComponentState > ComponentStateOrder();

    /**
     * Starts activation process.
     */
    void DoActivationL( TVtUiComponentState& aComponentState,
        TVtUiComponentState::TState aNewState );

    /**
     * Starts deactivation process.
     */
    void DoDeactivationL( TVtUiComponentState& aComponentState,
        TVtUiComponentState::TState aNewState );

    /**
     * Calculates activation.
     */
    void CalculateActivationL( const TVtUiBlockList& aBlockList,
        const TVtUiBlockList& aExclList, TStateList& aStateList,
        TActivationAction aAction );

    /**
     * Commits activation calculation results.
     */
    void CommitStateListL( TStateList& aList );

    /**
     * Constructs component state list before the calculations.
     */
    void ConstructStateListL( TStateList& aList );

private: // data

    // Window server event listeners
    RPointerArray< MVtUiWindowServerEventObserver > iWsEventObservers;

    // Resource change event listeners
    RPointerArray< MVtUiResourceChangeObserver > iResourceChangeObservers;

    // Key event listeners
    RPointerArray< MVtUiKeyEventObserver > iKeyEventObservers;
    
    // Layout change listeners
    RPointerArray< MVtUiLayoutChangeObserver > iLayoutChangeObservers;

    // Registered components
    RPointerArray< TVtUiComponentState > iComponents;

    };

#endif // C_VTUICOMPONENTMANAGER_H

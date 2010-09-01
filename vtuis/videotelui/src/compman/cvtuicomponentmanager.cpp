/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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


#include <cvtlogger.h>

#include "cvtuicomponentmanager.h"
#include "mvtuiwindowservereventobserver.h"
#include "mvtuiresourcechangeobserver.h"
#include "mvtuikeyeventobserver.h"
#include "mvtuilayoutchangeobserver.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// CmpByPtr
// ---------------------------------------------------------------------------
//
template < class T >
TInt CmpByPtr( const T& aObj1, const T& aObj2 )
    {
    return reinterpret_cast< TInt >( &aObj1 ) -
        reinterpret_cast< TInt >( &aObj2 );
    }

// ---------------------------------------------------------------------------
// FindByPtr
// ---------------------------------------------------------------------------
//
template < class T >
TInt FindByPtr( const TInt* aPtr, const T& aObj )
    {
    return *aPtr - reinterpret_cast< TInt >( &aObj );
    }

// ---------------------------------------------------------------------------
// CmpMVtUiComponent
// ---------------------------------------------------------------------------
//
TInt CmpMVtUiComponent( const MVtUiComponent& aC1, const MVtUiComponent& aC2 )
    {
    return ( aC1.ComponentId() - aC2.ComponentId() );
    }

// ---------------------------------------------------------------------------
// CmpTVtUiComponentState
// ---------------------------------------------------------------------------
//
TInt CmpTVtUiComponentState( const TVtUiComponentState& aC1,
    const TVtUiComponentState& aC2 )
    {
    return ( aC1.Component().ComponentId() - aC2.Component().ComponentId() );
    }

// ---------------------------------------------------------------------------
// CmpTVtUiComponentStateByKey
// ---------------------------------------------------------------------------
//
TInt CmpTVtUiComponentStateByKey( const MVtUiComponent::TComponentId* aKey,
    const TVtUiComponentState& aC )
    {
    return ( *aKey - aC.Component().ComponentId() );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiComponentManager::NewL
// ---------------------------------------------------------------------------
//
CVtUiComponentManager* CVtUiComponentManager::NewL()
    {
    __VTPRINTENTER( "CompMgr.NewL" )
    CVtUiComponentManager* self = new ( ELeave ) CVtUiComponentManager();
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "CompMgr.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::~CVtUiComponentManager
// ---------------------------------------------------------------------------
//
CVtUiComponentManager::~CVtUiComponentManager()
    {
    __VTPRINTENTER( "CompMgr.~" )
    iWsEventObservers.Close();
    iResourceChangeObservers.Close();
    iKeyEventObservers.Close();
    iLayoutChangeObservers.Close();
    iComponents.Close();
    __VTPRINTEXIT( "CompMgr.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::HandleWsEventL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::HandleWsEventL( const TWsEvent& aEvent,
    CCoeControl* aDestination )
    {
    for ( TInt i = iWsEventObservers.Count() - 1; i >= 0; i-- )
        {
        iWsEventObservers[ i ]->HandleWsEventL( aEvent, aDestination );
        }
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::HandleResourceChangeL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::HandleResourceChangeL( TInt aType )
    {
    for ( TInt i = iResourceChangeObservers.Count() - 1; i >= 0; i-- )
        {
        iResourceChangeObservers[ i ]->HandleResourceChangeL( aType );
        }
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager:OfferKeyEventL
// ---------------------------------------------------------------------------
//
TKeyResponse CVtUiComponentManager::OfferKeyEventL(
    const TKeyEvent& aEvent, TEventCode aCode )
    {
    TKeyResponse response( EKeyWasNotConsumed );
    for ( TInt i = iKeyEventObservers.Count() - 1; i >= 0; i-- )
        {
        response = iKeyEventObservers[ i ]->OfferKeyEventL( aEvent, aCode );
        if ( response == EKeyWasConsumed )
            {
            break;
            }
        }
    return response;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::HandleLayoutChangeL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::HandleLayoutChangeL()
    {
    for ( TInt i = iLayoutChangeObservers.Count() - 1; i >= 0; i-- )
        {
        iLayoutChangeObservers[ i ]->HandleLayoutChangeL();
        }    
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ChangeWsEventRegistration
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::ChangeWsEventRegistration(
    MVtUiWindowServerEventObserver& aObserver, TAction aAction )
    {
    return AddOrRemoveComponent( iWsEventObservers, &aObserver, aAction );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ChangeResourceChangeRegistration
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::ChangeResourceChangeRegistration(
    MVtUiResourceChangeObserver& aObserver, TAction aAction )
    {
    return AddOrRemoveComponent( iResourceChangeObservers, &aObserver,
        aAction );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ChangeKeyEventRegistration
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::ChangeKeyEventRegistration(
    MVtUiKeyEventObserver& aObserver, TAction aAction )
    {
    return AddOrRemoveComponent( iKeyEventObservers, &aObserver, aAction );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ChangeLayoutChangeRegistration
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::ChangeLayoutChangeRegistration(
    MVtUiLayoutChangeObserver& aObserver, TAction aAction )
    {
    return AddOrRemoveComponent( iLayoutChangeObservers, &aObserver, aAction );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ChangeComponentRegistration
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::ChangeComponentRegistration(
    TVtUiComponentState& aComponentState, TAction aAction )
    {
    __VTPRINTENTER( "CompMgr.ChangeComponentRegistrationL" )
    TInt result( KErrNone );
    if ( aAction == ERegister )
        {
        result =
            iComponents.InsertInOrder( &aComponentState,
                ComponentStateOrder() );
        }
    else
        {
        TInt index( iComponents.FindInOrder(
            &aComponentState, ComponentStateOrder() ) );
        if ( index != KErrNotFound )
            {
            iComponents.Remove( index );
            }
        }
    __VTPRINTEXITR( "CompMgr.ChangeComponentRegistrationL %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::RequestActivationL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::RequestActivationL(
    MVtUiComponent::TComponentId aId )
    {
    __VTPRINTENTER( "CompMgr.RequestActivationL" )
    TInt index( iComponents.FindInOrder( aId, ::CmpTVtUiComponentStateByKey ) );
    if ( index == KErrNotFound )
        {
        User::Leave( index );
        }
    else
        {
        TVtUiComponentState& state( *iComponents[ index ] );
        if ( state.State() == TVtUiComponentState::EActive )
            {
            User::Leave( KErrNotReady );
            }
        else
            {
            DoActivationL( state, TVtUiComponentState::EActive );
            }
        }
    __VTPRINTEXIT( "CompMgr.RequestActivationL" )
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::DeActivateComponentL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::DeActivateComponentL(
    MVtUiComponent::TComponentId aId )
    {
    __VTPRINTENTER( "CompMgr.DeActivateComponentL" )
    TInt index( iComponents.FindInOrder( aId, ::CmpTVtUiComponentStateByKey ) );
    if ( index == KErrNotFound )
        {
        User::Leave( index );
        }
    else
        {
        TVtUiComponentState& state( *iComponents[ index ] );
        if ( state.State() == TVtUiComponentState::EInactive )
            {
            User::Leave( KErrNotReady );
            }
        else
            {
            DoDeactivationL( state, TVtUiComponentState::EInactive );
            }
        }
    __VTPRINTEXIT( "CompMgr.DeActivateComponentL" )
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::DoActivationL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::DoActivationL(
	TVtUiComponentState& aComponentState,
	TVtUiComponentState::TState aNewState )
    {
    __VTPRINTENTER( "CompMgr.DoActivationL" )
    TStateList stateList;
    ConstructStateListL( stateList );
    TInt index( stateList.FindItem(
    	aComponentState.Component().ComponentId() ) );
    if ( index != KErrNotFound )
        {
        TStateListItem& sli( stateList.At( index ) );
        TVtUiBlockListBitField exclList;
        for ( TInt i = stateList.ItemCount() - 1; i >= 0; i-- )
        	{
        	TStateListItem& sli2( stateList.At( i ) );
        	if ( sli2.ComponentId() != sli.ComponentId() )
        		{
        		if ( sli2.State() == TVtUiComponentState::EActive &&
        			 !sli.BlockList().Contains( sli2.ComponentId() ) )
        			{
        			exclList.Union( sli2.BlockList() );
        			}
        		}
        	}
       	sli.SetRoot();
        sli.SetState( aNewState );
        CalculateActivationL( sli.BlockList(), exclList, stateList, EHide );
        }
    CommitStateListL( stateList );
    __VTPRINTEXIT( "CompMgr.DoActivationL" )
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::DoDeactivationL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::DoDeactivationL(
    TVtUiComponentState& aComponentState,
    TVtUiComponentState::TState aNewState )
    {
    __VTPRINTENTER( "CompMgr.DoDeactivationL" )
    TStateList stateList;
    ConstructStateListL( stateList );
    TInt index( stateList.FindItem(
        aComponentState.Component().ComponentId() ) );
    if ( index != KErrNotFound )
        {
        TStateListItem& sli( stateList.At( index ) );
        TVtUiBlockListBitField exclList;
        if ( sli.State() == TVtUiComponentState::EActive )
        	{
	        for ( TInt i = stateList.ItemCount() - 1; i >= 0; i-- )
	        	{
	        	TStateListItem& sli2( stateList.At( i ) );
	        	if ( sli2.ComponentId() != sli.ComponentId() )
	        		{
	        		if ( sli2.State() == TVtUiComponentState::EActive )
	        			{
	        			exclList.Union( sli2.BlockList() );
	        			}
	        		}
	        	}
        	}
        sli.SetRoot();
        sli.SetState( aNewState );
        CalculateActivationL( sli.BlockList(), exclList, stateList, EShow );
        }
    CommitStateListL( stateList );
    __VTPRINTEXIT( "CompMgr.DoDeactivationL" )
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::CommitStateListL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::CommitStateListL( TStateList& aList )
    {
    __VTPRINTENTER( "CompMgr.CommitStateListL" )
    // Sort list by component state. Components will first deactivated, then
    // blocked and finally activated.
    aList.Sort( TStateListItem::StateOrder() );
    for ( TInt i = 0; i < aList.ItemCount(); i++ )
        {
        const TStateListItem& sli( aList.At( i ) );
        TInt index( iComponents.FindInOrder( sli.ComponentId(),
            ::CmpTVtUiComponentStateByKey ) );
        if ( index != KErrNotFound )
            {
            TVtUiComponentState& cs( *iComponents[ index ] );
            if ( cs.State() != sli.State() )
                {
                switch ( sli.State() )
                    {
                case TVtUiComponentState::EInactive:
                    cs.DeActivateComponentL();
                    break;

                case TVtUiComponentState::EActive:
                    cs.ActivateComponentL();
                    break;

                case TVtUiComponentState::EWaiting:
                    cs.BlockComponentL();
                    break;

                default:
                    User::Leave( KErrArgument );
                    break;
                    }
                }
            }
        }
    __VTPRINTEXIT( "CompMgr.CommitStateListL" )
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::CalculateActivationL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::CalculateActivationL(
    const TVtUiBlockList& aBlockList,
    const TVtUiBlockList& aExclList,
    TStateList& aStateList, TActivationAction aAction )
    {
    __VTPRINTENTER( "CompMgr.CalculateActivationL" )
    __VTPRINT2( DEBUG_GEN, "aAction = %d", (TInt)aAction )
    TVtUiBlockListBitField blockList;
    CVtUiBlockListIterator* iterator = aBlockList.IteratorLC();
    while ( iterator->HasNext() )
        {
        MVtUiComponent::TComponentId cid( iterator->Next() );
		if ( aExclList.Contains( cid ) )
			{
			continue;
			}
        TInt index( aStateList.FindItem( cid ) );
        if ( index != KErrNotFound )
            {
            TStateListItem& sli( aStateList.At( index ) );
            __VTPRINT3( DEBUG_GEN, "@1, Id = %d, state = %d", (TInt)sli.ComponentId(), (TInt)sli.State() )
            if ( !sli.IsRoot() )
                {
                if ( aAction == EShow )
                    {
                    // if action == EShow and component is being blocked,
                    // then activate component
                    if ( sli.State() == TVtUiComponentState::EWaiting )
                        {
                        sli.SetState( TVtUiComponentState::EActive );
                        if ( !sli.IsVisited() )
                            {
                            blockList.Union( sli.BlockList() );
                            }
                        sli.SetVisited();
                        }
                    }
                else // aAction == EHide
                    {
                    // if action == EHide and component is active, then
                    // block component
                    if ( sli.State() == TVtUiComponentState::EActive )
                        {
                        sli.SetState( TVtUiComponentState::EWaiting );
                        if ( !sli.IsVisited() )
                            {
                            blockList.Union( sli.BlockList() );
                            }
                        sli.SetVisited();
                        }
                    }
                }
			__VTPRINT3( DEBUG_GEN, "@2, Id = %d, state = %d", (TInt)sli.ComponentId(), (TInt)sli.State() )
            }
        }
    CleanupStack::PopAndDestroy(); // iterator
    if ( !blockList.IsEmpty() )
        {
        CalculateActivationL( blockList, aExclList, aStateList,
            ( aAction == EShow ) ? EHide : EShow );
        }
    __VTPRINTEXIT( "CompMgr.CalculateActivationL" )
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ConstructStateListL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::ConstructStateListL( TStateList& aList )
    {
    for ( TInt i = iComponents.Count() - 1; i >= 0; i-- )
        {
        TStateListItem sli( *iComponents[ i ] );
        aList.AddItemL( sli );
        }
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::CVtUiComponentManager
// ---------------------------------------------------------------------------
//
CVtUiComponentManager::CVtUiComponentManager()
    : iWsEventObservers( 1 ), iResourceChangeObservers( 1 ),
      iKeyEventObservers( 1 ),iLayoutChangeObservers( 1 ), iComponents( 1 )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::ConstructL()
    {
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::AddOrRemoveComponent
// ---------------------------------------------------------------------------
//
template < class T >
TInt CVtUiComponentManager::AddOrRemoveComponent( RPointerArray< T >& aArray,
    T* aComponent, TAction aAction )
    {
    __VTPRINTENTER( "CompMgr.AddOrRemoveComponent" )
    TInt result( KErrNone );
    if ( aAction == ERegister )
        {
        result = aArray.InsertInOrder( aComponent, ::CmpByPtr );
        }
    else
        {
        TInt index( aArray.FindInOrder( aComponent, ::CmpByPtr ) );
        if ( index != KErrNotFound )
            {
            aArray.Remove( index );
            }
        }
    __VTPRINTEXITR( "CompMgr.AddOrRemoveComponent %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ComponentOrder
// ---------------------------------------------------------------------------
//
TLinearOrder< MVtUiComponent > CVtUiComponentManager::ComponentOrder()
    {
    return TLinearOrder< MVtUiComponent >( ::CmpMVtUiComponent );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::ComponentStateOrder
// ---------------------------------------------------------------------------
//
TLinearOrder< TVtUiComponentState > CVtUiComponentManager::ComponentStateOrder()
    {
    return TLinearOrder< TVtUiComponentState >( ::CmpTVtUiComponentState );
    }

// Implementation of CVtUiComponentManager::TStateListItem

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::TStateListItem
// ---------------------------------------------------------------------------
//
CVtUiComponentManager::TStateListItem::TStateListItem(
    const TVtUiComponentState& aState )
    : iComponentId( aState.Component().ComponentId() ),
      iState( aState.State() ), iIsRoot( EFalse ), iIsVisited( EFalse )
    {
    iBlockList.Union( aState.BlockList() );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::ComponentId
// ---------------------------------------------------------------------------
//
MVtUiComponent::TComponentId
CVtUiComponentManager::TStateListItem::ComponentId() const
    {
    return iComponentId;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::State
// ---------------------------------------------------------------------------
//
TVtUiComponentState::TState CVtUiComponentManager::TStateListItem::State() const
    {
    return iState;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::SetState
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::TStateListItem::SetState(
    TVtUiComponentState::TState aState )
    {
    iState = aState;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::BlockList
// ---------------------------------------------------------------------------
//
const TVtUiBlockList& CVtUiComponentManager::TStateListItem::BlockList() const
    {
    return iBlockList;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::SetRoot
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::TStateListItem::SetRoot()
    {
    iIsRoot = ETrue;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::IsRoot
// ---------------------------------------------------------------------------
//
TBool CVtUiComponentManager::TStateListItem::IsRoot() const
    {
    return iIsRoot;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::SetVisited
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::TStateListItem::SetVisited()
    {
    iIsVisited = ETrue;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::IsVisited
// ---------------------------------------------------------------------------
//
TBool CVtUiComponentManager::TStateListItem::IsVisited() const
    {
    return iIsVisited;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::KeyOrder
// ---------------------------------------------------------------------------
//
CVtUiComponentManager::TStateListItem::TKeyCmpFunc
CVtUiComponentManager::TStateListItem::KeyOrder()
    {
    return KeyCmpFunc;
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::LinearOrder
// ---------------------------------------------------------------------------
//
TLinearOrder< CVtUiComponentManager::TStateListItem >
CVtUiComponentManager::TStateListItem::LinearOrder()
    {
    return TLinearOrder< TStateListItem >( ItemCmpFunc );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::StateOrder
// ---------------------------------------------------------------------------
//
TLinearOrder< CVtUiComponentManager::TStateListItem >
CVtUiComponentManager::TStateListItem::StateOrder()
    {
    return TLinearOrder< TStateListItem >( StateCmpFunc );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::ItemCmpFunc
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::TStateListItem::ItemCmpFunc(
    const TStateListItem& aItem1, const TStateListItem& aItem2 )
    {
    return ( aItem1.ComponentId() - aItem2.ComponentId() );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::KeyCmpFunc
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::TStateListItem::KeyCmpFunc(
    const MVtUiComponent::TComponentId* aKey, const TStateListItem& aItem )
    {
    return ( *aKey - aItem.ComponentId() );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateListItem::StateCmpFunc
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::TStateListItem::StateCmpFunc(
    const TStateListItem& aItem1, const TStateListItem& aItem2 )
    {
    return ( aItem1.State() - aItem2.State() );
    }
// Implementation of CVtUiComponentManager::TStateList

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::TStateList
// ---------------------------------------------------------------------------
//
CVtUiComponentManager::TStateList::TStateList() : iItems( 1 )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::~TStateList
// ---------------------------------------------------------------------------
//
CVtUiComponentManager::TStateList::~TStateList()
    {
    iItems.Close();
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::AddItemL
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::TStateList::AddItemL( TStateListItem& aItem )
    {
    iItems.InsertInOrderL( aItem, TStateListItem::LinearOrder() );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::ItemCount
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::TStateList::ItemCount() const
    {
    return iItems.Count();
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::FindItem
// ---------------------------------------------------------------------------
//
TInt CVtUiComponentManager::TStateList::FindItem(
    MVtUiComponent::TComponentId aComponentId ) const
    {
    return iItems.FindInOrder( aComponentId, TStateListItem::KeyOrder() );
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::At
// ---------------------------------------------------------------------------
//
CVtUiComponentManager::TStateListItem&
CVtUiComponentManager::TStateList::At( TInt aIndex )
    {
    return iItems[ aIndex ];
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::At
// ---------------------------------------------------------------------------
//
const CVtUiComponentManager::TStateListItem&
CVtUiComponentManager::TStateList::At( TInt aIndex ) const
    {
    return iItems[ aIndex ];
    }

// ---------------------------------------------------------------------------
// CVtUiComponentManager::TStateList::Sort
// ---------------------------------------------------------------------------
//
void CVtUiComponentManager::TStateList::Sort(
    TLinearOrder< CVtUiComponentManager::TStateListItem > aOrder )
    {
    iItems.Sort( aOrder );
    }

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
* Description:  Component state base class.
*
*/


#include <cvtlogger.h>

#include "tvtuicomponentstate.h"

// -----------------------------------------------------------------------------
// TVtUiComponentState::ActivateComponentL
// -----------------------------------------------------------------------------
//
void TVtUiComponentState::ActivateComponentL()
    {
    __VTPRINTENTER( "CompState.ActivateComponentL" )
    iComponent.DoActivateL();
    iState = EActive;
    __VTPRINTEXITR( "CompState.ActivateComponentL %d", iState )
    }

// -----------------------------------------------------------------------------
// TVtUiComponentState::BlockComponentL
// -----------------------------------------------------------------------------
//
void TVtUiComponentState::BlockComponentL()
    {
    __VTPRINTENTER( "CompState.BlockComponentL" )
    iComponent.DoDeactivateL();
    iState = EWaiting;
    __VTPRINTEXITR( "CompState.BlockComponentL %d", iState )
    }

// -----------------------------------------------------------------------------
// TVtUiComponentState::DeActivateComponentL
// -----------------------------------------------------------------------------
//
void TVtUiComponentState::DeActivateComponentL()
    {
    __VTPRINTENTER( "CompState.DeActivateComponentL" )
    iComponent.DoDeactivateL();
    iState = EInactive;
    __VTPRINTEXITR( "CompState.DeActivateComponentL %d", iState )
    }

// -----------------------------------------------------------------------------
// TVtUiComponentState::State
// -----------------------------------------------------------------------------
//
TVtUiComponentState::TState TVtUiComponentState::State() const
    {
    return iState;
    }

// -----------------------------------------------------------------------------
// TVtUiComponentState::Component
// -----------------------------------------------------------------------------
//
const MVtUiComponent& TVtUiComponentState::Component() const
    {
    return iComponent;
    }

// -----------------------------------------------------------------------------
// TVtUiComponentState::BlockMask
// -----------------------------------------------------------------------------
//
const TVtUiBlockList& TVtUiComponentState::BlockList() const
    {
    return iBlockList;
    }

// -----------------------------------------------------------------------------
// TVtUiComponentState::BlockMask
// -----------------------------------------------------------------------------
//
TVtUiBlockList& TVtUiComponentState::BlockList()
    {
    return iBlockList;
    }

// -----------------------------------------------------------------------------
// TVtUiComponentState::InformDeactivation
// -----------------------------------------------------------------------------
//
TVtUiComponentState::TVtUiComponentState( MVtUiComponent& aComponent,
    const TVtUiBlockList& aBlockList )
    : iComponent( aComponent ), iState( EInactive )
    {
    __VTPRINTENTER( "CompState.ctor" )
    
    if( MVtUiComponent::EComponentIdToolbar == iComponent.ComponentId() )
        return;
        
    iBlockList.Union( aBlockList );
    __VTPRINTEXIT( "CompState.ctor" )
    }

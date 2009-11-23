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
* Description:  Menu context class.
*
*/


#include <cvtlogger.h>

#include "cvtuimenucontext.h"

/** Menu context reference priority */
const TInt KVtUiMenuContextPriority = 100;

// ---------------------------------------------------------------------------
// CVtUiMenuContext::~CVtUiMenuContext
// ---------------------------------------------------------------------------
//
CVtUiMenuContext::~CVtUiMenuContext()
    {
    __VTPRINTENTER( "MenuCtx.~" )
    UnregisterCommandContext();
    __VTPRINTEXIT( "MenuCtx.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenuContext::NewL
// ---------------------------------------------------------------------------
//
CVtUiMenuContext* CVtUiMenuContext::NewL(
    MVtUiCommandManager& aCommandManager )
    {
    __VTPRINTENTER( "MenuCtx.NewL" )
    CVtUiMenuContext* self = new ( ELeave ) CVtUiMenuContext( aCommandManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "MenuCtx.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiMenuContext::ValidateL
// ---------------------------------------------------------------------------
//
void CVtUiMenuContext::ValidateL( CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "MenuCtx.ValidateL" )
    ValidateMenuItemsL( aAction );
    __VTPRINTEXIT( "MenuCtx.ValidateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenuContext::CVtUiMenuContext
// ---------------------------------------------------------------------------
//
CVtUiMenuContext::CVtUiMenuContext( MVtUiCommandManager& aCommandManager )
    : CVtUiCmdContext( aCommandManager, EVtUiCmdContextTypeMenu,
      KVtUiMenuContextPriority )
    {
    __VTPRINTENTER( "MenuCtx.ctor" )
    __VTPRINTEXIT( "MenuCtx.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenuContext::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiMenuContext::ConstructL()
    {
    __VTPRINTENTER( "MenuCtx.ConstructL" )
    RegisterCommandContextL();
    __VTPRINTEXIT( "MenuCtx.ConstructL" )
    }

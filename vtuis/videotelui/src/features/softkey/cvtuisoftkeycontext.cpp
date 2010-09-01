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
* Description:  Sofkey context class implementation.
*
*/


#include <cvtlogger.h>

#include "cvtuisoftkeycontext.h"

/** Softkey context reference priority */
const TInt KVtUiSoftkeyContextPriority = 200;

// ---------------------------------------------------------------------------
// CVtUiSoftkeyContext::~CVtUiSoftkeyContext
// ---------------------------------------------------------------------------
//
CVtUiSoftkeyContext::~CVtUiSoftkeyContext()
    {
    __VTPRINTENTER( "SKCtx.~" )
    UnregisterCommandContext();
    __VTPRINTEXIT( "SKCtx.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeyContext::NewL
// ---------------------------------------------------------------------------
//
CVtUiSoftkeyContext* CVtUiSoftkeyContext::NewL(
    MVtUiCommandManager& aCommandManager )
    {
    __VTPRINTENTER( "SKCtx.NewL" )
    CVtUiSoftkeyContext* self =
        new ( ELeave ) CVtUiSoftkeyContext( aCommandManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "SKCtx.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeyContext::ValidateL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeyContext::ValidateL( CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "SKCtx.ValidateL" )
    ValidateSoftkeyItemsL( aAction );
    __VTPRINTEXIT( "SKCtx.ValidateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeyContext::CVtUiSoftkeyContext
// ---------------------------------------------------------------------------
//
CVtUiSoftkeyContext::CVtUiSoftkeyContext( MVtUiCommandManager& aCommandManager )
    : CVtUiCmdContext( aCommandManager, EVtUiCmdContextTypeSoftkey,
      KVtUiSoftkeyContextPriority )
    {
    __VTPRINTENTER( "SKCtx.ctor" )
    __VTPRINTEXIT( "SKCtx.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeyContext::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeyContext::ConstructL()
    {
    __VTPRINTENTER( "SKCtx.ConstructL" )
    RegisterCommandContextL();
    __VTPRINTEXIT( "SKCtx.ConstructL" )
    }

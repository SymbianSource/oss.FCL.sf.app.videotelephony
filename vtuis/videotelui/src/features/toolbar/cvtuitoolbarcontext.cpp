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
* Description:  Toolbar context implementation.
*
*/


#include <cvtlogger.h>

#include "cvtuitoolbarcontext.h"

// ======== LOCAL FUNCTIONS ========

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiToolbarContext::~CVtUiToolbarContext
// ---------------------------------------------------------------------------
//
CVtUiToolbarContext::~CVtUiToolbarContext()
    {
    __VTPRINTENTER( "ToolbarCtx.~" )
    UnregisterCommandContext();
    __VTPRINTEXIT( "ToolbarCtx.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarContext::NewL
// ---------------------------------------------------------------------------
//
CVtUiToolbarContext* CVtUiToolbarContext::NewL(
    MVtUiCommandManager& aCommandManager )
    {
    __VTPRINTENTER( "ToolbarCtx.NewL" )
    CVtUiToolbarContext* self =
        new ( ELeave ) CVtUiToolbarContext( aCommandManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "ToolbarCtx.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarContext::ValidateL
// ---------------------------------------------------------------------------
//
void CVtUiToolbarContext::ValidateL( CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "ToolbarCtx.ValidateL" )
    ValidateToolbarItemsL( aAction );
    __VTPRINTEXIT( "ToolbarCtx.ValidateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarContext::CVtUiToolbarContext
// ---------------------------------------------------------------------------
//
CVtUiToolbarContext::CVtUiToolbarContext(
    MVtUiCommandManager& aCommandManager )
    : CVtUiCmdContext( aCommandManager, EVtUiCmdContextTypeToolbar,
      KVtUiToolbarContextPriority )
    {
    __VTPRINTENTER( "ToolbarCtx.ctor" )
    __VTPRINTEXIT( "ToolbarCtx.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarContext::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiToolbarContext::ConstructL()
    {
    __VTPRINTENTER( "ToolbarCtx.ConstructL" )
    RegisterCommandContextL();
    __VTPRINTEXIT( "ToolbarCtx.ConstructL" )
    }
    
//  End of File


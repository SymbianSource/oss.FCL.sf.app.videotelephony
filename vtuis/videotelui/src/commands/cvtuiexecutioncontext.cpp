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
* Description:  Execution context class.
*
*/


#include <cvtlogger.h>

#include "cvtuiexecutioncontext.h"
#include "cvtuicmdcustomvalidationactionbase.h"

/** Execution context reference priority */
static const TInt KVtUiExecutionContextPriority = 1000;

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiExecutionContext::~CVtUiExecutionContext
// ---------------------------------------------------------------------------
//
CVtUiExecutionContext::~CVtUiExecutionContext()
    {
    __VTPRINTENTER( "ExecCtx.~" )
    UnregisterCommandContext();
    __VTPRINTEXIT( "ExecCtx.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiExecutionContext::NewL
// ---------------------------------------------------------------------------
//
CVtUiExecutionContext* CVtUiExecutionContext::NewL(
    MVtUiCommandManager& aCommandManager )
    {
    __VTPRINTENTER( "ExecCtx.NewL" )
    CVtUiExecutionContext* self =
        new ( ELeave ) CVtUiExecutionContext( aCommandManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "ExecCtx.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiExecutionContext::ValidateL
// ---------------------------------------------------------------------------
//
void CVtUiExecutionContext::ValidateL( CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "ExecCtx.ValidateL" )
    CustomValidationL(
        static_cast< CVtUiCmdCustomValidationActionBase& >( aAction ) );
    __VTPRINTEXIT( "ExecCtx.ValidateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiExecutionContext::CVtUiExecutionContext
// ---------------------------------------------------------------------------
//
CVtUiExecutionContext::CVtUiExecutionContext(
    MVtUiCommandManager& aCommandManager )
    : CVtUiCmdContext( aCommandManager, EVtUiCmdContextTypeExecution,
      KVtUiExecutionContextPriority )
    {
    __VTPRINTENTER( "ExecCtx.ctor" )
    __VTPRINTEXIT( "ExecCtx.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiExecutionContext::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiExecutionContext::ConstructL()
    {
    __VTPRINTENTER( "ExecCtx.ConstructL" )
    RegisterCommandContextL();
    __VTPRINTEXIT( "ExecCtx.ConstructL" )
    }

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
* Description:  Command context base class.
*
*/


#include <cvtlogger.h>

#include "cvtuicmdcontext.h"
#include "cvtuicmdvalidatorbase.h"
#include "cvtuicmdvalidationactionbase.h"
#include "mvtuicommandmanager.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// Compare routine used by InsertInOrder() and FindInOrder() to sort validator
// instances by priority.
// ---------------------------------------------------------------------------
//
TInt ValidatorPriCmpFunc( const CVtUiCmdValidatorBase& aV1,
    const CVtUiCmdValidatorBase& aV2 )
    {
    return aV1.Priority() - aV2.Priority();
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiCmdContext::~CVtUiCmdContext
// ---------------------------------------------------------------------------
//
CVtUiCmdContext::~CVtUiCmdContext()
    {
    __VTPRINTENTER( "CmdCtx.~" )
    iValidators.Reset();
    __VTPRINTEXIT( "CmdCtx.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::ReferencePriority
// ---------------------------------------------------------------------------
//
TInt CVtUiCmdContext::ReferencePriority() const
    {
    __VTPRINTENTER( "CmdCtx.ReferencePriority" )
    __VTPRINTEXITR( "CmdCtx.ReferencePriority %d", iReferencePriority )
    return iReferencePriority;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::ContextType
// ---------------------------------------------------------------------------
//
TVtUiCmdContextType CVtUiCmdContext::ContextType() const
    {
    __VTPRINTENTER( "CmdCtx.ContextType" )
    __VTPRINTEXITR( "CmdCtx.ContextType %d", iContextType )
    return iContextType;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::AddValidator
// ---------------------------------------------------------------------------
//
TInt CVtUiCmdContext::AddValidator( CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdCtx.AddValidator" )
    TInt result( KErrNone );
    if ( !aValidator.ValidatesContext( iContextType ) )
        {
        result = KErrNotSupported;
        }
    else
        {
        result = iValidators.InsertInOrderAllowRepeats( &aValidator,
            TLinearOrder< CVtUiCmdValidatorBase >( ::ValidatorPriCmpFunc ) );
        }
    __VTPRINTEXITR( "CmdCtx.AddValidator %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::RemoveValidator
// ---------------------------------------------------------------------------
//
void CVtUiCmdContext::RemoveValidator( const CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdCtx.RemoveValidator" )
    TInt idx( iValidators.FindInOrder( &aValidator,
        TLinearOrder< CVtUiCmdValidatorBase >( ::ValidatorPriCmpFunc ) ) );

    if ( idx != KErrNotFound )
        {
        iValidators.Remove( idx );
        }
    __VTPRINTEXIT( "CmdCtx.RemoveValidator" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::CVtUiCmdContext
// ---------------------------------------------------------------------------
//
CVtUiCmdContext::CVtUiCmdContext( MVtUiCommandManager& aCommandManager,
    TVtUiCmdContextType aCtxType, TInt aReferencePriority )
    : iCommandManager( aCommandManager ),
      iReferencePriority( aReferencePriority ), iContextType( aCtxType )
    {
    __VTPRINTENTER( "CmdCtx.ctor" )
    __VTPRINTEXIT( "CmdCtx.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::ValidateMenuItemsL
// ---------------------------------------------------------------------------
//
void CVtUiCmdContext::ValidateMenuItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdCtx.ValidateMenuItemsL" )
    __VTPRINT2( DEBUG_GEN, "    count = %d", iValidators.Count() )
    for ( TInt i = iValidators.Count() - 1; i >= 0; i-- )
        {
        iValidators[ i ]->ValidateMenuItemsL( aAction, iReferencePriority );
        }
    __VTPRINTEXIT( "CmdCtx.ValidateMenuItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::ValidateSoftkeyItemsL
// ---------------------------------------------------------------------------
//
void CVtUiCmdContext::ValidateSoftkeyItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdCtx.ValidateSoftkeyItemsL" )
    __VTPRINT2( DEBUG_GEN, "    count = %d", iValidators.Count() )
    for ( TInt i = iValidators.Count() - 1; i >= 0; i-- )
        {
        iValidators[ i ]->ValidateSoftkeyItemsL( aAction, iReferencePriority );
        }
    __VTPRINTEXIT( "CmdCtx.ValidateSoftkeyItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::ValidateToolbarItemsL
// ---------------------------------------------------------------------------
//
void CVtUiCmdContext::ValidateToolbarItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdCtx.ValidateToolbarItemsL" )
    __VTPRINT2( DEBUG_GEN, "    count = %d", iValidators.Count() )
    for ( TInt i = iValidators.Count() - 1; i >= 0; i-- )
        {
        iValidators[ i ]->ValidateToolbarItemsL( aAction, iReferencePriority );
        }
    __VTPRINTEXIT( "CmdCtx.ValidateToolbarItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::CustomValidationL
// ---------------------------------------------------------------------------
//
void CVtUiCmdContext::CustomValidationL(
    CVtUiCmdCustomValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdCtx.CustomValidationL" )
    __VTPRINT2( DEBUG_GEN, "    count = %d", iValidators.Count() )
    for ( TInt i = iValidators.Count() - 1; i >= 0; i-- )
        {
        iValidators[ i ]->CustomValidationL( aAction, iReferencePriority );
        }
    __VTPRINTEXIT( "CmdCtx.CustomValidationL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::RegisterCommandContextL
// ---------------------------------------------------------------------------
//
void CVtUiCmdContext::RegisterCommandContextL()
    {
    __VTPRINTENTER( "CmdCtx.RegisterCommandContextL" )
    User::LeaveIfError( iCommandManager.RegisterCommandContext( *this ) );
    __VTPRINTEXIT( "CmdCtx.RegisterCommandContextL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdContext::UnregisterCommandContext
// ---------------------------------------------------------------------------
//
void CVtUiCmdContext::UnregisterCommandContext()
    {
    __VTPRINTENTER( "CmdCtx.UnregisterCommandContext" )
    iCommandManager.UnregisterCommandContext( *this );
    __VTPRINTEXIT( "CmdCtx.UnregisterCommandContext" )
    }

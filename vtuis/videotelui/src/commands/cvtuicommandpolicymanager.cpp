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
* Description:  Command policy manager class.
*
*/


#include <cvtlogger.h>

#include "cvtuicommandpolicymanager.h"
#include "cvtuicmdcontext.h"
#include "cvtuicmdvalidatorbase.h"
#include "cvtuicmdvalidationactionbase.h"
#include "cvtuicmdcustomvalidationactionbase.h"
#include "cvtuiprimarycmdpolicy.h"
#include "cvtuicommandmanager.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// Used in InsertInOrder() method to compare two instances of CVtUiCmdContext.
// ---------------------------------------------------------------------------
//
TInt ContextTypeCmpFunc( const CVtUiCmdContext& aV1,
    const CVtUiCmdContext& aV2 )
    {
    return static_cast< TInt >( aV1.ContextType() ) -
        static_cast< TInt >( aV2.ContextType() );
    }

// ---------------------------------------------------------------------------
// Used in FindInOrder() method to compare instances of CVtUiCmdContext versus
// given key value.
// ---------------------------------------------------------------------------
//
TInt ContextTypeCmpFuncVsKey( const TVtUiCmdContextType* aKey,
    const CVtUiCmdContext& aValue )
    {
    return static_cast< TInt > ( *aKey ) -
        static_cast< TInt >( aValue.ContextType() );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::NewL
// ---------------------------------------------------------------------------
//
CVtUiCommandPolicyManager*
CVtUiCommandPolicyManager::NewL( const CVtUiCommandManager& aCmdManager )
    {
    CVtUiCommandPolicyManager* self =
        new ( ELeave ) CVtUiCommandPolicyManager( aCmdManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::~CVtUiCommandPolicyManager
// ---------------------------------------------------------------------------
//
CVtUiCommandPolicyManager::~CVtUiCommandPolicyManager()
    {
    __VTPRINTENTER( "CmdPolicyMgr.~" )
    iContexts.Reset();
    iValidators.Reset();
    delete iPrimaryCommandPolicy;
    __VTPRINTEXIT( "CmdPolicyMgr.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::RegisterCommandContext
// ---------------------------------------------------------------------------
//
TInt CVtUiCommandPolicyManager::RegisterCommandContext(
    CVtUiCmdContext& aContext )
    {
    __VTPRINTENTER( "CmdPolicyMgr.RegisterCommandContext" )
    TLinearOrder< CVtUiCmdContext > cmpFunc( ::ContextTypeCmpFunc );
    TInt result( KErrNone );
    TInt index( iContexts.FindInOrder( &aContext, cmpFunc ) );
    if ( index == KErrNotFound )
        {
        TInt error( iContexts.InsertInOrder( &aContext, cmpFunc ) );
        if ( !error )
            {
            CommandContextRegistered( aContext );
            }
        result = error;
        }
    else
        {
        result = KErrAlreadyExists;
        }
    __VTPRINTEXITR( "CmdPolicyMgr.RegisterCommandContext %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::UnregisterCommandContext
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::UnregisterCommandContext(
    CVtUiCmdContext& aContext )
    {
    __VTPRINTENTER( "CmdPolicyMgr.UnregisterCommandContext" )
    TLinearOrder< CVtUiCmdContext > cmpFunc( ::ContextTypeCmpFunc );
    TInt index( iContexts.FindInOrder( &aContext, cmpFunc ) );
    if ( index != KErrNotFound )
        {
        iContexts.Remove( index );
        CommandContextUnregistered( aContext );
        }
    __VTPRINTEXIT( "CmdPolicyMgr.UnregisterCommandContext" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::AddValidator
// ---------------------------------------------------------------------------
//
TInt CVtUiCommandPolicyManager::AddValidator(
    CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdPolicyMgr.AddValidator" )
    TInt error( iValidators.Append( &aValidator ) );
    if ( !error )
        {
        ValidatorAdded( aValidator );
        }
    __VTPRINTEXITR( "CmdPolicyMgr.AddValidator %d", error )
    return error;
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::RemoveValidator
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::RemoveValidator(
    CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdPolicyMgr.RemoveValidator" )
    TInt index( iValidators.Find( &aValidator ) );
    if ( index != KErrNotFound )
        {
        iValidators.Remove( index );
        ValidatorRemoved( aValidator );
        }
    __VTPRINTEXIT( "CmdPolicyMgr.RemoveValidator" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::ValidateMenuItemsL
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::ValidateMenuItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdPolicyMgr.ValidateMenuItemsL" )
    ValidateL( EVtUiCmdContextTypeMenu, aAction );
    __VTPRINTEXIT( "CmdPolicyMgr.ValidateMenuItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::ValidateSoftkeyItemsL
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::ValidateSoftkeyItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdPolicyMgr.ValidateSoftkeyItemsL" )
    ValidateL( EVtUiCmdContextTypeSoftkey, aAction );
    __VTPRINTEXIT( "CmdPolicyMgr.ValidateSoftkeyItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::ValidateToolbarItemsL
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::ValidateToolbarItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdPolicyMgr.ValidateToolbarItemsL" )
    ValidateL( EVtUiCmdContextTypeToolbar, aAction );
    __VTPRINTEXIT( "CmdPolicyMgr.ValidateToolbarItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::CustomValidateL
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::CustomValidateL(
    CVtUiCmdCustomValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdPolicyMgr.CustomValidateL" )
    ValidateL( EVtUiCmdContextTypeExecution, aAction );
    __VTPRINTEXIT( "CmdPolicyMgr.CustomValidateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::CVtUiCommandPolicyManager
// ---------------------------------------------------------------------------
//
CVtUiCommandPolicyManager::CVtUiCommandPolicyManager(
    const CVtUiCommandManager& aCmdManager ) : iCommandManager( aCmdManager )
    {
    __VTPRINTENTER( "CmdPolicyMgr.ctor" )
    __VTPRINTEXIT( "CmdPolicyMgr.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::ConstructL()
    {
    __VTPRINTENTER( "CmdPolicyMgr.ConstructL" )
    iPrimaryCommandPolicy =
        CVtUiPrimaryCmdPolicy::NewL( iCommandManager.UiStates(),
        iCommandManager.AppUi() );
    User::LeaveIfError( AddValidator( *iPrimaryCommandPolicy ) );
    __VTPRINTEXIT( "CmdPolicyMgr.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::CommandContextRegistered
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::CommandContextRegistered(
    CVtUiCmdContext& aContext )
    {
    __VTPRINTENTER( "CmdPolicyMgr.CommandContextRegistered" )
    for ( TInt i = iValidators.Count() - 1 ; i >= 0; i-- )
        {
        aContext.AddValidator( *iValidators[ i ] );
        }
    __VTPRINTEXIT( "CmdPolicyMgr.CommandContextRegistered" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::CommandContextUnregistered
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::CommandContextUnregistered(
    CVtUiCmdContext& aContext )
    {
    __VTPRINTENTER( "CmdPolicyMgr.CommandContextUnregistered" )
    for ( TInt i = iValidators.Count() - 1 ; i >= 0; i-- )
        {
        aContext.RemoveValidator( *iValidators[ i ] );
        }
    __VTPRINTEXIT( "CmdPolicyMgr.CommandContextUnregistered" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::ValidatorAdded
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::ValidatorAdded(
    CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdPolicyMgr.ValidatorAdded" )
    for ( TInt i = iContexts.Count() - 1 ; i >= 0; i-- )
        {
        iContexts[ i ]->AddValidator( aValidator );
        }
    __VTPRINTEXIT( "CmdPolicyMgr.ValidatorAdded" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::ValidatorRemoved
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::ValidatorRemoved(
    CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdPolicyMgr.ValidatorRemoved" )
    for ( TInt i = iContexts.Count() - 1 ; i >= 0; i-- )
        {
        iContexts[ i ]->RemoveValidator( aValidator );
        }
    __VTPRINTEXIT( "CmdPolicyMgr.ValidatorRemoved" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::FindCommandContextByType
// ---------------------------------------------------------------------------
//
CVtUiCmdContext* CVtUiCommandPolicyManager::FindCommandContextByType(
        TVtUiCmdContextType aContextType )
    {
    __VTPRINTENTER( "CmdPolicyMgr.FindCommandContextByType" )
    CVtUiCmdContext* result = NULL;
    TInt index( iContexts.FindInOrder( aContextType,
        ::ContextTypeCmpFuncVsKey ) );
    if ( index != KErrNotFound )
        {
        result = iContexts[ index ];
        }
    __VTPRINTEXIT( "CmdPolicyMgr.FindCommandContextByType" )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiCommandPolicyManager::ValidateL
// ---------------------------------------------------------------------------
//
void CVtUiCommandPolicyManager::ValidateL( TVtUiCmdContextType aContextType,
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdPolicyMgr.ValidateL" )
    CVtUiCmdContext* context =
        FindCommandContextByType( aContextType );
    if ( context )
        {
        aAction.BeginProcess();
        context->ValidateL( aAction );
        aAction.EndProcess();
        }
    __VTPRINTEXIT( "CmdPolicyMgr.ValidateL" )
    }


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
* Description:  Command manager class.
*
*/


#include <cvtlogger.h>

#include "cvtuicmdbase.h"
#include "cvtuicommandmanager.h"
#include "cvtuicommandpolicymanager.h"
#include "cvtuiprimarycmdpolicy.h"
#include "cvtuiexecutioncontext.h"
#include "cvtuimenuitemdimmeraction.h"
#include "tvtuistates.h"
#include "mvtuicommandui.h"
#include "cvtuicommandmodifybase.h"
#include "cvtuicmdstatecheckaction.h"

// Default array granularity.
static const TInt KVtUiArrayGranularity = 1;

// -----------------------------------------------------------------------------
// CVtUiCommandManager::NewL
// -----------------------------------------------------------------------------
//
CVtUiCommandManager* CVtUiCommandManager::NewL( const TVtUiStates& aUiStates,
    CVtUiAppUi& aAppUi )
    {
    __VTPRINTENTER( "CmdMgr.NewL" )
    CVtUiCommandManager* self = new ( ELeave ) CVtUiCommandManager( aUiStates,
        aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "CmdMgr.NewL" )
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::~CVtUiCommandManager
// -----------------------------------------------------------------------------
//
CVtUiCommandManager::~CVtUiCommandManager()
    {
    __VTPRINTENTER( "CmdMgr.~" )
    iCommands.Reset();
    iCommandUis.Reset();
    iCommandModifiers.Reset();
    delete iExecutionContext;
    delete iCmdStateCheckAction;
    delete iCmdPolicyMgr;
    __VTPRINTEXIT( "CmdMgr.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::UiStates
// -----------------------------------------------------------------------------
//
const TVtUiStates& CVtUiCommandManager::UiStates() const
    {
    return iUiStates;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::AppUi
// -----------------------------------------------------------------------------
//
const CVtUiAppUi& CVtUiCommandManager::AppUi() const
    {
    return iAppUi;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::VideoTelephonyVariation
// -----------------------------------------------------------------------------
//
const TVtUiVideoTelephonyVariation&
CVtUiCommandManager::VideoTelephonyVariation() const
    {
    return iVtVariation;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::HandleCommandL
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::HandleCommandL( TInt aCommandId )
    {
    TInt index( iCommands.FindInOrder( aCommandId, CVtUiCmdBase::KeyOrder() ) );
    if ( index != KErrNotFound )
        {
        iCommands[ index ]->HandleL();
        }
    /*

    This was commented out, because current CVtUiAppUi silently ignores
    commands that are not handled, changed this to emulate same kind of
    behaviour.

    else
        {
        User::Leave( KErrNotFound );
        }
    */
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::AddCommandUi
// -----------------------------------------------------------------------------
//
TInt CVtUiCommandManager::AddCommandUi( MVtUiCommandUi& aCommandUi )
    {
    __VTPRINTENTER( "CmdMgr.AddCommandUi" )
    TInt result( KErrAlreadyExists );
    TInt idx( iCommandUis.Find( &aCommandUi ) );
    if ( idx == KErrNotFound )
        {
        result = iCommandUis.Append( &aCommandUi );
        if ( result == KErrNone )
            {
            result = CommandUiAdded( aCommandUi );
            }
        }
    __VTPRINTEXITR( "CmdMgr.AddCommandUi %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::RemoveCommandUi
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::RemoveCommandUi( MVtUiCommandUi& aCommandUi )
    {
    __VTPRINTENTER( "CmdMgr.RemoveCommandUi" )
    TInt idx( iCommandUis.Find( &aCommandUi ) );
    if ( idx != KErrNotFound )
        {
        iCommandUis.Remove( idx );
        CommandUiRemoved( aCommandUi );
        }
    __VTPRINTEXIT( "CmdMgr.RemoveCommandUi" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::ValidateMenuItemsL
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::ValidateMenuItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdMgr.ValidateMenuItemsL" )
    iCmdPolicyMgr->ValidateMenuItemsL( aAction );
    __VTPRINTEXIT( "CmdMgr.ValidateMenuItemsL" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::ValidateSoftkeyItemsL
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::ValidateSoftkeyItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdMgr.ValidateSoftkeyItemsL" )
    iCmdPolicyMgr->ValidateSoftkeyItemsL( aAction );
    __VTPRINTEXIT( "CmdMgr.ValidateSoftkeyItemsL" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::ValidateToolbarItemsL
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::ValidateToolbarItemsL(
    CVtUiCmdValidationActionBase& aAction )
    {
    __VTPRINTENTER( "CmdMgr.ValidateToolbarItemsL" )
    iCmdPolicyMgr->ValidateToolbarItemsL( aAction );
    __VTPRINTEXIT( "CmdMgr.ValidateToolbarItemsL" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::IsCommandAllowedL
// -----------------------------------------------------------------------------
//
TBool CVtUiCommandManager::IsCommandAllowedL( TInt aCommandId )
    {
    __VTPRINTENTER( "CmdMgr.IsCommandAllowedL" )
    TInt index( iCommands.FindInOrder( aCommandId, CVtUiCmdBase::KeyOrder() ) );
    if ( index == KErrNotFound )
        {
        iCmdStateCheckAction->SetCommand( aCommandId );
        iCmdPolicyMgr->CustomValidateL( *iCmdStateCheckAction );
        }
    else
        {
        return iCommands[ index ]->IsEnabled();
        }
    __VTPRINTEXIT( "CmdMgr.IsCommandAllowedL" )
    return iCmdStateCheckAction->IsCommandAllowed();
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::RegisterCommandContext
// -----------------------------------------------------------------------------
//
TInt CVtUiCommandManager::RegisterCommandContext( CVtUiCmdContext& aContext )
    {
    __VTPRINTENTER( "CmdMgr.RegisterCommandContext" )
    TInt result( iCmdPolicyMgr->RegisterCommandContext( aContext ) );
    __VTPRINTEXITR( "CmdMgr.RegisterCommandContext %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::UnregisterCommandContext
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::UnregisterCommandContext( CVtUiCmdContext& aContext )
    {
    __VTPRINTENTER( "CmdMgr.UnregisterCommandContext" )
    iCmdPolicyMgr->UnregisterCommandContext( aContext );
    __VTPRINTEXIT( "CmdMgr.UnregisterCommandContext" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::AddValidator
// -----------------------------------------------------------------------------
//
TInt CVtUiCommandManager::AddValidator( CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdMgr.AddValidator" )
    TInt result( iCmdPolicyMgr->AddValidator( aValidator ) );
    __VTPRINTEXITR( "CmdMgr.AddValidator %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::RemoveValidator
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::RemoveValidator(
    CVtUiCmdValidatorBase& aValidator )
    {
    __VTPRINTENTER( "CmdMgr.RemoveValidator" )
    iCmdPolicyMgr->RemoveValidator( aValidator );
    __VTPRINTEXIT( "CmdMgr.RemoveValidator" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::RefreshL
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::RefreshL()
    {
    __VTPRINTENTER( "CmdMgr.RefreshL" )
    for ( TInt i = iCommandUis.Count() - 1; i >= 0; i-- )
        {
        iCommandUis[ i ]->RefreshL();
        }
    __VTPRINTEXIT( "CmdMgr.RefreshL" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::AddCommandModifier
// -----------------------------------------------------------------------------
//
TInt CVtUiCommandManager::AddCommandModifier(
    CVtUiCommandModifyBase& aModifier )
    {
    __VTPRINTENTER( "CmdMgr.AddCommandModifier" )
    TInt result(
        iCommandModifiers.InsertInOrder( &aModifier,
            CVtUiCommandModifyBase::PriorityOrder() ) );
    if ( result == KErrNone )
        {
        result = CommandModifierAdded( aModifier );
        }
    __VTPRINTEXITR( "CmdMgr.AddCommandModifier %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::RemoveCommandModifier
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::RemoveCommandModifier(
    CVtUiCommandModifyBase& aModifier )
    {
    __VTPRINTENTER( "CmdMgr.RemoveCommandModifier" )
    TInt idx( iCommandModifiers.FindInOrder( &aModifier,
        CVtUiCommandModifyBase::PriorityOrder() ) );
    if ( idx != KErrNotFound )
        {
        iCommandModifiers.Remove( idx );
        CommandModifierRemoved( aModifier );
        }
    __VTPRINTEXIT( "CmdMgr.RemoveCommandModifier" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::RegisterCommandL
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::RegisterCommandL( CVtUiCmdBase& aCommand )
    {
    __VTPRINTENTER( "CmdMgr.RegisterCommandL" )
    iCommands.InsertInOrderL( &aCommand, CVtUiCmdBase::LinearOrder() );
    __VTPRINTEXIT( "CmdMgr.RegisterCommandL" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::UnregisterCommand
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::UnregisterCommand( const CVtUiCmdBase& aCommand )
    {
    __VTPRINTENTER( "CmdMgr.UnregisterCommand" )
    TInt index( iCommands.FindInOrder( &aCommand,
        CVtUiCmdBase::LinearOrder() ) );
    if ( index != KErrNotFound )
        {
        iCommands.Remove( index );
        }
    __VTPRINTEXIT( "CmdMgr.UnregisterCommand" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::CVtUiCommandManager
// -----------------------------------------------------------------------------
//
CVtUiCommandManager::CVtUiCommandManager( const TVtUiStates& aUiStates, 
    CVtUiAppUi& aAppUi )
: iCommandUis( KVtUiArrayGranularity ),
  iCommandModifiers( KVtUiArrayGranularity ),
  iCommands( KVtUiArrayGranularity ),
  iUiStates( aUiStates ),
  iAppUi( aAppUi )
    {
    __VTPRINTENTER( "CmdMgr.ctor" )
    __VTPRINTEXIT( "CmdMgr.ctor" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::ConstructL()
    {
    __VTPRINTENTER( "CmdMgr.ConstructL" )
    iVtVariation.ReadL();
    iCmdPolicyMgr = CVtUiCommandPolicyManager::NewL( *this );
    iCmdStateCheckAction = CVtUiCmdStateCheckAction::NewL();
    iExecutionContext = CVtUiExecutionContext::NewL( *this );
    __VTPRINTEXIT( "CmdMgr.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::CommandModifierAdded
// -----------------------------------------------------------------------------
//
TInt CVtUiCommandManager::CommandModifierAdded(
    CVtUiCommandModifyBase& aModifier )
    {
    TInt error( KErrNone );
    for ( TInt i = iCommandUis.Count() - 1; !error && i >= 0; i-- )
        {
        error = iCommandUis[ i ]->AddCommandModifier( aModifier );
        }
    return error;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::CommandModifierRemoved
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::CommandModifierRemoved(
    CVtUiCommandModifyBase& aModifier )
    {
    for ( TInt i = iCommandUis.Count() - 1; i >= 0; i-- )
        {
        iCommandUis[ i ]->RemoveCommandModifier( aModifier );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::CommandUiAdded
// -----------------------------------------------------------------------------
//
TInt CVtUiCommandManager::CommandUiAdded( MVtUiCommandUi& aCommandUi )
    {
    TInt error( KErrNone );
    for ( TInt i = iCommandModifiers.Count() - 1; !error && i >= 0; i-- )
        {
        error = aCommandUi.AddCommandModifier( *iCommandModifiers[ i ] );
        }
    return error;
    }

// -----------------------------------------------------------------------------
// CVtUiCommandManager::CommandUiRemoved
// -----------------------------------------------------------------------------
//
void CVtUiCommandManager::CommandUiRemoved( MVtUiCommandUi& aCommandUi )
    {
    for ( TInt i = iCommandModifiers.Count() - 1; i >= 0; i-- )
        {
        aCommandUi.RemoveCommandModifier( *iCommandModifiers[ i ] );
        }
    }

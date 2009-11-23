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
* Description:  Toolbar command policy implementation.
*
*/


#include <cvtlogger.h>

#include "cvtuitoolbarcmdpolicy.h"
#include "cvtuicmdvalidationactionbase.h"
#include "tvtuicmdvalidatorcallback.h"
#include "cvtuitoolbarbase.h"
#include "videotelui.hrh"

// ======== LOCAL FUNCTIONS ========

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::NewL
// ---------------------------------------------------------------------------
//
CVtUiToolbarCmdPolicy* CVtUiToolbarCmdPolicy::NewL( CVtUiToolbarBase& aToolbar )
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.NewL" )
    CVtUiToolbarCmdPolicy* self = new ( ELeave ) CVtUiToolbarCmdPolicy(
        aToolbar );
    __VTPRINTEXIT( "ToolbarCmdPolicy.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::ValidateMenuItemsL
// ---------------------------------------------------------------------------
//
void CVtUiToolbarCmdPolicy::ValidateMenuItemsL(
    CVtUiCmdValidationActionBase& aAction, TInt /*aReferencePriority*/ )
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.ValidateMenuItemsL" )
    aAction.ProcessL(
        TVtUiCmdValidatorCallBack< CVtUiToolbarCmdPolicy >( *this,
            ValidateMenuCommand ) );
    __VTPRINTEXIT( "ToolbarCmdPolicy.ValidateMenuItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::ValidateSoftkeyItemsL
// ---------------------------------------------------------------------------
//
void CVtUiToolbarCmdPolicy::ValidateSoftkeyItemsL(
    CVtUiCmdValidationActionBase& /*aAction*/, TInt /*aReferencePriority*/ )
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.ValidateSoftkeyItemsL" )
    __VTPRINTEXIT( "ToolbarCmdPolicy.ValidateSoftkeyItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::ValidateToolbarItemsL
// ---------------------------------------------------------------------------
//
void CVtUiToolbarCmdPolicy::ValidateToolbarItemsL(
    CVtUiCmdValidationActionBase& /*aAction*/, TInt /*aReferencePriority*/ )
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.ValidateToolbarItemsL" )
    __VTPRINTEXIT( "ToolbarCmdPolicy.ValidateToolbarItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::CustomValidationL
// ---------------------------------------------------------------------------
//
void CVtUiToolbarCmdPolicy::CustomValidationL(
    CVtUiCmdCustomValidationActionBase&, TInt )
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.CustomValidationL" )
    __VTPRINTEXIT( "ToolbarCmdPolicy.CustomValidationL" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::ValidatesContext
// ---------------------------------------------------------------------------
//
TBool CVtUiToolbarCmdPolicy::ValidatesContext(
    const TVtUiCmdContextType& aCtxType ) const
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.ValidatesContext" )

    TBool result( EFalse );

    switch ( aCtxType )
        {
    case EVtUiCmdContextTypeMenu:
    case EVtUiCmdContextTypeSoftkey:
    case EVtUiCmdContextTypeToolbar:
        result = ETrue;
        break;

    default:
        break;
        }

    __VTPRINTEXITR( "ToolbarCmdPolicy.ValidatesContext %d", result )

    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::CVtUiToolbarCmdPolicy
// ---------------------------------------------------------------------------
//
CVtUiToolbarCmdPolicy::CVtUiToolbarCmdPolicy( CVtUiToolbarBase& aToolbar )
    : CVtUiCmdValidatorBase( EVtUiCmdPolicyPriorityToolbar ),
      iToolbar( aToolbar )
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.ctor" )
    __VTPRINTEXIT( "ToolbarCmdPolicy.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarCmdPolicy::ValidateMenuCommand
// ---------------------------------------------------------------------------
//
TBool CVtUiToolbarCmdPolicy::ValidateMenuCommand( TInt /*aCommandId*/ ) const
    {
    __VTPRINTENTER( "ToolbarCmdPolicy.ValidateMenuCommand" )
    // all commands are also in options menu
    __VTPRINTEXIT( "ToolbarCmdPolicy.ValidateMenuCommand")
    return EFalse;
    }


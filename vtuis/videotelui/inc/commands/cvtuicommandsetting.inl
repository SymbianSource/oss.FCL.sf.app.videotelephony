/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Command setting inline methods.
*
*/


#include <cvtlogger.h>

#include "cvtuicommandmodifybase.h"

// ======== LOCAL FUNCTIONS ========

static const TInt KVtUiModifierArrayGranularity = 1;

// ---------------------------------------------------------------------------
// CVtUiCommandSetting< A >::~CVtUiCommandSetting
// ---------------------------------------------------------------------------
//
template < typename A >
CVtUiCommandSetting< A >::~CVtUiCommandSetting()
    {
    iModifiers.Reset();
    }

// ---------------------------------------------------------------------------
// CVtUiCommandSetting< A >::CVtUiCommandSetting
// ---------------------------------------------------------------------------
//
template < typename A >
CVtUiCommandSetting< A >::CVtUiCommandSetting( Type aCommandType ) :
    iModifiers( KVtUiModifierArrayGranularity ), iCommandType( aCommandType )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiCommandSetting< A >::DefineCommandsL
// ---------------------------------------------------------------------------
//
template < typename A >
void CVtUiCommandSetting< A >::DefineCommandsL( const A& aAction )
    {
    __VTPRINTENTER( "CmdSet< A >.DefineCommandsL" )
    iAction = &aAction;
    if ( iModifiers.Count() > 0 )
        {
        iModifiers[ iModifiers.Count() - 1 ]->ModifyCommandsL( *this );
        }
    else
        {
        DoDefineCommandsL();
        }
    iAction = NULL;
    __VTPRINTEXIT( "CmdSet< A >.DefineCommandsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandSetting< A >::AddModifier
// ---------------------------------------------------------------------------
//
template < typename A >
TInt CVtUiCommandSetting< A >::AddModifier(
    CVtUiCommandModifyBase& aModifier )
    {
    __VTPRINTENTER( "CmdSet< A >.AddModifier" )
    TInt result( KErrNone );
    if ( aModifier.Supports( iCommandType ) )
        {
        TInt idx( iModifiers.FindInOrder( &aModifier,
            CVtUiCommandModifyBase::PriorityOrder() ) );
        if ( idx == KErrNotFound )
            {
            result = iModifiers.InsertInOrder( &aModifier,
                CVtUiCommandModifyBase::PriorityOrder() );
            }
        else
            {
            if ( iModifiers[ idx ] != &aModifier )
                {
                // Priorities match, but instance is not same -> argument
                // is not valid
                result = KErrArgument;
                }
            }
        }
    __VTPRINTEXITR( "CmdSet< A >.AddModifier %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiCommandSetting< A >::RemoveModifier
// ---------------------------------------------------------------------------
//
template < typename A >
void CVtUiCommandSetting< A >::RemoveModifier(
    CVtUiCommandModifyBase& aModifier )
    {
    __VTPRINTENTER( "CmdSet< A >.RemoveModifier" )
    TInt idx( iModifiers.FindInOrder( &aModifier,
        CVtUiCommandModifyBase::PriorityOrder() ) );

    if ( idx != KErrNotFound )
        {
        iModifiers.Remove( idx );
        }
    __VTPRINTEXIT( "CmdSet< A >.RemoveModifier" )
    }

// ---------------------------------------------------------------------------
// CVtUiCommandSetting< A >::CommandType
// ---------------------------------------------------------------------------
//
template < typename A >
MVtUiCommandSetting::Type CVtUiCommandSetting< A >::CommandType() const
    {
    return iCommandType;
    }

// ---------------------------------------------------------------------------
// CVtUiCommandSetting< A >::Action
// ---------------------------------------------------------------------------
//
template < typename A >
const A& CVtUiCommandSetting< A >::Action()
    {
    return *iAction;
    }


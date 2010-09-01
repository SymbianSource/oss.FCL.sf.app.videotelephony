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
* Description:  Command validation action base class.
*
*/


#include <cvtlogger.h>

#include "cvtuicmdvalidationactionbase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiCmdValidationActionBase::~CVtUiCmdValidationActionBase
// ---------------------------------------------------------------------------
//
CVtUiCmdValidationActionBase::~CVtUiCmdValidationActionBase()
    {
    __VTPRINTENTER( "ValActBase.~" )
    iHandledCommands.Reset();
    __VTPRINTEXIT( "ValActBase.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdValidationActionBase::BeginProcess
// ---------------------------------------------------------------------------
//
void CVtUiCmdValidationActionBase::BeginProcess()
    {
    __VTPRINTENTER( "ValActBase.BeginProcess" )
    iHandledCommands.Reset();
    __VTPRINTEXIT( "ValActBase.BeginProcess" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdValidationActionBase::EndProcess
// ---------------------------------------------------------------------------
//
void CVtUiCmdValidationActionBase::EndProcess()
    {
    __VTPRINTENTER( "ValActBase.EndProcess" )
    __VTPRINTEXIT( "ValActBase.EndProcess" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdValidationActionBase::CommandHandledL
// ---------------------------------------------------------------------------
//
void CVtUiCmdValidationActionBase::CommandHandledL( TInt aCommandId )
    {
    __VTPRINTENTER( "ValActBase.CommandHandledL" )
    __VTPRINT2( DEBUG_GEN, "    cmdId = %d", aCommandId );
    User::LeaveIfError( iHandledCommands.InsertInOrder( aCommandId ) );
    __VTPRINTEXIT( "ValActBase.CommandHandledL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdValidationActionBase::IsCommandHandled
// ---------------------------------------------------------------------------
//
TBool CVtUiCmdValidationActionBase::IsCommandHandled( TInt aCommandId ) const
    {
    __VTPRINTENTER( "ValActBase.IsCommandHandled" )
    TBool result( iHandledCommands.FindInOrder( aCommandId ) != KErrNotFound );
    __VTPRINTEXITR( "ValActBase.IsCommandHandled %d", result )
    return result;
    }

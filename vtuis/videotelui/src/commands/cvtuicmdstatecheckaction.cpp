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
* Description:  Menu item dimmer action class.
*
*/


#include <cvtlogger.h>

#include "cvtuicmdstatecheckaction.h"
#include "tvtuicmdvalidatorcallback.h"
#include "tvtuicmdcontexttype.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiCmdStateCheckAction::NewL
// ---------------------------------------------------------------------------
//
CVtUiCmdStateCheckAction* CVtUiCmdStateCheckAction::NewL()
    {
    __VTPRINTENTER( "CmdStChkAct.NewL" )
    CVtUiCmdStateCheckAction* self =
        new ( ELeave ) CVtUiCmdStateCheckAction();
    __VTPRINTEXIT( "CmdStChkAct.NewL" )
    return self;
	}

// ---------------------------------------------------------------------------
// CVtUiCmdStateCheckAction::SetCommand
// ---------------------------------------------------------------------------
//
void CVtUiCmdStateCheckAction::SetCommand( TInt aCommandId )
    {
    __VTPRINTENTER( "CmdStChkAct.SetCommand" )
    iCommandId = aCommandId;
    iIsCommandAllowed = EFalse;
    __VTPRINTEXIT( "CmdStChkAct.SetCommand" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdStateCheckAction::IsCommandAllowed
// ---------------------------------------------------------------------------
//
TBool CVtUiCmdStateCheckAction::IsCommandAllowed() const
    {
    return iIsCommandAllowed;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdStateCheckAction::ProcessL
// ---------------------------------------------------------------------------
//
void CVtUiCmdStateCheckAction::ProcessL(
    const MVtUiCmdValidatorCallBack& aCallBack )
    {
    __VTPRINTENTER( "CmdStChkAct.ProcessL" )
	if ( !IsCommandHandled( iCommandId ) )
	    {
        if ( aCallBack.Call( iCommandId ) )
            {
    	    CommandHandledL( iCommandId );
    	    iIsCommandAllowed = ETrue;
            }
	    }
    __VTPRINTEXIT( "CmdStChkAct.ProcessL" )
	}

// ---------------------------------------------------------------------------
// CVtUiCmdStateCheckAction::CVtUiCmdStateCheckAction
// ---------------------------------------------------------------------------
//
CVtUiCmdStateCheckAction::CVtUiCmdStateCheckAction()
    : CVtUiCmdCustomValidationActionBase( EVtUiCmdContextTypeExecution )
    {
    __VTPRINTENTER( "CmdStChkAct.ctor" )
    __VTPRINTEXIT( "CmdStChkAct.ctor" )
    }

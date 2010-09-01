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
#include <eikmenup.h>

#include "cvtuimenuitemdimmeraction.h"
#include "tvtuicmdvalidatorcallback.h"
#include "tvtuimenucommanditerator.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiMenuItemDimmerAction::NewL
// ---------------------------------------------------------------------------
//
CVtUiMenuItemDimmerAction* CVtUiMenuItemDimmerAction::NewL()
    {
    __VTPRINTENTER( "MenuDimAct.NewL" )
    CVtUiMenuItemDimmerAction* self =
        new ( ELeave ) CVtUiMenuItemDimmerAction();
    __VTPRINTEXIT( "MenuDimAct.NewL" )
    return self;
	}

// ---------------------------------------------------------------------------
// CVtUiMenuItemDimmerAction::SetMenuPane
// ---------------------------------------------------------------------------
//
void CVtUiMenuItemDimmerAction::SetMenuPane( CEikMenuPane* aMenuPane )
    {
    __VTPRINTENTER( "MenuDimAct.SetMenuPane" )
    iMenuPane = aMenuPane;
    __VTPRINTEXIT( "MenuDimAct.SetMenuPane" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenuItemDimmerAction::ProcessL
// ---------------------------------------------------------------------------
//
void CVtUiMenuItemDimmerAction::ProcessL(
    const MVtUiCmdValidatorCallBack& aCallBack )
    {
    __VTPRINTENTER( "MenuDimAct.ProcessL" )

    if ( iMenuPane )
        {
        for ( TVtUiMenuCommandIterator i( *iMenuPane ); i.HasNext(); )
            {
            TInt commandId( i.Next() );
        	if ( !IsCommandHandled( commandId ) )
        	    {
                if ( aCallBack.Call( commandId ) )
                    {
            	    CommandHandledL( commandId );
            	    SetItemDimmed( commandId );
                    }
        	    }
            }
        }
    __VTPRINTEXIT( "MenuDimAct.ProcessL" )
	}

// ---------------------------------------------------------------------------
// CVtUiMenuItemDimmerAction::EndProcess
// ---------------------------------------------------------------------------
//
void CVtUiMenuItemDimmerAction::EndProcess()
    {
    __VTPRINTENTER( "MenuDimAct.EndProcess" )
    iMenuPane = NULL;
    __VTPRINTEXIT( "MenuDimAct.EndProcess" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenuItemDimmerAction::CVtUiMenuItemDimmerAction
// ---------------------------------------------------------------------------
//
CVtUiMenuItemDimmerAction::CVtUiMenuItemDimmerAction()
    {
    __VTPRINTENTER( "MenuDimAct.ctor" )
    __VTPRINTEXIT( "MenuDimAct.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenuItemDimmerAction::SetItemDimmed
// ---------------------------------------------------------------------------
//
void CVtUiMenuItemDimmerAction::SetItemDimmed( TInt aCommandId )
    {
    __VTPRINTENTER( "MenuDimAct.SetItemDimmed" )
    iMenuPane->SetItemDimmed( aCommandId, ETrue );
    __VTPRINTEXIT( "MenuDimAct.SetItemDimmed" )
    }


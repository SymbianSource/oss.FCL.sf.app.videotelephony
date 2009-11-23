/*
* Copyright (c) 2006 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Mennu Ui feature class.
*
*/


#include <cvtlogger.h>

#include "cvtuimenus.h"
#include "cvtuimenucontext.h"
#include "cvtuimenuitemdimmeraction.h"
#include "cvtuifeaturemanager.h"
#include "cvtuicommandmanager.h"

// ---------------------------------------------------------------------------
// CVtUiMenus::NewL
// ---------------------------------------------------------------------------
//
CVtUiMenus* CVtUiMenus::NewL( CVtUiFeatureManager& aFeatureManager )
    {
    __VTPRINTENTER( "Menus.NewL" )
    CVtUiMenus* self = new ( ELeave ) CVtUiMenus( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "Menus.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::~CVtUiMenus
// ---------------------------------------------------------------------------
//
CVtUiMenus::~CVtUiMenus()
    {
    __VTPRINTENTER( "Menus.~" )    
    delete iMenuCommandContext;
    delete iMenuDimmerAction;
    __VTPRINTEXIT( "Menus.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::SetMenuPane
// ---------------------------------------------------------------------------
//
void CVtUiMenus::SetMenuPane( CEikMenuPane* aMenuPane )
    {
    __VTPRINTENTER( "Menus.SetMenuPane" )
    iMenuDimmerAction->SetMenuPane( aMenuPane );
    __VTPRINTEXIT( "Menus.SetMenuPane" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::StartL
// ---------------------------------------------------------------------------
//
void CVtUiMenus::StartL()
    {
    __VTPRINTENTER( "Menus.StartL" )
    __VTPRINTEXIT( "Menus.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::Stop
// ---------------------------------------------------------------------------
//
void CVtUiMenus::Stop()
    {
    __VTPRINTENTER( "Menus.Stop" )
    __VTPRINTEXIT( "Menus.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiMenus::InitFeatureL()
    {
    __VTPRINTENTER( "Menus.InitFeatureL" )
    __VTPRINTEXIT( "Menus.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::RefreshL
// ---------------------------------------------------------------------------
//
void CVtUiMenus::RefreshL()
    {
    __VTPRINTENTER( "Menus.RefreshL" )
    iFeatureManager.CommandManager().ValidateMenuItemsL( *iMenuDimmerAction );
    __VTPRINTEXIT( "Menus.RefreshL" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::AddCommandModifier
// ---------------------------------------------------------------------------
//
TInt CVtUiMenus::AddCommandModifier( CVtUiCommandModifyBase& )
    {
    __VTPRINTENTER( "Menus.AddCommandModifier" )
    __VTPRINTEXIT( "Menus.AddCommandModifier" )
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::RemoveCommandModifier
// ---------------------------------------------------------------------------
//
void CVtUiMenus::RemoveCommandModifier( CVtUiCommandModifyBase& )
    {
    __VTPRINTENTER( "Menus.RemoveCommandModifier" )
    __VTPRINTEXIT( "Menus.RemoveCommandModifier" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::CVtUiMenus
// ---------------------------------------------------------------------------
//
CVtUiMenus::CVtUiMenus( CVtUiFeatureManager& aFeatureManager )
    : CVtUiFeatureBase( EVtUiFeatureIdMenu, aFeatureManager )
    {
    __VTPRINTENTER( "Menus.ctor" )
    __VTPRINTEXIT( "Menus.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiMenus::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiMenus::ConstructL()
    {
    __VTPRINTENTER( "Menus.ConstructL" )
    iMenuCommandContext =
        CVtUiMenuContext::NewL( iFeatureManager.CommandManager() );
    iMenuDimmerAction = CVtUiMenuItemDimmerAction::NewL();
    
    // No need to add this to command manager as command UI. Menu is explicitly
    // updated by CVtUiAppUi::DynInitMenuPaneL and in all other situations
    // update is not needed because menu is not open. 
    // NOTE: If a command modifier is implemented for menu then it needs
    // to be added to command UI.
    __VTPRINTEXIT( "Menus.ConstructL" )
    }


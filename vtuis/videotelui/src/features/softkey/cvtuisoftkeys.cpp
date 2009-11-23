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
* Description:  Softkey UI feature implementation.
*
*/


#include <cvtlogger.h>
#include <eikbtgpc.h>
#include "cvtuisoftkeys.h"
#include "cvtuisoftkeysetting.h"
#include "cvtuisoftkeyvalidationaction.h"
#include "cvtuifeaturemanager.h"
#include "mvtuicommandmanager.h"
#include "cvtuisoftkeycontext.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::NewL
// ---------------------------------------------------------------------------
//
CVtUiSoftkeys* CVtUiSoftkeys::NewL( CVtUiFeatureManager& aFeatureManager,
    CEikButtonGroupContainer& aButtonGroupContainer )
    {
    __VTPRINTENTER( "SKs.NewL" )
    CVtUiSoftkeys* self =
        new ( ELeave ) CVtUiSoftkeys( aFeatureManager, aButtonGroupContainer );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "SKs.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::~CVtUiSoftkeys
// ---------------------------------------------------------------------------
//
CVtUiSoftkeys::~CVtUiSoftkeys()
    {
    __VTPRINTENTER( "SKs.~" )
    iFeatureManager.CommandManager().RemoveCommandUi( *this );
    delete iSoftkeyCommandContext;
    delete iSoftkeySetting;
    delete iSoftkeyValidationAction;
    __VTPRINTEXIT( "SKs.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::ButtonGroup
// ---------------------------------------------------------------------------
//
CEikButtonGroupContainer& CVtUiSoftkeys::ButtonGroup()
    {
    __VTPRINTENTER( "SKs.ButtonGroup" )
    __VTPRINTEXIT( "SKs.ButtonGroup" )
    return iButtonGroupContainer;
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::StartL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeys::StartL()
    {
    __VTPRINTENTER( "SKs.StartL" )
    __VTPRINTEXIT( "SKs.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::Stop
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeys::Stop()
    {
    __VTPRINTENTER( "SKs.Stop" )
    __VTPRINTEXIT( "SKs.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeys::InitFeatureL()
    {
    __VTPRINTENTER( "SKs.InitFeatureL" )
    __VTPRINTEXIT( "SKs.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::RefreshL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeys::RefreshL()
    {
    __VTPRINTENTER( "SKs.RefreshL" )
    iFeatureManager.CommandManager().ValidateSoftkeyItemsL(
        *iSoftkeyValidationAction );
    iSoftkeySetting->DefineCommandsL( *iSoftkeyValidationAction );
    iButtonGroupContainer.DrawNow();
    __VTPRINTEXIT( "SKs.RefreshL" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::AddCommandModifierL
// ---------------------------------------------------------------------------
//
TInt CVtUiSoftkeys::AddCommandModifier( CVtUiCommandModifyBase& aModifier )
    {
    __VTPRINTENTER( "SKs.AddCommandModifier" )
    TInt result( iSoftkeySetting->AddModifier( aModifier ) );
    __VTPRINTEXITR( "SKs.AddCommandModifier %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::RemoveCommandModifier
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeys::RemoveCommandModifier( CVtUiCommandModifyBase& aModifier )
    {
    __VTPRINTENTER( "SKs.RemoveCommandModifier" )
    iSoftkeySetting->RemoveModifier( aModifier );
    __VTPRINTEXIT( "SKs.RemoveCommandModifier" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::CVtUiSoftkeys
// ---------------------------------------------------------------------------
//
CVtUiSoftkeys::CVtUiSoftkeys( CVtUiFeatureManager& aFeatureManager,
    CEikButtonGroupContainer& aButtonGroupContainer )
    : CVtUiFeatureBase( EVtUiFeatureIdSoftkey, aFeatureManager ),
    iButtonGroupContainer( aButtonGroupContainer )
    {
    __VTPRINTENTER( "SKs.ctor" )
    __VTPRINTEXIT( "SKs.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeys::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeys::ConstructL()
    {
    __VTPRINTENTER( "SKs.ConstructL" )
    iSoftkeyCommandContext = CVtUiSoftkeyContext::NewL(
        iFeatureManager.CommandManager() );
    iSoftkeySetting = new ( ELeave ) CVtUiSoftkeySetting( *this );
    iSoftkeyValidationAction = CVtUiSoftkeyValidationAction::NewL();
    User::LeaveIfError(
        iFeatureManager.CommandManager().AddCommandUi( *this ) );
    __VTPRINTEXIT( "SKs.ConstructL" )
    }


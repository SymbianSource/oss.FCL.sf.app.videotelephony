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
* Description:  Softkey modifier class implementation.
*
*/


#include    <cvtlogger.h>
#include    "cvtuitoolbarskmodifier.h"
#include    "mvtuicommandsetting.h"
#include    "tvtuicommandmodifierpriority.h"
#include    "CVtUiAppUi.h"
#include    "tvtuistates.h"
#include    <eikbtgpc.h>
#include    <videotelui.rsg>


// ======== LOCAL FUNCTIONS ========

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiToolbarSKModifier::NewL
// ---------------------------------------------------------------------------
//
CVtUiToolbarSKModifier* CVtUiToolbarSKModifier::NewL( CVtUiAppUi& aAppUi,
    const TVtUiStates& aUiStates )
    {
    __VTPRINTENTER( "CVtUiToolbarSKModifier.NewL" )
    CVtUiToolbarSKModifier* self =
        new ( ELeave ) CVtUiToolbarSKModifier( aAppUi, aUiStates );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "CVtUiToolbarSKModifier.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarSKModifier::~CVtUiToolbarSKModifier
// ---------------------------------------------------------------------------
//
CVtUiToolbarSKModifier::~CVtUiToolbarSKModifier()
    {
    __VTPRINTENTER( "CVtUiToolbarSKModifier.~" )
    __VTPRINTEXIT( "CVtUiToolbarSKModifier.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarSKModifier::CVtUiToolbarSKModifier
// ---------------------------------------------------------------------------
//
CVtUiToolbarSKModifier::CVtUiToolbarSKModifier( CVtUiAppUi& aAppUi,
    const TVtUiStates& aUiStates ) :
    CVtUiCommandModifyBase ( EVtUiCmdModifierPriorityToolbar ),
    iAppUi ( aAppUi ), iUiStates ( aUiStates )
    {
    __VTPRINTENTER( "CVtUiToolbarSKModifier.Ctr" )
    __VTPRINTEXIT( "CVtUiToolbarSKModifier.Ctr" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarSKModifier::CVtUiToolbarSKModifier
// ---------------------------------------------------------------------------
//
void CVtUiToolbarSKModifier::ConstructL()
    {
    __VTPRINTENTER( "CVtUiToolbarSKModifier.ConstructL" )
    __VTPRINTEXIT( "CVtUiToolbarSKModifier.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarSKModifier::CVtUiToolbarSKModifier
// ---------------------------------------------------------------------------
//
void CVtUiToolbarSKModifier::ModifyCommandsL(
     MVtUiCommandSetting& aCommandSettings )
    {
    __VTPRINTENTER( "CVtUiToolbarSKModifier.ModifyCommandsL" )
    aCommandSettings.DoDefineCommandsL();

    // No need to change MSK during snapshot
    if ( iUiStates.IsCaptureModeOn() )
        {
        return;
        }

    CEikButtonGroupContainer* cba = iAppUi.GetCba();
    const TInt mskIndex = 3;
    // Set selection key to msk
    cba->SetCommandL( mskIndex, R_VIDEOTELUI_SELECT_CBA_BUTTON );
    __VTPRINTEXIT( "CVtUiToolbarSKModifier.ModifyCommandsL" )
    }
// ---------------------------------------------------------------------------
// CVtUiToolbarSKModifier::CVtUiToolbarSKModifier
// ---------------------------------------------------------------------------
//
TBool CVtUiToolbarSKModifier::Supports( MVtUiCommandSetting::Type aType ) const
    {
    __VTPRINTENTER( "CVtUiToolbarSKModifier.Supports" )
    __VTPRINTEXIT( "CVtUiToolbarSKModifier.Supports" )
    return ( aType == MVtUiCommandSetting::ECommandTypeSoftkeys );
    }

//  End of File

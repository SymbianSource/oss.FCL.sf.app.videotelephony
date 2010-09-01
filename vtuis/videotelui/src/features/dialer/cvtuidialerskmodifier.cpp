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
* Description:  Softkey modifier class.
*
*/


#include    <cvtlogger.h>
#include    "cvtuidialerskmodifier.h"
#include    "mvtuicommandsetting.h"
#include    "tvtuicommandmodifierpriority.h"
#include    "cvtuifeaturemanager.h"
#include    "tvtuistates.h"
#include    "tvtuifeatureids.h"
#include    "CVtUiAppUi.h"
#include    <eikbtgpc.h>
#include    <videotelui.rsg>


// ======== LOCAL FUNCTIONS ========

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiDialerSKModifier::NewL
// ---------------------------------------------------------------------------
//
CVtUiDialerSKModifier* CVtUiDialerSKModifier::NewL(
    CVtUiFeatureManager& aFeatureMgr )
    {
    __VTPRINTENTER( "CVtUiDialerSKModifier.NewL" )
    CVtUiDialerSKModifier* self =
        new ( ELeave ) CVtUiDialerSKModifier( aFeatureMgr );
    __VTPRINTEXIT( "CVtUiDialerSKModifier.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerSKModifier::~CVtUiDialerSKModifier
// ---------------------------------------------------------------------------
//
CVtUiDialerSKModifier::~CVtUiDialerSKModifier()
    {
    __VTPRINTENTER( "CVtUiDialerSKModifier.~" )
    __VTPRINTEXIT( "CVtUiDialerSKModifier.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerSKModifier::CVtUiDialerSKModifier
// ---------------------------------------------------------------------------
//
CVtUiDialerSKModifier::CVtUiDialerSKModifier(
    CVtUiFeatureManager& aFeatureMgr )
    : CVtUiCommandModifyBase( EVtUiCmdModifierPriorityNumberEntry ),
    iFeatureMgr( aFeatureMgr )
    {
    __VTPRINTENTER( "CVtUiDialerSKModifier.Ctr" )
    __VTPRINTEXIT( "CVtUiDialerSKModifier.Ctr" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerSKModifier::ModifyCommandsL
// ---------------------------------------------------------------------------
//
void CVtUiDialerSKModifier::ModifyCommandsL( MVtUiCommandSetting& )
    {
    __VTPRINTENTER( "CVtUiDialerSKModifier.ModifyCommandsL" )
    CEikButtonGroupContainer* cba = iFeatureMgr.AppUi().GetCba();
    cba->SetCommandSetL( R_VIDEOTELUI_SOFTKEYS_EMPTY_DIALEREXIT );
    __VTPRINTEXIT( "CVtUiDialerSKModifier.ModifyCommandsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerSKModifier::Supports
// ---------------------------------------------------------------------------
//
TBool CVtUiDialerSKModifier::Supports(
    MVtUiCommandSetting::Type aType ) const
    {
    __VTPRINTENTER( "CVtUiDialerSKModifier.Supports" )
    __VTPRINTEXIT( "CVtUiDialerSKModifier.Supports" )
    return ( aType == MVtUiCommandSetting::ECommandTypeSoftkeys );
    }

//  End of File

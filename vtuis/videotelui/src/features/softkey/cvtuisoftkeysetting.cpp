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
* Description:  Softkey setting implementation.
*
*/


#include <cvtlogger.h>
#include <eikbtgpc.h>

#include "cvtuisoftkeys.h"
#include "cvtuisoftkeysetting.h"
#include "cvtuisoftkeyvalidationaction.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiSoftkeySetting::~CVtUiSoftkeySetting
// ---------------------------------------------------------------------------
//
CVtUiSoftkeySetting::~CVtUiSoftkeySetting()
    {
    __VTPRINTENTER( "SKSet.~" )
    __VTPRINTEXIT( "SKSet.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeySetting::CVtUiSoftkeySetting
// ---------------------------------------------------------------------------
//
CVtUiSoftkeySetting::CVtUiSoftkeySetting( CVtUiSoftkeys& aSoftkeys ) :
    CVtUiCommandSetting( ECommandTypeSoftkeys ),
    iSoftkeys( &aSoftkeys )
    {
    __VTPRINTENTER( "SKSet.ctor" )
    __VTPRINTEXIT( "SKSet.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeySetting::DoDefineCommandsL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeySetting::DoDefineCommandsL()
    {
    __VTPRINTENTER( "SKSet.DoDefineCommandsL" )
    iSoftkeys->ButtonGroup().SetCommandSetL( Action().ResourceId() );
    __VTPRINTEXIT( "SKSet.DoDefineCommandsL" )
    }

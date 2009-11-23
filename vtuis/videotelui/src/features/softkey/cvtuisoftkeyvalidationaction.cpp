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
* Description:  Softkey validation action implementation.
*
*/


#include <cvtlogger.h>
#include <videotelui.rsg>
#include <avkon.rsg>

#include "cvtuisoftkeyvalidationaction.h"
#include "tvtuicmdvalidatorcallback.h"

// ======== MEMBER FUNCTIONS ========

// softkey ids
static const TInt SKIDS[] =
    {
    R_AVKON_SOFTKEYS_OPTIONS_BACK,
    R_VIDEOTELUI_SOFTKEYS_EMPTY_ACTIVE_COMMAND,
    R_VIDEOTELUI_SOFTKEYS_EMPTY_DIALEREXIT,
    R_VIDEOTELUI_SOFTKEYS_SHARE_OBJECT_IMAGE,
    R_VIDEOTELUI_SOFTKEYS_CAPTURE_VIDEO,
    R_VIDEOTELUI_SOFTKEYS_ENABLE_AUDIO,
    R_VIDEOTELUI_SOFTKEYS_ENABLE_VIDEO,
    R_VIDEOTELUI_SOFTKEYS_DIALER,
    R_VIDEOTELUI_SOFTKEYS_BT_HANDSFREE,
    R_VIDEOTELUI_SOFTKEYS_LOUDSPEAKER,
    R_VIDEOTELUI_SOFTKEYS_HANDSET_B,
    R_VIDEOTELUI_SOFTKEYS_END_CALL,
    R_AVKON_SOFTKEYS_EMPTY // this is end marker, keep it last
    };

// ---------------------------------------------------------------------------
// CVtUiSoftkeyValidationAction::NewL
// ---------------------------------------------------------------------------
//
CVtUiSoftkeyValidationAction* CVtUiSoftkeyValidationAction::NewL()
    {
    __VTPRINTENTER( "SKValAct.NewL" )
    CVtUiSoftkeyValidationAction* self =
        new ( ELeave ) CVtUiSoftkeyValidationAction();
    __VTPRINTEXIT( "SKValAct.NewL" )
    return self;
	}
// ---------------------------------------------------------------------------
// CVtUiSoftkeyValidationAction::BeginProcess
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeyValidationAction::BeginProcess()
    {
    __VTPRINTENTER( "SKValAct.EndProcess" )
    CVtUiCmdValidationActionBase::BeginProcess();
    iCurrentIdx = 0;
    __VTPRINTEXIT( "SKValAct.EndProcess" )
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeyValidationAction::ProcessL
// ---------------------------------------------------------------------------
//
void CVtUiSoftkeyValidationAction::ProcessL(
    const MVtUiCmdValidatorCallBack& aCallBack )
    {
    __VTPRINTENTER( "SKValAct.ProcessL" )
    while ( SKIDS[ iCurrentIdx ] != R_AVKON_SOFTKEYS_EMPTY )
        {
        if ( aCallBack.Call( SKIDS[ iCurrentIdx ] ) )
            {
            break;
            }
        else
            {
            iCurrentIdx++;
            }
        }
    __VTPRINTEXIT( "SKValAct.ProcessL" )
	}

// ---------------------------------------------------------------------------
// CVtUiSoftkeyValidationAction::ResourceId
// ---------------------------------------------------------------------------
//
TInt CVtUiSoftkeyValidationAction::ResourceId() const
    {
    __VTPRINTENTER( "SKValAct.ResourceId" )
    __VTPRINTEXITR( "SKValAct.ResourceId %d", SKIDS[ iCurrentIdx ] )
    return SKIDS[ iCurrentIdx ];
    }

// ---------------------------------------------------------------------------
// CVtUiSoftkeyValidationAction::CVtUiSoftkeyValidationAction
// ---------------------------------------------------------------------------
//
CVtUiSoftkeyValidationAction::CVtUiSoftkeyValidationAction()
    {
    __VTPRINTENTER( "SKValAct.ctor" )
    __VTPRINTEXIT( "SKValAct.ctor" )
    }


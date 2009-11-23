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
* Description:  Mini dialer open command implementation.
*
*/


#include <cvtlogger.h>

#include "cvtuicmdopendialer.h"
#include "mvtuicommandmanager.h"
#include "videotelui.hrh"

// ---------------------------------------------------------------------------
// CVtUiCmdOpenDialer::NewL
// ---------------------------------------------------------------------------
//
CVtUiCmdOpenDialer* CVtUiCmdOpenDialer::NewL(
    MVtUiCommandManager& aCommandManager, MVtUiFeature& aFeature )
    {
    __VTPRINTENTER( "CmdOpenDial.NewL" )
    CVtUiCmdOpenDialer* self =
        new ( ELeave ) CVtUiCmdOpenDialer( aCommandManager, aFeature );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "CmdOpenDial.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdOpenDialer::~CVtUiCmdOpenDialer
// ---------------------------------------------------------------------------
//
CVtUiCmdOpenDialer::~CVtUiCmdOpenDialer()
    {
    __VTPRINTENTER( "CmdOpenDial.~" )
    iCommandManager.UnregisterCommand( *this );
    __VTPRINTEXIT( "CmdOpenDial.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdOpenDialer::CVtUiCmdOpenDialer
// ---------------------------------------------------------------------------
//
CVtUiCmdOpenDialer::CVtUiCmdOpenDialer(
    MVtUiCommandManager& aCommandManager, MVtUiFeature& aFeature )
    : CVtUiFeatureCmdBase( aFeature, EVtUiCmdSendDTMF ),
      iCommandManager( aCommandManager )
    {
    __VTPRINTENTER( "CmdOpenDial.ctor" )
    __VTPRINTEXIT( "CmdOpenDial.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdOpenDialer::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiCmdOpenDialer::ConstructL()
    {
    __VTPRINTENTER( "CmdOpenDial.ConstructL" )
    iCommandManager.RegisterCommandL( *this );
    __VTPRINTEXIT( "CmdOpenDial.ConstructL" )
    }


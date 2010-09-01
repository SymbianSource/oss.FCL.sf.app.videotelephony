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

#include "cvtuicmdclosedialer.h"
#include "mvtuicommandmanager.h"
#include "mvtuifeature.h"
#include "videotelui.hrh"

// ---------------------------------------------------------------------------
// CVtUiCmdCloseDialer::NewL
// ---------------------------------------------------------------------------
//
CVtUiCmdCloseDialer* CVtUiCmdCloseDialer::NewL(
    MVtUiCommandManager& aCommandManager, MVtUiFeature& aFeature )
    {
    __VTPRINTENTER( "CmdCloseDial.NewL" )
    CVtUiCmdCloseDialer* self =
        new ( ELeave ) CVtUiCmdCloseDialer( aCommandManager, aFeature );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "CmdCloseDial.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdCloseDialer::~CVtUiCmdCloseDialer
// ---------------------------------------------------------------------------
//
CVtUiCmdCloseDialer::~CVtUiCmdCloseDialer()
    {
    __VTPRINTENTER( "CmdCloseDial.~" )
    iCommandManager.UnregisterCommand( *this );
    __VTPRINTEXIT( "CmdCloseDial.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdCloseDialer::HandleL
// ---------------------------------------------------------------------------
//
void CVtUiCmdCloseDialer::HandleL()
    {
    __VTPRINTENTER( "CmdCloseDial.HandleL" )
    iFeature.Stop();
    __VTPRINTEXIT( "CmdCloseDial.HandleL" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdCloseDialer::IsEnabled
// ---------------------------------------------------------------------------
//
TBool CVtUiCmdCloseDialer::IsEnabled() const
    {
    __VTPRINTENTER( "CmdCloseDial.IsEnabled" )
    const TBool enabled( iFeature.State() == MVtUiFeature::EActive );
    __VTPRINTEXITR( "CmdCloseDial.IsEnabled %d", enabled )
    return enabled;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdCloseDialer::CVtUiCmdCloseDialer
// ---------------------------------------------------------------------------
//
CVtUiCmdCloseDialer::CVtUiCmdCloseDialer(
    MVtUiCommandManager& aCommandManager, MVtUiFeature& aFeature )
    : CVtUiFeatureCmdBase( aFeature, EVtUiDialerExit ),
      iCommandManager( aCommandManager )
    {
    __VTPRINTENTER( "CmdCloseDial.ctor" )
    __VTPRINTEXIT( "CmdCloseDial.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiCmdCloseDialer::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiCmdCloseDialer::ConstructL()
    {
    __VTPRINTENTER( "CmdCloseDial.ConstructL" )
    iCommandManager.RegisterCommandL( *this );
    __VTPRINTEXIT( "CmdCloseDial.ConstructL" )
    }


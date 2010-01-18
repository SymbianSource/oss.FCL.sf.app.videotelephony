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
* Description:  Mini dialer feature
*
*/


#include <AknUtils.h>
#include <peninputcmdparam.h>
#include <cvtlogger.h>

#include "cvtuidialer.h"
#include "cvtuifeaturemanager.h"
#include "mvtuicommandmanager.h"
#include "mvtuicomponentmanager.h"
#include "cvtuicmdopendialer.h"
#include "cvtuicmdclosedialer.h"
#include "cvtuidialercontainer.h"
#include "cvtuidialervideocontrol.h"
#include "CVtUiAppUi.h"
#include "tvtuistates.h"
#include "CVtUiContextControl.h"

// ======== LOCAL FUNCTIONS ========

// Implementation of CVtUiDialer

// ---------------------------------------------------------------------------
// CVtUiDialer::NewL
// ---------------------------------------------------------------------------
//
CVtUiDialer* CVtUiDialer::NewL( CVtUiFeatureManager& aFeatureManager )
    {
    __VTPRINTENTER( "Dial.NewL" )
    CVtUiDialer* self = NULL;
    self = new ( ELeave ) CVtUiDialer( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "Dial.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::~CVtUiDialer
// ---------------------------------------------------------------------------
//
CVtUiDialer::~CVtUiDialer()
    {
    __VTPRINTENTER( "Dial.~" )
    delete iCmdOpen;
    delete iCmdClose;
    delete iDialerContainer;
    __VTPRINTEXIT( "Dial.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::VideoWindow
// ---------------------------------------------------------------------------
//
MVtUiVideoWindow& CVtUiDialer::VideoWindow() const
    {
    __VTPRINTENTER( "Dial.VideoWindow" )
    __VTPRINTEXIT( "Dial.VideoWindow" )
    return *iDialerContainer->ComponentAsVideoWindow();
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::VideoControl
// ---------------------------------------------------------------------------
//
CCoeControl& CVtUiDialer::VideoControl() const
    {
    __VTPRINTENTER( "Dial.VideoControl" )
    __VTPRINTEXIT( "Dial.VideoControl" )
    return *static_cast< MVtUiComponent* >
        ( iDialerContainer )->ComponentAsControl();
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::StartL
// ---------------------------------------------------------------------------
//
void CVtUiDialer::StartL()
    {
    __VTPRINTENTER( "Dial.StartL" )
    if ( State() == MVtUiFeature::EUnprepared )
        {
        // fixed toolbar is set to be hidden
        iFeatureManager.AppUi().ContextControl().MakeVisible( EFalse );
        iFeatureManager.UiStates().SetIsDialerActivating( ETrue );
        iFeatureManager.UiStates().SetIsFixedToolbarVisible( EFalse );
        iFeatureManager.CommandManager().RefreshL();
        PrepareL();
        iFeatureManager.ComponentManager().RequestActivationL(
            MVtUiComponent::EComponentIdDialer );
        iFeatureState = EActive;
        iFeatureManager.AppUi().SwitchLayoutToFlatStatusPaneL( ETrue );
        }
    __VTPRINTEXIT( "Dial.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::Stop
// ---------------------------------------------------------------------------
//
void CVtUiDialer::Stop()
    {
    __VTPRINTENTER( "Dial.Stop" )
    if ( State() == MVtUiFeature::EActive )
        {
        TInt error;
        TRAP( error,
            {
            iFeatureManager.AppUi().SwitchLayoutToFlatStatusPaneL( EFalse );
            iFeatureManager.ComponentManager().DeActivateComponentL(
                MVtUiComponent::EComponentIdDialer );
            } );
        Unprepare();
        iFeatureManager.AppUi().ContextControl().MakeVisible( ETrue );
        }
    __VTPRINTEXIT( "Dial.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiDialer::InitFeatureL()
    {
    __VTPRINTENTER( "Dial.InitFeatureL" )
    iDialerContainer =
        CVtUiDialerContainer::NewL( iFeatureManager );
    iCmdOpen = CVtUiCmdOpenDialer::NewL( iFeatureManager.CommandManager(),
        *this );
    iCmdClose = CVtUiCmdCloseDialer::NewL( iFeatureManager.CommandManager(),
        *this );
   __VTPRINTEXIT( "Dial.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::CVtUiDialer
// ---------------------------------------------------------------------------
//
CVtUiDialer::CVtUiDialer( CVtUiFeatureManager& aFeatureManager )
    : CVtUiFeatureBase( EVtUiFeatureIdDialer, aFeatureManager )
    {
    __VTPRINTENTER( "Dial.ctor" )
    __VTPRINTEXIT( "Dial.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiDialer::ConstructL()
    {
    __VTPRINTENTER( "Dial.ConstructL" )
    BaseConstructL();
    __VTPRINTEXIT( "Dial.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::PrepareL
// ---------------------------------------------------------------------------
//
void CVtUiDialer::PrepareL()
    {
    __VTPRINTENTER( "Dial.PrepareL" )
    iDialerContainer->RegisterComponentL();
    iFeatureState = EReady;
    __VTPRINTEXIT( "Dial.PrepareL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialer::Unprepare
// ---------------------------------------------------------------------------
//
void CVtUiDialer::Unprepare()
    {
    __VTPRINTENTER( "Dial.Unprepare" )
    iDialerContainer->UnregisterComponent();
    iFeatureState = EUnprepared;
    __VTPRINTEXIT( "Dial.Unprepare" )
    }

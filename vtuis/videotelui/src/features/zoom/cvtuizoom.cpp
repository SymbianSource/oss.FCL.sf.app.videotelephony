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
* Description:  Zoom feature implementation.
*
*/


#include <cvtlogger.h>
#include "cvtuizoom.h"
#include "tvtuifeatureids.h"
#include "cvtuizoompopup.h"
#include "cvtuifeaturemanager.h"
#include "tvtuistates.h"

// ---------------------------------------------------------------------------
// CVtUiZoom::NewL
// ---------------------------------------------------------------------------
//
CVtUiZoom* CVtUiZoom::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiZoom.NewL" )
    CVtUiZoom* self =
        new ( ELeave ) CVtUiZoom( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiZoom.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiZoom::~CVtUiZoom
// ---------------------------------------------------------------------------
//
CVtUiZoom::~CVtUiZoom()
    {
    __VTPRINTENTER( "CVtUiZoom.~" )
    __VTPRINTEXIT( "CVtUiZoom.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoom::RefreshL
// ---------------------------------------------------------------------------
//
void CVtUiZoom::RefreshL()
    {
    __VTPRINTENTER( "CVtUiZoom.RefreshL" )
    if ( State() == EActive )
        {
        static_cast< CVtUiZoomPopup& >( Popup() ).RefreshL();
        }
    __VTPRINTEXIT( "CVtUiZoom.RefreshL" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoom::StartL
// ---------------------------------------------------------------------------
//
void CVtUiZoom::StartL()
    {
    __VTPRINTENTER( "CVtUiZoom.StartL" )
    if ( State() == EActive )
        {
        // need to refresh when already active to replenish the close timer
        RefreshL();
        }
    else
        {
        iFeatureManager.UiStates().SetIsFloatingToolbarVisible( ETrue );
        CVtUiSliderBase::StartL();
        iFeatureManager.UiStates().SetZoomModeOn( ETrue );
        }
    __VTPRINTEXIT( "CVtUiZoom.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoom::Stop
// ---------------------------------------------------------------------------
//
void CVtUiZoom::Stop()
    {
    __VTPRINTENTER( "CVtUiZoom.Stop" )
    iFeatureManager.UiStates().SetZoomModeOn( EFalse );
    CVtUiSliderBase::Stop();
    __VTPRINTEXIT( "CVtUiZoom.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoom::ComponenStateChangedL()
// ---------------------------------------------------------------------------
//
void CVtUiZoom::ComponenStateChangedL()
    {
    __VTPRINTENTER( "CVtUiZoom.ComponenStateChangedL()" )
    // Close event received stop the feature
    // If this was a block event then do not stop the feature
    // Currently we can't separate block and stop events from component manager
    if ( !iFeatureManager.UiStates().IsCaptureModeOn() )
        {
       __VTPRINT( DEBUG_GEN, "CVtUiZoom.ComponenStateChangedL.Stop" )
        Stop();
        }
    __VTPRINTEXIT( "CVtUiZoom.ComponenStateChangedL()" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoom::CVtUiZoom
// ---------------------------------------------------------------------------
//
CVtUiZoom::CVtUiZoom( CVtUiFeatureManager& aFeatureManager )
    : CVtUiSliderBase( aFeatureManager, EVtUiFeatureIdZoom )
    {
    __VTPRINTENTER( "CVtUiZoom.CVtUiZoom" )
    __VTPRINTEXIT( "CVtUiZoom.CVtUiZoom" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoom::CVtUiZoom
// ---------------------------------------------------------------------------
//
void CVtUiZoom::ConstructL()
    {
    __VTPRINTENTER( "CVtUiZoom.ConstructL" )
    BaseConstructL();
    SetPopup( CVtUiZoomPopup::NewL( iFeatureManager ) );
    __VTPRINTEXIT( "CVtUiZoom.ConstructL" )
    }

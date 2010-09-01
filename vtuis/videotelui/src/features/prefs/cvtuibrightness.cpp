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
* Description:  implementation.
*
*/


#include    <cvtlogger.h>
#include    "cvtuibrightness.h"
#include    "tvtuifeatureids.h"
#include    "cvtuibrightnesspopup.h"
#include    "cvtuipopupbase.h"
#include    "cvtuiprefsliderbase.h"
#include    "videotelui.hrh"
#include    "cvtuifeaturemanager.h"
#include    "tvtuistates.h"

// ---------------------------------------------------------------------------
// CVtUiBrightness::NewL
// ---------------------------------------------------------------------------
//
CVtUiBrightness* CVtUiBrightness::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiBrightness.NewL" )
    CVtUiBrightness* self =
        new ( ELeave ) CVtUiBrightness( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiBrightness.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiBrightness::~CVtUiBrightness
// ---------------------------------------------------------------------------
//
CVtUiBrightness::~CVtUiBrightness()
    {
    __VTPRINTENTER( "CVtUiBrightness.~" )
    __VTPRINTEXIT( "CVtUiBrightness.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiBrightness::StartL
// ---------------------------------------------------------------------------
//
void CVtUiBrightness::StartL()
    {
    __VTPRINTENTER( "CVtUiBrightness.StartL" )
    CVtUiPrefSliderBase::StartL();
    iFeatureManager.UiStates().SetBrightnessModeOn( ETrue );
    __VTPRINTEXIT( "CVtUiBrightness.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiBrightness::Stop
// ---------------------------------------------------------------------------
//
void CVtUiBrightness::Stop()
    {
    __VTPRINTENTER( "CVtUiBrightness.Stop" )
    CVtUiPrefSliderBase::Stop();
    iFeatureManager.UiStates().SetBrightnessModeOn( EFalse );
    __VTPRINTEXIT( "CVtUiBrightness.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiBrightness::CVtUiBrightness
// ---------------------------------------------------------------------------
//
CVtUiBrightness::CVtUiBrightness( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPrefSliderBase( aFeatureManager, EVtUiFeatureIdBrightness )
    {
    __VTPRINTENTER( "CVtUiBrightness.CVtUiBrightness" )
    __VTPRINTEXIT( "CVtUiBrightness.CVtUiBrightness" )
    }

// ---------------------------------------------------------------------------
// CVtUiBrightness::CVtUiBrightness
// ---------------------------------------------------------------------------
//
void CVtUiBrightness:: ConstructL()
    {
    __VTPRINTENTER( "CVtUiBrightness.ConstructL" )
    BaseConstructL();
    SetPopup( CVtUiBrightnessPopup::NewL( iFeatureManager ) );
    __VTPRINTEXIT( "CVtUiBrightness.ConstructL" )
    }

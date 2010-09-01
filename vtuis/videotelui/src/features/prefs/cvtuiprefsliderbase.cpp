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
* Description:   Implementatin of base class for video pref sliders
*
*/


#include    <cvtlogger.h>

#include    "cvtuiprefsliderbase.h"
#include    "cvtuifeaturemanager.h"
#include    "mvtuicomponentmanager.h"
#include    "CVtUiAppUi.h"
#include    "mvtuicommandmanager.h"
#include    "cvtuiprefpopupbase.h"


// ---------------------------------------------------------------------------
// CVtUiPrefSliderBase::~CVtUiPrefSliderBase
// ---------------------------------------------------------------------------
//
CVtUiPrefSliderBase::~CVtUiPrefSliderBase()
    {
    __VTPRINTENTER( "CVtUiPrefSliderBase.~CVtUiPrefSliderBase" )
    __VTPRINTEXIT( "CVtUiPrefSliderBase.~CVtUiPrefSliderBase" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSliderBase::StartL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSliderBase::StartL()
    {
    __VTPRINTENTER( "CVtUiPrefSliderBase.StartL" )
    // call base class implementation
    CVtUiSliderBase::StartL();

    // Swap image places if needed
    iFeatureManager.AppUi().SwitchViewFinderToMainPaneL();
    
    __VTPRINTEXIT( "CVtUiPrefSliderBase.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefSliderBase::Stop
// ---------------------------------------------------------------------------
//
void CVtUiPrefSliderBase::Stop()
    {
    __VTPRINTENTER( "CVtUiPrefSliderBase.Stop" )
    if ( iFeatureState == MVtUiFeature::EActive )
        {
        // call base class implementation
        CVtUiSliderBase::Stop();

        // Swap image places if needed
        TRAP_IGNORE( iFeatureManager.AppUi().RestoreViewFinderL() );  
        }
    __VTPRINTEXIT( "CVtUiPrefSliderBase.Stop" )
    }


// ---------------------------------------------------------------------------
// CVtUiPrefSliderBase::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSliderBase::InitFeatureL()
    {
    __VTPRINTENTER( "CVtUiPrefSliderBase.InitFeatureL" )
    // call base class implementation
    CVtUiSliderBase::InitFeatureL();
    __VTPRINTEXIT( "CVtUiPrefSliderBase.InitFeatureL" )
    }


// ---------------------------------------------------------------------------
// CVtUiPrefSliderBase::CVtUiPrefSliderBase
// ---------------------------------------------------------------------------
//
CVtUiPrefSliderBase::CVtUiPrefSliderBase( CVtUiFeatureManager& aFeatureManager,
        TVtUiFeatureId aFeatureId  ) : CVtUiSliderBase(
    aFeatureManager, aFeatureId )
    {
    __VTPRINTENTER( "CVtUiPrefSliderBase.CVtUiPrefSliderBase" )
    __VTPRINTEXIT( "CVtUiPrefSliderBase.CVtUiPrefSliderBase" )
    }


// ---------------------------------------------------------------------------
// CVtUiPrefSliderBase::BaseConstructL
// ---------------------------------------------------------------------------
//
void CVtUiPrefSliderBase::BaseConstructL()
    {
    __VTPRINTENTER( "CVtUiPrefSliderBase.BaseConstructL" )
    CVtUiSliderBase::BaseConstructL();
    __VTPRINTEXIT( "CVtUiPrefSliderBase.BaseConstructL" )
    }





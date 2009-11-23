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
* Description:  Base class implementation for video telephone sliders
*
*/


#include    <cvtlogger.h>

#include    "cvtuisliderbase.h"
#include    "cvtuipopupbase.h"
#include    "cvtuifeaturemanager.h"
#include    "mvtuicomponentmanager.h"

// ---------------------------------------------------------------------------
// CVtUiSliderBase::~CVtUiSliderBase
// ---------------------------------------------------------------------------
//
CVtUiSliderBase::~CVtUiSliderBase()
    {
    __VTPRINTENTER( "CVtUiSliderBase.~CVtUiSliderBase" )
    delete iPopup;
    __VTPRINTEXIT( "CVtUiSliderBase.~CVtUiSliderBase" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::UpdateSlider
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::UpdateSlider()
    {
    __VTPRINTENTER( "CVtUiSliderBase.UpdateSlider" )
    
    iPopup->UpdatePopupL();
    
    __VTPRINTEXIT( "CVtUiSliderBase.UpdateSlider" )
    }
// ---------------------------------------------------------------------------
// CVtUiSliderBase::StartL
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::StartL()
    {
    __VTPRINTENTER( "CVtUiSliderBase.StartL" )
    if ( iFeatureState  == MVtUiFeature::EReady )
        {
        iFeatureManager.ComponentManager().
            RequestActivationL( iPopup->ComponentId() );
        // set state
        iFeatureState = MVtUiFeature::EActive;
        }
    __VTPRINTEXIT( "CVtUiSliderBase.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::Stop
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::Stop()
    {
    __VTPRINTENTER( "CVtUiSliderBase.Stop" )
    TRAP_IGNORE(
        {
        if ( iFeatureState == MVtUiFeature::EActive )
            {
            // set state
            iFeatureState = MVtUiFeature::EReady;
            iFeatureManager.ComponentManager().
                DeActivateComponentL( iPopup->ComponentId()  );
            }
        } );
    __VTPRINTEXIT( "CVtUiSliderBase.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::InitFeatureL()
    {
    __VTPRINTENTER( "CVtUiSliderBase.InitFeatureL" )
    iFeatureState = EReady;
    __VTPRINTEXIT( "CVtUiSliderBase.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::ComponenStateChangedL()
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::ComponenStateChangedL()
    {
    __VTPRINTENTER( "CVtUiSliderBase.ComponenStateChangedL()" )
    // Close event received stop the feature
    Stop();
    __VTPRINTEXIT( "CVtUiSliderBase.ComponenStateChangedL()" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::SetPermanenVisibility()
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::SetPermanenVisibility( TBool aPermanent )
    {
    if ( iPopup )
        {
        iPopup->SetPermanenVisibility( aPermanent );
        }
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::CVtUiSliderBase
// ---------------------------------------------------------------------------
//
CVtUiSliderBase::CVtUiSliderBase( CVtUiFeatureManager& aFeatureManager,
        TVtUiFeatureId aFeatureId  ) : CVtUiFeatureBase(
    aFeatureId, aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiSliderBase.CVtUiSliderBase" )
    __VTPRINTEXIT( "CVtUiSliderBase.CVtUiSliderBase" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::ConstructL()
    {
    __VTPRINTENTER( "CVtUiSliderBase.ConstructL" )
    BaseConstructL();
    __VTPRINTEXIT( "CVtUiSliderBase.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::SetPopup
// ---------------------------------------------------------------------------
//
void CVtUiSliderBase::SetPopup( CVtUiPopupBase* aPopup )
    {
    __VTPRINTENTER( "CVtUiSliderBase.SetPopup" )
    iPopup = aPopup;
    if ( iPopup )
        {
        iPopup->SetObserver( *this );
        }
    __VTPRINTEXIT( "CVtUiSliderBase.SetPopup" )
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::SetPopup
// ---------------------------------------------------------------------------
//
CVtUiPopupBase& CVtUiSliderBase::Popup()
    {
    return *iPopup;
    }

// ---------------------------------------------------------------------------
// CVtUiSliderBase::SetPopup
// ---------------------------------------------------------------------------
//
const CVtUiPopupBase& CVtUiSliderBase::Popup() const
    {
    return *iPopup;
    }

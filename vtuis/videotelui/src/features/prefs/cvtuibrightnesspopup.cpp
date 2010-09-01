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



#include    <mvtengmedia.h>
#include    <cvtlogger.h>
#include    "cvtuibrightnesspopup.h"
#include	"tvtuilocalvariation.h"
#include    "mvtuicomponent.h"
#include    "CVtUiAppUi.h"
#include    "mvtuicomponentmanager.h"
#include    "tvtuicomponentstate.h"
#include    <mvtengcamerapreferences.h>

// ---------------------------------------------------------------------------
// CVtUiBrightnessPopup::NewL
// ---------------------------------------------------------------------------
//
CVtUiBrightnessPopup* CVtUiBrightnessPopup::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiBrightnessPopup.NewL" )
    CVtUiBrightnessPopup* self =
        new ( ELeave ) CVtUiBrightnessPopup( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiBrightnessPopup.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiBrightnessPopup::~CVtUiBrightnessPopup
// ---------------------------------------------------------------------------
//
CVtUiBrightnessPopup::~CVtUiBrightnessPopup()
    {
    __VTPRINTENTER( "CVtUiBrightnessPopup.~" )
    __VTPRINTEXIT( "CVtUiBrightnessPopup.~" )
    }
    
// ---------------------------------------------------------------------------
// CVtUiBrightnessPopup::CurrentValue
// ---------------------------------------------------------------------------
//
TInt CVtUiBrightnessPopup::CurrentValue()
    {
    __VTPRINTENTER( "CVtUiBrightnessPopup.CurrentValue" )
    // ask from engine current value
    TInt value;
    if ( iCameraPref->GetBrightness( value) )
        {
        __VTPRINTEXIT( "CVtUiBrightnessPopup.CurrentValueERR" )
        return 0;
        }
    __VTPRINTEXIT( "CVtUiBrightnessPopup.CurrentValue" )
    return value;
    }    
// ---------------------------------------------------------------------------
// CVtUiBrightnessPopup::CVtUiBrightnessPopup
// ---------------------------------------------------------------------------
//
CVtUiBrightnessPopup::CVtUiBrightnessPopup( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPrefPopupBase( aFeatureManager, TVtUiBlockListBitField(
        MVtUiComponent::EComponentIdDialer |
        MVtUiComponent::EComponentIdToolbar |
        MVtUiComponent::EComponentIdNumberEntry |
        MVtUiComponent::EComponentIdVolume |
        MVtUiComponent::EComponentIdZoom |
        MVtUiComponent::EVComponentIdContrast ), EVComponentIdBrightness,
        KVtEngSetBrightness ) 
    {

    __VTPRINTENTER( "CVtUiBrightnessPopup.CVtUiBrightnessPopup" )
    __VTPRINTEXIT( "CVtUiBrightnessPopup.CVtUiBrightnessPopup" )
    }
    
// ---------------------------------------------------------------------------
// CVtUiBrightnessPopup::CVtUiBrightnessPopup
// ---------------------------------------------------------------------------
//
void CVtUiBrightnessPopup:: ConstructL()
    {
    __VTPRINTENTER( "CVtUiBrightnessPopup.ConstructL" )
    BaseConstructL();
    __VTPRINTEXIT( "CVtUiBrightnessPopup.ConstructL" )
    }

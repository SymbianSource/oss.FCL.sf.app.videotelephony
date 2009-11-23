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
* Description:  Implementation of base class for video preference popups
*
*/


#include    <cvtlogger.h>
#include    <mvtengcamerapreferences.h>
#include    <cvtengmodel.h>

#include    "cvtuiprefpopupbase.h"
#include    "mvtuicomponentmanager.h"
#include    "mvtuicomponentstateobserver.h"
#include    "cvtuifeaturemanager.h"
#include    "CVtUiAppUi.h"

// Number of steps
static const TInt KStepCount = 20;

// Slider min value
static const TInt KSLiderMinValue = -100;

// Slider min value
static const TInt KSLiderDefaultValue = 0;

// Slider max value
static const TInt KSLiderMaxValue = 100;

// Min adjust value
static const TInt KMinAdjustValue = 0;

// Max adjust value
static const TInt KMaxAdjustValue = 20;

// default time out time for zoom popup
const TInt KDefaultPrefTimeOutTime = 5;  

// ---------------------------------------------------------------------------
// CVtUiPrefPopupBase::~CVtUiPrefPopupBase
// ---------------------------------------------------------------------------
//
CVtUiPrefPopupBase::~CVtUiPrefPopupBase()
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.~CVtUiPrefPopupBase" )
    __VTPRINTEXIT( "CVtUiPrefPopupBase.~CVtUiPrefPopupBase" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefPopupBase::HandleControlEventL()
// ---------------------------------------------------------------------------
//
void CVtUiPrefPopupBase::HandleControlEventL(
    CCoeControl* aControl,TCoeEvent aEventType )
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.HandleControlEventL" )
    CVtUiPopupBase::HandleControlEventL( aControl, aEventType );
    if ( aEventType == EEventStateChanged )
        {
        const TInt value( Value() );
        if ( value != iCurrent )
            {
            __VTPRINT( DEBUG_GEN, "CVtUiPrefPopupBase.OfferKeyEventL  value != current " )
            iCurrent = value;
             __VTPRINT2( DEBUG_GEN, "CVtUiPrefPopupBase.HandleControlEventL  = %d", ScaledValue() )
            AdjustVideoL( ScaledValue() );
            }
        }
    
    __VTPRINTEXIT( "CVtUiPrefPopupBase.HandleControlEventL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefPopupBase::UpdatePopupL()
// ---------------------------------------------------------------------------
//
void CVtUiPrefPopupBase::UpdatePopupL()
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.UpdatePrefPopupL" )
    
    AdjustVideoL( ScaledValue() );
    
    __VTPRINTEXIT( "CVtUiPrefPopupBase.UpdatePrefPopupL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefPopupBase::OfferKeyEventL()
// ---------------------------------------------------------------------------
//
TKeyResponse CVtUiPrefPopupBase::OfferKeyEventL( const TKeyEvent& aEvent, 
        TEventCode aCode )
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.OfferKeyEventL" )
    TKeyResponse response = 
        CVtUiPopupBase::OfferKeyEventL( aEvent, aCode );
    
    if ( response == EKeyWasConsumed )
        {
        AdjustVideoL( ScaledValue() );
        }
    
    __VTPRINTEXIT( "CVtUiPrefPopupBase.OfferKeyEventL" )
    return response;
    }

// CVtUiPrefPopupBase::AdjustVideoL()
// ---------------------------------------------------------------------------
//
void CVtUiPrefPopupBase::AdjustVideoL( TInt aValue )
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.AdjustVideoL" )
    // cast the parameter
    TPtrC8 params( reinterpret_cast< TUint8* >( &aValue ), sizeof( TInt ) );

    // Adjust Contrast
    iFeatureManager.AppUi().DoExecuteCmdL( iEngineCommandId, &params );
    __VTPRINTEXIT( "CVtUiPrefPopupBase.AdjustVideoL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrefPopupBase::DoActivateL()
// ---------------------------------------------------------------------------
//
void CVtUiPrefPopupBase::DoActivateL()
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.DoActivateL" )
    CVtUiPopupBase::DoActivateL();
    // Set current value
    __VTPRINT2( DEBUG_GEN, "CVtUiPrefPopupBase.DoActivateL  = %d", CurrentValue() )
    ScaleAndSetValue( CurrentValue() );
    AdjustVideoL( ScaledValue() );
    __VTPRINTEXIT( "CVtUiPrefPopupBase.DoActivateL" )
    }

// CVtUiPrefPopupBase::CVtUiPrefPopupBase
// ---------------------------------------------------------------------------
//
CVtUiPrefPopupBase::CVtUiPrefPopupBase( CVtUiFeatureManager& aFeatureManager,
  TVtUiBlockListBitField aBitField, TComponentId aComponentId, TInt aCmdId  ) :
    CVtUiPopupBase( aFeatureManager.ComponentManager(), aBitField,
    aComponentId ),  iFeatureManager( aFeatureManager ),
    iEngineCommandId ( aCmdId )
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.CVtUiPrefPopupBase" )
    __VTPRINTEXIT( "CVtUiPrefPopupBase.CVtUiPrefPopupBase" )
    }


// ---------------------------------------------------------------------------
// CVtUiPrefPopupBase::BaseConstructL
// ---------------------------------------------------------------------------
//
void CVtUiPrefPopupBase::BaseConstructL()
    {
    __VTPRINTENTER( "CVtUiPrefPopupBase.BaseConstructL" )
    CVtUiPopupBase::BaseConstructL();
    // Get camera preferences extension.
    iCameraPref = static_cast<MVtEngCameraPreferences*> ( iFeatureManager.
        AppUi().Model().Extension( KVtEngExtensionCameraPreferences ) );

    // Set range and step count for the slider
    SetAdjustRange( KMinAdjustValue, KMaxAdjustValue, KStepCount );
    
    // Set value range to baseclass
    // range  e.g. 0-20
    SetMinAndMaxValues( KSLiderMinValue , KSLiderMaxValue );
    
    // Set slider type to percentage
    SetValueType( EAknSliderValuePercentage );
    
    // Set default value
    ScaleAndSetValue( KSLiderDefaultValue );
    
    // Set timeout
    SetTimeOut( KDefaultPrefTimeOutTime );
    
    __VTPRINTEXIT( "CVtUiPrefPopupBase.BaseConstructL" )
    }

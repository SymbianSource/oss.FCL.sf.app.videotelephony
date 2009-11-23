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
* Description:  Zoom popup implementation.
*
*/


#include    <aknvolumepopup.h>
#include    <cvtlogger.h>
#include    "cvtuizoompopup.h"
#include    "cvtuifeaturemanager.h"
#include	"tVtuifeaturevariation.h"
#include    "CVtUiAppUi.h"
#include    "cvtengmodel.h"

// Number of zoom steps
static const TInt KZoomStepCount = 10;

// Minimum zoom factor value
static const TInt KMinZoomFactor = 0;

// default time out time for zoom popup
const TInt KDefaultZoomTimeOutTime = 5;  

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::NewL
// ---------------------------------------------------------------------------
//
CVtUiZoomPopup* CVtUiZoomPopup::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiZoomPopup.NewL" )
    CVtUiZoomPopup* self =
        new ( ELeave ) CVtUiZoomPopup( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiZoomPopup.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::~CVtUiZoomPopup
// ---------------------------------------------------------------------------
//
CVtUiZoomPopup::~CVtUiZoomPopup()
    {
    __VTPRINTENTER( "CVtUiZoomPopup.~" )
    __VTPRINTEXIT( "CVtUiZoomPopup.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::RefreshL
// ---------------------------------------------------------------------------
//
void CVtUiZoomPopup::RefreshL()
    {
    __VTPRINTENTER( "CVtUiZoomPopup.RefreshL" )
    
    UpdateAdjustRangeL();
    
    iCurrent = CurrentZoomStep();
    if ( iCurrent < KMinZoomFactor )
        {
        User::Leave( KErrArgument );
        }
    SetValue( iCurrent );
    ShowPopupL();
    __VTPRINTEXIT( "CVtUiZoomPopup.RefreshL" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::DoActivateL()
// ---------------------------------------------------------------------------
//
void CVtUiZoomPopup::DoActivateL()
    {
    __VTPRINTENTER( "CVtUiZoomPopup.DoActivateL" )
    UpdateAdjustRangeL();
    CVtUiPopupBase::DoActivateL();
    // In order to refresh softkey.
    iFeatureManager.AppUi().RefreshSoftkeysL();
    __VTPRINTEXIT( "CVtUiZoomPopup.DoActivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::OfferKeyEventL()
// ---------------------------------------------------------------------------
//
TKeyResponse CVtUiZoomPopup::OfferKeyEventL( const TKeyEvent& aEvent,
    TEventCode aCode )
    {
    __VTPRINTENTER( "CVtUiZoomPopup.OfferKeyEventL" )
    TKeyResponse response( EKeyWasNotConsumed );
    // Don't  handle other types here
    if ( aCode != EEventKey )
        {
        return response;
        }
        
    if ( aEvent.iScanCode == EStdKeyUpArrow ||
         aEvent.iScanCode == EStdKeyDownArrow ||
         aEvent.iCode == EKeyZoomIn ||
         aEvent.iCode == EKeyZoomOut )
        {
        __VTPRINT( DEBUG_GEN, "CVtUiZoomPopup.OfferKeyEventL zoom key" )
        TInt step( 1 );
        if ( aEvent.iScanCode == EStdKeyDownArrow ||
             aEvent.iCode == EKeyZoomOut )
            {
            step = -step;
            }
        const TInt current( Value() );
        TInt value( current + step );
        value = Max( KMinZoomFactor, Min( value, KZoomStepCount ) );
        if ( value != current )
            {
            __VTPRINT2( DEBUG_GEN, "CVtUiZoomPopup.OfferKeyEventL zoom = %d",
                value )
            SetValue( value );
            iFeatureManager.AppUi().SetZoomFactorL( ScaledValue() );
            response = EKeyWasConsumed;
            }
        ShowPopupL();
        }
    __VTPRINTEXITR( "CVtUiZoomPopup.OfferKeyEventL %d", response )
    return response;
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::HandleControlEventL
// ---------------------------------------------------------------------------
//
void CVtUiZoomPopup::HandleControlEventL( CCoeControl* aControl,
    TCoeEvent aEventType )
    {
    __VTPRINTENTER( "CVtUiZoomPopup.HandleControlEventL" )
    CVtUiPopupBase::HandleControlEventL( aControl, aEventType );
    
    if ( aEventType == EEventStateChanged )
        {
        __VTPRINT2( DEBUG_GEN, "CVtUiZoomPopup.HandleControlEventL zoom = %d", ScaledValue() )
        
        if ( CurrentZoomStep() != Value() )
            {
            iFeatureManager.AppUi().SetZoomFactorL( ScaledValue() );
            }
        }
        
    __VTPRINTEXIT( "CVtUiZoomPopup.HandleControlEventL" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::CVtUiZoomPopup
// ---------------------------------------------------------------------------
//
CVtUiZoomPopup::CVtUiZoomPopup( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPopupBase( aFeatureManager.ComponentManager(),
      TVtUiBlockListBitField(
        MVtUiComponent::EComponentIdDialer |
        MVtUiComponent::EComponentIdToolbar |
        MVtUiComponent::EComponentIdNumberEntry |
        MVtUiComponent::EComponentIdVolume  |
        MVtUiComponent::EVComponentIdBrightness |
        MVtUiComponent::EVComponentIdContrast
        ),
      EComponentIdZoom ),
      iFeatureManager( aFeatureManager ),
      iMedia( aFeatureManager.AppUi().Model().Media() ),
      iCurrent( KErrNotReady )
    {
    __VTPRINTENTER( "CVtUiZoomPopup.CVtUiZoomPopup" )
    __VTPRINTEXIT( "CVtUiZoomPopup.CVtUiZoomPopup" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiZoomPopup::ConstructL()
    {
    __VTPRINTENTER( "CVtUiZoomPopup.ConstructL" )
    BaseConstructL();
    // Set slider type to percentage
    SetValueType( EAknSliderValuePercentage );
    
    // Set timeout
    SetTimeOut( KDefaultZoomTimeOutTime );
    __VTPRINTEXIT( "CVtUiZoomPopup.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::UpdateAdjustRangeL
// ---------------------------------------------------------------------------
//
void CVtUiZoomPopup::UpdateAdjustRangeL()
    {
    __VTPRINTENTER( "CVtUiZoomPopup.UpdateAdjustRangeL" )
    // Get max zoom step from engine
    iMax = MaxZoomStep();
    // Set value range to visible slider control
    // range 0-10 or 0-iMax if max < 0
    // stepcount = 10 or iMax if max < 10
    SetAdjustRange( KMinZoomFactor, Min( KZoomStepCount, iMax ), Min( KZoomStepCount, iMax ) );
   
    // Set value range to baseclass
    // range on e.g. 0-20
    SetMinAndMaxValues( KMinZoomFactor, iMax );    
    
    // Get current zoom step
    iCurrent = CurrentZoomStep();    
    
    if ( iCurrent == KErrNotFound || iMax == KErrNotFound || iCurrent > iMax )
        {
        User::Leave( KErrNotFound );
        }
    // Set new value
    SetValue( iCurrent );
    __VTPRINTEXIT( "CVtUiZoomPopup.UpdateAdjustRangeL" )
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::CurrentZoomStep
// ---------------------------------------------------------------------------
//
TInt CVtUiZoomPopup::CurrentZoomStep() const
    {
    __VTPRINTENTER( "CVtUiZoomPopup.CurrentZoomStep" )
    TInt current( KMinZoomFactor );
    const TInt error( iMedia.GetCurrentZoomStep( current ) );
    current = ( error ? KErrNotFound : current );
    
    // Value asked from the engine must be scaled.
    // If the current asked  value is 1 then the scaling formula in the 
    // popupbase doesn't round the value to 1 there fore value is 
    // initalized to 1.
    TInt  val = 1; 
    if ( current != 1 )
        {
        val =  SliderValueWithScaling( current );
        }
    __VTPRINTEXITR( "CVtUiZoomPopup.CurrentZoomStep %d", val )
    return val;
    }

// ---------------------------------------------------------------------------
// CVtUiZoomPopup::MaxZoomStep
// ---------------------------------------------------------------------------
//
TInt CVtUiZoomPopup::MaxZoomStep() const
    {
    __VTPRINTENTER( "CVtUiZoomPopup.MaxZoomStep" )
    TInt max( KMinZoomFactor );
    const TInt error( iMedia.GetMaxZoomStep( max ) );
    max = ( error ? KErrNotFound : max );
    __VTPRINTEXITR( "CVtUiZoomPopup.MaxZoomStep %d", max )
    return max;
    }
    
// ---------------------------------------------------------------------------
// CVtUiZoomPopup::ScaleAndSetZoomFactorL
// ---------------------------------------------------------------------------
//
void CVtUiZoomPopup::ScaleAndSetZoomFactorL( TInt aValue )
    {
       __VTPRINTENTER( "CVtUiZoomPopup.ScaleAndSetZoomFactorL" )
    const TInt value = aValue * MaxZoomStep() / 10; // 10 vakioksi count + 1 ei yhtä
    iFeatureManager.AppUi().SetZoomFactorL( value );  
     __VTPRINTEXITR( "CVtUiZoomPopup.ScaleAndSetZoomFactorL %d", value )
    }


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
* Description:  Base class for video telephone popups
*
*/


#include    <cvtlogger.h>
#include    <AknUtils.h>
#include    <aknvolumepopup.h>
#include    <fbs.h>

#include    "cvtuipopupbase.h"
#include    "mvtuicomponentmanager.h"
#include    "mvtuicomponentstateobserver.h"
#include    "VtUiPanic.h"
#include    <layoutmetadata.cdl.h>
#include    <videotelui.rsg>
#include    <aknlayoutscalable_apps.cdl.h>

// default time out time for popup
const TInt KDefaultTimeOutTime = 2;  

// max value for slider is 100 (100%)
const TInt KMaxSliderValue = 100;  

// Implementation of TVtUiBaseComponentState

// ---------------------------------------------------------------------------
// TVtUiBaseComponentState::TVtUiBaseComponentState
// ---------------------------------------------------------------------------
//
TVtUiBaseComponentState::TVtUiBaseComponentState(
    MVtUiComponent& aComponent, TVtUiBlockListBitField aBitField  ) :
    TVtUiComponentState( aComponent, aBitField )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::~CVtUiPopupBase
// ---------------------------------------------------------------------------
//
CVtUiPopupBase::~CVtUiPopupBase()
    {
    __VTPRINTENTER( "CVtUiPopupBase.~CVtUiPopupBase" )
    if ( iPopup )
        {
        iPopup->CloseVolumePopup();
        }
     // unregister component change registration
    iComponentManager.ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::EUnregister );
    delete iPopup;
    __VTPRINTEXIT( "CVtUiPopupBase.~CVtUiPopupBase" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::ComponentId
// ---------------------------------------------------------------------------
//
 MVtUiComponent::TComponentId CVtUiPopupBase::ComponentId() const
    {
    __VTPRINTENTER( "CVtUiPopupBase.ComponentId" )
    __VTPRINTEXIT( "CVtUiPopupBase.ComponentId" )
    return iComponentId;
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::ComponentAsControl
// ---------------------------------------------------------------------------
//
 CCoeControl* CVtUiPopupBase::ComponentAsControl()
    {
    __VTPRINTENTER( "CVtUiPopupBase.ComponentAsControl" )
    __VTPRINTEXIT( "CVtUiPopupBase.ComponentAsControl" )
    return NULL;
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::DoActivateL
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::DoActivateL()
    {
    __VTPRINTENTER( "CVtUiPopupBase.DoActivateL" )
    User::LeaveIfError(
       iComponentManager.ChangeResourceChangeRegistration(
        *this, MVtUiComponentManager::ERegister ) );

    User::LeaveIfError( iComponentManager.ChangeKeyEventRegistration(
        *this, MVtUiComponentManager::ERegister ) );

    ShowPopupL();
    __VTPRINTEXIT( "CVtUiPopupBase.DoActivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::DoDeactivateL()
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::DoDeactivateL()
    {
    __VTPRINTENTER( "CVtUiPopupBase.DoDeactivateL()" )
    iPopup->CloseVolumePopup();
    //notify observer that popup has been closed
    if ( iCompStateObserver )
        {
        iCompStateObserver->ComponenStateChangedL();
        }
    // unregister resource change registration
    iComponentManager.ChangeResourceChangeRegistration(
        *this, MVtUiComponentManager::EUnregister );

    iComponentManager.ChangeKeyEventRegistration(
        *this, MVtUiComponentManager::EUnregister );
    __VTPRINTEXIT( "CVtUiPopupBase.DoDeactivateL()" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::HandleResourceChangeL()
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::HandleResourceChangeL( TInt aType )
    {
    __VTPRINTENTER( "CVtUiPopupBase.HandleResourceChangeL()" )
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        iPopup->SetPosition( PopupPosition() );
        }
    __VTPRINTEXIT( "CVtUiPopupBase.HandleResourceChangeL()" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::HandleControlEventL
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::HandleControlEventL( CCoeControl* /*aControl*/,
    TCoeEvent aEventType )
    {
    __VTPRINTENTER( "CVtUiPopupBase.HandleControlEventL" )
    if ( aEventType == EEventStateChanged )
        {
        // popup closed
        if( !IsPopUpVisible() )
            {
            ClosePopup();
            }
        }
    __VTPRINTEXIT( "CVtUiPopupBase.HandleControlEventL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::OfferKeyEventL()
// ---------------------------------------------------------------------------
//
TKeyResponse CVtUiPopupBase::OfferKeyEventL( const TKeyEvent& aEvent,
    TEventCode aCode )
    {
    __VTPRINTENTER( "CVtUiPopupBase.OfferKeyEventL" )
    TKeyResponse response( EKeyWasNotConsumed );
    // Don't  handle other types here
    if ( aCode != EEventKey )
        {
        return response;
        }

    if ( aEvent.iScanCode == EStdKeyUpArrow ||
            aEvent.iScanCode == EStdKeyDownArrow )
        {
        __VTPRINT( DEBUG_GEN, "CVtUiPopupBase.OfferKeyEventL" )
        TInt step( 1 );
        if ( aEvent.iScanCode == EStdKeyDownArrow )
            {
            step = -step;
            }
        
        const TInt current( Value() );
        TInt value( current + step );
        
        TInt maxValue;
        TInt minValue;
        iPopup->GetRange( minValue, maxValue );
        
        __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase.OfferKeyEventL iPopup minValue = %d",
                minValue )
        __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase.OfferKeyEventL iPopup maxValue = %d",
                maxValue )
         
        minValue = minValue / iScalingConstant;
        value = Max( minValue, Min( value, iStepCount ) );
        if ( value != current )
            {
            __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase.OfferKeyEventL Volume value = %d",
                    value )
            SetValue( value );
            response = EKeyWasConsumed;
            }
        ShowPopupL();
        }
    __VTPRINTEXITR( "CVtUiPopupBase.OfferKeyEventL %d", response )
    return response;
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetObserver()
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetObserver( MVtUiComponentStateObserver& aCompStateObserver )
    {
    __VTPRINTENTER( "CVtUiPopupBase.SetObserver()" )
    iCompStateObserver = &aCompStateObserver;
    __VTPRINTEXIT( "CVtUiPopupBase.SetObserver()" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetValueType()
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetValueType( TInt aValueType )
    {
    __VTPRINTENTER( "CVtUiPopupBase.SetValueType" )
    iPopup->SetValueType( aValueType );
    __VTPRINTEXIT( "CVtUiPopupBase.SetValueType" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetPermanenVisibility()
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetPermanenVisibility( TBool aPermanent )
    {
    __VTPRINTENTER( "CVtUiPopupBase.SetPermanenVisibility" )
    __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase = %d", aPermanent  );
    const TInt longPeriod( 86400 ); // 24 h
    if ( aPermanent ) 
        {
        iPopup->SetTimeOutAsSecond( longPeriod );
        iPopup->ClosePopupWhenTappedOutside( !aPermanent );
        }
     else
        {
        iPopup->ClosePopupWhenTappedOutside( !aPermanent );
        iPopup->SetTimeOutAsSecond( iTimeOutTime );
        }
     __VTPRINTEXIT( "CVtUiPopupBase.SetPermanenVisibility" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::CVtUiPopupBase
// ---------------------------------------------------------------------------
//
CVtUiPopupBase::CVtUiPopupBase(  MVtUiComponentManager& aComponentManager,
  TVtUiBlockListBitField aBitField, TComponentId aComponentId ) :
  iComponentManager ( aComponentManager ), iComponentState( *this, aBitField ),
  iComponentId( aComponentId ), iScalingConstant( 1 )
    {
    __VTPRINTENTER( "CVtUiPopupBase.CVtUiPopupBase" )
    __VTPRINTEXIT( "CVtUiPopupBase.CVtUiPopupBase" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::BaseConstructL
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::BaseConstructL()
    {
    __VTPRINTENTER( "CVtUiPopupBase.BaseConstructL" )
    iPopup = CAknVolumePopup::NewL( NULL, ETrue );
    iPopup->SetObserver( this );

    // Initialized to 2 seconds
    iTimeOutTime = KDefaultTimeOutTime;
    
    // set position
    iPopup->SetPosition( PopupPosition() );
   
    User::LeaveIfError(
        iComponentManager.ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::ERegister ) );
    __VTPRINTEXIT( "CVtUiPopupBase.BaseConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::ShowPopupL
// ---------------------------------------------------------------------------
//
void  CVtUiPopupBase::ShowPopupL()
    {
    __VTPRINTENTER( "CVtUiPopupBase.ShowPopupL" )
    iPopup->ShowVolumePopupL();
    __VTPRINTEXIT( "CVtUiPopupBase.ShowPopupL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::OpenPopupL
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::OpenPopupL()
    {
    __VTPRINTENTER( "CVtUiPopupBase.OpenPopupL" )
    TRAPD( error,
        iComponentManager.RequestActivationL( ComponentId() ) );
    __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase.OpenPopupL reqAct=%d", error );
    User::LeaveIfError( error );
    __VTPRINTEXIT( "CVtUiPopupBase.OpenPopupL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::ClosePopup
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::ClosePopup()
    {
    __VTPRINTENTER( "CVtUiPopupBase.ClosePopup" )
    TInt error( KErrNone );
    TRAP( error, iComponentManager.DeActivateComponentL( ComponentId() ) );
    __VTPRINTEXITR( "CVtUiPopupBase.ClosePopup %d", error )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetTimeOut
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetTimeOut( TInt aTime )
    {
    iTimeOutTime = aTime;
    iPopup->SetTimeOutAsSecond( aTime );
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::IsPopUpVisible
// ---------------------------------------------------------------------------
//
TBool CVtUiPopupBase::IsPopUpVisible()
    {
    return iPopup->IsVisible();
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::PopupPosition
// ---------------------------------------------------------------------------
//
TPoint CVtUiPopupBase::PopupPosition() const
    {
    __VTPRINTENTER( "CVtUiPopupBase.PopupPosition" )
    TRect mainPaneRect;
    TAknWindowLineLayout popupLineLayout;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, mainPaneRect );
    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        popupLineLayout =
            AknLayoutScalable_Apps::aid_placing_vt_slider_lsc().LayoutLine();
        }
    else
        {
        popupLineLayout = 
            AknLayoutScalable_Apps::aid_placing_vt_slider_prt().LayoutLine();
        }
    
    TAknLayoutRect layoutRect;
    layoutRect.LayoutRect( mainPaneRect, popupLineLayout );
    __VTPRINTEXIT( "CVtUiPopupBase.PopupPosition" )
    return layoutRect.Rect().iTl;
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetPopupValue
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetPopupValue( TInt aValue )
    {
    iPopup->SetValue( aValue * iScalingConstant );
    }
       
// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetAdjustRange
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetAdjustRange( TInt aMinValue, TInt aMaxValue,
    TInt aStepCount )
    {
    __VTPRINTENTER( "CVtUiPopupBase.SetAdjustRange" )
    __ASSERT_ALWAYS( aMinValue <= aMaxValue &&
        ( aMaxValue - aMinValue ) >= aStepCount &&
        aStepCount > 0, VtUiPanic::Panic( EVtUiPanicOutOfRange ) );
    
    // store stepcount
    iStepCount = aStepCount;
    
    // Aknvolumepopup does not do any scaling i.e max value
    // must be 100 or otherwise the per cent value is not shown right.
    // Scaling constant is used to multiple max value to be 100.
    iScalingConstant = KMaxSliderValue / aMaxValue;
    iPopup->SetRange( aMinValue, KMaxSliderValue );
    TInt stepSize = KMaxSliderValue / aStepCount;
    iPopup->SetStepSize( stepSize );
    __VTPRINTEXIT( "CVtUiPopupBase.SetAdjustRange" )
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetValue
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetValue( TInt aValue )
    {
    __VTPRINTENTER( "CVtUiPopupBase.SetValue" )
    SetPopupValue( aValue ); 
    __VTPRINTEXITR( "CVtUiPopupBase.SetValue %d", Value() )
    }
 
 // ---------------------------------------------------------------------------
// CVtUiPopupBase::ScaleAndSetValue
// ---------------------------------------------------------------------------
//
 void CVtUiPopupBase::ScaleAndSetValue( TInt aValue )
    {
    __VTPRINTENTER( "CVtUiPopupBase.ScaleAndSetValue" )
    SetPopupValue( SliderValueWithScaling( aValue ) );
    __VTPRINTEXITR( "CVtUiPopupBase.ScaleAndSetValue %d", Value() )
    }
 
// ---------------------------------------------------------------------------
// CVtUiPopupBase::ScaledValue
// ---------------------------------------------------------------------------
//
 TInt CVtUiPopupBase::ScaledValue() const
    {
    __VTPRINTENTER( "CVtUiPopupBase.ScaledValue" )
     TInt value = Value() * ( iMax-iMin ) / iStepCount + iMin;
    __VTPRINTEXITR( "CVtUiPopupBase.ScaledValue %d", value )    
    return value;
    }
    
// ---------------------------------------------------------------------------
// CVtUiPopupBase::SliderValueWithScaling
// ---------------------------------------------------------------------------
//
 TInt CVtUiPopupBase::SliderValueWithScaling( TInt aValue) const
    {
    __VTPRINTENTER( "CVtUiPopupBase.SliderValueWithScaling" )
    __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase.aValue=%d", aValue )
    __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase.iStepCount=%d", iStepCount )
    __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase.iMax=%d", iMax )
    
    if ( iMax == aValue)
        {
        return iStepCount;
        }
    else if ( iMin == aValue )
        {
        return 0;
        }
    TInt modValue = iStepCount * ( aValue - iMin) % ( iMax - iMin );        
    TInt value = iStepCount * ( aValue - iMin) / ( iMax - iMin ); 
           
    if ( modValue >  ( iMax - iMin ) / 2 )
        {
        value++;
        }
    
    __VTPRINTEXITR( "CVtUiPopupBase.SliderValueWithScaling %d", value )    
    return value;
    }
    
// ---------------------------------------------------------------------------
// CVtUiPopupBase::SetMinAndMaxValues
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::SetMinAndMaxValues( TInt aMin, TInt aMax )
    {
     __VTPRINTENTER( "CVtUiPopupBase.SetMaxAndMinValues" )
     __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase..aMax=%d", aMax )
     __VTPRINT2( DEBUG_GEN, "CVtUiPopupBase..aMinV=%d", aMin )
    iMax = aMax;
    iMin = aMin;
    __VTPRINTEXIT( "CVtUiPopupBase.SetMaxAndMinValues " ) 
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::Value
// ---------------------------------------------------------------------------
//
TInt CVtUiPopupBase::Value() const
    {
    __VTPRINTENTER( "CVtUiPopupBase.Value" )
    __VTPRINTEXITR( "CVtUiPopupBase.Value %d", iPopup->Value() )
    return iPopup->Value() / iScalingConstant;
    }

// ---------------------------------------------------------------------------
// CVtUiPopupBase::UpdatePopupL
// ---------------------------------------------------------------------------
//
void CVtUiPopupBase::UpdatePopupL()
    {
    __VTPRINTENTER( "CVtUiPopupBase.UpdatePopupL" )
    __VTPRINTEXIT( "CVtUiPopupBase.UpdatePopupL " ) 
    }

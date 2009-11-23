/*
* Copyright (c) 2007 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  White balance UI feature implementation.
*
*/


#include    <mvtengmedia.h>
#include    <cvtengmodel.h>
#include    <mvtengcamerapreferences.h>
#include    "cvtuiwhitebalance.h"
#include    "tvtuifeatureids.h"
#include    <videotelui.rsg>
#include    <cvtlogger.h>
#include    "mvtuicomponentmanager.h"
#include    "cvtuifeaturemanager.h"
#include    "CVtUiAppUi.h"
#include	"tvtuilocalvariation.h"
#include    "tvtuistates.h"
#include    "cvtuifeaturemanager.h"
#include    "cvtuicommandmanager.h"

// Implementation of TVtUiWhiteBalanceComponentState

// ---------------------------------------------------------------------------
// TVtUiWhiteBalanceComponentState::TVtUiWhiteBalanceComponentState
// ---------------------------------------------------------------------------
//
TVtUiWhiteBalanceComponentState::TVtUiWhiteBalanceComponentState(
    MVtUiComponent& aComponent ) :
    TVtUiComponentState( aComponent,
        TVtUiBlockListBitField(
            MVtUiComponent::EComponentIdToolbar |
            MVtUiComponent::EComponentIdNumberEntry ) )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::NewL
// ---------------------------------------------------------------------------
//
CVtUiWhiteBalance* CVtUiWhiteBalance::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.NewL" )
    CVtUiWhiteBalance* self =
        new ( ELeave ) CVtUiWhiteBalance( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiWhiteBalance.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::~CVtUiWhiteBalance
// ---------------------------------------------------------------------------
//
CVtUiWhiteBalance::~CVtUiWhiteBalance()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.~CVtUiWhiteBalance" )
    // unregister layout change
    iFeatureManager.ComponentManager().ChangeLayoutChangeRegistration(
        *this, MVtUiComponentManager::EUnregister );
     // unregister component
    iFeatureManager.ComponentManager().ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::EUnregister );
    __VTPRINTEXIT( "CVtUiWhiteBalance.~CVtUiWhiteBalance" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::StartL
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::StartL()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.StartL" )
    if ( iFeatureState == MVtUiFeature::EReady )
        {
        iFeatureManager.AppUi().EnableCommandActivatingAndCleanupPushL();
        iFeatureManager.UiStates().SetIsFixedToolbarVisible( EFalse );
        iFeatureManager.ComponentManager().
            RequestActivationL ( MVtUiComponent::EComponentIdWhiteBalance );
        CleanupStack::Pop(); // EnableCommandActivatingAndCleanupPushL
        // set state
        iFeatureState = MVtUiFeature::EActive;
        }
    __VTPRINTEXIT( "CVtUiWhiteBalance.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::Stop
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::Stop()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.Stop" )
    iAsyncCallback->Cancel();
    iAsyncCallback->Set( TCallBack( &DoStopL, this ) );
    iAsyncCallback->CallBack();
    __VTPRINTEXIT( "CVtUiWhiteBalance.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::InitFeatureL()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.InitFeatureL" )
    CVtUiPrefSettingListBase::InitFeatureL();
    User::LeaveIfError(
       iFeatureManager.ComponentManager().ChangeComponentRegistration(
       iComponentState, MVtUiComponentManager::ERegister ) );
    User::LeaveIfError(
       iFeatureManager.ComponentManager().ChangeLayoutChangeRegistration(
       *this, MVtUiComponentManager::ERegister ) );
    iFeatureState  = EReady;
    __VTPRINTEXIT( "CVtUiWhiteBalance.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::ComponentId
// ---------------------------------------------------------------------------
//
MVtUiComponent::TComponentId CVtUiWhiteBalance::ComponentId() const
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.ComponentId" )
    __VTPRINTEXIT( "CVtUiWhiteBalance.ComponentId" )
    return MVtUiComponent::EComponentIdWhiteBalance;
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::ComponentAsControl
// ---------------------------------------------------------------------------
//
CCoeControl* CVtUiWhiteBalance::ComponentAsControl()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.ComponentAsControl" )
    __VTPRINTEXIT( "CVtUiWhiteBalance.ComponentAsControl" )
    return NULL;
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::DoActivateL
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::DoActivateL()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.DoActivateL" )
    // get supported white balance modes
    iCameraPref->GetSupportedWhiteBalanceModes( iSupportedModes );
    __VTPRINT2( DEBUG_GEN,"CVtUiWhiteBalance.DoActivateL=%d", iSupportedModes )
    iFeatureManager.UiStates().SetWhiteBalanceModeOn( ETrue );
    iAsyncCallback->Cancel();
    iAsyncCallback->Set( TCallBack( &DoStartL, this ) );
    iAsyncCallback->CallBack();
    __VTPRINTEXIT( "CVtUiWhiteBalance.DoActivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::DoDeactivateL
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::DoDeactivateL()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.DoDeactivateL" )
    iFeatureManager.UiStates().SetWhiteBalanceModeOn( EFalse );
    CVtUiPrefSettingListBase::StopSettingPageL();
    __VTPRINTEXIT( "CVtUiWhiteBalance.DoDeactivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::HandleLayoutChangeL
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::HandleLayoutChangeL()
    {
     __VTPRINTENTER( "CVtUiWhiteBalance.HandleLayoutChangeL" )
    if ( iFeatureState  == MVtUiFeature::EActive )
        {
        SizeChanged();
        }
    __VTPRINTEXIT( "CVtUiWhiteBalance.HandleLayoutChangeL" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::CurrentSelection
// ---------------------------------------------------------------------------
//
TInt CVtUiWhiteBalance::CurrentSelection()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.CurrentSelection" )
    // ask from engine which item is currently active
    MVtEngCameraPreferences::TWhiteBalance wb;
    if ( iCameraPref->GetWhiteBalance( wb ) )
        {
        __VTPRINT( DEBUG_GEN, "CurrentSelection::error" );
        __VTPRINTEXIT( "CVtUiWhiteBalance.CurrentSelection" )
        // if error occured return 0 i.e. first list item
        return 0;
        }
    __VTPRINTEXIT( "CVtUiWhiteBalance.CurrentSelection" )
    return MapWBEnumToArrayIndex( wb );
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::SetItemsL
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::SetItemsL( CDesCArray& aArray )
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.SetItemsL" )
    __VTPRINT2( DEBUG_GEN, "CVtUiWhiteBalance.SetItemsL=%d", iSupportedModes )
    // Auto mode allways supported
    ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_AUTOMATIC_OPTION );
    iActiveItems.Append( MVtEngCameraPreferences::EAuto );

    if( iSupportedModes & MVtEngCameraPreferences::EDaylight )
        {
        ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_SUNNY_OPTION );
        iActiveItems.Append( MVtEngCameraPreferences::EDaylight );
        }
    if( iSupportedModes & MVtEngCameraPreferences::ECloudy )
        {
        ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_CLOUDY_OPTION );
        iActiveItems.Append( MVtEngCameraPreferences::ECloudy );
        }
    if( iSupportedModes & MVtEngCameraPreferences::ETungsten )
        {
        ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_INCANDESCENT_OPTION );
        iActiveItems.Append( MVtEngCameraPreferences::ETungsten );
        }
    if( iSupportedModes & MVtEngCameraPreferences::EFluorescent )
        {
        ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_FLUORESCENT_OPTION );
        iActiveItems.Append( MVtEngCameraPreferences::EFluorescent );
        }
    __VTPRINTEXIT( "CVtUiWhiteBalance.SetItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::SettingPageResId
// ---------------------------------------------------------------------------
//
TInt CVtUiWhiteBalance::SettingPageResId() const
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.SettingPageResId" )
    __VTPRINTEXIT( "CVtUiWhiteBalance.SettingPageResId" )
    return R_VIDEOTELUI_WHITE_BALANCE_SETTING_PAGE;
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::SettingPageItemChangedL
// ---------------------------------------------------------------------------
//
void CVtUiWhiteBalance::SettingPageItemChangedL( TInt aIndex )
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.SettingPageItemChangedL" )
    __VTPRINT2( DEBUG_GEN, "CVtUiWhiteBalance.index=%d", aIndex )
    if ( iFeatureManager.UiStates().ExecState() == TVtUiStates::EExecStateResetting )
        {
        __VTPRINTEXIT( "CVtUiWhiteBalance.SettingPageItemChangedL" )
        return;
        }
    // Map index to right white balance value
    MVtEngCameraPreferences::TWhiteBalance wb = MapArrayIndexToWBEnum( aIndex );

    // cast the parameter
    TPtrC8 params( reinterpret_cast< TUint8* >( &wb ),
        sizeof( MVtEngCameraPreferences::TWhiteBalance ) );

    // Adjust white balance
    MVtEngMedia::TCameraId camId;
    iFeatureManager.AppUi().Model().Media().GetCurrentCameraId(camId);

    if( camId == MVtEngMedia::ESecondaryCamera  )
        {            
         iFeatureManager.AppUi().DoExecuteCmdL( KVtEngSetWhiteBalance, &params );        
         iPendingSettingChangeCmd = EFalse;
         }
    else
        iPendingSettingChangeCmd = ETrue;
    __VTPRINTEXIT( "CVtUiWhiteBalance.SettingPageItemChangedL" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::CVtUiWhiteBalance
// ---------------------------------------------------------------------------
//
CVtUiWhiteBalance::CVtUiWhiteBalance( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPrefSettingListBase( aFeatureManager, EVtUiFeatureIdWhiteBalance ),
    iComponentState( *this )
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.CVtUiWhiteBalance" )
    __VTPRINTEXIT( "CVtUiWhiteBalance.CVtUiWhiteBalance" )
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::MapWBEnumToArrayIndex
// ---------------------------------------------------------------------------
//
TInt CVtUiWhiteBalance::MapWBEnumToArrayIndex( MVtEngCameraPreferences::
    TWhiteBalance& aWhiteBalance ) const
    {
     __VTPRINTENTER( "CVtUiWhiteBalance.MapWBEnumToArrayIndex" )
    __VTPRINT2( DEBUG_GEN, "CVtUiWhiteBalance.cpunt=%d", iActiveItems.Count() )
    for ( TInt i = 0; i < iActiveItems.Count(); ++i )
         {
         if ( iActiveItems [ i ] ==  aWhiteBalance  )
             {
             __VTPRINT2( DEBUG_GEN, "CVtUiWhiteBalance.index=%d", i )
             __VTPRINTEXIT( "CVtUiWhiteBalance.MapWBEnumToArrayIndex" )
             return i;
             }
         }
     // not found
     __VTPRINTEXIT( "CVtUiWhiteBalance.MapWBEnumToArrayIndexNF" )
     return KErrNotFound;
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::MapArrayIndexToWBEnum
// ---------------------------------------------------------------------------
//
MVtEngCameraPreferences::TWhiteBalance CVtUiWhiteBalance::
    MapArrayIndexToWBEnum( TInt aIndex) const
    {
     __VTPRINTENTER( "CVtUiWhiteBalance.MapArrayIndexToWBEnum" )
     __VTPRINT2( DEBUG_GEN, "CVtUiWhiteBalance.index=%d", aIndex )
    __VTPRINT2( DEBUG_GEN, "CVtUiWhiteBalance.count=%d", iActiveItems.Count() )
    const TInt count = iActiveItems.Count();
    if ( count > 0 && aIndex < count && aIndex >= 0 )
        {
        __VTPRINTEXIT( "CVtUiWhiteBalance.MapArrayIndexToWBEnum" )
        return static_cast< MVtEngCameraPreferences::TWhiteBalance >
            ( iActiveItems[ aIndex ] );
        }
    else // not valid index return first item in the list
        {
        __VTPRINTEXIT( "CVtUiWhiteBalance.MapArrayIndexToWBEnum_ERROR_INDEX" )
        return static_cast< MVtEngCameraPreferences::TWhiteBalance >
            ( iActiveItems[ 0 ] );
        }
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::DoStop
// ---------------------------------------------------------------------------
//
TInt CVtUiWhiteBalance::DoStopL( TAny* aAny )
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.DoStopL" )
    CVtUiWhiteBalance* self = static_cast< CVtUiWhiteBalance* >( aAny );
    if ( self->iFeatureState == MVtUiFeature::EActive )
        {
        __VTPRINT( DEBUG_GEN, "CVtUiWhiteBalance::Stop1" );
        self->iFeatureManager.ComponentManager().
            DeActivateComponentL ( MVtUiComponent::EComponentIdWhiteBalance );
        // set state
        self->iFeatureState = MVtUiFeature::EReady;
        }
    __VTPRINTEXIT( "CVtUiWhiteBalance.DoStopL" )
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CVtUiWhiteBalance::DoStart
// ---------------------------------------------------------------------------
//
TInt CVtUiWhiteBalance::DoStartL( TAny* aAny )
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.DoStart" )
    CVtUiWhiteBalance* self = static_cast< CVtUiWhiteBalance* >( aAny );
    self->CVtUiPrefSettingListBase::StartSettingPageL();
    self->iFeatureManager.UiStates().SetIsCommandActivating( EFalse );
    __VTPRINTEXIT( "CVtUiWhiteBalance.DoStart" )
    return KErrNone;
    }

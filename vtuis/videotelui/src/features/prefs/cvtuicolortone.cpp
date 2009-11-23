/*
* Copyright (c) 2006 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Color tone UI feature implementation.
*
*/


#include    <mvtengmedia.h>
#include    <cvtengmodel.h>
#include    <mvtengcamerapreferences.h>
#include    <cvtlogger.h>
#include    "cvtuicolortone.h"
#include    "tvtuifeatureids.h"
#include    <videotelui.rsg>
#include    "mvtuicomponentmanager.h"
#include    "cvtuifeaturemanager.h"
#include    "CVtUiAppUi.h"
#include	"tvtuilocalvariation.h"
#include    "cvtuifeaturemanager.h"
#include    "tvtuistates.h"
#include    "cvtuicommandmanager.h"

// Implementation of TVtUiColorToneComponentState

// ---------------------------------------------------------------------------
// TVtUiColorToneComponentState::TVtUiColorToneComponentState
// ---------------------------------------------------------------------------
//
TVtUiColorToneComponentState::TVtUiColorToneComponentState(
    MVtUiComponent& aComponent ) :
    TVtUiComponentState( aComponent,
        TVtUiBlockListBitField(
            MVtUiComponent::EComponentIdDialer |
            MVtUiComponent::EComponentIdToolbar |
            MVtUiComponent::EComponentIdNumberEntry ) )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::NewL
// ---------------------------------------------------------------------------
//
CVtUiColorTone* CVtUiColorTone::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "UiColorTone.NewL" )
    CVtUiColorTone* self =
        new ( ELeave ) CVtUiColorTone( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "UiColorTone.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::~CVtUiColorTone
// ---------------------------------------------------------------------------
//
CVtUiColorTone::~CVtUiColorTone()
    {
    __VTPRINTENTER( "UiColorTone.~" )
    // unregister layout change
    iFeatureManager.ComponentManager().ChangeLayoutChangeRegistration(
        *this, MVtUiComponentManager::EUnregister );
     // unregister component
    iFeatureManager.ComponentManager().ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::EUnregister );
    __VTPRINTEXIT( "UiColorTone.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::StartL
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::StartL()
    {
    __VTPRINTENTER( "UiColorTone.StartL" )
    if ( iFeatureState  == MVtUiFeature::EReady )
        {
        iFeatureManager.AppUi().EnableCommandActivatingAndCleanupPushL();
        iFeatureManager.UiStates().SetIsFixedToolbarVisible( EFalse );        
        iFeatureManager.ComponentManager().
            RequestActivationL ( MVtUiComponent::EComponentIdColorTone );
        CleanupStack::Pop(); // EnableCommandActivatingAndCleanupPushL
        // set state
        iFeatureState  = MVtUiFeature::EActive;
        }
    __VTPRINTEXIT( "UiColorTone.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::Stop
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::Stop()
    {
    __VTPRINTENTER( "UiColorTone.Stop" )
    iAsyncCallback->Cancel();
    iAsyncCallback->Set( TCallBack( &DoStopL, this ) );
    iAsyncCallback->CallBack();
    __VTPRINTEXIT( "UiColorTone.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::InitFeatureL()
    {
    __VTPRINTENTER( "UiColorTone.InitFeatureL" )
    CVtUiPrefSettingListBase::InitFeatureL();
    User::LeaveIfError(
       iFeatureManager.ComponentManager().ChangeComponentRegistration(
       iComponentState, MVtUiComponentManager::ERegister ) );
    User::LeaveIfError(
       iFeatureManager.ComponentManager().ChangeLayoutChangeRegistration(
       *this, MVtUiComponentManager::ERegister ) );
    iFeatureState  = EReady;
    __VTPRINTEXIT( "UiColorTone.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::ComponentId
// ---------------------------------------------------------------------------
//
MVtUiComponent::TComponentId CVtUiColorTone::ComponentId() const
    {
    __VTPRINTENTER( "UiColorTone.ComponentId" )
    __VTPRINTEXIT( "UiColorTone.ComponentId" )
    return MVtUiComponent::EComponentIdColorTone;
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::ComponentAsControl
// ---------------------------------------------------------------------------
//
CCoeControl* CVtUiColorTone::ComponentAsControl()
    {
    __VTPRINTENTER( "UiColorTone.ComponentAsControl" )
    __VTPRINTEXIT( "UiColorTone.ComponentAsControl" )
    return NULL;
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::DoActivateL
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::DoActivateL()
    {
    __VTPRINTENTER( "UiColorTone.DoActivateL" )
    // get supported color tone modes
    iCameraPref->GetSupportedColorTones( iSupportedModes );
    __VTPRINT2( DEBUG_GEN, "UiColorTone.ConstructL=%d", iSupportedModes )
    iFeatureManager.UiStates().SetColorToneModeOn( ETrue );
    iAsyncCallback->Cancel();
    iAsyncCallback->Set( TCallBack( &DoStartL, this ) );
    iAsyncCallback->CallBack();
    __VTPRINTEXIT( "UiColorTone.DoActivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::DoDeactivateL
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::DoDeactivateL()
    {
    __VTPRINTENTER( "UiColorTone.DoDeactivateL" )
    iFeatureManager.UiStates().SetColorToneModeOn( EFalse );
    CVtUiPrefSettingListBase::StopSettingPageL();
    __VTPRINTEXIT( "UiColorTone.DoDeactivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::HandleLayoutChangeL
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::HandleLayoutChangeL()
    {
    __VTPRINTENTER( "UiColorTone.HandleLayoutChangeL" )
    if ( iFeatureState  == MVtUiFeature::EActive )
        {
        SizeChanged();
        }
    __VTPRINTEXIT( "UiColorTone.HandleLayoutChangeL" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::CurrentSelection
// ---------------------------------------------------------------------------
//
TInt CVtUiColorTone::CurrentSelection()
    {
    __VTPRINTENTER( "UiColorTone.CurrentSelection" )
    // ask from engine which item is currently active
    MVtEngCameraPreferences::TColorTone wb;
    if ( iCameraPref->GetColorTone( wb ) )
        {
        __VTPRINTEXIT( "UiColorTone.CurrentSelectionERR" )
        // if error occured return 0 i.e. first list item
        return 0;
        }
    __VTPRINTEXIT( "UiColorTone.CurrentSelection" )
    return MapCTEnumToArrayIndex( wb );
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::SetItemsL
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::SetItemsL( CDesCArray& aArray )
    {
    __VTPRINTENTER( "UiColorTone.SetItemsL<" )
    __VTPRINT2( DEBUG_GEN, "UiColorTone.SetItemsL=%d", iSupportedModes )
    // Normal mode allways supported
    ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_CT_NORMAL_OPTION );
    iActiveItems.Append( MVtEngCameraPreferences::ENormal );

    if( iSupportedModes & MVtEngCameraPreferences::ESepia )
        {
        ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_SEPIA_OPTION );
        iActiveItems.Append( MVtEngCameraPreferences::ESepia );
        }
    if( iSupportedModes & MVtEngCameraPreferences::EGrayscale )
        {
        ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_B_AND_W_OPTION );
        iActiveItems.Append( MVtEngCameraPreferences::EGrayscale );
        }
    if( iSupportedModes & MVtEngCameraPreferences::ENegative )
        {
        ReadAndAppendItemL( aArray, R_VIDEOTELUI_QTN_INCAL_NEGATIVE_OPTION );
        iActiveItems.Append( MVtEngCameraPreferences::ENegative );
        }
    __VTPRINTEXIT( "UiColorTone.SetItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::SettingPageResId
// ---------------------------------------------------------------------------
//
TInt CVtUiColorTone::SettingPageResId() const
    {
    __VTPRINTENTER( "UiColorTone.SettingPageResId" )
    __VTPRINTEXIT( "UiColorTone.SettingPageResId" )
    return R_VIDEOTELUI_COLOR_TONE_SETTING_PAGE;
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::SettingPageItemChanged
// ---------------------------------------------------------------------------
//
void CVtUiColorTone::SettingPageItemChangedL( TInt aIndex )
    {
    __VTPRINTENTER( "CVtUiColorTone.SettingPageItemChangedL" )
    __VTPRINT2( DEBUG_GEN, "CVtUiColorTone.index=%d", aIndex )
    if ( iFeatureManager.UiStates().ExecState() == TVtUiStates::EExecStateResetting )
        {
    __VTPRINTEXIT( "CVtUiColorTone.SettingPageItemChangedL" )
        return;
        }
    // Map index to right color tone value
    MVtEngCameraPreferences::TColorTone ct = MapArrayIndexToCTEnum( aIndex );

    // cast the parameter
    TPtrC8 params( reinterpret_cast< TUint8* >( &ct ),
        sizeof( MVtEngCameraPreferences::TColorTone ) );

    // Adjust color tone
  MVtEngMedia::TCameraId currentCamId;
    iFeatureManager.AppUi().Model().Media().GetCurrentCameraId( currentCamId );
    if( currentCamId == MVtEngMedia::ESecondaryCamera  )
        {
        iFeatureManager.AppUi().DoExecuteCmdL( KVtEngSetColorTone, &params );
        iPendingSettingChangeCmd = EFalse;
        }
    else
        iPendingSettingChangeCmd = ETrue;
    __VTPRINTEXIT( "CVtUiColorTone.SettingPageItemChangedL" )
    }


// ---------------------------------------------------------------------------
// CVtUiColorTone::CVtUiColorTone
// ---------------------------------------------------------------------------
//
CVtUiColorTone::CVtUiColorTone( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPrefSettingListBase( aFeatureManager, EVtUiFeatureIdColourTone ),
    iComponentState( *this )
    {
    __VTPRINTENTER( "UiColorTone.UiColorTone" )
    __VTPRINTEXIT( "UiColorTone.UiColorTone" )
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::MapCTEnumToArrayIndex
// ---------------------------------------------------------------------------
//
TInt CVtUiColorTone::MapCTEnumToArrayIndex( MVtEngCameraPreferences::
    TColorTone& aColorTone ) const
    {
    __VTPRINTENTER( "CVtUiColorTone.MapCTEnumToArrayIndex" )
    __VTPRINT2( DEBUG_GEN, "CVtUiColorTone.cpunt=%d", iActiveItems.Count() )
    for ( TInt i = 0; i < iActiveItems.Count(); ++i )
         {
         if ( iActiveItems [ i ] ==  aColorTone  )
             {
             __VTPRINT2( DEBUG_GEN, "CVtUiColorTone.index=%d", i )
             __VTPRINTEXIT( "CVtUiColorTone.MapCTEnumToArrayIndex" )
             return i;
             }
         }
     __VTPRINTEXIT( "CVtUiColorTone.MapCTEnumToArrayIndex" )
     // not found
     return KErrNotFound;
    }
// ---------------------------------------------------------------------------
// CVtUiColorTone::MapArrayIndexToCTEnum
// ---------------------------------------------------------------------------
//
MVtEngCameraPreferences::TColorTone CVtUiColorTone::MapArrayIndexToCTEnum(
    TInt aIndex) const
    {
    __VTPRINTENTER( "TColorTone.MapArrayIndexToCTEnum" )
    __VTPRINT2( DEBUG_GEN, "TColorTone.index=%d", aIndex )
    __VTPRINT2( DEBUG_GEN, "TColorTone.count=%d", iActiveItems.Count() )
    const TInt count = iActiveItems.Count();
    if ( count > 0 && aIndex < count && aIndex >= 0 )
        {
        __VTPRINTEXIT( "TColorTone.MapArrayIndexToCTEnum" )
        return static_cast< MVtEngCameraPreferences::TColorTone >
            ( iActiveItems[ aIndex ] );
        }
    else // not valid index return first item in the list
        {
        __VTPRINTEXIT( "TColorTone.MapArrayIndexToCTEnum_ERROR_INDEX" )
        return static_cast< MVtEngCameraPreferences::TColorTone >
            ( iActiveItems[ 0 ] );
        }
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::DoStop
// ---------------------------------------------------------------------------
//
TInt CVtUiColorTone::DoStopL( TAny* aAny )
    {
    __VTPRINTENTER( "CVtUiColorTone.DoStopL" )
    CVtUiColorTone* self = static_cast< CVtUiColorTone* >( aAny );
    if ( self->iFeatureState  == MVtUiFeature::EActive )
        {
        self->iFeatureManager.ComponentManager().
            DeActivateComponentL ( MVtUiComponent::EComponentIdColorTone );
        // set state
        self->iFeatureState = MVtUiFeature::EReady;
        }
    __VTPRINTEXIT( "CVtUiColorTone.DoStopL" )
    return KErrNone;
    }

// ---------------------------------------------------------------------------
// CVtUiColorTone::DoStart
// ---------------------------------------------------------------------------
//
TInt CVtUiColorTone::DoStartL( TAny* aAny )
    {
    __VTPRINTENTER( "CVtUiColorTone.DoStart" )
    CVtUiColorTone* self = static_cast< CVtUiColorTone* >( aAny );
    self->CVtUiPrefSettingListBase::StartSettingPageL();
    self->iFeatureManager.UiStates().SetIsCommandActivating( EFalse );
    __VTPRINTEXIT( "CVtUiColorTone.DoStart" )
    return KErrNone;
    }

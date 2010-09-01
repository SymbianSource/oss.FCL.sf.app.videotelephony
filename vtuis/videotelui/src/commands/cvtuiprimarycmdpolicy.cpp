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
* Description:  Primary policy class.
*
*/


#include <featmgr.h>
#include <avkon.hrh>
#include <cvtlogger.h>
#include <videotelui.rsg>
#include <avkon.rsg>

#include "cvtuiprimarycmdpolicy.h"
#include "cvtuicmdvalidationactionbase.h"
#include "cvtuicmdcustomvalidationactionbase.h"
#include "tvtuicmdvalidatorcallback.h"
#include "tvtuistates.h"
#include "videotelui.hrh"
#include "tVtuifeaturevariation.h"
#include "CVtUiAppUi.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::NewL
// ---------------------------------------------------------------------------
//
CVtUiPrimaryCmdPolicy* CVtUiPrimaryCmdPolicy::NewL(
    const TVtUiStates& aUiStates, const CVtUiAppUi& aAppUi )
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.NewL" )
    CVtUiPrimaryCmdPolicy* self =
        new ( ELeave ) CVtUiPrimaryCmdPolicy( aUiStates, aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "PrimaryCmdPolicy.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::~CVtUiPrimaryCmdPolicy
// ---------------------------------------------------------------------------
//
CVtUiPrimaryCmdPolicy::~CVtUiPrimaryCmdPolicy()
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.~" )
    __VTPRINTEXIT( "PrimaryCmdPolicy.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateMenuItemsL
// ---------------------------------------------------------------------------
//
void CVtUiPrimaryCmdPolicy::ValidateMenuItemsL(
    CVtUiCmdValidationActionBase& aAction, TInt )
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.ValidateMenuItemsL" )
    aAction.ProcessL(
        TVtUiCmdValidatorCallBack< CVtUiPrimaryCmdPolicy >( *this,
            ValidateMenuCommand ) );
    __VTPRINTEXIT( "PrimaryCmdPolicy.ValidateMenuItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateSoftkeyItemsL
// ---------------------------------------------------------------------------
//
void CVtUiPrimaryCmdPolicy::ValidateSoftkeyItemsL(
    CVtUiCmdValidationActionBase& aAction, TInt )
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.ValidateSoftkeyItemsL" )
    aAction.ProcessL(
        TVtUiCmdValidatorCallBack< CVtUiPrimaryCmdPolicy >( *this,
            ValidateSoftkey ) );
    __VTPRINTEXIT( "PrimaryCmdPolicy.ValidateSoftkeyItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateSoftkeyItemsL
// ---------------------------------------------------------------------------
//
void CVtUiPrimaryCmdPolicy::ValidateToolbarItemsL(
    CVtUiCmdValidationActionBase& aAction, TInt )
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.ValidateToolbarItemsL" )
    aAction.ProcessL(
        TVtUiCmdValidatorCallBack< CVtUiPrimaryCmdPolicy >( *this,
            ValidateToolbarCommand ) );
    __VTPRINTEXIT( "PrimaryCmdPolicy.ValidateToolbarItemsL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::CustomValidationL
// ---------------------------------------------------------------------------
//
void CVtUiPrimaryCmdPolicy::CustomValidationL(
    CVtUiCmdCustomValidationActionBase& aAction, TInt )
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.CustomValidationL" )
    switch ( aAction.CustomTypeId() )
        {
    // Command state validation
    case EVtUiCmdContextTypeExecution:
        aAction.ProcessL( TVtUiCmdValidatorCallBack< CVtUiPrimaryCmdPolicy >(
            *this, ValidateCommandState ) );
        break;

    default:
        __VTPRINT2( DEBUG_GEN,
            "PrimaryCmdPolicy.CustomValidationL unknown typeId = %d",
            aAction.CustomTypeId() );
        break;
        }
    __VTPRINTEXIT( "PrimaryCmdPolicy.CustomValidationL" )
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidatesContext
// ---------------------------------------------------------------------------
//
TBool CVtUiPrimaryCmdPolicy::ValidatesContext(
    const TVtUiCmdContextType& aCtxType ) const
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.ValidatesContext" )

    TBool result( EFalse );

    switch ( aCtxType )
        {
    case EVtUiCmdContextTypeMenu:
    case EVtUiCmdContextTypeSoftkey:
    case EVtUiCmdContextTypeToolbar:
    case EVtUiCmdContextTypeExecution:
        result = ETrue;
        break;

    default:
        break;
        }

    __VTPRINTEXITR( "PrimaryCmdPolicy.ValidatesContext %d", result )

    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::CVtUiPrimaryCmdPolicy
// ---------------------------------------------------------------------------
//
CVtUiPrimaryCmdPolicy::CVtUiPrimaryCmdPolicy( const TVtUiStates& aUiStates,
    const  CVtUiAppUi& aAppUi )
    : CVtUiCmdValidatorBase( EVtUiCmdPolicyPriorityPrimary ),
      iUiStates( aUiStates ), iAppUi( aAppUi )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiPrimaryCmdPolicy::ConstructL()
    {
    TVtUiActiveIdleVariation activeIdleVariation;
    iAIEnabled = activeIdleVariation.IsActiveIdleEnabled();
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateMenuCommand
// ---------------------------------------------------------------------------
//
TBool CVtUiPrimaryCmdPolicy::ValidateMenuCommand( TInt aCommandId ) const
    {
    TBool handled;
    return ValidateCommand( aCommandId, handled );
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateSoftkey
// ---------------------------------------------------------------------------
//
TBool CVtUiPrimaryCmdPolicy::ValidateSoftkey( TInt aResourceId ) const
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.ValidateSoftkey" )
    TBool result( EFalse );
    switch ( aResourceId )
        {
    case R_VIDEOTELUI_SOFTKEYS_EMPTY_ACTIVE_COMMAND:
        result = iUiStates.IsCommandActivating();
        break;

    case R_VIDEOTELUI_SOFTKEYS_EMPTY_DIALEREXIT:
        result = iUiStates.IsDialerActivating();
        break;

    case R_VIDEOTELUI_SOFTKEYS_SHARE_OBJECT_IMAGE:
        result = iUiStates.MediaState().IsSharing();
        break;

    case R_VIDEOTELUI_SOFTKEYS_CAPTURE_VIDEO:
        result = iUiStates.IsCaptureModeOn();
        break;

    case R_VIDEOTELUI_SOFTKEYS_ENABLE_AUDIO:
        result = !iUiStates.AudioState().IsAudio();
        break;

    case R_VIDEOTELUI_SOFTKEYS_ENABLE_VIDEO:
        result = !iUiStates.MediaState().IsVideo() &&
            iUiStates.MediaState().HasCamera() &&
            ( iUiStates.ExecState() == TVtUiStates::EExecStateRunning );
        break;

    case R_VIDEOTELUI_SOFTKEYS_DIALER:
    case R_VIDEOTELUI_SOFTKEYS_BT_HANDSFREE:
    case R_VIDEOTELUI_SOFTKEYS_LOUDSPEAKER:
    case R_VIDEOTELUI_SOFTKEYS_HANDSET_B:
        {
        if ( FeatureManager::FeatureSupported( KFeatureIdOnScreenDialer ) &&
             ( iUiStates.ExecState() == TVtUiStates::EExecStateRunning ) )
            {
            switch ( aResourceId )
                {
            case R_VIDEOTELUI_SOFTKEYS_DIALER:
                result = ETrue;
                break;
                }
            }
        else
            {
            switch ( aResourceId )
                {
            case R_VIDEOTELUI_SOFTKEYS_BT_HANDSFREE:
                result = iUiStates.AudioState().CanActivateBtHf();
                break;

            case R_VIDEOTELUI_SOFTKEYS_LOUDSPEAKER:
                result = iUiStates.AudioState().CanActivateLoudspeaker();
                break;

            case R_VIDEOTELUI_SOFTKEYS_HANDSET_B:
                result = iUiStates.AudioState().CanDeactivateLoudspeaker();
                break;
                }
            }
        }
        break;

    case R_VIDEOTELUI_SOFTKEYS_END_CALL:
        result = ETrue;
        break;
        }
    __VTPRINTEXITR( "PrimaryCmdPolicy.ValidateSoftkey %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateToolbarCommand
// ---------------------------------------------------------------------------
//
TBool CVtUiPrimaryCmdPolicy::ValidateToolbarCommand( TInt aCommandId ) const
    {
     __VTPRINTENTER( "PrimaryCmdPolicy.ValidateToolbarCommand" )
    __VTPRINT2( DEBUG_GEN, "cmdId = %d", aCommandId )
    TBool result( ETrue );
    switch( aCommandId )
        {
        case EVtUiCmdZoom:
        case EVtUiCmdShareObjectImage:
        case EVtUiCmdSwapImagesPlaces:
        //case EVtUiCmdSnapshot:

            result = EFalse;
            break;

        default:
            result = ValidateMenuCommand( aCommandId );
            break;
        }
    __VTPRINTEXITR( "PrimaryCmdPolicy.ValidateToolbarCommand %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateCommandState
// ---------------------------------------------------------------------------
//
TBool CVtUiPrimaryCmdPolicy::ValidateCommandState( TInt aCommandId ) const
    {
     __VTPRINTENTER( "PrimaryCmdPolicy.ValidateCommandState" )
    TBool handled;
    TBool allowed( !ValidateCommand( aCommandId, handled ) );
    if ( !handled )
        {
        switch ( aCommandId )
            {
        case EVtUiCmdCapture:
        case EVtUiCmdCancelCapture:
            allowed = iUiStates.IsCaptureModeOn();
            break;

        case EVtUiCmdStopSharingObjectImage:
            allowed = iUiStates.MediaState().IsSharing() &&
                !iUiStates.MediaState().IsVideoPermanentlyStopped();
            break;

        default:
            allowed = ETrue;
            break;
            }
        }
    __VTPRINTEXITR( "PrimaryCmdPolicy.ValidateCommandState %d", allowed )
    return allowed;
    }

// ---------------------------------------------------------------------------
// CVtUiPrimaryCmdPolicy::ValidateCommand
// ---------------------------------------------------------------------------
//
TBool CVtUiPrimaryCmdPolicy::ValidateCommand( TInt aCommandId,
    TBool& aHandled ) const
    {
    __VTPRINTENTER( "PrimaryCmdPolicy.ValidateCommand" )

    __VTPRINT2( DEBUG_GEN, "    cmdId = %d", aCommandId )

    TBool result( ETrue );

    aHandled = ETrue;

    const TVtUiMediaState& mediaState( iUiStates.MediaState() );
    const TVtUiAudioState& audioState( iUiStates.AudioState() );
    const TBool disabledVideo( !mediaState.IsVideo() ||
        mediaState.IsSharing() );
    const TBool disabledAudio( !audioState.IsAudio() );
    const TBool disableVideoOptions( !mediaState.HasCamera() );
    const TBool freezeSupported( mediaState.IsFreezeSupported() );
    const TBool frozen( mediaState.IsFrozen() );

    const TBool videoPermStopped( mediaState.IsVideoPermanentlyStopped() );
    const TBool audioPermStopped( audioState.IsAudioPermanentlyStopped() );

    switch( aCommandId )
        {
    case EVtUiCmdSnapshot:
        result = ( disabledVideo && !frozen ) ||
                   disableVideoOptions ||
                   !freezeSupported;
        break;

    case EVtUiCmdUsePrimaryCamera:
        result = mediaState.IsPrimaryCameraInUse() || frozen ||
            !mediaState.HasPrimaryCamera() || mediaState.IsSharing() ||
            videoPermStopped;
        break;

    case EVtUiCmdUseSecondaryCamera:
        result = mediaState.IsSecondaryCameraInUse() || frozen ||
            !mediaState.HasSecondaryCamera() || mediaState.IsSharing() ||
            videoPermStopped;
        break;

    case EVtUiCmdDeactivateBT:
        result = !audioState.CanDeactivateBtHf();
        break;

    case EVtUiCmdSwitchFromBTToIHF:
        result = !audioState.CanDeactivateBtHf() ||
            !audioState.CanActivateLoudspeaker();
        break;

    case EVtUiCmdActivateBT:
        result = !audioState.CanActivateBtHf();
        break;

    case EVtUiCmdDeactivateLoudspeaker:
        result = !audioState.CanDeactivateLoudspeaker();
        break;

    case EVtUiCmdActivateLoudspeaker:
        result = !audioState.CanActivateLoudspeaker();
        break;

    case EVtUiCmdSwapImagesPlaces:
        // Swap image places is always shown in menu.
        result = EFalse;
        break;

    case EVtUiCmdAdjustVideo:
        // Adjust video is always shown in menu.
        result = EFalse;
        break;

    case EVtUiCmdAdjustVideoVideoQuality:
        result = EFalse;
        break;

    case EVtUiCmdAdjustVideoWhiteBalance:
        result = !iUiStates.IsWhiteBalanceSettingAvailable() || frozen;
        break;

    case EVtUiCmdAdjustVideoBrightness:
          result =!iUiStates.IsBrightnessSettingAvailable() || frozen;
        break;

    case EVtUiCmdAdjustVideoContrast:
        result =!iUiStates.IsContrastSettingAvailable() || frozen;
        break;

    case EVtUiCmdAdjustVideoColourTone:
        result = !iUiStates.IsColorToneSettingAvailable() || frozen;

        break;
    case EVtUiCmdZoom:
        result = frozen || disableVideoOptions || disabledVideo;
        break;

    case EVtUiCmdCreateVoice:
        // Downgrading to voice call is not possible if remote end MSISDN
        // is unavailable or there is waiting call.
        result = !iUiStates.IsCLIReceived() || iUiStates.IsWaitingCall();
        break;

    case EVtUiCmdGoToIdle:
#ifndef RD_BOOT_CUSTOMIZABLE_AI
        result = !iAIEnabled;
#else
        // When RD_BOOT_CUSTOMIZABLE_AI is defined, active idle is always
        // shown in menu
        // result = EFalse;
        // disable the go to idle when autolock is on.
        result = iUiStates.IsDeviceLockOn();
#endif //RD_BOOT_CUSTOMIZABLE_AI
        break;

    case EAknCmdHelp:
    	{
    	TVtUiHelpVariation hlpvariation;
        result = !hlpvariation.IsHelpSupported();
        }
        break;

    case EAknCmdExit:
        // Exit option is disabled by default. Change ETrue to EFalse
        // and it is in the menu.
        break;

    case EVtUiCmdEndActiveCall:
        // End active call always shown in menu.
        result = EFalse;
        break;

    case EVtUiCmdShareObjectImage:
        result = frozen || mediaState.IsNotAbleToShare() ||
            mediaState.IsInitializingShare() || videoPermStopped ||
            iAppUi.IsActiveCommand( EVtUiCmdShareObjectImage );
        break;

    case EVtUiCmdEnableMain:
        result = (  iAppUi.IsActiveCommand( EVtUiCmdEnableVideo ) ||
                    iAppUi.IsActiveCommand( EVtUiCmdDisableVideo ) ||
                 !disabledVideo || disableVideoOptions || videoPermStopped )
                  && ( iAppUi.IsActiveCommand ( EVtUiCmdEnableAudio ) ||
                  !disabledAudio || audioPermStopped );
        break;

    case EVtUiCmdEnableVideo:
        result = !disabledVideo || disableVideoOptions ||
            videoPermStopped;
        break;

    case EVtUiCmdEnableAudio:
        result = !disabledAudio || audioPermStopped;
        break;

    case EVtUiCmdEnableBoth:
        result = !disabledVideo || !disabledAudio || disableVideoOptions ||
            videoPermStopped || audioPermStopped;
        break;

    case EVtUiCmdDisableMain:
        result = ( iAppUi.IsActiveCommand( EVtUiCmdDisableVideo ) ||
                   iAppUi.IsActiveCommand( EVtUiCmdEnableVideo ) ||
                 disabledVideo || disableVideoOptions || videoPermStopped ) &&
                ( iAppUi.IsActiveCommand( EVtUiCmdDisableAudio ) ||
                disabledAudio || audioPermStopped );
        break;

    case EVtUiCmdDisableVideo:
        result = disabledVideo || disableVideoOptions || videoPermStopped;
        break;

    case EVtUiCmdDisableAudio:
        result = disabledAudio || audioPermStopped;
        break;

    case EVtUiCmdDisableBoth:
        result = disableVideoOptions || disabledVideo || disabledAudio ||
            videoPermStopped || audioPermStopped;
        break;

    case EVtUiCmdSendDTMF:
        if ( FeatureManager::FeatureSupported( KFeatureIdOnScreenDialer ) )
            {
            result = EFalse;
            }
        else
            {
            result = ETrue;
            }
        break;

    default:
        aHandled = EFalse;
        break;
        }

    __VTPRINTEXITR( "PrimaryCmdPolicy.ValidateCommand %d", result )

    return result;
    }


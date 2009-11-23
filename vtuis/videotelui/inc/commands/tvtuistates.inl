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
* Description:  UI states class inline methods.
*
*/


// -----------------------------------------------------------------------------
// TVtUiStates::MediaState
// -----------------------------------------------------------------------------
//
const TVtUiMediaState& TVtUiStates::MediaState() const
    {
    return iMediaState;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::AudioState
// -----------------------------------------------------------------------------
//
const TVtUiAudioState& TVtUiStates::AudioState() const
    {
    return iAudioState;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetCLIReceived
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetCLIReceived( TBool aSet )
    {
    aSet ? SetFlag( EIsCLIReceived ) : ClearFlag( EIsCLIReceived );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsCLIReceived
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsCLIReceived() const
    {
    return IsFlag( EIsCLIReceived );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetLayoutChangeNeeded
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetLayoutChangeNeeded( TBool aSet )
    {
    aSet ? SetFlag( EIsLayoutChangeNeeded ) :
        ClearFlag( EIsLayoutChangeNeeded );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsLayoutChangeNeeded
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsLayoutChangeNeeded() const
    {
    return IsFlag( EIsLayoutChangeNeeded );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetBlankControlAdded
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetBlankControlAdded( TBool aSet )
    {
    aSet ? SetFlag( EIsBlankControlAdded ) :
        ClearFlag( EIsBlankControlAdded );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsBlankControlAdded
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsBlankControlAdded() const
    {
    return IsFlag( EIsBlankControlAdded );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetLaunchOkOptionsMenu
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetLaunchOkOptionsMenu( TBool aSet )
    {
    aSet ? SetFlag( EIsLaunchOkOptionsMenu ) :
        ClearFlag( EIsLaunchOkOptionsMenu );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsLaunchOkOptionsMenu
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsLaunchOkOptionsMenu() const
    {
    return IsFlag( EIsLaunchOkOptionsMenu );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetDeviceLockOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetDeviceLockOn( TBool aSet )
    {
    aSet ? SetFlag( EIsDeviceLockOn ) :
        ClearFlag( EIsDeviceLockOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsDeviceLockOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsDeviceLockOn() const
    {
    return IsFlag( EIsDeviceLockOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetDetailsReceived
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetDetailsReceived( TBool aSet )
    {
    aSet ? SetFlag( EDetailsReceived ) :
        ClearFlag( EDetailsReceived );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsDetailsReceived
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsDetailsReceived() const
    {
    return IsFlag( EDetailsReceived );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetWaitingForFirstFrame
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetWaitingForFirstFrame( TBool aSet )
    {
    aSet ? SetFlag( EWaitingForFirstFrame ) :
        ClearFlag( EWaitingForFirstFrame );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsWaitingForFirstFrame
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsWaitingForFirstFrame() const
    {
    return IsFlag( EWaitingForFirstFrame );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetUseSQCif
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetUseSQCif( TBool aSet )
    {
    aSet ? SetFlag( EUseSQCif ) :
        ClearFlag( EUseSQCif );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsUseSQCif
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsUseSQCif() const
    {
    return IsFlag( EUseSQCif );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetViewFindersInitialPlaceContextPane
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetViewFindersInitialPlaceContextPane( TBool aSet )
    {
    aSet ? SetFlag( EViewFindersInitialPlaceContextPane ) :
        ClearFlag( EViewFindersInitialPlaceContextPane );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsViewFindersInitialPlaceContextPane
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsViewFindersInitialPlaceContextPane() const
    {
    return IsFlag( EViewFindersInitialPlaceContextPane );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetViewFinderToMainPane
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetViewFinderToMainPane( TBool aSet )
    {
    aSet ? SetFlag( EViewFinderToMainPane ) :
        ClearFlag( EViewFinderToMainPane );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsViewFinderToMainPane
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsViewFinderToMainPane() const
    {
    return IsFlag( EViewFinderToMainPane );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetCaptureModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetCaptureModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsCaptureModeOn ) :
        ClearFlag( EIsCaptureModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsCaptureModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsCaptureModeOn() const
    {
    return IsFlag( EIsCaptureModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetThisApplicationForeground
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetThisApplicationForeground( TBool aSet )
    {
    aSet ? SetFlag( EIsThisApplicationForeground ) :
        ClearFlag( EIsThisApplicationForeground );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsThisApplicationForeground
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsThisApplicationForeground() const
    {
    return IsFlag( EIsThisApplicationForeground );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetDisableBlindSetting
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetDisableBlindSetting( TBool aSet )
    {
    aSet ? SetFlag( EIsDisableBlindSetting ) :
        ClearFlag( EIsDisableBlindSetting );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsDisableBlindSetting
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsDisableBlindSetting() const
    {
    return IsFlag( EIsDisableBlindSetting );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetExecShowCameraInUse
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetExecShowCameraInUse( TBool aSet )
    {
    aSet ? SetFlag( EExecShowCameraInUse ) :
        ClearFlag( EExecShowCameraInUse );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsExecShowCameraInUse
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsExecShowCameraInUse() const
    {
    return IsFlag( EExecShowCameraInUse );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsZoomModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsZoomModeOn() const
    {
    return IsFlag( EIsZoomModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetZoomModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetZoomModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsZoomModeOn ) :
        ClearFlag( EIsZoomModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsWhiteBalanceModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsWhiteBalanceModeOn() const
    {
    return IsFlag( EIsWhiteBalanceModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetWhiteBalanceModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetWhiteBalanceModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsWhiteBalanceModeOn ) :
        ClearFlag( EIsWhiteBalanceModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsColorToneModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsColorToneModeOn() const
    {
    return IsFlag( EIsColorToneModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetColorToneModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetColorToneModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsColorToneModeOn ) :
        ClearFlag( EIsColorToneModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsBrightnessModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsBrightnessModeOn() const
    {
    return IsFlag( EIsBrightnessModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetBrightnessModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetBrightnessModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsBrightnessModeOn ) :
        ClearFlag( EIsBrightnessModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsContrastModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsContrastModeOn() const
    {
    return IsFlag( EIsContrastModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetContrastModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetContrastModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsContrastModeOn ) :
        ClearFlag( EIsContrastModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetIsNumberEntryOpen
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetIsNumberEntryOpen( TBool aSet )
    {
    aSet ? SetFlag( EIsNumberEntryOpen ) :
        ClearFlag( EIsNumberEntryOpen );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsNumberEntryOpen
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsNumberEntryOpen() const
    {
    return IsFlag( EIsNumberEntryOpen );
    }


// -----------------------------------------------------------------------------
// TVtUiStates::SetIsToolbarAvailable
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetIsToolbarAvailable( TBool aSet )
    {
    aSet ? SetFlag( EIsToolbarAvailable ) :
        ClearFlag( EIsToolbarAvailable );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsToolbarAvailable
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsToolbarAvailable() const
    {
    return IsFlag( EIsToolbarAvailable );
    }

// -----------------------------------------------------------------------------
// TVtUiStates:::SetWaitingCall
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetWaitingCall( TBool aSet )
    {
    aSet ? SetFlag( EIsWaitingCall ) :
        ClearFlag( EIsWaitingCall );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsWaitingCall
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsWaitingCall() const
    {
    return IsFlag( EIsWaitingCall );
    }

// -----------------------------------------------------------------------------
// TVtUiStates:::SetSelectingShare
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetSelectingShare( TBool aSet )
    {
    aSet ? SetFlag( EIsSelectingShare ) :
        ClearFlag( EIsSelectingShare );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsSelectingShare
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsSelectingShare() const
    {
    return IsFlag( EIsSelectingShare );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetIsDialerOpen
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetIsDialerOpen( TBool aSet )
    {
    aSet ? SetFlag( EIsDialerOpen ) :
        ClearFlag( EIsDialerOpen );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsDialerOpen
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsDialerOpen() const
    {
    return IsFlag( EIsDialerOpen );
    }


// -----------------------------------------------------------------------------
// TVtUiStates::SetIsFixedToolbarVisible
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetIsFixedToolbarVisible( TBool aSet )
    {
    aSet ? SetFlag( EIsFixedToolbarVisible ) :
        ClearFlag( EIsFixedToolbarVisible );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsFixedToolbarVisible
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsFixedToolbarVisible() const
    {
    return IsFlag( EIsFixedToolbarVisible );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetIsDialerActivating
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetIsDialerActivating( TBool aSet )
    {
    aSet ? SetFlag( EIsDialerActivating ) :
        ClearFlag( EIsDialerActivating );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsDialerActivating
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsDialerActivating() const
    {
    return IsFlag( EIsDialerActivating );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsCommandActivating
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsCommandActivating() const
    {
    return iCommandActivatingRefCount > 0;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsVolumeModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsVolumeModeOn() const
    {
    return IsFlag( EIsVolumeModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetVolumeModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetVolumeModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsVolumeModeOn ) :
        ClearFlag( EIsVolumeModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetIsFloatingToolbarVisible
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetIsFloatingToolbarVisible( TBool aSet )
    {
    aSet ? SetFlag( EIsFloatingToolbarVisible ) :
        ClearFlag( EIsFloatingToolbarVisible );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsFloatingToolbarVisible
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsFloatingToolbarVisible() const
    {
    return IsFlag( EIsFloatingToolbarVisible );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsVideoQualityModeOn
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsVideoQualityModeOn() const
    {
    return IsFlag( EIsVideoQualityModeOn );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetVideoQualityModeOn
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetVideoQualityModeOn( TBool aSet )
    {
    aSet ? SetFlag( EIsVideoQualityModeOn ) :
        ClearFlag( EIsVideoQualityModeOn );
    }
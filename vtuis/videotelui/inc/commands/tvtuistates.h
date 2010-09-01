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
* Description:  UI states class definition.
*
*/


#ifndef T_VTUISTATES_H
#define T_VTUISTATES_H

#include <e32base.h>

#include "tvtuimediastate.h"
#include "tvtuiaudiostate.h"

class CVtEngModel;
class MVtEngCameraPreferences;

/**
 *  TVtUiStates
 *
 *  Contains information about Application UI's current status.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiStates ) : public TVtFlagContainer
    {

public: // enumerations

    /**
    * Application execution state (will be set by the app state classes)
    */
    enum TVtUiExecState
        {
        EExecStateStarting,
        EExecStateRunning,
        EExecStateResetting,
        EExecStateFinalized
        };

public:

    /**
     * Constructor.
     */
    TVtUiStates( CVtEngModel& aModel );

    /**
     * Updates UI states.
     */
    void Update();

    /**
     * Return whether or not ColorToneSetting
     * is supported by current camera.
     *
     * @return ETrue if at least one color tone setting is available,
     * EFalse otherwise.
     */
    TBool IsColorToneSettingAvailable() const;

    /**
     * Return whether or not WhiteBalanceSetting
     * is supported by current camera.
     *
     * @return ETrue if at least one white balance setting is available,
     * EFalse otherwise.
     */
    TBool IsWhiteBalanceSettingAvailable() const;

    /**
     * Return whether or not ontrast setting
     * is supported by current camera.
     *
     * @return ETrue if at contrast setting is available,
     * EFalse otherwise.
     */
    TBool IsContrastSettingAvailable() const;

    /**
     * Return whether or not brightness setting
     * is supported by current camera.
     *
     * @return ETrue if brightness setting is available,
     * EFalse otherwise.
     */
    TBool IsBrightnessSettingAvailable() const;

    /**
     * Returns reference to media state object
     *
     * @return Reference to media state object.
     */
    inline const TVtUiMediaState& MediaState() const;

    /**
     * Returns reference to audio state object
     *
     * @return Reference to audio state object.
     */
    inline const TVtUiAudioState& AudioState() const;

    /**
     * Sets or clears EIsCLIReceived
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetCLIReceived( TBool aSet );

    /**
     * Check if EIsCLIReceived is set
     *
     * @return ETrue if EIsCLIReceived is set EFalse otherwise
     */
    inline TBool IsCLIReceived() const;

    /**
     * Sets or clears EIsLayoutChangeNeeded
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetLayoutChangeNeeded( TBool aSet );

    /**
     * Check if EIsLayoutChangeNeeded is set
     *
     * @return ETrue if EIsLayoutChangeNeeded is set EFalse otherwise
     */
    inline TBool IsLayoutChangeNeeded() const;

    /**
     * Sets or clears EIsBlankControlAdded
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetBlankControlAdded( TBool aSet );

    /**
     * Check if EIsBlankControlAdded is set
     *
     * @return ETrue if EIsBlankControlAdded is set EFalse otherwise
     */
    inline TBool IsBlankControlAdded() const;

    /**
     * Sets or clears EIsLaunchOkOptionsMenu
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetLaunchOkOptionsMenu( TBool aSet );

    /**
     * Check if EIsLaunchOkOptionsMenu is set
     *
     * @return ETrue if EIsLaunchOkOptionsMenu is set EFalse otherwise
     */
    inline TBool IsLaunchOkOptionsMenu() const;

    /**
     * Sets or clears EIsDeviceLockOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetDeviceLockOn( TBool aSet );

    /**
     * Check if EIsDeviceLockOn is set
     *
     * @return ETrue if EIsDeviceLockOn is set EFalse otherwise
     */
    inline TBool IsDeviceLockOn() const;

    /**
     * Sets or clears EDetailsReceived
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetDetailsReceived( TBool aSet );

    /**
     * Check if EDetailsReceived is set
     *
     * @return ETrue if EDetailsReceived is set EFalse otherwise
     */
    inline TBool IsDetailsReceived() const;

    /**
     * Sets or clears EWaitingForFirstFrame
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetWaitingForFirstFrame( TBool aSet );

    /**
     * Check if EWaitingForFirstFrame is set
     *
     * @return ETrue if EWaitingForFirstFrame is set EFalse otherwise
     */
    inline TBool IsWaitingForFirstFrame() const;

    /**
     * Sets or clears EUseSQCif
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetUseSQCif( TBool aSet );

    /**
     * Check if EUseSQCif is set
     *
     * @return ETrue if EUseSQCif is set EFalse otherwise
     */
    inline TBool IsUseSQCif() const;

    /**
     * Sets or clears EIsViewFindersInitialPlaceContextPane
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetViewFindersInitialPlaceContextPane( TBool aSet );

    /**
     * Check if EIsViewFindersInitialPlaceContextPane is set
     *
     * @return ETrue if EIsViewFindersInitialPlaceContextPane is set EFalse
     * otherwise
     */
    inline TBool IsViewFindersInitialPlaceContextPane() const;

    /**
     * Sets or clears EViewFinderToMainPane
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetViewFinderToMainPane( TBool aSet );

    /**
     * Check if EViewFinderToMainPane is set
     *
     * @return ETrue if EViewFinderToMainPane is set EFalse otherwise
     */
    inline TBool IsViewFinderToMainPane() const;

    /**
     * Sets or clears EIsCaptureModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetCaptureModeOn( TBool aSet );

    /**
     * Check if EIsCaptureModeOn is set
     *
     * @return ETrue if EIsCaptureModeOn is set EFalse otherwise
     */
    inline TBool IsCaptureModeOn() const;

    /**
     * Sets or clears EIsThisApplicationForeground
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetThisApplicationForeground( TBool aSet );

    /**
     * Check if EIsThisApplicationForeground is set
     *
     * @return ETrue if EIsThisApplicationForeground is set EFalse otherwise
     */
    inline TBool IsThisApplicationForeground() const;

    /**
     * Sets or clears EIsDisableBlindSetting
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetDisableBlindSetting( TBool aSet );

    /**
     * Check if EIsDisableBlindSetting is set
     *
     * @return ETrue if EIsDisableBlindSetting is set EFalse otherwise
     */
    inline TBool IsDisableBlindSetting() const;

    /**
     * Sets or clears EExecShowCameraInUse
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetExecShowCameraInUse( TBool aSet );

    /**
     * Check if EExecShowCameraInUse is set
     *
     * @return ETrue if EExecShowCameraInUse is set EFalse otherwise
     */
    inline TBool IsExecShowCameraInUse() const;

     /**
     * Check if EIsZoomModeOn is set
     *
     * @return ETrue if EIsZoomModeOn is set EFalse otherwise
     */
    inline TBool IsZoomModeOn() const;

    /**
     * Sets or clears EIsZoomModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetZoomModeOn( TBool aSet );

    /**
    * Check if EIsWhiteBalanceModeOn is set
    *
    * @return ETrue if EIsWhiteBalanceModeOn is set EFalse otherwise
    */
    inline TBool IsWhiteBalanceModeOn() const;

    /**
     * Sets or clears EIsWhiteBalanceModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetWhiteBalanceModeOn( TBool aSet );

    /**
    * Check if EIsColorToneModeOn is set
    *
    * @return ETrue if EIsColorToneModeOn is set EFalse otherwise
    */
    inline TBool IsColorToneModeOn() const;

    /**
     * Sets or clears EIsColorToneModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetColorToneModeOn( TBool aSet );

    /**
    * Check if EBrightnessModeOn is set
    *
    * @return ETrue if EBrightnessModeOn is set EFalse otherwise
    */
    inline TBool IsBrightnessModeOn() const;

    /**
     * Sets or clears EBrightnessModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetBrightnessModeOn( TBool aSet );

    /**
     *  Check if EContrastModeOn is set
     *
     *  @return ETrue if EContrastModeOn is set EFalse otherwise
     */
    inline TBool IsContrastModeOn() const;

    /**
     * Sets or clears EContrastModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetContrastModeOn( TBool aSet );

    /**
     * Sets or clears EIsNumberEntryOpen
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetIsNumberEntryOpen( TBool aSet );

    /**
     * Check if EIsNumberEntryOpen is set
     *
     * @return ETrue if EIsNumberEntryOpen is set EFalse otherwise
     */
    inline TBool IsNumberEntryOpen() const;

    /**
     * Sets or clears EIsToolbarAvailable
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetIsToolbarAvailable( TBool aSet );

    /**
     * Check if IsToolbarAvailable is set
     *
     * @return ETrue if IsToolbarAvailable is set EFalse otherwise
     */
    inline TBool IsToolbarAvailable() const;

    /**
     * Sets or clears EIsWaitingCall
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetWaitingCall( TBool aSet );

	/**
     * Check if there is waiting video/voice call.
     *
     * @return ETrue if waiting call is ongoing, EFalse otherwise
     */
    inline TBool IsWaitingCall() const;

     /**
     * Sets or clears EIsSelectingShare
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
     inline void SetSelectingShare( TBool aSet );

	/**
     * Check if user is selecting file to be shared.
     *
     * @return ETrue if user is selecting file, EFalse otherwise
     */
    inline TBool IsSelectingShare() const;

     /**
     * Sets or clears EIsDialerOpen
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetIsDialerOpen( TBool aSet );

	/**
     * Check if video DTMF dialer is open.
     *
     * @return ETrue if dialer is open, EFalse otherwise
     */
    inline TBool IsDialerOpen() const;

    /**
     * Sets or clears EIsFixedToolbarVisible
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetIsFixedToolbarVisible( TBool aSet );

	/**
     * Check if fixed toolbar is visible.
     *
     * @return ETrue iftoolbar is visible, EFalse otherwise
     */
    inline TBool IsFixedToolbarVisible() const;

    /**
     * Sets or clears EIsDialerActivating
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetIsDialerActivating( TBool aSet );

	/**
     * Check if dialer is being activated
     *
     * @return ETrue if dialer is being activated, EFalse otherwise
     */
    inline TBool IsDialerActivating() const;

    /**
     * Adjusts command activating reference count
     *
     * @param aSet ETrue if setting will be increased, EFalse if
     * decreased.
     */
    void SetIsCommandActivating( TBool aSet );

	/**
     * Check if command activating ref.count is greater than zero
     *
     * @return ETrue if any command is being activated, EFalse otherwise
     */
    inline TBool IsCommandActivating() const;

    /**
     *  Check if EIsVolumeModeOn is set
     *
     *  @return ETrue if EIsVolumeModeOn is set EFalse otherwise
     */
    inline TBool IsVolumeModeOn() const;

    /**
     * Sets or clears EIsVolumeModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetVolumeModeOn( TBool aSet );

    /**
     *  Check if EIsVideoQualityModeOn is set
     *
     *  @return ETrue if EIsVideoQualityModeOn is set EFalse otherwise
     */
    inline TBool IsVideoQualityModeOn() const;

    /**
     * Sets or clears EIsVideoQualityModeOn
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
     
    inline void SetVideoQualityModeOn( TBool aSet );    
    /**
     * Sets or clears EIsFloatingToolbarVisible
     *
     * @param aSet ETrue if setting will be set, EFalse otherwise.
     */
    inline void SetIsFloatingToolbarVisible( TBool aSet );

    /**
     * Check if floating toolbar is visible.
     *
     * @return ETrue iftoolbar is visible, EFalse otherwise
     */
    inline TBool IsFloatingToolbarVisible() const;

    /**
    * Returns application's execution state.
    * @return Application's current execution state.
    */
    TVtUiExecState ExecState() const;

private: // methods to be accessed only by certain classes (see friends)

    /**
    * Sets application's execution state.
    * @param aState Application's new execution state.
    */
    void SetExecState( const TVtUiExecState aState );

private:

    // Enumeration for ui state flags.
    enum TFlags
        {
        /** Set if CLI is received */
        EIsCLIReceived = ( 1<<0 ),

        /** Set if layout change is needed */
        EIsLayoutChangeNeeded = ( 1<<1 ),

        /** Set if blank control has been added to control stack */
        EIsBlankControlAdded = ( 1<<2 ),

        /** Set if launch ok in options menu */
        EIsLaunchOkOptionsMenu = ( 1<<3 ),

        /** Set if device lock is on */
        EIsDeviceLockOn = ( 1<<4 ),

        /** Set if details have been received */
        EDetailsReceived = ( 1<<5 ),

        /** Set if waiting for first frame */
        EWaitingForFirstFrame = ( 1<<6 ),

        /** Set if SQCIF is being used */
        EUseSQCif = ( 1 << 7 ),

        /** Set if images was in context pane before freeze, unset if not */
        EViewFindersInitialPlaceContextPane = ( 1<<8 ),

        /** Set if viewfinder has to be moved to mainpane, when imageshare is
            ready */
        EViewFinderToMainPane = ( 1<<9 ),

        /** Set if capture mode is on, unset if off */
        EIsCaptureModeOn = ( 1<<10 ),

        /** Set if application on foreground */
        EIsThisApplicationForeground = ( 1<<11 ),

        /** Set if blind setting should be temporarily disabled.
            This is used in preventing blind bitmap from flashing
            while operations involving multiple engine commands/events
            take place (e.g. 'Swap image places' and layout switch). */
        EIsDisableBlindSetting = ( 1<<12 ),

        /** Set if camera in use note should be shown. */
        EExecShowCameraInUse = ( 1<<13 ),

        /** Set if zooming slider indicators is shown in navi pane.
            Toolbar also dims other toolbar controls except zoom
            mode control.*/
        EIsZoomModeOn = ( 1<<14 ),

        /** Set if contrast mode is on, unset if off */
        EIsContrastModeOn = ( 1<<15 ),

        /** Set if brightness mode is on, unset if off */
        EIsBrightnessModeOn = ( 1<<16 ),

        /** Set if number entry is open in UI (do not use this flag in new code)
         */
        EIsNumberEntryOpen = ( 1<<17 ),

        /** Set if toolbar is available in UI */
        EIsToolbarAvailable = ( 1<<18 ),

		/** Set if waiting call exists */
        EIsWaitingCall = ( 1<<19 ),

        /** Set if initializing share */
        EIsSelectingShare = ( 1<<20 ),

        /** Set if initializing share */
        EIsDialerOpen = ( 1<<21 ),

        /** Set if white balance mode is on, unset if off */
        EIsWhiteBalanceModeOn = ( 1<<22 ),

        /** Set if color tone mode is on, unset if off */
        EIsColorToneModeOn = ( 1 << 23 ),

        /** Set if fixed toolar is visible, unset if not */
        EIsFixedToolbarVisible = ( 1 << 24 ),

        /** Set if dialer is being activated, unset if not */
        EIsDialerActivating = ( 1 << 25 ),

        /** Set if volume mode is on, unset if off */
        EIsVolumeModeOn = ( 1 << 26 ),

        /** Set if floating toolar is visible, unset if not */
        EIsFloatingToolbarVisible = ( 1 << 27 ),
        
        /** Set if video quality mode is on, unset if not */
        EIsVideoQualityModeOn = ( 1 << 28 )
        };

    // Engine media state
    TVtUiMediaState iMediaState;

    // Engine audio state
    TVtUiAudioState iAudioState;

    // Refrence to engine
    CVtEngModel& iModel;

    // Refrence to camera prefrences
    MVtEngCameraPreferences* iCameraPref;

    // Application execution state
    TVtUiExecState iExecState;
    
    // Reference count of command activating. Enables command to be set
    // active several times and action to take only when count is reset
    // back to zer0.
    TUint iCommandActivatingRefCount;

private: // friends

    friend class TVtUiAppStateBase;

    };

#include "tvtuistates.inl"

#endif // T_VTUISTATES_H

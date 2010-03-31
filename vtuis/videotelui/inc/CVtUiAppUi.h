/*
* Copyright (c) 2004-2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Application UI class for Video Telephone application.
*
*/



#ifndef CVTUIAPPUI_H
#define CVTUIAPPUI_H

//  INCLUDES
#include    <aknappui.h>
#include    <vtengcommands.h>
#include    <mvtengmedia.h>
#include    <tvtengrendering.h>
#include    <tvtengrenderingdsa.h>
#include    <tvtengrenderingdp.h>
#include    <tvtengrenderingnga.h>
#include    <AknProgressDialog.h>
#include    <mvtengaudio.h>
#include    <remconcoreapi.h>

#include    "CVtUiActiveExec.h"
#include    "tvtuilocalvariation.h"
#include    "tvtuiappstatebase.h"


// FORWARD DECLARATION
class CVtUiBlankControl;
class CAknNavigationControlContainer;
class CAknTitlePane;
class CVtEngModel;
class MVtUiVideoWindow;
class CRepository;
class CAknQueryDialog;
class CAknProgressDialog;
class TVtUiStates;
class CVtUiCommandManager;
class CVtUiComponentManager;
class CVtUiFeatureManager; // TOOLBAR MOD
class MVtUiNumberSource;
class CVtUiMainControl;
class CVtUiContextControl;
class CVtUiBitmapManager;
class CVtUiVolumeControl;
class CAknIncallBubble;
class CVtUiRemoteVideoControl;
class CVtUiEndCallButtonPane;

// CLASS DECLARATION

/**
*  Application UI class for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiAppUi
    : public CAknAppUi,
      protected MVtUiActiveExec,
      public MVtUiStateContext,
      public MProgressDialogCallback
    {
    public:

        // Rendering modes
        enum TRenderingMode
            {
            ERenderingModeDefault,
            ERenderingModeDialer
            };

    public: // Constructors and destructor

        /**
        * C++ constructor.
        */
        CVtUiAppUi();

        /**
        * Symbian constructor.
        */
        void ConstructL();

        /**
        * C++ destructor.
        */
        ~CVtUiAppUi();

    public: // New functions

        /*
        *  This function decides possibility of swapimg image places.
        */
        TBool CanSwapImagePlaces();

        /*
        * Switches status pane between flat and normal one.
        */
        void SwitchLayoutToFlatStatusPaneL( TBool aSwitch );

        /**
        * Refreshes all.
        */
        void RefreshL();

        /**
        * Refreshes navi pane.
        */
        void RefreshNaviPaneL();

        /**
        * Refreshes softkeys.
        */
        void RefreshSoftkeysL();
        
        /**
        * Refreshes menu.
        */
        void RefreshMenuL();

        /**
        * Refresh zoom popup
        */
        void RefreshZoomPopupL();
        
        /**
        * Stop brightness or Contrast
        */        
        void StopBrightnessOrContrast();
        /**
        * Refreshes blind flags.
        */
        void RefreshBlind();

        /**
        * Refreshes synchronisation.
        */
        void RefreshSynchronise();

        /**
        * Opens number entry.
        * @return ETrue if number entry opened.
        */
        TBool OpenNumberEntryL();

        /**
        * Handles EKeyPhoneSend presses
        */
        TKeyResponse HandlePhoneSendKeyL( const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * Returns pointer to cba.
        */
        CEikButtonGroupContainer* GetCba();

        /**
        * Sets zoom mode.
        * @param aEnableZoomMode Etrue if zoom mode is on.
        * EFalse otherwise.
        * @param aIsPermanent ETrue if zoomindicator's timeout
        * should be ignored. EFalse otherwise..
        */
        void SetZoomModeL( const TBool aEnableZoomMode,
            const TBool aIsPermanent = EFalse );

        /**
        * Checks if command is active.
        * @param aCommand Command id.
        * @return Etrue if command is active
        * EFalse otherwise.
        */
        TBool IsActiveCommand( TInt aCommand ) const;

        TVtUiAppStateBase& State();

        /**
        * Returns reference to bitmap manager.
        */
        CVtUiBitmapManager& BitmapManager();

        /**
        * Sets given zoom step, if it allowed.
        * @param aZoomStep New zoom step to be set.
        */
        void SetZoomFactorL( TInt aZoomStep );
        
        /*
        * Simulate key event
        */
        void CmdSimulateKeyEvent( TInt aScanCode );

    public: // Functions from base classes

        /**
        * From CAknAppUi, handles window server events.
        * @param aEvent event.
        * @param aDestination destination control.
        */
        virtual void HandleWsEventL(
            const TWsEvent& aEvent,
            CCoeControl* aDestination );

        /**
        * From CAknAppUi, processes commands.
        * @param aCommand the identifier of the command to be handled.
        */
        virtual void ProcessCommandL(
            TInt aCommand );

        /**
        * From CAknAppUi, handles commands.
        * @param aCommand the identifier of the command to be handled.
        */
        virtual void HandleCommandL(
            TInt aCommand );

        /**
        * From CAknAppUi, handles dynamic initialisation of menu panes.
        * @param aResourceId the resource identifier for the pane.
        * @param aMenuPane the menu pane corresponding to the resource.
        */
        virtual void DynInitMenuPaneL(
            TInt aResourceId,
            CEikMenuPane* aMenuPane );

        /**
        * From CAknAppUi, handles key events.
        * @param aKeyEvent event to be handled.
        * @param aType type of the key event.
        * @return response code (EKeyWasConsumed, EKeyWasNotConsumed)
        */
        virtual TKeyResponse HandleKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * From CAknAppUi, handles resouce changes.
        * @param aType type of resource change.
        */
        virtual void HandleResourceChangeL( TInt aType );

        /**
        * From CAknAppUi, handles foreground status changes.
        * @param aForeground ETrue if foreground.
        */
        virtual void HandleForegroundEventL( TBool aForeground );

        /**
        * Returns a pointer to CEikonEnv.
        */
        CEikonEnv* GetEikonEnv();

    protected: // Functions from base classes

        /**
        * From CAknAppUi, returns help context.
        * @return help context.
        */
        virtual CArrayFix<TCoeHelpContext>* HelpContextL() const;

        /**
        * @see MVtUiActiveExec::ActiveExecExecuteL.
        */
        virtual TBool ActiveExecExecuteL(
            CVtUiActiveExec& aActiveExec,
            const TInt aState,
            TInt& aNextState,
            TRequestStatus& aRequest );

        /**
        * @see MVtUiActiveExec::ActiveExecContinue.
        */
        virtual TBool ActiveExecContinue(
            CVtUiActiveExec& aActiveExec,
            TInt& aState,
            const TInt aError );

        /**
        * @see MVtUiActiveExec::ActiveExecCancel.
        */
        virtual void ActiveExecCancel(
            CVtUiActiveExec& aActiveExec,
            const TInt aState );

        /**
        * @see MVtUiActiveExec::ActiveExecDone.
        */
        virtual void ActiveExecDone(
            CVtUiActiveExec& aActiveExec,
            const TInt aInitialState );

    public: // from MVtUiStateContext

        /** @see MVtUiStateContext::StartupPhase1L */
        virtual void StartupPhase1L();

        /** @see MVtUiStateContext::ShutdownL */
        virtual void ShutdownL();

        /** @see MVtUiStateContext::StartupPhase2L */
        virtual void StartupPhase2L();

        /** @see MVtUiStateContext::ChangeApplicationFocus */
        virtual void ChangeApplicationFocus( const TBool aForeground );

        /** @see MVtUiStateContext::ChangeState */
        virtual void ChangeState( TVtUiAppStateBase* aState );

        /** @see MVtUiStateContext::StartTone */
        virtual void StartDtmfTone( const TChar& aTone );

        /** @see MVtUiStateContext::StopTone */
        virtual void StopDtmfTone();

        /** @see MVtUiStateContext::Model */
        virtual CVtEngModel& Model();

        /** @see MVtUiStateContext::VideoTelephonyVariation */
        virtual const TVtUiVideoTelephonyVariation&
            VideoTelephonyVariation() const;

        /** @see MVtUiStateContext::NumberSource*/
        virtual MVtUiNumberSource* NumberSource() const;

        /** @see MVtUiStateContext::RefreshL */
        virtual void RefreshL( const TInt aRefreshFlags );

        /** @see MVtUiStateContext::DoExecuteCmdL */
        virtual void DoExecuteCmdL(
            const TVtEngCommandId aCommand,
            TDesC8* aParams );

        /** @see MVtUiStateContext::DoHandleLayoutChangedL */
        virtual void DoHandleLayoutChangedL();

        /** From MVtUiShutterObserver via MVtUiStateContext
        *  Exits the application.
        */
        virtual void HandleShutdownReady();

        /**
        * Gets reference to context control.
        * @return reference to context control.
        */
        CVtUiContextControl& ContextControl();

        /**
        * Gets reference to main control.
        * @return reference to main control.
        */
        CVtUiMainControl& MainControl();

        /**
        * Gets reference to remote video control.
        * @return reference to remote video control.
        */        
        CVtUiRemoteVideoControl& RemoteVideoControl();

        /**
        * Gets reference to end call pane.
        * @return reference to end call pane.
        */
        CVtUiEndCallButtonPane& EndCallButtonPane();

        /**
        * Switches viewfinder to main pane if it is currently in context
        * pane.
        */
        void SwitchViewFinderToMainPaneL( TBool aUpdateState = ETrue );

        /**
        * Switches viewfinder to context pane if it is currently in main
        * pane.
        */
        void SwitchViewFinderToContextPaneL( TBool aUpdateState = ETrue );

        /**
        * Restores viewfinder back to pane where it was prior to calling the
        * switch ViewFinderToMainPane() or ViewFinderToContextPane() methods.
        */
        void RestoreViewFinderL();

        /*
        * Updates volume to the Video Telephone engine.
        */
        void CmdUpdateVolumeL( MVtEngAudio::TVtEngOutputVolume aVolume );

        /**
        * Increases "command activating" ref.count and adds cleanup item
        * to decrease it. Refreshes commands in case of first increment from
        * zero. When PopAndDestroy() is called, cleanup decreases reference
        * count and if it reduces back to zero command refresh is again done.
        */
        void EnableCommandActivatingAndCleanupPushL();

    private: // from MProgressDialogCallback

        /**
        * @see MProgressDialogCallback::DialogDismissedL
        */
        void DialogDismissedL( TInt aButtonId );

    private:

        // COMMAND HANDLING

        /**
        * Checks if command is allowed.
        * @param aCommand command identifier.
        * @return ETrue if allowed, EFalse otherwise.
        */
        TBool IsCommandAllowedL( const TInt aCommand );

        /**
        * Refreshes iDisabledFlags.
        */
        void RefreshDisabledFlagsL();

        /**
        * Refreshes camera option availability.
        * @param aUsePrimaryCameraNotAllowed it will be updated to ETrue if
        *        it is not allowed to activate primary camera.
        * @param aUseSecondaryCameraNotAllowed it will be updated to ETrue if
        *        it is not allowed to activate secondary camera.
        */
        void RefreshCameraOptionAvailability(
            TBool& aUsePrimaryCameraNotAllowed,
            TBool& aUseSecondaryCameraNotAllowed );

        /**
        * Enables capture mode.
        */
        void CmdSnapshotL();

        /**
        * Freezes outgoing video image.
        */
        void CmdCaptureL();

        /**
        * Disables capture mode.
        */
        void CmdCancelCaptureL();


        /**
        * Enables video.
        */
        void CmdEnableVideoL();

        /**
        * Enables audio (unmute microphone).
        */
        void CmdEnableAudioL();

        /**
        * Disables video.
        */
        void CmdDisableVideoL();

        /**
        * Disables audio (mute microphone).
        */
        void CmdDisableAudioL();

        /**
        * Activates Bluetooth handsfree.
        */
        void CmdActivateBtL();

        /**
        * Deactivates Bluetooth handsfree.
        */
        void CmdDeactivateBtL();

        /**
        * Activates loudspeaker.
        */
        void CmdActivateLoudspeakerL();

        /**
        * Deactivates loudspeaker.
        */
        void CmdDeactivateLoudspeakerL();

        /**
        * Ends active call.
        */
        void CmdEndActiveCallL();

        /**
        * Swaps images places.
        */
        void CmdSwapImagesPlacesL();

        /**
        * Switches used camera.
        * @param aPrimaryCamera ETrue if primary camera is to be selected,
        *        EFalse if secondary camera is to be selected.
        */
        void CmdUseCameraL( const TBool aPrimaryCamera );

        /**
        * Launches help application.
        */
        void CmdHelpL();

        /**
        * Prepare exiting the application.
        */
        void PrepareExitL();

        /**
        * Updates zoom step to Video Telephone engine.
        */
        void CmdUpdateZoomL();

        /**
        * Dials emergency call.
        */
        void CmdDialEmergencyL();

        /**
        * Goes to Idle.
        */
        void CmdGoToIdleL();

        /**
        * Initialize image sharing.
        */
        void CmdInitializeShareImageL( TBool& aNeedRefresh );

        /**
        * Start sharing image.
        */
        void CmdShareImageL();

        /**
        * Stops sharing image.
        */
        void CmdStopShareImageL( TBool& aNeedRefresh );

		/**
        * Handles change in call waiting state.
        * @param aIsWaiting The state of call waiting.
        */
	    void HandleWaitingStateChange( TBool aIsWaiting );

        // STATE TRANSITIONS

        /**
        * @see MVtUiActiveExec::ActiveExecExecuteL.
        */
        TBool ActiveExecInitExecuteL(
            const TInt aState,
            TInt& aNextState,
            TRequestStatus& aRequest );

        /**
        * @see MVtUiActiveExec::ActiveExecContinue.
        */
        TBool ActiveExecInitContinue(
            TInt& aState,
            const TInt aError );

        /**
        * @see MVtUiActiveExec::ActiveExecCancel.
        */
        void ActiveExecInitCancel(
            const TInt aState );

        /**
        * @see MVtUiActiveExec::ActiveExecDone.
        */
        void ActiveExecInitDone(
            const TInt aInitialState );

        /**
        * Executes command taking no parameters.
        * @param aCommand command to be performed.
        * @param aRequest request status.
        */
        void ActiveExecInitExecuteCommandL(
            const TVtEngCommandId aCommand,
            TRequestStatus& aRequest );

        /**
        * Executes command taking no parameters.
        * @param aCommand command to be performed.
        * @param aParam command parameters.
        * @param aRequest request status.
        */
        template < class T >
        void ActiveExecInitExecuteCommandL(
            const TVtEngCommandId aCommand,
            T& aParam,
            TRequestStatus& aRequest );

        /**
        * Executes 'prepare camera' command.
        * @param aSource source to be prepared.
        * @param aRequest request status.
        */
        void ActiveExecInitPrepareCameraL(
            const MVtEngMedia::TMediaSource aSource,
            TRequestStatus& aRequest );

        /**
        * Executes 'set source' command.
        * @param aSource source to be selected.
        * @param aRequest request status.
        */
        void ActiveExecInitSetSourceL(
            const MVtEngMedia::TMediaSource aSource,
            TRequestStatus& aRequest );

        /**
        * Executes prepare viewfinder command.
        * @param aRequest request status to be completed when finished.
        */
        void ActiveExecInitPrepareViewFinderL(
            TRequestStatus& aRequest );

        /**
        * Executes prepare remote render command.
        * @param aRequest request status to be completed when finished.
        */
        void ActiveExecInitPrepareRemoteRenderL(
            TRequestStatus& aRequest );


        /**
        * Executes command taking no parameters.
        * @param aCommand command to be performed.
        * @param aRequest request status.
        */
        void ActiveExecCmdExecuteCommandL(
            const TVtEngCommandId aCommand,
            TRequestStatus& aRequest );

        /**
        * Executes 'set source' command.
        * @param aSource source to be selected.
        * @param aRequest request status.
        */
        void ActiveExecCmdSetSourceL(
            const MVtEngMedia::TMediaSource aSource,
            TRequestStatus& aRequest );

        /**
        * Executes 'prepare camera' command.
        * @param aSource source to be selected.
        * @param aRequest request status.
        */
        void ActiveExecCmdPrepareCameraL(
            const MVtEngMedia::TMediaSource aSource,
            TRequestStatus& aRequest );


        /**
        * Determines main control options.
        * @param aRemoteVideo for remote video.
        * @return rendering options.
        */
        TVtEngRenderingOptions
            DetermineMainControlOptions( TBool aRemoteVideo );

        /**
        * Determines context control options.
        * @return rendering options.
        */
        TVtEngRenderingOptions DetermineContextControlOptions();

        /**
        * Determines dialer control options.
        * @return rendering options.
        */
        TVtEngRenderingOptions DetermineDialerControlOptions();

        /**
        * Determines main control DSA options.
        * @param aRemoteVideo for remote video.
        * @return rendering options.
        */
        TVtEngRenderingOptionsDSA
            DetermineMainControlOptionsDSA( TBool aRemoteVideo );

        /**
        * Determines context control DSA options.
        * @return rendering options.
        */
        TVtEngRenderingOptionsDSA DetermineContextControlOptionsDSA();

        /**
        * Determines dialer control DSA options.
        * @return rendering options.
        */
        TVtEngRenderingOptionsDSA DetermineDialerControlOptionsDSA();

        /**
        * Determines main control DP options.
        * @param aRemoteVideo for remote video.
        * @return rendering options.
        */
        TVtEngRenderingOptionsDP
            DetermineMainControlOptionsDP( TBool aRemoteVideo );

        /**
        * Determines context control DP options.
        * @return rendering options.
        */
        TVtEngRenderingOptionsDP DetermineContextControlOptionsDP();

        /**
        * Determines dialer control DP options.
        * @return rendering options.
        */
        TVtEngRenderingOptionsDP DetermineDialerControlOptionsDP();

        /**
        * Determines remote video  control options.
        * @return rendering options.
        */
        TVtEngRenderingOptionsNGA
            DetermineRemoteVideoControlOptionsNGA();

        // SYNCHRONOUS / BLOCKING EXECUTION:

        /**
        * Performs a command without any parameters.
        * @param aCommand command to be performed.
        */
        void ExecuteCmdL( const TVtEngCommandId aCommand );

        /**
        * Performs a command with a parameter.
        * @param aCommmand command to be performed.
        * @param aParam parameter.
        */
        template< class T >
        void ExecuteCmdL(
            const TVtEngCommandId aCommand,
            T& aParam );

        // ASYNCHRONOUS EXECUTION:

        /**
        * Performs a command without any parameters.
        * @param aDialogPtr pointer to which returned value is stored.
        * @param aCommand command to be performed.
        * @param aStatus request status.
        * @return dialog.
        */
        CEikDialog* ExecuteCmdAsyncL(
            CEikDialog** aDialogPtr,
            const TVtEngCommandId aCommand,
            TRequestStatus& aStatus );

        /**
        * Performs a command with a parameter.
        * @param aDialogPtr pointer to which returned value is stored.
        * @param aCommmand command to be performed.
        * @param aParam parameter.
        * @param aStatus request status.
        * @return dialog.
        */
        template< class T >
        CEikDialog* ExecuteCmdAsyncL(
            CEikDialog** aDialogPtr,
            const TVtEngCommandId aCommand,
            T& aParam,
            TRequestStatus& aStatus );

        /**
        * Performs a command.
        * @param aDialogPtr pointer to which returned value is stored.
        * @param aCommand command.
        * @param aParams parameter, optional.
        * @param aStatus request status.
        * @return dialog.
        */
        CEikDialog* DoExecuteCmdAsyncL(
            CEikDialog** aDialogPtr,
            const TVtEngCommandId aCommand,
            TDesC8* aParams,
            TRequestStatus& aStatus );

        /**
        * Executes command in TRAP harnness.
        * @param aCommand command identifier.
        * @param aParam optional, parameters.
        * @return error code.
        */
        TInt Execute( const TVtEngCommandId aCommand, TDesC8* aParam );

        // EVENT HANDLING

        /**
        * Handles foreground changed events.
        * @param aIsForeground ETrue if foreground, EFalse otherwise.
        */
        void HandleForegroundChangedL(
            TBool aIsForeground );

        /**
        * Handles engine reset.
        */
        void HandleEngineResetL();

        /**
        * Handles successful answer operation.
        */
        void HandleAnswerL();

        /**
        * Stops waiting image text showing.
        */
        void StopWaitingImage();

        /**
         * Stops white balance showing.
         */
        void StopWhiteBalanceOrColortone();
        
        /**
        * Handles layout changes basically calling HandleLayoutChangedL
        * in trap harness.
        * @return error code.
        */
        TInt HandleLayoutChanged();

        /**
        * Handles layout changes.
        */
        void HandleLayoutChangedL();

        /**
        * Handles video frame.
        * @param aLocal local frame if ETrue, EFalse if remote.
        * @param aBitmap frame, ownership not transferred.
        */
        void HandleVideoFrameL(
            const TBool aLocal,
            CFbsBitmap* aBitmap );

        void SetVideoFrame(
            const TBool aLocal,
            CFbsBitmap* aBitmap );

          /**
        * Handles video call details.
        * @param aCallID call id.
        * @param aCallName call name.
        * @param aIsPeerAddressAvailable is peer address available.
        */
        void HandleVideoCallDetailsL(
            const TInt aCallId,
            const TDesC& aCallName,
            const TBool aIsPeerAddressAvailable );

        /**
        * Checks if it's time to bring this application
        * to the foreground.
        */
        void CheckBringToForeground();

        /**
        * Checks if it's time to send this application
        * to the background.
        */
        void CheckSendToBackground();

        /**
        * Handles remote problem.
        */
        void HandleVideoFrameRemoteProblemL();

        /**
        * Handles local problem.
        */
        void HandleVideoFrameLocalProblemL();

        /**
        * Set a new remote video layout.
        */
        void ChangeRemoteVideoLayoutL();

        /**
        * Show image initialization progress dialog.
        */
        void ShowImageInitializeProgressL();

        /**
        * Hide image initialization progress dialog.
        */
        void HideImageInitializeProgressL();

        /**
        * Sets SQCif usage.
        * @param aUseSQCif SQCif is used.
        */
        void RemoteVideoIsSQCif( TBool aUseSQCif );

        /**
        * Sets SQCif usage to control.
        * @param aUseSQCif SQCif is used.
        */
        void ControlUsesSQCif( TBool aUseSQCif );

        /**
        * Checks if beating needs to be started.
        * @param aCallDurationEnabled call duration enabled status.
        */
        void CheckBeatL( const TBool aCallDurationEnabled );

        /**
        * Handles heart beats.
        */
        void HandleBeat();

        // UTILITY METHODS

        /**
        * Informs the user that camera is reserved by another application.
        */
        void ShowCameraInUseNoteL() const;

        /**
        * Informs the user that the selected operation is not allowed.
        */
        void ShowNotAllowedNoteL() const;

        /**
        * Informs the user that it is not allowed to create normal call.
        */
        void ShowCallNotAllowedNoteL() const;

        /**
        * Informs the user that the other camera is not usable.
        */
        void ShowOtherCameraNotUsableNoteL() const;

        /**
        * Informs the user that image loading failed.
        */
        void ShowUnableToOpenNoteL() const;

        /**
        * Informs the user that error happened during image decoding.
        * Note: Cannot be constant because DoExecuteL() is used for
        * calling this method.
        */
        void ShowImageDecodingErrorNoteL();

        /**
        * Informs the user that image is DRM protected and cannot be opened.
        */
        void ShowDRMNotAllowedNoteL() const;

        /**
        * Sets softkeys.
        * @param aSoftkeyResourceId softkey resource id.
        */
        void SetSoftkeysL( const TInt aSoftkeyResourceId );

        /**
        * Sets application hidden from fast swap window.
        * @param aHidden ETrue if to be hidden, EFalse if visible.
        */
        void SetHiddenL( const TBool aHidden );

        /**
        * Updates title pane to show call index.
        * @param aCallId call id.
        */
        void SetCallIdL( const TInt aCallId );

        /**
        * Updates title pane to show name.
        * @param aName name to be displayed in title pane.
        * @return ETrue if succeeded, EFalse if not enough memory.
        */
        TBool SetCallNameL( const TDesC& aName );

        /**
        * Brings Telephone application to the foreground.
        */
        void BringTelephoneToForeground();

        /**
        * Returns window group identifier of the principal
        * telephone application.
        * @return window group id or 0 if failed.
        */
        TInt TelephoneApplicationWgId();

        /**
        * Returns ETrue if number entry should be shown to the user.
        * This can be called only after ReadTelephonyVariant has
        * been called.
        * @return ETrue if number entry should be shown to the user.
        */
        inline TBool ShowNumberEntry() const;

        /**
        * Checks if active idle is enabled.
        * @return ETrue if active idle is enabled.
        */
        TBool IsActiveIdleEnabledL() const;

        /**
        * Checks engine functionality.
        */
        void CheckEngineFunctionality();

        /**
        * Returns navi pane.
        * @return navi pane instance. Ownership not transferred.
        */
        inline CAknNavigationControlContainer* NaviPaneL();

        /**
        * Returns title pane.
        * @return title pane instance. Ownership not transferred.
        */
        inline CAknTitlePane* TitlePaneL();

        /**
        * Pushes item to cleanup stack to update softkeys.
        */
        inline void CleanupPushRefreshL();

        /**
        * Pushes item to cleanup stack to enable blind status setting.
        */
        inline void CleanupPushEnableBlindL();

        /**
        * Callback function to refresh navi pane and softkeys.
        * @param aAny pointer to an instance of this class.
        */
        static void DoRefresh( TAny* aAny );

        /**
        * Callback function to enable blind status checking.
        * @param aAny pointer to an instance of this class.
        */
        static void DoEnableBlindSetting( TAny* aAny );

        /**
        * Callback function to disable command activation
        * state.
        * @param aAny pointer to an instance of this class.
        */
        static void DoDisableCommandActivating( TAny* aAny );

        /**
        * Decreases command activation ref.count and refreshes
        * states if count gets zero.
        */
        void HandleCommandDeactivationL();

        /**
        * Callback function to handle exit timeout.
        * @param aAny pointer to instance of this class.
        * @return KErrNone always.
        */
        static TInt DoHandleExitTimeout( TAny* aAny );

        /**
        * Callback function to exit.
        * @param aAny pointer to instance of this class.
        * @return KErrNone always.
        */
        static TInt DoExit( TAny* aAny );

        /**
        * Checks whether viewfinder is currently in main pane.
        * @return ETrue if viewfinder is in main pane.
        */
        TBool IsViewFinderInMainPane() const;

public:
        /**
        * Checks whether viewfinder is currently in context pane.
        * @return ETrue if viewfinder is in context pane.
        */
        TBool IsViewFinderInContextPane() const;
private:
        /**
        * Updates context pane icon
        */
        void UpdateContextPaneIconL();

        /**
        * Enables or disables the incall bubble.
        */
        void SetIncallBubbleAllowedInUsualL( TBool aAllowed );

        /**
        * Shows progress dialog using given resource.
        */
        void ShowProgressDialogL( TInt aResourceId,
            MProgressDialogCallback* aCallback = NULL );

        /**
        * Hides (completes) progress dialog.
        */
        void HideProgressDialogL();

        /**
        * Static async callback for switching viewfinder to MainPane, also
        * starts image sharing.
        */
        static TInt AsyncViewFinderToMainPaneAndShare( TAny* aPtr );

        /**
        * Static async callback for starting image share.
        */
        static TInt AsyncShare( TAny* aPtr );

        /**
        * Static async callback for showing error note and resharing image.
        */
        static TInt AsyncShowErrorAndRestartShare( TAny* aPtr );

        /**
        * Static async callback for handling layout change.
        */
        static TInt DelayedHandleLayoutChanged( TAny* aPtr );

        /**
        * Gets current camera orientations for primary and secondary camera.
        */
        void GetCameraOrientations();

        /**
        * Sets initial camera orientation.
        */
        void SetInitialCameraOrientationL();

        /**
        * Sets current camera orientation.
        */
        void SetCameraOrientationL();

        /**
        * Updates engine states.
        */
        void RefreshStatesL();

        /**
        * Starts video preference feature specified by command id.
        */
        void CmdAdjustVideoL( TInt aCommand );

        /**
        * AppUi has been initialized and its current state is EVtUiAppUiAnswered.
        * Do any other needed initilization here e.g. start features.
        */
        void AppUiInitDoneDoPostInitL();

        /*
        *  This function decides how the wsevent should be handled
        * if zoom mode is on.
        * @param  aEvent window server event.
        * @return ETrue if caller function should return, EFalse otherwise.
        */
        TBool ProcessWsEventIfZoomModeIsActiveL( const TWsEvent& aEvent );

        /*
        *  This function hides the brightness, contrast, volume slider if their mode is on.
        */
        void StopSliders();
        
        /*
        * This function can get the focus window group id
        */
        TInt GetFocusWindowGroupId();

        /**
        * Does pre handling to key events, especially for Zoom in and Zoom out
        * HW keys.
        * @param aEvent event.
        */
        TBool PreHandleKeyEventL( const TWsEvent& aEvent );

        /**
        * Calls SimulateKeyEventL() for stored zoom key event.
        */
        void SimulateStoredKeyEventL( const TEventCode aEventCode );

        /**
        * Stores zoom key event. If there is different zoom key event
        * already stored, keyup event is sent for that event before
        * new event is stored.
        */
        void StoreKeyEventL( const TKeyEvent& aKeyEvent );

        /**
        * Callback function that calls TryToStartTb function
        */
        static TInt DoTryToStartTbL( TAny* aAny );

        /*
        * Tries to start toolbar. Toolbar is started if
        * option menus is not visible.
        */
        void TryToStartTbL();

        /*
        * Update video prefrence
        */
        void UpdateVBSettingL();


        /**
        * Sets current rendering mode (i.e. default or dialer)
        */
        void SetRenderingModeL( const TRenderingMode aMode,
            MVtUiVideoWindow* aDownlink );

        /**
        * Updates rendering parameters.
        */
        void UpdateRenderingParametersL();

        /*
        * Media state has been changed
        */
        void MediaStateChangedL();

        /*
        * Updates volume slider
        */
        void RefreshVolumeL();

        /*
        * Adjusts volume up or down one step.
        */
        void AdjustVolumeL( TRemConCoreApiOperationId aOperationId );

    private:

        // Pointer to stored downlink window.
        MVtUiVideoWindow* iStoredDownlinkWindow;

        // Current rendering mode
        TRenderingMode iRenderingMode;

        // Command framework instance
        CVtUiCommandManager* iCommandManager;

        // Inner class.
        class CInstance;

        // Model instance. Exists only while there is a video call.
        CInstance* iInstance;

        // Inner class to observe all events.
        class CEventObserver;

        // Inner class for verifying media gallery objects
        class CVtUiAppUiMGVerifier;

        // Owned event observer.
        CEventObserver* iEventObserver;

        // Owned blank control for reset & shutdown.
        CVtUiBlankControl* iBlankControl;

        /**
        * Enumerates disabled flags:
        * EDisabledVideo - video disabled,
        * EDisabledAudio - audio disabled,
        * EVideoOptionsDisabled - video options disabled.
        */
        enum TDisabledFlags
            {
            EDisabledVideo = 1,
            EDisabledAudio = 2,
            EVideoOptionsDisabled = 4
            };

		// The Ihf Note id.
		TInt iIhfNoteId;

        // Flags for disabled. Sum of subset of TDisabledFlags.
        TInt iDisabledFlags;

        // Current softkey resource id.
        TInt iCurrentSoftkeys;

        // Telephony variant.
        TVtUiVideoTelephonyVariation iVTVariation;

        // Window group id of this application.
        TInt iThisApplicationWgId;

        // Window group id of eikon server.
        TInt iEikonServerWgId;

        // Window group id for AknCapServer
        TInt iAknCapServerWgId;

        // Window group id for Akn Notifier Server
        TInt iAknNfyServerWgId;

        // Owned active executor for initialisation / uninitialisation.
        CVtUiActiveExec* iActiveExec;

        // Owned current dialog on execution.
        CEikDialog* iExecDialog;

        // Owned blank dialog.
        CEikDialog* iExecBlankDialog;

        // Reference to request status.
        TRequestStatus* iShutdownRequest;

        // Owned active executor for command execution.
        CVtUiActiveExec* iCmdActiveExec;

        // Owned current dialog on command execution.
        CEikDialog* iCmdExecDialog;

        // Owned blank dialog on command execution.
        CEikDialog* iCmdExecBlankDialog;


        // Owned timer for making sure that
        // the application is terminated in time.
        CPeriodic* iExitTimer;

        // DTMF tone, used as parameter to KVtEngStartDtmfTone.
        TPckgBuf< TChar > iDtmfTone;

        // Pointer to uplink window.
        MVtUiVideoWindow* iUplinkWindow;

        // Pointer to downlink window.
        MVtUiVideoWindow* iDownlinkWindow;

        // Query dialog for switching to voice call
        CAknQueryDialog* iCreateVoiceCallDlg;

        // Progress dialog shown when initializing
        CAknProgressDialog* iProgressDlg;

        // ASync callback.
        CAsyncCallBack* iAsyncCallback;

        // Async callback for layout change
        CAsyncCallBack* iLayoutChangeCallback;

        // Camera orientation for primary camera
        MVtEngMedia::TCameraOrientation iPrimaryCameraOrientation;

        // Camera orientation for secondary camera
        MVtEngMedia::TCameraOrientation iSecondaryCameraOrientation;

        // Currently used camera orientation
        MVtEngMedia::TCameraOrientation iCurrentCameraOrientation;

        // Current loudspeaker volume
        TInt iLoudspeakerVolume;

        // Current handset volume
        TInt iHandsetVolume;

        // Ui states (media, audio, boolean variables)
        TVtUiStates* iUiStates;

        // Component manager instance
        CVtUiComponentManager* iComponentManager;

        // Feature manager instance
        CVtUiFeatureManager* iFeatureManager;

        // Pointer to cba
        CEikButtonGroupContainer* iCba;

        // Active number source
        MVtUiNumberSource* iNumberSource;

        TVtUiAppStateBase*  iState;

        // Stored zoom key event
        TKeyEvent iStoredKeyEvent;

        // ETrue if incoming call is waiting call
        TBool iIsWaitingCallState;

        // ETrue if key event has been stored
        TBool iIsStoredKeyEvent;

        // Timer for starting the toolbar
        CPeriodic* iTbPeriodic;

        // Owned volume control class for adjusting
        // engine side volume
        CVtUiVolumeControl* iVolCtrl;

    private: // Friend classes

        // Inner class.
        friend class CInstance;

        // Inner class.
        friend class CEventObserver;

    private:

        // Class for active command handling
        class TActiveCommand
            {

        public:

            /**
            * Constructor.
            * @param aActiveCommands array of command ids.
            * @param aCommand command id.
            */
            TActiveCommand( RArray< TInt >& aActiveCommands, TInt aCommandId );

            /**
            * Destructor
            */
            ~TActiveCommand();

            /**
            * Adds command to active commands
            */
            void OpenL();

        private:

            /**
            * Removes command from active commands
            */
            void Close();

        private:

            // Reference to array of active command ids.
            RArray< TInt >& iActiveCommands;

            // Command id.
            const TInt iCommandId;

            };


    private:
        // Active command ids.
        RArray< TInt > iActiveCommands;
        // The last time swap image operation occured.
        TTime iLastSwapTime;
        // Incall bubble.
        CAknIncallBubble* iIncallBubble;
        //This flag is used to check if orientation changed before some action
        //Currently is only used for prepare remote render and start remote render
        TBool iIsLandScapeOrientation;
        //flag indicates layoutchang session
        TBool iLayoutChg;
        //save cmd for later use 
        TInt iDelayedCmd;
    };

#endif      // CVTUIAPPUI_H

// End of File

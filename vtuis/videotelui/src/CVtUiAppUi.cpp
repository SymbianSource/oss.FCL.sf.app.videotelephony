/*
* Copyright (c) 2004 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiAppUi application UI class.
*
*/



// INCLUDE FILES
#include    "videotelui.hrh"
#include    "CVtUiAppUi.h"
#include    "CVtUiMainControl.h"
#include    "CVtUiContextControl.h"
#include    "CVtUiNumberEntryActivationControl.h"
#include    "CVtUiNaviPane.h"
#include    "VtUiLayout.h"
#include    "MVtUiEngineCommandManager.h"
#include    "CVtUiExecuteCmdDialog.h"
#include    "CVtUiAllowVideoDialog.h"
#include    "CVtUiBlankControl.h"
#include    "VtUiLayout.h"
#include    "VtUiUtility.h"
#include    "VtUiPanic.h"
#include    "CVtUiActivateBtHfDialog.h"
#include    "CVtUiRemoteVideoControl.h"
#include    "CVtUiEndCallButtonPane.h"
#include    <csxhelp/incl.hlp.hrh>


#include    <AknIncallBubbleNotify.h>
#include    <AknsLayeredBackgroundControlContext.h>
#include    <AknUtils.h>
#include    <aknnavi.h>
#include    <akntitle.h>
#include    <AknDlgShut.h>
#include    <aknnotedialog.h>
#include    <aknnotewrappers.h>
#include    <akncontext.h>
#include    <eikspane.h>
#include    <eikmenup.h>
#include    <eikmenub.h>
#include    <apgcli.h>
#include    <featmgr.h>
#include    <videotelui.rsg>
#include    <hlplch.h>
#include    <apgwgnam.h>
#include    <StringLoader.h>
#include    <AknDef.h>
#include    <aknconsts.h>


#include    <e32property.h>
#include    <ecom/ecom.h>
#include    <coreapplicationuisdomainpskeys.h>
#include    <UikonInternalPSKeys.h>
#include    <centralrepository.h>
#include    <videotelephonyinternalcrkeys.h>
#include    <settingsinternalcrkeys.h>
#include    <e32property.h>
#include    <telcommsinfopskeys.h>
#include    <telinformationpskeys.h>
#include    <activeidle2domainpskeys.h>
#include     <ctsydomainpskeys.h>

#include    <AknQueryDialog.h>
#include     <AknGlobalNote.h>
#include     <aknsoundsystem.h>


#include    <cvtlogger.h>
#include    <cvtengmodel.h>
#include    <mvtengeventobserver.h>
#include    <mvtengcommandobserver.h>
#include    <mvtengcommandhandler.h>
#include    <mvtengframeobserver.h>
#include    <mvtengaudio.h>
#include    <mvtengsessioninfo.h>
#include    <vtengevents.h>
#include    <mvtengmedia.h>

#include    "CVtUiBitmapManager.h"

#include    <MGFetch.h>
#include    <MMGFetchVerifier.h>
#include    <caf/manager.h>
#include    <caf/virtualpathptr.h>

#include    "cvtuifeaturemanager.h"
#include    "cvtuicomponentmanager.h"
#include    "cvtuicommandmanager.h"
#include    "tvtuistates.h"
#include    "cvtuimenus.h"
#include    "cvtuisoftkeys.h"
#include    "cvtuitoolbarbase.h"
#include    "cvtuiwhitebalance.h"
#include    "cvtuicolortone.h"
#include    "cvtuibrightness.h"
#include    "cvtuicontrast.h"
#include    <remconinterfaceselector.h>
#include    <remconcoreapitarget.h>
#include    <remconcoreapitargetobserver.h>
#include    "tvtuiwsevent.h"
#include    "mvtuinumbersource.h"
#include    "tVtuifeaturevariation.h"
#include    "cvtuidialer.h"
#include    "tvtuiappstates.h"
#include    "cvtuivolume.h"
#include    "cvtuizoom.h"
#include    "cvtuivolumecontrol.h"

using namespace ContentAccess;

// CONSTANTS

// Engine orientation to application orientation map
const CVtUiAppUi::TAppUiOrientation engToAppOrientation[] = {
    CVtUiAppUi::EAppUiOrientationLandscape,
    CVtUiAppUi::EAppUiOrientationPortrait,
    CVtUiAppUi::EAppUiOrientationUnspecified };

// Amount of help contexts.
const TInt KVtUiHelpContextAmount = 1;

// UID of Video Telephone application.
const TUid KVtUiAppUid = { KVtUiAppUidValue };

// Granularity of command observer array.
const TInt KVtUiCommandObserverArrayGranularity = 5;

// Default call index.
const TInt KVtUiDefaultCallId = 1;

// Control priority for the blank control. Above all other controls.
const TInt KVtUiBlankControlPriority =
    ECoeStackPriorityEnvironmentFilter + 100;

// Exit timeout.
const TInt KVtUiExitTimeout = 10000000;

// UID of the main telephone application
const TUid KVtUiTelephoneUid = { 0x100058B3 };

// Reset value for volume
const TInt  KVolumeResetValue = -1;

// Remote video control normal priority
const TInt KVtUiRemoteVideoControlOrdinalPriNormal = 0;

// Remote video control high priority
const TInt KVtUiRemoteVideoControlOrdinalPriHigh = 2;

// Name of the EIKON server window group.
_LIT( KVtUiEikonServer, "EikonServer" );

// Name of the AknCapServer window group.
_LIT( KVtUiAknCapServer, "*akncapserver*" );

// Name of the AknNotifierServer window group.
_LIT( KVtUiAknNotifierServer, "*aknnfysrv*" );

// Volume repeat delay.
const TInt KVtUiVolumeRepeatDelay = KAknStandardKeyboardRepeatRate;

// Volume repeat long delay.
const TInt KVtUiVolumeRepeatLongDelay = KAknKeyboardRepeatInitialDelay;

// Start time for toolbar timer
const TTimeIntervalMicroSeconds32 KStartTime( 600000 );

// period time for toolbar timer
const TTimeIntervalMicroSeconds32 KPeriodTime( 300000 );

// The maximum frequency that user can swap image places.
const TInt64 KVtUiMaxSwapImagesFreq( 1000000 );

// Enumerates methods used in event handling. This enumeration MUST
// match with methodArray local array.
enum TVtUiHandleEvents
    {
    // Refresh states
    EVtUiRefreshStates =                    1 << 0,
    // Handle remote problem.
    EVtUiHandleVideoFrameRemoteProblem =    1 << 1,
    // Handle local problem.
    EVtUiHandleVideoFrameLocalProblem =     1 << 2,
    // Refresh navipane.
    EVtUiRefreshNaviPane =                  1 << 3,
    // Refresh softkeys.
    EVtUiRefreshSoftkeys =                  1 << 4,
    // Refresh blind icon status.
    EVtUiRefreshBlind =                     1 << 5,
    // Stop showing waiting image text.
    EVtUiStopWaitingImage =                 1 << 6,    
    // Rx resolution changed.
    EVtUiChangeRemoteVideoLayout =          1 << 7,
    // Show initializing image progress
    EVtUiShowImageInitializingProgress =    1 << 8,
    // Hide initializing image progress
    EVtUiHideImageInitializingProgress =    1 << 9,
    // Set camera orientation
    EVtUiSetOrientation =                   1 << 10,
    //Handle media status change
    EVtUiMediaStateChanged =                1 << 11,
    //Show decoding error note
    EVtUiShowDecodingError =                1 << 12,
    // Stop the white balance and color tone
    EVtUiStopWBOrColortone =                1 << 13,
    // refresh Menu
    EVtUiRefreshMenu =                      1 << 14,
    // Stop brightness and contrast slider
    EVtUiStopBrightnessOrContrast =         1 << 15,
    // refresh zoom popup
    EVtUiRefreshZoomPopup =                           1 << 16
    };

// Enumerates states for CVtUiActiveExec.
enum
    {
    // Operation finished. Must equal to zero.
    EVtUiAppUiNone,

    // Active execution states for iActiveExec:

    // Startup (prepare engine):
    EVtUiAppUiStartup = 100,                             // 100
    //     Close dialogs.
    EVtUiAppUiStartupCloseDialogs = EVtUiAppUiStartup,   // 100
    //     Initialise engine.
    EVtUiAppUiStartupInitEngine,                         // 101
    //     Prepare viewfinder.
    EVtUiAppUiStartupPrepareViewfinder,                  // 102
    //     Prepare remote render.
    EVtUiAppUiStartupPrepareRemoteRender,                // 103
    //     Remove blank.
    EVtUiAppUiStartupRemoveBlank,                        // 104

    // Shutdown (reset engine):
    EVtUiAppUiShutdown = 300,                            // 300
    //     Close dialogs.
    EVtUiAppUiShutdownCloseDialogs = EVtUiAppUiShutdown, // 300
    //     Hide application.
    EVtUiAppUiShutdownHideApplication,                   // 301
    //     Reset engine.
    EVtUiAppUiShutdownResetEngine,                       // 302
    //     Remove blank.
    EVtUiAppUiShutdownRemoveBlank,                       // 303

    // Answered:
    EVtUiAppUiAnswered = 500,                            // 500
    //     Show blank dialog.
    EVtUiAppUiAnsweredStart = EVtUiAppUiAnswered,        // 500
    //     Refresh navipane.
    EVtUiAppUiAnsweredRefreshNavi,                       // 501
    //     Refresh softkeys.
    EVtUiAppUiAnsweredRefreshSoftkeys,                   // 502
    //     Start remote render.
    EVtUiAppUiAnsweredStartRemoteRender,                 // 503

    //     Prepares camera
    EVtUiAppUiAnsweredCheckCamera,                       // 504
    //     Choose if it's needed to show query or directly activate camera.
    EVtUiAppUiAnsweredChoose,                            // 505
    //     Set still image as source.
    EVtUiAppUiAnsweredQuerySetupStill,                   // 506
    //     Set none as source.
    EVtUiAppUiAnsweredQuerySetupNone,                    // 507
    //     Start viewfinder.
    EVtUiAppUiAnsweredQuerySetupStart,                   // 508
    //     Show "allow video image" query.
    EVtUiAppUiAnsweredQueryShow,                         // 509
    //     Check if user allowed video image.
    EVtUiAppUiAnsweredQueryDecide,                       // 510
    //     Select camera as source.
    EVtUiAppUiAnsweredQuerySelectCamera,                 // 511
    //     Select still image as source.
    EVtUiAppUiAnsweredQuerySelectStill,                  // 512
    //     Select none as source.
    EVtUiAppUiAnsweredQuerySelectNone,                   // 513
    //     Start viewfinder.
    EVtUiAppUiAnsweredQueryStartViewfinder,              // 514
    //     Finish.
    EVtUiAppUiAnsweredQueryFinish,                       // 515
    //     Select camera as source.
    EVtUiAppUiAnsweredSelectCamera,                      // 516
    //     Select still image as source.
    EVtUiAppUiAnsweredSelectStill,                       // 517
    //     Select none as source.
    EVtUiAppUiAnsweredSelectNone,                        // 518
    //     Start viewfinder.
    EVtUiAppUiAnsweredStartViewfinder,                   // 519
    //     Finish.
    EVtUiAppUiAnsweredFinish,                            // 520

    //     Prepares camera
    EVtUiAppUiAnsweredDoPrepareCamera                   // 521
    };

/**
* Enumerates background layers
*/
enum TVtUiBackgroundLayers
    {
    // Idle state background.
    EVtUiLayerBackground = 0,
    // Wallpaper layout.
    EVtUiLayerWallpaper = 1,
    // Amount of layers.
    EVtUiLayerCount = 2
    };

// MODULE DATA STRUCTURES

/**
* Asynchronous command executor that does not use dialog for waiting the
* execution completion.
* @since Series 60 5.0
*/
class CVtEngCmdExec : public CBase, private MVtEngCommandObserver
    {

public:
    /**
    * Static constructor.
    */
    static CVtEngCmdExec* NewL( MVtEngCommandHandler& aCommandHandler,
        MVtUiEngineCommandManager& aCommandManager,
        CEikButtonGroupContainer& aCBA );

    /**
    * Executes given command asynchronously, waiting the command completion.
    */
    void ExecuteCmdLD( const TVtEngCommandId aCommandId );

    /**
    * Destructor.
    */
    ~CVtEngCmdExec();

private: // from MVtEngCommandObserver

    /**
    * @see MVtEngCommandObserver::HandleVTCommandPerformedL
    */
    void HandleVTCommandPerformedL( TVtEngCommandId aCommand,
        const TInt aError );

private:

    /**
    * Constructor.
    */
    CVtEngCmdExec( MVtEngCommandHandler& aCommandHandler,
        MVtUiEngineCommandManager& aCommandManager,
        CEikButtonGroupContainer& aCBA );

private:

    CActiveSchedulerWait iWait;

    MVtEngCommandHandler& iCommandHandler;

    MVtUiEngineCommandManager& iCommandManager;

    TVtEngCommandId iCommandId;

    CEikButtonGroupContainer& iCBA;

    };

// -----------------------------------------------------------------------------
// CVtEngCmdExec::NewL
// -----------------------------------------------------------------------------
//
CVtEngCmdExec* CVtEngCmdExec::NewL( MVtEngCommandHandler& aCommandHandler,
    MVtUiEngineCommandManager& aCommandManager, CEikButtonGroupContainer& aCBA )
    {
    CVtEngCmdExec* self = new ( ELeave ) CVtEngCmdExec( aCommandHandler,
        aCommandManager, aCBA );
    return self;
    }

// -----------------------------------------------------------------------------
// CVtEngCmdExec::ExecuteCmdLD
// -----------------------------------------------------------------------------
//
void CVtEngCmdExec::ExecuteCmdLD( const TVtEngCommandId aCommandId )
    {
    __VTPRINTENTER("CVtEngCmdExec::ExecuteCmdLD")
    CleanupStack::PushL( this );
    iCommandId = aCommandId;
    iCommandManager.AddObserverL( *this );
    iCommandHandler.ExecuteL( aCommandId, NULL );
    iCBA.SetCommandSetL( R_VIDEOTELUI_SOFTKEYS_EMPTY );
    iCBA.DrawNow();
    iWait.Start();
    CleanupStack::PopAndDestroy(); // this
    __VTPRINTEXIT("CVtEngCmdExec::ExecuteCmdLD")
    }

// -----------------------------------------------------------------------------
// CVtEngCmdExec::~CVtEngCmdExec
// -----------------------------------------------------------------------------
//
CVtEngCmdExec::~CVtEngCmdExec()
    {
    __VTPRINTENTER("CVtEngCmdExec::~CVtEngCmdExec")
    if ( iWait.IsStarted())
        {
        __VTPRINT(DEBUG_GEN, "CVtEngCmdExec::~CVtEngCmdExec AsyncStop")
        iWait.AsyncStop();
        }
    iCommandManager.RemoveObserver( *this );
    __VTPRINTEXIT("CVtEngCmdExec::~CVtEngCmdExec")
    }

// -----------------------------------------------------------------------------
// CVtEngCmdExec::HandleVTCommandPerformedL
// -----------------------------------------------------------------------------
//
void CVtEngCmdExec::HandleVTCommandPerformedL( TVtEngCommandId aCommand,
        const TInt aError )
    {
    __VTPRINTENTER("CVtEngCmdExec::HandleVTCommandPerformedL")
    if ( iCommandId == aCommand )
        {
         if ( iWait.IsStarted())
            {
            __VTPRINT(DEBUG_GEN, "CVtEngCmdExec::HandleVTCommandPerformedL AsyncStop")
            iWait.AsyncStop();
            }
        else
            {
            // request already completed
            }
        }
    else
        {
        // wrong command ID
        }
    __VTPRINTEXIT("CVtEngCmdExec::HandleVTCommandPerformedL")
    }

// -----------------------------------------------------------------------------
// CVtEngCmdExec::CVtEngCmdExec
// -----------------------------------------------------------------------------
//
CVtEngCmdExec::CVtEngCmdExec( MVtEngCommandHandler& aCommandHandler,
    MVtUiEngineCommandManager& aCommandManager, CEikButtonGroupContainer& aCBA )
    : iCommandHandler( aCommandHandler ),
      iCommandManager( aCommandManager ), iCBA( aCBA )
    {
    }
    
/**
* Encapsulates all instances related to user interface.
* @since Series 60 2.6
*/
class CVtUiAppUi::CInstance
    : public CBase
    {
    public: // Constructors and destructors

        /**
        * Two-phased constructor.
        * @param aAppUi reference to application UI.
        */
        static CInstance* NewL( CVtUiAppUi& aAppUi );

        /**
        * Destructor.
        */
        ~CInstance();

        /**
        * Called when side volume key is pressed.
        */
        void VolumeKeyPressedL();

        /**
        * Create remote video control.
        */        
        void CreateRemoteVideoControl();

    private:

        /**
        * Constructor.
        */
        CInstance( CVtUiAppUi& aAppUi );

        /**
        * Symbian OS constructor.
        */
        void ConstructL();

        /**
        * Relayout controls.
        */
        void LayoutChanged();

    private:

        // Parent can access members.
        friend class CVtUiAppUi;

        // Ref to application UI.
        CVtUiAppUi& iAppUi;

        // Owned bitmap manager.
        CVtUiBitmapManager* iBitmapManager;

        // ETrue if iMainControl has been added to stack.
        TBool iMainControlInStack;

        // Owned main pane control.
        CVtUiMainControl* iMainControl;

        // ETrue if iContextControl has been added to stack.
        TBool iContextControlInStack;

        // Owned context pane control.
        CVtUiContextControl* iContextControl;

        // Owned remote video control.
        CVtUiRemoteVideoControl* iRemoteVideoControl;
        
        //ETrue if iRemoteVideoControl has been added to stack.
        TBool iRemoteVideoControlInStack;

        // Owned navi pane controller.
        CVtUiNaviPane* iNaviPane;

        // ETrue if number entry has been added to stack.
        TBool iNumberEntryInStack;

        // Owned number entry activation control.
        CVtUiNumberEntryActivationControl* iNumberEntryActivation;
        
        // Owned button pane control
        CVtUiEndCallButtonPane* iEndCallButtonPane;
        
        // ETrue if iButtonPane has been added to stack.
        TBool iButtonPaneInStack;

    };

/**
* Encapsulates event handling.
* @since Series 60 2.6
*/
class CVtUiAppUi::CEventObserver
    : public CBase,
      public MVtUiEngineCommandManager,
      public MVtEngEventObserver,
      public MVtEngCommandObserver,
      public MVtEngFrameObserver,
      private MBeating,
      private MRemConCoreApiTargetObserver
    {
    public: // Constructors and destructors

        /**
        * Two-phased constructor.
        * @param aAppUi application UI.
        */
        static CEventObserver* NewL( CVtUiAppUi& aAppUi );

        /**
        * Destructor.
        */
        ~CEventObserver();

    public: // New functions

        /**
        * Returns engine model.
        * @return model instance.
        */
        inline CVtEngModel& Model();
        
        /**
        * Creates remote control framework session.
        */
        void CreateRemConSessionL();

        /**
        * Deletes remote control framework session.
        */
        void DeleteRemConSession();

        /**
        * Checks if command is supported by engine.
        * @param aCommandId command.
        * @return ETrue if supported, EFalse otherwise.
        */
        TBool CommandSupported( const TInt aCommandId ) const;

        /**
        * Checks if command is supported and synchronous.
        * @param aCommandId command.
        * @return ETrue if synchronous & supported, EFalse otherwise.
        */
        TBool CommandSupportedAndSynchronous(
            const TInt aCommandId ) const;

        /**
        * Starts heartbeat timer.
        */
        void StartBeatL();

        /**
        * Stops heartbeat timer.
        */
        void StopBeat();

        /**
        * Stops volume repeat handling timer.
        */
        void StopVolumeRepeatTimer();
        
        /**
        * Sends response to prepare.
        * @param aResult result code.
        */
        void SendPrepareResponse( const TInt aResult );

    public: // Functions from base classes

        /**
        * @see MVtUiCommandManager::AddObserverL.
        */
        virtual void AddObserverL( MVtEngCommandObserver& aObserver );

        /**
        * @see MVtUiCommandManager::RemoveObserver.
        */
        virtual void RemoveObserver( MVtEngCommandObserver& aObserver );

        /**
        * @see MVtEngEventObserver::HandleVtEventL.
        */
        virtual void HandleVtEventL( TInt aEvent );

        /**
        * @see MVtEngCommandObserver::HandleVTCommandPerformedL.
        */
        virtual void HandleVTCommandPerformedL(
            TVtEngCommandId aCommand,
            const TInt aError );

        /**
        * @see MVtEngFrameObserver::vtHandleFrameL.
        */
        virtual void vtHandleFrameL( TFrameType aType, CFbsBitmap* aBitmap );

        /**
        * @see MVtEngFrameObserver::vtSetFrame
        */
        virtual void vtSetFrame( TFrameType aType, CFbsBitmap* aBitmap );

        /**
        * @see MBeating::Beat.
        */
        virtual void Beat();

        /**
        * @see MBeating::Synchronize.
        */
        virtual void Synchronize();


    private:

        /**
        * Constructor.
        * @param aAppUi application UI.
        */
        CEventObserver( CVtUiAppUi& aAppUi );

        /**
        * Symbian OS constructor.
        */
        void ConstructL();

        /**
        * Executes CVtUiAppUi methods.
        * @param aBits sum of subset of TVtUiHandleEvents.
        */
        void DoExecuteL( TInt aBits );
        /**
        * Handles volume change.
        * @param aButtonAct button action.
        */
        void HandleVolumeChange(
            TRemConCoreApiButtonAction aButtonAct );
        /**
        * Handles mute change.
        * @param aButtonAct button action.
        */
        void HandleRemMuteChange(
            TRemConCoreApiButtonAction aButtonAct );
        /**
        * @see MRemConCoreApiTargetObserver::MrccatoCommand.
        */
        virtual void MrccatoCommand(
            TRemConCoreApiOperationId aOperationId,
            TRemConCoreApiButtonAction aButtonAct );

        /**
        * Callback function to handle volume repeat.
        * @param aAny pointer to an instance of this class.
        * @return KErrNone.
        */
        static TInt DoHandleVolumeRepeat( TAny* aAny );

    private:

        // Type definition for CVtUiAppUi member functions.
        typedef void (CVtUiAppUi::*TMethodL)();

        // Ref to application ui.
        CVtUiAppUi& iAppUi;

        // Engine model.
        CVtEngModel* iModel;

        // ETrue when command events are being sent.
        TBool iInCommandPerformed;

        // Owned array of observers.
        RPointerArray< MVtEngCommandObserver > iCommandObservers;

        // Owned heart beat timer to update call duration.
        CHeartbeat* iBeat;
        

        // Owned interface selector instance.
        CRemConInterfaceSelector* iRemConInterfaceSelector;

        // Pointer to target instance. Owned by iRemConInterfaceSelector.
        CRemConCoreApiTarget* iRemConCoreApiTarget;

        // Owned timer for volume repeat handling.
        CPeriodic* iRemConVolumeRepeatTimer;

        // Rencon operation id
        TRemConCoreApiOperationId iRCCAOperationId;

    };

/**
* Verifies objects fetched using media gallery. Only non DRM protected
* objects are allowed.
* @since Series 60 3.1
*/
class CVtUiAppUi::CVtUiAppUiMGVerifier :
    public CBase,
    public MMGFetchVerifier
    {
    public:

            /**
            * Static constructor, pushes created instance into cleanup stack.
            */
        static CVtUiAppUiMGVerifier* NewLC(
            CVtUiAppUi& aAppUi, CCoeEnv& aCoeEnv );

            /**
            * Destructor.
            */
        ~CVtUiAppUiMGVerifier();

    public: // from MMGFetchVerifier

        /**
            * @see MMGFetchVerifier::VerifySelectionL
            */
        TBool VerifySelectionL( const MDesCArray* aSelectedFiles );

    private:

            /**
            * 2nd constructor in two phase construction.
            */
        void ConstructL();

        /**
            * Constructor.
            */
        CVtUiAppUiMGVerifier( CVtUiAppUi& aAppUi, CCoeEnv& aCoeEnv );

    private:

        // Reference to Application UI
        CVtUiAppUi& iAppUi;

        // Pointer to COE
        CCoeEnv* iCoeEnv;

        // Pointer to CManager which manages files and content access agents
        CManager* iManager;
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiAppUi::CVtUiAppUi
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CVtUiAppUi()
    : iRenderingMode( ERenderingModeDefault ),
      iLoudspeakerVolume( KVolumeResetValue ),
      iHandsetVolume( KVolumeResetValue ),
      iActiveCommands( 1 ),
      iLayoutChg( EFalse ),
      iDelayedCmd( 0 )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ConstructL()
    {
    VTLOGINIT
    __VTPRINTENTER( "VtUi.ConstructL" )

    FeatureManager::InitializeLibL();
    BaseConstructL( EAknEnableSkin | EAknEnableMSK | EAknSingleClickCompatible );
    
    iCba = Cba();
    // Must be done before creating features
    iVTVariation.ReadL();

    iEventObserver = CEventObserver::NewL( *this );
    iUiStates = new ( ELeave ) TVtUiStates( iEventObserver->Model() );
    iUiStates->Update();
        iUiStates->SetViewFindersInitialPlaceContextPane( ETrue );
        
    TVtUiAppStateBase::SetInitialStateL( *this, *iUiStates );

    iCommandManager = CVtUiCommandManager::NewL( *iUiStates, *this );

    iComponentManager = CVtUiComponentManager::NewL();

    iFeatureManager = CVtUiFeatureManager::NewL( *this, *iUiStates,
         *iCommandManager, *iComponentManager );

    iInstance = CInstance::NewL( *this );

    CEikMenuBar* menu = iEikonEnv->AppUiFactory()->MenuBar();
    menu->SetContextMenuTitleResourceId( R_VIDEOTELUI_OK_MENUBAR );



    CEikonEnv& eikEnv = *( iEikonEnv );
    eikEnv.SetSystem( ETrue );
    eikEnv.WsSession().ComputeMode( RWsSession::EPriorityControlDisabled );

    iThisApplicationWgId = eikEnv.RootWin().Identifier();
    iEikonServerWgId =
        eikEnv.WsSession().FindWindowGroupIdentifier( 0, KVtUiEikonServer );
    iAknCapServerWgId =
        eikEnv.WsSession().FindWindowGroupIdentifier( 0, KVtUiAknCapServer );
    iAknNfyServerWgId =
        eikEnv.WsSession().FindWindowGroupIdentifier( 0,
            KVtUiAknNotifierServer );

    __ASSERT_ALWAYS(
        iEikonServerWgId != KErrNotFound,
        VtUiPanic::Panic( EVtUiPanicEikonServerNotFound ) );
    (void)eikEnv.RootWin().EnableFocusChangeEvents();


    iUplinkWindow = iInstance->iContextControl;
    iDownlinkWindow = iInstance->iMainControl;


    if ( iCba )
        {
        CCoeControl* control = iCba->ButtonGroup()->AsControl();
        static_cast< CEikCba* >( control )->
            SetSkinBackgroundId( KAknsIIDQsnBgAreaControlIdle );
        }

    iBlankControl = new ( ELeave ) CVtUiBlankControl;
    iBlankControl->ConstructL( ClientRect() );
    AddToStackL(
        iBlankControl,
        KVtUiBlankControlPriority,
        ECoeStackFlagRefusesFocus );

    iUiStates->SetBlankControlAdded( ETrue );

    iActiveExec =
        new ( ELeave ) CVtUiActiveExec( CActive::EPriorityHigh );
    SetCallIdL( KVtUiDefaultCallId );

    iExitTimer = CPeriodic::NewL( CActive::EPriorityHigh );
    CheckEngineFunctionality();

    iAsyncCallback =
        new ( ELeave ) CAsyncCallBack (
            TCallBack( &AsyncViewFinderToMainPaneAndShare, this ),
            CActive::EPriorityStandard );

    iLayoutChangeCallback =
        new ( ELeave ) CAsyncCallBack(
            TCallBack( &DelayedHandleLayoutChanged, this ),
            CActive::EPriorityStandard );

    iCurrentCameraOrientation = MVtEngMedia::EOrientationObeyLayoutSwitch;

    GetCameraOrientations();

    SetInitialCameraOrientationL();

    iVolCtrl= new ( ELeave )CVtUiVolumeControl(
        Model().CommandHandler(),
        Model().Audio(),
        *iEventObserver,
        *iFeatureManager);
    iVolCtrl->ConstructL();

    iIncallBubble = CAknIncallBubble::NewL();

    iIsWaitingCallState = EFalse;
    
    __VTPRINTEXIT( "VtUi.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::~CVtUiAppUi
// -----------------------------------------------------------------------------
//
CVtUiAppUi::~CVtUiAppUi()
    {
    __VTPRINTENTER( "VtUi.~" )

    iActiveCommands.Close();

    delete iLayoutChangeCallback;
    delete iAsyncCallback;

    if ( iUiStates && iUiStates->IsBlankControlAdded() )
        {
        RemoveFromStack( iBlankControl );
        }
    TInt lightsValue = 0;
    if ( RProperty::Get( KPSUidCoreApplicationUIs,
            KLightsVTForcedLightsOn, lightsValue ) == KErrNone )
        {
        if ( lightsValue == EForcedLightsOn )
            {
            __VTPRINT( DEBUG_GEN, "VtUi.~ Good night!" )
            (void) RProperty::Set(
                KPSUidCoreApplicationUIs,
                KLightsVTForcedLightsOn,
                EForcedLightsOff );
            }
        }
    delete iActiveExec;
    delete iInstance;
    delete iBlankControl;
    // Delete volume control before its dependencies are deleted.
    delete iVolCtrl;
    delete iEventObserver;
    delete iExitTimer;
    // Featuremanager must be destructed
    // before componentmanager and commandmanager
    delete iFeatureManager;
    delete iComponentManager;
    delete iCommandManager;
    delete iUiStates;

    if ( iTbPeriodic )
        {
        iTbPeriodic->Cancel();
        }
    delete iTbPeriodic;

    if ( iIncallBubble )
        {
        TRAP_IGNORE( iIncallBubble->SetIncallBubbleAllowedInUsualL( ETrue ) )    
        }
    delete iIncallBubble;

    // Close all RComm sessions to prevent memory leaks.
    REComSession::FinalClose();

    FeatureManager::UnInitializeLib();
    __VTPRINTEXIT( "VtUi.~" )
    VTLOGUNINIT
    }

// -----------------------------------------------------------
// CVtUiAppUi::SwitchLayoutToFlatStatusPaneL
// -----------------------------------------------------------
//
void CVtUiAppUi::SwitchLayoutToFlatStatusPaneL( TBool aSwitch )
    {
    __VTPRINTENTER( "VtUi.SwitchLayoutToFlatStatusPaneL" )
    CEikStatusPane* statusPane = StatusPane();

    const TInt idleResId(
        VtUiLayout::IsLandscapeOrientation() ?
            R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL :
                R_AVKON_STATUS_PANE_LAYOUT_USUAL );

    const TBool isStatusPaneFlat(
        ( statusPane->CurrentLayoutResId() ==
            R_AVKON_WIDESCREEN_PANE_LAYOUT_USUAL_FLAT ) ||
        ( statusPane->CurrentLayoutResId() ==
            R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT ) );

    if ( aSwitch )
        {
        if ( isStatusPaneFlat && VtUiLayout::IsLandscapeOrientation() )
            {
            __VTPRINT( DEBUG_GEN,
                "VtUi.SwitchLayoutToFlatStatusPaneL LAYOUT USUAL" );
            statusPane->SwitchLayoutL( idleResId );
            }
        else if ( !isStatusPaneFlat && !VtUiLayout::IsLandscapeOrientation() )
            {
            __VTPRINT( DEBUG_GEN,
                "VtUi.SwitchLayoutToFlatStatusPaneL USUAL FLAT" );
            statusPane->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL_FLAT );
            }
        }
    else
        {
        if ( isStatusPaneFlat )
            {
            __VTPRINT( DEBUG_GEN,
                "VtUi.SwitchLayoutToFlatStatusPaneL LAYOUT IDLE" );
            statusPane->SwitchLayoutL( idleResId );
            }
        }
    // ApplyCurrentSettingsL is called whenever statuspane
    // visibility status or pane layout changes.
    statusPane->ApplyCurrentSettingsL();
    statusPane->DrawNow();
    // Make sure whole control is fully updated
    iInstance->iMainControl->DrawNow();
    __VTPRINTEXIT( "VtUi.SwitchLayoutToFlatStatusPaneL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshL()
    {
    __VTPRINTENTER( "VtUi.Refresh" )
    RefreshBlind();
    RefreshNaviPaneL();    
    __VTPRINTEXIT( "VtUi.Refresh" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshNaviPaneL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshNaviPaneL()
    {
    // Update only if navi pane exists
    if ( iInstance )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.RefreshNavi" )
        CVtUiNaviPane* navi = iInstance->iNaviPane;

        // Refresh muted state
        MVtEngMedia& media = Model().Media();
        TInt mediaAvail;
        VtUiUtility::GetOutgoingMediaState( media, mediaAvail );
        mediaAvail = ~mediaAvail;
        navi->SetMuted( mediaAvail & MVtEngMedia::EMediaAudio );

        // Refresh call duration
        MVtEngSessionInfo& session = Model().Session();
        MVtEngSessionInfo::TDuration duration;
        TBool enabled;
        if ( session.GetDuration( duration, enabled ) != KErrNone )
            {
            enabled = EFalse;
            }
        navi->SetCallDuration( duration, enabled );

        // Update all changes
        navi->CommitL();

        CheckBeatL( enabled );
        }
    }

void CVtUiAppUi::StopBrightnessOrContrast()
    {
    
    MVtUiFeature* br = iFeatureManager->GetFeatureById( EVtUiFeatureIdBrightness );
    if ( br )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.StopBrightness" )
        if ( br->State() ==  MVtUiFeature::EActive )
            {
            __VTPRINT( DEBUG_GEN, "VtUi.StopBrightnessOrContrast br->STOP" )
            br->Stop();
            }
        }
    
    MVtUiFeature* cr = iFeatureManager->GetFeatureById( EVtUiFeatureIdContrast );
    if ( cr )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.StopContrast" )
        if ( cr->State() ==  MVtUiFeature::EActive )
           {
           __VTPRINT( DEBUG_GEN, "VtUi.StopBrightnessOrContrast cr->STOP" )
           cr->Stop();
           }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshZoomPopupL()
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshZoomPopupL()
    {
    CVtUiZoom* zm = static_cast< CVtUiZoom* >(
            iFeatureManager->GetFeatureById( EVtUiFeatureIdZoom ) );
    if( zm && iUiStates->IsZoomModeOn())
        zm->RefreshL();
    }
// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshMenuL()
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshMenuL()
    {
    
    CVtUiMenus* menus = static_cast< CVtUiMenus* >(
            iFeatureManager->GetFeatureById( EVtUiFeatureIdMenu ) );
    if ( menus )
    {
        iUiStates->Update();
        __VTPRINT( DEBUG_GEN, "VtUi.RefreshMenuL" )
        menus->RefreshL();
        CAknAppUi::ProcessCommandL( EEikCmdCanceled ); // does not leave
        }
    }
              
// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshSoftkeysL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshSoftkeysL()
    {
    if ( iUiStates->IsThisApplicationForeground() )
        {
        CVtUiSoftkeys* sk = static_cast< CVtUiSoftkeys* >(
            iFeatureManager->GetFeatureById( EVtUiFeatureIdSoftkey ) );
        if ( sk )
            {
            sk->RefreshL();
            }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshBlind
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshBlind()
    {
    if ( iInstance && !iUiStates->IsDisableBlindSetting() )
        {
        __VTPRINTENTER( "VtUi.RefreshBlind" )
        TInt avail;
        MVtEngMedia& media = Model().Media();

        // Update blind flags.for outgoing media:
        VtUiUtility::GetOutgoingMediaState( media, avail );
        avail = ~avail;
        TBool noVideo( avail & MVtEngMedia::EMediaVideo );
        const TBool isFrozen( VtUiUtility::GetFreezeState ( media ) );
        MVtEngMedia::TMediaSource source( MVtEngMedia::EMediaNone );
        media.GetSource( source );
        if ( noVideo && !isFrozen &&
            ( source != MVtEngMedia::EMediaStillImage ) )
            {
            iUplinkWindow->SetStreamBitmap( NULL );
            }

        iUplinkWindow->SetBlind( noVideo );
        iUplinkWindow->SetWaiting( EFalse );

        if ( iUiStates->IsThisApplicationForeground() )
            {
            // Update blind flags for incoming media:
            VtUiUtility::GetIncomingMediaState( media, avail );
            avail = ~avail;
            noVideo = ( avail & MVtEngMedia::EMediaVideo );
            if ( noVideo )
                {
                iDownlinkWindow->SetStreamBitmap( NULL );
                }
            iDownlinkWindow->SetBlind( noVideo );
            }
        iDownlinkWindow->SetWaiting( iUiStates->IsWaitingForFirstFrame() );
        __VTPRINTEXIT( "VtUi.RefreshBlind" )
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::OpenNumberEntryL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::OpenNumberEntryL()
    {
    __VTPRINTENTER( "VtUi.OpenNumberEntryL" )

    CEikMenuBar* menuBar = iEikonEnv->AppUiFactory()->MenuBar();
    if ( IsDisplayingDialog() || ( menuBar && menuBar->IsDisplayed() ) )
        {
        __VTPRINTEXIT( "VtUi.OpenNumberEntryL" )
        return EFalse;
        }

    TInt error( KErrNotFound );

    MVtUiFeature* numberEntry =
        iFeatureManager->GetFeatureById( EVtUiFeatureIdNumberEntry );

    MVtUiFeature* dialer =
        iFeatureManager->GetFeatureById( EVtUiFeatureIdDialer );

    const TBool dialerActive( dialer &&
        ( dialer->State() == MVtUiFeature::EActive ) );

    if ( numberEntry && !dialerActive )
        {
        TRAP( error, numberEntry->StartL() );
        }

    const TBool result( !error );

    if ( result )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.NumberEntry.StopZ" )
        RefreshSoftkeysL();
        }

    __VTPRINTEXITR( "VtUi.OpenNumberEntryL %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandlePhoneSendKeyL
// Handles EKeyPhoneSend key events.
// -----------------------------------------------------------------------------
//
TKeyResponse CVtUiAppUi::HandlePhoneSendKeyL( const TKeyEvent& /*aKeyEvent*/,
    TEventCode aType )
    {
    __VTPRINTENTER( "VtUi.HandlePhoneSendKeyL" )
    CEikMenuBar* menuBar = iEikonEnv->AppUiFactory()->MenuBar();
    if ( !( IsDisplayingDialog() || ( menuBar && menuBar->IsDisplayed() ) ) )
        {
        const TBool isNumberSource( iUiStates->IsNumberEntryOpen() ||
            iUiStates->IsDialerOpen() );
        if ( ( aType == EEventKey ) && isNumberSource )
            {
            ProcessCommandL( EVtUiCmdDialEmergency );
            }
        }
    __VTPRINTEXIT( "VtUi.HandlePhoneSendKeyL" )
    return EKeyWasConsumed;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::StartDtmfTone
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::StartDtmfTone( const TChar& aTone )
    {
    // should be called only through current application state
    iDtmfTone = aTone;
    __VTPRINT2( DEBUG_GEN, "VtUi.DTMF.Start.%d", iDtmfTone() )
    if ( Execute( KVtEngStartDtmfTone, &iDtmfTone ) != KErrNone )
        {
        iDtmfTone = 0;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::StopDtmfTone
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::StopDtmfTone()
    {
    // should be called only through current application state
    if ( iDtmfTone() )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.DTMF.STOP" )
        (void) Execute( KVtEngStopDtmfTone, NULL );
        iDtmfTone = 0;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleWsEventL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleWsEventL(
        const TWsEvent& aEvent,
        CCoeControl* aDestination )
    {
    __VTPRINTENTER( "VtUi.HandleWsEventL" )
    const TInt type = aEvent.Type();
    __VTPRINT2( DEBUG_GEN, "VtUi.HandleWsEventL type = %d", type );

    // Zoom-in and Zoom-out keys need specific handling because keyup and
    // keydown events cannot be checked from iCode field of TKeyEvent
    if ( PreHandleKeyEventL( aEvent ) )
        {
        __VTPRINTEXIT( "VtUi.HandleWsEventL (PreHandleKeyEventL)" )
        return;
        }

    // Zoom mode is dismissed if some interrupting event happens prior timeout.
    // Zoom mode can be interrupted with a  keypress i.e. any keypress, except
    // keys that are reserved for adjusting zoom dismiss zoom mode. Also any
    // system event e.g. note or waiting call dismiss zoom mode.
    if ( iUiStates->IsZoomModeOn() )
        {
        if ( ProcessWsEventIfZoomModeIsActiveL( aEvent ) )
            {
            __VTPRINTEXIT( "VtUi.HandleWsEventL (IsZoomModeOn)" )
            return;
            }
        }
    // Zoom mode can be also activated with up and down arrow keys.
    switch ( type )
        {
        case EEventKey:
        case EEventKeyUp:
        case EEventKeyDown:
            {
            const TKeyEvent* keyEvent = aEvent.Key();
            const TBool isHwZoomKey(
                keyEvent->iCode == EKeyZoomIn ||
                keyEvent->iCode == EKeyZoomOut );
            const TBool isZoomKey(
                keyEvent->iScanCode == EStdKeyUpArrow ||
                keyEvent->iScanCode == EStdKeyDownArrow ||
                isHwZoomKey );

            // Zoom mode can be also activated with up and down arrow keys.
            if ( isZoomKey )
                {
                const TBool isZoomAllowed(
                    !iEikonEnv->AppUiFactory()->MenuBar()->IsDisplayed() &&
                    !iUiStates->MediaState().IsSharing() &&
                    !iUiStates->MediaState().IsFrozen() &&
                    !iUiStates->IsSelectingShare() &&
                    VtUiUtility::IsZoomAllowed( Model().Media() ) &&
                    !( iUiStates->IsNumberEntryOpen() && ShowNumberEntry() ) &&
                    //there must not be the command which may switch provider to None
                    !IsActiveCommand( EVtUiCmdDisableVideo )&&
                    !IsActiveCommand( EVtUiCmdDisableBoth )&&
                    !IsActiveCommand( EVtUiCmdUsePrimaryCamera )&&
                    !IsActiveCommand( EVtUiCmdUseSecondaryCamera) );

                if ( isZoomAllowed )
                    {
                     // If menu is open, toolbar is available, video is frozen,
                     // sharing is on or user is selecting a file to be shared
                     // do not set zoom mode on. If HW zoom key was pressed,
                     // then zoom mode is activated even if toolbar is present.
                    if ( isHwZoomKey || !iUiStates->IsToolbarAvailable() )
                        {
                        SetZoomModeL( ETrue );
                        }
                    }
                }
            }
            break;
        default:
            break;
        }

    TBool partialForeGroundlost( EFalse );
    switch ( type )
        {
        // Enter new rendering mode
        case EVtUiWsEventBeginRenderingMode:
            {
            const TVtUiWsEvent< TRenderingMode >& event(
               static_cast< const TVtUiWsEvent< TRenderingMode >& >
                ( aEvent ) );
            MVtUiDialer* dialer =  static_cast< CVtUiDialer* > (
                iFeatureManager->GetFeatureById( EVtUiFeatureIdDialer ) );
            __ASSERT_ALWAYS( dialer,
                VtUiPanic::Panic( EVtUiPanicRendererNotFound ) );
            iInstance->iContextControl->MakeVisible( EFalse );
            SetRenderingModeL( *event.Data(), &dialer->VideoWindow() );
            }
            break;

        // End rendering mode -> revert to previous
        case EVtUiWsEventEndRenderingMode:
            {
            SetRenderingModeL( ERenderingModeDefault, iStoredDownlinkWindow );
            iInstance->iContextControl->MakeVisible( ETrue );
            iStoredDownlinkWindow = NULL;
            }
            break;

        // New number source have been activated
        case EVtUiWsEventNumberSourceActivate:
            {
            const TVtUiWsEvent< MVtUiNumberSource >& event(
               static_cast< const TVtUiWsEvent< MVtUiNumberSource >& >
                ( aEvent ) );
            iNumberSource = event.Data();
            }
            break;

        case EVtUiWsEventNumberSourceDeactivate:
            {
            const TVtUiWsEvent< MVtUiNumberSource >& event(
               static_cast< const TVtUiWsEvent< MVtUiNumberSource >& >
                ( aEvent ) );
            if ( iNumberSource == event.Data() )
                {
                iNumberSource = NULL;
                }
            }
            break;


        // VT goes background e.g. selected application from fastswap
        case KAknFullOrPartialForegroundLost:
            {
            // If capture mode is on stop it
            if ( iUiStates->IsCaptureModeOn() )
                {
                CmdCancelCaptureL();
                }
            SetIncallBubbleAllowedInUsualL( ETrue );
            const TInt windowGroupId =
                iCoeEnv->WsSession().GetFocusWindowGroup();

            // In S60 5.0 we get PartialFocusLost also for some notes and
            // overally items that are somehow overlapping screen instead of
            // FocusLost. In those cases we should not put app to background.
            if( ( windowGroupId != iThisApplicationWgId ) &&
                ( windowGroupId != iEikonServerWgId ) &&
                ( windowGroupId != iAknCapServerWgId ) &&
                ( windowGroupId != iAknNfyServerWgId ) )
                {
                partialForeGroundlost = ETrue;
                }

            // Fall through to EEventFocusLost event
            }
        case EEventFocusLost:
            {
            // If focus window group is not this application nor window server,
            // then this application can not be in focus.
            const TInt windowGroupId = GetFocusWindowGroupId();

            if ( ( windowGroupId != iThisApplicationWgId ) &&
                 ( windowGroupId != iEikonServerWgId ) &&
                 ( windowGroupId != iAknCapServerWgId ) &&
                 ( windowGroupId != iAknNfyServerWgId ) || partialForeGroundlost )
                {
                iCoeEnv->RootWin().DisableFocusChangeEvents();

                TBool old = iUiStates->IsThisApplicationForeground();
                if ( old )
                    {
                    TRAP_IGNORE( HandleForegroundChangedL( EFalse ) );
                    }
                }
            }
            break;

        case EEventFocusGained:
        case KAknFullOrPartialForegroundGained:
            {
            SetIncallBubbleAllowedInUsualL( EFalse );
            // Now this application is focused.
            (void)iCoeEnv->RootWin().EnableFocusChangeEvents();
            TBool old = iUiStates->IsThisApplicationForeground();

            if ( !old )
                {
                (void) HandleLayoutChanged();
                TRAP_IGNORE( HandleForegroundChangedL( ETrue ) );
                }
            }
            break;

        case EEventKey:
        case EEventKeyUp:
        case EEventKeyDown:
            {
            // Key events with EModifierSpecial are received via FEP.
            const TKeyEvent* keyEvent = aEvent.Key();
            if ( keyEvent->iModifiers & EModifierSpecial )
                {
                TChar dtmfTone;
                if ( VtUiUtility::IsDTMFEvent( *keyEvent, dtmfTone ) )
                    {
                    if ( type == EEventKey )
                        {
                        StartDtmfTone( dtmfTone );
                        }
                    else if ( type == EEventKeyUp )
                        {
                        StopDtmfTone();
                        }
                    }
                }
            }
            break;

        default:
            break;
        }
    // Offer event to component manager
    iComponentManager->HandleWsEventL( aEvent, aDestination );

    // All events are sent to base class.
    CAknAppUi::HandleWsEventL( aEvent, aDestination );
    __VTPRINTEXIT( "VtUi.HandleWsEventL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::GetFocusWindowGroupId
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::GetFocusWindowGroupId()
    {
    __VTPRINTENTER( "VtUi.GetFocusWindowGroupId" )
    RWsSession& ws = iCoeEnv->WsSession();
    RArray<RWsSession::TWindowGroupChainInfo>* allWgIds = 
        new (ELeave) RArray<RWsSession::TWindowGroupChainInfo>( 4 );

    CleanupDeletePushL( allWgIds );
    CleanupClosePushL( *allWgIds );

    User::LeaveIfError( ws.WindowGroupList( 0, allWgIds) );

    const TInt chainCount = allWgIds->Count();
    
    RApaLsSession appArcSession;
    User::LeaveIfError( appArcSession.Connect() );

    appArcSession.GetAllApps();

    CApaWindowGroupName* windowName;
    TInt firstAppWgId = KErrNone;
    for ( TInt index=0; index < chainCount; index++ )
        {
        RWsSession::TWindowGroupChainInfo& info = (*allWgIds)[index];
        if ( info.iParentId <= 0 )
            {
            TInt wgId=info.iId;
            windowName = CApaWindowGroupName::NewLC(ws, wgId);
            TUid applicationUid = windowName->AppUid();                

            // application screen (0 = main screen, 1 = cover ui )          
            // the possible error value is omitted 
            TInt appScreen = -1; 
            TInt errId = appArcSession.GetDefaultScreenNumber( appScreen, applicationUid ); 
            if (  errId != KErrNone )
                {
                CleanupStack::PopAndDestroy( windowName );  //windowName
                continue;   
                }
            if ( firstAppWgId == KErrNone && ( appScreen == 0 || appScreen == -1 ) )
                {
                firstAppWgId = wgId; //   firstAppWgId should be the top windows group id.
                }

            CleanupStack::PopAndDestroy();  //windowName
            }
        }
    CleanupStack::PopAndDestroy( 2 ); // allWgIds, *allWgIds
    
    __VTPRINTEXIT( "VtUi.GetFocusWindowGroupId" )
    return firstAppWgId;
    }


// -----------------------------------------------------------------------------
// CVtUiAppUi::PreHandleKeyEventL
//
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::PreHandleKeyEventL( const TWsEvent& aEvent )
    {
    __VTPRINTENTER( "VtUi.PreHandleKeyEventL" )
    TBool consumed( EFalse );
    switch( aEvent.Type() )
        {

    case EEventKey:
        {
        // when both these are set, then it's our simulated key press
        const TInt
            modifiers( EModifierKeypad | EModifierSpecial );

        const TKeyEvent* ptrKeyEventC =
            aEvent.Key();

        const TBool isHwZoomKey(
            ptrKeyEventC->iCode == EKeyZoomIn ||
            ptrKeyEventC->iCode == EKeyZoomOut );

        if ( isHwZoomKey &&
             ( ptrKeyEventC->iModifiers & modifiers ) != modifiers )
            {
            __VTPRINT3( DEBUG_GEN, "VtUi.PreHandleKeyEventL keyc=%d scanc=%d",
                ptrKeyEventC->iCode, ptrKeyEventC->iScanCode )
            consumed = ETrue;

            // Send EEventKeyDown only when iRepeats is 0
            if ( !ptrKeyEventC->iRepeats )
                {
                TKeyEvent keyDownEvent( *ptrKeyEventC );
                keyDownEvent.iRepeats = 0;
                iCoeEnv->SimulateKeyEventL( keyDownEvent, EEventKeyDown );
                }

            // Send EEventKey always
            TKeyEvent keyEvent( *ptrKeyEventC );
            keyEvent.iModifiers |= modifiers;
            iCoeEnv->SimulateKeyEventL( keyEvent, EEventKey );

            // Que EEventKeyUp
            TKeyEvent keyUpEvent( *ptrKeyEventC );
            keyUpEvent.iRepeats = 0;
            StoreKeyEventL( keyUpEvent );
            }
        else if ( ( ptrKeyEventC->iModifiers & modifiers ) == modifiers )
            {
            __VTPRINT( DEBUG_GEN,
                "VtUi.PreHandleKeyEventL own event spotted, removing mods" )
            // event is generated by us, remove modifiers
            TKeyEvent* ptrKeyEvent = const_cast< TKeyEvent* >( ptrKeyEventC );
            ptrKeyEvent->iModifiers &= ~modifiers;
            }
        }
        break;

    case EEventKeyUp:
        if ( iIsStoredKeyEvent )
            {
            if ( iStoredKeyEvent.iScanCode == aEvent.Key()->iScanCode )
                {
                consumed = ETrue;
                SimulateStoredKeyEventL( EEventKeyUp );
                }
            }
        break;

    default:
        break;

        }

    __VTPRINTEXITR( "VtUi.PreHandleKeyEventL %d", consumed )
    return consumed;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SimulateStoredKeyEventL
//
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SimulateStoredKeyEventL( const TEventCode aEventCode )
    {
    __VTPRINTENTER( "VtUi.SimulateStoredKeyEventL" )
    if ( iIsStoredKeyEvent )
        {
        // Reset flag first because SimulateKeyEventL() is synchronous
        iIsStoredKeyEvent = EFalse;
        iCoeEnv->SimulateKeyEventL( iStoredKeyEvent, aEventCode );
        }
    __VTPRINTEXITR( "VtUi.SimulateStoredKeyEventL %d", iIsStoredKeyEvent )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::StoreKeyEventL
//
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::StoreKeyEventL( const TKeyEvent& aKeyEvent )
    {
    __VTPRINTENTER( "VtUi.StoreKeyEventL" )
    if ( iIsStoredKeyEvent && ( iStoredKeyEvent.iCode != aKeyEvent.iCode ) )
        {
        SimulateStoredKeyEventL( EEventKeyUp );
        }

    if ( !iIsStoredKeyEvent )
        {
        iIsStoredKeyEvent = ETrue;
        iStoredKeyEvent = aKeyEvent;
        }
    __VTPRINTEXITR( "VtUi.StoreKeyEventL %d", iIsStoredKeyEvent )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoTryToStartTb
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::DoTryToStartTbL( TAny* aAny )
    {
    CVtUiAppUi* self = static_cast< CVtUiAppUi* >( aAny );
    self->TryToStartTbL();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::UpdateVBSettingL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::UpdateVBSettingL()
    {
    // If white balance or color tone setting
    // feauture exists update setting
    CVtUiWhiteBalance* wb = static_cast< CVtUiWhiteBalance* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdWhiteBalance ) );

    CVtUiColorTone* ct = static_cast< CVtUiColorTone* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdColourTone ) );

    // If brightness or contrast slider
    // feauture exists update them
    CVtUiBrightness* br = static_cast< CVtUiBrightness* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdBrightness ) );
    
    CVtUiContrast* contr = static_cast< CVtUiContrast* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdContrast ) );
    

    
    if ( wb && iUiStates->IsWhiteBalanceSettingAvailable() )
        {
        __VTPRINT( DEBUG_GEN,"VtUi.UpdateVBSettingL WB update" )
        wb->UpdateSettingL();
        }

    if ( ct && iUiStates->IsColorToneSettingAvailable() )
        {
        __VTPRINT( DEBUG_GEN,"VtUi.UpdateVBSettingL CT update" )
        ct->UpdateSettingL();
        }
    
    if ( br && iUiStates->IsBrightnessSettingAvailable() )
        {
        __VTPRINT( DEBUG_GEN,"VtUi.UpdateVBSettingL br update" )
        br->UpdateSlider();
        }
    
    if ( contr && iUiStates->IsContrastSettingAvailable() )
        {
        __VTPRINT( DEBUG_GEN,"VtUi.UpdateVBSettingL contract update" )
        contr->UpdateSlider();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::TryToStartTb
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::TryToStartTbL()
    {
    __VTPRINTENTER( "VtUi.TryToStartTbL" )
    CVtUiToolbarBase* tb = static_cast< CVtUiToolbarBase* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar ) );
    if ( tb )
        {
        // If menu, dialog or dialer is displayed do not start the toolbar,
        // but let the timer run another round
        CEikMenuBar* menuBar = iEikonEnv->AppUiFactory()->MenuBar();
        if ( !( menuBar && menuBar->IsDisplayed() ) &&
             !IsDisplayingDialog() &&
             !(
                iUiStates->IsDialerActivating() ||
                iUiStates->IsDialerOpen() ||
                iUiStates->IsWhiteBalanceModeOn() ||
                iUiStates->IsColorToneModeOn()  ||
                iUiStates->IsBrightnessModeOn()  ||
                iUiStates->IsContrastModeOn()  ||
                iUiStates->IsZoomModeOn() ||
                iUiStates->IsVolumeModeOn() ||
                iUiStates->IsCaptureModeOn() )
                )
            {
            if ( iTbPeriodic )
                {
                iTbPeriodic->Cancel();
                }
            tb->StartL();
            }
        }
    __VTPRINTEXIT( "VtUi.TryToStartTbL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetRenderingModeL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetRenderingModeL( const TRenderingMode aMode,
    MVtUiVideoWindow* aNewDownlink )
    {
    __VTPRINTENTER( "VtUi.SetRenderingModeL" )
    __VTPRINT2( DEBUG_GEN, "VtUi.SetRenderingModeL=%d", aMode );
    iRenderingMode = aMode;
    
    TInt pos = 
        iInstance->iRemoteVideoControl->DrawableWindow()->OrdinalPosition();
    if ( aMode == ERenderingModeDialer )
        {
        // Remote video control has the highest priority in dialer
        iInstance->iRemoteVideoControl->DrawableWindow()->SetOrdinalPosition( 
                pos, KVtUiRemoteVideoControlOrdinalPriHigh );
        }
    else 
        {
        // Set remote video control priority back to normal
        iInstance->iRemoteVideoControl->DrawableWindow()->SetOrdinalPosition( 
                pos, KVtUiRemoteVideoControlOrdinalPriNormal );
        }
    
    if ( aNewDownlink )
        {
        if ( iDownlinkWindow != aNewDownlink )
            {
            iStoredDownlinkWindow = iDownlinkWindow;
            iDownlinkWindow = aNewDownlink;
            iStoredDownlinkWindow->SetRemoteVideoControl(NULL);
            iDownlinkWindow->SetRemoteVideoControl(iInstance->iRemoteVideoControl);
            iDownlinkWindow->LayoutRemoteVideo();
            }
        }
    RefreshBlind();
    UpdateRenderingParametersL();
    __VTPRINTEXIT( "VtUi.SetRenderingModeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::UpdateRenderingParametersL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::UpdateRenderingParametersL()
    {
    __VTPRINTENTER( "VtUi.UpdateRenderingParametersL" )
 
    MVtEngMedia& media = Model().Media();
    const TBool viewFinderStarted =
        media.RenderingStarted( MVtEngMedia::EMediaOutgoing );
    const TBool remoteRenderStarted =
        media.RenderingStarted( MVtEngMedia::EMediaIncoming );

    // Clear bitmaps
    iInstance->iContextControl->SetStreamBitmap( NULL );
    iInstance->iMainControl->SetStreamBitmap( NULL );

    // Stop viewfinder & remote render.
    if( viewFinderStarted )
        {
        ExecuteCmdL( KVtEngStopViewFinder );
        }
    ExecuteCmdL( KVtEngStopRenderRemote );

    // Re-layout the remote video
    iDownlinkWindow->LayoutRemoteVideo();
    
    const TBool uplinkWindowEqualsContextControl =
        ( iUplinkWindow == iInstance->iContextControl );

    // Prepare viewfinder.
    TVtEngRenderingOptions configViewfinder(
         uplinkWindowEqualsContextControl ?
            DetermineContextControlOptions() :
            DetermineMainControlOptions( EFalse ) );
    ExecuteCmdL( KVtEngPrepareViewFinder, configViewfinder );

    // Prepare remote render.
    TRAPD ( err, {
    TVtEngRenderingOptionsNGA configRemoteRenderNGA(
            DetermineRemoteVideoControlOptionsNGA() );
    ExecuteCmdL(
            KVtEngPrepareRemoteRenderNGA,
                configRemoteRenderNGA );
    } );
    if ( err != KErrNone )
        {
        if ( viewFinderStarted )
            {
            // Start viewfinder.
            ExecuteCmdL( KVtEngStartViewFinder );
            }
        User::Leave ( err );
        }
        
    // Start remote render.
    TRAP_IGNORE( ExecuteCmdL( KVtEngStartRenderRemote ) );

    if ( viewFinderStarted )
        {
        // Start viewfinder.
        ExecuteCmdL( KVtEngStartViewFinder );
        }

    // Redraw remote video last frame to make sure that in layout change
    // situation we still have something on screen.
    iDownlinkWindow->Redraw();
    __VTPRINTEXIT( "VtUi.UpdateRenderingParametersL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::MediaStateChangedL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::MediaStateChangedL()
    {
    CEikMenuBar* menuBar = iEikonEnv->AppUiFactory()->MenuBar();
    // close menu if it is shown
    if ( menuBar && menuBar->IsDisplayed() )
        {
        TKeyEvent keyEvent;
        keyEvent.iCode =  EKeyEscape;
        menuBar->OfferKeyEventL( keyEvent, EEventKey );
        }
    // Refresh toolbar
    CVtUiToolbarBase* tb = static_cast< CVtUiToolbarBase* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar ) );
    if ( tb )
        {
        tb->RefreshL();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ProcessCommandL
// Processes commands.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ProcessCommandL(
        TInt aCommand )
    {
    __VTPRINTENTER( "VtUi.ProcessCommandL" )
    
    // delay mute cmd received during layout change
    if ( aCommand == EAknSoftkeyOptions )
        {
        if ( iLayoutChg )
            {
            iDelayedCmd = EAknSoftkeyOptions;
            __VTPRINTEXIT( "VtUi.ProcessCommandL mute delayed due to LayoutChange" )
            return;
            }
        }
    
    MVtEngCommandHandler& command = Model().CommandHandler();
    command.ExecuteL( KVtEngRequestLastRemoteFrame, NULL );
    
    // only with fixed toolbar
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( iUiStates->IsFixedToolbarVisible())
            {
            // When option menu is opened fixed toolbar should
            // be set hidden
            iUiStates->SetIsFixedToolbarVisible( EFalse );
            // Stop toolbar
            MVtUiFeature* tb =
            iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar );
            if ( tb )
                {
                // timer could be active
                if ( iTbPeriodic )
                    {
                    iTbPeriodic->Cancel();
                    }
                tb->Stop();
                }
            if ( !iTbPeriodic )
                {
                iTbPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
                }
            // Toolbar doesn't come visible until options menu is closed.
            iTbPeriodic->Start( KStartTime, KPeriodTime, TCallBack( DoTryToStartTbL, this ) );
            }
        }
    else
        {
        StopSliders(); 
        }

    iInstance->iMainControl->SetSize( iInstance->iMainControl->Size() );
    iInstance->iMainControl->DrawNow();
        
    // Handle OK options menu.
    const TInt menuResource =
        iUiStates->IsLaunchOkOptionsMenu() ?
            R_VIDEOTELUI_OK_MENUBAR :
            R_VIDEOTELUI_MENUBAR;

    iUiStates->SetLaunchOkOptionsMenu( EFalse );

    CEikMenuBar* menu = iEikonEnv->AppUiFactory()->MenuBar();
    if ( menu )
        {
        menu->SetMenuTitleResourceId( menuResource );
        //Here we again set back the type of menu to "Options" when pressed LSK
        menu->SetMenuType( CEikMenuBar::EMenuOptions );
        }
    CAknAppUi::ProcessCommandL( aCommand );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::IsActiveCommand
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::IsActiveCommand( TInt aCommand ) const
    {
    return ( iActiveCommands.FindInOrder( aCommand ) != KErrNotFound );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::State
// -----------------------------------------------------------------------------
//
TVtUiAppStateBase& CVtUiAppUi::State()
    {
    return *iState;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::BitmapManager
// -----------------------------------------------------------------------------
//
CVtUiBitmapManager& CVtUiAppUi::BitmapManager()
    {
    return *iInstance->iBitmapManager;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::TActiveCommand::TActiveCommand
// -----------------------------------------------------------------------------
//
CVtUiAppUi::TActiveCommand::TActiveCommand(  RArray< TInt >& aActiveCommands,
    TInt aCommandId )
    : iActiveCommands( aActiveCommands ), iCommandId( aCommandId )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::TActiveCommand::~TActiveCommand
// -----------------------------------------------------------------------------
//
CVtUiAppUi::TActiveCommand::~TActiveCommand()
    {
    Close();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::TActiveCommand::OpenL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::TActiveCommand::OpenL()
    {
    iActiveCommands.InsertInOrderL( iCommandId );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::TActiveCommand::Close
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::TActiveCommand::Close()
    {
    TInt index( iActiveCommands.FindInOrder( iCommandId ) );
    if ( index != KErrNotFound )
        {
        iActiveCommands.Remove( index );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleCommandL
// Handles commands.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleCommandL(
        TInt aCommand )
    {
    __VTPRINTENTER( "VtUi.HandleCommand" )

    // Check if same command is already being performed.
    if ( IsActiveCommand( aCommand ) || ( iState &&
         iState->HandleCommandL( aCommand ) ==
         TVtUiAppStateBase::EEventHandled ) )
        {
        __VTPRINTEXIT( "VtUi.HandleCommand <silently ignoring> 0" )
        return;
        }

    // Check if command is allowed to be performed.
    if ( !IsCommandAllowedL( aCommand ) )
        {
        ShowNotAllowedNoteL();
        __VTPRINTEXITR( "VtUi.HandleCommand %d", KErrAccessDenied )
        return;
        }

    // delay mute cmd received during layout change (EGWG-7QQ3GZ)
    if ( (aCommand == EVtUiCmdDisableAudio) || (aCommand == EVtUiCmdUsePrimaryCamera)
            ||(aCommand == EVtUiCmdUseSecondaryCamera)
            ||(aCommand == EVtUiCmdDisableVideo) )
        {
        if ( iLayoutChg )
            {
            iDelayedCmd = aCommand;
            __VTPRINTEXIT( "VtUi.HandleCommand mute delayed due to LayoutChange" )
            return;
            }
        }
    
    TActiveCommand activeCommand( iActiveCommands, aCommand );
    // Close() will be called by the destructor, when instance goes out of
    // scope
    activeCommand.OpenL();

    TBool refresh = EFalse;
    CleanupPushRefreshL();

    // Execute command
    switch ( aCommand )
        {
        case EAknCmdHelp:
            CmdHelpL();
            break;

        case EVtUiCmdOkOptions:
            iUiStates->SetLaunchOkOptionsMenu( ETrue );
            ProcessCommandL( EAknSoftkeyOptions );
            break;

        case EVtUiCmdEnableMain:
        case EVtUiCmdDisableMain:
            // Submenu is opened automatically.
            break;

        case EVtUiCmdEnableVideo:
            {
            MVtEngMedia::TShareObjectState shareObjectState;
            VtUiUtility::GetObjectSharingState( Model().Media(),
                                                shareObjectState );
            if( shareObjectState != MVtEngMedia::ESharingImage )
                {
                refresh = ETrue;
                EnableCommandActivatingAndCleanupPushL();
                CmdEnableVideoL();
                CleanupStack::PopAndDestroy();
                }
            else
                {
                CmdStopShareImageL( refresh );
                EnableCommandActivatingAndCleanupPushL();
                CmdEnableVideoL();
                CleanupStack::PopAndDestroy();
                }
            }
            break;

        case EVtUiCmdEnableAudio:
            refresh = ETrue;
            CmdEnableAudioL();
            break;

        case EVtUiCmdEnableBoth:
            EnableCommandActivatingAndCleanupPushL();
            CmdEnableAudioL();
            MVtEngMedia::TShareObjectState shareObjectState;
            VtUiUtility::GetObjectSharingState( Model().Media(),
                                                shareObjectState );
            if( shareObjectState != MVtEngMedia::ESharingImage )
                {
                refresh = ETrue;
                CmdEnableVideoL();
                }
            else
                {
                CmdStopShareImageL( refresh );
                CmdEnableVideoL();
                }
            // EnableCommandActivatingAndCleanupPushL
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdDisableVideo:
            refresh = ETrue;
            EnableCommandActivatingAndCleanupPushL();
            CmdDisableVideoL();
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdDisableAudio:
            refresh = ETrue;
            EnableCommandActivatingAndCleanupPushL();
            CmdDisableAudioL();
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdDisableBoth:
            HandleCommandL( EVtUiCmdDisableAudio );
            HandleCommandL( EVtUiCmdDisableVideo );
            break;

        case EVtUiCmdActivateBT:
            refresh = ETrue;
            EnableCommandActivatingAndCleanupPushL();
            CmdActivateBtL();
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdDeactivateBT:
            refresh = ETrue;
            EnableCommandActivatingAndCleanupPushL();
            CmdDeactivateBtL();
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdActivateLoudspeaker:
        case EVtUiCmdSwitchFromBTToIHF:
            refresh = ETrue;
            EnableCommandActivatingAndCleanupPushL();
            CmdActivateLoudspeakerL();
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdDeactivateLoudspeaker:
            refresh = ETrue;
            EnableCommandActivatingAndCleanupPushL();
            CmdDeactivateLoudspeakerL();
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdUsePrimaryCamera:
            refresh = ETrue;
            CmdUseCameraL( ETrue );
            break;

        case EVtUiCmdUseSecondaryCamera:
            refresh = ETrue;
            CmdUseCameraL( EFalse );
            break;

        case EVtUiCmdSwapImagesPlaces:
            refresh = ETrue;
            CleanupPushEnableBlindL();
            iUiStates->SetDisableBlindSetting( ETrue );
            CmdSwapImagesPlacesL();
                        
            MVtEngMedia& media = Model().Media();
            if ( VtUiUtility::GetFreezeState( media ) )
                {
                TBool isViewFinderInContextPane = IsViewFinderInContextPane();
                iUiStates->SetViewFindersInitialPlaceContextPane( isViewFinderInContextPane );
                }
                
            CleanupStack::PopAndDestroy(); // CleanupPushEnableBlindL
            break;

        case EVtUiCmdZoom:
            refresh = ETrue;
            // Toolbar uses this same command to set zoom on and off
            // therefore this works as a toggle button
            SetZoomModeL( !iUiStates->IsZoomModeOn() );

            break;

        case EAknSoftkeyBack:
            {
            refresh = ETrue;
            MVtUiFeature* numberEntry =
                iFeatureManager->GetFeatureById( EVtUiFeatureIdNumberEntry );
            if ( numberEntry )
                {
                numberEntry->Stop();
                }
            }
            break;

        case EVtUiCmdSnapshot:
            EnableCommandActivatingAndCleanupPushL();
            CmdSnapshotL();
            // EnableCommandActivatingAndCleanupPushL
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdCapture:
            CmdCaptureL();
            break;

        case EVtUiCmdCancelCapture:
            CmdCancelCaptureL();
            break;

        case EVtUiCmdGoToIdle:
            CmdGoToIdleL();
            break;

        // Dial emergency call
        case EVtUiCmdDialerEmergencyCall:
        __VTPRINT( DEBUG_GEN, "VtUiHandleCommand.CmdEmergencyCall" );
            CmdSimulateKeyEvent( EStdKeyYes );
            break;
        // Object sharing related

        case EVtUiCmdShareObjectImage:
            CmdInitializeShareImageL( refresh );
            break;

        case EVtUiCmdStopSharingObjectImage:
            EnableCommandActivatingAndCleanupPushL();
            CmdStopShareImageL( refresh );
            // EnableCommandActivatingAndCleanupPushL
            CleanupStack::PopAndDestroy();
            break;

        case EVtUiCmdAdjustVideoVideoQuality:
        case EVtUiCmdAdjustVideoWhiteBalance:
        case EVtUiCmdAdjustVideoBrightness:
        case EVtUiCmdAdjustVideoContrast:
        case EVtUiCmdAdjustVideoColourTone:
        __VTPRINT( DEBUG_GEN, "VtUiHandleCommand.CmdAdjustVideoL" );
            CmdAdjustVideoL( aCommand );
            break;

        case EAknSoftkeyExit:
        case EAknCmdExit:
        case EEikCmdExit:
            // handled by state
            break;

        default:
            iCommandManager->HandleCommandL( aCommand );
            break;
        }

    if ( refresh )
        {
        CleanupStack::PopAndDestroy(); // CleanupPushRefreshL
        }
    else
        {
        CleanupStack::Pop(); // CleanupPushRefreshL
        }
    __VTPRINTEXITR( "VtUi.HandleCommand %d", KErrNone )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DynInitMenuPaneL
// Initialises menu pane dynamically.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::DynInitMenuPaneL(
        TInt,
        CEikMenuPane* aMenuPane )
    {
    __VTPRINTENTER( "VtUi.DynInitMenuPaneL" )
    
    CVtUiMenus* menus = static_cast< CVtUiMenus* >(
        iFeatureManager->GetFeatureById( EVtUiFeatureIdMenu ) );
    if ( menus )
        {
        iUiStates->Update();
        menus->SetMenuPane( aMenuPane );
        menus->RefreshL();
        }
    __VTPRINTEXIT( "VtUi.DynInitMenuPaneL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleKeyEventL
// Handles key events.
// -----------------------------------------------------------------------------
//
TKeyResponse CVtUiAppUi::HandleKeyEventL(
        const TKeyEvent& aKeyEvent,
        TEventCode aType )
    {
    __VTPRINTENTER( "VtUi.HandleKeyEventL" )

    TKeyResponse resp( EKeyWasNotConsumed );

    if ( !iUiStates->IsNumberEntryOpen() ||
         ( iUiStates->IsNumberEntryOpen() && !ShowNumberEntry() ) )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.ToZoom" )

        const TBool isHwZoomKey( aKeyEvent.iCode == EKeyZoomIn ||
            aKeyEvent.iCode == EKeyZoomOut );

        // if outgoing video is frozen disable zoom
        MVtEngMedia& media = Model().Media();
        if ( VtUiUtility::GetFreezeState ( media ) )
            {
             if ( aKeyEvent.iScanCode == EStdKeyUpArrow ||
                 aKeyEvent.iScanCode == EStdKeyDownArrow ||
                 isHwZoomKey )
                {
                __VTPRINTEXITR( "VtUi.HandleKeyEventL %d", EKeyWasConsumed )
                return EKeyWasConsumed;
                }
            }

        // Handle volume up & down

        }

    // If key event it not yet consumed, offer it to component manager
    if ( resp == EKeyWasNotConsumed )
        {
        resp = iComponentManager->OfferKeyEventL( aKeyEvent, aType );
        }

    __VTPRINTEXITR( "VtUi.HandleKeyEventL %d", resp )
    return resp;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleResourceChangeL
// Handles change of a resource.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleResourceChangeL(
        TInt aType )
    {
    __VTPRINTENTER( "VtUi.HandleResourceChangeL" )
    const TBool layoutChange =
        aType == KEikDynamicLayoutVariantSwitch ||
        aType == KAknsMessageSkinChange;
    if ( iInstance && layoutChange )
        {
        iInstance->iBitmapManager->InvalidateBitmaps();
        }

    CAknAppUi::HandleResourceChangeL( aType );

    if ( iInstance )
        {
        if ( layoutChange )
            {
            CVtUiToolbarBase* tb = static_cast< CVtUiToolbarBase* >(
                iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar ) );
            if( tb )
                {
                tb->HandleLayoutChangeL();
                }
            // Relayout controls
            iBlankControl->SetRect( ClientRect() );
            iInstance->LayoutChanged();
            }
        if ( iInstance->iNaviPane )
            {
            iInstance->iNaviPane->HandleResourceChange( aType );
            }
        if ( layoutChange )
            {
            (void) HandleLayoutChanged();
            }
        }

    iComponentManager->HandleResourceChangeL( aType );

    __VTPRINTEXIT( "VtUi.HandleResourceChangeL");
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleForegroundEventL
// Handles foreground status change.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleForegroundEventL( TBool aForeground )
    {
    CAknAppUi::HandleForegroundEventL( aForeground );

    if ( !aForeground )
        {
        StopDtmfTone();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::GetEikonEnv
// -----------------------------------------------------------------------------
//
CEikonEnv* CVtUiAppUi::GetEikonEnv()
    {
    return iEikonEnv;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::GetCba
// -----------------------------------------------------------------------------
//
CEikButtonGroupContainer* CVtUiAppUi::GetCba()
    {
    return iCba;
    }

//
// -----------------------------------------------------------------------------
// CVtUiAppUi::SetZoomModeL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetZoomModeL( const TBool aEnableZoomMode,
    const TBool aIsPermanent )
    {
    __VTPRINTENTER( "VtUi.SetZoomModeL" )
    __VTPRINT2( DEBUG_GEN, "VtUi.SetZoomMo=%d", aEnableZoomMode  );
    // If capture mode is on zoom mode cannot be changed
    if ( iUiStates->IsCaptureModeOn() )
        {
        __VTPRINTEXIT( "VtUi.SetZoomModeL.CaptureOn" )
        return;
        }
    CVtUiZoom* zoom = static_cast< CVtUiZoom* >(
        iFeatureManager->GetFeatureById( EVtUiFeatureIdZoom ) );
    if ( zoom )
        {
        if ( aEnableZoomMode )
            {
            if( aIsPermanent )
                {
                zoom->SetPermanenVisibility( aEnableZoomMode );
                }
            zoom->StartL();
            }
        else
            {
            if( aIsPermanent )
                {
                zoom->SetPermanenVisibility( aEnableZoomMode );
                }
            zoom->Stop();
            }
        }
    iUiStates->SetZoomModeOn( aEnableZoomMode );
    CVtUiToolbarBase* tb = static_cast< CVtUiToolbarBase* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar ) );
      if ( tb )
        {
        tb->RefreshL();
        }

    __VTPRINTEXIT( "VtUi.SetZoomModeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HelpContextL
// Returns help context array.
// -----------------------------------------------------------------------------
//
CArrayFix<TCoeHelpContext>* CVtUiAppUi::HelpContextL() const
    {
    CArrayFix<TCoeHelpContext>* array =
        new ( ELeave ) CArrayFixFlat<TCoeHelpContext>( KVtUiHelpContextAmount );
    CleanupStack::PushL( array );

    array->AppendL(
        TCoeHelpContext(
            KVtUiTelephoneUid,
            KINCAL_HLP_VIDEO_CALL ) );

    CleanupStack::Pop( array );
    return array;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecExecuteL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::ActiveExecExecuteL(
        CVtUiActiveExec& /*aActiveExec*/,
        const TInt aState,
        TInt& aNextState,
        TRequestStatus& aRequest )
    {
    return ActiveExecInitExecuteL(
            aState,
            aNextState,
            aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecContinue
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::ActiveExecContinue(
        CVtUiActiveExec& /*aActiveExec*/,
        TInt& aState,
        const TInt aError )
    {
    return ActiveExecInitContinue( aState, aError );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecCancel
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecCancel(
        CVtUiActiveExec& /*aActiveExec*/,
        TInt aState )
    {
    ActiveExecInitCancel( aState );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecDone
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecDone(
        CVtUiActiveExec& /*aActiveExec*/,
        const TInt aInitialState )
    {    
    ActiveExecInitDone( aInitialState );
    }

// state object service handlers


// -----------------------------------------------------------------------------
// CVtUiAppUi::ShutdownL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShutdownL()
    {
    __VTPRINTENTER( "VtUi.ShutdownL" )
    
    CVtUiWhiteBalance* wb = static_cast< CVtUiWhiteBalance* >(
            iFeatureManager->GetFeatureById( EVtUiFeatureIdWhiteBalance ) );
    CVtUiColorTone* ct = static_cast< CVtUiColorTone* >(
            iFeatureManager->GetFeatureById( EVtUiFeatureIdColourTone ) );
    
    if ( wb && wb->State() == MVtUiFeature::EActive )
        {
        __VTPRINT( DEBUG_GEN, "CVtUiWhiteBalance::DoDeactivateL" );
        wb->DoDeactivateL ();
        }
    if ( ct && ct->State() == MVtUiFeature::EActive )
        {
        __VTPRINT( DEBUG_GEN, "CVtUiColorTone::DoDeactivateL" );
        ct->DoDeactivateL( );            
        }
    
    // close volume slider
    CVtUiVolume* volume = static_cast< CVtUiVolume* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdVolume ) );
    if ( volume )
         {
         volume->Stop();
         }
    // if capture mode is on stop the zoom
    if ( iUiStates->IsCaptureModeOn() )
        {
        CVtUiZoom* zoom = static_cast< CVtUiZoom* >(
        iFeatureManager->GetFeatureById( EVtUiFeatureIdZoom ) );
        if ( zoom )
            {
            zoom->Stop();
            }
        }

    iActiveExec->Start( EVtUiAppUiShutdown, *this );
    __VTPRINTEXIT( "VtUi.ShutdownL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::StartupPhase1L
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::StartupPhase1L()
    {
    __VTPRINTENTER( "VtUi.StartupPhase1L" )
    iActiveExec->Start( EVtUiAppUiStartup, *this );
    __VTPRINTEXIT( "VtUi.StartupPhase1L" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::StartupPhase2L
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::StartupPhase2L()
    {
    __VTPRINTENTER( "VtUi.StartupPhase2L" )
    iActiveExec->Start( EVtUiAppUiAnswered, *this );
    __VTPRINTEXIT( "VtUi.StartupPhase2L" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ChangeState
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ChangeState( TVtUiAppStateBase* aState )
    {
    __VTPRINTENTER( "VtUi.ChangeState" )
    iState = aState;
    __VTPRINTEXIT( "VtUi.ChangeState" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::IsCommandAllowedL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::IsCommandAllowedL( const TInt aCommand )
    {
    return iCommandManager->IsCommandAllowedL( aCommand );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshDisabledFlagsL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshDisabledFlagsL()
    {
    // Refresh iDisabledFlags according to the current state.
    TInt avail;
    MVtEngMedia& media = Model().Media();
    VtUiUtility::GetOutgoingMediaState( media, avail );
    avail = ~avail;

    iDisabledFlags = 0;
    if ( avail & MVtEngMedia::EMediaAudio )
        {
        iDisabledFlags |= EDisabledAudio;
        }
    if ( avail & MVtEngMedia::EMediaVideo )
        {
        iDisabledFlags |= EDisabledVideo;
        }

    // If there are not cameras, then video options should be disabled.
    if ( !VtUiUtility::HasCameras( media ) )
        {
        iDisabledFlags |= EVideoOptionsDisabled;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshCameraOptionAvailability
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshCameraOptionAvailability(
        TBool& aUsePrimaryCameraNotAllowed,
        TBool& aUseSecondaryCameraNotAllowed )
    {
    aUsePrimaryCameraNotAllowed = ETrue;
    aUseSecondaryCameraNotAllowed = ETrue;

    // Check sources caps and current camera to see which
    // items should be included to the menu.

    TInt sourcesCaps = 0;
    MVtEngMedia& media = Model().Media();
    (void) media.GetSourcesCaps( sourcesCaps );

    MVtEngMedia::TCameraId cameraId;
    const TBool hasCameraId =
        ( media.GetCurrentCameraId( cameraId ) == KErrNone );

    if ( hasCameraId )
        {
        // Camera is in use. Now selected camera is not included
        // to the menu.
        switch ( cameraId )
            {
            case MVtEngMedia::EPrimaryCamera:
                sourcesCaps &=
                    ~MVtEngMedia::ESourceCapsPrimaryCamera;
                break;

            case MVtEngMedia::ESecondaryCamera:
                sourcesCaps &=
                    ~MVtEngMedia::ESourceCapsSecondaryCamera;
                break;

            default:
                sourcesCaps = 0;
                break;
            }
        }
    else
        {
        // If camera is not in use, then the "enable video" option
        // will automatically use one of the existing cameras.
        // However, if there are two cameras, then we need
        // to include secondary to the menu.

        const TInt bothCameras =
            ( MVtEngMedia::ESourceCapsPrimaryCamera |
            MVtEngMedia::ESourceCapsSecondaryCamera );
        sourcesCaps &= ~bothCameras;
        if ( sourcesCaps == bothCameras )
            {
            sourcesCaps &=
                ~MVtEngMedia::ESourceCapsPrimaryCamera;
            }
        else
            {
            sourcesCaps = 0;
            }
        }

    sourcesCaps = ~sourcesCaps;
    aUsePrimaryCameraNotAllowed =
        ( sourcesCaps & MVtEngMedia::ESourceCapsPrimaryCamera );
    aUseSecondaryCameraNotAllowed =
        ( sourcesCaps & MVtEngMedia::ESourceCapsSecondaryCamera );
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::CmdCaptureL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdCaptureL()
    {
    //firstly need to know if underlying provider supports KVtEngFreeze
    MVtEngCommandHandler& command = Model().CommandHandler();
    const TInt caps = command.GetCommandCaps( KVtEngFreeze );
    if ( (caps & MVtEngCommandHandler::EAttribEnabled) == 0)
        {
        return;
        }
    // end capture mode, image captured
    iUiStates->SetCaptureModeOn( EFalse );
    // end zoom mode
    SetZoomModeL( EFalse, ETrue );
    // freeze outgoing video
    ExecuteCmdL( KVtEngFreeze );
    RefreshBlind();
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::CmdSnapshotL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdSnapshotL()
    {
    __VTPRINTENTER( "VtUi.CmdSnapshotL" )
    
    // zoom mode must be set on before capture mode is set on
    SetZoomModeL( ETrue, ETrue );
    
    // set capture mode on
    iUiStates->SetCaptureModeOn( ETrue );

    // if outgoing video is already frozen
    MVtEngMedia& media = Model().Media();
    const TBool isFrozen( VtUiUtility::GetFreezeState( media ) );
    if ( isFrozen )
        {
        ExecuteCmdL( KVtEngUnfreeze );
        }
    if ( !IsViewFinderInMainPane() )
        {
        SwitchViewFinderToMainPaneL( !isFrozen );
        }
    else if ( !isFrozen )
        {
        iUiStates->SetViewFindersInitialPlaceContextPane( EFalse );
        }
    
    RefreshStatesL();
    RefreshBlind();
    __VTPRINTEXIT( "VtUi.CmdSnapshotL" )
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::CmdCancelCaptureL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdCancelCaptureL()
    {
    __VTPRINTENTER( "VtUi.CmdCancelCaptureL" )
    // end capture mode, image capture canceled
    iUiStates->SetCaptureModeOn( EFalse );
    SetZoomModeL( EFalse, ETrue );
    RefreshStatesL();
    RestoreViewFinderL();
    RefreshBlind();
    __VTPRINTEXIT( "VtUi.CmdCancelCaptureL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdEnableVideoL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdEnableVideoL()
    {
    // if outgoing video is frozen
    MVtEngMedia& media = Model().Media();
    if ( VtUiUtility::GetFreezeState( media ) )
        {
        ExecuteCmdL( KVtEngUnfreeze );
        // swap images if needed
        RestoreViewFinderL();
        }
    else
        {
        ExecuteCmdL( KVtEngStopViewFinder );
        iUplinkWindow->SetStreamBitmap( NULL );
        MVtEngMedia::TMediaSource source = MVtEngMedia::EMediaCamera;
        ExecuteCmdL( KVtEngSetSource, source );
        MVtEngMedia::TCameraId id;
        if ( Model().Media().GetCurrentCameraId( id ) == KErrInUse )
            {
            ShowCameraInUseNoteL();
            }
        ExecuteCmdL( KVtEngStartViewFinder );
        }
    // update VB settings
    UpdateVBSettingL();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdEnableAudioL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdEnableAudioL()
    {
    ExecuteCmdL( KVtEngUnmuteOutgoingAudio );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdDisableVideoL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdDisableVideoL()
    {
        
        if( iUiStates->IsZoomModeOn() )
            {
            // if zoom feature is active, stop that
            MVtUiFeature* zm = iFeatureManager->GetFeatureById( EVtUiFeatureIdZoom );
            if ( zm )
                {
                if ( zm->State() ==  MVtUiFeature::EActive )
                    {
                    __VTPRINT( DEBUG_GEN, "VtUi.CmdDisableVideoL zm->STOP" )
                    zm->Stop();
                    }
                }
            }
        
    ExecuteCmdL( KVtEngStopViewFinder );

    iUplinkWindow->SetStreamBitmap( NULL );

    TInt err = KErrNotFound;
    if ( VtUiUtility::HasStillImage( Model().Media() ) )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.:CmdDisableVideoL.HasStill" )
        MVtEngMedia::TMediaSource source = MVtEngMedia::EMediaStillImage;
        TRAP( err, ExecuteCmdL( KVtEngSetSource, source ) );
        }
    if ( ( err != KErrNone ) )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.:CmdDisableVideoL.MediaNone" )
        MVtEngMedia::TMediaSource source = MVtEngMedia::EMediaNone;
        ExecuteCmdL( KVtEngSetSource, source );
        }

    ExecuteCmdL( KVtEngStartViewFinder );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdDisableAudioL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdDisableAudioL()
    {
    ExecuteCmdL( KVtEngMuteOutgoingAudio );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdActivateBtL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdActivateBtL()
    {
    TInt error = KErrNone;
    CVtUiActivateBtHfDialog* dialog =
        new ( ELeave ) CVtUiActivateBtHfDialog(
            NULL,
            &error,
            Model().CommandHandler(),
            *iEventObserver );
    dialog->ExecuteDialogLD();

    if ( error != KErrCancel )
        {
        switch ( error )
            {
            case KErrNone:
                break;

            case KErrNoMemory:
            case KErrNotSupported:
                // Clear failure - to be handled in active scheduler.
                User::Leave( error );
                break;

            default:
                // Failed - still show local information note in error situation.
                {
                HBufC* prompt =
                    StringLoader::LoadLC(
                        R_VIDEOTELUI_QTN_BT_DEVICE_NOT_AVAIL );
                CAknInformationNote* note =
                    new ( ELeave ) CAknInformationNote( ETrue );
                note->ExecuteLD( *prompt );
                CleanupStack::PopAndDestroy( prompt );
                }
                break;
            }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdDeactivateBtL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdDeactivateBtL()
    {
    // Command to Video tel engine
    MVtEngAudio::TVtEngRoutingSetting audioSetting =
        MVtEngAudio::EDeactivateBT;

    ExecuteCmdL( KVtEngSetAudioRouting, audioSetting );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdActivateLoudspeakerL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdActivateLoudspeakerL()
    {
    MVtEngAudio::TVtEngRoutingSetting audioSetting =
        MVtEngAudio::EActivateHandsfree;
    ExecuteCmdL( KVtEngSetAudioRouting, audioSetting );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdDeactivateLoudspeakerL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdDeactivateLoudspeakerL()
    {
    MVtEngAudio::TVtEngRoutingSetting audioSetting =
        MVtEngAudio::EDeactivateHansfree;
    ExecuteCmdL( KVtEngSetAudioRouting, audioSetting );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdSwapImagesPlacesL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdSwapImagesPlacesL()
    {
    __VTPRINTENTER( "VtUi.Swap" )

    MVtEngMedia& media = Model().Media();
    const TBool viewFinderStarted =
        media.RenderingStarted( MVtEngMedia::EMediaOutgoing );
    const TBool remoteRenderStarted =
        media.RenderingStarted( MVtEngMedia::EMediaIncoming );

    if ( viewFinderStarted )
        {
        // Stop viewfinder.
        __VTPRINT( DEBUG_GEN, "VtUi.Swap.VF.down" )
        ExecuteCmdL( KVtEngStopViewFinder );
        }
    // Stop remote render.
    __VTPRINT( DEBUG_GEN, "VtUi.Swap.RR.down" )
    ExecuteCmdL( KVtEngStopRenderRemote );

    // Clear windows.
    iUplinkWindow->Reset();
    iDownlinkWindow->Reset();

    const TBool uplinkWindowEqualsContextControl =
        ( iUplinkWindow == iInstance->iContextControl );

    // Prepare viewfinder.
    __VTPRINT( DEBUG_GEN, "VtUi.Swap.VF.upd" )
    TVtEngRenderingOptions configViewfinder(
         uplinkWindowEqualsContextControl ?
             DetermineMainControlOptions( EFalse ) :
             DetermineContextControlOptions() );
    ExecuteCmdL( KVtEngPrepareViewFinder, configViewfinder );

    // Swap windows.
    if ( ERenderingModeDialer == iRenderingMode )
        {
        MVtUiVideoWindow* tmpWindow = iUplinkWindow;
        iUplinkWindow = iStoredDownlinkWindow;
        iStoredDownlinkWindow = tmpWindow;        
        }
    else
        {
        MVtUiVideoWindow* tmpWindow = iUplinkWindow;
        iUplinkWindow = iDownlinkWindow;
        iDownlinkWindow = tmpWindow;        
        }
    iUplinkWindow->SetRemoteVideoControl(NULL);
    iDownlinkWindow->SetRemoteVideoControl(iInstance->iRemoteVideoControl);
    iDownlinkWindow->LayoutRemoteVideo();    

    // Prepare remote render.
    __VTPRINT( DEBUG_GEN, "VtUi.Swap.RR.upd" )
    TRAPD ( err, {
    TVtEngRenderingOptionsNGA configRemoteRenderNGA(
            DetermineRemoteVideoControlOptionsNGA() );
    ExecuteCmdL(
            KVtEngPrepareRemoteRenderNGA,
                configRemoteRenderNGA );
    } );
    
    if ( err != KErrNone )
        {
        if ( viewFinderStarted )
            {
            // Start viewfinder.
            ExecuteCmdL( KVtEngStartViewFinder );
            }
        User::Leave ( err );    
        }
    // Start remote render.
    __VTPRINT( DEBUG_GEN, "VtUi.Swap.RR.up" )
    if ( remoteRenderStarted )
        {
        ExecuteCmdL( KVtEngStartRenderRemote );
        }

    __VTPRINT( DEBUG_GEN, "VtUi.Swap.VF.up" )
    if ( viewFinderStarted )
        {
        // Start viewfinder.
        ExecuteCmdL( KVtEngStartViewFinder );
        }

    iDownlinkWindow->Redraw();

    // Refresh blind & waiting will be handled in HandleCommandL.
    __VTPRINTEXIT( "VtUi.Swap" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdUseCameraL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdUseCameraL( const TBool aPrimaryCamera )
    {
    EnableCommandActivatingAndCleanupPushL();
    MVtEngMedia& media = Model().Media();

    MVtEngMedia::TMediaSource selectedSource =
        ( aPrimaryCamera ) ?
            MVtEngMedia::EMediaCameraPri : MVtEngMedia::EMediaCameraSec;

    TInt available = 0;
    VtUiUtility::GetOutgoingMediaState( media, available );
    if ( available & MVtEngMedia::EMediaVideo )
        {
        ExecuteCmdL( KVtEngStopViewFinder );

        iUplinkWindow->SetStreamBitmap( NULL );
        TRAPD( err, ExecuteCmdL( KVtEngSetSource, selectedSource ) );

        if ( err == KErrNone )
            {
            ExecuteCmdL( KVtEngStartViewFinder );
            }
        else
            {
            ShowOtherCameraNotUsableNoteL();
            }
        }
    else
        {
        MVtEngMedia::TPrepareCameraParams params;
        params.iMediaSource = selectedSource;
        params.iInitialize = EFalse;
        TRAPD( err, ExecuteCmdL( KVtEngPrepareCamera, params ) );
        if ( err != KErrNone )
            {
            ShowOtherCameraNotUsableNoteL();
            }
        }
    CleanupStack::PopAndDestroy(); // EnableCommandActivatingAndCleanupPushL
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdHelpL
// Launches help application.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdHelpL()
    {
    HlpLauncher::LaunchHelpApplicationL(
        iEikonEnv->WsSession(),
        AppHelpContextL() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::PrepareExitL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::PrepareExitL()
    {
    __VTPRINTENTER( "VtUi.PrepareExitL" )
    // Cancel progress dialog
    HideProgressDialogL();
    // Cancel menu.
    CAknAppUi::ProcessCommandL( EEikCmdCanceled ); // does not leave

    if ( !iExitTimer->IsActive() )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.Exit.Timer.Go" )
        iExitTimer->Start(
            KVtUiExitTimeout,
            KVtUiExitTimeout,
            TCallBack( DoHandleExitTimeout, this ) );
        }

    // Asynchronous shutdown - execute command.
    iBlankControl->SetActive( ETrue );
    __VTPRINTEXIT( "VtUi.PrepareExitL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdUpdateZoomL
// This method is called to update zoom step to the Video Telephone engine
// side from the HandleKeyEventL method.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdUpdateZoomL()
    {
    __VTPRINTENTER( "VtUi.UpdZm" )

    __VTPRINTEXIT( "VtUi.UpdZm" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetZoomFactorL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetZoomFactorL( TInt aZoomStep )
    {
    __VTPRINTENTER( "VtUi.SetZoomFactorL" )
    MVtEngMedia& media = Model().Media();
    if ( VtUiUtility::IsZoomAllowed( media ) )
        {
        ExecuteCmdL( KVtEngSetZoomStep, aZoomStep );
        }
    __VTPRINTEXIT( "VtUi.SetZoomFactorL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdSimulateKeyEvent
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdSimulateKeyEvent( TInt aScanCode )
   {
   TRawEvent lEventDown;
   lEventDown.Set( TRawEvent::EKeyDown, aScanCode );
   UserSvr::AddEvent( lEventDown );
   User::After( 100000 );
   TRawEvent lEventUp;
   lEventUp.Set( TRawEvent::EKeyUp, aScanCode );
   UserSvr::AddEvent( lEventUp );
   }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdUpdateVolumeL
// This method is called to update volume to the Video Telephone engine
// side
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdUpdateVolumeL( MVtEngAudio::TVtEngOutputVolume aVolume )
    {
    __VTPRINTENTER( "VtUi.CmdUpdateVolumeL" )
    iVolCtrl->AdjustVolumeL( aVolume );
    __VTPRINTEXIT( "VtUi.CmdUpdateVolumeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdGoToIdleL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdGoToIdleL()
    {
    __VTPRINTENTER( "VtUi.CmdGoToIdleL" )
    TInt idleUid = 0;
    if ( RProperty::Get(
             KPSUidAiInformation,
             KActiveIdleUid,
             idleUid ) == KErrNone )
        {
        __VTPRINT2( DEBUG_GEN, "Idle UID: %d", idleUid )
        TApaTaskList taskList( iEikonEnv->WsSession() );
        TApaTask task = taskList.FindApp( TUid::Uid( idleUid ) );
        if ( task.Exists() )
            {
            __VTPRINT( DEBUG_GEN, "Idle task found")
            RProperty::Set( KPSUidUikon, KUikVideoCallTopApp, KVtUiAppUid.iUid );
            task.BringToForeground();
            }
        }
    __VTPRINTEXIT( "VtUi.CmdGoToIdleL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdInitializeShareImageL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdInitializeShareImageL( TBool& aNeedRefresh )
    {
    __VTPRINTENTER( "VtUi.CmdInitializeShareImageL" )
    EnableCommandActivatingAndCleanupPushL();

    MVtUiFeature* tb =
    iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar );
      if ( tb )
        {
        // timer could be active
        if ( iTbPeriodic )
            {
            iTbPeriodic->Cancel();
            }
        tb->Stop();
        }
    CDesCArray* selectedFiles = new ( ELeave ) CDesCArrayFlat( 1 );
    CleanupStack::PushL( selectedFiles );
    CVtUiAppUi::CVtUiAppUiMGVerifier* verifier =
        CVtUiAppUi::CVtUiAppUiMGVerifier::NewLC( *this, *iCoeEnv );

     // number erntry is not availabe while media gallery is open
    iInstance->iNumberEntryActivation->SetActive( EFalse );
    iUiStates->SetSelectingShare( ETrue );

    TBool result( EFalse );
    TRAPD( err, result =
        MGFetch::RunL( *selectedFiles, EImageFile, EFalse, verifier ) );

   // leave occured
   if ( err != KErrNone )
       {
       if ( iUiStates->ExecState() == TVtUiStates::EExecStateRunning )
           {
           ShowUnableToOpenNoteL();
           }
       else
           {
           __VTPRINTEXIT( "VtUi.CmdInitializeShareImageL 1" )
           Exit();
           }
       }

    if ( result && ( selectedFiles->Count() > 0 ) )
        {
        MVtEngMedia::TShareObjectState shareObjectState;
        VtUiUtility::GetObjectSharingState( Model().Media(), shareObjectState );
        iUiStates->SetViewFinderToMainPane(
            shareObjectState == MVtEngMedia::ENotSharing );
        MVtEngMedia::TShareObjectImageParameters
            parameters( selectedFiles->operator[]( 0 ) );
        ExecuteCmdL( KVtEngInitializeShareImage, parameters );
        aNeedRefresh = ETrue;
        }
    else  // selection canceled start toolbar timer
        {
        if ( !iTbPeriodic )
            {
            iTbPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
            }
        iTbPeriodic->Cancel();
        iTbPeriodic->Start( KStartTime, KPeriodTime, TCallBack( DoTryToStartTbL, this ) );
        }
    CleanupStack::PopAndDestroy( 2 ); // selectedFiles, verifier
    // number entry is availabe again
    iInstance->iNumberEntryActivation->SetActive( ETrue );
    iUiStates->SetSelectingShare( EFalse );
    CleanupStack::PopAndDestroy(); // EnableCommandActivatingAndCleanupPushL();
    
    __VTPRINTEXIT( "VtUi.CmdInitializeShareImageL 0" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdShareImageL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdShareImageL()
    {
    ExecuteCmdL( KVtEngStartShareImage );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdStopShareImageL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CmdStopShareImageL( TBool& aNeedRefresh )
    {
    ExecuteCmdL( KVtEngStopShareImage );
    RestoreViewFinderL();
    aNeedRefresh = ETrue;
    // update VB settings
    UpdateVBSettingL();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleWaitingStateChange
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleWaitingStateChange( TBool aIsWaiting )
    {
    // Dialer must be closed in case of waiting call
    MVtUiFeature* dialer =
        iFeatureManager->GetFeatureById( EVtUiFeatureIdDialer );
    if ( dialer )
        {
        dialer->Stop();
        }
    iUiStates->SetWaitingCall( aIsWaiting );
    if (aIsWaiting == EFalse && 
        iIsWaitingCallState != EFalse && 
        !iUiStates->IsThisApplicationForeground() )
        {
        iIsWaitingCallState = EFalse;
        ChangeApplicationFocus( ETrue );
        TRAP_IGNORE ( SetHiddenL( EFalse ) );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitExecuteL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::ActiveExecInitExecuteL(
        const TInt aState,
        TInt& aNextState,
        TRequestStatus& aRequest )
    {
    __VTPRINTENTER( "VtUi.InitExec" )
    __VTPRINT2( DEBUG_GEN, "VtUi.InitExec.st=%d", aState )

    TBool synch = EFalse;

    switch ( aState )
        {
        // Startup chain:
        case EVtUiAppUiStartupCloseDialogs:
            // Close all dialogs.
            iBlankControl->SetActive( EFalse );
            AknDialogShutter::ShutDialogsL( *iEikonEnv );
            iBlankControl->SetActive( ETrue );

            synch = ETrue;
            aNextState = EVtUiAppUiStartupInitEngine;
            break;

        case EVtUiAppUiStartupInitEngine:
            iUplinkWindow = iInstance->iContextControl;
            iDownlinkWindow = iInstance->iMainControl;
            ActiveExecInitExecuteCommandL( KVtEngInitializeEngine, aRequest );
            aNextState = EVtUiAppUiStartupPrepareViewfinder;
            break;

        case EVtUiAppUiStartupPrepareViewfinder:
            ActiveExecInitPrepareViewFinderL( aRequest );
            iUplinkWindow->SetStreamBitmap( NULL );
            aNextState = EVtUiAppUiStartupPrepareRemoteRender;
            break;

        case EVtUiAppUiStartupPrepareRemoteRender:
        
            iInstance->CreateRemoteVideoControl();
            ActiveExecInitPrepareRemoteRenderL( aRequest );
            iDownlinkWindow->SetStreamBitmap( NULL );
            aNextState = EVtUiAppUiStartupRemoveBlank;
            break;

        case EVtUiAppUiStartupRemoveBlank:
             // Finally remove blank control.
            iBlankControl->SetActive( EFalse );
            aNextState = EVtUiAppUiNone;
            synch = ETrue;
            break;

        // Shutdown chain:
        case EVtUiAppUiShutdownCloseDialogs:
            {
            // Close all dialogs.
            iBlankControl->SetActive( EFalse );
            AknDialogShutter::ShutDialogsL( *iEikonEnv );
            iBlankControl->SetActive( ETrue );

            MVtUiFeature* numberEntry = iFeatureManager->GetFeatureById(
                EVtUiFeatureIdNumberEntry );
            // Number entry may be active if its deactivation timer is still
            // pending. Stop performs some cleanup which is needed before AppUi
            // cleanup.
            if ( numberEntry )
                {
                numberEntry->Stop();
                }

            synch = ETrue;
            aNextState = EVtUiAppUiShutdownHideApplication;
            }
            break;

        case EVtUiAppUiShutdownHideApplication:
            if ( iUiStates->IsThisApplicationForeground() )
                {
                BringTelephoneToForeground();
                }
            else
                {
                ChangeApplicationFocus( EFalse );
                }
            iDownlinkWindow->SetStreamBitmap( NULL );
            iUplinkWindow->SetStreamBitmap( NULL );
            SetHiddenL( ETrue );
            iEventObserver->DeleteRemConSession();

            synch = ETrue;
            aNextState = EVtUiAppUiShutdownResetEngine;
            break;

        case EVtUiAppUiShutdownResetEngine:
            {
            aRequest = KRequestPending;

            MVtEngCommandHandler& command = Model().CommandHandler();
            // There should not be any commands ongoing because
            // we have canceled all dialogs (and this should
            // be the only command without dialog).
            command.CancelCommand( command.PendingCommand() ); // ignore error
            command.ExecuteL( KVtEngResetEngine, NULL );
            iShutdownRequest = &aRequest;

            aNextState = EVtUiAppUiShutdownRemoveBlank;
            }
            break;

        case EVtUiAppUiShutdownRemoveBlank:
            // Finally remove blank control.
            iBlankControl->SetActive( EFalse );

            synch = ETrue;
            aNextState = EVtUiAppUiNone;
            break;

        // Answered chain:
        case EVtUiAppUiAnsweredStart:
            {
            CVtUiBlankDialog* dialog =
                new ( ELeave ) CVtUiBlankDialog( &iExecBlankDialog );
            dialog->ExecuteDialogNoWaitLD();
            iExecBlankDialog = dialog;

            synch = ETrue;
            if ( iUiStates->IsLayoutChangeNeeded() )
                {
                (void) HandleLayoutChanged();
                }
            aNextState = EVtUiAppUiAnsweredRefreshNavi;
            }
            break;

        case EVtUiAppUiAnsweredRefreshNavi:
            RefreshNaviPaneL();
            iEventObserver->CreateRemConSessionL();

            synch = ETrue;
            aNextState = EVtUiAppUiAnsweredRefreshSoftkeys;
            break;

        case EVtUiAppUiAnsweredRefreshSoftkeys:
            RefreshSoftkeysL();

            synch = ETrue;
            aNextState = EVtUiAppUiAnsweredStartRemoteRender;
            break;

        case EVtUiAppUiAnsweredStartRemoteRender:
            {
            // Set waiting text to main control and start remote rendering.
            // Video Telephone application should get KVtEngRemoteVideoStarted
            // event when the first frame is received.
            iDownlinkWindow->SetWaiting( ETrue );
            iUiStates->SetWaitingForFirstFrame( ETrue );
            //Must check if orientation changed between prepare remote render and start remote render
            //If changed, update render parameter firstly
            if ( iIsLandScapeOrientation != VtUiLayout::IsLandscapeOrientation() )
                {
                 __VTPRINT( DEBUG_GEN, "layout has been changed before start RemoteRender" )
                 UpdateRenderingParametersL();
                }

            ActiveExecInitExecuteCommandL( KVtEngStartRenderRemote,
                aRequest );

            aNextState = EVtUiAppUiAnsweredCheckCamera;            
            }
            break;

        case EVtUiAppUiAnsweredCheckCamera:
            {
            MVtEngMedia& media = Model().Media();
            if ( VtUiUtility::HasCameras( media ) )
                {
                aNextState = EVtUiAppUiAnsweredChoose;
                synch = ETrue;
                }
            else
                {
                if ( VtUiUtility::HasStillImage( media ) )
                    {
                    aNextState = EVtUiAppUiAnsweredSelectStill;
                    }
                else
                    {
                    aNextState = EVtUiAppUiAnsweredSelectNone;
                    }

                synch = ETrue;
                }
            }
            break;

        case EVtUiAppUiAnsweredChoose:
            {
            // If camera is in use, then show note,
            // select still image, stop.
            //
            // If call is mobile terminated, then show query.
            //      If user answers 'yes' to the query,
            //      then activate camera.
            //      If user answers 'no' to the query,
            //      then choose still image.
            //
            // If call is mobile originated, then select camera.
            //
            // If selecting a camera fails, then select still image.
            // If selecting still image fails, then select none.
            //
            CVtEngModel& model = Model();
            MVtEngSessionInfo& session = model.Session();
            MVtEngMedia& media = model.Media();

            MVtEngMedia::TCameraId id;
            TInt cameraErr = model.Media().GetCurrentCameraId( id );
            if ( cameraErr == KErrInUse )
                {
                // Camera is in use.
                iUiStates->SetExecShowCameraInUse( ETrue );

                if ( VtUiUtility::HasStillImage( media ) )
                    {
                    aNextState = EVtUiAppUiAnsweredSelectStill;
                    }
                else
                    {
                    aNextState = EVtUiAppUiAnsweredSelectNone;
                    }
                }
            else
                {
                // Check the direction of the call.
                iUiStates->SetExecShowCameraInUse( EFalse );
                MVtEngSessionInfo::TDirection direction;
                if ( session.GetDirection( direction ) != KErrNone )
                    {
                    direction = MVtEngSessionInfo::EDirectionMT;
                    }

                if ( direction == MVtEngSessionInfo::EDirectionMT )
                    {
                    // Start steps towards the "Allow video" query.
                    if ( VtUiUtility::HasStillImage( media ) )
                        {
                        aNextState = EVtUiAppUiAnsweredQuerySetupStill;
                        }
                    else
                        {
                        aNextState = EVtUiAppUiAnsweredQuerySetupNone;
                        }
                    }
                else
                    {                    
                    aNextState = EVtUiAppUiAnsweredDoPrepareCamera;
                    }
                }
            synch = ETrue;
            }
            break;

        case EVtUiAppUiAnsweredQuerySetupStill:
            ActiveExecInitSetSourceL( MVtEngMedia::EMediaStillImage, aRequest );
            aNextState = EVtUiAppUiAnsweredQuerySetupStart;
            break;

        case EVtUiAppUiAnsweredQuerySetupNone:
            ActiveExecInitSetSourceL( MVtEngMedia::EMediaNone, aRequest );
            aNextState = EVtUiAppUiAnsweredQuerySetupStart;
            break;

        case EVtUiAppUiAnsweredQuerySetupStart:
            ActiveExecInitExecuteCommandL( KVtEngStartViewFinder, aRequest );
            aNextState = EVtUiAppUiAnsweredQueryShow;
            break;

        case EVtUiAppUiAnsweredQueryShow:
            {
            RefreshL();
            TInt state = EPSCTsyCallStateUninitialized;
            TInt err = RProperty::Get(
                KPSUidCtsyCallInformation,
                KCTsyCallState,
                state );
            __VTPRINT3( DEBUG_GEN, "VtUi.InitExec WaitingCall State=%d, err=%d",
            state, err )
            if ( EPSCTsyCallStateRinging != state )
                {
                ChangeApplicationFocus( ETrue );
                SetHiddenL( EFalse );
                }
            else
                {
                iIsWaitingCallState = ETrue;
                }

            // User selectable call answer mute.
            // In GS one can set call ansewer status
            // eighter to query user, allways show, allways mute.
            // GS values are checked from CR key ( KSettingsVTVideoSending )
            // (default value is 0 = allways query).
            TVtUiGsMuteVariation camute;
            __VTPRINT2( DEBUG_GEN, "VtUi.InitExe GS CR key KSettingsVTVideoSending querystate=%d", camute.GsMuteState() )
            if ( camute.GsMuteState() == KAllwaysQuery && !iUiStates->IsDeviceLockOn() && EPSCTsyCallStateRinging != state)
                {
                CVtUiAllowVideoDialog* dialog =
                    new ( ELeave ) CVtUiAllowVideoDialog(
                        &iExecDialog,
                        CAknQueryDialog::ENoTone );
                dialog->ExecuteDialogLD( aRequest );
                iExecDialog = dialog;
                aNextState = EVtUiAppUiAnsweredQueryDecide;
                }
            else if ( camute.GsMuteState() == KAllwaysAllow )
                {
                aNextState = EVtUiAppUiAnsweredDoPrepareCamera;
                synch = ETrue;
                }
            else
                {
                aNextState = EVtUiAppUiNone;
                synch = ETrue;
                }

            }
            break;

        case EVtUiAppUiAnsweredQueryDecide:
            {
            delete iExecDialog;
            iExecDialog = NULL;

            if ( iActiveExec->RequestStatus() ==
                 CVtUiAllowVideoDialog::EUserAllowed )
                {
                aNextState = EVtUiAppUiAnsweredDoPrepareCamera;
                }
            else
                {
                aNextState = EVtUiAppUiNone;
                }

            synch = ETrue;
            }
            break;

        case EVtUiAppUiAnsweredDoPrepareCamera:
            {
            MVtEngMedia& media = Model().Media();
            MVtEngMedia::TMediaSource source = MVtEngMedia::EMediaCamera;
            ActiveExecInitPrepareCameraL( source, aRequest );
            aNextState = EVtUiAppUiAnsweredSelectCamera;
            }
            break;

        case EVtUiAppUiAnsweredQuerySelectCamera:
        case EVtUiAppUiAnsweredSelectCamera:
            ActiveExecInitSetSourceL( MVtEngMedia::EMediaCamera, aRequest );
            if ( aState == EVtUiAppUiAnsweredSelectCamera )
                {
                aNextState = EVtUiAppUiAnsweredStartViewfinder;
                }
            else
                {
                aNextState = EVtUiAppUiAnsweredQueryStartViewfinder;
                }
            break;

        case EVtUiAppUiAnsweredQuerySelectStill:
        case EVtUiAppUiAnsweredSelectStill:
            ActiveExecInitSetSourceL( MVtEngMedia::EMediaStillImage, aRequest );

            if ( aState == EVtUiAppUiAnsweredSelectStill )
                {
                aNextState = EVtUiAppUiAnsweredStartViewfinder;
                }
            else
                {
                aNextState = EVtUiAppUiAnsweredQueryStartViewfinder;
                }
            break;

        case EVtUiAppUiAnsweredQuerySelectNone:
        case EVtUiAppUiAnsweredSelectNone:
            ActiveExecInitSetSourceL( MVtEngMedia::EMediaNone, aRequest );

            if ( aState == EVtUiAppUiAnsweredSelectNone )
                {
                aNextState = EVtUiAppUiAnsweredStartViewfinder;
                }
            else
                {
                aNextState = EVtUiAppUiAnsweredQueryStartViewfinder;
                }
            break;

        case EVtUiAppUiAnsweredQueryStartViewfinder:
        case EVtUiAppUiAnsweredStartViewfinder:
            ActiveExecInitExecuteCommandL( KVtEngStartViewFinder, aRequest );

            if ( aState == EVtUiAppUiAnsweredStartViewfinder )
                {
                aNextState = EVtUiAppUiAnsweredFinish;
                }
            else
                {
                aNextState = EVtUiAppUiAnsweredQueryFinish;
                }
            break;

        case EVtUiAppUiAnsweredQueryFinish:
        case EVtUiAppUiAnsweredFinish:
            RefreshL();
            if ( iUiStates->IsExecShowCameraInUse() )
                {
                ShowCameraInUseNoteL();
                }
            
            if ( aState != EVtUiAppUiAnsweredQueryFinish )
                {
                ChangeApplicationFocus( ETrue );
                }
            SetHiddenL( EFalse );

            synch = ETrue;
            aNextState = EVtUiAppUiNone;
            break;

        default:
            User::Leave( KErrNotSupported );
            break;
        }

    __VTPRINT2( DEBUG_GEN, "VtUi.InitExec.sync=%d", synch )
    __VTPRINT2( DEBUG_GEN, "VtUi.InitExec.next=%d", aNextState )
    __VTPRINTEXITR( "VtUi.InitExec %d", synch )
    return synch;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitContinue
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::ActiveExecInitContinue(
        TInt& aState,
        const TInt aError )
    {
    __VTPRINTENTER( "VtUi.InitExecCont" )
    __VTPRINT2( DEBUG_GEN, "VtUi.InitExecCont.st=%d", aState )
    //__VTPRINT2( DEBUG_GEN, "VtUi.InitExecCont.err=%d", aError )

    const TInt state = aState;
    switch ( state )
        {
        case EVtUiAppUiStartupCloseDialogs:
        case EVtUiAppUiStartupInitEngine:
        case EVtUiAppUiStartupPrepareViewfinder:
        case EVtUiAppUiStartupPrepareRemoteRender:
        case EVtUiAppUiStartupRemoveBlank:
            // Prepare failed.
            break;

        case EVtUiAppUiShutdownCloseDialogs:
            if( KErrNotReady == aError )
                {
                aState = EVtUiAppUiShutdownHideApplication;
                break;
                }
        case EVtUiAppUiShutdownResetEngine:            
        case EVtUiAppUiShutdownRemoveBlank:
            // shutdown failed
            break;            

        case EVtUiAppUiShutdownHideApplication:
            aState = EVtUiAppUiShutdownResetEngine;
            break;
            

        case EVtUiAppUiAnsweredStart:
            aState = EVtUiAppUiAnsweredRefreshNavi;
            break;

        case EVtUiAppUiAnsweredRefreshNavi:
            aState = EVtUiAppUiAnsweredRefreshSoftkeys;
            break;

        case EVtUiAppUiAnsweredRefreshSoftkeys:
            aState = EVtUiAppUiAnsweredStartRemoteRender;
            break;

        case EVtUiAppUiAnsweredStartRemoteRender:
        case EVtUiAppUiAnsweredStartViewfinder:
        case EVtUiAppUiAnsweredSelectNone:
        case EVtUiAppUiAnsweredFinish:
        case EVtUiAppUiAnsweredQueryStartViewfinder:
        case EVtUiAppUiAnsweredQuerySelectNone:
        case EVtUiAppUiAnsweredQueryFinish:
            // Answered failed.
            break;

        case EVtUiAppUiAnsweredCheckCamera:
            aState = EVtUiAppUiAnsweredChoose;
            break;

        case EVtUiAppUiAnsweredChoose:
            aState = EVtUiAppUiAnsweredQuerySetupStill;
            break;

        case EVtUiAppUiAnsweredQuerySetupStill:
            aState = EVtUiAppUiAnsweredQuerySetupNone;
            break;

        case EVtUiAppUiAnsweredQuerySetupStart:
        case EVtUiAppUiAnsweredQuerySetupNone:
            aState = EVtUiAppUiAnsweredQueryShow;
            break;

        case EVtUiAppUiAnsweredQueryShow:
        case EVtUiAppUiAnsweredQueryDecide:
        case EVtUiAppUiAnsweredSelectCamera:
            aState = EVtUiAppUiAnsweredSelectStill;
            break;

        case EVtUiAppUiAnsweredQuerySelectCamera:
            aState = EVtUiAppUiAnsweredQuerySelectStill;
            break;

        case EVtUiAppUiAnsweredQuerySelectStill:
            aState = EVtUiAppUiAnsweredQuerySelectNone;
            break;

        case EVtUiAppUiAnsweredSelectStill:
            aState = EVtUiAppUiAnsweredSelectNone;
            break;

        default:
            break;
        }

    const TBool cont = ( aState != state );
    __VTPRINT2( DEBUG_GEN, "VtUi.InitExecCont.cont=%d", cont )

    if ( !cont )
        {
        delete iExecBlankDialog;
        iExecBlankDialog = NULL;
        // Operation failed.
        if ( iState )
            {
            TRAP_IGNORE( iState->AppUiStartupFailedL() );
            }
        }
    __VTPRINTEXITR( "VtUi.InitExecCont %d", cont )
    return cont;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitCancel
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecInitCancel(
        const TInt /*aState*/ )
    {
    __VTPRINTENTER( "VtUi.InitExecCancel" )

    iBlankControl->SetActive( EFalse );
    delete iExecDialog;
    delete iExecBlankDialog;

    if ( iShutdownRequest )
        {
        User::RequestComplete( iShutdownRequest, KErrCancel );
        iShutdownRequest = NULL;
        }
    __VTPRINTEXIT( "VtUi.InitExecCancel" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitDone
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecInitDone(
        const TInt aInitialState )
    {
    __VTPRINTENTER( "VtUi.ExecInitDone" )
    __VTPRINT2( DEBUG_GEN, "VtUi.InitExecDone.ini=%d", aInitialState )
    delete iExecBlankDialog;
    iExecBlankDialog = NULL;
    // Operation succeeded

    // Now we have finished.
    if ( iState )
        {
        if ( aInitialState == EVtUiAppUiAnswered )
            {
            TRAP_IGNORE( iState->AppUiStartupPhase2DoneL() );
            TRAP_IGNORE( AppUiInitDoneDoPostInitL() );
            }
        else if ( aInitialState == EVtUiAppUiShutdown )
            {
            TRAP_IGNORE( iState->ShutdownDoneL() );
            }
        else // EVtUiAppUiStartup
            {
            TRAP_IGNORE( iState->AppUiStartupPhase1DoneL() );
            }
        }
    __VTPRINTEXIT( "VtUi.ExecInitDone" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitExecuteCommandL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecInitExecuteCommandL(
        const TVtEngCommandId aCommand,
        TRequestStatus& aRequest )
    {
    iExecDialog =
        ExecuteCmdAsyncL(
        &iExecDialog,
        aCommand,
        aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitExecuteCommandL
// -----------------------------------------------------------------------------
//
template < class T >
void CVtUiAppUi::ActiveExecInitExecuteCommandL(
        const TVtEngCommandId aCommand,
        T& aParam,
        TRequestStatus& aRequest )
    {
    iExecDialog =
        ExecuteCmdAsyncL(
        &iExecDialog,
        aCommand,
        aParam,
        aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitPrepareCameraL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecInitPrepareCameraL(
        const MVtEngMedia::TMediaSource aSource,
        TRequestStatus& aRequest )
    {
    MVtEngMedia::TPrepareCameraParams params;
    params.iMediaSource = aSource;
    params.iInitialize = ETrue;
    iExecDialog =
        ExecuteCmdAsyncL(
            &iExecDialog,
            KVtEngPrepareCamera,
            params,
            aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitSetSourceL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecInitSetSourceL(
        const MVtEngMedia::TMediaSource aSource,
        TRequestStatus& aRequest )
    {
    MVtEngMedia::TMediaSource source =
        aSource;
    iExecDialog =
        ExecuteCmdAsyncL(
            &iExecDialog,
            KVtEngSetSource,
            source,
            aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitPrepareViewFinderL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecInitPrepareViewFinderL(
        TRequestStatus& aRequest )
    {
    // Configure view finder to context pane.
    if ( iEventObserver->CommandSupported( KVtEngPrepareViewFinder ) )
        {
        TVtEngRenderingOptions configViewfinder(
            DetermineContextControlOptions() );

        iExecDialog =
            ExecuteCmdAsyncL(
                &iExecDialog,
                KVtEngPrepareViewFinder,
                configViewfinder,
                aRequest );
        }
    else
        {
        // Viewfinder does not support DSA - panic.
        VtUiPanic::Panic( EVtUiPanicPrepareViewFinderNotSupported );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecInitPrepareRemoteRenderL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecInitPrepareRemoteRenderL(
        TRequestStatus& aRequest )
    {
    if ( iEventObserver->CommandSupported( KVtEngPrepareRemoteRenderNGA ) )
        {
        // Cropping is performed when we draw the picture.
        TVtEngRenderingOptionsNGA configRemoteRenderNGA(
                DetermineRemoteVideoControlOptionsNGA() );

        iExecDialog =
            ExecuteCmdAsyncL(
                &iExecDialog,
                KVtEngPrepareRemoteRenderNGA,
                configRemoteRenderNGA,
                aRequest );
        }
    else
        {
        // Neither supported - panic.
        VtUiPanic::Panic( EVtUiPanicPrepareRemoteRenderNotSupported );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecCmdExecuteCommandL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecCmdExecuteCommandL(
        const TVtEngCommandId aCommand,
        TRequestStatus& aRequest )
    {
    iCmdExecDialog =
        ExecuteCmdAsyncL(
            &iCmdExecDialog,
            aCommand,
            aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecCmdSetSourceL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecCmdSetSourceL(
        const MVtEngMedia::TMediaSource aSource,
        TRequestStatus& aRequest )
    {
    MVtEngMedia::TMediaSource source = aSource;
    iCmdExecDialog =
        ExecuteCmdAsyncL(
            &iCmdExecDialog,
            KVtEngSetSource,
            source,
            aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ActiveExecCmdPrepareCameraL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ActiveExecCmdPrepareCameraL(
        const MVtEngMedia::TMediaSource aSource,
        TRequestStatus& aRequest )
    {
    MVtEngMedia::TPrepareCameraParams params;
    params.iMediaSource = aSource;
    params.iInitialize = ETrue;
    iCmdExecDialog =
        ExecuteCmdAsyncL(
            &iCmdExecDialog,
            KVtEngPrepareCamera,
            params,
            aRequest );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineMainControlOptions
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptions
    CVtUiAppUi::DetermineMainControlOptions( TBool aRemoteVideo )
    {
    // Determine main pane options.
    TRect screen;
    TAknWindowLineLayout stream;
    TAknLayoutRect rect;

    screen = iInstance->iMainControl->Rect();
    VtUiLayout::GetSecondWindowStreamWholeLayout(
        stream, aRemoteVideo && iUiStates->IsUseSQCif() );

    rect.LayoutRect( screen, stream );
    screen = rect.Rect();

    return TVtEngRenderingOptions( *iEventObserver, screen.Size() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineContextControlOptions
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptions CVtUiAppUi::DetermineContextControlOptions()
    {
    // Determine context pane options.
    TRect screen;
    TRect clip;
    TAknWindowLineLayout stream;
    TAknLayoutRect rect;

    VtUiLayout::GetApplicationParentRect( screen );
    VtUiLayout::GetFirstWindowBackgroundLayout( stream );
    rect.LayoutRect( screen, stream );
    TRect background = rect.Rect();

    VtUiLayout::GetFirstWindowStreamLayout( stream );
    rect.LayoutRect( screen, stream );

    // No cropping is performed, thus clip == screen.
    clip = rect.Rect();
    clip.iTl -= background.iTl;
    clip.iBr -= background.iTl;

    screen = clip;

    return
        TVtEngRenderingOptions(
            *iEventObserver,
            screen.Size() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineDialerControlOptions
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptions CVtUiAppUi::DetermineDialerControlOptions()
    {
    MVtUiDialer* dialer =  static_cast< CVtUiDialer* > (
        iFeatureManager->GetFeatureById( EVtUiFeatureIdDialer ) );

    __ASSERT_ALWAYS( dialer, VtUiPanic::Panic( EVtUiPanicRendererNotFound ) );

    return
        TVtEngRenderingOptions(
            *iEventObserver,
            dialer->VideoControl().Size() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineMainControlOptions
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptionsDSA
    CVtUiAppUi::DetermineMainControlOptionsDSA( TBool aRemoteVideo )
    {
    // Determine main pane options.
    TRect screen;
    TRect clip;
    TAknWindowLineLayout stream;
    TAknLayoutRect rect;
    const TBool usesSQCif( aRemoteVideo && iUiStates->IsUseSQCif() );
    screen = iInstance->iMainControl->Rect();
    VtUiLayout::GetSecondWindowStreamLayout( stream,
        iUiStates->IsToolbarAvailable(), usesSQCif );
    rect.LayoutRect( screen, stream );
    clip = rect.Rect();

    VtUiLayout::GetSecondWindowStreamWholeLayout( stream,
        iUiStates->IsToolbarAvailable(), usesSQCif );
    rect.LayoutRect( screen, stream );
    screen = rect.Rect();

    return
        TVtEngRenderingOptionsDSA(
            *iEventObserver,
            iEikonEnv->WsSession(),
            *( iEikonEnv->ScreenDevice() ),
            *( iInstance->iMainControl->DrawableWindow() ),
            clip,
            screen );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineContextControlOptionsDSA
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptionsDSA CVtUiAppUi::DetermineContextControlOptionsDSA()
    {
    // Determine context pane options.
    TRect screen;
    TRect clip;
    TAknWindowLineLayout stream;
    TAknLayoutRect rect;

    VtUiLayout::GetApplicationParentRect( screen );
    VtUiLayout::GetFirstWindowBackgroundLayout( stream );
    rect.LayoutRect( screen, stream );
    TRect background = rect.Rect();

    VtUiLayout::GetFirstWindowStreamLayout( stream );
    rect.LayoutRect( screen, stream );

    // No cropping is performed, thus clip == screen.
    clip = rect.Rect();
    clip.iTl -= background.iTl;
    clip.iBr -= background.iTl;

    screen = clip;

    return
        TVtEngRenderingOptionsDSA(
            *iEventObserver,
            iEikonEnv->WsSession(),
            *( iEikonEnv->ScreenDevice() ),
            *( iInstance->iContextControl->DrawableWindow() ),
            screen,
            clip );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineDialerControlOptionsDSA
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptionsDSA CVtUiAppUi::DetermineDialerControlOptionsDSA()
    {
    MVtUiDialer* dialer =  static_cast< CVtUiDialer* > (
        iFeatureManager->GetFeatureById( EVtUiFeatureIdDialer ) );

    __ASSERT_ALWAYS( dialer, VtUiPanic::Panic( EVtUiPanicRendererNotFound ) );

    CCoeControl& videoWindow( dialer->VideoControl() );

    return
        TVtEngRenderingOptionsDSA(
            *iEventObserver,
            iEikonEnv->WsSession(),
            *( iEikonEnv->ScreenDevice() ),
            *( videoWindow.DrawableWindow() ),
            videoWindow.Rect(),
            videoWindow.Rect() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineMainControlOptionsDP
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptionsDP
    CVtUiAppUi::DetermineMainControlOptionsDP( TBool aRemoteVideo )
    {
    // Determine main pane options.
    const TRect screen( iInstance->iMainControl->Rect() );
    TAknWindowLineLayout stream;
    const TBool usesSQCif( aRemoteVideo && iUiStates->IsUseSQCif() );

    // Even if the name is whole layout, this layout is (due to problem
    // in layouts) video stream layout
    TAknLayoutRect whole;
    VtUiLayout::GetSecondWindowStreamWholeLayout( stream,
        iUiStates->IsToolbarAvailable(), usesSQCif );
    whole.LayoutRect( screen, stream );

    // Even if the name is actual layout, this layout is (due to problem
    // in layouts) whole == clipping layout
    TAknLayoutRect actual;
    VtUiLayout::GetSecondWindowStreamLayout( stream,
        iUiStates->IsToolbarAvailable(), usesSQCif );
    actual.LayoutRect( screen, stream );

    return
        TVtEngRenderingOptionsDP(
            *iEventObserver,
            iEikonEnv->WsSession(),
            *( iEikonEnv->ScreenDevice() ),
            *( iInstance->iMainControl->DrawableWindow() ),
            actual.Rect(),
            whole.Rect(),
            iInstance->iMainControl->PositionRelativeToScreen() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineContextControlOptionsDP
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptionsDP CVtUiAppUi::DetermineContextControlOptionsDP()
    {
    // Determine context pane options.
    TAknWindowLineLayout stream;
    TAknLayoutRect rect;

    TRect screen;
    VtUiLayout::GetApplicationParentRect( screen );
    VtUiLayout::GetFirstWindowBackgroundLayout( stream );
    rect.LayoutRect( screen, stream );
    const TRect background( rect.Rect() );

    VtUiLayout::GetFirstWindowStreamLayout( stream );
    rect.LayoutRect( screen, stream );

    // No cropping is performed, thus clip == screen.
    TRect clip( rect.Rect() );
    clip.iTl -= background.iTl;
    clip.iBr -= background.iTl;

    return
        TVtEngRenderingOptionsDP(
            *iEventObserver,
            iEikonEnv->WsSession(),
            *( iEikonEnv->ScreenDevice() ),
            *( iInstance->iContextControl->DrawableWindow() ),
            clip,
            clip,
            iInstance->iContextControl->PositionRelativeToScreen() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineDialerControlOptionsDP
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptionsDP CVtUiAppUi::DetermineDialerControlOptionsDP()
    {
    MVtUiDialer* dialer =  static_cast< CVtUiDialer* > (
        iFeatureManager->GetFeatureById( EVtUiFeatureIdDialer ) );

    __ASSERT_ALWAYS( dialer, VtUiPanic::Panic( EVtUiPanicRendererNotFound ) );

    CCoeControl& videoWindow( dialer->VideoControl() );

    TPoint offs( videoWindow.DrawableWindow()->AbsPosition() );
    TRect rect( videoWindow.Rect() );
    return
        TVtEngRenderingOptionsDP(
            *iEventObserver,
            iEikonEnv->WsSession(),
            *( iEikonEnv->ScreenDevice() ),
            *( videoWindow.DrawableWindow() ),
            rect,
            rect,
            offs );
    }
// -----------------------------------------------------------------------------
// CVtUiAppUi::DetermineRemoteVideoControlOptionsNGA
// -----------------------------------------------------------------------------
//
TVtEngRenderingOptionsNGA
    CVtUiAppUi::DetermineRemoteVideoControlOptionsNGA()
    {
        return TVtEngRenderingOptionsNGA( *iEventObserver,
                iInstance->iRemoteVideoControl ->GetRWindow() , iEikonEnv->WsSession());
    }
// -----------------------------------------------------------------------------
// CVtUiAppUi::ExecuteCmdL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ExecuteCmdL( const TVtEngCommandId aCommand )
    {
    DoExecuteCmdL( aCommand, NULL );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ExecuteCmdL
// -----------------------------------------------------------------------------
//
template< class T >
void CVtUiAppUi::ExecuteCmdL(
        const TVtEngCommandId aCommand,
        T& aParam )
    {
    TPtrC8 params( reinterpret_cast< TUint8* >( &aParam ), sizeof( T ) );
    DoExecuteCmdL( aCommand, &params );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoExecuteCmdL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::DoExecuteCmdL(
        const TVtEngCommandId aCommand,
        TDesC8* aParams )
    {
    __VTPRINT2( DEBUG_GEN, "VtUi.DoExec.cmd=%d", aCommand )
    MVtEngCommandHandler& command = Model().CommandHandler();
    const TInt caps = command.GetCommandCaps( aCommand );

    if ( caps >= KErrNone )
        {
        const TBool asynchronous =
            ( caps & MVtEngCommandHandler::EAttribAsync );

        if ( asynchronous  )
            {
            if ( aCommand == KVtEngHandleLayoutChange )
                {
                CVtEngCmdExec* cmdExec = CVtEngCmdExec::NewL(
                    Model().CommandHandler(), *iEventObserver, *GetCba() );
                cmdExec->ExecuteCmdLD( aCommand );
                }
            else
                {
                CVtUiExecuteCmdDialog* dlg =
                    new ( ELeave ) CVtUiExecuteCmdDialog(
                        NULL,
                        Model().CommandHandler(),
                        *iEventObserver );
                dlg->ExecuteCmdLD( aCommand, aParams, NULL );
                }
            }
        else
            {
            command.ExecuteL( aCommand, aParams );
            RefreshStatesL();
            }
        }
    else
        {
        // Failed.
        User::Leave( caps );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleShutdownReady
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleShutdownReady()
    {
    __VTPRINTENTER( "VtUi.HandleShutdownReady" )

    if(iAsyncCallback->IsActive())
        {
        iAsyncCallback->Cancel();
        }

    iAsyncCallback->Set(
        TCallBack( &DoExit, this ) );
    iAsyncCallback->CallBack();
    __VTPRINTEXIT( "VtUi.HandleShutdownReady" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ContextControl
// -----------------------------------------------------------------------------
//
CVtUiContextControl& CVtUiAppUi::ContextControl()
   {
    __VTPRINTENTER( "VtUi.ContextControl" )
   __VTPRINTEXIT( "VtUi.ContextControl" )
   return *iInstance->iContextControl;
   }

// -----------------------------------------------------------------------------
// CVtUiAppUi::MainControl
// -----------------------------------------------------------------------------
//
CVtUiMainControl& CVtUiAppUi::MainControl()
   {
   __VTPRINTENTER( "VtUi.MainControl" )
   __VTPRINTEXIT( "VtUi.MainControl" )
   return *iInstance->iMainControl;
   }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RemoteVideoControl
// -----------------------------------------------------------------------------
//
CVtUiRemoteVideoControl& CVtUiAppUi::RemoteVideoControl()
   {
   __VTPRINTENTER( "VtUi.RemoteVideoControl" )
   __VTPRINTEXIT( "VtUi.RemoteVideoControl" )
   return *iInstance->iRemoteVideoControl;
   }

// -----------------------------------------------------------------------------
// CVtUiAppUi::EndCallButtonPane
// -----------------------------------------------------------------------------
//
CVtUiEndCallButtonPane& CVtUiAppUi::EndCallButtonPane()
   {
   __VTPRINTENTER( "VtUi.EndCallButtonPane" )
   __VTPRINTEXIT( "VtUi.EndCallButtonPane" )
   return *iInstance->iEndCallButtonPane;
   }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoExit
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::DoExit( TAny* aAppUi )
    {
    __VTPRINTENTER( "VtUi.DoExit" )
    CVtUiAppUi* self = static_cast< CVtUiAppUi* >( aAppUi );
    self->iAsyncCallback->Cancel();
    // Before exiting ensure there are no pending actions.
    self->ActiveExecInitCancel( 0 );
    self->Exit();
    __VTPRINTEXIT( "VtUi.DoExit" )
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ExecuteCmdAsyncL
// -----------------------------------------------------------------------------
//
CEikDialog* CVtUiAppUi::ExecuteCmdAsyncL(
        CEikDialog** aDialogPtr,
        const TVtEngCommandId aCommand,
        TRequestStatus& aStatus )
    {
    return DoExecuteCmdAsyncL( aDialogPtr, aCommand, NULL, aStatus );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ExecuteCmdAsyncL
// -----------------------------------------------------------------------------
//
template< class T >
CEikDialog* CVtUiAppUi::ExecuteCmdAsyncL(
        CEikDialog** aDialogPtr,
        const TVtEngCommandId aCommand,
        T& aParam,
        TRequestStatus& aStatus )
    {
    TPtrC8 params( reinterpret_cast< TUint8* >( &aParam ), sizeof( T ) );
    return DoExecuteCmdAsyncL( aDialogPtr, aCommand, &params, aStatus );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoExecuteCmdAsyncL
// -----------------------------------------------------------------------------
//
CEikDialog* CVtUiAppUi::DoExecuteCmdAsyncL(
        CEikDialog** aDialogPtr,
        const TVtEngCommandId aCommand,
        TDesC8* aParams,
        TRequestStatus& aStatus )
    {
    __VTPRINT2( DEBUG_GEN, "VtUi.DoExecAsync.cmd=%d", aCommand )
    MVtEngCommandHandler& command = Model().CommandHandler();
    const TInt caps = command.GetCommandCaps( aCommand );

    if ( caps >= KErrNone )
        {
        const TBool asynchronous =
            ( caps & MVtEngCommandHandler::EAttribAsync );

        if ( asynchronous  )
            {
            CVtUiExecuteCmdDialog* dlg =
                new ( ELeave ) CVtUiExecuteCmdDialog(
                    aDialogPtr,
                    Model().CommandHandler(),
                    *iEventObserver );
            dlg->ExecuteCmdLD( aCommand, aParams, &aStatus );
            return dlg;
            }
        else
            {
            command.ExecuteL( aCommand, aParams );
            RefreshStatesL();
            TRequestStatus* status = &aStatus;
            User::RequestComplete( status, KErrNone );
            }
        }
    else
        {
        // Failed.
        User::Leave( caps );
        }

    return NULL;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::Execute
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::Execute( const TVtEngCommandId aCommand, TDesC8* aParam )
    {
    MVtEngCommandHandler& command = Model().CommandHandler();
    TRAPD( err, command.ExecuteL( aCommand, aParam ) );
#ifdef VTDEBUG
    if ( err != KErrNone )
        {
        __VTPRINT3( DEBUG_GEN, "VtUi.Execute.Nok.cmd=%d,err=%d", aCommand, err )
        }
#endif // VTDEBUG
    return err;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleForegroundChangedL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleForegroundChangedL(
        TBool aIsForeground )
    {
    __VTPRINTENTER( "VtUi.HandleForegroundChangedL" )
    __VTPRINT2( DEBUG_GEN, "VtUi.foreground=%d", (TInt) aIsForeground )


    // Let the Engine know that Application's foregorund
    // has changed. Then Engine can do some initalize/uninitalize
    // before rendering due to the foreground state.
    iState->PreHandleForegroundChangedL(aIsForeground);

    // These operations must be done before
    // sending KVtEngSetUIForeground command to engine i.e. calling
    // iState->HandleForegroundChangedL( aIsForeground )
    if ( !aIsForeground  )
        {
        // if capture mode is on stop it
        if ( iUiStates->IsCaptureModeOn() )
            {
            CmdCancelCaptureL();
            }
        // if brightness or contrast feature is active stop those
        MVtUiFeature* br = iFeatureManager->GetFeatureById( EVtUiFeatureIdBrightness );
        if ( br )
            {
            __VTPRINT( DEBUG_GEN, "VtUi.HandleForegroundChangedL br" )
            if ( br->State() ==  MVtUiFeature::EActive )
                {
                __VTPRINT( DEBUG_GEN, "VtUi.HandleForegroundChangedL br->STOP" )
                br->Stop();
                }
            }

        MVtUiFeature* cr = iFeatureManager->GetFeatureById( EVtUiFeatureIdContrast );
        if ( cr )
            {
            __VTPRINT( DEBUG_GEN, "VtUi.HandleForegroundChangedL cr" )
            if ( cr->State() ==  MVtUiFeature::EActive )
               {
               __VTPRINT( DEBUG_GEN, "VtUi.HandleForegroundChangedL cr->STOP" )
               cr->Stop();
               }
            }

        }

    TBool foregroundAndReady = EFalse;
    if ( iState )
        {
        foregroundAndReady = iState->HandleForegroundChangedL( aIsForeground );
        iUiStates->SetThisApplicationForeground( aIsForeground );
        }
    if ( foregroundAndReady )
        {
        // Refresh navi pane. This will start call duration updating
        // if necessary.
        RefreshNaviPaneL();
        }
    else if ( !aIsForeground )
        {


        iEventObserver->StopBeat();
        }
    SetIncallBubbleAllowedInUsualL( !foregroundAndReady );
    __VTPRINTEXIT( "VtUi.HandleForegroundChangedL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshL( const TInt aRefreshFlags )
    {
    if ( aRefreshFlags & EUiStates )
        {
        RefreshNaviPaneL();
        }
    if ( aRefreshFlags & EBlind )
        {
        RefreshBlind();
        }
    if ( aRefreshFlags & ENaviPane )
        {
        RefreshNaviPaneL();
        }
    if ( aRefreshFlags & ESoftkeys )
        {
        RefreshSoftkeysL();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleEngineResetL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleEngineResetL()
    {
    __VTPRINTENTER( "VtUi.HandleEngineResetL" )
    if ( iShutdownRequest )
        {
        __VTPRINT( DEBUG_GEN, "  VtUi.HandleEngineResetL shutdown" )
        User::RequestComplete( iShutdownRequest, KErrNone );
        iShutdownRequest = NULL;
        }
    __VTPRINTEXIT( "VtUi.HandleEngineResetL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::StopWaitingImage
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::StopWaitingImage()
    {
    if ( iInstance )
        {
        iDownlinkWindow->SetWaiting( EFalse );
        iUiStates->SetWaitingForFirstFrame( EFalse );
        RemoteVideoControl().MakeVisible(ETrue);
        iDownlinkWindow->LayoutRemoteVideo();
        }
    }

void CVtUiAppUi::StopWhiteBalanceOrColortone()
    {
    if( iEventObserver )
        {
        MVtEngMedia::TCameraId currentCamId;
        //CVtEngMediaHandler& mediaHandler = iEventObserver->Model().Media();
        ///mediaHandler.GetCurrentCameraId( currentCamId );
        iEventObserver->Model().Media().GetCurrentCameraId( currentCamId );
        __VTPRINT2( DEBUG_GEN, "  CVtUiAppUi::StopWhiteBalance currentCamId is %d", currentCamId);
        
        CVtUiWhiteBalance* wb = static_cast< CVtUiWhiteBalance* >(
                                iFeatureManager->GetFeatureById( EVtUiFeatureIdWhiteBalance ) );
        CVtUiColorTone* ct = static_cast< CVtUiColorTone* >(
        iFeatureManager->GetFeatureById( EVtUiFeatureIdColourTone ) );
        
        // only when the current camera switch to the Primary to stop the wb
        if( currentCamId == MVtEngMedia::EPrimaryCamera )
            {
            
            if( wb && ( wb->State() == MVtUiFeature::EActive ) )
                {
                    
                wb->Stop();
                }
            
            if( ct && ( ct->State() == MVtUiFeature::EActive ) )
                {                    
                ct->Stop();
                }
            
            return;
            }
        if( currentCamId == MVtEngMedia::ESecondaryCamera )
            {
            if( wb && wb->IsPendingCmd() )
                wb->HandlePendingCmdL();
            if( ct && ct->IsPendingCmd() )
                ct->HandlePendingCmdL();
            }
        }
    }
// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleLayoutChanged
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::HandleLayoutChanged()
    {
    iLayoutChangeCallback->CallBack();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DelayedHandleLayoutChanged
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::DelayedHandleLayoutChanged( TAny* aPtr )
    {
    CVtUiAppUi* self = reinterpret_cast< CVtUiAppUi* > ( aPtr );
    self->iUiStates->SetDisableBlindSetting( ETrue );
    TRAPD( err, self->HandleLayoutChangedL() );
    self->iUiStates->SetDisableBlindSetting( EFalse );
    self->RefreshBlind();
    return err;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleLayoutChangedL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleLayoutChangedL()
    {
    __VTPRINTENTER( "VtUi.LayoutChg" )
    if ( iState )
        {
        iState->HandleLayoutChangedL();
        }
    __VTPRINTEXIT( "VtUi.LayoutChg" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoHandleLayoutChangedL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::DoHandleLayoutChangedL()
    {
    __VTPRINTENTER( "VtUi.DoLayoutChg" )
    // Fully update rendering parameters
    UpdateRenderingParametersL();
    // Notify engine about layout change
    iLayoutChg = ETrue;
    TRAPD( error, ExecuteCmdL( KVtEngHandleLayoutChange ) );
    iLayoutChg = EFalse;

    // Not ready error is allowed to happen (e.g. when sharing)
    if ( error && ( error != KErrNotReady ) )
        {
        User::Leave( error );
        }
    else
        {
        __VTPRINT( DEBUG_GEN,
            "VtUi.DoLayoutChg KVtEngHandleLayoutChange == KErrNotReady (ok)" )
        TVtEngCommandId pendingCommand = Model().CommandHandler().PendingCommand();
        TVtEngCommandId invalidCommand = Model().CommandHandler().InvalidCommand();
        
        __VTPRINT2( DEBUG_GEN, "VtUi.DoLayoutChg pendingCommand=%d",
                pendingCommand )
        
        __VTPRINT2( DEBUG_GEN, "VtUi.DoLayoutChg invalidCommand=%d",
                invalidCommand )
        
        if ( pendingCommand  == KVtEngMuteOutgoingAudio || 
                pendingCommand  == KVtEngUnmuteOutgoingAudio ||
                pendingCommand  == KVtEngSetAudioRouting ||
                pendingCommand  == KVtEngSetAudioVolume ||
                pendingCommand  == KVtEngSetSource ||
                pendingCommand  == KVtEngPrepareCamera ||
                pendingCommand  == KVtEngUnfreeze ||
                invalidCommand  == KVtEngHandleLayoutChange )
            {
            iPendingCmd = pendingCommand;
            iUiStates->SetLayoutChangeNeeded( ETrue );
            }
        }
    // Notify component manager
    iComponentManager->HandleLayoutChangeL();
    MVtUiFeature* dialer =
        iFeatureManager->GetFeatureById( EVtUiFeatureIdDialer );
    const TBool dialerActive( dialer &&
        ( dialer->State() == MVtUiFeature::EActive ) );
    SwitchLayoutToFlatStatusPaneL( dialerActive );
    
    // Update the cam's whiteBalance and colorTone cause layoutchange will renew the camera,so
    // restore the last user setting
    UpdateVBSettingL();
    

    if ( iDelayedCmd != 0 )
        {
        __VTPRINT2( DEBUG_GEN, "VtUi.DoLayoutChg reexecute the delayed cmd=%d", iDelayedCmd);
        if( iDelayedCmd == EAknSoftkeyOptions )
            {
            ProcessCommandL( iDelayedCmd );
            }
        else
            {
            HandleCommandL( iDelayedCmd );
            }
        iDelayedCmd = 0;
        }
    __VTPRINTEXIT( "VtUi.DoLayoutChg" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleVideoFrameL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleVideoFrameL(
        const TBool aLocal,
        CFbsBitmap* aBitmap )
    {
    if ( aLocal )
        {
        iUplinkWindow->SetStreamBitmap( aBitmap );

        if ( aBitmap )
            {
            // If white balance or color tone setting feauture is
            // active update feature's setting page's background.
            CVtUiWhiteBalance* wb = static_cast< CVtUiWhiteBalance* >(
            iFeatureManager->GetFeatureById( EVtUiFeatureIdWhiteBalance ) );

            CVtUiColorTone* ct = static_cast< CVtUiColorTone* >(
            iFeatureManager->GetFeatureById( EVtUiFeatureIdColourTone ) );

            if ( wb )
                {
                  __VTPRINT( DEBUG_GEN,"VtUi.HandleVideoFrameL WB" )
                if ( wb->State() == MVtUiFeature::EActive )
                    {
                    __VTPRINT( DEBUG_GEN,"VtUi.HandleVideoFrameL WB update" )
                    wb->UpdateBackground( aBitmap );
                    }
                }
            if ( ct )
                {
                 __VTPRINT( DEBUG_GEN,"VtUi.HandleVideoFrameL CT" )
                if (ct->State() == MVtUiFeature::EActive)
                    {
                     __VTPRINT( DEBUG_GEN,"VtUi.HandleVideoFrameL CT update" )
                    ct->UpdateBackground( aBitmap );
                    }
                }
            }
        }
    else
        {
        iDownlinkWindow->SetStreamBitmap( aBitmap );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetVideoFrame
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetVideoFrame(
        const TBool aLocal,
        CFbsBitmap* aBitmap )
    {
    if ( aLocal )
        {
        }
    else
        {
        iDownlinkWindow->SetStreamBitmapReserve( aBitmap );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleVideoFrameRemoteProblemL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleVideoFrameRemoteProblemL()
    {
    __VTPRINTENTER( "VtUi.HandleRemote" )
    HandleVideoFrameL( EFalse, NULL );
    __VTPRINTEXIT( "VtUi.HandleRemote" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleVideoFrameLocalProblemL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleVideoFrameLocalProblemL()
    {
    __VTPRINTENTER( "VtUi.HandleLocal" )
    // Camera might have changed - better to stop zoom.
    HandleVideoFrameL( ETrue, NULL );
    __VTPRINTEXIT( "VtUi.HandleLocal" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RemoteVideoIsSQCif
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RemoteVideoIsSQCif( TBool aIsSQCif )
    {
    iUiStates->SetUseSQCif( aIsSQCif );
    if ( iDownlinkWindow == iInstance->iMainControl )
        {
        ControlUsesSQCif( aIsSQCif );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ControlUsesSQCif
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ControlUsesSQCif( TBool aIsSQCif )
    {
    iInstance->iMainControl->SupportSQCif( aIsSQCif );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ChangeRemoteVideoLayoutL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ChangeRemoteVideoLayoutL()
    {
    HandleLayoutChanged();
    if ( iDownlinkWindow == iInstance->iMainControl )
        {
        iDownlinkWindow->SetBlind( EFalse );
        StopWaitingImage();
        iInstance->iMainControl->DrawNow();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowImageInitializeProgressL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowImageInitializeProgressL()
    {
    __VTPRINTENTER( "VtUi.ShowImageInitializeProgressL" )
    ShowProgressDialogL( R_PROGRESS_DECODING_IMAGE_WAIT_NOTE, this );
    __VTPRINTEXIT( "VtUi.ShowImageInitializeProgressL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HideImageInitializeProgressL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HideImageInitializeProgressL()
    {
    __VTPRINTENTER( "VtUi.HideImageInitializeProgressL" )
    // if volume slider is visible hide it
    CVtUiVolume* volume = static_cast< CVtUiVolume* >(
    iFeatureManager->GetFeatureById( EVtUiFeatureIdVolume ) );
    if ( volume )
         {
         volume->Stop();
         }
    HideProgressDialogL();
    __VTPRINTEXIT( "VtUi.HideImageInitializeProgressL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CheckBeatL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CheckBeatL( const TBool aCallDurationEnabled )
    {
    // Update call duration periodically if necessary.
    const MVtEngSessionInfo::TSessionState state = Model().Session().State( EFalse );
    const TBool timerEnable =
        ( aCallDurationEnabled ) &&
        ( ( state == MVtEngSessionInfo::EConnected ) ||
          ( state == MVtEngSessionInfo::ENegotiating ) ||
          ( state == MVtEngSessionInfo::EOpen ) );

    if ( timerEnable && iUiStates->IsThisApplicationForeground() )
        {
        iEventObserver->StartBeatL();
        }
    else
        {
        iEventObserver->StopBeat();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleBeat
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleBeat()
    {
    TRAP_IGNORE( RefreshNaviPaneL(); );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowCameraInUseNoteL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowCameraInUseNoteL() const
    {
    // The note must not be blocking.

    CAknNoteDialog* dlg = new ( ELeave ) CAknNoteDialog( NULL );

    dlg->PrepareLC( R_VIDEOTELUI_INFORMATION_NOTE );
    dlg->ButtonGroupContainer().SetCommandSetL( R_AVKON_SOFTKEYS_OK_EMPTY );

    HBufC* buf = StringLoader::LoadLC( R_VIDEOTELUI_QTN_INCAL_CLOSE_CAMCORDER );
    dlg->SetTextL( *buf );
    CleanupStack::PopAndDestroy( buf );

    dlg->SetTone( CAknNoteDialog::EConfirmationTone );
    dlg->SetTimeout( CAknNoteDialog::EUndefinedTimeout );
    dlg->RunLD();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowNotAllowedNoteL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowNotAllowedNoteL() const
    {
    HBufC* prompt =
        StringLoader::LoadLC(
            R_VIDEOTELUI_TEXT_NOT_ALLOWED );

    CAknInformationNote* note =
        new ( ELeave ) CAknInformationNote( ETrue );
    note->ExecuteLD( *prompt );
    CleanupStack::PopAndDestroy( prompt );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowCallNotAllowedNoteL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowCallNotAllowedNoteL() const
    {
    HBufC* prompt =
        StringLoader::LoadLC(
            R_VIDEOTELUI_TEXT_CALL_NOT_ALLOWED );

    CAknInformationNote* note =
        new ( ELeave ) CAknInformationNote( ETrue );
    note->ExecuteLD( *prompt );
    CleanupStack::PopAndDestroy( prompt );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowOtherCameraNotUsableNoteL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowOtherCameraNotUsableNoteL() const
    {
    HBufC* prompt =
        StringLoader::LoadLC(
            R_VIDEOTELUI_QTN_ERR_CAM_SWAP );

    CAknInformationNote* note =
        new ( ELeave ) CAknInformationNote( ETrue );
    note->ExecuteLD( *prompt );
    CleanupStack::PopAndDestroy( prompt );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowUnableToOpenNoteL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowUnableToOpenNoteL() const
    {
    HBufC* prompt =
        StringLoader::LoadLC(
            R_VIDEOTELUI_QTN_ERR_UNABLE_TO_OPEN_IMAGE );
    CAknInformationNote* note =
        new ( ELeave ) CAknInformationNote( ETrue );
    note->ExecuteLD( *prompt );
    CleanupStack::PopAndDestroy( prompt );
    }

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowImageDecodingErrorNoteL()
    {
    HBufC* prompt =
        StringLoader::LoadLC(
            R_VIDEOTELUI_QTN_INCAL_NOTE_DECODING_FAILED );
    CAknInformationNote* note =
        new ( ELeave ) CAknInformationNote( ETrue );
    note->ExecuteLD( *prompt );
    CleanupStack::PopAndDestroy( prompt );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowDRMNotAllowedNoteL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowDRMNotAllowedNoteL() const
    {
    HBufC* prompt =
        StringLoader::LoadLC(
            R_VIDEOTELUI_QTN_ERR_DRM_NOT_ALLOWED );
    CAknInformationNote* note =
        new ( ELeave ) CAknInformationNote( ETrue );
    note->ExecuteLD( *prompt );
    CleanupStack::PopAndDestroy( prompt );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetSoftkeysL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetSoftkeysL( const TInt aSoftkeyResourceId )
    {
    if ( iCurrentSoftkeys != aSoftkeyResourceId )
        {
        if ( iCba )
            {
            iCba->SetCommandSetL( aSoftkeyResourceId );
            iCba->DrawNow();
            }
        iCurrentSoftkeys = aSoftkeyResourceId;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetHiddenL
// Makes application visible / invisible in fast swap window.
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetHiddenL(
        const TBool aHidden )
    {
    CEikonEnv* eikonEnv = iEikonEnv;
    CApaWindowGroupName* windowGroupName =
        CApaWindowGroupName::NewLC(
            eikonEnv->WsSession(),
            iThisApplicationWgId );
    windowGroupName->SetHidden( aHidden );
    User::LeaveIfError(
        windowGroupName->SetWindowGroupName(
            eikonEnv->RootWin() ) );
    CleanupStack::PopAndDestroy( windowGroupName );

    // Update application UID.
    TUid applicationUid = KVtUiAppUid;
    if ( aHidden )
        {
        applicationUid.iUid = KVtUiTelephoneUid.iUid;
        }
    __VTPRINT2( DEBUG_GEN, "VtUi.SetHiddenL applicationUid.iUid=%x",
        applicationUid.iUid )
    // Set application that is "default top application"
    TInt originalTopAppUid = 0;
    TInt err = RProperty::Get(
        KPSUidUikon,
        KUikVideoCallTopApp,
        originalTopAppUid );
    __VTPRINT3( DEBUG_GEN, "VtUi.SetHiddenL orig. topApp=%x, err=%d",
    originalTopAppUid, err )
    if ( originalTopAppUid != applicationUid.iUid &&
         iUiStates->IsDetailsReceived() )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.SetHiddenL Do write KUikVideoCallTopApp" )
        // Update key only if differs from original value and call
        // has been answered
        RProperty::Set(
            KPSUidUikon,
            KUikVideoCallTopApp,
            applicationUid.iUid );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetCallIdL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetCallIdL( const TInt aCallId )
    {
    HBufC* titlePane =
        StringLoader::LoadLC( R_VIDEOTELUI_QTN_CALL_NUMBER_VIDEO, aCallId );
    TPtr ptr = titlePane->Des();
    AknTextUtils::DisplayTextLanguageSpecificNumberConversion( ptr );
    TitlePaneL()->SetText( titlePane );
    CleanupStack::Pop( titlePane );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetCallNameL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::SetCallNameL( const TDesC& aName )
    {
    HBufC* nameBuf = aName.Alloc();
    if ( nameBuf )
        {
        TPtr ptr = nameBuf->Des();
        AknTextUtils::DisplayTextLanguageSpecificNumberConversion( ptr );
        TitlePaneL()->SetText( nameBuf );
        }

    return ( nameBuf != NULL );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::BringTelephoneForeground
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::BringTelephoneToForeground()
    {
    __VTPRINTENTER( "VtUi.BringTelephoneToForeground" )
    // If Telephone application is running, then
    // bring it to the foreground.
    const TInt windowGroupId = TelephoneApplicationWgId();
    if ( windowGroupId )
        {
        CEikonEnv* eikonEnv = iEikonEnv;
        TApaTask task( eikonEnv->WsSession() );
        task.SetWgId( windowGroupId );
        task.BringToForeground();
        }

    // In any case, send this application to the background.
    ChangeApplicationFocus( EFalse );
    __VTPRINTEXIT( "VtUi.BringTelephoneToForeground" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ChangeApplicationFocus
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ChangeApplicationFocus( const TBool aForeground )
    {
    __VTPRINTENTER( "VtUi.ChangeApplicationFocus" )
    CEikonEnv* eikonEnv = iEikonEnv;
    TApaTask task( eikonEnv->WsSession() );
    task.SetWgId( iThisApplicationWgId );
    if ( !aForeground )
        {
        task.SendToBackground();
        }
    else if ( !iUiStates->IsDeviceLockOn() )
        {
        task.BringToForeground();
        }
    __VTPRINTEXIT( "VtUi.ChangeApplicationFocus" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::TelephoneApplicationWgId
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::TelephoneApplicationWgId()
    {
    TInt resultWgId = 0;

    TApaTaskList taskList( iEikonEnv->WsSession() );
    TInt appUid = 0;

    // Try first Telephone application.
    if ( RProperty::Get(
             KPSUidTelInformation,
             KTelPhoneUid,
             appUid ) == KErrNone )
        {
        TApaTask task = taskList.FindApp( TUid::Uid( appUid ) );
        if ( task.Exists() )
            {
            resultWgId = task.WgId();
            }
        }

    // Then Idle application.
    if ( !resultWgId &&
         ( RProperty::Get(
               KPSUidAiInformation,
               KActiveIdleUid,
               appUid ) == KErrNone ) )
        {
        TApaTask task = taskList.FindApp( TUid::Uid( appUid ) );
        if ( task.Exists() )
            {
            resultWgId = task.WgId();
            }
        }

    return resultWgId;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowNumberEntry
// -----------------------------------------------------------------------------
//
inline TBool CVtUiAppUi::ShowNumberEntry() const
    {
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::IsActiveIdleEnabledL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::IsActiveIdleEnabledL() const
    {
    TVtUiActiveIdleVariation activeIdleVariation;
    return activeIdleVariation.IsActiveIdleEnabled();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CheckEngineFunctionality
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CheckEngineFunctionality()
    {
    const TBool prepareViewFinder =
        iEventObserver->CommandSupportedAndSynchronous(
             KVtEngPrepareViewFinder );
    const TBool prepareRemoteRender =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngPrepareRemoteRender );
    const TBool prepareRemoteRenderDSA =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngPrepareRemoteRenderDSA );
    const TBool prepareRemoteRenderDP =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngPrepareRemoteRenderDP );
    const TBool stopViewFinder =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngStopViewFinder );
    const TBool startViewFinder =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngStartViewFinder );
    const TBool stopRemoteRender =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngStopRenderRemote );
    const TBool startRemoteRender =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngStartRenderRemote );
    const TBool setUIForeground =
        iEventObserver->CommandSupportedAndSynchronous(
            KVtEngSetUIForeground );

    TVtUiDPVariation dpvariation;
    TBool dpSupported( dpvariation.IsDPSupported() );

    if ( !prepareViewFinder ||
         ( !prepareRemoteRender && !prepareRemoteRenderDSA && !dpSupported ) ||
         ( !prepareRemoteRender && !prepareRemoteRenderDP && dpSupported ) ||
         !stopViewFinder ||
         !startViewFinder ||
         !stopRemoteRender ||
         !startRemoteRender ||
         !setUIForeground )
        {
        // Not supported - should never occur.
        __VTPRINT( DEBUG_GEN, "VtUi.EngineFunc.ASSERT" )
        VtUiPanic::Panic( EVtUiPanicEngineFunctionalityAssert );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::Model
// -----------------------------------------------------------------------------
//
CVtEngModel& CVtUiAppUi::Model()
    {
    return iEventObserver->Model();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::VideoTelephonyVariation
// -----------------------------------------------------------------------------
//
const TVtUiVideoTelephonyVariation& CVtUiAppUi::VideoTelephonyVariation() const
    {
    return iVTVariation;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::NumberSource
// -----------------------------------------------------------------------------
//
MVtUiNumberSource* CVtUiAppUi::NumberSource() const
    {
    return iNumberSource;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::NaviPaneL
// -----------------------------------------------------------------------------
//
inline CAknNavigationControlContainer* CVtUiAppUi::NaviPaneL()
    {
    return
        static_cast< CAknNavigationControlContainer* >
            ( StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidNavi ) ) );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::TitlePaneL
// -----------------------------------------------------------------------------
//
inline CAknTitlePane* CVtUiAppUi::TitlePaneL()
    {
    return
        static_cast< CAknTitlePane* >
            ( StatusPane()->ControlL( TUid::Uid( EEikStatusPaneUidTitle ) ) );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CleanupPushRefreshL
// -----------------------------------------------------------------------------
//
inline void CVtUiAppUi::CleanupPushRefreshL()
    {
    CleanupStack::PushL(
        TCleanupItem( DoRefresh, this ) );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CleanupPushEnableBlindL
// -----------------------------------------------------------------------------
//
inline void CVtUiAppUi::CleanupPushEnableBlindL()
    {
    CleanupStack::PushL(
        TCleanupItem( DoEnableBlindSetting, this ) );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::EnableCommandActivatingAndCleanupPushL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::EnableCommandActivatingAndCleanupPushL()
    {
    __VTPRINTENTER( "VtUi.EnableCommandActivatingAndCleanupPushL" )
    // add anyway to cleanup stack to avoid caring about stack balance
    CleanupStack::PushL(
        TCleanupItem( DoDisableCommandActivating, this ) );
    // but in case of consecutive calls on this don't refresh (avoid flicker)
    const TBool alreadyActivating( iUiStates->IsCommandActivating() );
    // increases ref.count if alread set as activating
    iUiStates->SetIsCommandActivating( ETrue );
    if ( !alreadyActivating )
        {
        // refresh only when ref.count incremented from zero.
        iCommandManager->RefreshL();
        }
    __VTPRINTEXIT( "VtUi.EnableCommandActivatingAndCleanupPushL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoDisableCommandActivating
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::DoDisableCommandActivating( TAny* aAny )
    {
    CVtUiAppUi* self =
        reinterpret_cast< CVtUiAppUi* >( aAny );
    TRAP_IGNORE( self->HandleCommandDeactivationL() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HandleCommandDeactivationL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HandleCommandDeactivationL()
    {
    __VTPRINTENTER( "VtUi.HandleCommandDeactivationL" )
    iUiStates->SetIsCommandActivating( EFalse );
    if ( !iUiStates->IsCommandActivating() )
        {
        RefreshStatesL();
        }
    __VTPRINTEXIT( "VtUi.HandleCommandDeactivationL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoEnableBlindSetting
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::DoEnableBlindSetting( TAny* aAny )
    {
    CVtUiAppUi* self =
        reinterpret_cast< CVtUiAppUi* >( aAny );
    self->iUiStates->SetDisableBlindSetting( EFalse );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoRefresh
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::DoRefresh( TAny* aAny )
    {
    CVtUiAppUi* self =
        reinterpret_cast< CVtUiAppUi* >( aAny );
    TRAP_IGNORE( self->RefreshL() );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DoHandleExitTimeout
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::DoHandleExitTimeout( TAny* /*aAny*/ )
    {
    __VTPRINT( DEBUG_GEN, "VtUi.Exit.Timer.EXPIRED!" )
    VtUiPanic::Panic( EVtUiPanicApplicationShutdownTimeout );

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::IsViewFinderInMainPane
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::IsViewFinderInMainPane() const
    {
    return !( IsViewFinderInContextPane() );
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::IsViewFinderInContextPane
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::IsViewFinderInContextPane() const
    {
    return ( iUplinkWindow == iInstance->iContextControl );
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::SwitchViewFinderToMainPaneL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SwitchViewFinderToMainPaneL( TBool aUpdateState )
    {
    __VTPRINTENTER( "VtUi.SwitchViewFinderToMainPaneL" )
    //change local video in to main pane
    if( IsViewFinderInContextPane() )
        {
        //flag indicates the initial position of uplink window before freeze
        if ( aUpdateState )
            {
            iUiStates->SetViewFindersInitialPlaceContextPane( ETrue );
            }
        HandleCommandL( EVtUiCmdSwapImagesPlaces );
        }
    else
        {
        if ( aUpdateState )
            {
            iUiStates->SetViewFindersInitialPlaceContextPane( EFalse );
            }
        }
    __VTPRINTEXIT( "VtUi.SwitchViewFinderToMainPaneL" )
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::SwitchViewFinderToContextPaneL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SwitchViewFinderToContextPaneL( TBool aUpdateState )
    {
    __VTPRINTENTER( "VtUi.SwitchViewFinderToContextPaneL" )
    //change local video in to context pane
    if( !IsViewFinderInContextPane() )
        {
        //flag indicates the initial position of uplink window before freeze
        if ( aUpdateState )
            {
            iUiStates->SetViewFindersInitialPlaceContextPane( EFalse );
            }
        HandleCommandL( EVtUiCmdSwapImagesPlaces );
        }
    else
        {
        if ( aUpdateState )
            {
            iUiStates->SetViewFindersInitialPlaceContextPane( ETrue );
            }
        }
    __VTPRINTEXIT( "VtUi.SwitchViewFinderToContextPaneL" )
    }

// -----------------------------------------------------------------------------
// VtUiAppUi::RestoreViewFinderL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RestoreViewFinderL()
    {
    __VTPRINTENTER( "VtUi.RestoreViewFinderL" )
    if( IsViewFinderInContextPane() )
        {
        if( !iUiStates->IsViewFindersInitialPlaceContextPane() )
            {
            SwitchViewFinderToMainPaneL( EFalse );
            }
        }
    else
        {
        if( iUiStates->IsViewFindersInitialPlaceContextPane() )
            {
            SwitchViewFinderToContextPaneL( EFalse );
            }
        }
    __VTPRINTEXIT( "VtUi.RestoreViewFinderL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::DialogDismissedL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::DialogDismissedL( TInt )
    {
    __VTPRINTENTER( "VtUi.DialogDismissedL" )
    MVtUiFeature* tb =
        iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar );
    if ( tb )
        {
        if ( !iTbPeriodic )
            {
            iTbPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
            }
        iTbPeriodic->Cancel();
        // try to strat toolbar feature immediately
        iTbPeriodic->Start( 0, KPeriodTime, TCallBack( DoTryToStartTbL, this ) );
        }
     __VTPRINTEXIT( "VtUi.DialogDismissedL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::UpdateContextPaneIconL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::UpdateContextPaneIconL()
    {
    CEikStatusPane* statusPane = StatusPane();

    if ( statusPane )
        {
        if ( statusPane->PaneCapabilities(
            TUid::Uid( EEikStatusPaneUidContext ) ).IsPresent() )
            {
            CAknContextPane* contextPane = NULL;
            TRAPD ( err, contextPane = static_cast<CAknContextPane*> (
                statusPane->ControlL( TUid::Uid( EEikStatusPaneUidContext ) ) ) );
            if ( err != KErrNone || ! contextPane )
                {
                return;
                }

            // Set a new context pane icon
            CFbsBitmap* newBitmap = new(ELeave) CFbsBitmap;
            CleanupStack::PushL( newBitmap );
            User::LeaveIfError( newBitmap->Create( TSize( 1, 1 ), EGray2 ) );

            CFbsBitmap* newMask = new(ELeave) CFbsBitmap;
            CleanupStack::PushL( newMask );
            User::LeaveIfError( newMask->Create( TSize( 1, 1 ), EGray2 ) );

            // create an off-screen device and context
            CFbsBitmapDevice* bitmapDevice = CFbsBitmapDevice::NewL( newMask );
            CleanupStack::PushL( bitmapDevice );
            CFbsBitGc* maskGc = NULL;
            User::LeaveIfError( bitmapDevice->CreateContext( maskGc ) );
            User::LeaveIfNull( maskGc );
            CleanupStack::PushL( maskGc );
            maskGc->SetPenStyle( CGraphicsContext::ENullPen );
            maskGc->SetBrushColor( TRgb::Gray2( 1 ) ); // transparency
            maskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
            maskGc->Clear();
            CleanupStack::PopAndDestroy( 2 ); // maskGc, bitmapDevice

            // newBitmap, new Mask ownership transfer
            contextPane->SetPicture( newBitmap, newMask );
            CleanupStack::Pop( 2 ); // newBitmap, newMask
            }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetIncallBubbleAllowedInUsualL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetIncallBubbleAllowedInUsualL( TBool aAllowed )
    {
    __VTPRINT2( DEBUG_GEN, "Ui.SetIncallBubbleAllowedInUsualL: %d", aAllowed )

    // If call is being disconnected, we do not want to show in-call bubble
    // anymore but dismiss it.
    if( iUiStates->ExecState() == TVtUiStates::EExecStateResetting ||
        iUiStates->ExecState() == TVtUiStates:: EExecStateFinalized )
        {
        __VTPRINT2( DEBUG_GEN, "Ui.SetIncallBubbleAllowedInUsualL forced to false: %d", aAllowed )
        aAllowed = EFalse;
        }

    if ( iIncallBubble )
        {
        iIncallBubble->SetIncallBubbleAllowedInUsualL( aAllowed );
        }
    __VTPRINT( DEBUG_GEN, "Ui.SetIncallBubbleAllowedInUsualL>" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ShowProgressDialogL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::ShowProgressDialogL( TInt aResourceId,
    MProgressDialogCallback* aCallback )
    {
    __VTPRINTENTER( "VtUi.ShowProgressDialogL" )
    if( iProgressDlg )
        {
        User::Leave( KErrNotReady );
        }
    iProgressDlg = new ( ELeave ) CAknProgressDialog(
        reinterpret_cast<  CEikDialog** >( &iProgressDlg ), ETrue );
    iProgressDlg->SetCallback( aCallback );
    iProgressDlg->ExecuteLD( aResourceId );
    __VTPRINTEXIT( "VtUi.ShowProgressDialogL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::HideProgressDialogL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::HideProgressDialogL()
    {
    __VTPRINTENTER( "VtUi.HideProgressDialogL" )
    if( iProgressDlg )
        {
        iProgressDlg->ProcessFinishedL();
        }
    __VTPRINTEXIT( "VtUi.HideProgressDialogL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::AsyncViewFinderToMainPaneAndShare
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::AsyncViewFinderToMainPaneAndShare( TAny* aPtr )
    {
    __VTPRINTENTER( "VtUi.AsyncViewFinderToMainPaneAndShare" )
    CVtUiAppUi* self = reinterpret_cast< CVtUiAppUi* >( aPtr );

    TRAPD( result, { self->SwitchViewFinderToMainPaneL();
                                     self->CmdShareImageL();} );
    __VTPRINTEXITR( "VtUi.AsyncViewFinderToMainPaneAndShare %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::AsyncShare
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::AsyncShare( TAny* aPtr )
    {
    __VTPRINTENTER( "VtUi.AsyncShare" )
    CVtUiAppUi* self = reinterpret_cast< CVtUiAppUi* >( aPtr );
    TRAPD( result, self->CmdShareImageL() );
    __VTPRINTEXITR( "VtUi.AsyncShare %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::AsyncShowErrorAndRestartShare
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::AsyncShowErrorAndRestartShare( TAny* aPtr )
    {
    __VTPRINTENTER( "VtUi.AsyncShowErrorAndRestartShare" )
    CVtUiAppUi* self = reinterpret_cast< CVtUiAppUi* >( aPtr );
    TRAPD( result, { self->ShowUnableToOpenNoteL();
                    self->HandleCommandL( EVtUiCmdShareObjectImage ); } );
    __VTPRINTEXITR( "VtUi.AsyncShowErrorAndRestartShare %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::GetCameraOrientations
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::GetCameraOrientations()
    {
    __VTPRINTENTER( "VtUi.GetCameraOrientations" )
    MVtEngMedia& media = Model().Media();
     media.GetCameraOrientations( iPrimaryCameraOrientation,
          iSecondaryCameraOrientation );
    __VTPRINTEXIT( "VtUi.GetCameraOrientations" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetInitialCameraOrientationL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetInitialCameraOrientationL()
    {
    __VTPRINTENTER( "VtUi.SetInitialCameraOrientationL" )
    MVtEngMedia::TCameraId cameraId;
    MVtEngMedia& media( Model().Media() );
    media.GetCurrentCameraId( cameraId );
    MVtEngMedia::TCameraOrientation targetOrientation(
        cameraId == MVtEngMedia::EPrimaryCamera ?
            iPrimaryCameraOrientation :
            ( cameraId == MVtEngMedia::ESecondaryCamera ?
                iSecondaryCameraOrientation :
                iCurrentCameraOrientation ) );
    if ( iCurrentCameraOrientation != targetOrientation )
        {
        __VTPRINT3( DEBUG_GEN,
            "VtUi.SetInitialCameraOrientationL Old=%d New=%d",
                iCurrentCameraOrientation,
                targetOrientation )
        SetOrientationL( engToAppOrientation[ targetOrientation ] );
        iCurrentCameraOrientation = targetOrientation;
        }
    __VTPRINTEXIT( "VtUi.SetInitialCameraOrientationL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::SetCameraOrientationL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::SetCameraOrientationL()
    {
    __VTPRINTENTER( "VtUi.SetCameraOrientationL" )
    MVtEngMedia::TCameraOrientation newOrientation = iCurrentCameraOrientation;
    MVtEngMedia::TCameraId cameraId;
    MVtEngMedia& media = Model().Media();
    if ( media.GetCurrentCameraId( cameraId ) == KErrNone )
        {
        switch ( cameraId )
            {
            case MVtEngMedia::EPrimaryCamera:
                __VTPRINT( DEBUG_GEN, "VtUi.SetCameraOrient.Primary")
                if( iCurrentCameraOrientation != iPrimaryCameraOrientation )
                    {
                    newOrientation = iPrimaryCameraOrientation;
                    }
                break;

            case MVtEngMedia::ESecondaryCamera:
                __VTPRINT( DEBUG_GEN, "VtUi.SetCameraOrient.Secondary")
                if ( iCurrentCameraOrientation != iSecondaryCameraOrientation )
                    {
                    newOrientation = iSecondaryCameraOrientation;
                    }
                    break;

            default:
                break;
            }
        }

    __VTPRINT2( DEBUG_GEN, "VtUi.SetCameraOrient.Cur=%d",
        iCurrentCameraOrientation )
    __VTPRINT2( DEBUG_GEN, "VtUi.SetCameraOrient.New=%d",
        newOrientation )

    if ( iCurrentCameraOrientation != newOrientation )
            {
            // map camera orientation to appui layout orientation
            TAppUiOrientation newAppUiOrientation;
            if ( newOrientation == MVtEngMedia::EOrientationLandscape )
                {
                __VTPRINT( DEBUG_GEN, "VtUi.SetCameraOrient=LS")
                newAppUiOrientation = EAppUiOrientationLandscape;
                }
            else if ( newOrientation == MVtEngMedia::EOrientationPortrait )
                {
                __VTPRINT( DEBUG_GEN, "VtUi.SetCameraOrient=PR")
                newAppUiOrientation = EAppUiOrientationPortrait;
                }
            else
                {
                __VTPRINT( DEBUG_GEN, "VtUi.SetCameraOrient=OL")
                newAppUiOrientation = EAppUiOrientationUnspecified;
                }
            SetOrientationL( newAppUiOrientation );
            }
    __VTPRINTEXIT( "VtUi.SetCameraOrientationL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshStatesL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshStatesL()
    {
    __VTPRINTENTER( "VtUi.RefreshStatesL" )
    // If transaction (set of commands) is pending refresh in delayed until
    // all of them are processed.
    if ( !iUiStates->IsCommandActivating() )
        {
        iUiStates->Update();
        if ( iUiStates->IsThisApplicationForeground() )
            {
            iCommandManager->RefreshL();
            }
        }
    __VTPRINTEXIT( "VtUi.RefreshStatesL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CmdAdjustVideoL
// -----------------------------------------------------------------------------
//
 void CVtUiAppUi::CmdAdjustVideoL( TInt aCommand )
    {
        __VTPRINTENTER( "VtUi.CmdAdjustVideoL" )
    TInt featureId( -1 );
    switch ( aCommand )
        {
    case EVtUiCmdAdjustVideoVideoQuality:
        featureId = EVtUiFeatureIdVideoQuality;
        break;
    case EVtUiCmdAdjustVideoWhiteBalance:
        featureId = EVtUiFeatureIdWhiteBalance;
        break;
    case EVtUiCmdAdjustVideoBrightness:
        featureId = EVtUiFeatureIdBrightness;
        break;
    case EVtUiCmdAdjustVideoContrast:
        featureId = EVtUiFeatureIdContrast;
        break;
    case EVtUiCmdAdjustVideoColourTone:
        featureId = EVtUiFeatureIdColourTone;
        break;
    default:
        break;
        }
   MVtUiFeature* vb = iFeatureManager->GetFeatureById( featureId );
   if ( vb )
      {
      __VTPRINT( DEBUG_GEN, "VtUi.CmdAdjustVideoL.StartL" );
      vb->StartL();
      }
    __VTPRINTEXIT( "VtUi.CmdAdjustVideoL" )
   }

// -----------------------------------------------------------------------------
// CVtUiAppUi::AppUiInitDoneDoPostInitL
// -----------------------------------------------------------------------------
//
 void CVtUiAppUi::AppUiInitDoneDoPostInitL()
    {
    MVtUiFeature* tb = iFeatureManager->GetFeatureById( EVtUiFeatureIdToolbar );
    if ( tb )
        {
        if ( !iTbPeriodic )
            {
            iTbPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
            }
        iTbPeriodic->Cancel();
        // try to strat toolbar feature immediately
        iTbPeriodic->Start( 0, KPeriodTime, TCallBack( DoTryToStartTbL, this ) );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::ProcessWsEventIfZoomModeIsActiveL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::ProcessWsEventIfZoomModeIsActiveL( const TWsEvent& aEvent )
    {
    __VTPRINTENTER( "VtUi.ProWsEvtIfZoomActivedL" )
    const TInt type = aEvent.Type();
    switch( type )
        {
        case EEventKey:
        case EEventKeyUp:
        case EEventKeyDown:
            {
            const TKeyEvent* keyEvent = aEvent.Key();


            // Up and down arrow key events does the zooming,
            // and should be forwarded to appui's key event handler.
            // Also ETrue must be returned, so that other controls
            // would not get these key events.
            TEventCode eventCode = (TEventCode)aEvent.Type();
            if ( keyEvent->iScanCode == EStdKeyUpArrow ||
                keyEvent->iScanCode == EStdKeyDownArrow ||
                keyEvent->iCode == EKeyZoomIn ||
                keyEvent->iCode == EKeyZoomOut )
                {
                HandleKeyEventL( *keyEvent, eventCode );
                __VTPRINTEXIT( "VtUi.ProWsEvtIfZoomActivedL" )
                return ETrue;
                }
            __VTPRINT( DEBUG_GEN, "VtUi.HandleWsEventL zoom mode set" );
            // If user selects zoom mode from options menu EEventKeyUp
            // will be generated after that. Therefore this event must be
            // ignored. Also EEventKeyDown are ignored. This means that
            // only EEventKey events can dismiss the zoom mode.
            if ( type != EEventKeyUp && type != EEventKeyDown )
                {
                 // If zoom mode is on only zoom mode button is available in
                 // toolbar. Pressing the zoom mode button in toolbar
                 // should not dismiss the zoom mode, that is why this events
                 // are ignored. If toolbar is not available and
                 // also EKeyDevice3 (selection key) event should dismiss
                 // the zoom mode.
                 if ( keyEvent->iCode != EKeyDevice3 ||
                     ( keyEvent->iCode == EKeyDevice3 &&
                     !iUiStates->IsToolbarAvailable() ) )
                    {
                    __VTPRINT( DEBUG_GEN, "VtUi.ProWsEvtIfZoomActivedL.EKeyDevice3" );
                    SetZoomModeL( EFalse );
                    }
                }
            }
            break;

        case EEventPointer:
            __VTPRINT( DEBUG_GEN, "VtUi.ProWsEvtIfZoomActivedL.EEventPointer" );
            break;

        case KAknHardwareLayoutSwitch:
            // Window server event used when layout changes
            __VTPRINT( DEBUG_GEN, "VtUi.ProcessWsEventIfZoomModeIsActiveL.LayoutSwitch" );
            break;

        case EEventScreenDeviceChanged:
            // The screen size mode has changed, for instance when  the cover on a phone 
            // that supports screen flipping is opened or closed. 
            __VTPRINT( DEBUG_GEN, "VtUi.ProcessWsEventIfZoomModeIsActiveL.ScreenChanged" );
            break;

        case EVtUiWsEventNumberSourceDeactivate:
            // Number source deactivated
            __VTPRINT( DEBUG_GEN, "VtUi.ProWsEvtIfZoomActivedL.NumberDeactivate" );
            break;

        default:
            __VTPRINT( DEBUG_GEN, "VtUi.ProWsEvtIfZoomActivedL.default" );
            // EVtUiWsEventNumberSourceActivate could be generated through number buttons
            // and execution runs to default statement
            SetZoomModeL( EFalse );
            break;
            }
    __VTPRINTEXIT( "VtUi.ProWsEvtIfZoomActivedL2" )
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::StopSliders()
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::StopSliders()
    {
    __VTPRINTENTER( "VtUi.StopSliders" )
    if( iUiStates->IsBrightnessModeOn() )
        {
        // if brightness feature is active, stop that
        MVtUiFeature* br = iFeatureManager->GetFeatureById( EVtUiFeatureIdBrightness );
        if ( br )
            {
            if ( br->State() ==  MVtUiFeature::EActive )
                {
                __VTPRINT( DEBUG_GEN, "VtUi.StopSliders br->STOP" )
                br->Stop();
                }
            }
        }
    // if contrast feature is active, stop that
    if( iUiStates->IsContrastModeOn() )
        {
        // if contrast feature is active, stop that
        MVtUiFeature* cr = iFeatureManager->GetFeatureById( EVtUiFeatureIdContrast );
        if ( cr )
            {
            if ( cr->State() ==  MVtUiFeature::EActive )
                {
                __VTPRINT( DEBUG_GEN, "VtUi.StopSliders cr->STOP" )
                cr->Stop();
                }
            }
        }
    // if volume feature is active, stop that
    if( iUiStates->IsVolumeModeOn() )
        {
        // if volume feature is active, stop that
        MVtUiFeature* vl = iFeatureManager->GetFeatureById( EVtUiFeatureIdVolume );
        if ( vl )
            {
            if ( vl->State() ==  MVtUiFeature::EActive )
                {
                __VTPRINT( DEBUG_GEN, "VtUi.StopSliders vl->STOP" )
                vl->Stop();
                }
            }
        }
    // if zoom feature is active, stop that
    if( iUiStates->IsZoomModeOn() )
        {
        // if zoom feature is active, stop that
        MVtUiFeature* zm = iFeatureManager->GetFeatureById( EVtUiFeatureIdZoom );
        if ( zm )
            {
            if ( zm->State() ==  MVtUiFeature::EActive )
                {
                __VTPRINT( DEBUG_GEN, "VtUi.StopSliders zm->STOP" )
                zm->Stop();
                }
            }
        }   
    __VTPRINTEXIT( "VtUi.StopSliders" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CanSwapImagePlaces()
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::CanSwapImagePlaces()
    {
    __VTPRINTENTER( "VtUi.CanSwapImagePlaces" )
    TTime now; 
    now.HomeTime();
    // User can swap image places if the frequency is lower than maximum frequency. 
    if ( now.MicroSecondsFrom( iLastSwapTime ).Int64() >= KVtUiMaxSwapImagesFreq ) 
        {
        __VTPRINT( DEBUG_GEN, "VtUi.Swap can swap image" )
        iLastSwapTime = now;
        __VTPRINTEXIT( "VtUi.CanSwapImagePlaces" )
        return ETrue;
        }
    else
        {
        __VTPRINT( DEBUG_GEN, "VtUi.Swap can not swap image" )
        __VTPRINTEXIT( "VtUi.CanSwapImagePlaces" )
        return EFalse;
        }
    }

// Implementation of CVtUiAppUi::CInstance

// -----------------------------------------------------------------------------
// CVtUiAppUi::CInstance::CInstance
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CInstance::CInstance( CVtUiAppUi& aAppUi )
    : iAppUi( aAppUi )
    {
    }

void CVtUiAppUi::CInstance::CreateRemoteVideoControl()
    {    
    iRemoteVideoControl = CVtUiRemoteVideoControl::NewL( iAppUi );
    iRemoteVideoControl->MakeVisible(EFalse);
    iMainControl->SetRemoteVideoControl( iRemoteVideoControl );
    iMainControl->LayoutRemoteVideo();
    
    iAppUi.AddToStackL( iRemoteVideoControl );
    
    iRemoteVideoControlInStack = ETrue;
    
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CInstance::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CInstance::ConstructL()
    {
    iBitmapManager = new ( ELeave ) CVtUiBitmapManager;

    TRect parent;
    TAknWindowLineLayout control;

    VtUiLayout::GetApplicationParentRect( parent );
    iMainControl = CVtUiMainControl::NewL( *iBitmapManager,
            iAppUi,
            *iAppUi.iUiStates  );

    VtUiLayout::GetMainPaneLayout( control );
    AknLayoutUtils::LayoutControl( iMainControl, parent, control );

    iAppUi.AddToStackL( iMainControl );
    iMainControlInStack = ETrue;

    TAknLayoutRect layout;
    layout.LayoutRect( parent, control );
    iNumberEntryActivation =
        new ( ELeave ) CVtUiNumberEntryActivationControl( iAppUi );
    iNumberEntryActivation->ConstructL( layout.Rect() );

    iContextControl = CVtUiContextControl::NewL(
            *iBitmapManager,
            iAppUi,
            *iAppUi.iUiStates );

    VtUiLayout::GetFirstWindowBackgroundLayout(
        control );
    AknLayoutUtils::LayoutControl( iContextControl, parent, control );
    iAppUi.AddToStackL( iContextControl );
    iContextControlInStack = ETrue;

    iEndCallButtonPane = CVtUiEndCallButtonPane::NewL( parent );
        
    VtUiLayout::GetButtonPaneLayout( control );
    
    AknLayoutUtils::LayoutControl( iEndCallButtonPane, parent, control );
    iAppUi.AddToStackL( iEndCallButtonPane );
    iButtonPaneInStack = ETrue;
    
    iNaviPane =
        CVtUiNaviPane::NewL(
            *( iAppUi.NaviPaneL() ),
            iAppUi );

    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CInstance::LayoutChanged
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CInstance::LayoutChanged()
    {
    // Layout controls.
    TRect parent;
    TAknWindowLineLayout control;
    VtUiLayout::GetApplicationParentRect( parent );
    VtUiLayout::GetMainPaneLayout( control );
    AknLayoutUtils::LayoutControl( iMainControl, parent, control );
    if(iMainControl)
        iMainControl->LayoutRemoteVideo();
    AknLayoutUtils::LayoutControl( iNumberEntryActivation, parent, control );
    VtUiLayout::GetFirstWindowBackgroundLayout( control );
    AknLayoutUtils::LayoutControl( iContextControl, parent, control );
    
    VtUiLayout::GetButtonPaneLayout( control );
    AknLayoutUtils::LayoutControl( iEndCallButtonPane, parent, control );
    
    if(iContextControl)
        iContextControl->LayoutRemoteVideo();
    
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CInstance::VolumeKeyPressedL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CInstance::VolumeKeyPressedL()
    {
    __VTPRINTENTER( "CVtUiAppUi.VolumeKeyPressedL" )
    // if the application is in foreground show volume sliders
    if ( iAppUi.IsForeground() )
        {
        // If application is shutting down, no need to show volume popup
        if ( iAppUi.iState == NULL ||
             iAppUi.iState ==
                TVtUiStateResetting::InstanceL( iAppUi, *iAppUi.iUiStates ) )
            {
            return;
            }

        CVtUiVolume* volume = static_cast< CVtUiVolume* >(
            iAppUi.iFeatureManager->GetFeatureById( EVtUiFeatureIdVolume ) );
        if ( volume )
            {
            // If the capture mode is on we should
            // end the capture mode
            if( iAppUi.iUiStates->IsCaptureModeOn() )
                {
                iAppUi.CmdCancelCaptureL();
                }
            volume->StartL();
            }
        }
    __VTPRINTEXIT( "CVtUiAppUi.VolumeKeyPressedL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CInstance::NewL
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CInstance* CVtUiAppUi::CInstance::NewL( CVtUiAppUi& aAppUi )
    {
    CInstance* self = new ( ELeave ) CInstance( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );

    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CInstance::~CInstance
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CInstance::~CInstance()
    {
    if ( iMainControl && iMainControlInStack )
        {
        iAppUi.RemoveFromStack( iMainControl );
        }
    if ( iContextControl && iContextControlInStack )
        {
        iAppUi.RemoveFromStack( iContextControl );
        }
    if(iRemoteVideoControl &&iRemoteVideoControlInStack)
        {
        iAppUi.RemoveFromStack( iRemoteVideoControl );
        }
    if( iEndCallButtonPane && iButtonPaneInStack )
        {
        iAppUi.RemoveFromStack( iEndCallButtonPane );
        }
    delete iMainControl;
    delete iContextControl;
    delete iRemoteVideoControl;
    delete iNumberEntryActivation;
    delete iNaviPane;
    delete iBitmapManager;
    delete iEndCallButtonPane;
    }

// Implementation of CVtUiAppUi::CEventObserver

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::CEventObserver
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CEventObserver::CEventObserver( CVtUiAppUi& aAppUi )
    : iAppUi( aAppUi ),
      iCommandObservers( KVtUiCommandObserverArrayGranularity )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::ConstructL()
    {
    iModel = CVtEngModel::NewL( *this, *this );

    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::NewL
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CEventObserver* CVtUiAppUi::CEventObserver::NewL(
        CVtUiAppUi& aAppUi )
    {
    CEventObserver* self = new ( ELeave ) CEventObserver( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::~CEventObserver
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CEventObserver::~CEventObserver()
    {
    iCommandObservers.Close();

    delete iModel;
    delete iBeat;

    delete iRemConInterfaceSelector;
    iRemConCoreApiTarget = NULL; // not owned.
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::Model
// -----------------------------------------------------------------------------
//
inline CVtEngModel& CVtUiAppUi::CEventObserver::Model()
    {
    return *iModel;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::CreateRemConSessionL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::CreateRemConSessionL()
    {
    __VTPRINTENTER( "VtUiComms.CreateRemCon" )
    // If one of the iRemCon* pointers equals to NULL, then all of them are
    // NULL.
    if ( !iRemConInterfaceSelector )
        {
        CRemConInterfaceSelector* interfaceSelector =
            CRemConInterfaceSelector::NewL();
        CleanupStack::PushL( interfaceSelector );

        CRemConCoreApiTarget* coreApiTarget =
            CRemConCoreApiTarget::NewL( *interfaceSelector, *this );
        // The coreApiTarget instance is owned by interfaceSelector instance.
        // This instance must implement MRemConCoreApiTargetObserver interface.
        CleanupStack::PushL( coreApiTarget );
        interfaceSelector->OpenTargetL();

        iRemConVolumeRepeatTimer = CPeriodic::NewL( CActive::EPriorityHigh );

        CleanupStack::Pop( coreApiTarget );
        CleanupStack::Pop( interfaceSelector );

        iRemConInterfaceSelector = interfaceSelector;
        iRemConCoreApiTarget = coreApiTarget;
        }
    __VTPRINTEXIT( "VtUiComms.CreateRemCon" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::DeleteRemConSession
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::DeleteRemConSession()
    {
    delete iRemConVolumeRepeatTimer;
    iRemConVolumeRepeatTimer = NULL;

    delete iRemConInterfaceSelector;
    iRemConInterfaceSelector = NULL;

    iRemConCoreApiTarget = NULL; // not owned.
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::CommandSupported
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::CEventObserver::CommandSupported(
        const TInt aCommandId ) const
    {
    const TInt caps = iModel->CommandHandler().GetCommandCaps( aCommandId );
    return
        ( caps >= KErrNone ) &&
        ( caps & MVtEngCommandHandler::EAttribSupported );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::CommandSupportedAndSynchronous
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::CEventObserver::CommandSupportedAndSynchronous(
        const TInt aCommandId ) const
    {
    const TInt caps = iModel->CommandHandler().GetCommandCaps( aCommandId );
    return
        ( caps >= KErrNone ) &&
        ( caps & MVtEngCommandHandler::EAttribSupported ) &&
        ( ~caps & MVtEngCommandHandler::EAttribAsync );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::AddObserverL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::AddObserverL(
        MVtEngCommandObserver& aObserver )
    {
    User::LeaveIfError(
        iCommandObservers.Append( &aObserver ) );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::RemoveObserver
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::RemoveObserver(
        MVtEngCommandObserver& aObserver )
    {
    const TInt pos = iCommandObservers.Find( &aObserver );
    if ( pos != KErrNotFound )
        {
        if ( !iInCommandPerformed )
            {
            iCommandObservers.Remove( pos );
            }
        else
            {
            iCommandObservers[ pos ] = NULL;
            }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::StartBeatL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::StartBeatL()
    {
    if ( !iBeat )
        {
        iBeat = CHeartbeat::NewL( CActive::EPriorityStandard );
        }

    if ( !iBeat->IsActive() )
        {
        iBeat->Start( ETwelveOClock, this );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::StopBeat
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::StopBeat()
    {
    delete iBeat;
    iBeat = NULL;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::StopVolumeRepeatTimer
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::StopVolumeRepeatTimer()
    {
    iRemConVolumeRepeatTimer->Cancel();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::HandleVtEventL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::HandleVtEventL(
        TInt aEvent )
    {
    __VTPRINTENTER( "VtUiComms.HandleVtEventL" )
    __VTPRINT2( DEBUG_GEN, "VtUi.HandleEvt=%d", aEvent )

    /** Allow application state to handle event first. It may also deny further
      * handling by indicating the event was handled */
    if ( iAppUi.iState &&
        iAppUi.iState->HandleVtEventL( aEvent )
            == TVtUiAppStateBase::EEventHandled )
        {
        __VTPRINTEXITR( "VtUiComms.HandleVtEventL %d", 0 )
        return;
        }

    TInt callBits = EVtUiRefreshStates;

    // New camera orientation
    switch( aEvent )
        {
        case KVtEngSourceChanged:
            callBits |= EVtUiSetOrientation;
            break;
        default:
            break;
        }
        
    switch( aEvent )
        {
        case KVtEngSourceChanged:
            callBits |= EVtUiStopWBOrColortone;
            break;
        default:
            break;
        }
    
    switch( aEvent )
        {
        case KVtEngSessionWaitingCallActive:
        case KVtEngSessionWaitingCallInactive:
            iAppUi.HandleWaitingStateChange(
                aEvent == KVtEngSessionWaitingCallActive );
            break;
        default:
            break;
        }
    switch( aEvent )
        {
        case KVtEngShareImageInitializeBegin:
            callBits |= EVtUiShowImageInitializingProgress;
            break;

        case KVtEngShareImageInitializeEnd:
            callBits |= EVtUiHideImageInitializingProgress;
            break;

        case KVtEngShareImageDecodingError:
            callBits |= EVtUiShowDecodingError;
            break;

        default:
            break;
        }

    // Handle rendering problems.
    switch ( aEvent )
        {
        case KVtEngRemoteRenderingProblem:
            callBits |= EVtUiHandleVideoFrameRemoteProblem;
            break;

        case KVtEngViewFinderStopped:
        case KVtEngLocalRenderingProblem:
            callBits |= EVtUiHandleVideoFrameLocalProblem;
            break;

        default:
            break;
        }

    // Refresh navipane.
    switch ( aEvent )
        {
        case KVtEngSourceChanged:
        case KVtEngCameraChanged:
        case KVtEngSessionStateChanged:
        case KVtEngDurationSettingChanged:
        case KVtEngAudioOutputVolumeChanged:
        case KVtEngAudioRoutingChanged:
        case KVtEngAudioMuted:
        case KVtEngAudioUnmuted:
            callBits |= EVtUiRefreshNaviPane;
            break;

        default:
            break;
        }

    // Refresh softkeys.
    switch ( aEvent )
        {
        case KVtEngSourceChanged:
        case KVtEngSourceCapsChanged:
        case KVtEngSessionAnswerPossible:
        case KVtEngSessionStateChanged:
        case KVtEngAudioRoutingChanged:
        case KVtEngAudioRoutingAvailabilityChanged:
        case KVtEngAudioMuted:
        case KVtEngAudioUnmuted:
        case KVtEngLCHProviderSwitchDone:
            callBits |= EVtUiRefreshSoftkeys;
            break;

        default:
            break;
        }

    // Refresh blind status
    switch ( aEvent )
        {
        case KVtEngSourceChanged:
        case KVtEngRemoteVideoPaused:
        case KVtEngRemoteVideoResumed:
        case KVtEngRemoteVideoStarted:
        case KVtEngRemoteVideoStopped:
        case KVtEngLCHProviderSwitchDone:
            callBits |= EVtUiRefreshBlind;
            break;

        default:
            break;
        }

    // Check if it's required to stop "waiting image" display.
    switch ( aEvent )
        {
        case KVtEngRemoteVideoResumed:
        case KVtEngRemoteVideoStarted:
            callBits |= EVtUiStopWaitingImage;
            break;

        default:
            break;
        }

    // Check if it is needed to set a new layout for remote renderer.
    switch ( aEvent )
        {
        case KVtEngResolutionToQCIF:
            callBits |= EVtUiChangeRemoteVideoLayout;
            iAppUi.RemoteVideoIsSQCif( EFalse );
            break;
        case KVtEngResolutionToSQCIF:
            callBits |= EVtUiChangeRemoteVideoLayout;
            iAppUi.RemoteVideoIsSQCif( ETrue );
            break;
        default:
            break;
        }

    switch ( aEvent )
        {
        case KVtEngAudioRoutingChanged:
        case KVtEngAudioRoutingAvailabilityChanged:
        case KVtEngMediaOutgoingVideoChannelStatusChanged:
        case KVtEngMediaOutgoingAudioChannelStatusChanged:
             callBits |= EVtUiMediaStateChanged;
            break;

        case KVtEngAudioVolumeMin:
            iAppUi.KeySounds()->PlaySound( EAvkonSIDVolumeMinTone );
            break;

       case KVtEngAudioVolumeMax:
            iAppUi.KeySounds()->PlaySound( EAvkonSIDVolumeMaxTone );
            break;

        default:
            break;
        }
    
    // Refresh Menu.
    switch ( aEvent )
        {
        case KVtEngSourceChanged:
            callBits |= EVtUiRefreshMenu;
            callBits |= EVtUiStopBrightnessOrContrast;
            callBits |= EVtUiRefreshZoomPopup;
            break;
        default:
            break;
        }

    TRAP_IGNORE ( DoExecuteL( callBits ) );
    __VTPRINTEXITR( "VtUiComms.HandleVtEventL %d", 1 )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::HandleVTCommandPerformedL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::HandleVTCommandPerformedL(
        TVtEngCommandId aCommand,
        const TInt aError )
    {
    __VTPRINTENTER( "VtUiComms.HandleVTCommandPerformedL" )
    __VTPRINT2( DEBUG_GEN, "VtUiComms.HandleVTCommandPerformedL aCommand = %d",
            aCommand )
    
    if ( iAppUi.iState &&
         iAppUi.iState->HandleVTCommandPerformedL( aCommand, aError ) ==
         TVtUiAppStateBase::EEventHandled )
        {
        // state didn't allow further processing of command completion
        __VTPRINTEXITR( "VtUiComms.HandleVTCommandPerformedL %d", 0 )
        return;
        }
    iAppUi.RefreshStatesL();

    if ( aCommand == KVtEngMuteOutgoingAudio ||
         aCommand == KVtEngUnmuteOutgoingAudio )
         {
         iAppUi.RefreshL();
         }

    const TInt count = iCommandObservers.Count();
    TInt nullPosition = KErrNotFound;

    iInCommandPerformed = ETrue;

    // iInCommandPerformed equals ETrue while inside the following loop;
    // Exceptions must not be raised.
    for ( TInt index = 0; index < count; index++ )
        {
        MVtEngCommandObserver* obs = iCommandObservers[ index ];
        if ( obs )
            {
            TRAP_IGNORE( obs->HandleVTCommandPerformedL( aCommand, aError ) );
            }
        else
            {
            // We store only one position; eventually all NULL elements of the
            // array will be removed.
            nullPosition = index;
            }
        }
    iInCommandPerformed = EFalse;

    if ( nullPosition != KErrNotFound )
        {
        iCommandObservers.Remove( nullPosition );
        }

    // Specific handling of some commands:
    if ( aCommand == KVtEngResetEngine ) // Engine has been reset
        {
        __ASSERT_ALWAYS( !aError, VtUiPanic::Panic( EVtUiPanicResetFailed ) );
        iAppUi.HandleEngineResetL();
        }
    else if ( ( aCommand == KVtEngInitializeShareImage ) ||
              ( aCommand == KVtEngStartShareImage ) )
        {
        __VTPRINT3( DEBUG_GEN,
            "VtUi.HandleVTCommandPerformedL cmd=%d err=%d", aCommand, aError );
        if( aError != KErrNone )
            {
            // stop toolbar feature to prevent drawing over error dialog
           MVtUiFeature* tb = iAppUi.iFeatureManager->
           GetFeatureById( EVtUiFeatureIdToolbar );
            if ( tb )
                {
                tb->Stop();
                }
            iAppUi.iAsyncCallback->Set(
                TCallBack( &AsyncShowErrorAndRestartShare, &iAppUi ) );
            iAppUi.iAsyncCallback->CallBack();
            }
        else if( aCommand == KVtEngInitializeShareImage )
            {
            if ( iAppUi.iUiStates->IsViewFinderToMainPane()  )
                {
                iAppUi.iAsyncCallback->Set(
                    TCallBack( &AsyncViewFinderToMainPaneAndShare, &iAppUi ) );
                }
            else
                {
                iAppUi.iAsyncCallback->Set(
                    TCallBack( &AsyncShare, &iAppUi ) );
                }
            iAppUi.iAsyncCallback->CallBack();
            }
        }
    else if ( iAppUi.iUiStates->IsLayoutChangeNeeded() && 
            ( aCommand  == KVtEngSetSource ||
            aCommand  == KVtEngPrepareCamera ||
            aCommand  == KVtEngUnfreeze ||
            aCommand  == KVtEngHandleLayoutChange ) ||
            ( ( aCommand  == KVtEngMuteOutgoingAudio || 
              aCommand  == KVtEngUnmuteOutgoingAudio ||
              aCommand  == KVtEngSetAudioRouting ||
              aCommand  == KVtEngSetAudioVolume ) && 
              ( aCommand == iAppUi.iPendingCmd ) ) )
        {
        iAppUi.iPendingCmd = KVtEngCommandNone;
        iAppUi.iUiStates->SetLayoutChangeNeeded( EFalse );
        iAppUi.DoHandleLayoutChangedL();
        }
    __VTPRINTEXITR( "VtUiComms.HandleVTCommandPerformedL %d", 1 )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::vtHandleFrameL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::vtHandleFrameL(
        TFrameType aType,
        CFbsBitmap* aBitmap )
    {
    static TUint32 lastTick = 0;
    static TBool flag = EFalse;
            
        
    CEikMenuBar* menuBar = (STATIC_CAST(CEikonEnv*, this->iAppUi.iCoeEnv))->AppUiFactory()->MenuBar();
    if ( menuBar && menuBar->IsDisplayed() )
         {
         if ( !flag )
            {
            flag = ETrue;
            lastTick = User::NTickCount();
            }
         else
            {
            TUint32 newTick = User::NTickCount();

            //don't consider time wrap
            //one frame per 200ms
            if ( newTick - lastTick < 400 )
                {
                __VTPRINTEXITR( "CVtUiAppUi::CEventObserver::vtSetFrame %d", 0 )
                return;
                }
            else
                {
                lastTick = newTick;
                }
            }
         }
    else
        {
        flag = EFalse;
        }
        
    TBool local = EFalse;
    switch ( aType )
        {
        case ELocalVideoFrame:
            local = ETrue;
            break;

        case ERemoteVideoFrame:
        default:
            break;
        }

    iAppUi.HandleVideoFrameL( local, aBitmap );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::vtSetFrame
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::vtSetFrame(
        TFrameType aType,
        CFbsBitmap* aBitmap )
    {
    TBool local = EFalse;
    switch ( aType )
        {
        case ELocalVideoFrame:
            local = ETrue;
            break;

        case ERemoteVideoFrame:
        default:
            break;
        }

    iAppUi.SetVideoFrame( local, aBitmap );
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::Beat
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::Beat()
    {
    iAppUi.HandleBeat();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::Synchronize
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::Synchronize()
    {
    iAppUi.HandleBeat();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::DoExecuteL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::DoExecuteL( TInt aBits )
    {
    __VTPRINT2( DEBUG_GEN, "VtUi.DoExec.bits=%d", aBits )

    // Array of methods - leaving methods are allowed.
    const TMethodL methodArray[] =
        {
        &CVtUiAppUi::RefreshStatesL,
        &CVtUiAppUi::HandleVideoFrameRemoteProblemL,
        &CVtUiAppUi::HandleVideoFrameLocalProblemL,
        &CVtUiAppUi::RefreshNaviPaneL,
        &CVtUiAppUi::RefreshSoftkeysL,
        &CVtUiAppUi::RefreshBlind,
        &CVtUiAppUi::StopWaitingImage,
        &CVtUiAppUi::ChangeRemoteVideoLayoutL,
        &CVtUiAppUi::ShowImageInitializeProgressL,
        &CVtUiAppUi::HideImageInitializeProgressL,
        &CVtUiAppUi::SetCameraOrientationL,
        &CVtUiAppUi::MediaStateChangedL,
        &CVtUiAppUi::ShowImageDecodingErrorNoteL,
        &CVtUiAppUi::StopWhiteBalanceOrColortone,
        &CVtUiAppUi::RefreshMenuL,
        &CVtUiAppUi::StopBrightnessOrContrast,
        &CVtUiAppUi::RefreshZoomPopupL
        };
    const TInt count = ( sizeof( methodArray ) / sizeof ( TMethodL ) );

    // Execute selected methods.
    while ( aBits )
        {
        for ( TInt index = 0; ( index < count ) && aBits; index++ )
            {
            const TInt mask = ( 1 << index );
            if ( aBits & mask )
                {
                // Bit is set if corresponding method
                // is wanted to be executed.

                aBits &= ~mask;
                TMethodL method = methodArray[ index ];
                ( iAppUi.*method )(); // may leave
                }
            }
        aBits = 0; // for loop executed successfully.
        }
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::HandleVolumeChange
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::HandleVolumeChange(
        TRemConCoreApiButtonAction aButtonAct )
    {
   __VTPRINTENTER( "VtUi.HandleVolumeChange" )
    // Order of the events is as follows:
    //      Click - Immediately when key is pressed down
    //      Press - After 0.6 seconds
    //      Release - When key is released after 0.6 seconds
    //
    // Thus, the following sequences are possible from single keypress:
    //      <Click>
    //      <Click> <0.6 sec pause> <Press> <indefinite pause> <Release>

    switch ( aButtonAct )
        {
        case ERemConCoreApiButtonPress:
            __VTPRINT( DEBUG_GEN, "VtUi.HandleVolumeChange.ButtonPress" )
            TRAP_IGNORE( iAppUi.AdjustVolumeL( iRCCAOperationId ) );
            TRAP_IGNORE( iAppUi.RefreshVolumeL() );
            TRAP_IGNORE( iAppUi.iInstance->VolumeKeyPressedL() );
             
            iRemConVolumeRepeatTimer->Start(
                KVtUiVolumeRepeatLongDelay,
                KVtUiVolumeRepeatDelay,
                TCallBack( DoHandleVolumeRepeat, this ) );
          
            break;

        case ERemConCoreApiButtonRelease:
            __VTPRINT( DEBUG_GEN, "VtUi.HandleVolumeChange.ButtonRelease" )
            iRCCAOperationId = ENop;
            TRAP_IGNORE( iAppUi.iInstance->VolumeKeyPressedL() );
            break;

        case ERemConCoreApiButtonClick:
            __VTPRINT( DEBUG_GEN, "VtUi.HandleVolumeChange.ButtonClick" )
             TRAP_IGNORE( iAppUi.AdjustVolumeL( iRCCAOperationId ) );
             TRAP_IGNORE( iAppUi.RefreshVolumeL() );
             TRAP_IGNORE( iAppUi.iInstance->VolumeKeyPressedL() );
            break;

        default:
            break;
        }
    __VTPRINTEXIT( "VtUi.HandleVolumeChange" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::HandleRemMuteChange
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::HandleRemMuteChange(
        TRemConCoreApiButtonAction aButtonAct )
    {
    __VTPRINTENTER( "VtUi.EventObserver.HandleRemMuteChange" )
    TBool AudioEn (EFalse );
    AudioEn = iAppUi.iUiStates->AudioState().IsAudio();
    if( AudioEn )
        iAppUi.HandleCommandL( EVtUiCmdDisableAudio );
    else
        iAppUi.HandleCommandL( EVtUiCmdEnableAudio );
    __VTPRINTEXIT( "VtUi.EventObserver.HandleRemMuteChange" )
    }
// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::DoHandleVolumeRepeat
// -----------------------------------------------------------------------------
//
TInt CVtUiAppUi::CEventObserver::DoHandleVolumeRepeat( TAny* aAny )
    {
    __VTPRINTENTER( "VtUi.SvkRpt" )
    CEventObserver* self = reinterpret_cast< CEventObserver* >( aAny );
    TRAP_IGNORE( self->iAppUi.AdjustVolumeL( self->iRCCAOperationId ) );
    TRAP_IGNORE( self->iAppUi.RefreshVolumeL() );
    __VTPRINTEXIT( "VtUi.SvkRpt" )
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::RefreshVolumeL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::RefreshVolumeL()
    {
    __VTPRINTENTER( "VtUi.RefreshVolumeL" )
    // Refresh volume
    CVtUiVolume* volume = static_cast< CVtUiVolume* >(
        iFeatureManager->GetFeatureById( EVtUiFeatureIdVolume ) );
    if ( volume )
        {
        volume->RefreshL();
        }
    __VTPRINTEXIT( "VtUi.RefreshVolumeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::AdjustVolumeL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::AdjustVolumeL( TRemConCoreApiOperationId aOperationId )
    {
    __VTPRINTENTER( "VtUi.AdjustVolumeL" )
    __VTPRINT2( DEBUG_GEN,
        "VtUi.AdjustVolumeL aOperationId = %d", aOperationId )
    TInt command( KVtEngCommandNone );
    switch ( aOperationId )
        {
    case ERemConCoreApiVolumeDown:
        command = KVtEngDecreaseAudioVolume;
        break;

    case ERemConCoreApiVolumeUp:
        command = KVtEngIncreaseAudioVolume;
        break;

    default:
        break;
        }

    if ( command != KVtEngCommandNone )
        {
        ExecuteCmdL( command );
        }
    __VTPRINTEXIT( "VtUi.AdjustVolumeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CEventObserver::MrccatoCommand
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CEventObserver::MrccatoCommand(
        TRemConCoreApiOperationId aOperationId,
        TRemConCoreApiButtonAction aButtonAct )
    {
     __VTPRINTENTER( "VtUi.MrccatoCommand" )
    // Side volume keys will also dismiss zoom mode if zoom mode is active
    if ( iAppUi.iUiStates->IsZoomModeOn() )
        {
        __VTPRINT( DEBUG_GEN, "VtUi.MrccatoCommand1" )
        TRAP_IGNORE( iAppUi.SetZoomModeL( EFalse ));
        }

    iRemConVolumeRepeatTimer->Cancel();
    iRCCAOperationId = aOperationId;
    switch ( aOperationId )
        {
        case ERemConCoreApiVolumeUp:
            // if volume in maximum value and volume up is pressed
            // volume indicator must still be shown for a while if
            //  muted or call duration is shown in navipane
            __VTPRINT( DEBUG_GEN, "VtUi.MrccatoCommand ERemConCoreApiVolumeUp" )
            HandleVolumeChange( aButtonAct );
            break;

        case ERemConCoreApiVolumeDown:
            // if volume in minimun value and volume down is pressed
            // volume indicator must still be shown for a while if
            //  muted or call duration is shown in navipane
            __VTPRINT( DEBUG_GEN, "VtUi.MrccatoCommand ERemConCoreApiVolumeDown" )
            HandleVolumeChange( aButtonAct );
            break;
        case ERemConCoreApiMute:
            __VTPRINT( DEBUG_GEN, "VtUi.MrccatoCommand ERemConCoreApiMute" )
            HandleRemMuteChange( aButtonAct );
        default:
            // Other commands ignored.
            break;
        }
 __VTPRINTEXIT( "VtUi.MrccatoCommand" )
    }

// Implementation of CVtUiAppUi::CVtUiAppUiMGVerifier

// -----------------------------------------------------------------------------
// CVtUiAppUi::CVtUiAppUiMGVerifier::NewLC
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CVtUiAppUiMGVerifier* CVtUiAppUi::CVtUiAppUiMGVerifier::NewLC(
    CVtUiAppUi& aAppUi, CCoeEnv& aCoeEnv )
    {
    CVtUiAppUiMGVerifier* self = new ( ELeave )
        CVtUiAppUiMGVerifier( aAppUi, aCoeEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CVtUiAppUiMGVerifier::~CVtUiAppUiMGVerifier
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CVtUiAppUiMGVerifier::~CVtUiAppUiMGVerifier()
    {
    delete iManager;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CVtUiAppUiMGVerifier::VerifySelectionL
// -----------------------------------------------------------------------------
//
TBool CVtUiAppUi::CVtUiAppUiMGVerifier::VerifySelectionL(
    const MDesCArray* aSelectedFiles )
    {
    TBool isOk( EFalse );
    if ( aSelectedFiles->MdcaCount() > 0 )
        {
        TVirtualPathPtr virtualPath(
            aSelectedFiles->MdcaPoint( 0 ), KDefaultContentObject );

        // not ptotected by default
        TInt isProtected = 0;

        TInt err = iManager->GetAttribute( EIsProtected,
            isProtected, virtualPath );
        if ( isProtected )
            {
            iAppUi.ShowDRMNotAllowedNoteL();
            }
        if ( err == KErrNone )
            {
            isOk = !isProtected;
            }
        }
    return isOk;
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CVtUiAppUiMGVerifier::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiAppUi::CVtUiAppUiMGVerifier::ConstructL()
    {
    iManager = CManager::NewL();
    }

// -----------------------------------------------------------------------------
// CVtUiAppUi::CVtUiAppUiMGVerifier::CVtUiAppUiMGVerifier
// -----------------------------------------------------------------------------
//
CVtUiAppUi::CVtUiAppUiMGVerifier::CVtUiAppUiMGVerifier(
    CVtUiAppUi& aAppUi, CCoeEnv& aCoeEnv )
    : iAppUi( aAppUi ), iCoeEnv( &aCoeEnv )
    {
    }

//  End of File

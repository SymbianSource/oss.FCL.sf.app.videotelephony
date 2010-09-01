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
* Description:  Concrete application state classes
*
*/


#ifndef T_VTUIAPPSTATES_H
#define T_VTUIAPPSTATES_H

#include "tvtuiappstatebase.h"
#include <babitflags.h>
#include <vtengcommands.h>

class CAknQueryDialog;

/**
*  Initial application state. Responsible for startup phase 1 and
*  startup phase 2 (see EVtUiAppUiStartup in CVtUiAppUi.cpp).
*  Certain other state changes are required for phase 2 and history
*  of their reception is handled with precondition flags.
*
*  @since S60 v3.2
*/
class TVtUiStateStarting : public TVtUiAppStateBase
    {
public:
    /**
    * returns singleton instance of TVtUiStateStarting
    * @param aCtx state context
    * @param aUiStates UI states
    * @return singleton
    */
    static TVtUiStateStarting* InstanceL(
        MVtUiStateContext& aCtx,
        TVtUiStates& aUiStates );

public: // from TVtUiAppStateBase

    /** @see TVtUiAppStateBase */
    virtual void AppUiStartupPhase1DoneL();

    /** @see TVtUiAppStateBase */
    virtual void AppUiStartupPhase2DoneL();

    /** @see TVtUiAppStateBase */
    virtual TEventResponse HandleVtEventL( TInt aEvent );

    /** @see TVtUiAppStateBase */
    virtual TEventResponse HandleCommandL( const TInt aCommand );

    /** @see TVtUiAppStateBase */
    virtual TBool HandleForegroundChangedL( TBool aIsForeground );

private: // from TVtUiAppStateBase

    /** @see TVtUiAppStateBase */
    virtual void OpenL();

    /** @see TVtUiAppStateBase */
    virtual void Close();

private: // new methods

    void CheckSessionStateL();
    static TInt AsynchOpen( TAny* aAny );
    
    void DoOpenL();
    
    /** Preconditions that must be passed in order to proceed
     * to Phase 2 in startup.
     */
    enum TPreconditions
        {
        /** waiting for CLI from engine*/
        EWaitingCLI,
        /** waiting for phase1 to complete */
        EWaitingPhase1ToComplete,
        /** waiting for engine to get proper state */
        EWaitingSessionState
    };

    /**
    * Clears precondition passed as argument and checks if any
    * preconditions hold and if not proceeds to phase 2 of startup.
    */
    void CheckPhase2StartupL( const TPreconditions aClearCondition );
    
    void HandleCLIReceivedL();

private: // constructors and destructors

    // c++ constructor
    TVtUiStateStarting(
        MVtUiStateContext& aCtx,
        TVtUiStates& aUiStates );

    // Destructor
    virtual ~TVtUiStateStarting();

private: // data members

    // Precondition for state change to running
    TBitFlags8 iPreconditions;

    // Singleton
    static TVtUiStateStarting* iInstance;
    
    // Starts phase1 startup in state state context. Needed because
    // initial state is opened from within state context construction.
    CAsyncCallBack*     iStartCallback;
    };

/**
*  Application state that is active in normal operation.
*
*  @since S60 v3.2
*/
class TVtUiStateRunning : public TVtUiAppStateBase
    {
public:
    /**
    * returns singleton instance of TVtUiStateRunning
    * @param aCtx state context
    * @param aUiStates UI states
    * @return singleton
    */
    static TVtUiStateRunning* InstanceL(
        MVtUiStateContext& aCtx,
        TVtUiStates& aUiStates );

public: // from TVtUiAppStateBase

    /** @see TVtUiAppStateBase */
    virtual TEventResponse HandleVtEventL( TInt aEvent );

    /** @see TVtUiAppStateBase */
    virtual TEventResponse HandleCommandL( const TInt aCommand );

    /** @see TVtUiAppStateBase */
    virtual TBool HandleForegroundChangedL( TBool aIsForeground );

    /** @see TVtUiAppStateBase */
    virtual TBool PreHandleForegroundChangedL( TBool aIsForeground );
    /** @see TVtUiAppStateBase */
    virtual void HandleLayoutChangedL();

    /** @see TVtUiAppStateBase */
    virtual void StartDtmfTone( const TChar& aTone );

    /** @see TVtUiAppStateBase */
    virtual void StopDtmfTone();

    /** @see TVtUiAppStateBase */
    virtual void OpenL();

private: // from TVtUiAppStateBase
    /** @see TVtUiAppStateBase */
    virtual void Close();

private: // constructors and destructors

    // c++ constructor
    TVtUiStateRunning(
        MVtUiStateContext& aCtx,
        TVtUiStates& aUiStates );

    // Destructor
    virtual ~TVtUiStateRunning();

private: // new functions

    /** Requests call handling subsystem to initiate a voice call.
     * Starts shutdown of the application.
     */
    void CreateVoiceCallL();

    /** Dials emergency call and starts shutdown */
    void DialEmergencyCallL();
    
    void ShutdownWithEngineCommandL( const TInt aCommand );

private: // data members
    // singleton
    static TVtUiStateRunning* iInstance;
    // Create voice call query instance
    CAknQueryDialog* iCreateVoiceCallDlg;
    };

/**
*  Application state that is active during shutdown.
*
*  @since S60 v3.2
*/
class TVtUiStateResetting : public TVtUiAppStateBase
    {
public:
    /**
    * returns singleton instance of TVtUiStateResetting
    * @param aCtx state context
    * @param aUiStates UI states
    * @param aCommand engine command to send when resetting state activates
    * @return singleton
    */
    static TVtUiStateResetting* InstanceL(
        MVtUiStateContext& aCtx,
        TVtUiStates& aUiStates,
        const TVtEngCommandId aCommand = KVtEngCommandNone );

public: // from TVtUiAppStateBase

    /** @see TVtUiAppStateBase */
    virtual void AppUiStartupFailedL();

    /** @see TVtUiAppStateBase */
    virtual void ShutdownDoneL();

    /** @see TVtUiAppStateBase */
    virtual TEventResponse HandleVTCommandPerformedL(
        TVtEngCommandId aCommand,
        const TInt aError );

    /** @see TVtUiAppStateBase */
    virtual TEventResponse HandleVtEventL( TInt aEvent );

    /** @see TVtUiAppStateBase */
    virtual TEventResponse HandleCommandL( const TInt aCommand );

    /** @see TVtUiAppStateBase */
    virtual TBool HandleForegroundChangedL( TBool aIsForeground );

    /** @see TVtUiAppStateBase */
    virtual void HandleLayoutChangedL();

private: // from TVtUiAppStateBase

    /** @see TVtUiAppStateBase */
    virtual void OpenL();

    /** @see TVtUiAppStateBase */
    virtual void Close();

private: // constructors and destructors

    // c++ constructor
    TVtUiStateResetting(
        MVtUiStateContext& aCtx,
        TVtUiStates& aUiStates,
        const TVtEngCommandId aCommand = KVtEngCommandNone );

    // Destructor
    virtual ~TVtUiStateResetting();

private: // data members

    // Singleton
    static TVtUiStateResetting* iInstance;
    
    // Used in user originated shutdown (end active call/switch to voice)
    TVtEngCommandId iCommand;
    };

#endif // T_VTUIAPPSTATES_H

/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiExecuteCmdDialog class.
*
*/



// INCLUDE FILES
#include    "CVtUiExecuteCmdDialog.h"
#include    "MVtUiEngineCommandManager.h"
#include    <mvtengcommandhandler.h>
#include    <cvtlogger.h>

// MODULE DATA STRUCTURES

/**
* Active object to perform asynchronous commands.
* @since Series 60 2.6
*/
class CVtUiExecuteCmdDialog::CActiveCmd
    : public CActive
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        */
        CActiveCmd(
            CVtUiExecuteCmdDialog& aDialog,
            MVtEngCommandHandler& aCommandHandler,
            TVtEngCommandId aCommand,
            TDesC8* aParams );

        /**
        * Destructor.
        */
        ~CActiveCmd();

    public: // New functions

        /**
        * Starts active object. Command will be performed in RunL.
        */
        void Start();

        /**
        * Checks if command has been performed.
        * @return ETrue if command has been performed.
        */
        TBool CommandPerformed() const;

    private:

        /**
        * @see CActive::RunL
        */
        void RunL();

        /**
        * @see CActive::DoCancel.
        */
        void DoCancel();

        /**
        * @see CActive::RunError.
        */
        TInt RunError( TInt aResult );

    private:

        // Ref to dialog.
        CVtUiExecuteCmdDialog& iDialog;

        // Ref to command handler.
        MVtEngCommandHandler& iCommandHandler;

        // Command to be executed.
        TVtEngCommandId iCommand;

        // Owned parameters.
        TDesC8* iCommandParams;

        // ETrue if command has been performed.
        TBool iCommandPerformed;

    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CVtUiExecuteCmdDialog
// -----------------------------------------------------------------------------
//
CVtUiExecuteCmdDialog::CVtUiExecuteCmdDialog(
        CEikDialog** aSelfPtr,
        MVtEngCommandHandler& aCommandHandler,
        MVtUiEngineCommandManager& aCommandManager )
    : CVtUiBlankDialog( aSelfPtr ),
      iCommandHandler( aCommandHandler ),
      iCommandManager( aCommandManager )
    {
    __VTPRINT2( DEBUG_GEN, "Ui.Dlg.Ctor this=%d", (TInt)this )
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::~CVtUiExecuteCmdDialog
// -----------------------------------------------------------------------------
//
CVtUiExecuteCmdDialog::~CVtUiExecuteCmdDialog()
    {
    __VTPRINTENTER( "VtUiExCmdDlg.~" )
    __VTPRINT2( DEBUG_GEN, "VtUiExCmdDlg.~ this=%d", (TInt)this )
    if ( iActiveCmd )
        {
        if ( !iCommandCompleted && iActiveCmd->CommandPerformed() )
            {
            iCommandHandler.CancelCommand( iCommand ); // ignore error
            }
        }
    delete iCommandParams;
    delete iActiveCmd;

    iCommandManager.RemoveObserver( *this );
    __VTPRINTEXIT( "VtUiExCmdDlg.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::ExecuteCmdLD
// -----------------------------------------------------------------------------
//
void CVtUiExecuteCmdDialog::ExecuteCmdLD(
        const TVtEngCommandId aCommandId,
        TDesC8* aParams,
        TRequestStatus* aRequest )
    {
    __VTPRINTENTER( "VtUiExCmdDlg.ExecuteCmd" )
    __VTPRINT2( DEBUG_GEN, "Ui.Dlg.Exec this=%d", (TInt)this )
    iCommand = aCommandId;
    CleanupStack::PushL( this );
    if ( aParams )
        {
        iCommandParams = aParams->AllocL();
        }

    iCommandManager.AddObserverL( *this );
    CleanupStack::Pop( this );

    CVtUiBlankDialog::ExecuteDialogLD( aRequest );
    __VTPRINTEXIT( "VtUiExCmdDlg.ExecuteCmd" )
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::PostLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CVtUiExecuteCmdDialog::PostLayoutDynInitL()
    {
    __VTPRINTENTER( "VtUiExCmdDlg.PostL" )
    iActiveCmd =
        new ( ELeave ) CActiveCmd(
            *this, iCommandHandler, iCommand, iCommandParams );
    iActiveCmd->Start();
    __VTPRINTEXITR( "VtUiExCmdDlg.PostL this=%d", (TInt)this )
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::HandleVTCommandPerformedL
// -----------------------------------------------------------------------------
//
void CVtUiExecuteCmdDialog::HandleVTCommandPerformedL(
        TVtEngCommandId aCommand,
        const TInt aError )
    {
    __VTPRINTENTER( "VtUiExCmdDlg.HandleVTCommandPerformed" )
    __VTPRINT2( DEBUG_GEN, "VtUiExCmdDlg.cmd.%d", aCommand )
    __VTPRINT2( DEBUG_GEN, "VtUiExCmdDlg.err.%d", aError )
    if ( iActiveCmd && ( aCommand == iCommand ) )
        {
        if ( iActiveCmd->CommandPerformed() && !iCommandCompleted )
            {
            __VTPRINT( DEBUG_GEN, "VtUiExCmdDlg.match" )
            iCommandCompleted = ETrue;
            // Corrupted images may leave during initialization, thus we have
            // to mask out errors when they happen during share initialize.
            // Error code is handled correctly in CVtUiAppUi::CEventObserver::
            // HandleVTCommandPerformedL() method, thus it will not be ignored.
            if ( aCommand == KVtEngInitializeShareImage )
                {
                Complete( KErrNone );
                }
            else
                {
                Complete( aError );
                }
            }
        }
    __VTPRINTEXIT( "VtUiExCmdDlg.HandleVTCommandPerformed" )
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::HandleExecuteFailed
// -----------------------------------------------------------------------------
//
void CVtUiExecuteCmdDialog::HandleExecuteFailed( TInt aResult )
    {
    __VTPRINT3( DEBUG_GEN, "VtUiExCmdDlg.Fail this=%d res=%d",
        (TInt)this, aResult )
    Complete( aResult );
    }

// Implementation of CVtUiExecuteCmdDialog::CActiveCmd:

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CActiveCmd::CActiveCmd
// -----------------------------------------------------------------------------
//
CVtUiExecuteCmdDialog::CActiveCmd::CActiveCmd(
        CVtUiExecuteCmdDialog& aDialog,
        MVtEngCommandHandler& aCommandHandler,
        TVtEngCommandId aCommand,
        TDesC8* aParams)
    : CActive( CActive::EPriorityHigh ),
      iDialog( aDialog ),
      iCommandHandler( aCommandHandler ),
      iCommand( aCommand ),
      iCommandParams( aParams )
    {
    CActiveScheduler::Add( this );
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CActiveCmd::~CActiveCmd
// -----------------------------------------------------------------------------
//
CVtUiExecuteCmdDialog::CActiveCmd::~CActiveCmd()
    {
    __VTPRINT2( DEBUG_GEN, "VtUiExCmdDlgCmd.Dtor this=%d", (TInt)this )
    Cancel();
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CActiveCmd::Start
// -----------------------------------------------------------------------------
//
void CVtUiExecuteCmdDialog::CActiveCmd::Start()
    {
    __VTPRINTENTER( "VtUiExCmdDlgCmd.Start" )
    TRequestStatus* status = &iStatus;
    User::RequestComplete( status, KErrNone );
    SetActive();
    __VTPRINTEXITR( "VtUiExCmdDlgCmd.Start this=%d", (TInt)this )
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CActiveCmd::CommandPerformed
// -----------------------------------------------------------------------------
//
TBool CVtUiExecuteCmdDialog::CActiveCmd::CommandPerformed() const
    {
    __VTPRINT3( DEBUG_GEN, "VtUiExCmdDlgCmd.Perf this=%d,cmd=%d",
        (TInt)this, iCommandPerformed )
    return iCommandPerformed;
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CActiveCmd::RunL
// -----------------------------------------------------------------------------
//
void CVtUiExecuteCmdDialog::CActiveCmd::RunL()
    {
    __VTPRINTENTER( "VtUiExCmdDlgCmd.RunL" )
    iCommandHandler.ExecuteL( iCommand, iCommandParams );
    iCommandPerformed = ETrue;
    __VTPRINTEXITR( "VtUiExCmdDlgCmd.RunL this=%d", (TInt)this )
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CActiveCmd::DoCancel
// -----------------------------------------------------------------------------
//
void CVtUiExecuteCmdDialog::CActiveCmd::DoCancel()
    {
    __VTPRINT2( DEBUG_GEN, "VtUiExCmdDlgCmd.DoCnl this=%d", (TInt)this )
    // Request is completed immediately.
    }

// -----------------------------------------------------------------------------
// CVtUiExecuteCmdDialog::CActiveCmd::RunError
// -----------------------------------------------------------------------------
//
TInt CVtUiExecuteCmdDialog::CActiveCmd::RunError( TInt aResult )
    {
    __VTPRINTENTER( "VtUiExCmdDlgCmd.RunError" )
    // Exception was raised in RunL. Inform the dialog to close itself.
    iDialog.HandleExecuteFailed( aResult );
    __VTPRINTEXITR( "VtUiExCmdDlgCmd.RunError this=%d", (TInt)this )
    return KErrNone;
    }

//  End of File

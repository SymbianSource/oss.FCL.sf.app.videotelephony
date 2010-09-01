/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Dialog for command execution for Video Telephone application.
*
*/



#ifndef CVTUIEXECUTECMDDIALOG_H
#define CVTUIEXECUTECMDDIALOG_H

//  INCLUDES
#include    "CVtUiBlankDialog.h"
#include    <mvtengcommandobserver.h>

// FORWARD DECLARATIONS
class MVtEngCommandHandler;
class MVtUiEngineCommandManager;

// CLASS DECLARATION

/**
*  Dialog for command execution for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiExecuteCmdDialog
    : public CVtUiBlankDialog,
      private MVtEngCommandObserver
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        *
        * @param aSelfPtr optional pointer to itself.
        * @param aCommandHandler command handler.
        * @param aCommandManager command manager.
        */
        CVtUiExecuteCmdDialog(
            CEikDialog** aSelfPtr,
            MVtEngCommandHandler& aCommandHandler,
            MVtUiEngineCommandManager& aCommandManager );

        /**
        * Destructor.
        */
        ~CVtUiExecuteCmdDialog();

    public: // New functions

        /**
        * Executes command dialog.
        * @param aCommandId command identifier.
        * @param aParams parameters.
        * @param aRequest request status, optional.
        */
        void ExecuteCmdLD(
            const TVtEngCommandId aCommandId,
            TDesC8* aParams,
            TRequestStatus* aRequest );

    protected: // Functions from base classes

        /**
        * @see CVtUiBlankDialog::PostLayoutDynInitL.
        */
        void PostLayoutDynInitL();

    private:

        /**
        * @see MVtEngCommandObserver::HandleVTCommandPerformedL.
        */
        virtual void HandleVTCommandPerformedL(
            TVtEngCommandId aCommand,
            const TInt aError );

        /**
        * Handles execution failure.
        * @param aResult error code.
        */
        void HandleExecuteFailed( TInt aResult );

    private:

        // Inner class.
        class CActiveCmd;

        // Friend.
        friend class CActiveCmd;

        // Ref to command handler.
        MVtEngCommandHandler& iCommandHandler;

        // Ref to command manager.
        MVtUiEngineCommandManager& iCommandManager;

        // Command to be executed.
        TVtEngCommandId iCommand;

        // Owned parameters.
        HBufC8* iCommandParams;

        // ETrue if command has been completed.
        TBool iCommandCompleted;

        // Owned active object to perform the command.
        CActiveCmd* iActiveCmd;

    };

#endif      // CVTUIEXECUTECMDDIALOG_H

// End of File

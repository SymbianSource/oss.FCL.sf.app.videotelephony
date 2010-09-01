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
* Description:  Bluetooth HF activation dialog for Video Telephone application.
*
*/



#ifndef CVTUIACTIVATEBTHFDIALOG_H
#define CVTUIACTIVATEBTHFDIALOG_H

//  INCLUDES
#include    <AknWaitDialog.h>
#include    <mvtengcommandobserver.h>
#include    <mvtengaudio.h>

// FORWARD DECLARATIONS
class MVtEngCommandHandler;
class MVtUiEngineCommandManager;

// CLASS DECLARATION

/**
*  Bluetooth HF activation dialog for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiActivateBtHfDialog
    : public CAknWaitDialog,
      private MVtEngCommandObserver
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        *
        * @param aSelfPtr optional pointer to itself.
        * @param aError optional pointer to error code variable.
        * @param aCommandHandler command handler.
        * @param aCommandManager command manager.
        */
        CVtUiActivateBtHfDialog(
            CEikDialog** aSelfPtr,
            TInt* aError,
            MVtEngCommandHandler& aCommandHandler,
            MVtUiEngineCommandManager& aCommandManager );

        /**
        * Destructor.
        */
        ~CVtUiActivateBtHfDialog();

    public: // New functions

        /**
        * Executes bluetooth activation dialog.
        */
        void ExecuteDialogLD();

    protected: // Functions from base classes

        /**
        * @see CEikDialog::PostLayoutDynInitL.
        */
        virtual void PostLayoutDynInitL();

    private:

        /**
        * @see MVtEngCommandObserver::HandleVTCommandPerformedL.
        */
        virtual void HandleVTCommandPerformedL(
            TVtEngCommandId aCommand,
            const TInt aError );

    private:

        // Reference to command handler.
        MVtEngCommandHandler& iCommandHandler;

        // Reference to command manager.
        MVtUiEngineCommandManager& iCommandManager;

        // ETrue if command is performed.
        TBool iCommandPerformed;

        // Pointer to error code variable.
        TInt* iError;

        // Audio routing setting.
        TPckgBuf< MVtEngAudio::TVtEngRoutingSetting > iAudioRouting;

    };

#endif      // CVTUIACTIVATEBTHFDIALOG_H

// End of File

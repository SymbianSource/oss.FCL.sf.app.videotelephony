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
* Description:  Blank dialog for Video Telephone application.
*
*/



#ifndef CVTUIBLANKDIALOG_H
#define CVTUIBLANKDIALOG_H

//  INCLUDES
#include    <eikdialg.h>

// CLASS DECLARATION

/**
*  Blank dialog for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiBlankDialog
    : public CEikDialog
    {
    public: // Constructors and destructor
        
        /**
        * Constructor.
        *
        * @param aSelfPtr optional pointer to itself.
        */
        CVtUiBlankDialog( CEikDialog** aSelfPtr );

        /**
        * Destructor. If a pointer was passed in constructor, 
        * it will be cleared here.
        */
        ~CVtUiBlankDialog();

    public: // New functions

        /**
        * Executes blank dialog, no wait flag set.
        */
        void ExecuteDialogNoWaitLD();

        /**
        * Executes blank dialog.
        * @param aRequest request status, optional.
        */
        void ExecuteDialogLD( 
            TRequestStatus* aRequest );

    protected: // New functions

        /**
        * Completes dialog with error.
        * Note: this method will delete the dialog.
        * @param aError error code.
        */
        void Complete( const TInt aError );

    protected: // Functions from base classes

        /**
        * @see CEikDialog::PreLayoutDynInitL.
        */
        void PreLayoutDynInitL();
        
        /**
        * @see CEikDialog::PostLayoutDynInitL.
        */
        void PostLayoutDynInitL();

        /**
        * @see CEikDialog::OkToExitL.
        */
        TBool OkToExitL( TInt aButtonId );

        /**
        * @see CEikDialog::Draw.
        */
        void Draw( const TRect& aRect ) const;

    private:

        // Pointer to itself.
        CEikDialog** iSelfPtr;

        // Error code.
        TInt* iError;

        // Request status.
        TRequestStatus* iRequest;
    };

#endif      // CVTUIBLANKDIALOG_H
            
// End of File

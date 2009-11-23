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
* Description:  'Allow video image' query for Video Telephone application.
*
*/



#ifndef CVTUIALLOWVIDEODIALOG_H
#define CVTUIALLOWVIDEODIALOG_H

//  INCLUDES
#include    <aknquerydialog.h>

// CLASS DECLARATION

/**
*  'Allow video image' query for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiAllowVideoDialog
    : public CAknQueryDialog
    {
    public: // Constructors and destructor
        
        /**
        * Constructor.
        *
        * @param aSelfPtr optional pointer to itself.
        * @param aTone tone to be played.
        */
        CVtUiAllowVideoDialog( 
            CEikDialog** aSelfPtr,
            const TTone& aTone );

        /**
        * Destructor.
        */
        ~CVtUiAllowVideoDialog();

    public: // New functions

        /**
        * Enumerates different results which
        * can be completed to request status.
        */
        enum TResult
            {
            // Query was canceled.
            EQueryCanceled = 1,
            // Query was dismissed due to timeout.
            EQueryDismissedTimeout,
            // User denied video sending.
            EUserDenied,
            // User allowed video sending.
            EUserAllowed
            };

        /**
        * Runs dialog.
        * @param aStatus request status.
        */
        void ExecuteDialogLD(
            TRequestStatus& aStatus );

    protected: // Functions from base classes
       
        /**
        * @see CAknQueryDialog::PostLayoutDynInitL.
        */
        virtual void PostLayoutDynInitL();

        /**
        * @see CAknQueryDialog::OkToExitL.
        */
        virtual TBool OkToExitL( TInt aCommand );

    private:

        /**
        * Callback function. Called when this query
        * is dismissed.
        * @param aAny pointer to instance of this class.
        * @return KErrNone.
        */
        static TInt DoDismissDialogTimeoutL( TAny* aAny );

    private:

        // Pointer to pointer to this instance.
        CEikDialog** iSelfPtr;

        // Timer for dismissing the query after timeout.
        CPeriodic* iQueryTimer;

        // Request status.
        TRequestStatus* iRequestStatus;

    };

#endif      // CVTUIALLOWVIDEODIALOG_H
            
// End of File

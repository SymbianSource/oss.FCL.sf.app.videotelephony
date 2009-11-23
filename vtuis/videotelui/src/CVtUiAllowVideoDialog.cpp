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
* Description:  Implementation of the CVtUiAllowVideoDialog class.
*
*/



// INCLUDE FILES
#include    "CVtUiAllowVideoDialog.h"
#include    <stringloader.h>
#include    <videotelui.rsg>

// CONSTANTS

// Timeout for allow video query.
const TInt KVtUiAllowVideoDialogTimeout = 5000000;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiAllowVideoDialog::CVtUiAllowVideoDialog
// -----------------------------------------------------------------------------
//
CVtUiAllowVideoDialog::CVtUiAllowVideoDialog(
        CEikDialog** aSelfPtr,
        const TTone& aTone )
    : CAknQueryDialog( aTone ),
      iSelfPtr( aSelfPtr )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiAllowVideoDialog::~CVtUiAllowVideoDialog
// -----------------------------------------------------------------------------
//
CVtUiAllowVideoDialog::~CVtUiAllowVideoDialog()
    {
    if ( iSelfPtr )
        {
        *iSelfPtr = NULL;
        iSelfPtr = NULL;
        }

    if ( iRequestStatus )
        {
        User::RequestComplete( iRequestStatus, KErrNone );
        iRequestStatus = NULL;
        }

    delete iQueryTimer;
    }

// -----------------------------------------------------------------------------
// CVtUiAllowVideoDialog::ExecuteDialogLD
// -----------------------------------------------------------------------------
//
void CVtUiAllowVideoDialog::ExecuteDialogLD(
        TRequestStatus& aStatus )
    {
    aStatus = KRequestPending;

    HBufC* prompt = StringLoader::LoadLC( R_VIDEOTELUI_QTN_SEND_VIDEO_IMAGE );

    PrepareLC( R_VIDEOTELUI_ALLOW_VIDEO_QUERY );
    SetPromptL( *prompt );
    RunLD();

    CleanupStack::PopAndDestroy( prompt );
    iRequestStatus = &aStatus;
    }

// -----------------------------------------------------------------------------
// CVtUiAllowVideoDialog::PostLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CVtUiAllowVideoDialog::PostLayoutDynInitL()
    {
    CAknQueryDialog::PostLayoutDynInitL();

    iQueryTimer = CPeriodic::NewL( CActive::EPriorityStandard );
    iQueryTimer->Start(
        KVtUiAllowVideoDialogTimeout,
        KVtUiAllowVideoDialogTimeout,
        TCallBack( DoDismissDialogTimeoutL, this ) );
    }

// -----------------------------------------------------------------------------
// CVtUiAllowVideoDialog::OkToExitL
// -----------------------------------------------------------------------------
//
TBool CVtUiAllowVideoDialog::OkToExitL( TInt aCommand )
    {
    const TBool exit = 
        CAknQueryDialog::OkToExitL( aCommand );

    if ( exit )
        {
        CVtUiAllowVideoDialog::TResult result =
            CVtUiAllowVideoDialog::EQueryCanceled;

        switch ( aCommand )
            {
            case EAknSoftkeyOk:
            case EAknSoftkeyYes:
                result = CVtUiAllowVideoDialog::EUserAllowed;
                break;

            case EAknSoftkeyNo:
                result = CVtUiAllowVideoDialog::EUserDenied;
                break;

            default:
                break;
            }

        if ( iRequestStatus )
            {
            User::RequestComplete( iRequestStatus, result );
            iRequestStatus = NULL;
            }
        }

    return exit;
    }

// -----------------------------------------------------------------------------
// CVtUiAllowVideoDialog::DoDismissDialogTimeoutL
// -----------------------------------------------------------------------------
//
TInt CVtUiAllowVideoDialog::DoDismissDialogTimeoutL( TAny* aAny )
    {
    CVtUiAllowVideoDialog* self =
        static_cast< CVtUiAllowVideoDialog* >( aAny );

    TRequestStatus* status = self->iRequestStatus;
    self->iRequestStatus = NULL;
    
    delete self;    

    User::RequestComplete( 
        status,
        CVtUiAllowVideoDialog::EQueryDismissedTimeout );

    return KErrNone;
    }

//  End of File

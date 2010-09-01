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
* Description:  Implementation of the CVtUiBlankDialog class.
*
*/



// INCLUDE FILES
#include    "CVtUiBlankDialog.h"
#include    <videotelui.rsg>
#include    <avkon.hrh>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::CVtUiBlankDialog
// -----------------------------------------------------------------------------
//
CVtUiBlankDialog::CVtUiBlankDialog(
        CEikDialog** aSelfPtr )
    : iSelfPtr( aSelfPtr ) 
    {
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::~CVtUiBlankDialog
// -----------------------------------------------------------------------------
//
CVtUiBlankDialog::~CVtUiBlankDialog()
    {
    if ( iSelfPtr )
        {
        *iSelfPtr = NULL;
        iSelfPtr = NULL;
        }

    if ( iRequest )
        {
        User::RequestComplete( iRequest, KErrCancel );
        iRequest = NULL;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::ExecuteDialogNoWaitLD
// -----------------------------------------------------------------------------
//
void CVtUiBlankDialog::ExecuteDialogNoWaitLD()
    {
    ExecuteLD( R_VIDEOTELUI_BLANK_NOWAIT_DLG );
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::ExecuteDialogLD
// -----------------------------------------------------------------------------
//
void CVtUiBlankDialog::ExecuteDialogLD(
        TRequestStatus* aRequest )
    {
    if ( !aRequest )
        {
        TInt error = KErrNone;
        iError = &error;
 
        ExecuteLD( R_VIDEOTELUI_BLANK_DLG );
        User::LeaveIfError( error );
        }
    else
        {
        // It's assumed that either ExecuteLD leaves or
        // then dialog is started (& dialog is not immediately deleted).
        *aRequest = KRequestPending;
        ExecuteLD( R_VIDEOTELUI_BLANK_NOWAIT_DLG );
        iRequest = aRequest; 
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::Complete
// -----------------------------------------------------------------------------
//
void CVtUiBlankDialog::Complete( const TInt aError )
    {
    if ( iError )
        {
        *iError = aError;
        }

    if ( iRequest )
        {
        User::RequestComplete( iRequest, aError );
        iRequest = NULL;
        }

    delete this;
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::PreLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CVtUiBlankDialog::PreLayoutDynInitL()
    {
    MakeVisible( EFalse );
    ButtonGroupContainer().MakeVisible( EFalse );
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::PostLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CVtUiBlankDialog::PostLayoutDynInitL()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::OkToExitL
// -----------------------------------------------------------------------------
//
TBool CVtUiBlankDialog::OkToExitL( TInt aButtonId )
    {
    if ( aButtonId != EEikBidCancel )
        {
        return EFalse;
        }
    else
        {
        return CEikDialog::OkToExitL( aButtonId );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBlankDialog::Draw
// -----------------------------------------------------------------------------
//
void CVtUiBlankDialog::Draw( const TRect& /*aRect*/ ) const
    {
    }

//  End of File

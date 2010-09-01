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
* Description:  Implementation of the CVtUiActivateBtHfDialog class.
*
*/



// INCLUDE FILES
#include    "CVtUiActivateBtHfDialog.h"
#include    "MVtUiEngineCommandManager.h"
#include    <mvtengcommandhandler.h>
#include    <videotelui.rsg>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiActivateBtHfDialog::CVtUiActivateBtHfDialog
// -----------------------------------------------------------------------------
//
CVtUiActivateBtHfDialog::CVtUiActivateBtHfDialog(
        CEikDialog** aSelfPtr,
        TInt* aError, 
        MVtEngCommandHandler& aCommandHandler,
        MVtUiEngineCommandManager& aCommandManager )
    : CAknWaitDialog( aSelfPtr ),
      iCommandHandler( aCommandHandler ),
      iCommandManager( aCommandManager ),
      iError( aError ),
      iAudioRouting( MVtEngAudio::EActivateBT )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiActivateBtHfDialog::~CVtUiActivateBtHfDialog
// -----------------------------------------------------------------------------
//
CVtUiActivateBtHfDialog::~CVtUiActivateBtHfDialog()
    {
    if ( iError )
        {
        *iError = KErrCancel;
        iError = NULL;
        }

    if ( iCommandPerformed )
        {
        iCommandHandler.CancelCommand( KVtEngSetAudioRouting ); // ignore error
        }
    iCommandManager.RemoveObserver( *this );
    }

// -----------------------------------------------------------------------------
// CVtUiActivateBtHfDialog::ExecuteDialogLD
// -----------------------------------------------------------------------------
//
void CVtUiActivateBtHfDialog::ExecuteDialogLD()
    {
    CleanupStack::PushL( this );
    iCommandManager.AddObserverL( *this );
    SetTone( CAknNoteDialog::ENoTone );
    CleanupStack::Pop( this );

    ExecuteLD( R_VIDEOTELUI_BTHF_CONNECT_WAIT_NOTE );
    }

// -----------------------------------------------------------------------------
// CVtUiActivateBtHfDialog::PostLayoutDynInitL
// -----------------------------------------------------------------------------
//
void CVtUiActivateBtHfDialog::PostLayoutDynInitL()
    {
    iCommandHandler.ExecuteL( KVtEngSetAudioRouting, &iAudioRouting );
    iCommandPerformed = ETrue;

    CAknWaitDialog::PostLayoutDynInitL();
    }

// -----------------------------------------------------------------------------
// CVtUiActivateBtHfDialog::HandleVTCommandPerformedL
// -----------------------------------------------------------------------------
//
void CVtUiActivateBtHfDialog::HandleVTCommandPerformedL( 
        TVtEngCommandId aCommand,
        const TInt aError )
    {
    if ( aCommand == KVtEngSetAudioRouting )
        {
        if ( iError )
            {
            *iError = aError;
            iError = NULL;
            }

        ProcessFinishedL();
        }
    }

//  End of File

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
* Description:  Implementation of the CVtUiActiveExec class.
*
*/



// INCLUDE FILES
#include    "CVtUiActiveExec.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiActiveExec::CVtUiActiveExec
// -----------------------------------------------------------------------------
//
CVtUiActiveExec::CVtUiActiveExec(
        const TInt aPriority )
    : CActive( aPriority )
    {
    CActiveScheduler::Add( this );
    }

// -----------------------------------------------------------------------------
// CVtUiActiveExec::~CVtUiActiveExec
// -----------------------------------------------------------------------------
//
CVtUiActiveExec::~CVtUiActiveExec()
    {
    Cancel();
    }

// -----------------------------------------------------------------------------
// CVtUiActiveExec::Start
// -----------------------------------------------------------------------------
//
void CVtUiActiveExec::Start( 
        TInt aStartState, 
        MVtUiActiveExec& aExec )
    {
    Cancel();

    iInitialState = aStartState;
    iCurrentState = aStartState;
    iNextState = aStartState;

    iActiveExec = &aExec;

    TRequestStatus* status = &iStatus;
    User::RequestComplete( status, KErrNone );
    SetActive();
    }

// -----------------------------------------------------------------------------
// CVtUiActiveExec::InitialState
// -----------------------------------------------------------------------------
//
TInt CVtUiActiveExec::InitialState() const
    {
    return iInitialState;
    }

// -----------------------------------------------------------------------------
// CVtUiActiveExec::RequestStatus
// -----------------------------------------------------------------------------
//
TInt CVtUiActiveExec::RequestStatus() const
    {
    return iStatus.Int();
    }

// -----------------------------------------------------------------------------
// CVtUiActiveExec::RunL
// -----------------------------------------------------------------------------
//
void CVtUiActiveExec::RunL()
    {
    User::LeaveIfError( iStatus.Int() );
    TBool synch = ETrue;

    // Execute to the next asynchronous operation.
    while ( synch )
        {
        iCurrentState = iNextState;
        if ( iCurrentState )
            {
            synch = iActiveExec->ActiveExecExecuteL( 
                *this,
                iCurrentState, 
                iNextState, 
                iStatus );

            if ( !synch )
                {
                SetActive();
                }
            }
        else
            {   
            iActiveExec->ActiveExecDone( *this, iInitialState );
            if ( !IsActive() )
                {
                iInitialState = 0;
                }

            synch = EFalse;
            }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiActiveExec::DoCancel
// -----------------------------------------------------------------------------
//
void CVtUiActiveExec::DoCancel()
    {
    if ( iActiveExec )
        {
        iActiveExec->ActiveExecCancel( *this, iCurrentState );
        
        iCurrentState = 0;
        iActiveExec = NULL;
        iInitialState = 0;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiActiveExec::RunError
// -----------------------------------------------------------------------------
//
TInt CVtUiActiveExec::RunError( TInt aError )
    {
    if ( iActiveExec->ActiveExecContinue( *this, iCurrentState, aError ) )
        {
        iNextState = iCurrentState;

        TRequestStatus* status = &iStatus;
        User::RequestComplete( status, KErrNone );
        SetActive();
        }
    else
        {
        if ( !IsActive() )
            {
            iInitialState = 0;
            }
        }
    
    return KErrNone;
    }

//  End of File  

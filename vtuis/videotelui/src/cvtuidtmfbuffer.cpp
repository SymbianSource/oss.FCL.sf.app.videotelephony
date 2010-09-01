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
* Description:   Implementation of DTMF buffer class
*
*/


#include <coemain.h>
#include <cvtlogger.h>
#include "cvtuidtmfbuffer.h"
#include "tvtuiwsevent.h"
#include "VtUiUtility.h"

// Time after which buffer will be automatically reset (4 seconds).
const TInt KBufferResetInterval = 4 * 1000000;

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::NewL
// ---------------------------------------------------------------------------
//
CVtUiDTMFBuffer* CVtUiDTMFBuffer::NewL( const CCoeEnv& aCoeEnv )
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.NewL" )
    CVtUiDTMFBuffer* self = new ( ELeave ) CVtUiDTMFBuffer( aCoeEnv );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "CVtUiDTMFBuffer.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::~CVtUiDTMFBuffer
// ---------------------------------------------------------------------------
//
CVtUiDTMFBuffer::~CVtUiDTMFBuffer()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.~" )
    Cancel();
    iTimer.Close();
    __VTPRINTEXIT( "CVtUiDTMFBuffer.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::Append
// ---------------------------------------------------------------------------
//
TBool CVtUiDTMFBuffer::Append( TChar aChar )
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.Append" )
    TBool result( EFalse );
    if ( VtUiUtility::IsDTMFCharacter( aChar ) )
        {
        if ( iBuffer.Length() == iBuffer.MaxLength() )
            {
            iBuffer = iBuffer.Right( 1 );
            }
        iBuffer.Append( aChar );
        StartTimer();
        result = ETrue;
        }
    __VTPRINTEXITR( "CVtUiDTMFBuffer.Append %d", result )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::Reset
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::Reset()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.Reset" )
    Cancel();
    ResetBuffer();
    __VTPRINTEXIT( "CVtUiDTMFBuffer.Reset" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::Activate
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::Activate()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.Activate" )
    TVtUiWsEvent< MVtUiNumberSource > event(
        EVtUiWsEventNumberSourceActivate, this );
    iCoeEnv.WsSession().SendEventToWindowGroup(
        iCoeEnv.RootWin().WindowGroupId(), event );
    __VTPRINTEXIT( "CVtUiDTMFBuffer.Activate" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::Deactivate
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::Deactivate()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.Deactivate" )
    TVtUiWsEvent< MVtUiNumberSource > event(
        EVtUiWsEventNumberSourceDeactivate, this );
    iCoeEnv.WsSession().SendEventToWindowGroup(
        iCoeEnv.RootWin().WindowGroupId(), event );
    __VTPRINTEXIT( "CVtUiDTMFBuffer.Deactivate" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::GetContents
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::GetContents( TDes& aContents ) const
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.GetContents" )
    const TInt length( aContents.MaxLength() < iBuffer.Length() ?
            aContents.MaxLength() : iBuffer.Length() );
    if ( length )
        {
        aContents = iBuffer.Mid( 0, length );
        }
    else
        {
        aContents.Zero();
        }
    __VTPRINTEXIT( "CVtUiDTMFBuffer.GetContents" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::DoCancel
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::DoCancel()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.DoCancel" )
    iTimer.Cancel();
    __VTPRINTEXIT( "CVtUiDTMFBuffer.DoCancel" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::RunL
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::RunL()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.RunL" )
    TimerExpired( iStatus.Int() );
    __VTPRINTEXIT( "CVtUiDTMFBuffer.RunL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::CVtUiDTMFBuffer
// ---------------------------------------------------------------------------
//
CVtUiDTMFBuffer::CVtUiDTMFBuffer( const CCoeEnv& aCoeEnv ) :
    CActive( EPriorityStandard ), iCoeEnv( aCoeEnv )
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.ctor" )
    CActiveScheduler::Add( this );
    __VTPRINTEXIT( "CVtUiDTMFBuffer.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::ConstructL()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.ConstructL" )
    User::LeaveIfError( iTimer.CreateLocal() );
    __VTPRINTEXIT( "CVtUiDTMFBuffer.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::StartTimer
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::StartTimer()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.StartTimer" )
    Cancel();
    SetActive();
    iTimer.After( iStatus, KBufferResetInterval );
    __VTPRINTEXIT( "CVtUiDTMFBuffer.StartTimer" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::TimerExpired
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::TimerExpired( TInt aError )
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.TimerExpired" )
    if ( aError != KErrCancel )
        {
        ResetBuffer();
        }
    __VTPRINTEXIT( "CVtUiDTMFBuffer.TimerExpired" )
    }

// ---------------------------------------------------------------------------
// CVtUiDTMFBuffer::ResetBuffer
// ---------------------------------------------------------------------------
//
void CVtUiDTMFBuffer::ResetBuffer()
    {
    __VTPRINTENTER( "CVtUiDTMFBuffer.ResetBuffer" )
    iBuffer.Zero();
    __VTPRINTEXIT( "CVtUiDTMFBuffer.ResetBuffer" )
    }

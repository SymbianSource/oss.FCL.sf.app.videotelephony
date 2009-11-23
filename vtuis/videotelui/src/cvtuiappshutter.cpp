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
* Description:  Class responsible for application exit.
*
*/


#include "cvtuiappshutter.h"
#include "mvtuishutterobserver.h"
#include "mvtuistatecontext.h"
#include "mvtuinumbersource.h"
#include "tvtuilocalvariation.h"
#include <cvtlogger.h>
#include <eikenv.h>
#include <aknutils.h>
#include <aknnotewrappers.h>
#include <stringloader.h>

// singleton instance
static CVtUiAppShutter* iAppShutter = NULL;

// -----------------------------------------------------------------------------
// CVtUiAppShutter::InstanceL
// -----------------------------------------------------------------------------
//
CVtUiAppShutter* CVtUiAppShutter::InstanceL(
    MVtUiShutterObserver& aObserver )
    {
    __VTPRINTENTER( "CVtUiAppShutter.InstanceL" )
    if ( iAppShutter == NULL )
        {
        iAppShutter = new ( ELeave )
            CVtUiAppShutter( aObserver );
        }
    __VTPRINTEXIT( "CVtUiAppShutter.InstanceL" )
    return iAppShutter;
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::CVtUiAppShutter
// -----------------------------------------------------------------------------
//
CVtUiAppShutter::CVtUiAppShutter(
    MVtUiShutterObserver& aObserver ) :
    iPendingStateFlags( 0 ),
    iObserver( aObserver )
    {
    iPendingStateFlags.Set( EShutterWaitingStart );
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::~CVtUiAppShutter
// -----------------------------------------------------------------------------
//
CVtUiAppShutter::~CVtUiAppShutter()
    {
    __VTPRINTENTER( "CVtUiAppShutter.~" )
    // mark singleton null
    iAppShutter = NULL;
    delete iCallback;
    __VTPRINTEXIT( "CVtUiAppShutter.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::StartShutdown
// Called when application may exit, i.e TVtUiStateResetting state receives
// ShutdownDoneL message.
// -----------------------------------------------------------------------------
//
void CVtUiAppShutter::StartShutdown()
    {
    __VTPRINTENTER( "CVtUiAppShutter.StartShutdown" )
    iPendingStateFlags.Clear( EShutterWaitingStart );
    ShutdownIfReadyAndDestroy();
    __VTPRINTEXITR( "CVtUiAppShutter.StartShutdown flags %d",
        iPendingStateFlags.Value() )
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::ShutdownWithEmergencyCallL
// -----------------------------------------------------------------------------
//
void CVtUiAppShutter::ShutdownWithEmergencyCallL(
    MVtUiStateContext& aStateContext )
    {
    // Leaves if other than emergency number is supplied...
    CEmergencyCaller* emergency = CEmergencyCaller::DialEmergencyL( *this,
        aStateContext );
    // therefore the flag and member variable must not be set before above call.
    iPendingStateFlags.Set( EShutterWaitingEmergencyCallback );
    iEmergencyCaller = emergency;
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::EmergencyCallDoneL
// -----------------------------------------------------------------------------
//
void CVtUiAppShutter::EmergencyCallDoneL()
    {
    // Destruction of emergency handler is done asynchrounously to avoid
    // problems that might
    iPendingStateFlags.Clear( EShutterWaitingEmergencyCallback );
    TCallBack cb( EmergencyResponseCallback, this );
    EnqueCallbackL( cb );
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::EmergencyResponseCallback
// -----------------------------------------------------------------------------
//
TInt CVtUiAppShutter::EmergencyResponseCallback( TAny* aAny )
    {
    CVtUiAppShutter* shutter =
        reinterpret_cast<CVtUiAppShutter*>( aAny );
    // delete callback
    delete shutter->iCallback;
    shutter->iCallback = NULL;
    // delete emergency caller
    delete shutter->iEmergencyCaller;
    shutter->iEmergencyCaller = NULL;

    shutter->ShutdownIfReadyAndDestroy();
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::EnqueCallbackL
// -----------------------------------------------------------------------------
//
void CVtUiAppShutter::EnqueCallbackL( TCallBack& aCallback )
    {
    __VTPRINTENTER( "CVtUiAppShutter.EnqueAsyncCommsCommandL" )
    if ( !iCallback )
        {
        iCallback = new ( ELeave ) CAsyncCallBack( aCallback, EPriorityHigh );
        }
    iCallback->Call();
    __VTPRINTEXIT( "CVtUiAppShutter.EnqueAsyncCommsCommandL" )
    __VTPRINTEXIT( "CVtUiAppShutter.EnqueCallbackL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::ShutdownIfReadyAndDestroy
// -----------------------------------------------------------------------------
//
void CVtUiAppShutter::ShutdownIfReadyAndDestroy()
    {
    __VTPRINTENTER( "CVtUiAppShutter.ShutdownIfReadyAndDestroy" )
    __VTPRINT2( DEBUG_GEN, "  shutter flags %d",
        iPendingStateFlags.Value() );
    if ( !iPendingStateFlags.Value() )
        {
        iObserver.HandleShutdownReady();
        delete this;
        }
    __VTPRINTEXIT( "CVtUiAppShutter.ShutdownIfReadyAndDestroy" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::CEmergencyCaller::DialEmergencyL
// -----------------------------------------------------------------------------
//
CVtUiAppShutter::CEmergencyCaller* CVtUiAppShutter::CEmergencyCaller::
    DialEmergencyL(
    CVtUiAppShutter& aObserver,
    MVtUiStateContext& aStateContext )
    {
    __VTPRINTENTER( "CEmergencyCaller.DialEmergencyL" )
    CVtUiAppShutter::CEmergencyCaller* self = new ( ELeave )
        CVtUiAppShutter::CEmergencyCaller( aObserver, aStateContext );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    __VTPRINTEXIT( "CEmergencyCaller.DialEmergencyL" )
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::CEmergencyCaller::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiAppShutter::CEmergencyCaller::ConstructL()
    {
    __VTPRINTENTER( "CEmergencyCaller.ConstructL" )
    const MVtUiNumberSource* source = iStateContext.NumberSource();
    if ( source )
        {
        source->GetContents( iNumber );
        AknTextUtils::ConvertDigitsTo( iNumber, EDigitTypeWestern );
        User::LeaveIfError( iServer.Connect() );
    	iEmergency = CPhCltEmergencyCall::NewL( this );
        TBool isEmergenyNumber = EFalse;
        const TInt err =
        	iEmergency->FindEmergencyPhoneNumber( iNumber, isEmergenyNumber );

        if ( err == KErrNone && isEmergenyNumber )
            {
            __VTPRINT( DEBUG_GEN, "iEmergency->DialEmergencyCallL")
            iEmergency->DialEmergencyCallL( iNumber );
            }
        if ( !isEmergenyNumber || err )
            {
            __VTPRINT( DEBUG_GEN, "  not EC number => leave" )
            // Not an emergency call number. Abort emergency call process.
            User::Leave( KErrArgument );
            }
        }
    __VTPRINTEXIT( "CEmergencyCaller.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::CEmergencyCaller::CEmergencyCaller
// -----------------------------------------------------------------------------
//
CVtUiAppShutter::CEmergencyCaller::CEmergencyCaller(
    CVtUiAppShutter& aObserver,
    MVtUiStateContext& aStateContext ) :
    iObserver( aObserver ),
    iStateContext( aStateContext )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::CEmergencyCaller::~CEmergencyCaller
// -----------------------------------------------------------------------------
//
CVtUiAppShutter::CEmergencyCaller::~CEmergencyCaller()
    {
    __VTPRINTENTER( "CEmergencyCaller.~" )
    delete iEmergency;
    iServer.Close();
    __VTPRINTEXIT( "CEmergencyCaller.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiAppShutter::CEmergencyCaller::HandleEmergencyDialL
// -----------------------------------------------------------------------------
//
void CVtUiAppShutter::CEmergencyCaller::HandleEmergencyDialL(
    const TInt )
    {
    __VTPRINTENTER( "CEmergencyCaller.HandleEmergencyDialL" )
    iObserver.EmergencyCallDoneL();
    __VTPRINTEXIT( "CEmergencyCaller.HandleEmergencyDialL" )
    }


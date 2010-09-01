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
* Description:  Implementation of the TVtUiCallParameters class.
*
*/



// INCLUDE FILES
#include    "TVtUiCallParameters.h"

// CONSTANTS

// Enumerates call parameter flags.
enum TVtUiCallParameterFlags
    {
    // Audio status has been updated.
    EVtUiCallParameterFlagHasAudio = 1,
    // Audio status equals to ETrue.
    EVtUiCallParameterFlagAudioEnabled = 2,
    // Video status has been updated.
    EVtUiCallParameterFlagHasVideo = 4,
    // Video status equals to ETrue.
    EVtUiCallParameterFlagVideoEnabled = 8,
    // Selected camera has been updated.
    EVtUiCallParameterFlagHasSelectedCamera = 16,
    // Primary camera has been selected. Otherwise secondary has been selected.
    EVtUiCallParameterFlagHasSelectedPrimary = 32,
    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// TVtUiCallParameters::TVtUiCallParameters
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
TVtUiCallParameters::TVtUiCallParameters()
    : iFlags( 0 )
    {
    }

// -----------------------------------------------------------------------------
// TVtUiCallParameters::Reset
// -----------------------------------------------------------------------------
//
void TVtUiCallParameters::Reset()
    {
    iFlags = 0;
    }

// -----------------------------------------------------------------------------
// TVtUiCallParameters::SetAudioStatus
// -----------------------------------------------------------------------------
//
void TVtUiCallParameters::SetAudioStatus( const TBool aEnabled )
    {
    iFlags |= ( EVtUiCallParameterFlagAudioEnabled + 
                EVtUiCallParameterFlagHasAudio );
    if ( !aEnabled )
        {
        iFlags &= ~EVtUiCallParameterFlagAudioEnabled;
        }
    }

// -----------------------------------------------------------------------------
// TVtUiCallParameters::GetAudioStatus
// -----------------------------------------------------------------------------
//
TInt TVtUiCallParameters::GetAudioStatus( TBool& aEnabled ) const
    {
    TInt err = KErrNotFound;
    if ( iFlags & EVtUiCallParameterFlagHasAudio )
        {
        err = KErrNone;
        aEnabled = ( iFlags & EVtUiCallParameterFlagAudioEnabled );
        }

    return err;
    }

// -----------------------------------------------------------------------------
// TVtUiCallParameters::SetVideoStatus
// -----------------------------------------------------------------------------
//
void TVtUiCallParameters::SetVideoStatus( const TBool aEnabled )
    {
    iFlags |= ( EVtUiCallParameterFlagVideoEnabled + 
                EVtUiCallParameterFlagHasVideo );
    if ( !aEnabled )
        {
        iFlags &= ~EVtUiCallParameterFlagVideoEnabled;
        }
    }

// -----------------------------------------------------------------------------
// TVtUiCallParameters::GetVideoStatus
// -----------------------------------------------------------------------------
//
TInt TVtUiCallParameters::GetVideoStatus( TBool& aEnabled )
    {
    TInt err = KErrNotFound;
    if ( iFlags & EVtUiCallParameterFlagHasVideo )
        {
        err = KErrNone;
        aEnabled = ( iFlags & EVtUiCallParameterFlagVideoEnabled );
        }

    return err;
    }

// -----------------------------------------------------------------------------
// TVtUiCallParameters::SetSelectedCamera
// -----------------------------------------------------------------------------
//
void TVtUiCallParameters::SetSelectedCamera( const TBool aPrimary )
    {
    iFlags |= EVtUiCallParameterFlagHasSelectedCamera;
    
    if ( aPrimary )
        {
        iFlags |= EVtUiCallParameterFlagHasSelectedPrimary;
        }
    else
        {
        iFlags &= ~EVtUiCallParameterFlagHasSelectedPrimary;
        }
    }

// -----------------------------------------------------------------------------
// TVtUiCallParameters::GetSelectedCamera
// -----------------------------------------------------------------------------
//
TInt TVtUiCallParameters::GetSelectedCamera( TBool& aPrimary )
    {
    TInt err = KErrNotFound;
    if ( iFlags & EVtUiCallParameterFlagHasSelectedCamera )
        {
        err = KErrNone;
        aPrimary = ( iFlags & EVtUiCallParameterFlagHasSelectedPrimary );
        }

    return err;
    }

//  End of File  

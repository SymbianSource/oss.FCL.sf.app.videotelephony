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
* Description:  Media state class inline methods.
*
*/


// -----------------------------------------------------------------------------
// TVtUiMediaState::TVtUiMediaState
// -----------------------------------------------------------------------------
//
TVtUiMediaState::TVtUiMediaState( MVtEngMedia& aMedia,
    MVtEngCommandHandler& aCommandHandler  )
    : iMedia( aMedia ), iCommandHandler( aCommandHandler )
    {
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsVideo
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsVideo() const
    {
    return IsFlag( EIsVideo );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::HasCamera
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::HasCamera() const
    {
    return IsFlag( EHasCamera );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsFreezeSupported
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsFreezeSupported() const
    {
    return IsFlag( EIsFreezeSupported );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsFrozen
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsFrozen() const
    {
    return IsFlag( EIsFrozen );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsSharing
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsSharing() const
    {
    return IsFlag( EIsSharing );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsInitializingShare
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsInitializingShare() const
    {
    return IsFlag( EIsInitializingShare );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsPrimaryCameraInUse
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsPrimaryCameraInUse() const
    {
    return IsFlag( EIsPrimaryCameraInUse );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsSecondaryCameraInUse
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsSecondaryCameraInUse() const
    {
    return IsFlag( EIsSecondaryCameraInUse );
    }
    
// -----------------------------------------------------------------------------
// TVtUiMediaState::IsNotAbleToShare
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsNotAbleToShare() const
    {
    return IsFlag( EIsNotAbleToShare );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::HasPrimaryCamera
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::HasPrimaryCamera() const
    {
    return IsFlag( EHasPrimaryCamera );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::HasSecondaryCamera
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::HasSecondaryCamera() const
    {
    return IsFlag( EHasSecondaryCamera );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsContrastSupported
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsContrastSupported() const
    {
    return IsFlag( EIsContrastSupported );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsWhiteBalanceSupported
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsWhiteBalanceSupported() const
    {
    return IsFlag( EIsWhiteBalanceSupported );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsColorToneSupported
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsColorToneSupported() const
    {
    return IsFlag( EIsColorToneSupported );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsBrightnessSupported
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsBrightnessSupported() const
    {
    return IsFlag( EIsBrightnessSupported );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsVideoPermanentlyStopped
// -----------------------------------------------------------------------------
//
TBool TVtUiMediaState::IsVideoPermanentlyStopped() const
	{
	return IsFlag( EIsVideoPermanentlyStopped );
	}

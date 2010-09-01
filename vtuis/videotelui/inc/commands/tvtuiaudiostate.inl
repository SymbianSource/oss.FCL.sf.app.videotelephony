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
* Description:  Audio state class inline methods.
*
*/


// -----------------------------------------------------------------------------
// TVtUiAudioState::TVtUiAudioState
// -----------------------------------------------------------------------------
//
TVtUiAudioState::TVtUiAudioState( CVtEngModel& aModel )
: iModel( aModel )
    {
    }

// -----------------------------------------------------------------------------
// TVtUiAudioState::IsAudio
// -----------------------------------------------------------------------------
//
TBool TVtUiAudioState::IsAudio() const
    {
    return IsFlag( EIsAudio );
    }

// -----------------------------------------------------------------------------
// TVtUiAudioState::CanActivateBtHf
// -----------------------------------------------------------------------------
//
TBool TVtUiAudioState::CanActivateBtHf() const
    {
    return IsFlag( ECanActivateBtHf );
    }

// -----------------------------------------------------------------------------
// TVtUiAudioState::CanDeactivateBtHf
// -----------------------------------------------------------------------------
//
TBool TVtUiAudioState::CanDeactivateBtHf() const
    {
    return IsFlag( ECanDeactivateBtHf );
    }

// -----------------------------------------------------------------------------
// TVtUiAudioState::CanActivateLoudspeaker
// -----------------------------------------------------------------------------
//
TBool TVtUiAudioState::CanActivateLoudspeaker() const
    {
    return IsFlag( ECanActivateLoudspeaker );
    }

// -----------------------------------------------------------------------------
// TVtUiAudioState::CanDeactivateLoudspeaker
// -----------------------------------------------------------------------------
//
TBool TVtUiAudioState::CanDeactivateLoudspeaker() const
    {
    return IsFlag( ECanDeactivateLoudspeaker );
    }

// -----------------------------------------------------------------------------
// TVtUiMediaState::IsAudioPermanentlyStopped
// -----------------------------------------------------------------------------
//
TBool TVtUiAudioState::IsAudioPermanentlyStopped() const
	{
	return IsFlag( EIsAudioPermanentlyStopped );
	}

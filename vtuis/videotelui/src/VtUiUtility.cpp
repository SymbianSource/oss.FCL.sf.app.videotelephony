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
* Description:  Implementation of the VtUiUtility class.
*
*/



// INCLUDE FILES
#include    "VtUiUtility.h"
#include    "VtUiPanic.h"
#include    <featmgr.h>
#include    <mvtengmedia.h>
#include    <cvtlogger.h>
#include    <AknUtils.h>
#include 	"tVtuifeaturevariation.h"

// Characters to open number entry.
_LIT( KVtUiDTMFCharacters, "0123456789*#" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// VtUiUtility::GetAudioRoutingAvailability
// -----------------------------------------------------------------------------
//
void VtUiUtility::GetAudioRoutingAvailability(
        MVtEngAudio& aAudio,
        TInt& aAvailable )
    {
    aAvailable = 0;
    TVtUiBTVariation btvariation;
    const TBool bluetoothAudioSupported =
        btvariation.IsBTSupported();

    MVtEngAudio::TAudioRoutingState routingState;
    if ( aAudio.GetRoutingState( routingState ) == KErrNone )
        {
        // Deactivate BT handsfree.
        if ( bluetoothAudioSupported &&
             IsAudioRoutingAvailable(
                aAudio,
                routingState,
                MVtEngAudio::EAudioBT,
                MVtEngAudio::EAudioHandset ) )
            {
            aAvailable |= EDeactivateBtHandsfree;
            }

        // Activate BT handsfree.
        if ( bluetoothAudioSupported &&
             ( IsAudioRoutingAvailable(
                 aAudio,
                 routingState,
                 MVtEngAudio::EAudioHandset,
                 MVtEngAudio::EAudioBT ) ||
               IsAudioRoutingAvailable(
                aAudio,
                routingState,
                MVtEngAudio::EAudioLoudspeaker,
                MVtEngAudio::EAudioBT ) ) )
            {
            aAvailable |= EActivateBtHandsfree;
            }

        // Deactivate loudspeaker
        if ( IsAudioRoutingAvailable(
                aAudio,
                routingState,
                MVtEngAudio::EAudioLoudspeaker,
                MVtEngAudio::EAudioHandset ) )
            {
            aAvailable |= EDeactivateLoudspeaker;
            }

        // Activate loudspeaker
        if ( IsAudioRoutingAvailable(
                aAudio,
                routingState,
                MVtEngAudio::EAudioHandset,
                MVtEngAudio::EAudioLoudspeaker ) ||
             ( bluetoothAudioSupported && 
               IsAudioRoutingAvailable( 
                   aAudio,
                   routingState, 
                   MVtEngAudio::EAudioBT, 
                   MVtEngAudio::EAudioLoudspeaker ) ) )
            {
            aAvailable |= EActivateLoudspeaker;
            }
        }
    }

// -----------------------------------------------------------------------------
// VtUiUtility::GetOutgoingMediaState
// -----------------------------------------------------------------------------
//
void VtUiUtility::GetOutgoingMediaState(
        MVtEngMedia& aMedia,
        TInt& aAvailable )
    {
    TInt outgoingMediaState;
    const TInt err =
        aMedia.GetMediaState(
            MVtEngMedia::EMediaOutgoing,
            outgoingMediaState );
    if ( err == KErrNone )
        {
        // If source is still image, then video sending is off.
        MVtEngMedia::TMediaSource source;
        if ( aMedia.GetSource( source ) == KErrNone )
            {
            if ( source == MVtEngMedia::EMediaStillImage )
                {
                outgoingMediaState &= ~MVtEngMedia::EMediaVideo;
                }
            }
        TBool freezeSupported;
        if( aMedia.GetFreezeSupported( freezeSupported ) == KErrNone )
            {
            TBool isFrozen;
            if( freezeSupported && aMedia.GetFreezeState( isFrozen ) == KErrNone )
                {
                if( isFrozen )
                    {
                    outgoingMediaState &= ~MVtEngMedia::EMediaVideo;
                    }
                }
            }
        }
    else
        {
        outgoingMediaState =
            ( MVtEngMedia::EMediaAudio | MVtEngMedia::EMediaVideo );
        }
    aAvailable = outgoingMediaState;
    }

// -----------------------------------------------------------------------------
// VtUiUtility::GetIncomingMediaState
// -----------------------------------------------------------------------------
//
void VtUiUtility::GetIncomingMediaState(
        MVtEngMedia& aMedia,
        TInt& aAvailable )
    {
    TInt mediaState;
    const TInt err =
        aMedia.GetMediaState(
            MVtEngMedia::EMediaIncoming,
            mediaState );
    if ( err != KErrNone )
        {
        mediaState =
            ( MVtEngMedia::EMediaAudio | MVtEngMedia::EMediaVideo );
        }

    aAvailable = mediaState;
    }

// -----------------------------------------------------------------------------
// VtUiUtility::HasStillImage
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::HasStillImage(
        MVtEngMedia& aMedia )
    {
    TInt caps;
    const TInt capsErr = aMedia.GetSourcesCaps( caps );
    return ( capsErr == KErrNone ) &&
           ( caps & MVtEngMedia::ESourceCapsStillImage );
    }

// -----------------------------------------------------------------------------
// VtUiUtility::GetFreezeState
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::GetFreezeState(
        MVtEngMedia& aMedia )
    {
    TBool isFrozen;
    const TInt err = aMedia.GetFreezeState( isFrozen );
    if ( err == KErrNone )
        {
        return isFrozen;
        }
    else //provider was not ready
        {
        return EFalse;
        }
    }

// -----------------------------------------------------------------------------
// VtUiUtility::IsFreezeSupported
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::IsFreezeSupported(
        MVtEngMedia& aMedia )
    {
    TBool isFreezeSupported;
    const TInt err = aMedia.GetFreezeSupported( isFreezeSupported );
    if ( err == KErrNone )
        {
        return isFreezeSupported;
        }
    else //provider was not ready
        {
        return EFalse;
        }
    }

// -----------------------------------------------------------------------------
// VtUiUtility::GetVideoQuality
// -----------------------------------------------------------------------------
//
void VtUiUtility::GetVideoQuality(
        	MVtEngMedia& aMedia,
        	MVtEngMedia::TVideoQuality& aVideoQuality )
    {
    aMedia.GetVideoQuality( aVideoQuality );
    }

// -----------------------------------------------------------------------------
// VtUiUtility::GetObjectSharingState
// -----------------------------------------------------------------------------
//
void VtUiUtility::GetObjectSharingState(
    MVtEngMedia& aMedia,
    MVtEngMedia::TShareObjectState& aShareObjectState )
    {
    aMedia.GetObjectSharingState( aShareObjectState );
    }


// -----------------------------------------------------------------------------
// VtUiUtility::IsZoomAllowed
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::IsZoomAllowed(
        MVtEngMedia& aMedia )
    {
    TBool result = EFalse;

    TInt currentStep;
    if ( aMedia.GetCurrentZoomStep( currentStep ) == KErrNone )
        {
        TInt max;
        if ( aMedia.GetMaxZoomStep( max ) == KErrNone )
            {
            // Zooming is allowed if maximum zoom step is greater than
            // zero and camera is in use (and not still image / none).
            TInt avail;
            GetOutgoingMediaState( aMedia, avail );

            result = ( max > 0 ) && ( avail & MVtEngMedia::EMediaVideo );
            }
        }

    __VTPRINT2( DEBUG_GEN, "Ui.AllowZoom.%d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// VtUiUtility::HasCameras
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::HasCameras( MVtEngMedia& aMedia )
    {
    TInt sourceCaps;
    if ( aMedia.GetSourcesCaps( sourceCaps ) != KErrNone )
        {
        sourceCaps = 0;
        }
    return ( sourceCaps & MVtEngMedia::ESourceCapsPrimaryCamera ) ||
           ( sourceCaps & MVtEngMedia::ESourceCapsSecondaryCamera );
    }

// -----------------------------------------------------------------------------
// VtUiUtility::IsAudioRoutingAvailable
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::IsAudioRoutingAvailable(
        MVtEngAudio& aAudio,
        const MVtEngAudio::TAudioRoutingState aCurrent,
        const MVtEngAudio::TAudioRoutingState aSource,
        const MVtEngAudio::TAudioRoutingState aTarget )
    {
    TBool result = EFalse;
    if ( aCurrent == aSource )
        {
        TBool available = EFalse;
        TInt err = aAudio.GetRoutingAvailability( aTarget, available );

        result = ( ( err == KErrNone ) && ( available ) );
        }

    return result;
    }


// -----------------------------------------------------------------------------
// VtUiUtility::IsDTMFEvent
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::IsDTMFEvent( const TKeyEvent& aKeyEvent, TChar& aDtmfTone )
    {
    TBuf<1> buffer; // one character
    buffer.Append( aKeyEvent.iCode );
    AknTextUtils::ConvertDigitsTo( buffer, EDigitTypeWestern );
    aDtmfTone = buffer[ 0 ];
    return
        ( KVtUiDTMFCharacters().Locate( buffer[ 0 ] ) != KErrNotFound );
    }

// -----------------------------------------------------------------------------
// VtUiUtility::IsDTMFCharacter
// -----------------------------------------------------------------------------
//
TBool VtUiUtility::IsDTMFCharacter( const TChar aChar )
    {
    return
        ( KVtUiDTMFCharacters().Locate( aChar ) != KErrNotFound );
    }

//  End of File

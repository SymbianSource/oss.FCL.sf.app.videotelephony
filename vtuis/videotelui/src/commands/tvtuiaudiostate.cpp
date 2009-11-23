/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Audio state class.
*
*/

#include <cvtlogger.h>
#include <cvtengmodel.h>

#include "tvtuiaudiostate.h"
#include "VtUiUtility.h"

// -----------------------------------------------------------------------------
// TVtUiAudioState::UpdateFlags
// -----------------------------------------------------------------------------
//
void TVtUiAudioState::UpdateFlags()
    {
    __VTPRINTENTER( "AudioState.UpdateFlags" )
    TInt avail( 0 );

    VtUiUtility::GetAudioRoutingAvailability( iModel.Audio(), avail );

    const TBool videoCallConnected ( iModel.Media().VideoCallConnected());
    //Before update AudioRouting, video call state must to be checked.
    //AudioRouting can not be changed if call is not in EConnected state.
    if ( videoCallConnected )
        {
        __VTPRINT( DEBUG_GEN, " videoCallConnected " )
        if ( avail & VtUiUtility::EDeactivateBtHandsfree )
            {
            SetFlag( ECanDeactivateBtHf );
            }
        if ( avail & VtUiUtility::EActivateBtHandsfree )
            {
            SetFlag( ECanActivateBtHf );
            }
        if ( avail & VtUiUtility::EDeactivateLoudspeaker )
            {
            SetFlag( ECanDeactivateLoudspeaker );
            }
        if ( avail & VtUiUtility::EActivateLoudspeaker )
            {
            SetFlag( ECanActivateLoudspeaker );
            }
        }

    VtUiUtility::GetOutgoingMediaState( iModel.Media(), avail );

    if ( avail & MVtEngMedia::EMediaAudio )
        {
        SetFlag( EIsAudio );
        }

    TInt status ( 0 );
    iModel.Media().GetMediaState( MVtEngMedia::EMediaOutgoing, status );
    if ( !(status & MVtEngMedia::EMediaAudioChannelOpen ) )
        {
        SetFlag( EIsAudioPermanentlyStopped );
        }

    __VTPRINTEXITR( "AudioState.UpdateFlags bits = %b", Value() )
    }

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
* Description:  Volume popup implementation.
*
*/


#include    <aknvolumepopup.h>
#include    <cvtlogger.h>
#include    "cvtuivolumepopup.h"
#include    "cvtuifeaturemanager.h"
#include	"tVtuifeaturevariation.h"
#include    "CVtUiAppUi.h"
#include    "cvtengmodel.h"

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::NewL
// ---------------------------------------------------------------------------
//
CVtUiVolumePopup* CVtUiVolumePopup::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiVolumePopup.NewL" )
    CVtUiVolumePopup* self =
        new ( ELeave ) CVtUiVolumePopup( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiVolumePopup.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::~CVtUiVolumePopup
// ---------------------------------------------------------------------------
//
CVtUiVolumePopup::~CVtUiVolumePopup()
    {
    __VTPRINTENTER( "CVtUiVolumePopup.~" )
    __VTPRINTEXIT( "CVtUiVolumePopup.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::UpdateVolumeAndRouting
// ---------------------------------------------------------------------------
//
void CVtUiVolumePopup::UpdateVolumeAndRoutingL()
    {
    __VTPRINTENTER( "CVtUiVolumePopup.UpdateVolumeAndRoutingL" )
    MVtEngAudio& audio( iModel.Audio() );
    MVtEngAudio::TAudioRoutingState audioRouting;
    User::LeaveIfError( audio.GetRoutingState( audioRouting ) );
    //update routing and volume for this routing
    iAudioRouting = audioRouting;
    iVolume = OutputVolume( iAudioRouting );
    SetValue( iVolume );    
    __VTPRINTEXIT( "CVtUiVolumePopup.UpdateVolumeAndRoutingL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::RefreshL
// ---------------------------------------------------------------------------
//
void CVtUiVolumePopup::RefreshL()
    {
    __VTPRINTENTER( "CVtUiVolumePopup.RefreshL" )
    MVtEngAudio& audio( iModel.Audio() );
    MVtEngAudio::TAudioRoutingState audioRouting;
    User::LeaveIfError( audio.GetRoutingState( audioRouting ) );

    // Check if audio routing has changed
    if ( audioRouting != iAudioRouting )
        {
        __VTPRINT( DEBUG_GEN,
            "CVtUiVolumePopup.RefreshL audio routing changed" )
        // Audio routing changed -> update routing and volume for this routing
        iAudioRouting = audioRouting;
        iVolume = OutputVolume( iAudioRouting );
        SetValue( iVolume );
        __VTPRINT2( DEBUG_GEN, "CVtUiVolumePopup.RefreshL routing = %d",
            iAudioRouting )
        __VTPRINT2( DEBUG_GEN, "CVtUiVolumePopup.RefreshL volume = %d",
            iVolume )
        ClosePopup();
        }
    else
        {
        // No change in audio routing
        const TInt volume( OutputVolume( iAudioRouting ) );
        if ( volume != iVolume )
            {
            __VTPRINT( DEBUG_GEN, "CVtUiVolumePopup.RefreshL volume changed" )
            iVolume = volume;
            SetValue( iVolume );
            __VTPRINT2( DEBUG_GEN, "CVtUiVolumePopup.RefreshL volume = %d",
                iVolume )
            if ( !IsPopUpVisible() )
                {
                __VTPRINT( DEBUG_GEN, "CVtUiVolumePopup.RefreshL OpenPopupL" )
                OpenPopupL();
                }
            else
                {
                __VTPRINT( DEBUG_GEN, "CVtUiVolumePopup.RefreshL ShowPopupL" )
                ShowPopupL();
                }
            }
        else
            {
            __VTPRINT( DEBUG_GEN, "CVtUiVolumePopup.RefreshL ShowPopupL2" )
            ShowPopupL();
            }
        }
    __VTPRINTEXIT( "CVtUiVolumePopup.RefreshL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::DoActivateL()
// ---------------------------------------------------------------------------
//
void CVtUiVolumePopup::DoActivateL()
    {
    __VTPRINTENTER( "CVtUiVolumePopup.DoActivateL" )
    CVtUiPopupBase::DoActivateL();
    // In order to refresh softkey.
    iFeatureManager.AppUi().RefreshSoftkeysL();
    __VTPRINTEXIT( "CVtUiVolumePopup.DoActivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::OfferKeyEventL()
// ---------------------------------------------------------------------------
//
TKeyResponse CVtUiVolumePopup::OfferKeyEventL( const TKeyEvent& aEvent,
    TEventCode /*aCode*/ )
    {
    __VTPRINTENTER( "CVtUiVolumePopup.OfferKeyEventL" )
    TKeyResponse response( EKeyWasNotConsumed );
    TVtUiSideVolumeKeysVariation svkvariation;
    if ( !svkvariation.IsSideVolumeKeysSupported() &&
         ( aEvent.iScanCode == EStdKeyLeftArrow ||
           aEvent.iScanCode == EStdKeyRightArrow ) )
        {
        ShowPopupL();
        UpdateVolumeL();
        }
    __VTPRINTEXITR( "CVtUiVolumePopup.OfferKeyEventL %d", response )
    return response;
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::HandleControlEventL
// ---------------------------------------------------------------------------
//
void CVtUiVolumePopup::HandleControlEventL( CCoeControl* aControl,
    TCoeEvent aEventType )
    {
    __VTPRINTENTER( "CVtUiVolumePopup.HandleControlEventL" )
    CVtUiPopupBase::HandleControlEventL( aControl, aEventType );
    if ( aEventType == EEventStateChanged )
        {
        UpdateVolumeL();
        }
    __VTPRINTEXIT( "CVtUiVolumePopup.HandleControlEventL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::CVtUiVolumePopup
// ---------------------------------------------------------------------------
//
CVtUiVolumePopup::CVtUiVolumePopup( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPopupBase( aFeatureManager.ComponentManager(),
      TVtUiBlockListBitField(
        MVtUiComponent::EComponentIdToolbar |
        MVtUiComponent::EComponentIdNumberEntry |
        MVtUiComponent::EComponentIdZoom |
        MVtUiComponent::EVComponentIdContrast |
        MVtUiComponent::EVComponentIdBrightness ),
      EComponentIdVolume ),
      iModel( aFeatureManager.AppUi().Model() ), 
      iFeatureManager ( aFeatureManager ) 
    {
    __VTPRINTENTER( "CVtUiVolumePopup.CVtUiVolumePopup" )
    __VTPRINTEXIT( "CVtUiVolumePopup.CVtUiVolumePopup" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiVolumePopup::ConstructL()
    {
    __VTPRINTENTER( "CVtUiVolumePopup.ConstructL" )
    BaseConstructL();
    // set default value
    MVtEngAudio& audio( iModel.Audio() );
    MVtEngAudio::TAudioRoutingState audioRouting;
    User::LeaveIfError( audio.GetRoutingState( audioRouting ) );
    SetValue( OutputVolume( audioRouting ) );
    // set default audiorouting
    iAudioRouting = audioRouting;
    __VTPRINTEXIT( "CVtUiVolumePopup.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::OutputVolume
// ---------------------------------------------------------------------------
//
TInt CVtUiVolumePopup::OutputVolume(
    MVtEngAudio::TAudioRoutingState aRouting ) const
    {
    __VTPRINTENTER( "CVtUiVolumePopup.OutputVolume" )
    const MVtEngAudio& audio( iModel.Audio() );
    const TInt volume( audio.OutputVolume(
        !( aRouting == MVtEngAudio::EAudioLoudspeaker ) ) );
    __VTPRINTEXITR( "CVtUiVolumePopup.OutputVolume %d", volume )
    return volume;
    }

// ---------------------------------------------------------------------------
// CVtUiVolumePopup::UpdateVolumeL
// ---------------------------------------------------------------------------
//
void CVtUiVolumePopup::UpdateVolumeL()
    {
    __VTPRINTENTER( "CVtUiVolumePopup.UpdateVolumeL" )
    
    MVtEngAudio& audio( iModel.Audio() );
    MVtEngAudio::TAudioRoutingState audioRouting;
    User::LeaveIfError( audio.GetRoutingState( audioRouting ) );

    const TInt volume( OutputVolume( iAudioRouting ) );
    
    __VTPRINT2( DEBUG_GEN, "CVtUiVolumePopup.UpdateVolumeL volume = %d",
                volume )      
    __VTPRINT2( DEBUG_GEN, "CVtUiVolumePopup.UpdateVolumeL Value() = %d",
                Value() )                
    if ( volume != Value() )
        {
        MVtEngAudio::TVtEngOutputVolume newVolume;
        
        // Get current audio values from engine
        // and set new audio volume to right routing
        if ( iAudioRouting == MVtEngAudio::EAudioLoudspeaker )
            {
            __VTPRINT( DEBUG_GEN, "CVtUiVolumePopup.UpdateVolumeL.LS")
            // changed value
            newVolume.iHandsfreeVolume = Value();
            // old value
            TInt volume = audio.OutputVolume( ETrue );
            newVolume.iHandsetVolume = volume;
            }
        else
            {
            __VTPRINT( DEBUG_GEN, "CVtUiVolumePopup.UpdateVolumeL.HS")
            // changed value
            newVolume.iHandsetVolume = Value();
            // old value
            TInt volume = audio.OutputVolume( EFalse );
            newVolume.iHandsfreeVolume = volume;
            }
            
      iFeatureManager.AppUi().CmdUpdateVolumeL( newVolume );
      }
    __VTPRINTEXIT( "CVtUiVolumePopup.UpdateVolumeL" )    
    }

/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Toolbar hide item action class.
*
*/


#include <cvtlogger.h>
#include "cvtuihidetoolbaritemaction.h"
#include "tvtuicmdvalidatorcallback.h"
#include "tvtuitoolbarcommanditerator.h"
#include "cvtuitoolbarbase.h"
#include "videotelui.hrh"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiHideToolbarItemAction::NewL
// ---------------------------------------------------------------------------
//
CVtUiHideToolbarItemAction* CVtUiHideToolbarItemAction::NewL(
    CVtUiToolbarBase* aToolbar, const TVtUiStates& aUiStates )
    {
    __VTPRINTENTER( "HideTbAct.NewL" )
    CVtUiHideToolbarItemAction* self =
        new ( ELeave ) CVtUiHideToolbarItemAction( aToolbar, aUiStates );
    __VTPRINTEXIT( "HideTbAct.NewL" )
    return self;
	}

// ---------------------------------------------------------------------------
// CVtUiHideToolbarItemAction::~CVtUiHideToolbarItemAction
// ---------------------------------------------------------------------------
//
CVtUiHideToolbarItemAction::~CVtUiHideToolbarItemAction()
    {
    }

// ---------------------------------------------------------------------------
// CVtUiHideToolbarItemAction::ProcessL
// ---------------------------------------------------------------------------
//
void CVtUiHideToolbarItemAction::ProcessL(
    const MVtUiCmdValidatorCallBack& aCallBack )
    {
    __VTPRINTENTER( "HideTbAct.ProcessL" )
    for ( TVtUiToolbarCommandIterator i( *iToolbar ); i.HasNext(); )
        {
        TInt commandId( i.Next() );
    	if ( !IsCommandHandled( commandId ) )
    	    {
    	    __VTPRINT2( DEBUG_GEN, "HideTbAct.cb.call.cmddId=%d", commandId )
            if ( aCallBack.Call( commandId ) )  // primarypolicy 
                {                               // says can't be shown
        	    CommandHandledL( commandId );
        	    SetItemHiddenL( commandId );
                }
             else
                {
                HideOrShowToolbarControlL( commandId );
                }
    	    }
        }
    __VTPRINTEXIT( "HideTbAct.ProcessL" )
	}

// ---------------------------------------------------------------------------
// CVtUiHideToolbarItemAction::CVtUiHideToolbarItemAction
// ---------------------------------------------------------------------------
//
CVtUiHideToolbarItemAction::CVtUiHideToolbarItemAction
    ( CVtUiToolbarBase* aToolbar, const  TVtUiStates& aUiStates )
    : iToolbar( aToolbar ), iUiStates ( aUiStates )
    {
    __VTPRINTENTER( "HideTbAct.ctor" )    
    __VTPRINTEXIT( "HideTbAct.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiHideToolbarItemAction::SetItemHiddenL
// ---------------------------------------------------------------------------
//
void CVtUiHideToolbarItemAction::SetItemHiddenL( TInt aCommandId )
    {
    __VTPRINTENTER( "HideTbAct.SetItemHidden" )
    iToolbar->SetCmdIdVisibilityStateL( aCommandId, 
        CVtUiToolbarBase::EHidden );
    __VTPRINTEXIT( "HideTbAct.SetItemHidden" )
    }

// ---------------------------------------------------------------------------
// CVtUiHideToolbarItemAction::HideOrShowToolbarControlL
// ---------------------------------------------------------------------------
//
void CVtUiHideToolbarItemAction::HideOrShowToolbarControlL
     ( TInt aCommandId )
     {
     __VTPRINTENTER( "HideTbAct.HideOrShowToolbarControlL" )
     TBool isZoomModeOn = iUiStates.IsZoomModeOn();
     TBool isVolumeModeOn = iUiStates.IsVolumeModeOn();
     TBool isBrightnessModeOn = iUiStates.IsBrightnessModeOn();
     TBool isContrastModeOn = iUiStates.IsContrastModeOn();
     TBool dimmed = EFalse;
     const TVtUiMediaState& mediaState( iUiStates.MediaState() );
     const TVtUiAudioState& audioState( iUiStates.AudioState() );

     switch ( aCommandId )
            {
            case EVtUiCmdDisableVideo:
            case EVtUiCmdSwapImagesPlaces:
            case EVtUiCmdDisableAudio:
            case EVtUiCmdEnableAudio:
                if ( isContrastModeOn || 
                    isBrightnessModeOn
                    || isZoomModeOn || isVolumeModeOn )
                    {
                    dimmed = ETrue;
                    }
                break;
            case EVtUiCmdEnableVideo:
                if ( isZoomModeOn || isVolumeModeOn )        
                    {
                    dimmed = ETrue;
                    }             
                break;
                
            case EVtUiCmdUsePrimaryCamera:            
            case EVtUiCmdUseSecondaryCamera:
                if ( isContrastModeOn || 
                    isBrightnessModeOn
                    || iUiStates.IsCaptureModeOn() ||
                    mediaState.IsSharing()
                    || isZoomModeOn || isVolumeModeOn )        
                    {
                    dimmed = ETrue;
                    } 
                break;
            case EVtUiCmdZoom:
                if ( isContrastModeOn ||
                     isBrightnessModeOn||
                     !mediaState.IsVideo() ||
                     mediaState.IsFrozen() ||
                     mediaState.IsSharing() ||
                     isVolumeModeOn )
                     {
                     dimmed = ETrue;
                     }
                 break;
                 
            case EVtUiCmdShareObjectImage:
                if ( isContrastModeOn || 
                     isBrightnessModeOn ||
                     isZoomModeOn || mediaState.IsFrozen() ||
                     mediaState.IsVideoPermanentlyStopped() ||
                     isVolumeModeOn )
                     {
                     dimmed = ETrue;
                     } 
                break;

            case EVtUiCmdActivateBT:
                dimmed = !audioState.CanActivateBtHf() ||
                    audioState.IsAudioPermanentlyStopped() ||
                    isZoomModeOn || isContrastModeOn || 
                    isBrightnessModeOn ||
                    isVolumeModeOn ;
                break;

            case EVtUiCmdDeactivateLoudspeaker:
                dimmed = !audioState.CanDeactivateLoudspeaker() ||
                    audioState.IsAudioPermanentlyStopped() ||
                    isZoomModeOn || isContrastModeOn || 
                    isBrightnessModeOn ||
                    isVolumeModeOn;
                break;

            case EVtUiCmdSwitchFromBTToIHF:
                dimmed = !audioState.CanDeactivateBtHf() ||
                    !audioState.CanActivateLoudspeaker() ||
                    audioState.IsAudioPermanentlyStopped() ||
                    isZoomModeOn || isContrastModeOn || 
                    isBrightnessModeOn ||
                    isVolumeModeOn;
                break;

            case EVtUiCmdActivateLoudspeaker:
                dimmed = !audioState.CanActivateLoudspeaker() ||
                    audioState.IsAudioPermanentlyStopped() ||
                    isZoomModeOn || isContrastModeOn || 
                    isBrightnessModeOn ||
                    isVolumeModeOn;
                break;

            /*
            case EVtUiCmdSnapshot:
                 if ( iUiStates.IsContrastModeOn() || iUiStates.IsBrightnessModeOn ()
                      || isZoomModeOn || ( !iUiStates.MediaState().IsVideo() && 
                      !iUiStates.MediaState().IsFrozen() ) ||
                      !iUiStates.MediaState().IsFreezeSupported() || iUiStates.IsContrastModeOn() || 
                        iUiStates.IsBrightnessModeOn() || isVolumeModeOn )
                     {
                     dimmed = ETrue;
                     } 
                 break;
            */                 
            default:
                 dimmed = EFalse;
                break;
            }
            
     // update toolbar's commands visibility values
     if ( dimmed )
        {
        iToolbar->SetCmdIdVisibilityStateL( aCommandId, 
            CVtUiToolbarBase::EDimmed );
        }
     else
        {
        iToolbar->SetCmdIdVisibilityStateL( aCommandId, 
            CVtUiToolbarBase::EShown );
        }
     __VTPRINTEXIT( "HideTbAct.HideOrShowToolbarControlL" )
     }

// ---------------------------------------------------------------------------
// CVtUiHideToolbarItemAction::EndProcess
// ---------------------------------------------------------------------------
//
void CVtUiHideToolbarItemAction::EndProcess()
    {
    __VTPRINTENTER( "HideTbAct.EndProcess" )    
    TRAP_IGNORE( iToolbar->UpdateToolbarL() );
    __VTPRINTEXIT( "HideTbAct.EndProcess" )    
    }   
//  End of File

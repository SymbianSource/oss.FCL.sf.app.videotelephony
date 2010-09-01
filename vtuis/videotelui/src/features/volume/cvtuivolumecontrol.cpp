/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the cvtuivolumecontrol class.
*
*/


#include    "cvtuivolumecontrol.h"
#include    "MVtUiEngineCommandManager.h"
#include    <mvtengcommandhandler.h>
#include    <cvtlogger.h>
#include    "cvtuivolume.h"
#include    "cvtuifeaturemanager.h"

// -----------------------------------------------------------------------------
// CVtUiVolumeControl::CVtUiVolumeControl
// -----------------------------------------------------------------------------
//
CVtUiVolumeControl::CVtUiVolumeControl(
        MVtEngCommandHandler& aCommandHandler,
        MVtEngAudio& aAudio,
        MVtUiEngineCommandManager& aCommandManager,
        CVtUiFeatureManager& aFeatureManager )
    :  iCommandHandler( aCommandHandler ),
      iAudio( aAudio ),
      iCommandManager( aCommandManager ),
      iVolumePtr( (TUint8*)&iVolume, sizeof( TVolume ) ),
      iFeatureManager( aFeatureManager )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiVolumeControl::~CVtUiVolumeControl
// -----------------------------------------------------------------------------
//
CVtUiVolumeControl::~CVtUiVolumeControl()
    {
    if ( iIsActive )
        {
        iCommandHandler.CancelCommand( KVtEngSetAudioVolume ); // ignore error
        }
    iCommandManager.RemoveObserver( *this );               
    }

// -----------------------------------------------------------------------------
// CVtUiVolumeControl::ExecuteDialogLD
// -----------------------------------------------------------------------------
//
void CVtUiVolumeControl::ConstructL()
    {
    CleanupStack::PushL( this );
    iCommandManager.AddObserverL( *this );
    CleanupStack::Pop( this );
    }

// -----------------------------------------------------------------------------
// CVtUiVolumeControl::SetVoAdjustVolumeL
// -----------------------------------------------------------------------------
//
void CVtUiVolumeControl::AdjustVolumeL( TVolume aVolume  )
    {
    __VTPRINTENTER( "VtUiVolCtrl.AdjustVolumeL")
    if ( iIsActive )
        {
        __VTPRINTENTER( "VtUiVolCtrl.AdjustVolumeL.Isactive")
        return;
        }
    iIsActive = ETrue;         
    iVolume = aVolume;
    iCommandHandler.ExecuteL( KVtEngSetAudioVolume, &iVolumePtr );
    __VTPRINTEXIT( "VtUiVolCtrl.AdjustVolumeL")
    }

// -----------------------------------------------------------------------------
// CVtUiVolumeControl::HandleVTCommandPerformedL
// -----------------------------------------------------------------------------
//
void CVtUiVolumeControl::HandleVTCommandPerformedL(
        TVtEngCommandId aCommand,
        const TInt aError )
    {
    __VTPRINTENTER( "VtUiVolCtrl.HandleVTCommandPerformedL")
    if ( aCommand == KVtEngSetAudioVolume )
        {
        __VTPRINT( DEBUG_GEN, "VtUiVolCtrl.perf" )
        TInt error = aError;
        // If volume has been changed, then try to set volume again.
        //iIsActive = ETrue;
        if ( IsVolumeChangedL() )
            {
            __VTPRINT( DEBUG_GEN, "VtUiVolCtrl.retry" )
            TRAP( error,
               iCommandHandler.ExecuteL(
                   KVtEngSetAudioVolume,
                   &iVolumePtr ) );
            __VTPRINT2( DEBUG_GEN, "VtUiVolCtrl.err.%d", error )
            iIsActive = ( error == KErrNone );
            }
        else
            {
             __VTPRINT( DEBUG_GEN,
              "VtUiVolCtrl.HandleVTCommandPerformedL iIsActive = EFalse; " )
            iIsActive = EFalse; 
            }            
      
        }
    __VTPRINTEXIT( "VtUiVolCtrl.HandleVTCommandPerformedL")        
    }

// -----------------------------------------------------------------------------
// CVtUiVolumeControl::IsVolumeChangedL
// -----------------------------------------------------------------------------
//
TBool CVtUiVolumeControl::IsVolumeChangedL()
    {
    __VTPRINTENTER( "VtUiVolCtrl.IsVolumeChangedL" )
    MVtEngAudio::TAudioRoutingState audioRouting;
    User::LeaveIfError( iAudio.GetRoutingState( audioRouting ) );
    const TInt volume( iAudio.OutputVolume(
        !( audioRouting == MVtEngAudio::EAudioLoudspeaker ) ) );
     
    CVtUiVolume* vp = static_cast< CVtUiVolume* >(
    iFeatureManager.GetFeatureById( EVtUiFeatureIdVolume ) );
    TInt sliderVolume( volume );
    if ( vp )
        {
        sliderVolume = vp->GetVolumeValue();
        // update correct volume
        if ( audioRouting == MVtEngAudio::EAudioLoudspeaker )
            {
            __VTPRINT( DEBUG_GEN, "VtUiVolCtrl.IsVolumeChangedL.LS")
            iVolume.iHandsfreeVolume = sliderVolume;
            }
        else
            {
            __VTPRINT( DEBUG_GEN, "VtUiVolCtrl.IsVolumeChangedL.HS")
            iVolume.iHandsetVolume = sliderVolume;
            }
        }
        
    __VTPRINT2( DEBUG_GEN, "VtUiVolCtrl.vol %d", volume )        
    __VTPRINT2( DEBUG_GEN, "VtUiVolCtrl.slidvol %d", sliderVolume )
    __VTPRINTEXITR( "VtUiVolCtrl.IsVolumeChangedL %d", sliderVolume == volume )    
    return sliderVolume == volume ? EFalse : ETrue; 
    }
//  End of File

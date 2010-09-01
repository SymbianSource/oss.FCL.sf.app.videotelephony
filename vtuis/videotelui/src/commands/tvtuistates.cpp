/*
* Copyright (c) 2006 - 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Video UI states class.
*
*/


#include <cvtengmodel.h>
#include <mvtengcamerapreferences.h>
#include <cvtlogger.h>

#include "tvtuistates.h"

// -----------------------------------------------------------------------------
// TVtUiStates::TVtUiStates
// -----------------------------------------------------------------------------
//
TVtUiStates::TVtUiStates( CVtEngModel& aModel )
    : iMediaState( aModel.Media(), aModel.CommandHandler() ), iAudioState( aModel ),
    iModel( aModel ), iExecState( EExecStateStarting),
    iCommandActivatingRefCount( 0 )
    {
    // get camera preferences
    iCameraPref = static_cast<MVtEngCameraPreferences*>
        ( iModel.Extension( KVtEngExtensionCameraPreferences ) );
    }

// -----------------------------------------------------------------------------
// TVtUiStates::Update
// -----------------------------------------------------------------------------
//
void TVtUiStates::Update()
    {
    iMediaState.Update();
    iAudioState.Update();
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsColorToneSettingAvailable
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsColorToneSettingAvailable() const
    {
    __VTPRINTENTER( "TVtUiStates.IsColorToneSettingAvailable" )
    TUint32 supportedModes;
    // Get supported whitebalance modes
    if ( iCameraPref )
    	{
	    if ( iCameraPref->GetSupportedColorTones( supportedModes ) )
	        {
	        // error occured
	        __VTPRINTEXIT( "TVtUiStates.IsColorToneSettingAvailableErr" )
	        return EFalse;
	        }
    	}

    // Clean the flag, flags that are possible are
    // A bitfield of suported colortones
    // ENormal         = 0x00,
    // ESepia          = 0x01,
    // EGrayscale      = 0x02,
    // ENegative       = 0x04
    supportedModes &= 0x07;

    // If supported modes is 0 automatic,then return EFalse
    return supportedModes;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsWhiteBalanceSettingAvailable
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsWhiteBalanceSettingAvailable() const
    {
    __VTPRINTENTER( "TVtUiStates.IsWhiteBalanceSettingAvailable" )
    TUint32 supportedModes;
    // Get supported whitebalance modes
    if ( iCameraPref )
    	{
	    if ( iCameraPref->GetSupportedWhiteBalanceModes( supportedModes ) )
	        {
	        // error occured
	        __VTPRINTEXIT( "TVtUiStates.IsWhiteBalanceSettingAvailableErr" )
	        return EFalse;
	        }
    	}
    __VTPRINT2( DEBUG_GEN, "IsWhiteBalanceSettingAvailable=%d", supportedModes )
    // If supported modes is 0 ,then return EFalse
    __VTPRINTEXIT( "TVtUiStates.IsWhiteBalanceSettingAvailable2" )
 	return supportedModes;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsContrastSettingAvailable
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsContrastSettingAvailable() const
    {
    __VTPRINTENTER( "TVtUiStates.IsContrastSettingAvailable" )
    TBool ret( ETrue );
    if ( iCameraPref )
        {
        TInt temp;
	    ret = !iCameraPref->GetContrast( temp );
        }
    return ret;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::IsBrightnessSettingAvailable
// -----------------------------------------------------------------------------
//
TBool TVtUiStates::IsBrightnessSettingAvailable() const
    {
    __VTPRINTENTER( "TVtUiStates.IsBrightnessSettingAvailable" )
    TBool ret( ETrue );
    if ( iCameraPref )
	     {
	     TInt temp;
	     ret = !iCameraPref->GetBrightness( temp );
         }
    return ret;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetExecState
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetExecState( const TVtUiExecState aState )
    {
    iExecState = aState;
    }

// -----------------------------------------------------------------------------
// TVtUiStates::SetIsCommandActivating
// -----------------------------------------------------------------------------
//
void TVtUiStates::SetIsCommandActivating( TBool aSet )
    {
    if ( aSet )
        {
        iCommandActivatingRefCount++;
        }
    else if ( iCommandActivatingRefCount > 0 )
        {
        iCommandActivatingRefCount--;    
        }    
    }

// -----------------------------------------------------------------------------
// TVtUiStates::ExecState
// -----------------------------------------------------------------------------
//
TVtUiStates::TVtUiExecState TVtUiStates::ExecState() const
    {
    return iExecState;
    }

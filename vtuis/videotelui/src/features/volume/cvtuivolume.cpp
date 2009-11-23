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
* Description:  Volume feature implementation.
*
*/


#include    <cvtlogger.h>
#include    "cvtuivolume.h"
#include    "tvtuifeatureids.h"
#include    "cvtuivolumepopup.h"
#include    "cvtuifeaturemanager.h"
#include    "tvtuifeatureids.h"
#include    "tvtuistates.h"

// ---------------------------------------------------------------------------
// CVtUiVolume::NewL
// ---------------------------------------------------------------------------
//
CVtUiVolume* CVtUiVolume::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiVolume.NewL" )
    CVtUiVolume* self =
        new ( ELeave ) CVtUiVolume( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiVolume.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiVolume::~CVtUiVolume
// ---------------------------------------------------------------------------
//
CVtUiVolume::~CVtUiVolume()
    {
    __VTPRINTENTER( "CVtUiVolume.~" )
    __VTPRINTEXIT( "CVtUiVolume.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolume::RefreshL
// ---------------------------------------------------------------------------
//
void CVtUiVolume::RefreshL()
    {
    __VTPRINTENTER( "CVtUiVolume.RefreshL" )
    if ( State() == EActive )
        {
        __VTPRINT( DEBUG_GEN, "CVtUiPopupBase.RefreshL.EActive" )
        static_cast< CVtUiVolumePopup& >( Popup() ).RefreshL();
        }
    else
        {
        __VTPRINT( DEBUG_GEN, "CVtUiVolume.RefreshL.Else" )
        static_cast< CVtUiVolumePopup& >( Popup() ).UpdateVolumeAndRoutingL();
        }        
    __VTPRINTEXIT( "CVtUiVolume.RefreshL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolume::StartL
// ---------------------------------------------------------------------------
//
void CVtUiVolume::StartL()
    {
    __VTPRINTENTER( "CVtUiVolume.StartL" )
    // if brightness or contrast slider is active stop those
    MVtUiFeature* br = iFeatureManager.
    	GetFeatureById( EVtUiFeatureIdBrightness );
    if ( br && br->State() == EActive )
    	{
        __VTPRINT( DEBUG_GEN, "CVtUiPopupBase.StartL.br->Stop" )
    	br->Stop();
    	}
    
    MVtUiFeature* cr = iFeatureManager.
	GetFeatureById( EVtUiFeatureIdContrast );
		if ( cr && cr->State() == EActive )
			{
			__VTPRINT( DEBUG_GEN, "CVtUiPopupBase.StartL.cr->Stop" )
			cr->Stop();
			}

    if ( State() == EActive )
        {
        // need to refresh when already active to replenish the close timer
        RefreshL();
        }
    else
        {
        iFeatureManager.UiStates().SetIsFloatingToolbarVisible( ETrue );
        CVtUiSliderBase::StartL();
        iFeatureManager.UiStates().SetVolumeModeOn( ETrue );
        // Toolbar needs to be refreshed if contrat and brightness were dismissed
        
        }
    __VTPRINTEXIT( "CVtUiVolume.StartL" )
    }
    
// ---------------------------------------------------------------------------
// CVtUiVolume::Stop
// ---------------------------------------------------------------------------
//
void CVtUiVolume::Stop()
    {
    __VTPRINTENTER( "CVtUiVolume.Stop" )    	
    iFeatureManager.UiStates().SetVolumeModeOn( EFalse );
    CVtUiSliderBase::Stop();
    __VTPRINTEXIT( "CVtUiVolume.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolume::GetVolumeValue
// ---------------------------------------------------------------------------
//
TInt CVtUiVolume::GetVolumeValue()
    {
    __VTPRINTENTER( "CVtUiVolume.GetVolumeValue" )    	
    __VTPRINTEXITR( "CVtUiVolume.GetVolumeValue%d", Popup().Value() )
    return Popup().Value();
    }

// ---------------------------------------------------------------------------
// CVtUiVolume::CVtUiVolume
// ---------------------------------------------------------------------------
//
CVtUiVolume::CVtUiVolume( CVtUiFeatureManager& aFeatureManager )
    : CVtUiSliderBase( aFeatureManager, EVtUiFeatureIdVolume )
    {

    __VTPRINTENTER( "CVtUiVolume.CVtUiVolume" )
    __VTPRINTEXIT( "CVtUiVolume.CVtUiVolume" )
    }

// ---------------------------------------------------------------------------
// CVtUiVolume::CVtUiVolume
// ---------------------------------------------------------------------------
//
void CVtUiVolume:: ConstructL()
    {
    __VTPRINTENTER( "CVtUiVolume.ConstructL" )
    BaseConstructL();
    SetPopup( CVtUiVolumePopup::NewL( iFeatureManager ) );
    __VTPRINTEXIT( "CVtUiVolume.ConstructL" )
    }

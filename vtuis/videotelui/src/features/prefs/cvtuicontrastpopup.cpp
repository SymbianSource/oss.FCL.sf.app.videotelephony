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
* Description:  Implementation of Contrast popup
*
*/



#include    <AknVolumePopup.h>
#include    "cvtuicontrastpopup.h"
#include    <cvtlogger.h>
#include	"tvtuilocalvariation.h"
#include    <mvtengmedia.h>
#include    "mvtuicomponent.h"
#include    "CVtUiAppUi.h"
#include    <videotelui.mbg>
#include    <mvtengcamerapreferences.h>

// ---------------------------------------------------------------------------
// CVtUiContrastPopup::NewL
// ---------------------------------------------------------------------------
//
CVtUiContrastPopup* CVtUiContrastPopup::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiContrastPopup.NewL" )
    CVtUiContrastPopup* self =
        new ( ELeave ) CVtUiContrastPopup( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiContrastPopup.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiContrastPopup::~CVtUiContrastPopup
// ---------------------------------------------------------------------------
//
CVtUiContrastPopup::~CVtUiContrastPopup()
    {
    __VTPRINTENTER( "CVtUiContrastPopup.~" )
    __VTPRINTEXIT( "CVtUiContrastPopup.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiContrastPopup::CurrentValue
// ---------------------------------------------------------------------------
//
TInt CVtUiContrastPopup::CurrentValue()
    {
    __VTPRINTENTER( "CVtUiContrastPopup.CurrentValue" )
    // ask from engine current value
    TInt value;
    if ( iCameraPref->GetContrast( value) )
        {
        __VTPRINTEXIT( "CVtUiContrastPopup.CurrentValueERR" )
        return 0;
        }
    __VTPRINTEXIT( "CVtUiContrastPopup.CurrentValue" )
    return value;
    }    

// ---------------------------------------------------------------------------
// CVtUiContrastPopup::CVtUiContrastPopup
// ---------------------------------------------------------------------------
//
CVtUiContrastPopup::CVtUiContrastPopup( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPrefPopupBase( aFeatureManager, TVtUiBlockListBitField(
        MVtUiComponent::EComponentIdDialer |
        MVtUiComponent::EComponentIdToolbar |
        MVtUiComponent::EComponentIdNumberEntry |
        MVtUiComponent::EComponentIdVolume |
        MVtUiComponent::EComponentIdZoom |
        MVtUiComponent::EVComponentIdBrightness ), EVComponentIdContrast,
        KVtEngSetContrast ) 
    {
    __VTPRINTENTER( "CVtUiContrastPopup.CVtUiContrastPopup" )
    __VTPRINTEXIT( "CVtUiContrastPopup.CVtUiContrastPopup" )
    }
    
// ---------------------------------------------------------------------------
// CVtUiContrastPopup::CVtUiContrastPopup
// ---------------------------------------------------------------------------
//
void CVtUiContrastPopup::ConstructL()
    {
    __VTPRINTENTER( "CVtUiContrastPopup.ConstructL" )
    BaseConstructL();
    __VTPRINTEXIT( "CVtUiContrastPopup.ConstructL" )
    }

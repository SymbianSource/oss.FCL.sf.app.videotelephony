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
* Description:  implementation.
*
*/


#include    <cvtlogger.h>
#include    "cvtuicontrast.h"
#include    "tvtuifeatureids.h"
#include    "cvtuicontrastpopup.h"
#include    "cvtuipopupbase.h"
#include    "videotelui.hrh"
#include    "cvtuifeaturemanager.h"
#include    "tvtuistates.h"

// ---------------------------------------------------------------------------
// CVtUiContrast::NewL
// ---------------------------------------------------------------------------
//
CVtUiContrast* CVtUiContrast::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiContrast.NewL" )
    CVtUiContrast* self =
        new ( ELeave ) CVtUiContrast( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiContrast.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiContrast::~CVtUiContrast
// ---------------------------------------------------------------------------
//
CVtUiContrast::~CVtUiContrast()
    {
    __VTPRINTENTER( "CVtUiContrast.~" )
    __VTPRINTEXIT( "CVtUiContrast.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiContrast::StartL
// ---------------------------------------------------------------------------
//
void CVtUiContrast::StartL()
    {
    __VTPRINTENTER( "CVtUiContrast.StartL" )  
    CVtUiPrefSliderBase::StartL();
    iFeatureManager.UiStates().SetContrastModeOn( ETrue );
    __VTPRINTEXIT( "CVtUiContrast.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiContrast::Stop
// ---------------------------------------------------------------------------
//
void CVtUiContrast::Stop()
    {
 		__VTPRINTENTER( "CVtUiContrast.Stop" )    	
    CVtUiPrefSliderBase::Stop();
    iFeatureManager.UiStates().SetContrastModeOn( EFalse );
    __VTPRINTEXIT( "CVtUiContrast.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiContrast::CVtUiContrast
// ---------------------------------------------------------------------------
//
CVtUiContrast::CVtUiContrast( CVtUiFeatureManager& aFeatureManager )
    : CVtUiPrefSliderBase( aFeatureManager, EVtUiFeatureIdContrast )
    {
    __VTPRINTENTER( "CVtUiContrast.CVtUiContrast" )
    __VTPRINTEXIT( "CVtUiContrast.CVtUiContrast" )
    }

// ---------------------------------------------------------------------------
// CVtUiContrast::CVtUiContrast
// ---------------------------------------------------------------------------
//
void CVtUiContrast:: ConstructL()
    {
    __VTPRINTENTER( "CVtUiContrast.ConstructL" )
    BaseConstructL();
    SetPopup( CVtUiContrastPopup::NewL( iFeatureManager ) );
    __VTPRINTEXIT( "CVtUiContrast.ConstructL" )
    }

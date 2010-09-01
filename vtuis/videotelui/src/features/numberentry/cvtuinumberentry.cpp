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
* Description:  Number entry UI feature implementation.
*
*/


#include <cvtlogger.h>

#include "cvtuinumberentry.h"
#include "cvtuifeaturemanager.h"
#include "mvtuicommandmanager.h"
#include "mvtuicomponentmanager.h"
#include "mvtuicommandui.h"
#include "tvtuifeatureids.h"
#include "CVtUiNumberEntryControl.h"
#include "CVtUiAppUi.h"


// We need this to be able to make control's priority lower than activation
// control's priority is
extern const TInt KVtUiNumberEntryActivationPriority;

// Priority of number entry control.
const TInt KVtUiNumberEntryControlPriorityHidden =
    KVtUiNumberEntryActivationPriority - 1;

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::NewL
// ---------------------------------------------------------------------------
//
CVtUiNumberEntry* CVtUiNumberEntry::NewL(
    CVtUiFeatureManager& aFeatureManager )
    {
    __VTPRINTENTER( "NE.NewL" )
    CVtUiNumberEntry* self =
        new ( ELeave ) CVtUiNumberEntry( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "NE.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::~CVtUiNumberEntry
// ---------------------------------------------------------------------------
//
CVtUiNumberEntry::~CVtUiNumberEntry()
    {
    __VTPRINTENTER( "NE.~" )
    DeleteNumberEntryControl();
    __VTPRINTEXIT( "NE.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::StartL
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::StartL()
    {
    __VTPRINTENTER( "NE.StartL" )
    if ( State() == MVtUiFeature::EUnprepared )
        {
        PrepareL();
        iFeatureManager.ComponentManager().RequestActivationL(
            MVtUiComponent::EComponentIdNumberEntry );
        iFeatureState = MVtUiFeature::EActive;
        }
    __VTPRINTEXIT( "NE.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::Stop
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::Stop()
    {
    __VTPRINTENTER( "NE.Stop" )
    if ( State() == MVtUiFeature::EActive )
        {
        TRAP_IGNORE( iFeatureManager.ComponentManager().DeActivateComponentL(
            MVtUiComponent::EComponentIdNumberEntry ) );
        iFeatureState = MVtUiFeature::EReady;
        }
    Unprepare();
    __VTPRINTEXIT( "NE.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::InitFeatureL()
    {
    __VTPRINTENTER( "NE.InitFeatureL" )
    CreateNumberEntryControlL();
    __VTPRINTEXIT( "NE.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::ControlActivated
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::ControlActivatedL()
    {
    __VTPRINTENTER( "NE.ControlActivatedL" )
    __VTPRINTEXIT( "NE.ControlActivatedL" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::ControlDeactivated
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::ControlDeactivated()
    {
    __VTPRINTENTER( "NE.ControlDeactivated" )
    __VTPRINTEXIT( "NE.ControlDeactivated" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::CVtUiNumberEntry
// ---------------------------------------------------------------------------
//
CVtUiNumberEntry::CVtUiNumberEntry( CVtUiFeatureManager& aFeatureManager )
    : CVtUiFeatureBase( EVtUiFeatureIdNumberEntry, aFeatureManager )
    {
    __VTPRINTENTER( "NE.ctor" )
    __VTPRINTEXIT( "NE.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::ConstructL()
    {
    __VTPRINTENTER( "NE.ConstructL" )
    BaseConstructL();
    __VTPRINTEXIT( "NE.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::PrepareL
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::PrepareL()
    {
    __VTPRINTENTER( "NE.PrepareL" )
    iNumberEntryControl->SetNumberEntryControlObserver( this );
    iNumberEntryControl->RegisterComponentL(
        iFeatureManager.ComponentManager() );
    iFeatureManager.AppUi().AddToStackL( iNumberEntryControl,
        KVtUiNumberEntryControlPriorityHidden, ECoeStackFlagRefusesFocus );
    iFeatureState = MVtUiFeature::EReady;
    __VTPRINTEXIT( "NE.PrepareL" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::Unprepare()
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::Unprepare()
    {
    __VTPRINTENTER( "NE.Unprepare" )
    if ( iFeatureState > MVtUiFeature::EUnprepared )
	    {
	    iNumberEntryControl->SetNumberEntryControlObserver( NULL );
	    iFeatureManager.AppUi().RemoveFromStack( iNumberEntryControl );
	    iNumberEntryControl->UnregisterComponent(
	        iFeatureManager.ComponentManager() );
	    iFeatureState = MVtUiFeature::EUnprepared;
	  	}
    __VTPRINTEXIT( "NE.Unprepare" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::CreateNumberEntryControlL
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::CreateNumberEntryControlL()
    {
    __VTPRINTENTER( "NE.CreateNumberEntryControlL" )
    iNumberEntryControl = new ( ELeave ) CVtUiNumberEntryControl( *this,
        iFeatureManager.UiStates() );
    iNumberEntryControl->ConstructL( TRect() );
    iNumberEntryControl->SetMopParent( &iFeatureManager.AppUi() );
    __VTPRINTEXIT( "NE.CreateNumberEntryControlL" )
    }

// ---------------------------------------------------------------------------
// CVtUiNumberEntry::DeleteNumberEntryControl
// ---------------------------------------------------------------------------
//
void CVtUiNumberEntry::DeleteNumberEntryControl()
    {
    __VTPRINTENTER( "NE.DeleteNumberEntryControl" )
    delete iNumberEntryControl;
    iNumberEntryControl = NULL;
    iFeatureState = MVtUiFeature::EUnprepared;
    __VTPRINTEXIT( "NE.DeleteNumberEntryControl" )
    }

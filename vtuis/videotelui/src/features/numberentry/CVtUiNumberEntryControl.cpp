/*
* Copyright (c) 2004-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiNumberEntryControl control class.
*
*/


// INCLUDE FILES
#include    "CVtUiNumberEntryControl.h"
#include    "VtUiLayout.h"
#include    "VtUiUtility.h"
#include    "mvtuicomponentmanager.h"
#include    "tvtuistates.h"
#include    "tvtuiwsevent.h"
#include    "mvtuifeature.h"
#include    "mvtuinumberentrycontrolobserver.h"
#include    "cvtuidtmfbuffer.h"

#include    <aknsutils.h>
#include    <cvtlogger.h>
#include    <eikenv.h>

// CONSTANTS

// ============================ MEMBER FUNCTIONS ===============================

// Implementation for TVtUiNumberEntryComponentState

// -----------------------------------------------------------------------------
// TVtUiNumberEntryComponentState::TVtUiNumberEntryComponentState
// -----------------------------------------------------------------------------
//
TVtUiNumberEntryComponentState::TVtUiNumberEntryComponentState(
    MVtUiComponent& aComponent )
    : TVtUiComponentState( aComponent,
        TVtUiBlockListBitField(
            MVtUiComponent::EComponentIdDialer ) )
    {
    }

// Implementation for CVtUiNumberEntryControl

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::CVtUiNumberEntryControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiNumberEntryControl::CVtUiNumberEntryControl(
        MVtUiFeature& aFeature,
        TVtUiStates& aUiStates )
    : iFeature( aFeature ),
      iComponentState( *this ),
      iUiStates( aUiStates )
    {
    __VTPRINTENTER( "NECtrl.ctor" )
    __VTPRINTEXIT( "NECtrl.ctor" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::ConstructL( const TRect& aRect )
    {
    __VTPRINTENTER( "NECtrl.ConstructL" )
    CreateWindowL();
    SetRect( aRect );
    ActivateL();
    MakeVisible( EFalse );
    iInputBuffer = CVtUiDTMFBuffer::NewL( *iCoeEnv );
    __VTPRINTEXIT( "NECtrl.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::~CVtUiNumberEntryControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiNumberEntryControl::~CVtUiNumberEntryControl()
    {
    __VTPRINTENTER( "NECtrl.~" )
    AknsUtils::DeregisterControlPosition( this );
    delete iInputBuffer;
    __VTPRINTEXIT( "NECtrl.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::OpenNumberEntry
// -----------------------------------------------------------------------------
//
TBool CVtUiNumberEntryControl::OpenNumberEntry()
    {
    __VTPRINTENTER( "NECtrl.OpenNumberEntry" )
    TBool result( EFalse );
    if ( !iUiStates.IsNumberEntryOpen() )
        {
        __VTPRINT( DEBUG_GEN, "VtUiNumberEntry.OPEN" )
        iInputBuffer->Activate();
        iUiStates.SetIsNumberEntryOpen( ETrue );
        result = ETrue;
        }
    __VTPRINTEXITR( "NECtrl.OpenNumberEntry %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::IsNumberEntryOpen
// -----------------------------------------------------------------------------
//
TBool CVtUiNumberEntryControl::IsNumberEntryOpen() const
    {
    __VTPRINTENTER( "NECtrl.IsNumberEntryOpen" )
    const TBool result( iUiStates.IsNumberEntryOpen() );
    __VTPRINTEXITR( "NECtrl.IsNumberEntryOpen %d",result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::CloseNumberEntry
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::CloseNumberEntry()
    {
    __VTPRINTENTER( "NECtrl.CloseNumberEntry" )
    if ( iUiStates.IsNumberEntryOpen() )
        {
        __VTPRINT( DEBUG_GEN, "NECtrl.CloseNumberEntry CLOSE" )
        iUiStates.SetIsNumberEntryOpen( EFalse );
        iInputBuffer->Deactivate();
        }
    __VTPRINTEXIT( "NECtrl.CloseNumberEntry" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::RegisterComponentL
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::RegisterComponentL(
    MVtUiComponentManager& aComponentManager )
    {
    __VTPRINTENTER( "NECtrl.RegisterComponentL" )
    User::LeaveIfError( aComponentManager.ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::ERegister ) );
    __VTPRINTEXIT( "NECtrl.RegisterComponentL" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::UnregisterComponent
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::UnregisterComponent(
    MVtUiComponentManager& aComponentManager )
    {
    __VTPRINTENTER( "NECtrl.UnregisterComponent" )
    iInputBuffer->Reset();
    aComponentManager.ChangeComponentRegistration( iComponentState,
        MVtUiComponentManager::EUnregister );
    __VTPRINTEXIT( "NECtrl.UnregisterComponent" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::SetNumberEntryControlObserver
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::SetNumberEntryControlObserver(
    MVtUiNumberEntryControlObserver* aObserver )
    {
    __VTPRINTENTER( "NECtrl.SetNumberEntryControlObserver" )
    iControlObserver = aObserver;
    __VTPRINTEXIT( "NECtrl.SetNumberEntryControlObserver" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CVtUiNumberEntryControl::OfferKeyEventL(
        const TKeyEvent& aKeyEvent,
        TEventCode )
    {
    __VTPRINTENTER( "NECtrl.OfferKeyEventL" )

    TKeyResponse resp( EKeyWasNotConsumed );

    if ( IsDisplayingMenuOrDialog() ||
        aKeyEvent.iCode == EKeyLeftArrow ||
        aKeyEvent.iCode == EKeyRightArrow ||
        aKeyEvent.iCode == EKeyUpArrow ||
        aKeyEvent.iCode == EKeyDownArrow ||
        aKeyEvent.iCode == EKeyBackspace ||
        aKeyEvent.iCode == EKeyZoomIn ||
        aKeyEvent.iCode == EKeyZoomOut ||
        aKeyEvent.iScanCode == EStdKeyUpArrow ||
        aKeyEvent.iScanCode == EStdKeyDownArrow ||
        aKeyEvent.iScanCode == EStdKeyLeftArrow ||
        aKeyEvent.iScanCode == EStdKeyRightArrow )
        {
        return resp;
        }

    TChar dtmfTone;
    if ( VtUiUtility::IsDTMFEvent( aKeyEvent, dtmfTone ) )
        {
        iInputBuffer->Append( dtmfTone );
        }

    __VTPRINTEXITR( "NECtrl.OfferKeyEvent %d", resp )
    return resp;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::DoCloseNumberEntry
// -----------------------------------------------------------------------------
//
TInt CVtUiNumberEntryControl::DoCloseNumberEntry( TAny* aAny )
    {
    __VTPRINTENTER( "NECtrl.DoCloseNumberEntry" )
    CVtUiNumberEntryControl* self =
        reinterpret_cast< CVtUiNumberEntryControl* >( aAny );
    self->HandleTimeoutCloseNumberEntry();
    __VTPRINTEXIT( "NECtrl.DoCloseNumberEntry" )
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::HandleTimeoutCloseNumberEntry
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::HandleTimeoutCloseNumberEntry()
    {
    __VTPRINTENTER( "NECtrl.HandleTimeoutCloseNumberEntry" )
    __VTPRINTEXIT( "NECtrl.HandleTimeoutCloseNumberEntry" )
    iFeature.Stop();
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::IsDisplayingMenuOrDialog
// -----------------------------------------------------------------------------
//
TBool CVtUiNumberEntryControl::IsDisplayingMenuOrDialog() const
    {
    __VTPRINTENTER( "NECtrl.IsDisplayingMenuOrDialog" )
    CEikMenuBar* menuBar = iEikonEnv->AppUiFactory()->MenuBar();
    const TBool result( CCoeEnv::Static()->AppUi()->IsDisplayingDialog() ||
        ( menuBar && menuBar->IsDisplayed() ) );
    __VTPRINTEXITR( "NECtrl.IsDisplayingMenuOrDialog %d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::ComponentId
// -----------------------------------------------------------------------------
//
MVtUiComponent::TComponentId CVtUiNumberEntryControl::ComponentId() const
    {
    __VTPRINTENTER( "NECtrl.ComponentId" )
    __VTPRINTEXIT( "NECtrl.ComponentId" )
    return MVtUiComponent::EComponentIdNumberEntry;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::ComponentAsControl
// -----------------------------------------------------------------------------
//
CCoeControl* CVtUiNumberEntryControl::ComponentAsControl()
    {
    __VTPRINTENTER( "NECtrl.ComponentAsControl" )
    __VTPRINTEXIT( "NECtrl.ComponentAsControl" )
    return this;
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::DoActivateL
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::DoActivateL()
    {
    __VTPRINTENTER( "NECtrl.DoActivateL" )
    OpenNumberEntry();
    if ( iControlObserver )
        {
        iControlObserver->ControlActivatedL();
        }
    __VTPRINTEXIT( "NECtrl.DoActivateL" )
    }

// -----------------------------------------------------------------------------
// CVtUiNumberEntryControl::DoDeactivateL
// -----------------------------------------------------------------------------
//
void CVtUiNumberEntryControl::DoDeactivateL()
    {
    __VTPRINTENTER( "NECtrl.DoDeactivateL" )
    CloseNumberEntry();
    if ( iControlObserver )
        {
        iControlObserver->ControlDeactivated();
        }
    __VTPRINTEXIT( "NECtrl.DoDeactivateL" )
    }

//  End of File

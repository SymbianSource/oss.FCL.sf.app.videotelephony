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
* Description:  Dialer feature
*
*/


#include    <cvtlogger.h>
#include    <cvideodtmfdialer.h>
#include    <AknsDrawUtils.h>
#include    <AknsUtils.h>
#include    <aknlayoutscalable_apps.cdl.h>
#include    <aknlayoutscalable_avkon.cdl.h>
#include    <layoutmetadata.cdl.h>
#include    <featmgr.h>
#include    <AknsBasicBackgroundControlContext.h>

#include    "VtUiUtility.h"
#include    "VtUiLayout.h"
#include    "mvtuicomponentmanager.h"
#include    "cvtuidialercontainer.h"
#include    "cvtuidialervideocontrol.h"
#include    "tvtuiwsevent.h"
#include    "tvtuistates.h"
#include    "cvtuidialerskmodifier.h"
#include    "cvtuifeaturemanager.h"
#include    "CVtUiAppUi.h"
#include    "mvtuicommandmanager.h"
#include    "cvtuidtmfbuffer.h"

// Index of white color.
const TInt KVtUiColorWhite = 0;

// Implementation of TVtUiMiniDialerComponentState

// ---------------------------------------------------------------------------
// TVtUiDialerComponentState::TVtUiDialerComponentState
// ---------------------------------------------------------------------------
//
TVtUiDialerComponentState::TVtUiDialerComponentState(
    MVtUiComponent& aComponent ) :
    TVtUiComponentState( aComponent,
        TVtUiBlockListBitField(
            MVtUiComponent::EComponentIdToolbar |
            MVtUiComponent::EComponentIdNumberEntry ) )
    {
    }

// Implementation of CVtUiDialerContainer

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::NewL
// ---------------------------------------------------------------------------
//
CVtUiDialerContainer* CVtUiDialerContainer::NewL(
    CVtUiFeatureManager& aFeatureManager )
    {
    __VTPRINTENTER( "DialContainer.NewL" )
    CVtUiDialerContainer* self =
        new ( ELeave ) CVtUiDialerContainer( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL( aFeatureManager.AppUi().BitmapManager() );
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "DialContainer.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::~CVtUiDialerContainer
// ---------------------------------------------------------------------------
//
CVtUiDialerContainer::~CVtUiDialerContainer()
    {
    __VTPRINTENTER( "DialContainer.~" )
    delete iAsyncDeactivate;
    delete iVideoControl;
    delete iDialer;
    delete iSKModifier;
    delete iInputBuffer;
    delete iBgContext;
    AknsUtils::DeregisterControlPosition( this );
    __VTPRINTEXIT( "DialContainer.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::HandleResourceChangeL
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::HandleResourceChangeL( TInt aType )
    {
    __VTPRINTENTER( "DialContainer.HandleResourceChangeL" )
    switch ( aType )
        {
    case KEikDynamicLayoutVariantSwitch:
    case KAknsMessageSkinChange:
        LayoutDialerContainer();
        break;
    default:
        break;
        }
    __VTPRINTEXIT( "DialContainer.HandleResourceChangeL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::ComponentId
// ---------------------------------------------------------------------------
//
MVtUiComponent::TComponentId CVtUiDialerContainer::ComponentId() const
    {
    return EComponentIdDialer;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::ComponentAsControl
// ---------------------------------------------------------------------------
//
CCoeControl* CVtUiDialerContainer::ComponentAsControl()
    {
    return iVideoControl;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::DoActivateL
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::DoActivateL()
    {
    __VTPRINTENTER( "DialContainer.DoActivateL" )
    iUiStates.SetIsDialerActivating( EFalse );
    LayoutDialerContainer();
    Reset();
    iVideoControl->MakeVisible( ETrue );
    iDialer->MakeVisible( ETrue );
    MakeVisible( ETrue );
    User::LeaveIfError( iFeatureManager->
        CommandManager().AddCommandModifier( *iSKModifier ) );
    iInputBuffer->Activate();
    iMode = CVtUiAppUi::ERenderingModeDialer;
    TVtUiWsEvent< CVtUiAppUi::TRenderingMode > renderingEvent(
        EVtUiWsEventBeginRenderingMode, &iMode );
    iCoeEnv->WsSession().SendEventToWindowGroup(
        Window().WindowGroupId(), renderingEvent );
    iUiStates.SetIsDialerOpen( ETrue );
    iAsyncDeactivate->Cancel();
    __VTPRINTEXIT( "DialContainer.DoActivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::DoDeactivateL
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::DoDeactivateL()
    {
    __VTPRINTENTER( "DialContainer.DoDeactivateL" )
    iFeatureManager->CommandManager().
        RemoveCommandModifier( *iSKModifier );
    iUiStates.SetIsDialerOpen( EFalse );
    iVideoControl->MakeVisible( EFalse );
    iDialer->MakeVisible( EFalse );
    MakeVisible( EFalse );
    Reset();
    iInputBuffer->Deactivate();
    iAsyncDeactivate->CallBack();
    __VTPRINTEXIT( "DialContainer.DoDeactivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::GetContents
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::GetContents( TDes& aContents ) const
    {
    __VTPRINTENTER( "DialContainer.GetContents" )
    iInputBuffer->GetContents( aContents );
    __VTPRINTEXIT( "DialContainer.GetContents" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::OfferKeyEventL
// ---------------------------------------------------------------------------
//
TKeyResponse CVtUiDialerContainer::OfferKeyEventL( const TKeyEvent& aEvent,
    TEventCode aType )
    {
    __VTPRINTENTER( "DialContainer.OfferKeyEventL" )
    TKeyResponse response( EKeyWasNotConsumed );
    TChar dtmfTone;
    if ( VtUiUtility::IsDTMFEvent( aEvent, dtmfTone ) &&
         ( aType == EEventKey ) )
        {
        response = EKeyWasConsumed;
        AppendDigit( dtmfTone );
        }
    __VTPRINTEXIT( "DialContainer.OfferKeyEventL" )
    return response;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::Draw
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::Draw( const TRect& ) const
    {
    __VTPRINTENTER( "DialContainer.Draw" )
    CWindowGc& gc( SystemGc() );
    gc.SetBrushStyle( CWindowGc::ESolidBrush );
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushColor( AKN_LAF_COLOR( KVtUiColorWhite ) );
    gc.Clear();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, cc, this, gc, Rect() );
    __VTPRINTEXIT( "DialContainer.Draw" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::SizeChanged
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::SizeChanged()
    {
    __VTPRINTENTER( "DialContainer.SizeChanged" )
    TRect bgRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, bgRect );
    iBgContext->SetRect( bgRect );

    AknsUtils::RegisterControlPosition( this );
    CCoeControl::SizeChanged();
    __VTPRINTEXIT( "DialContainer.SizeChanged" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::PositionChanged
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::PositionChanged()
    {
    __VTPRINTENTER( "DialContainer.PositionChanged" )
    AknsUtils::RegisterControlPosition( this );
    CCoeControl::PositionChanged();
    __VTPRINTEXIT( "DialContainer.PositionChanged" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::CountComponentControls
// ---------------------------------------------------------------------------
//
TInt CVtUiDialerContainer::CountComponentControls() const
    {
    return iDialer ? 1 : 0;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::ComponentControl
// ---------------------------------------------------------------------------
//
CCoeControl* CVtUiDialerContainer::ComponentControl( TInt aIndex ) const
    {
    CCoeControl* result = NULL;
    switch ( aIndex )
        {
    case 0:
        result = iDialer;
        break;
    default:
        break;
        }
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::CVtUiDialerContainer
// ---------------------------------------------------------------------------
//
CVtUiDialerContainer::CVtUiDialerContainer(
    CVtUiFeatureManager& aFeatureManager ) :
    iComponentState( *this ),
    iFeatureManager( &aFeatureManager ),
    iComponentManager( &aFeatureManager.ComponentManager() ),
    iUiStates( aFeatureManager.UiStates() )
    {
    __VTPRINTENTER( "DialContainer.ctor" )
    __VTPRINTEXIT( "DialContainer.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::ConstructL( CVtUiBitmapManager& aBitmapManager )
    {
    __VTPRINTENTER( "DialContainer.ConstructL" )
    iBgContext = CAknsBasicBackgroundControlContext::NewL(
                      KAknsIIDQsnBgScreen, Rect(), ETrue );
    CreateWindowL();
    DrawableWindow()->SetPointerGrab( ETrue );
    SetExtent( TPoint(), TSize() );
    ActivateL();
    MakeVisible( EFalse );
    iInputBuffer = CVtUiDTMFBuffer::NewL( *iCoeEnv );
    iVideoControl = CVtUiDialerVideoControl::NewL( aBitmapManager );
    iDialer = CVideoDTMFDialer::NewL( *this, *iVideoControl, DialerRect() );
    iSKModifier = CVtUiDialerSKModifier::NewL( *iFeatureManager );
    // Disable fading when using DP (eliminates nasty color error)
    if ( FeatureManager::FeatureSupported( KFeatureIdDisplayPost ) )
        {
        Window().SetNonFading( ETrue );
        }
    iAsyncDeactivate = new ( ELeave ) CAsyncCallBack(
        TCallBack( ASyncDoDeactivate, this ), CActive::EPriorityLow );
    __VTPRINTEXIT( "DialContainer.ConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::RegisterComponentL
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::RegisterComponentL()
    {
    __VTPRINTENTER( "DialContainer.RegisterComponentL" )
    User::LeaveIfError( iComponentManager->ChangeResourceChangeRegistration(
        *this, MVtUiComponentManager::ERegister ) );
    User::LeaveIfError(
        iComponentManager->ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::ERegister ) );
    User::LeaveIfError( iComponentManager->ChangeKeyEventRegistration(
        *this, MVtUiComponentManager::ERegister ) );
    __VTPRINTEXIT( "DialContainer.RegisterComponentL" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::UnregisterComponent
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::UnregisterComponent()
    {
    __VTPRINTENTER( "DialContainer.UnregisterComponent" )
    iComponentManager->ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::EUnregister );
    iComponentManager->ChangeResourceChangeRegistration(
        *this, MVtUiComponentManager::EUnregister );
    iComponentManager->ChangeKeyEventRegistration(
        *this, MVtUiComponentManager::EUnregister );
    __VTPRINTEXIT( "DialContainer.UnregisterComponent" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::UnregisterComponent
// ---------------------------------------------------------------------------
//
MVtUiVideoWindow* CVtUiDialerContainer::ComponentAsVideoWindow()
    {
    __VTPRINTENTER( "DialContainer.ComponentAsVideoWindow" )
    __VTPRINTEXIT( "DialContainer.ComponentAsVideoWindow" )
    return iVideoControl;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::LayoutDialerContainer
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::LayoutDialerContainer()
    {
    __VTPRINTENTER( "DialContainer.LayoutDialerContainer" )

    TAknWindowLineLayout mainPaneLL;

    if ( Layout_Meta_Data::IsLandscapeOrientation() )
        {
        // Landscape: Option11 (thin status pane, lsc)
        mainPaneLL = AknLayoutScalable_Apps::main_pane( 15 ).LayoutLine();
        }
    else
        {
        // Portrait: main pane with status pane off, control pane on
        mainPaneLL = AknLayoutScalable_Apps::main_pane( 12 ).LayoutLine();
        }

    TRect appWinRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EApplicationWindow,
        appWinRect );

    // Layout container
    AknLayoutUtils::LayoutControl( this, appWinRect, mainPaneLL );

    // Layout dialer
    const TInt variety( Layout_Meta_Data::IsLandscapeOrientation() ?
        1 : 0 );
    TAknWindowLineLayout dialerLLout(
        AknLayoutScalable_Apps::main_video_tele_dialer_pane(
            variety ).LayoutLine() );
    AknLayoutUtils::LayoutControl( iDialer, Rect(), dialerLLout );

    // Layout video control
    AknLayoutUtils::LayoutControl( iVideoControl, iDialer->Rect(),
         AknLayoutScalable_Apps::video_down_pane_cp(
            variety ).LayoutLine() );

    __VTPRINTEXIT( "DialContainer.LayoutDialerContainer" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::DialerRect
// ---------------------------------------------------------------------------
//
TRect CVtUiDialerContainer::DialerRect() const
    {
    __VTPRINTENTER( "DialContainer.DialerRect" )
    TRect mainPaneRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane,
        mainPaneRect );
    __VTPRINTEXIT( "DialContainer.DialerRect" )
    return mainPaneRect;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::Reset
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::Reset()
    {
    __VTPRINTENTER( "DialContainer.Reset" )
    iInputBuffer->Reset();
    __VTPRINTEXIT( "DialContainer.Reset" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::AppendDigit
// ---------------------------------------------------------------------------
//
void CVtUiDialerContainer::AppendDigit( TChar aDigit )
    {
    __VTPRINTENTER( "DialContainer.AppendDigit" )
    iInputBuffer->Append( aDigit );
    __VTPRINTEXIT( "DialContainer.AppendDigit" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::MopSupplyObject
// ---------------------------------------------------------------------------
//
TTypeUid::Ptr CVtUiDialerContainer::MopSupplyObject( TTypeUid aId )
 {
     __VTPRINTENTER( "CVtUiDialerContainer.MopSupplyObject" )
 // Required during rendering of the background skin in Draw()
 if (aId.iUid == MAknsControlContext::ETypeId)
     {
      __VTPRINTEXIT( "CVtUiDialerContainer.MopSupplyObject.1" )
     return MAknsControlContext::SupplyMopObject( aId, iBgContext );
     }
    __VTPRINTEXIT( "CVtUiDialerContainer.MopSupplyObject.2" )
 return CCoeControl::MopSupplyObject( aId );
 }

// ---------------------------------------------------------------------------
// CVtUiDialerContainer::ASyncDoDeactivate
// ---------------------------------------------------------------------------
//
TInt CVtUiDialerContainer::ASyncDoDeactivate( TAny* aSelf )
    {
    __VTPRINTENTER( "DialContainer.ASyncDoDeactivate" )
    CVtUiDialerContainer* self =
        reinterpret_cast< CVtUiDialerContainer* >( aSelf );
    self->iMode = CVtUiAppUi::ERenderingModeDialer;
    TVtUiWsEvent< CVtUiAppUi::TRenderingMode > renderingEvent(
        EVtUiWsEventEndRenderingMode, &self->iMode );
    self->iCoeEnv->WsSession().SendEventToWindowGroup(
        self->Window().WindowGroupId(), renderingEvent );
    __VTPRINTEXIT( "DialContainer.ASyncDoDeactivate" )
    return KErrNone;
    }

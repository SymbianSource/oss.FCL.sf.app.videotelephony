/*
* Copyright (c) 2004, 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiContextControl control class.
*
*/



// INCLUDE FILES
#include    "CVtUiContextControl.h"
#include    "VtUiLayout.h"
#include    <aknsutils.h>
#include    <aknsdrawutils.h>
#include    <cvtlogger.h>
#include    <featmgr.h>
#include    "CVtUiAppUi.h"
#include    "tvtuistates.h"
#include    <aknsutils.h>
#include	"tVtuifeaturevariation.h"


// -----------------------------------------------------------------------------
// CVtUiContextControl::NewL
// Constructor that may leave.
// -----------------------------------------------------------------------------
//
CVtUiContextControl* CVtUiContextControl::NewL(
    CVtUiBitmapManager& aBitmapManager, CVtUiAppUi& aAppUi,
    TVtUiStates& aUiStates)
    {
    __VTPRINTENTER( "CtxCtrl.NewL" )
    CVtUiContextControl* self = new ( ELeave ) CVtUiContextControl(
        aBitmapManager, aAppUi, aUiStates );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "CtxCtrl.NewL" )
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::~CVtUiContextControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiContextControl::~CVtUiContextControl()
    {
    __VTPRINTENTER( "CtxCtrl.~" )
    BitmapManager().RemoveBitmap( iBackgroundId );
    BitmapManager().RemoveBitmap( iBlindId );
    BitmapManager().RemoveBitmap( iBlindMaskId );
    if ( iAppUi.EventMonitor() )
        {
        iAppUi.EventMonitor()->RemoveObserver( this );
        }
    __VTPRINTEXIT( "CtxCtrl.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CVtUiContextControl::HandlePointerEventL(
    const TPointerEvent& aPointerEvent)
    {
    __VTPRINTENTER( "CtxCtrl.HandlePointerEventL" )
    __VTPRINT2( DEBUG_GEN, "CtxCtrl.HandlePtr  ok= %d", iOkToSwapOnButtonUp )
    if ( AknLayoutUtils::PenEnabled() )
        {
        if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
            {
            TRect window( Size() );
            if ( !window.Contains( aPointerEvent.iPosition ) )
                {
                iOkToSwapOnButtonUp = ETrue;
                SetGloballyCapturing( EFalse );
                SetPointerCapture( EFalse); 
                }
            else if( iOkToSwapOnButtonUp )
                {
                 if ( !iUiStates.IsWhiteBalanceModeOn() &&
                      !iUiStates.IsColorToneModeOn() &&
                      !iUiStates.IsZoomModeOn() &&
                      !iUiStates.IsCaptureModeOn() &&
                      !iUiStates.IsContrastModeOn() &&
                      !iUiStates.IsBrightnessModeOn() &&
                      !iUiStates.IsVolumeModeOn() )
                        {
                        if ( !( iAppUi.CanSwapImagePlaces() ) )
                            {
                            return;
                            }	
                        iAppUi.HandleCommandL( EVtUiCmdSwapImagesPlaces );
                        }
                }
            else
                {
                SetGloballyCapturing( EFalse );
                SetPointerCapture( EFalse); 
                iOkToSwapOnButtonUp = ETrue;
                }
            }
        }
    __VTPRINTEXIT( "CtxCtrl.HandlePointerEventL" )
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::HandleSizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiContextControl::HandleSizeChanged()
    {
    __VTPRINTENTER( "CtxCtrl.HandleSizeChanged" )
    TRect screen;
    VtUiLayout::GetApplicationParentRect( screen );

    TAknWindowLineLayout control;
    VtUiLayout::GetFirstWindowBackgroundLayout( control );
    TAknLayoutRect backLayout;
    backLayout.LayoutRect( screen, control );
    BitmapManager().SetSize( iBackgroundId, backLayout.Rect().Size() );

    const TPoint positionRelativeToScreen( -PositionRelativeToScreen() );

    VtUiLayout::GetFirstWindowStreamDisabledIconLayout( control );
    TAknLayoutRect blindLayout;
    blindLayout.LayoutRect( screen, control );
    iBlindRect = blindLayout.Rect();
    iBlindRect.Move( positionRelativeToScreen );
    BitmapManager().SetSize( iBlindId, iBlindRect.Size() );
    BitmapManager().SetSize( iBlindMaskId, iBlindRect.Size() );

    VtUiLayout::GetFirstWindowStreamLayout( control );
    TAknLayoutRect streamLayout;
    streamLayout.LayoutRect( screen, control );
    iStreamRect = streamLayout.Rect();
    iStreamRect.Move( positionRelativeToScreen ) ;
    __VTPRINTEXIT( "CtxCtrl.HandleSizeChanged" )
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::StreamBlitPosition
// -----------------------------------------------------------------------------
//
TPoint CVtUiContextControl::StreamBlitPosition() const
    {
    __VTPRINTENTER( "CtxCtrl.StreamBlitPosition" )
    __VTPRINTEXIT( "CtxCtrl.StreamBlitPosition" )
    return iStreamRect.iTl;
    }

// ---------------------------------------------------------------------------
// CVtUiContextControl::StreamClippingRect
// ---------------------------------------------------------------------------
//
TRect CVtUiContextControl::StreamClippingRect() const
    {
    __VTPRINTENTER( "CtxCtrl.StreamClippingRect" )
    __VTPRINTEXIT( "CtxCtrl.StreamClippingRect" )
    return iStreamRect;
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::DrawColoredBackground
// -----------------------------------------------------------------------------
//
void CVtUiContextControl::DrawColoredBackground( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "CtxCtrl.DrawColoredBackground" )
    CVtUiVideoControlBase::DrawColoredBackground( aGc );
    // Draw background image
    CFbsBitmap* bg = NULL;
    CFbsBitmap* bgMask = NULL;
    BitmapManager().GetBitmaps( iBackgroundId, bg, bgMask );
    if ( bg )
        {
        const TPoint origin;
        const TRect rect( origin, bg->SizeInPixels() );
        if ( bgMask )
            {
            aGc.BitBltMasked( origin, bg, rect, bgMask, ETrue );
            }
        else
            {
            aGc.BitBlt( origin, bg );
            }
        }
    __VTPRINTEXIT( "CtxCtrl.DrawColoredBackground" )
    }

// ---------------------------------------------------------------------------
// CVtUiContextControl::BlindImage
// ---------------------------------------------------------------------------
//
CFbsBitmap* CVtUiContextControl::BlindImage() const
    {
    __VTPRINTENTER( "CtxCtrl.BlindImage" )
    __VTPRINTEXIT( "CtxCtrl.BlindImage" )
    return Bitmap( iBlindId );
    }

// ---------------------------------------------------------------------------
// CVtUiContextControl::BlindMask
// ---------------------------------------------------------------------------
//
CFbsBitmap* CVtUiContextControl::BlindMask() const
    {
    __VTPRINTENTER( "CtxCtrl.BlindImage" )
    __VTPRINTEXIT( "CtxCtrl.BlindImage" )
    return Bitmap( iBlindMaskId );
    }

// ---------------------------------------------------------------------------
// CVtUiContextControl::BlindBlitPosition
// ---------------------------------------------------------------------------
//
TPoint CVtUiContextControl::BlindBlitPosition() const
    {
    __VTPRINTENTER( "CtxCtrl.BlindBlitPosition" )
    __VTPRINTEXIT( "CtxCtrl.BlindBlitPosition" )
    return iBlindRect.iTl;
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::CVtUiContextControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiContextControl::CVtUiContextControl(
        CVtUiBitmapManager& aBitmapManager,
        CVtUiAppUi& aAppUi,
        TVtUiStates& aUiStates )
    : CVtUiVideoControlBase( aBitmapManager ),
      iAppUi( aAppUi ),
      iUiStates( aUiStates )
    {
    __VTPRINTENTER( "CtxCtrl.ctor" )
    SetRenderingHint( ENoWaitingText );
    SetRenderingHint( EColoredBackground );
    __VTPRINTEXIT( "CtxCtrl.ctor" )
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiContextControl::ConstructL()
    {
    __VTPRINTENTER( "CtxCtrl.ConstructL" )
    BaseConstructL();
    iBackgroundId =
        BitmapManager().AddBitmapsL(
            EVtUiBitmap_qgn_graf_call_video_out_bg,
            EVtUiBitmap_qgn_graf_call_video_out_bg_mask,
            EFalse );
    BitmapManager().SetAspectRatio( iBackgroundId, EFalse );
    iBlindId =
        BitmapManager().AddBitmapL(
            EVtUiBitmap_qgn_indi_call_video_blind_out,
            EFalse );
    BitmapManager().SetAspectRatio( iBlindId, EFalse );
    iBlindMaskId =
        BitmapManager().AddBitmapL(
            EVtUiBitmap_qgn_indi_call_video_blind_out_mask_icon,
            EFalse );
    BitmapManager().SetAspectRatio( iBlindMaskId, EFalse );
    SetNonFocusing();
    if ( iAppUi.EventMonitor() )
        {
        iAppUi.EventMonitor()->AddObserverL( this );
        }
        
    iOkToSwapOnButtonUp = ETrue;
    __VTPRINTEXIT( "CtxCtrl.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::HandleWsEventL
// -----------------------------------------------------------------------------
//
void CVtUiContextControl::HandleWsEventL( const TWsEvent& aEvent,
    CCoeControl* aDestination )
    {
    __VTPRINTENTER( "CVtUiContextControl.HandleWsEventL" )
    if( aEvent.Type() == EEventPointer )
        {
        // Touch outside of volume popup, close volume popup
        if ( aEvent.Pointer()->iType == TPointerEvent::EButton1Down )
            {
            if ( aDestination == this )
                {
                iOkToSwapOnButtonUp = !iUiStates.IsZoomModeOn() &&
                    !iUiStates.IsCaptureModeOn() &&
                    !iUiStates.IsContrastModeOn() &&
                    !iUiStates.IsBrightnessModeOn() &&
                    !iUiStates.IsVolumeModeOn();
                    SetGloballyCapturing( ETrue );
                    SetPointerCapture( ETrue ); 
                }
            }             
        }
    __VTPRINTEXIT( "CVtUiContextControl.HandleWsEventL" )
    }

// -----------------------------------------------------------------------------
// CVtUiContextControl::LayoutRemoteVideo
// -----------------------------------------------------------------------------
//
void CVtUiContextControl::LayoutRemoteVideo()
    {
    __VTPRINTENTER( "CVtUiContextControl.LayoutRemoteVideo" )
    if ( NULL != iRemoteVideoControl )
        {
        TRect rectRemoteVideo(StreamClippingRect());
        rectRemoteVideo.Move(PositionRelativeToScreen());
        iRemoteVideoControl->SetExtent(rectRemoteVideo.iTl,rectRemoteVideo.Size());        
        }
    __VTPRINTEXIT( "CVtUiContextControl.LayoutRemoteVideo" )
    }
//  End of File

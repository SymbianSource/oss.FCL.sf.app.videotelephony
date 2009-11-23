/*
* Copyright (c) 2004 - 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiMainControl control class.
*
*/



// INCLUDE FILES
#include    "CVtUiMainControl.h"
#include    "VtUiLayout.h"
#include    <aknsutils.h>
#include    <aknsdrawutils.h>
#include    <cvtlogger.h>
#include    <featmgr.h>
#include    "CVtUiAppUi.h"
#include    "tvtuistates.h"
#include    <aknsutils.h>
#include	"tVtuifeaturevariation.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiMainControl::NewL
// -----------------------------------------------------------------------------
CVtUiMainControl* CVtUiMainControl::NewL( CVtUiBitmapManager& aBitmapManager,
    TVtUiStates& aUiStates )
    {
    __VTPRINTENTER( "MainCtrl.NewL" )
    CVtUiMainControl* self =
        new ( ELeave ) CVtUiMainControl( aBitmapManager, aUiStates );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "MainCtrl.NewL" )
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::CVtUiMainControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiMainControl::CVtUiMainControl( CVtUiBitmapManager& aBitmapManager,
    TVtUiStates& aUiStates ) : CVtUiVideoControlBase( aBitmapManager ),
    iUiStates ( aUiStates )
    {
    __VTPRINTENTER( "MainCtrl.Ctor" )
    SetRenderingHint( ESkinnedBackground );
    __VTPRINTEXIT( "MainCtrl.Ctor" )
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiMainControl::ConstructL()
    {
    __VTPRINTENTER( "MainCtrl.ConstructL" )
    BaseConstructL();
    iBlindId =
        BitmapManager().AddBitmapL(
            EVtUiBitmap_qgn_indi_call_video_blind_in,
            EFalse );
    BitmapManager().SetAspectRatio( iBlindId, EFalse );
    iBlindMaskId =
        BitmapManager().AddBitmapL(
            EVtUiBitmap_qgn_indi_call_video_blind_in_mask_icon,
            EFalse );
    BitmapManager().SetAspectRatio( iBlindMaskId, EFalse );
    __VTPRINTEXIT( "MainCtrl.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::~CVtUiMainControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiMainControl::~CVtUiMainControl()
    {
    __VTPRINTENTER( "MainCtrl.~" )
    BitmapManager().RemoveBitmap( iBlindId );
    BitmapManager().RemoveBitmap( iBlindMaskId );
    __VTPRINTEXIT( "MainCtrl.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::HandleSizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiMainControl::HandleSizeChanged()
    {
    __VTPRINTENTER( "MainCtrl.HandleSizeChanged" )
    const TRect mainPaneRect( Rect() );

    // blind icon and mask
    TAknWindowLineLayout blind;
    VtUiLayout::GetSecondWindowDisabledIconLayout( blind );
    iBlindLayout.LayoutRect( mainPaneRect, blind );
    const TSize blindSize( iBlindLayout.Rect().Size() );
    BitmapManager().SetSize( iBlindId, blindSize );
    BitmapManager().SetSize( iBlindMaskId, blindSize );

    // stream
    TAknWindowLineLayout stream;
    VtUiLayout::GetSecondWindowStreamWholeLayout( stream,
         iUiStates.IsToolbarAvailable(), iSQCifRemote );

    iStreamLayoutRect.LayoutRect( mainPaneRect, stream );

    __VTPRINTEXIT( "MainCtrl.HandleSizeChanged" )
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::DrawWaitingText
// -----------------------------------------------------------------------------
//
TBool CVtUiMainControl::DrawWaitingText( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "MainCtrl.DrawWaitingText" )
    TBool wasDrawn( EFalse );
    if ( !iSQCifRemote)
        {
        wasDrawn = CVtUiVideoControlBase::DrawWaitingText( aGc );
        }
    __VTPRINTEXITR( "MainCtrl.DrawWaitingText %d", wasDrawn )
    return wasDrawn;
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::StreamBlitPosition
// -----------------------------------------------------------------------------
//
TPoint CVtUiMainControl::StreamBlitPosition() const
    {
    __VTPRINTENTER( "MainCtrl.StreamBlitPosition" )
    const TSize videoSize( iStreamBitmap->SizeInPixels() );
    const TSize streamSize( iStreamLayoutRect.Rect().Size() );
    __VTPRINTEXIT( "MainCtrl.StreamBlitPosition" )
    return AdjustPointForDP( iStreamLayoutRect.Rect().iTl );
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::StreamClippingRect
// -----------------------------------------------------------------------------
//
TRect CVtUiMainControl::StreamClippingRect() const
    {
    __VTPRINTENTER( "MainCtrl.StreamClippingRect" )
    __VTPRINTEXIT( "MainCtrl.StreamClippingRect" )
    return AdjustRectForDP( iStreamLayoutRect.Rect() );
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::BlindImage
// -----------------------------------------------------------------------------
//
CFbsBitmap* CVtUiMainControl::BlindImage() const
    {
    __VTPRINTENTER( "MainCtrl.BlindImage" )
    __VTPRINTEXIT( "MainCtrl.BlindImage" )
    return Bitmap( iBlindId );
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::BlindMask
// -----------------------------------------------------------------------------
//
CFbsBitmap* CVtUiMainControl::BlindMask() const
    {
    __VTPRINTENTER( "MainCtrl.BlindMask" )
    __VTPRINTEXIT( "MainCtrl.BlindMask" )
    return Bitmap( iBlindMaskId );
    }

// ---------------------------------------------------------------------------
// CVtUiMainControl::BlindBlitPosition
// ---------------------------------------------------------------------------
//
TPoint CVtUiMainControl::BlindBlitPosition() const
    {
    __VTPRINTENTER( "CVtUiMainControl.BlindBlitPosition" )
    __VTPRINTEXIT( "CVtUiMainControl.BlindBlitPosition" )
    return iBlindLayout.Rect().iTl;
    }

// ---------------------------------------------------------------------------
// CVtUiMainControl::WaitingTextLayout
// ---------------------------------------------------------------------------
//
TAknTextLineLayout CVtUiMainControl::WaitingTextLayout( TInt aLine )
    {
    __VTPRINTENTER( "MainCtrl.WaitingTextLayout" )
    TAknTextLineLayout textLayout;
    VtUiLayout::GetSecondWindowWaitingTextLayout( textLayout,
        aLine ? EFalse : ETrue );
    __VTPRINTEXIT( "MainCtrl.WaitingTextLayout" )
    return textLayout;
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::SupportSQCif
// -----------------------------------------------------------------------------
//
void CVtUiMainControl::SupportSQCif( TBool aIsSupported )
    {
    __VTPRINTENTER( "MainCtrl.SupportSQCif" )
    const TBool layoutUpdateRequired( aIsSupported != iSQCifRemote );
    iSQCifRemote = aIsSupported;
    if ( layoutUpdateRequired )
        {
        HandleSizeChanged();
        }
    __VTPRINTEXITR( "MainCtrl.SupportSQCif %d", iSQCifRemote )
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::LayoutRemoteVideo
// -----------------------------------------------------------------------------
//
void CVtUiMainControl::LayoutRemoteVideo( )
    {    
    __VTPRINTENTER( "MainCtrl.LayoutRemoteVideo" )
    if ( NULL != iRemoteVideoControl )
        {
        TRect rectRemoteVideo(StreamClippingRect());
        rectRemoteVideo.Move(PositionRelativeToScreen());
        iRemoteVideoControl->SetExtent(rectRemoteVideo.iTl,rectRemoteVideo.Size());
        }
    __VTPRINTEXIT( "MainCtrl.LayoutRemoteVideo" )
    }
//  End of File

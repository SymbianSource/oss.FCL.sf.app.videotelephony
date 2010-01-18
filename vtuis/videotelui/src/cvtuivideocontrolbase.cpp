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
* Description:  Video control base class implementation.
*
*/


#include    <cvtlogger.h>
#include    <featmgr.h>
#include    <AknsDrawUtils.h>
#include    <aknsutils.h>
#include    <aknbiditextutils.h>
#include    <stringloader.h>
#include    <videotelui.rsg>

#include     <aknsbasicbackgroundcontrolcontext.h>
#include    <aknstatuspaneutils.h>
#include    "cvtuivideocontrolbase.h"
#include    "mvtuicomponentmanager.h"
#include    "VtUiLayout.h"

// CONSTANTS

// Index of white color.
const TInt KVtUiColorWhite = 0;

// Amount of characters reserved per line.
const TInt KVtUiWaitingExtraSpacePerLine = KAknBidiExtraSpacePerLine + 1;

// Amount of lines used for 'waiting text'
const TInt KVtUiWaitingLineCount = 2;

// Implementation of CVtUiVideoControlBase

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::~CVtUiVideoControlBase
// ---------------------------------------------------------------------------
//
CVtUiVideoControlBase::~CVtUiVideoControlBase()
    {
    __VTPRINTENTER( "VidCtrlBase.~" )
    AknsUtils::DeregisterControlPosition( this );
    iStreamBitmap = NULL; // not owned.
    delete iWaitingTextWrappedArray;
    delete iWaitingTextWrapped;
    delete iBgContext;
    __VTPRINTEXIT( "VidCtrlBase.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::CVtUiVideoControlBase
// ---------------------------------------------------------------------------
//
CVtUiVideoControlBase::CVtUiVideoControlBase(
    CVtUiBitmapManager& aBitmapManager ) :
    iBitmapManager( &aBitmapManager )
    {
    __VTPRINTENTER( "VidCtrlBase.ctor" )
    __VTPRINTEXIT( "VidCtrlBase.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::BaseConstructL
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::BaseConstructL()
    {
    __VTPRINTENTER( "VidCtrlBase.BaseConstructL" )
    iBgContext = CAknsBasicBackgroundControlContext::NewL(
                       KAknsIIDQsnBgAreaMain, Rect(), ETrue );
    CreateWindowL();
    SetExtent( TPoint(), TSize() );
    ActivateL();
    // Disable fading when using DP (eliminates nasty color error)
    if ( FeatureManager::FeatureSupported( KFeatureIdDisplayPost ) )
        {
        Window().SetNonFading( ETrue );
        }
    WrapOnDemand();
    __VTPRINTEXIT( "VidCtrlBase.BaseConstructL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::SetRenderingHint
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SetRenderingHint( TRenderingHint aHint )
    {
    __VTPRINTENTER( "VidCtrlBase.SetRenderingHint" )
    __VTPRINT2( DEBUG_GEN, "VidCtrlBase.SetRenderingHint aHint = %d", aHint )
    iHints.Set( aHint );
    __VTPRINTEXIT( "VidCtrlBase.SetRenderingHint" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::ClearRenderingHint
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::ClearRenderingHint( TRenderingHint aHint )
    {
    __VTPRINTENTER( "VidCtrlBase.ClearRenderingHint" )
    __VTPRINT2( DEBUG_GEN, "VidCtrlBase.ClearRenderingHint aHint = %d", aHint )
    iHints.Clear( aHint );
    __VTPRINTEXIT( "VidCtrlBase.ClearRenderingHint" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::BitmapManager
// ---------------------------------------------------------------------------
//
CVtUiBitmapManager& CVtUiVideoControlBase::BitmapManager() const
    {
    return *iBitmapManager;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::Bitmap
// ---------------------------------------------------------------------------
//
CFbsBitmap* CVtUiVideoControlBase::Bitmap( TVtUiBitmapPoolId aId ) const
    {
    __VTPRINTENTER( "VidCtrlBase.Bitmap" )
    CFbsBitmap* bitmap = NULL;
    iBitmapManager->GetBitmap( aId, bitmap );
    __VTPRINTEXITR( "VidCtrlBase.Bitmap %d", TInt( bitmap ) )
    return bitmap;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::AdjustPointForDP
// ---------------------------------------------------------------------------
//
TPoint CVtUiVideoControlBase::AdjustPointForDP( const TPoint aPoint ) const
    {
    __VTPRINTENTER( "VidCtrlBase.AdjustPointForDP" )
    TPoint result( aPoint );
    if ( FeatureManager::FeatureSupported( KFeatureIdDisplayPost ) )
        {
        if ( result.iX & 1 )
            {
            result.iX++;
            }
        }
    __VTPRINTEXIT( "VidCtrlBase.AdjustPointForDP" )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::AdjustRectForDP
// ---------------------------------------------------------------------------
//
TRect CVtUiVideoControlBase::AdjustRectForDP( const TRect aRect ) const
    {
    __VTPRINTENTER( "VidCtrlBase.AdjustRectForDP" )
    TRect result( aRect );
    if ( FeatureManager::FeatureSupported( KFeatureIdDisplayPost ) )
        {
        if ( result.iTl.iX & 1 )
            {
            result.Move( 1, 0 );
            result.SetWidth( Max( 0, result.Width() - 1 ) );
            }
        if ( result.Width() & 1 )
            {
            result.SetWidth( result.Width() - 1 );
            }
        }
    __VTPRINTEXIT( "VidCtrlBase.AdjustRectForDP" )
    return result;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::WaitingTextLayout
// ---------------------------------------------------------------------------
//
TAknTextLineLayout CVtUiVideoControlBase::WaitingTextLayout( TInt )
    {
    return TAknTextLineLayout();
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::HandleSizeChanged
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::HandleSizeChanged()
    {
    __VTPRINTENTER( "VidCtrlBase.HandleSizeChanged" )
    __VTPRINTEXIT( "VidCtrlBase.HandleSizeChanged" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DrawSkinnedBackground
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DrawSkinnedBackground( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DrawSkinnedBackground" )
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    MAknsControlContext* cc = AknsDrawUtils::ControlContext( this );
    AknsDrawUtils::Background( skin, cc, this, aGc, Rect() );
    __VTPRINTEXIT( "VidCtrlBase.DrawSkinnedBackground" )
    }

// -----------------------------------------------------------------------------
// CVtUiVideoControlBase::MopSupplyObject
// -----------------------------------------------------------------------------
//

TTypeUid::Ptr CVtUiVideoControlBase::MopSupplyObject( TTypeUid aId )
 {
     __VTPRINTENTER( "VidCtrlBase.MopSupplyObject" )
 // Required during rendering of the background skin in Draw()
 if (aId.iUid == MAknsControlContext::ETypeId)
     {
      __VTPRINTEXIT( "VidCtrlBase.MopSupplyObject.1" )
     return MAknsControlContext::SupplyMopObject( aId, iBgContext );
     }
    __VTPRINTEXIT( "VidCtrlBase.MopSupplyObject.2" )
 return CCoeControl::MopSupplyObject( aId );
 }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DrawColoredBackground
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DrawColoredBackground( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DrawColoredBackground" )
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.SetPenStyle( CGraphicsContext::ENullPen );
    aGc.SetBrushColor( AKN_LAF_COLOR( KVtUiColorWhite ) );
    aGc.DrawRect( Rect() );
    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    __VTPRINTEXIT( "VidCtrlBase.DrawColoredBackground" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DrawWaitingText
// ---------------------------------------------------------------------------
//
TBool CVtUiVideoControlBase::DrawWaitingText( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DrawWaitingText" )
    const TInt count( iWaitingTextWrappedArray->Count() );
    if ( count > 0 )
        {
        aGc.SetClippingRect( StreamClippingRect() );
        aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TRgb color( iWaitingTextLine1Layout.Color() );
        AknsUtils::GetCachedColor(
            skin,
            color,
            KAknsIIDQsnTextColors,
            EAknsCIQsnTextColorsCG6 );
        iWaitingTextLine1Layout.DrawText(
            aGc,
            iWaitingTextWrappedArray->At( 0 ), // first line
            EFalse,
            color );
        if ( count > 1 ) // two lines
            {
            iWaitingTextLine2Layout.DrawText(
                aGc,
                iWaitingTextWrappedArray->At( 1 ), // second line
                EFalse,
                color );
            }
        }
    __VTPRINTEXITR( "VidCtrlBase.DrawWaitingText %d", ETrue )
    return ETrue;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DrawBlind
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DrawBlind( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DrawBlind" )
    CFbsBitmap* icon = BlindImage();
    if ( icon )
        {
        CFbsBitmap* mask = BlindMask();
        if ( mask )
            {
            aGc.BitBltMasked(
                BlindBlitPosition(),
                icon,
                TRect( icon->SizeInPixels() ),
                mask,
                ETrue );
            }
        else
            {
            aGc.BitBlt(
                BlindBlitPosition(),
                icon );
            }
        }
    __VTPRINTEXIT( "VidCtrlBase.DrawBlind" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DrawStream
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DrawStream( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DrawStream" )
    aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    aGc.SetClippingRect( StreamClippingRect() );
    aGc.BitBlt( StreamBlitPosition(), iStreamBitmap );
    aGc.CancelClippingRect();
    __VTPRINTEXIT( "VidCtrlBase.DrawStream" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::StreamBlitPosition
// ---------------------------------------------------------------------------
//
TPoint CVtUiVideoControlBase::StreamBlitPosition() const
    {
    __VTPRINTENTER( "VidCtrlBase.StreamBlitPosition" )
    __VTPRINTEXIT( "VidCtrlBase.StreamBlitPosition" )
    return Rect().iTl;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::StreamClippingRect
// ---------------------------------------------------------------------------
//
TRect CVtUiVideoControlBase::StreamClippingRect() const
    {
    __VTPRINTENTER( "VidCtrlBase.StreamClippingRect" )
    __VTPRINTEXIT( "VidCtrlBase.StreamClippingRect" )
    return Rect();
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::BlindImage
// ---------------------------------------------------------------------------
//
CFbsBitmap* CVtUiVideoControlBase::BlindImage() const
    {
    __VTPRINTENTER( "VidCtrlBase.BlindImage" )
    __VTPRINTEXIT( "VidCtrlBase.BlindImage" )
    return NULL;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::BlindMask
// ---------------------------------------------------------------------------
//
CFbsBitmap* CVtUiVideoControlBase::BlindMask() const
    {
    __VTPRINTENTER( "VidCtrlBase.BlindMask" )
    __VTPRINTEXIT( "VidCtrlBase.BlindMask" )
    return NULL;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::BlindBlitPosition
// ---------------------------------------------------------------------------
//
TPoint CVtUiVideoControlBase::BlindBlitPosition() const
    {
    __VTPRINTENTER( "VidCtrlBase.BlindBlitPosition" )
    __VTPRINTEXIT( "VidCtrlBase.BlindBlitPosition" )
    return TPoint();
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::Reset
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::Reset()
    {
    __VTPRINTENTER( "VidCtrlBase.Reset" )
    iBlindStatus = EFalse;
    iStreamBitmap = NULL;
    iWaitingTextShow = EFalse;
    __VTPRINTEXIT( "VidCtrlBase.Reset" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::SetBlind
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SetBlind( TBool aBlindStatus )
    {
    __VTPRINTENTER( "VidCtrlBase.SetBlind" )
    /* Once SetBlind called, re-draw the control anyway */
//    if ( iBlindStatus != aBlindStatus )
//        {
        iBlindStatus = aBlindStatus;
        DrawNow();
//        }
    __VTPRINTEXITR( "VidCtrlBase.SetBlind %d", iBlindStatus )
    }

// -----------------------------------------------------------------------------
// CVtUiVideoControlBase::IsAlphaZero
// Checks if the alpha has been set to zero.
// -----------------------------------------------------------------------------
//
TBool CVtUiVideoControlBase::IsAlphaZero() const
    {
    __VTPRINTENTER( "VidCtrlBase.IsAlphaZero" )
    TBool isZero( EFalse );
    const CWsScreenDevice& sdev(
        *static_cast< CWsScreenDevice*>( SystemGc().Device() ) );
    if ( sdev.DisplayMode() == EColor16MA )
        {
        TRgb color;
        TPoint point( Rect().Center() );
        sdev.GetPixel( color, point );
        isZero = ( color.Alpha() == 0 );
        }
    __VTPRINTEXITR( "VidCtrlBase.IsAlphaZero %d", isZero )
    return isZero;
    }

// -----------------------------------------------------------------------------
// CVtUiVideoControlBase::SetAlpha
// Sets alpha.
// -----------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SetAlpha( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.SetAlpha" )
    aGc.SetDrawMode( CGraphicsContext::EDrawModeOR );
    aGc.SetBrushColor( TRgb( 0, 0, 0, 255 ) );
    aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    aGc.Clear();
    aGc.Reset();
    __VTPRINTEXIT( "VidCtrlBase.SetAlpha" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::SetStreamBitmap
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SetStreamBitmap( CFbsBitmap* aStreamBitmap )
    {
    __VTPRINTENTER( "VidCtrlBase.SetStreamBitmap" )
    __VTPRINT2( DEBUG_GEN, "VidCtrlBase.SetStreamBitmap %d",
        (TInt) aStreamBitmap )
    const CFbsBitmap* oldBitmap( iStreamBitmap );
    iStreamBitmap = aStreamBitmap;
    iSetAlpha = IsAlphaZero();
    if ( iStreamBitmap )
        {
        RedrawStream();
        }
    else if ( oldBitmap )
        {
        DrawNow();
        }
    __VTPRINTEXIT( "VidCtrlBase.SetStreamBitmap" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::SetStreamBitmapReserve
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SetStreamBitmapReserve(
    CFbsBitmap* aStreamBitmap )
    {
    __VTPRINTENTER( "VidCtrlBase.SetStreamBitmapReserve" )
    __VTPRINT2( DEBUG_GEN, "VidCtrlBase.SetStreamBitmapReserve %d",
        (TInt) aStreamBitmap )
    const CFbsBitmap* oldBitmap( iStreamBitmap );
    iStreamBitmap = aStreamBitmap;
    if ( iStreamBitmap )
        {
        RedrawStream();
        }
    else if ( oldBitmap )
        {
        DrawNow();
        }
    __VTPRINTEXIT( "VidCtrlBase.SetStreamBitmapReserve" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::SetWaiting
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SetWaiting( TBool aShowWaitingText )
    {
    __VTPRINTENTER( "VidCtrlBase.SetWaiting" )
    if ( iWaitingTextShow != aShowWaitingText )
        {
        iWaitingTextShow = aShowWaitingText;
        WrapOnDemand();
        DrawNow();
        }
    __VTPRINTEXITR( "VidCtrlBase.SetWaiting %d", iWaitingTextShow )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::Redraw
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::Redraw()
    {
    __VTPRINTENTER( "VidCtrlBase.Redraw" )
    if ( iStreamBitmap )
        {
        __VTPRINT( DEBUG_GEN, "VidCtrlBase.Redraw drawing" );
        DrawNow();
        }
    __VTPRINTEXIT( "VidCtrlBase.Redraw" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::Draw
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::Draw( const TRect& ) const
    {
    __VTPRINTENTER( "VidCtrlBase.Draw" )
    DoDraw( SystemGc() );
    __VTPRINTEXIT( "VidCtrlBase.Draw" )
    }

// -----------------------------------------------------------------------------
// CVtUiVideoControlBase::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SizeChanged()
    {
    __VTPRINTENTER( "VidCtrlBase.SizeChanged" )
    AknsUtils::RegisterControlPosition( this );

    TRect bgRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EMainPane, bgRect );
    iBgContext->SetRect( bgRect );

    HandleSizeChanged();
    TRect parent( Rect() );
    if ( !parent.IsEmpty() )
        {
        TAknTextLineLayout text( WaitingTextLayout( 0 ) );
        iWaitingTextLine1Layout.LayoutText( parent, text );
        text = WaitingTextLayout( 1 );
        iWaitingTextLine2Layout.LayoutText( parent, text );
        delete iWaitingTextWrapped;
        iWaitingTextWrapped = NULL;
        delete iWaitingTextWrappedArray;
        iWaitingTextWrappedArray = NULL;
        WrapOnDemand();
        }
    __VTPRINTEXIT( "VidCtrlBase.SizeChanged" )
    }

// -----------------------------------------------------------------------------
// CVtUiVideoControlBase::PositionChanged
// -----------------------------------------------------------------------------
//
void CVtUiVideoControlBase::PositionChanged()
    {
    __VTPRINTENTER( "VidCtrlBase.SizeChanged" )
    AknsUtils::RegisterControlPosition( this );
    __VTPRINTEXIT( "VidCtrlBase.SizeChanged" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::RedrawStream
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::RedrawStream()
    {
    __VTPRINTENTER( "VidCtrlBase.RedrawStream" )
    const TRect clippingRect( StreamClippingRect() );
    Window().Invalidate( clippingRect );
    Window().BeginRedraw( clippingRect );
    ActivateGc();
    CWindowGc& gc = SystemGc();
    if ( iSetAlpha )
        {
        SetAlpha( gc );
        iSetAlpha = EFalse;
        }
    DoDrawStream( gc );
    DoDrawBlind( gc );
    DeactivateGc();
    Window().EndRedraw();
    __VTPRINTEXIT( "VidCtrlBase.RedrawStream" )
    }

// -----------------------------------------------------------------------------
// CVtUiVideoControlBase::WrapOnDemand
// -----------------------------------------------------------------------------
//
void CVtUiVideoControlBase::WrapOnDemand()
    {
    __VTPRINTENTER( "VidCtrlBase.WrapOnDemand" )
    if ( iWaitingTextShow && !iWaitingTextWrapped )
        {
        TRAP_IGNORE( WrapWaitingTextL() );
        }
    __VTPRINTEXIT( "VidCtrlBase.WrapOnDemand" )
    }

// -----------------------------------------------------------------------------
// CVtUiVideoControlBase::WrapWaitingTextL
// -----------------------------------------------------------------------------
//
void CVtUiVideoControlBase::WrapWaitingTextL()
    {
    __VTPRINTENTER( "VidCtrlBase.WrapWaitingTextL" )
    HBufC* waitingText =
        StringLoader::LoadLC( R_VIDEOTELUI_QTN_INCAL_WAITING_IMAGE );

    CArrayFix< TInt >* lines =
        new ( ELeave ) CArrayFixFlat< TInt >( KVtUiWaitingLineCount );
    CleanupStack::PushL( lines );
    lines->AppendL( iWaitingTextLine1Layout.TextRect().Width() );
    lines->AppendL( iWaitingTextLine2Layout.TextRect().Width() );

    CArrayFix<TPtrC>* wrap =
        new ( ELeave ) CArrayFixFlat< TPtrC >( KVtUiWaitingLineCount );
    CleanupStack::PushL( wrap );
    wrap->AppendL( TPtrC() );
    wrap->AppendL( TPtrC() );

    HBufC* waitingTextWrapped =
        HBufC::NewLC(
            waitingText->Length() +
            lines->Count() * KVtUiWaitingExtraSpacePerLine );

    TPtr textBuf = waitingTextWrapped->Des();
    textBuf.Zero();
    textBuf.Append( *waitingText );

    AknBidiTextUtils::ConvertToVisualAndWrapToArrayL(
        textBuf,
        *lines,
        *iWaitingTextLine1Layout.Font(),
        *wrap,
        ETrue );

    CleanupStack::Pop( waitingTextWrapped );
    iWaitingTextWrapped = waitingTextWrapped;

    CleanupStack::Pop( wrap );
    iWaitingTextWrappedArray = wrap;

    CleanupStack::PopAndDestroy( lines );
    CleanupStack::PopAndDestroy( waitingText );
    __VTPRINTEXIT( "VidCtrlBase.WrapWaitingTextL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DoDraw
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DoDraw( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.Draw(gc)" )
    if ( iSetAlpha )
        {
        SetAlpha( aGc );
        iSetAlpha = EFalse;
        }
    DoDrawBackground( aGc );
    if ( !DoDrawWaitingText( aGc ) )
        {
        DoDrawStream( aGc );
        DoDrawBlind( aGc );
        }
    __VTPRINTEXIT( "VidCtrlBase.Draw(gc)" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DoDrawBackground
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DoDrawBackground( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DoDrawBackground" )
    if ( iHints.IsSet( ESkinnedBackground ) )
        {
        DrawSkinnedBackground( aGc );
        }
    else if ( iHints.IsSet( EColoredBackground ) )
        {
        DrawColoredBackground( aGc );
        }
    __VTPRINTEXIT( "VidCtrlBase.DoDrawBackground" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DoDrawWaitingText
// ---------------------------------------------------------------------------
//
TBool CVtUiVideoControlBase::DoDrawWaitingText( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DoDrawWaitingText" )
    TBool wasDrawn( EFalse );
    if ( iHints.IsClear( ENoWaitingText ) && iWaitingTextShow &&
         iWaitingTextWrapped && iWaitingTextWrappedArray )
        {
        wasDrawn = DrawWaitingText( aGc );
        }
    __VTPRINTEXITR( "VidCtrlBase.DoDrawWaitingText %d", wasDrawn )
    return wasDrawn;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DoDrawBlind
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DoDrawBlind( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DoDrawBlind" )
    if ( iBlindStatus && iHints.IsClear( ENoBlindIcon ) )
        {
        DrawBlind( aGc );
        }
    __VTPRINTEXIT( "VidCtrlBase.DoDrawBlind" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::DoDrawStream
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::DoDrawStream( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "VidCtrlBase.DoDrawStream" )
    if ( iStreamBitmap )
        {
        DrawStream( aGc );
        }
    __VTPRINTEXIT( "VidCtrlBase.DoDrawStream" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::SetRemoteVideoControl
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase::SetRemoteVideoControl( CCoeControl* aRemoteControl )
    {
    __VTPRINTENTER( "VidCtrlBase.SetRemoteVideoControl" )
    iRemoteVideoControl = aRemoteControl;
    __VTPRINTEXIT( "VidCtrlBase.SetRemoteVideoControl" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::LayoutRemoteVideo
// ---------------------------------------------------------------------------
//
void CVtUiVideoControlBase:: LayoutRemoteVideo()
    {
    __VTPRINTENTER( "VidCtrlBase.LayoutRemoteVideo" )
    __VTPRINTEXIT( "VidCtrlBase.LayoutRemoteVideo" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoControlBase::RemoteVideoControl
// ---------------------------------------------------------------------------
//
CCoeControl * CVtUiVideoControlBase::RemoteVideoControl()
    {
    __VTPRINTENTER( "VidCtrlBase.RemoteVideoControl" )
    __VTPRINTEXIT( "VidCtrlBase.RemoteVideoControl" )
    return iRemoteVideoControl;
        
    }

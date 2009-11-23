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
* Description:  Implementation of the CVtUiZoomControl control class.
*
*/



// INCLUDE FILES
#include    "CVtUiZoomControl.h"
#include    "VtUiLayout.h"
#include    <aknsutils.h>
#include    <aknsdrawutils.h>
#include    "videotelui.hrh"

#include    <cvtlogger.h>
// CONSTANTS

// Maximum amount of steps.
const TInt KVtUiZoomControlMaxSteps = 11;

// Minimum amount of steps.
const TInt KVtUiZoomControlMinSteps = 1;

// Fixed point position.
const TInt KVtUiZoomControlFixed = 16;

// Fixed point number, corresponds to one.
const TInt KVtUiZoomControlOne = ( 1 << KVtUiZoomControlFixed );

// Amount of partial bits. It is expected that 
// KVtUiZoomControlFixed >= KVtUiZoomControlPartial.
const TInt KVtUiZoomControlPartial = 8;

// Maximum duration of zooming from minimum to maximum, in microseconds.
const TInt KVtUiZoomDurationMax = 2000000;

// Maximum duration to increase zoom step by one, in microseconds.
const TInt KVtUiZoomStepDurationMax = 200000;

// Index of transparent color.
const TInt KVtUiZoomTransparent = 0;

// MODULE DATA STRUCTURES

/**
* Inner class to hold everything related to one bitmap.
* @since Series 60 2.6
*/
class CVtUiZoomControl::CBitmap
    : public CBase
    {
    public: // Constructors and destructors.

        /**
        * Constructor.
        */
        CBitmap();

        /**
        * Symbian OS constructor.
        * @param aSize size of the bitmap.
        * @param aMode display mode of the bitmap.
        */
        void ConstructL( 
            const TSize& aSize,
            const TDisplayMode aMode );

        /**
        * Destructor.
        */
        ~CBitmap();

    public:

        /**
        * Returns bitmap.
        * @return bitmap, ownership not passed.
        */
        inline CFbsBitmap* Bitmap() const;

        /**
        * Returns bitmap context.
        * @return bitmap context, ownership not passed.
        */
        inline CFbsBitGc* Context() const;

    private:

        // Owned bitmap.
        CFbsBitmap* iBitmap;

        // Owned device.
        CFbsBitmapDevice* iDevice;

        // Owned context.
        CFbsBitGc* iContext;

    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CVtUiZoomControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiZoomControl::CVtUiZoomControl( CVtUiBitmapManager& aBitmapManager )
    : iBitmapManager( aBitmapManager )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::ConstructL()
    {
    iZoomDirId = 
        iBitmapManager.AddBitmapsL( 
            EVtUiBitmap_qgn_indi_zoom_dir, 
            EVtUiBitmap_qgn_indi_zoom_dir_mask,
            ETrue );
    iZoomAreaId =
        iBitmapManager.AddBitmapL( EVtUiBitmap_qgn_graf_zoom_area, EFalse );
    iBitmapManager.SetAspectRatio( iZoomAreaId, EFalse );

    iZoomMinId =
        iBitmapManager.AddBitmapL( EVtUiBitmap_qgn_indi_zoom_min, EFalse );
    iBitmapManager.SetAspectRatio( iZoomMinId, EFalse );

    iZoomMaxId =
        iBitmapManager.AddBitmapL( EVtUiBitmap_qgn_indi_zoom_max, EFalse );
    iBitmapManager.SetAspectRatio( iZoomMaxId, EFalse );
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::~CVtUiZoomControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiZoomControl::~CVtUiZoomControl()
    {
    AknsUtils::DeregisterControlPosition( this );

    iBitmapManager.RemoveBitmap( iZoomDirId );
    iBitmapManager.RemoveBitmap( iZoomAreaId );
    iBitmapManager.RemoveBitmap( iZoomMinId );
    iBitmapManager.RemoveBitmap( iZoomMaxId );

    delete iZoomPartialMask;
    delete iZoomPartialShade;
    delete iZoomPartialShadeMask;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::SetZoomParams
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::SetZoomParams( 
        const TInt aStepCount, 
        const TInt aCurrentStep )
    {
    iCurrentZoomStep = aCurrentStep;
    iMaxZoomStep = aStepCount;
    if ( iMaxZoomStep < 0 )
        {
        iMaxZoomStep = 0;
        }
    iCurrentZoomStep = Max( Min( iCurrentZoomStep, iMaxZoomStep ), 0 );
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CommitL
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::CommitL()
    {
    ReportEventL( MCoeControlObserver::EEventStateChanged );
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::IsZoomEnabled
// -----------------------------------------------------------------------------
//
TBool CVtUiZoomControl::IsZoomEnabled() const
    {
    return ( iMaxZoomStep > 0 );
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::GetZoomParams
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::GetZoomParams(
        TInt& aStepCount,
        TInt& aCurrentStep ) const
    {
    aStepCount = iMaxZoomStep;
    aCurrentStep = iCurrentZoomStep;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::UpdateZoomL
// -----------------------------------------------------------------------------
//
TBool CVtUiZoomControl::UpdateZoomL()
    {
    const TInt oldZoomStep = iCurrentZoomStep;
    if ( iZoomDirection )
        {
        __VTPRINT( DEBUG_GEN, "VtUiZmCtl.UpdZoom" )
        TTime timeNow;
        timeNow.UniversalTime();

        const TTimeIntervalMicroSeconds duration = 
            timeNow.MicroSecondsFrom( iZoomStartTime );

        if ( duration >= TInt64( KVtUiZoomDurationMax ) )
            {
            // Duration is over maximum, so we can stop zooming.
            if ( iZoomDirection > 0 )
                {
                iCurrentZoomStep = iMaxZoomStep;
                }
            else
                {
                iCurrentZoomStep = 0;
                }

            iZoomDirection = 0;
            }
        else if ( duration < TInt64( 0 ) )
            {
            // Clock has been changed. Stop zooming.
            iZoomDirection = 0;
            }
        else
            {
            // Zoom is increased at least by one step per 0.2 seconds.
            TInt64 minimum( duration.Int64() );
            minimum /= KVtUiZoomStepDurationMax;

            // Zoom is increased from minimum to maximum in 2 seconds.
            TInt64 maximum( duration.Int64() );
            maximum *= iMaxZoomStep;
            maximum /= KVtUiZoomDurationMax;

            // Select maximum.
            TInt zoomStepDelta = 
                iZoomDirection * Max( I64INT( minimum ), I64INT( maximum ) );
            TInt zoomStep = iZoomStepStart + zoomStepDelta;

            // If minimum has been reached, zooming can be stopped.
            if ( zoomStep < 0 )
                {
                zoomStep = 0;
                iZoomDirection = 0;
                }
            // If maximum has been reached, zooming can be stopped.
            if ( zoomStep > iMaxZoomStep )
                {
                zoomStep = iMaxZoomStep;
                iZoomDirection = 0;
                }

            iCurrentZoomStep = zoomStep;
            }
        __VTPRINT( DEBUG_GEN, "VtUiZmCtl.chk" )
        }

    const TBool updateNeeded = ( oldZoomStep != iCurrentZoomStep );
    if ( updateNeeded )
        {
        __VTPRINT( DEBUG_GEN, "VtUiZmCtl.upd" )
        ReportEventL( MCoeControlObserver::EEventStateChanged );
        }

    return updateNeeded;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::StopZoom
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::StopZoom()
    {
    iZoomDirection = 0;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CVtUiZoomControl::OfferKeyEventL(
        const TKeyEvent& aKeyEvent,
        TEventCode aType )
    {
    TKeyResponse response = EKeyWasNotConsumed;

    if ( aKeyEvent.iScanCode == EStdKeyUpArrow ||
         aKeyEvent.iScanCode == EStdKeyDownArrow ||
         aKeyEvent.iCode == EKeyZoomIn ||
         aKeyEvent.iCode == EKeyZoomOut )
        {
        switch ( aType )
            {
            case EEventKey:
                {
                TInt direction = +1;
                if ( aKeyEvent.iScanCode == EStdKeyDownArrow ||
                    aKeyEvent.iCode == EKeyZoomOut )
                    {
                    direction = -1;
                    }
        
                if ( !aKeyEvent.iRepeats )
                    {
                    // Update start parameters.
                    iZoomDirection = direction;
                    iZoomStepStart = iCurrentZoomStep + direction;
                    iZoomStepStart = Min( iZoomStepStart, iMaxZoomStep );
                    iZoomStepStart = Max( iZoomStepStart, 0 );
                    iZoomStartTime.UniversalTime();
                    }
                
                (void)UpdateZoomL();
                }
                break;

            case EEventKeyUp:
                // Stop zooming.
                iZoomDirection = 0;
                break;

            default:
                // Do nothing.
                break;
            }

        response = EKeyWasConsumed;
        }

    return response;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::HandleResourceChange(
        TInt aType )
    {
    if ( aType == KAknsMessageSkinChange ) 
        {
        // We must refresh partial bitmap upon next redraw.
        iZoomMaskPartial = KErrNotFound;
        iZoomMaskRow = KErrNotFound;
        }

    CCoeControl::HandleResourceChange( aType );
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::Draw
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::Draw( const TRect& /*aRect*/ ) const
    {   
    __VTPRINT( DEBUG_GEN, "VtUiZmCtl.Draw" )   
    iBitmapManager.SetSizeAndColor( 
        iZoomDirId, 
        iZoomDirLayout.Rect().Size(),
        iZoomDirLayout.Color() );
    iBitmapManager.SetSize( 
        iZoomAreaId, 
        iZoomAreaLayout.Rect().Size() );
    iBitmapManager.SetSize( 
        iZoomMinId, 
        iZoomAreaLayout.Rect().Size() );
    iBitmapManager.SetSize( 
        iZoomMaxId, 
        iZoomAreaLayout.Rect().Size() );

    CFbsBitmap* maxBitmap = NULL;
    CFbsBitmap* minBitmap = NULL;
    CFbsBitmap* areaBitmap = NULL;
    iBitmapManager.GetBitmap( iZoomMaxId, maxBitmap );
    iBitmapManager.GetBitmap( iZoomMinId, minBitmap );
    iBitmapManager.GetBitmap( iZoomAreaId, areaBitmap );

    TInt full;
    TInt partial;
    TRect drawRect;
    TPoint drawPos;

    DetermineSteps( full, partial );
    if ( areaBitmap && partial && ( full < KVtUiZoomControlMaxSteps ) )
        {
        // First generate bitmaps, so that drawing can be done 
        // quickly in sequence.
        GetPositionAndRect( 
            drawPos,
            drawRect,
            full + 1 );

        if ( !GenerateZoomMaskBitmap( 
                areaBitmap, 
                partial, 
                drawRect.iTl.iY,
                drawRect.Size() ) )
            {
            // If zoom mask generation fails, then we have no choice
            // than not to draw.
            partial = 0; 
            }
        }

    CWindowGc& gc = SystemGc();
    gc.SetBrushStyle( CGraphicsContext::ENullBrush );

    // Draw zoom direction indicator:

    CFbsBitmap* zoomDirBitmap = NULL;
    CFbsBitmap* zoomDirMask = NULL;
    iBitmapManager.GetBitmaps( iZoomDirId, zoomDirBitmap, zoomDirMask );
    if ( zoomDirBitmap && zoomDirMask )
        {
        iZoomDirLayout.DrawImage( gc, zoomDirBitmap, zoomDirMask );
        }
    
    // Draw zoom indicator:
    if ( !areaBitmap )
        {
        // If area bitmap is invalid, then we have to return.
        return;
        }

    if ( maxBitmap )
        {
        // First, draw maximum area.
        for ( TInt index = KVtUiZoomControlMinSteps; 
              index <= full; 
              index++ )
            {
            GetPositionAndRect( 
                drawPos, 
                drawRect, 
                index );
            gc.BitBltMasked( 
                drawPos,
                maxBitmap, 
                drawRect, 
                areaBitmap, 
                ETrue );
            }
        }

    if ( minBitmap && ( full < KVtUiZoomControlMaxSteps ) )
        {
        // Then draw minimum area.
        for ( TInt index = full + 1; 
              index <= KVtUiZoomControlMaxSteps; 
              index++ )
            {
            GetPositionAndRect( 
                drawPos, 
                drawRect, 
                index );
            gc.BitBltMasked( 
                drawPos, 
                minBitmap, 
                drawRect, 
                areaBitmap, 
                ETrue );
            }

        if ( maxBitmap && partial && iZoomPartialMask )
            {
            // Finally draw partial area.
            GetPositionAndRect( 
                drawPos,
                drawRect,
                full + 1 );
            gc.BitBltMasked( 
                drawPos,
                maxBitmap,
                drawRect, 
                iZoomPartialMask->Bitmap(),
                ETrue );
            }
        }
    
    __VTPRINT( DEBUG_GEN, "VtUiZmCtl.Draw.ok" )
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::SizeChanged()
    {
    AknsUtils::RegisterControlPosition( this );

    TRect parent( Rect() );
    TAknWindowLineLayout rect;
    if ( parent.IsEmpty() )
        {
        return;
        }

        {
        TAknLayoutRect& tmpRect = iZoomDirLayout; 
        VtUiLayout::GetZoomPaneLayout( rect );
        tmpRect.LayoutRect( parent, rect );
        parent = tmpRect.Rect();
        iZoomPaneRect = parent;
        }

    VtUiLayout::GetZoomDirLayout( rect );
    iZoomDirLayout.LayoutRect( parent, rect );
    iBitmapManager.SetSizeAndColor( 
        iZoomDirId, 
        iZoomDirLayout.Rect().Size(),
        iZoomDirLayout.Color() );

    VtUiLayout::GetZoomAreaLayout( rect );
    iZoomAreaLayout.LayoutRect( parent, rect );
    iBitmapManager.SetSize( 
        iZoomAreaId, 
        iZoomAreaLayout.Rect().Size() );
    iBitmapManager.SetSize( 
        iZoomMinId, 
        iZoomAreaLayout.Rect().Size() );
    iBitmapManager.SetSize( 
        iZoomMaxId, 
        iZoomAreaLayout.Rect().Size() );
    (void) CreateBitmaps();
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::PositionChanged
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::DetermineSteps
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::DetermineSteps(
        TInt& aFullSteps,
        TInt& aPartialStep ) const
    {
    aFullSteps = 1;
    aPartialStep = 0;

    TInt currentZoomStep = Max( Min( iCurrentZoomStep, iMaxZoomStep ), 0 );

    if ( iMaxZoomStep > 0 )
        {
        TInt zoomDeltaSteps = 0;
        TInt zoomDeltaMaxSteps = 0;

        // Formula equals: x = ( N * ( y - 1 ) ) / 10.
        
        aFullSteps = KVtUiZoomControlMinSteps;
        const TInt divider = 
            KVtUiZoomControlMaxSteps - KVtUiZoomControlMinSteps;
        for ( TInt row = KVtUiZoomControlMaxSteps - 1; 
              row >= KVtUiZoomControlMinSteps - 1;
              row-- )
            {
            const TInt zoomStartSteps = 
                ( iMaxZoomStep * row ) / divider;
            const TInt previousZoomStartSteps = 
                ( iMaxZoomStep * ( row - 1 ) ) / divider;

            if ( ( currentZoomStep >= zoomStartSteps ) &&
                 ( previousZoomStartSteps != zoomStartSteps ) )
                {
                aFullSteps = ( row + 1 );
                zoomDeltaSteps = currentZoomStep - zoomStartSteps;
                zoomDeltaMaxSteps = ( iMaxZoomStep * ( row + 1 ) ) / divider;
                zoomDeltaMaxSteps -= zoomStartSteps;
                break;
                }
            }

        aPartialStep = 0;
        if ( zoomDeltaSteps && zoomDeltaMaxSteps )
            {
            TInt64 partial( zoomDeltaSteps );
            partial *= KVtUiZoomControlOne;
            partial /= zoomDeltaMaxSteps;
            
            partial >>= ( KVtUiZoomControlFixed - KVtUiZoomControlPartial );
            aPartialStep = I64INT( partial );
            }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::GenerateZoomMaskBitmap
// -----------------------------------------------------------------------------
//
TBool CVtUiZoomControl::GenerateZoomMaskBitmap(
        CFbsBitmap* aMaskBitmap,    
        const TInt aPartial,
        const TInt aRow,
        const TSize& aRowSize ) const
    {
    if ( iZoomPartialMask && 
         ( ( iZoomMaskPartial != aPartial ) || 
           ( iZoomMaskRow != aRow ) ) )
        {
        DoGenerateZoomMaskBitmap( 
            aMaskBitmap,
            aPartial, 
            aRow,
            aRowSize );
        }
    return ( iZoomPartialMask != NULL );
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::DoGenerateZoomMaskBitmap
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::DoGenerateZoomMaskBitmap(
        CFbsBitmap* aMaskBitmap,
        const TInt aPartial,
        const TInt aRow,
        const TSize& aRowSize ) const
    {
    CFbsBitGc* bitmapMaskGc = iZoomPartialMask->Context();
    
    CFbsBitmap* shade = iZoomPartialShade->Bitmap();
    CFbsBitGc* shadeGc = iZoomPartialShade->Context();

    // Fill shade with aPartial.
    shadeGc->SetPenStyle( CGraphicsContext::ENullPen );
    shadeGc->SetBrushColor( TRgb::Gray256( aPartial ) );
    shadeGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    shadeGc->Clear(); 
    
    // Now grab one row from iZoomAreaBitmap.
    CFbsBitmap* mask = iZoomPartialShadeMask->Bitmap();
    CFbsBitGc* maskGc = iZoomPartialShadeMask->Context();

    // Clear with transparency.
    maskGc->SetPenStyle( CGraphicsContext::ENullPen );
    maskGc->SetBrushColor( TRgb::Gray2( 1 ) ); // transparency
    maskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    maskGc->Clear(); 

    maskGc->SetPenStyle( CGraphicsContext::ENullPen );
    // Blit appropriate region from aMaskBitmap to maskGc.
    maskGc->BitBlt( 
        TPoint( 0, aRow ), 
        aMaskBitmap, 
        TRect( TPoint( 0, aRow ), aRowSize ) );

    // Now fill bitmapMask with black (= transparency).
    bitmapMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
    bitmapMaskGc->SetBrushColor( TRgb::Gray256( KVtUiZoomTransparent ) );
    bitmapMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    bitmapMaskGc->Clear();

    // Then blit shade masked
    TPoint origin;
    TRect rect( origin, shade->SizeInPixels() );

    bitmapMaskGc->BitBltMasked( origin, shade, rect, mask, ETrue );

    iZoomMaskPartial = aPartial;
    iZoomMaskRow = aRow;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CreateBitmaps
// -----------------------------------------------------------------------------
//
TInt CVtUiZoomControl::CreateBitmaps()
    {
    TRAPD( err, CreateBitmapsL() );
    return err;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CreateBitmapsL
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::CreateBitmapsL()
    {
    TBool requiredToCreate = ETrue;
    TSize requiredSize = SizeOfBitmap();
    if ( iZoomPartialMask )
        {
        requiredToCreate = 
            ( requiredSize != iZoomPartialMask->Bitmap()->SizeInPixels() );
        }

    if ( requiredToCreate )
        {
        iZoomMaskPartial = KErrNotFound;
        iZoomMaskRow = KErrNotFound;

        // Delete old ones away.
        delete iZoomPartialMask;
        iZoomPartialMask = NULL;

        delete iZoomPartialShade;
        iZoomPartialShade = NULL;

        delete iZoomPartialShadeMask;
        iZoomPartialShadeMask = NULL;

        CBitmap* zoomPartialMask = new ( ELeave ) CBitmap;
        CleanupStack::PushL( zoomPartialMask );
        zoomPartialMask->ConstructL( requiredSize, EGray256 );

        CBitmap* zoomPartialShade = new ( ELeave ) CBitmap;
        CleanupStack::PushL( zoomPartialShade );
        zoomPartialShade->ConstructL( requiredSize, EGray256 );

        CBitmap* zoomPartialShadeMask = new ( ELeave ) CBitmap;
        CleanupStack::PushL( zoomPartialShadeMask );
        zoomPartialShadeMask->ConstructL( requiredSize, EGray2 );
    
        // Pop zoomPartialShadeMask, zoomPartialShade & zoomPartialMask.
        CleanupStack::Pop( 3, zoomPartialMask ); 
        iZoomPartialMask = zoomPartialMask;
        iZoomPartialShade = zoomPartialShade;
        iZoomPartialShadeMask = zoomPartialShadeMask;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::SizeOfBitmap
// -----------------------------------------------------------------------------
//
TSize CVtUiZoomControl::SizeOfBitmap() const
    {
    // Bitmaps fill the whole zoom area.
    return iZoomAreaLayout.Rect().Size();
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::GetPositionAndRect
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::GetPositionAndRect(
        TPoint& aPosition,
        TRect& aSourceRect,
        const TInt aZoomStep ) const
    {
    TAknWindowLineLayout rect;
    TAknLayoutRect layout;
    const TRect zoomAreaRect = iZoomAreaLayout.Rect();
    const TRect& zoomParentRect = iZoomPaneRect;

    VtUiLayout::GetZoomStepLayout( 
        rect, 
        aZoomStep ); 
    layout.LayoutRect( zoomParentRect, rect );
    aSourceRect = layout.Rect();
    aPosition = aSourceRect.iTl;

    aSourceRect.iTl -= zoomAreaRect.iTl;
    aSourceRect.iBr -= zoomAreaRect.iTl;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CBitmap::CBitmap
// -----------------------------------------------------------------------------
//
CVtUiZoomControl::CBitmap::CBitmap()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CBitmap::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiZoomControl::CBitmap::ConstructL( 
        const TSize& aSize,
        const TDisplayMode aMode )
    {
    CFbsBitmap* bitmap = new ( ELeave ) CFbsBitmap;
    CleanupStack::PushL( bitmap );

    User::LeaveIfError(
        bitmap->Create( aSize, aMode ) );

    CFbsBitmapDevice* device = CFbsBitmapDevice::NewL( bitmap );
    CleanupStack::PushL( device );

    CFbsBitGc* context = NULL;
    User::LeaveIfError( device->CreateContext( context ) );
    User::LeaveIfNull( context );

    CleanupStack::Pop( device );
    CleanupStack::Pop( bitmap );

    iContext = context;
    iDevice = device;
    iBitmap = bitmap;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CBitmap::~CBitmap
// -----------------------------------------------------------------------------
//
CVtUiZoomControl::CBitmap::~CBitmap()
    {
    delete iContext;
    delete iDevice;
    delete iBitmap;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CBitmap::Bitmap
// -----------------------------------------------------------------------------
//
inline CFbsBitmap* CVtUiZoomControl::CBitmap::Bitmap() const
    {
    return iBitmap;
    }

// -----------------------------------------------------------------------------
// CVtUiZoomControl::CBitmap::Context
// -----------------------------------------------------------------------------
//
inline CFbsBitGc* CVtUiZoomControl::CBitmap::Context() const
    {
    return iContext;
    }

//  End of File  

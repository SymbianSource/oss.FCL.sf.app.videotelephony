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
* Description:  Base class for video control.
*
*/


#ifndef C_VTUIVIDEOCONTROLBASE_H
#define C_VTUIVIDEOCONTROLBASE_H

#include    <coecntrl.h>
#include    <aknutils.h>
#include    <babitflags.h>

#include    "MVtUiVideoWindow.h"
#include    "CVtUiBitmapManager.h"

// FORWARD DECLARATIONS
class CVtUiBitmapManager;
class TAknTextLineLayout;
class CAknsBasicBackgroundControlContext;
/**
 *  CVtUiVideoControlBase
 *
 *  Video control base class.
 *
 *  @since S60 v5.0
 */
class CVtUiVideoControlBase : public CCoeControl, public MVtUiVideoWindow
    {

protected: // enumerations

    // Rendering hints
    enum TRenderingHint
        {
        // If this hint is set, then control's background is filled with color
        // at index 0. This hint is mutually exclusive with ESkinnedBackground.
        // If neither EColoredBackground nor ESkinnedBackground is set, then
        // no background drawing is done.
        EColoredBackground,

        // If this is set, then control's background is skinned. This hint is
        // mutually exclusive with EColoredBackground. If neither
        // EColoredBackground nor ESkinnedBackground is set, then no background
        // drawing is done.
        ESkinnedBackground,

        // If this hint is set, then no blind icon is drawn.
        ENoBlindIcon,

        // If this hint is set, then no waiting text is shown.
        ENoWaitingText
        };

public:

    /**
     * Destructor
     */
    ~CVtUiVideoControlBase();

protected:

    /**
     * Constructor
     */
    CVtUiVideoControlBase( CVtUiBitmapManager& aBitmapManager );

    /**
     * 2nd constructor
     */
    void BaseConstructL();

    /**
    * Sets (enables) rendering hints
    */
    void SetRenderingHint( TRenderingHint aHint );

    /**
    * Clears (disables) rendering hints
    */
    void ClearRenderingHint( TRenderingHint aHint );

    /**
    * Returns reference to bitmap manager.
    */
    CVtUiBitmapManager& BitmapManager() const;

    /**
    * Returns pointer to bitmap with given ID.
    */
    CFbsBitmap* Bitmap( TVtUiBitmapPoolId aId ) const;

    /**
    * Fixes given point suitable for DP (e.g. x coordinates of the point is
    * even).
    */
    TPoint AdjustPointForDP( const TPoint aPoint ) const;

    /**
    * Fixes given rect suitable for DP (e.g. x coordinates and width of the
    * rectangle are even).
    */
    TRect AdjustRectForDP( const TRect aRect ) const;

protected: // virtual methods

    /**
    * Gets waiting text layout.
    */
    virtual TAknTextLineLayout WaitingTextLayout( TInt aLine );

    /**
    * The size changed method. If you need to do special handling after the
    * control's size has changed, overwrite this method.
    */
    virtual void HandleSizeChanged();

    /**
    * Draws control background using current skin. If you need special
    * background rendering in inherited control, override this method.
    * There is no need to check ESkinnedBackground hint again in this method
    * because it has been checked prior to calling.
    */
    virtual void DrawSkinnedBackground( CWindowGc& aGc ) const;

    /**
    * Draws control background using color. If you need special
    * background rendering in inherited control, override this method.
    * There is no need to check EColoredBackground hint again in this method
    * because it has been checked prior to calling.
    */
    virtual void DrawColoredBackground( CWindowGc& aGc ) const;

    /**
    * Draws waiting text. If you need special waiting text rendering in
    * inherited control, override this method.
    * There is no need to check ENoWaitingText hint again in this method
    * because it has been checked prior to calling.
    */
    virtual TBool DrawWaitingText( CWindowGc& aGc ) const;

    /**
    * Draws blind icon. If you need special blind icon rendering in inherited
    * control, override this method.
    * There is no need to check ENoBlindIcon hint again in this method
    * because it has been checked prior to calling.
    */
    virtual void DrawBlind( CWindowGc& aGc ) const;

    /**
    * Draws stream. If you need special stream rendering in inherited control,
    * override this method. iStreamBitmap cannot be NULL if this method is
    * called.
    */
    virtual void DrawStream( CWindowGc& aGc ) const;

    /**
    * Returns blitting position (top-left corner) coordinates for the stream.
    */
    virtual TPoint StreamBlitPosition() const;

    /**
    * Returns clipping rectangle for the stream.
    */
    virtual TRect StreamClippingRect() const;

    /**
    * Returns pointer to blind bitmap or NULL if no bitmap is present.
    */
    virtual CFbsBitmap* BlindImage() const;

    /**
    * Returns pointer to blind mask or NULL if no mask is present.
    */
    virtual CFbsBitmap* BlindMask() const;

    /**
    * Returns blit position for blind icon.
    */
    virtual TPoint BlindBlitPosition() const;

public: // from MVtUiVideoWindow

    /**
    * @see MVtUiVideoWindow::Reset
    */
    void Reset();

    /**
    * @see MVtUiVideoWindow::SetBlind
    */
    void SetBlind( TBool aStatus );

    /**
    * @see MVtUiVideoWindow::SetStreamBitmap
    */
    void SetStreamBitmap( CFbsBitmap* aStreamBitmap );

    /**
    * @see MVtUiVideoWindow::SetStreamBitmapReserve
    */
    void SetStreamBitmapReserve( CFbsBitmap* aStreamBitmap );

    /**
    * @see MVtUiVideoWindow::SetWaiting
    */
    void SetWaiting( TBool aShowWaitingText );

    /**
    * @see MVtUiVideoWindow::Redraw
    */
    void Redraw();

    /**
    * @see CCoeControl::MopSupplyObject
    */
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );

    /**
     * Set remote video control 
     */
    virtual void SetRemoteVideoControl( CCoeControl* aRemoteControl );
    
    /**
     * Layout the postion and the size of the remote video control
      */
    virtual void LayoutRemoteVideo();    
    
    /**
     * Returns pointer to remote video control  or NULL if no remote video control  is present.
     */
    CCoeControl * RemoteVideoControl();
    
private: // from CCoeControl

    /**
    * @see CCoeControl::Draw
    */
    void Draw( const TRect& aRect ) const;

    /**
    * @see CCoeControl::SizeChanged
    */
    void SizeChanged();

    /**
    * @see CCoeControl::PositionChanged
    */
    void PositionChanged();

private:

    /**
    * Redraws stream bitmap.
    */
    void RedrawStream();

    /**
    * Wraps waiting text if needed.
    */
    void WrapOnDemand();

    /**
    * Wraps waiting text.
    */
    void WrapWaitingTextL();

    /**
    * The draw method.
    */
    void DoDraw( CWindowGc& aGc ) const;

    /**
    * Draws control background.
    */
    void DoDrawBackground( CWindowGc& aGc ) const;

    /**
    * Draws waiting text.
    */
    TBool DoDrawWaitingText( CWindowGc& aGc ) const;

    /**
    * Draws blind icon.
    */
    void DoDrawBlind( CWindowGc& aGc ) const;

    /**
    * Draws stream.
    */
    void DoDrawStream( CWindowGc& aGc ) const;

    TBool IsAlphaZero() const;

    void SetAlpha( CWindowGc& aGc ) const;

protected:

    // ETrue if blind icon is shown.
    TBool iBlindStatus;

    // Reference to stream bitmap.
    CFbsBitmap* iStreamBitmap;

    // ETrue if waiting text should be shown.
    TBool iWaitingTextShow;

    // Owned wrapped waiting text.
    HBufC* iWaitingTextWrapped;

    // Owned wrapped waiting text.
    CArrayFix< TPtrC >* iWaitingTextWrappedArray;

    // First line layout of waiting text.
    TAknLayoutText iWaitingTextLine1Layout;

    // Second line layout of waiting text.
    TAknLayoutText iWaitingTextLine2Layout;

    // Owned: background context.
    CAknsBasicBackgroundControlContext* iBgContext;

    // Reference to remote video control.
    CCoeControl* iRemoteVideoControl;    
    
private:

    // Pointer to bitmap manager.
    CVtUiBitmapManager* iBitmapManager;

    // Rendering hints
    TBitFlags32 iHints;

    // FrameUpdate() is called from AO.
    CAsyncCallBack* iAsyncFrameUpdated;

    mutable TBool iSetAlpha;

    };

#endif // C_VTUIVIDEOCONTROLBASE_H

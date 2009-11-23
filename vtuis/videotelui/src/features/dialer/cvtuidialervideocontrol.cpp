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
* Description:  Mini dialer feature
*
*/


#include    <cvtlogger.h>
#include    <aknlayoutscalable_apps.cdl.h>
#include    <aknlayoutscalable_avkon.cdl.h>
#include    <layoutmetadata.cdl.h>

#include "cvtuidialervideocontrol.h"

// Portrait variety constant
const static TInt KVarietyPortrait = 0;

// Landscape variety constant
const static TInt KVarietyLandscape = 1;

// Implementation of CVtUiDialerVideoControl

// ---------------------------------------------------------------------------
// CVtUiDialerVideoControl::NewL
// ---------------------------------------------------------------------------
//
CVtUiDialerVideoControl* CVtUiDialerVideoControl::NewL(
    CVtUiBitmapManager& aBitmapManager )
    {
    __VTPRINTENTER( "DialCtrl.NewL" )
    CVtUiDialerVideoControl* self =
        new ( ELeave ) CVtUiDialerVideoControl( aBitmapManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "DialCtrl.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiDialerVideoControl::~CVtUiDialerVideoControl
// ---------------------------------------------------------------------------
//
CVtUiDialerVideoControl::~CVtUiDialerVideoControl()
    {
    __VTPRINTENTER( "DialCtrl.~" )
    __VTPRINTEXIT( "DialCtrl.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerVideoControl::CVtUiDialerVideoControl
// ---------------------------------------------------------------------------
//
CVtUiDialerVideoControl::CVtUiDialerVideoControl(
    CVtUiBitmapManager& aBitmapManager ) :
    CVtUiVideoControlBase( aBitmapManager )
    {
    __VTPRINTENTER( "DialCtrl.ctor" )
    // Disable blind icon drawing
    SetRenderingHint( ENoBlindIcon );
    __VTPRINTEXIT( "DialCtrl.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiDialerVideoControl::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiDialerVideoControl::ConstructL()
    {
    __VTPRINTENTER( "DialCtrl.ConstructL" )
    BaseConstructL();
    __VTPRINTEXIT( "DialCtrl.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiDialerVideoControl::WaitingTextLayout
// -----------------------------------------------------------------------------
//
TAknTextLineLayout CVtUiDialerVideoControl::WaitingTextLayout( TInt aLine )
    {
    __VTPRINTENTER( "DialCtrl.WaitingTextLayout" )

    TInt variety( Layout_Meta_Data::IsLandscapeOrientation() ?
        KVarietyLandscape : KVarietyPortrait );

    TAknWindowComponentLayout l2(
        AknLayoutScalable_Apps::main_video_tele_dialer_pane( variety ) );

    TAknTextComponentLayout l3;

#if 0
    if ( variety == KVarietyPortrait )
        {
        if ( !aLine )
            {
            l3 = AknLayoutScalable_Apps::main_video_tele_dialer_pane_t1( 0 );
            }
        else
            {
            l3 = AknLayoutScalable_Apps::main_video_tele_dialer_pane_t2( 0 );
            }
        }
    else
        {
        if ( !aLine )
            {
            l3 = AknLayoutScalable_Apps::call_video_pane_t1();
            }
        else
            {
            l3 = AknLayoutScalable_Apps::call_video_pane_t2();
            }
        }
#endif

    if ( !aLine )
        {
        l3 = AknLayoutScalable_Apps::main_video_tele_dialer_pane_t1( 0 );
        }
    else
        {
        l3 = AknLayoutScalable_Apps::main_video_tele_dialer_pane_t2( 0 );
        }
    
    __VTPRINTEXIT( "DialCtrl.WaitingTextLayout" )
    return TAknWindowComponentLayout::ComposeText( l2, l3 ).LayoutLine();
    }

// -----------------------------------------------------------------------------
// CVtUiMainControl::LayoutRemoteVideo
// -----------------------------------------------------------------------------
//
void CVtUiDialerVideoControl::LayoutRemoteVideo( )
    {    
    __VTPRINTENTER( "DialCtrl.LayoutRemoteVideo" )
    if ( NULL != iRemoteVideoControl )
        {
        TRect rectRemoteVideo(StreamClippingRect());
        rectRemoteVideo.Move(PositionRelativeToScreen());
        iRemoteVideoControl->SetExtent(rectRemoteVideo.iTl,rectRemoteVideo.Size());
        }
    __VTPRINTEXIT( "DialCtrl.LayoutRemoteVideo" )
    }

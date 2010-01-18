/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiRemoteVideoControl
*                control class.
*
*/


// INCLUDE FILES
#include    <cvtlogger.h>
#include   <eikdef.h>
#include    <AknIncallBubbleNotify.h>
#include    <aknslayeredbackgroundcontrolcontext.h>
#include    <aknutils.h>
#include    <aknnavi.h>
#include    <akntitle.h>
#include    <akndlgshut.h>
#include    <aknnotedialog.h>
#include    <aknnotewrappers.h>
#include    <akncontext.h>
#include    <eikspane.h>
#include    <eikmenup.h>
#include    <eikmenub.h>
#include    <apgcli.h>
#include    <featmgr.h>
#include    <videotelui.rsg>
#include    <hlplch.h>
#include    <apgwgnam.h>
#include    <stringloader.h>
#include    <akndef.h>
#include    <aknconsts.h>
#include    "CVtUiRemoteVideoControl.h"
#include    "CVtUiAppUi.h"
#include    "CVtUiContextControl.h"


// Implementation of CVtUiRemoteVideoControl

// -----------------------------------------------------------------------------
// CVtUiRemoteVideoControl::NewL
// -----------------------------------------------------------------------------

CVtUiRemoteVideoControl* CVtUiRemoteVideoControl::NewL( CVtUiAppUi& aAppUi)
    {
    __VTPRINTENTER( "RemoteVideoControl.NewL" )
    CVtUiRemoteVideoControl* self = new ( ELeave ) CVtUiRemoteVideoControl(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop(); // self
    __VTPRINTEXIT( "RemoteVideoControl.NewL" )
    return self;

    }
// ---------------------------------------------------------------------------
// CVtUiRemoteVideoControl::~CVtUiRemoteVideoControl
// ---------------------------------------------------------------------------
//
CVtUiRemoteVideoControl::~CVtUiRemoteVideoControl()
    {    
    __VTPRINTENTER( "RemoteVideoControl.~" )
    __VTPRINTEXIT( "RemoteVideoControl.~" )
    }

// ---------------------------------------------------------------------------
// CVtUiRemoteVideoControl::CVtUiVideoControlBase
// ---------------------------------------------------------------------------
//
CVtUiRemoteVideoControl::CVtUiRemoteVideoControl( CVtUiAppUi& aAppUi):
    iAppUi(aAppUi)
    {
    __VTPRINTENTER( "RemoteVideoControl.ctor" )
    __VTPRINTEXIT( "RemoteVideoControl.ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiRemoteVideoControl::BaseConstructL
// ---------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::ConstructL()
    {
    __VTPRINTENTER( "RemoteVideoControl.ConstructL" )
    CreateWindowL();
    SetExtent( TPoint(), TSize() );
    ActivateL();
    //Window().SetNonFading( ETrue );    
    __VTPRINTEXIT( "RemoteVideoControl.ConstructL" )
    }

RWindow& CVtUiRemoteVideoControl::GetRWindow()
    {
    __VTPRINTENTER( "RemoteVideoControl.GetRWindow" )
    __VTPRINTEXIT( "RemoteVideoControl.GetRWindow" )
    return Window();
    }

// ---------------------------------------------------------------------------
// CVtUiRemoteVideoControl::HandleSizeChanged
// ---------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::HandleSizeChanged()
    {
    __VTPRINTENTER( "RemoteVideoControl.HandleSizeChanged" )    
    __VTPRINTEXIT( "RemoteVideoControl.HandleSizeChanged" )
    }

// -----------------------------------------------------------------------------
// CVtUiRemoteVideoControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::SizeChanged()
    {
    __VTPRINTENTER( "RemoteVideoControl.SizeChanged" )
    TPoint position = Position();
    TRect rect = Rect();
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl position x:%d", position.iX )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl position y:%d", position.iY )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iTl.x:%d", rect.iTl.iX )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iTl.y:%d", rect.iTl.iY )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iBr.x:%d", rect.iBr.iX )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iBr.y:%d", rect.iBr.iY )

    __VTPRINTEXIT( "RemoteVideoControl.SizeChanged" )
    }

// -----------------------------------------------------------------------------
// CVtUiRemoteVideoControl::PositionChanged
// -----------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::PositionChanged()
    {
    __VTPRINTENTER( "RemoteVideoControl.PositionChanged" )
    __VTPRINTEXIT( "RemoteVideoControl.PositionChanged" )
    }

// ---------------------------------------------------------------------------
// CVtUiRemoteVideoControl::Draw
// ---------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::Draw( const TRect& ) const
    {
    __VTPRINTENTER( "RemoteVideoControl.Draw" )
    //DoDraw( SystemGc() );
    __VTPRINTEXIT( "RemoteVideoControl.Draw" )
    }

// ---------------------------------------------------------------------------
// CVtUiRemoteVideoControl::DoDraw
// ---------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::DoDraw( CWindowGc& aGc ) const
    {
    __VTPRINTENTER( "RemoteVideoControl.DoDraw(gc)" )
 
   aGc.SetBrushStyle( CGraphicsContext::ESolidBrush );
   aGc.SetPenStyle( CGraphicsContext::ENullPen );
   aGc.SetBrushColor( KRgbRed );
   aGc.DrawRect( Rect() );
   aGc.SetBrushStyle( CGraphicsContext::ENullBrush );
    
    TPoint position = Position();
    TRect rect = Rect();
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl position x:%d", position.iX )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl position y:%d", position.iY )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iTl.x:%d", rect.iTl.iX )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iTl.y:%d", rect.iTl.iY )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iBr.x:%d", rect.iBr.iX )
    __VTPRINT2( DEBUG_GEN, "CVtUiRemoteVideoControl rect iBr.y:%d", rect.iBr.iY )

    __VTPRINTEXIT( "RemoteVideoControl.DoDraw(gc)" )
    }

// -----------------------------------------------------------------------------
// CVtUiRemoteVideoControl::HandlePointerEventL
// -----------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::HandlePointerEventL(
    const TPointerEvent& aPointerEvent)
    {
    __VTPRINTENTER( "RemoteVideoControl.HandlePointerEventL" )
    
    if(iAppUi.ContextControl().RemoteVideoControl())
        {
        iAppUi.ContextControl().HandlePointerEventL(aPointerEvent);
        }
    
    __VTPRINTEXIT( "RemoteVideoControl.HandlePointerEventL" )
    }

// -----------------------------------------------------------------------------
// CVtUiRemoteVideoControl::HandleWsEventL
// -----------------------------------------------------------------------------
//
void CVtUiRemoteVideoControl::HandleWsEventL( const TWsEvent& aEvent,
    CCoeControl* aDestination )
    {
    __VTPRINTENTER( "RemoteVideoControl.HandleWsEventL" )
    
    if(iAppUi.ContextControl().RemoteVideoControl())
    {
    iAppUi.ContextControl().HandleWsEventL( aEvent, aDestination );
    }    
    
    __VTPRINTEXIT( "RemoteVideoControl.HandleWsEventL" )
    }

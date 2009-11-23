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
* Description:  Implementation of the CVtUiBlankControl control class.
*
*/



// INCLUDE FILES
#include    "CVtUiBlankControl.h"
#include    <aknsutils.h>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiBlankControl::CVtUiBlankControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiBlankControl::CVtUiBlankControl()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiBlankControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiBlankControl::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    MakeVisible( EFalse );
    SetRect( aRect );
    }

// -----------------------------------------------------------------------------
// CVtUiBlankControl::~CVtUiBlankControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiBlankControl::~CVtUiBlankControl()
    {
    AknsUtils::DeregisterControlPosition( this );
    }

// -----------------------------------------------------------------------------
// CVtUiBlankControl::SetActive
// -----------------------------------------------------------------------------
//
void CVtUiBlankControl::SetActive( TBool aStatus )
    {
    iBlankerActive = aStatus;
    }

// -----------------------------------------------------------------------------
// CVtUiBlankControl::OfferKeyEventL
// -----------------------------------------------------------------------------
//
TKeyResponse CVtUiBlankControl::OfferKeyEventL(
        const TKeyEvent& /*aKeyEvent*/,
        TEventCode /*aType*/ )
    {
    return iBlankerActive ? EKeyWasConsumed : EKeyWasNotConsumed;
    }

// -----------------------------------------------------------------------------
// CVtUiBlankControl::Draw
// -----------------------------------------------------------------------------
//
void CVtUiBlankControl::Draw( const TRect& /*aRect*/ ) const
    {
    }

// -----------------------------------------------------------------------------
// CVtUiBlankControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiBlankControl::SizeChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

// -----------------------------------------------------------------------------
// CVtUiBlankControl::PositionChanged
// -----------------------------------------------------------------------------
//
void CVtUiBlankControl::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

//  End of File

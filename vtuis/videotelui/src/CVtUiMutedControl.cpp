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
* Description:  Implementation of the CVtUiMutedControl control class.
*
*/



// INCLUDE FILES
#include    "CVtUiMutedControl.h"
#include    "VtUiLayout.h"
#include    <eiklabel.h>
#include    <aknsutils.h>
#include    <aknsdrawutils.h>
#include    <stringloader.h>
#include    <videotelui.rsg>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiMutedControl::CVtUiMutedControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiMutedControl::CVtUiMutedControl()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiMutedControl::ConstructL()
    {
    HBufC* mutedText = 
        StringLoader::LoadLC( R_VIDEOTELUI_QTN_INCAL_MUTED_PANE );

    iMutedLabel = new ( ELeave ) CEikLabel;
    iMutedLabel->SetContainerWindowL( *this );
    iMutedLabel->SetTextL( *mutedText );

    CleanupStack::PopAndDestroy( mutedText );
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::~CVtUiMutedControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiMutedControl::~CVtUiMutedControl()
    {
    AknsUtils::DeregisterControlPosition( this );

    delete iMutedLabel;
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CVtUiMutedControl::HandleResourceChange(
        TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );

    if ( aType == KAknsMessageSkinChange )
        {
        SizeChanged();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::Draw
// -----------------------------------------------------------------------------
//
void CVtUiMutedControl::Draw( const TRect& /*aRect*/ ) const
    {
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiMutedControl::SizeChanged()
    {
    AknsUtils::RegisterControlPosition( this );

    TRect naviPane( Rect() );
    if ( naviPane.IsEmpty() )
        {
        return;
        }

    TAknTextLineLayout label;
    VtUiLayout::GetMutedTextLayout( label );

    AknLayoutUtils::LayoutLabel( iMutedLabel, naviPane, label );

    // Update label color
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();        
    TRgb skinColor;

    TInt error = 
        AknsUtils::GetCachedColor( 
            skin, 
            skinColor, 
            KAknsIIDQsnTextColors,
            EAknsCIQsnTextColorsCG2 );

    if ( ( error == KErrNone ) && iMutedLabel )
        {
        // Ignore error
        TRAP_IGNORE(  
            iMutedLabel->OverrideColorL( EColorLabelText, skinColor ) );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::PositionChanged
// -----------------------------------------------------------------------------
//
void CVtUiMutedControl::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::CountComponentControls
// -----------------------------------------------------------------------------
//
TInt CVtUiMutedControl::CountComponentControls() const
    {
    return 1; // one label
    }

// -----------------------------------------------------------------------------
// CVtUiMutedControl::ComponentControl
// -----------------------------------------------------------------------------
//
CCoeControl* CVtUiMutedControl::ComponentControl(
        TInt /*aIndex*/ ) const
    {
    return iMutedLabel;
    }

//  End of File  

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
* Description:  Implementation of the CVtUiNaviPaneControl control class.
*
*/



// INCLUDE FILES
#include    "CVtUiNaviPaneControl.h"
#include    "CVtUiNaviPane.h"
#include    "VtUiLayout.h"
#include    <AknsUtils.h>
#include    <AknsDrawUtils.h>

// CONSTANTS

// There are sixty seconds in one minute.
const TInt KVtUiOneMinuteInSeconds = 60;

// There are sixty minutes in one hour.
const TInt KVtUiOneHourInSeconds = 3600;

// Maximum duration is 99:59:59.
const TInt KVtUiMaxDurationInSeconds = 
    99*KVtUiOneHourInSeconds + 
    59*KVtUiOneMinuteInSeconds +
    59;

// Amount of digits.
const TInt KVtUiDigits = 10;

// Index of time separator.
const TInt KVtUiSeparatorTime = 0;

// Index of hour separator.
const TInt KVtUiSeparatorHour = 1;

// Index of minute separator.
const TInt KVtUiSeparatorMinute = 2;

// Index of second separator.
const TInt KVtUiSeparatorSecond = 3;

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::CVtUiNaviPaneControl
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiNaviPaneControl::CVtUiNaviPaneControl( CVtUiNaviPane& aNaviPane )
    : iNaviPane ( aNaviPane )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::ConstructL()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::~CVtUiNaviPaneControl
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiNaviPaneControl::~CVtUiNaviPaneControl()
    {
    AknsUtils::DeregisterControlPosition( this );
    }
    
// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::SetCallDuration
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::SetCallDuration( 
        const TTimeIntervalSeconds& aDuration,
        const TBool aEnabled )
    {
    iCallDurationEnabled = aEnabled;
    iCallDuration = aDuration;
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::CommitL
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::CommitL()
    {
    ReportEventL( MCoeControlObserver::EEventStateChanged ); 
    }
    
// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::Draw
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::Draw( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    
    const TDesC& callDurationText = GetCallDurationText();
    if ( callDurationText.Length() )
        {
        TRgb color = iCallDurationLayout.Color();
        // Color is not updated if it not found from the skin
        AknsUtils::GetCachedColor(
            skin,
            color,
            KAknsIIDQsnTextColors,
            EAknsCIQsnTextColorsCG2 );
        iCallDurationLayout.DrawText( gc, callDurationText, EFalse, color );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::SizeChanged
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::SizeChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    TAknWindowLineLayout rect;
    TRect parent( Rect() );
    if ( parent.IsEmpty() )
        {
        return;
        }

    TAknTextLineLayout text;
    VtUiLayout::GetCallDurationTextLayout( text );
    iCallDurationLayout.LayoutText( parent, text );
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::PositionChanged
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::PositionChanged()
    {
    AknsUtils::RegisterControlPosition( this );
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::GetCallDurationText
// -----------------------------------------------------------------------------
//
const TDesC& CVtUiNaviPaneControl::GetCallDurationText() const
    {
    iCallDurationBuffer.Zero();

    if ( iCallDurationEnabled )
        {
        TLocale locale;
    
        TInt durationInseconds = iCallDuration.Int();
        if ( durationInseconds > KVtUiMaxDurationInSeconds )
            {
            durationInseconds = KVtUiMaxDurationInSeconds;
            }

        const TInt hours = durationInseconds / KVtUiOneHourInSeconds;
        const TInt secondsLeft = 
            durationInseconds - ( hours * KVtUiOneHourInSeconds );

        const TInt minutes = secondsLeft / KVtUiOneMinuteInSeconds;
        const TInt seconds = 
            secondsLeft - ( minutes * KVtUiOneMinuteInSeconds );

        AppendChar( 
            iCallDurationBuffer, 
            locale.TimeSeparator( KVtUiSeparatorTime ) );

        AppendNum( 
            iCallDurationBuffer,
            hours );
    
        AppendChar( 
            iCallDurationBuffer, 
            locale.TimeSeparator( KVtUiSeparatorHour ) );
    
        AppendNum( 
            iCallDurationBuffer, 
            minutes );

        AppendChar( 
            iCallDurationBuffer, 
            locale.TimeSeparator( KVtUiSeparatorMinute ) );

        AppendNum( 
            iCallDurationBuffer, 
            seconds );

        AppendChar( 
            iCallDurationBuffer, 
            locale.TimeSeparator( KVtUiSeparatorSecond ) );

        // Convert numbers to display language.
        AknTextUtils::DisplayTextLanguageSpecificNumberConversion( 
            iCallDurationBuffer );
        }

    return iCallDurationBuffer;
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::AppendChar
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::AppendChar( 
        TDes& aBuffer,
        const TChar& aChar )
    {
    if ( aChar )
        {
        aBuffer.Append( aChar );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPaneControl::AppendNum
// -----------------------------------------------------------------------------
//
void CVtUiNaviPaneControl::AppendNum(
        TDes& aBuffer,
        TInt aNumber )
    {
    if ( aNumber < 0 )
        {
        aNumber = 0;
        }

    const TInt firstDigit = ( aNumber / KVtUiDigits ) % KVtUiDigits;
    const TInt secondDigit = ( aNumber % KVtUiDigits );

    aBuffer.AppendNum( firstDigit );
    aBuffer.AppendNum( secondDigit );
    }

//  End of File  

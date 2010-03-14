/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiNaviPane class.
*
*/



// INCLUDE FILES
#include    "CVtUiNaviPane.h"
#include    "CVtUiNaviPaneControl.h"
#include    "CVtUiMutedControl.h"
#include    "CVtUiAppUi.h"

#include    <cvtlogger.h>
#include    <avkon.rsg>
#include    <aknnavi.h>
#include    <aknnavide.h>
#include    <featmgr.h>
#include	"tVtuifeaturevariation.h"
#include    <StringLoader.h>
#include    <videotelui.rsg>

// CONSTANTS

// Timeout after which voice volume bar is switched back to indicators.
const TInt KVtUiVoiceVolumeTimeout = 2000000;

// LOCAL FUNCTION PROTOTYPES

/**
* Creates navigation decorator.
* @param aNaviPane reference to navi pane.
* @param aControl control to be decorated, ownership passed.
* @return new navigation decorator instance.
*/
CAknNavigationDecorator* CreateDecoratorL(
    CAknNavigationControlContainer& aNaviPane,
    CCoeControl* aControl );

// ============================= LOCAL FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CreateDecoratorL Creates navigation decorator.
// Returns: new navigation decorator instance.
// -----------------------------------------------------------------------------
//
CAknNavigationDecorator* CreateDecoratorL(
        CAknNavigationControlContainer& aNaviPane,
        CCoeControl* aControl )
    {
    CAknNavigationDecorator* decoratedFolder =
        CAknNavigationDecorator::NewL(
            &aNaviPane,
            aControl,
            CAknNavigationDecorator::ENotSpecified );

    CleanupStack::PushL( decoratedFolder );
    decoratedFolder->SetContainerWindowL( aNaviPane );
    aControl->SetContainerWindowL( *decoratedFolder );
    CleanupStack::Pop( decoratedFolder );

    decoratedFolder->MakeScrollButtonVisible( EFalse );

    return decoratedFolder;
    }

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiNaviPane::CVtUiNaviPane
// -----------------------------------------------------------------------------
//
CVtUiNaviPane::CVtUiNaviPane(
        CAknNavigationControlContainer& aNaviPane,
        CVtUiAppUi& aAppUi )
    : CActive( CActive::EPriorityStandard ),
      iNaviPane( aNaviPane ),
      iAppUi ( aAppUi )
    {
    CActiveScheduler::Add( this );
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::ConstructL
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::ConstructL( )
    {
    // Create the navi pane indicator (call duration).
        {
        CVtUiNaviPaneControl* naviControl =
            new ( ELeave ) CVtUiNaviPaneControl( *this );
        CleanupStack::PushL( naviControl );
        naviControl->ConstructL();
        CleanupStack::Pop( naviControl );

        iMainIndicators =
            CreateDecoratorL( iNaviPane, naviControl );

        iNaviPaneControl = naviControl;
        }

    // Create muted indicator.
        {
        HBufC* mutedText = 
            StringLoader::LoadLC( R_VIDEOTELUI_QTN_INCAL_MUTED_PANE ); 

        iMutedIndicator = iNaviPane.CreateNavigationLabelL( *mutedText );
        
        CleanupStack::PopAndDestroy( mutedText );
        }

    User::LeaveIfError( iTimer.CreateLocal() );

    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::NewL
// -----------------------------------------------------------------------------
//
CVtUiNaviPane* CVtUiNaviPane::NewL(
        CAknNavigationControlContainer& aNaviPane,
        CVtUiAppUi& aAppUi )
    {
    CVtUiNaviPane* self =
        new ( ELeave ) CVtUiNaviPane(
            aNaviPane, aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::~CVtUiNaviPane
// -----------------------------------------------------------------------------
//
CVtUiNaviPane::~CVtUiNaviPane()
    {
    Cancel();

    delete iMainIndicators;
    delete iMutedIndicator;

    iTimer.Close();
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::SetCurrentSpeaker
// Parameter aLoudspeaker defines which speaker is used.
// ETrue for loudspeaker, EFalse for handset.
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::SetCurrentSpeaker( const TBool aLoudspeaker )
    {
    if( iLoudspeaker != aLoudspeaker )
        {
        Cancel();
        if( iCallDurationEnabled || iMicrophoneMuted )
            {
            iSliderType = ENone;
            }
        }
    iLoudspeaker = aLoudspeaker;
    }


// -----------------------------------------------------------------------------
// CVtUiNaviPane::SetMuted
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::SetMuted(
        const TBool aStatus )
    {
    __VTPRINT2( DEBUG_GEN, "NaviPane.SetMuted.aStatus=%d", aStatus )
    if( iMicrophoneMuted != aStatus )
        {
        Cancel();
        // if volume indicator is shown when audio is umuted
        // volume indicator won't be dismissed and call duration
        // will not be shown
        if( iCallDurationEnabled || aStatus )
            {
            iSliderType = ENone;
            }
        }
    iMicrophoneMuted = aStatus;
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::SetCallDuration
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::SetCallDuration(
        const TTimeIntervalSeconds& aDuration,
        const TBool aEnabled )
    {
    iCallDurationEnabled = aEnabled;
    iNaviPaneControl->SetCallDuration( aDuration, aEnabled );
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::CommitL
//
// Priority order of different navi pane elements is the following:
// 1. Muted indicator
// 2. Main indicators (call duration)
//
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::CommitL()
    {
    CAknNavigationDecorator* selected = DefaultIndicator();

    PushL( selected );

    // If current is main indicators, then update now.
    if ( iCurrent == iMainIndicators )
        {
        iNaviPaneControl->CommitL();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::GetSpeakerVolume
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::GetSpeakerVolume(
        const TBool ,
        TInt& aValue ) const
    {
    aValue = 0;
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::HandleResourceChange
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::HandleResourceChange(
        TInt aType )
    {
    // iCurrent will get event through navi pane.
    if ( iMainIndicators != iCurrent )
        {
        iMainIndicators->HandleResourceChange( aType );
        iNaviPaneControl->HandleResourceChange( aType );
        }
    if ( iMutedIndicator != iCurrent )
        {
        iMutedIndicator->HandleResourceChange( aType );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::DoCancel
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::DoCancel()
    {
    iTimer.Cancel();
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::RunL
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::RunL()
    {
    iSliderType = ENone;
    CAknNavigationDecorator* selected = DefaultIndicator();
    if ( selected )
        {
        PushL( selected );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::PushAfterTimeout
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::PushAfterTimeout()
    {
    Cancel();
    iTimer.After( iStatus, KVtUiVoiceVolumeTimeout );
    SetActive();
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::PushL
// -----------------------------------------------------------------------------
//
void CVtUiNaviPane::PushL( CAknNavigationDecorator* aNew )
    {
    if ( !aNew )
        {
        if ( iCurrent )
            {
            iNaviPane.Pop();
            iCurrent = NULL;
            }
        else
            {
            iNaviPane.PushDefaultL();
            }
        }
    else if ( iCurrent != aNew )
        {
        // If current not defined, then push to navi pane. This should be called
        // during construction.
        if ( !iCurrent )
            {
            iNaviPane.PushL( *aNew );
            iCurrent = aNew;
            }
        // Otherwise replace the old one.
        else
            {
            iNaviPane.ReplaceL( *iCurrent, *aNew );
            iCurrent = aNew;
            }
        }
    }

// -----------------------------------------------------------------------------
// CVtUiNaviPane::DefaultIndicator
// Returns default indicator. Note that this does not include temporary
// zoom indicator.
// -----------------------------------------------------------------------------
//
CAknNavigationDecorator* CVtUiNaviPane::DefaultIndicator() const
    {
    CAknNavigationDecorator* selected = NULL;

    if ( IsActive() )
        {
        selected = iMainIndicators;
        }
    else if ( iMicrophoneMuted && iSliderType != EVolume && iSliderType != EZoom )
        {
        selected = iMutedIndicator;
        }
     else if ( iCallDurationEnabled && iSliderType != EVolume && iSliderType != EZoom )
        {
        selected = iMainIndicators;
        }

    return selected;
    }

//  End of File

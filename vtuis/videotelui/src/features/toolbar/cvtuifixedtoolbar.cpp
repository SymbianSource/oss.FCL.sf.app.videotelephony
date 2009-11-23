/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Fixed toolbar UI feature implementation.
*
*/


// INCLUDE FILES

#include    "cvtuifixedtoolbar.h"
#include    "cvtuifeaturemanager.h"
#include    "mvtuicomponentmanager.h"
#include    "mvtuicommandmanager.h"
#include    "videotelui.hrh"
#include    "tvtuistates.h"
#include    "cvtuitoolbarcmdpolicy.h"
#include    "cvtuitoolbarskmodifier.h"
#include    "CVtUiAppUi.h"
#include    <videotelui.rsg>
#include    <cvtlogger.h>
#include    <akntoolbar.h>
#include    "tvtuistates.h"
#include    <layoutmetadata.cdl.h>

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::NewL
// -----------------------------------------------------------------------------
//
CVtUiFixedToolbar* CVtUiFixedToolbar::NewL( CVtUiFeatureManager&
     aFeatureManager )
    {
    __VTPRINTENTER( "FixedToolbar.NewL" )
    CVtUiFixedToolbar* self = new ( ELeave ) CVtUiFixedToolbar(
        aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    __VTPRINTEXIT( "FixedToolbar.NewL" )
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::CVtUiFixedToolbar
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiFixedToolbar::CVtUiFixedToolbar( CVtUiFeatureManager&
    aFeatureManager ) : CVtUiToolbarBase( aFeatureManager )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::ConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::ConstructL()
    {
    __VTPRINTENTER( "FixedToolbar.ConstructL" )
    BaseConstructL();

    //create toolbar
    iToolbar = iFeatureManager.AppUi().CurrentFixedToolbar();

    // create and add items into the toolbar
    CreateToolbarButtonsL();

    // Dim all toolbar buttons until first refresh is called
    DimToolbarbuttons( ETrue );

    if ( !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        MakeToolbarVisible( EFalse );
        }

    __VTPRINTEXIT( "FixedToolbar.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::~CVtUiFixedToolbar
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiFixedToolbar::~CVtUiFixedToolbar()
    {
    __VTPRINTENTER( "FixedToolbar.~" )
    delete iIdle;
    __VTPRINTEXIT( "FixedToolbar.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::CreateToolbarButtons
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::CreateToolbarButtonsL()
    {
    __VTPRINTENTER( "FixedToolbar.CreateToolbarButtons" )
    // Default buttons created in base clase
    CVtUiToolbarBase::CreateToolbarButtonsL();

    // toggle microphone
    CreateToolbarItemL( R_AVKONBUTTON_AUDIO_ROUTING_BUTTON,
        EVtUiCmdToolbarAudioRouting, iFeatureManager.AppUi() );


    __VTPRINTEXIT( "FixedToolbar.CreateToolbarButtons" )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::PopulateCmdsIdsL
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::PopulateCmdsIdsL()
    {
    __VTPRINTENTER( "FixedToolbar.PopulateCmdsIdsL" )
    // Default commands populated in base clase
    CVtUiToolbarBase::PopulateCmdsIdsL();

    CVtUiAppUi& appUi = iFeatureManager.AppUi();

    iCmdIds.AppendL( EVtUiCmdActivateBT );
    iCmdIds.AppendL( EVtUiCmdSwitchFromBTToIHF );
    iCmdIds.AppendL( EVtUiCmdActivateLoudspeaker );
    iCmdIds.AppendL( EVtUiCmdDeactivateLoudspeaker );

    __VTPRINTEXIT( "FixedToolbar.PopulateCmdsIdsL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::SetToolbarVisibilityAfterLayoutChangeL
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::SetToolbarVisibilityAfterLayoutChangeL( TBool aVisible )
    {
    // Portrait to landscape show tb
        __VTPRINTENTER( "FixedToolbar.SetToolbarVisibilityAfterLayoutChangeL" )
    if( aVisible )
        {
        __VTPRINT(DEBUG_GEN, "FixedToolbar.SetToolbarVisibilityAfterLayoutChangeL.1" )
        // Set flag
        iFeatureManager.UiStates().SetIsFixedToolbarVisible( ETrue );
        // set visible
        iFeatureManager.AppUi().CurrentFixedToolbar()
            ->SetToolbarVisibility( ETrue );
        // Set callback to dim toolbarbuttons
        if ( !iIdle )
            {
            iIdle = CIdle::NewL( CActive::EPriorityIdle );
            }
        iIdle->Start( TCallBack( &DoDimToolbarButtons, this ) );
        }
    // Landsacpe to portrait hide tb
    else
        {
        __VTPRINT(DEBUG_GEN, "FixedToolbar.SetToolbarVisibilityAfterLayoutChangeL.2" )
        DimToolbarbuttons( EFalse );
        iFeatureManager.AppUi().CurrentFixedToolbar()
            ->SetToolbarVisibility( EFalse );
         // Set flag
        iFeatureManager.UiStates().SetIsFixedToolbarVisible( EFalse );
        }
    __VTPRINTEXIT( "FixedToolbar.SetToolbarVisibilityAfterLayoutChangeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::DimToolbarbuttons
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::DimToolbarbuttons( TBool aIsDimmed )
    {
    __VTPRINTENTER( "FixedToolbar.DimToolbarbuttons" )
    iToolbar->SetItemDimmed( EVtUiCmdToolbarToggleVideo, aIsDimmed, EFalse );
    iToolbar->SetItemDimmed( EVtUiCmdToolbarToggleMicrophone, aIsDimmed, EFalse );
    iToolbar->SetItemDimmed( EVtUiCmdToolbarAudioRouting, aIsDimmed, ETrue );
    __VTPRINTEXITR( "FixedToolbar.DimToolbarbuttons %d", aIsDimmed )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::MakeToolbarVisible
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::MakeToolbarVisible( const TBool aVisible )
    {
    __VTPRINTENTER( "FixedToolbar.MakeToolbarVisible" )
    iFeatureManager.AppUi().CurrentFixedToolbar()->
        SetToolbarVisibility( aVisible );
    iFeatureManager.UiStates().SetIsFixedToolbarVisible( aVisible );
    __VTPRINTEXITR( "FixedToolbar.MakeToolbarVisible %d", aVisible )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::DoShowToolbarL
// -----------------------------------------------------------------------------
//
TInt CVtUiFixedToolbar::DoShowToolbarL( TAny* aAny )
    {
    __VTPRINTENTER( "FixedToolbar.DoShowToolbarL" )
    CVtUiFixedToolbar* self = static_cast< CVtUiFixedToolbar* >( aAny );
    self->iFeatureManager.AppUi().CurrentFixedToolbar()
        ->SetToolbarVisibility( ETrue );
    __VTPRINTEXIT( "FixedToolbar.DoShowToolbarL" )
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::DoToolbarButton
// -----------------------------------------------------------------------------
//
TInt CVtUiFixedToolbar::DoDimToolbarButtons( TAny* aAny )
    {
    __VTPRINTENTER( "FixedToolbar.DoDimToolbarButtons" )
    CVtUiFixedToolbar* self = static_cast< CVtUiFixedToolbar* >( aAny );
    self->DimToolbarbuttons( ETrue );
    __VTPRINTEXIT( "FixedToolbar.DoDimToolbarButtons" )
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::DoActivateL
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::DoActivateL()
    {
    __VTPRINTENTER( "FixedToolbar.DoActivateL" )
    if ( !iFeatureManager.UiStates().IsFixedToolbarVisible() &&
         !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        // reset flag
        iFeatureManager.UiStates().SetIsFixedToolbarVisible( ETrue );
        // Show toolbar with delay in order to prevent overdrawing
        // witht other components.
        iAsyncCallback->Cancel();
        iAsyncCallback->Set( TCallBack( &DoShowToolbarL, this ) );
        iAsyncCallback->CallBack();
        }
    else
        {
        // Undim buttons
        __VTPRINT( DEBUG_GEN, "FixedToolbar.DoDeactivateL.DTB EFalse" )
        // toolbar might be unvisible, because condition in the contructor 
        // "if ( !Layout_Meta_Data::IsLandscapeOrientation() )"
        // will be evaluated ture eventhough the orientation is forced to be landsacepe
        // because it seems that the orientation is still portrait in the constructor phase
        MakeToolbarVisible( ETrue );
        DimToolbarbuttons( EFalse );
        }
    // Start blocking pointer events
    BlockPointerEvents( ETrue );
    // Base class
    CVtUiToolbarBase::DoActivateL();
    __VTPRINTEXIT( "FixedToolbar.DoActivateL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFixedToolbar::DoDeactivateL
// -----------------------------------------------------------------------------
//
void CVtUiFixedToolbar::DoDeactivateL()
    {
    __VTPRINTENTER( "FixedToolbar.DoDeactivateL" )
    iAsyncCallback->Cancel();
    if ( !iFeatureManager.UiStates().IsFixedToolbarVisible() &&
         !Layout_Meta_Data::IsLandscapeOrientation() )
        {
        iFeatureManager.AppUi().CurrentFixedToolbar()
            ->SetToolbarVisibility( EFalse );
        __VTPRINT( DEBUG_GEN, "FixedToolbar.DoDeactivateL.Vs" )
        }
    else
        {
        // Dim all buttons
        __VTPRINT( DEBUG_GEN, "FixedToolbar.DoDeactivateL.DTB ETrue" )
        DimToolbarbuttons( ETrue );
        }
    // Stop blocking pointer events
    BlockPointerEvents( EFalse );
    // Base class
    CVtUiToolbarBase::DoDeactivateL();
    __VTPRINTEXIT( "FixedToolbar.DoDeactivateL" )
    }

//  End of File

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
* Description:  Base class for toolbar.
*
*/


// INCLUDE FILES
#include    <centralrepository.h>
#include    <cvtlogger.h>
#include    <akntoolbar.h>
#include    <featmgr.h>
#include    <StringLoader.h>
#include    <videotelui.rsg>
#include    "videotelui.hrh"
#include    "cvtuitoolbarbase.h"
#include    "mvtuifeature.h"
#include    "tvtuistates.h"
#include    "cvtuitoolbarcontext.h"
#include    "cvtuitoolbarcmdpolicy.h"
#include    "cvtuicommandpolicymanager.h"
#include    "cvtuihidetoolbaritemaction.h"
#include    "cvtuifeaturemanager.h"
#include    "CVtUiAppUi.h"
#include    "mvtuicommandui.h"
#include    "cvtuitoolbarskmodifier.h"
#include    "mvtuicommandmanager.h"
#include    "mvtuicomponentmanager.h"
#include    "cvtuitoolbarbutton.h"
#include    "VideoTelephonyInternalCRKeys.h"
#include 	"tVtuifeaturevariation.h"
#include 	"cvtuitoolbarbutton.h"
#include    <layoutmetadata.cdl.h>

// Implementation of TVtUiToolbarComponentState

// ---------------------------------------------------------------------------
// TVtUiToolbarComponentState::TVtUiToolbarComponentState
// ---------------------------------------------------------------------------
//
TVtUiToolbarComponentState::TVtUiToolbarComponentState(
    MVtUiComponent& aComponent ) :
    TVtUiComponentState( aComponent,
        TVtUiBlockListBitField(
            MVtUiComponent::EComponentIdNull ) )
    {
    }

// ---------------------------------------------------------------------------
// Used in FindToolbaItemByCommandId method to search toolbar item by cmd id.
// ---------------------------------------------------------------------------
//
TInt ToolbarItemIdCmpFunc( const TInt* aId,
    const CVtUiToolbarButton& aToolbarItem )
    {
    return ( *aId - aToolbarItem.CmdId() );
    }


// ---------------------------------------------------------------------------
// Used in CreateToolbarItemL method to search feature by cmd id.
// ---------------------------------------------------------------------------
//
TInt ToolbarCmpFunc( const CVtUiToolbarButton& aV1, const CVtUiToolbarButton& aV2 )
    {
    return ( aV1.CmdId() - aV2.CmdId() );
    }

// ============================ MEMBER FUNCTIONS ===============================


// -----------------------------------------------------------------------------
// CVtUiToolbarBase::CVtUiToolbarBase
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiToolbarBase::CVtUiToolbarBase( CVtUiFeatureManager& aFeatureManager )
    : CVtUiFeatureBase( EVtUiFeatureIdToolbar, aFeatureManager ),
      iComponentState( *this )
    {
    __VTPRINTENTER( "Toolbar.CVtUiToolbarBase" )
    // Get number of supported buttons.
    // Six is the default value for floating toolbar
    // and three buttons for fixed toolbar
    TVtUiToolbarVariation toolbar;
    iNumberOfToolbarButtons = toolbar.NumberOfButtons();
    iCmdFocus = KErrNotFound;
    __VTPRINTEXITR( "Toolbar.CVtUiToolbarBase %d", iNumberOfToolbarButtons )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::BaseConstructL
// Symbian 2nd phase constructor.
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::BaseConstructL()
    {
    __VTPRINTENTER( "Toolbar.ConstructL" )
    CVtUiFeatureBase::BaseConstructL();
    iFeatureManager.UiStates().SetIsToolbarAvailable( ETrue );
    __VTPRINTEXIT( "Toolbar.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::~CVtUiToolbarBase
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiToolbarBase::~CVtUiToolbarBase()
    {
    __VTPRINTENTER( "Toolbar.~" )
    // Stop();
    // Stop can not be called here if toolbar is asked from ui fw = fixed toolbar.
    // If stop is called a crash occurs, whose root cause can not be solved.
    // It is related somehow with focus lost in ui fw.

    Clean();
    // unregister layout change
    iFeatureManager.ComponentManager().ChangeLayoutChangeRegistration(
        *this, MVtUiComponentManager::EUnregister );   
    // no need tot call resetanddestroy because buttons ownership is
    // transferred to akntoolbar.
    iToolBarControls.Reset();
    delete iToolbarCtx;
    delete iToolbarCmdPolicy;
    delete iHideToolbarItemAction;
    delete iToolbarSKModifier;
    iCmdIds.Close();
    iCmdStates.Close();
    __VTPRINTEXIT( "Toolbar.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::DynInitToolbarL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::DynInitToolbarL( TInt /*aResourceId*/,
    CAknToolbar* /*aToolbar*/ )
    {
    __VTPRINTENTER( "Toolbar.DynInitToolbarL" )
    __VTPRINTEXIT( "Toolbar.DynInitToolbarL" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::OfferToolbarEventL
// Destructor.
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::OfferToolbarEventL( TInt aCommand )
    {
    __VTPRINTENTER( "Toolbar.OfferToolbarEventL" )
    __VTPRINT2( DEBUG_GEN, "Toolbar.OfferToolbarEventL.aCommand=%d", aCommand )

    // if capture mode is on all msk events must be converted to capture command
    if ( iFeatureManager.UiStates().IsCaptureModeOn() )
        {
        iFeatureManager.AppUi().HandleCommandL( EVtUiCmdCapture );
        return;
        }

        TInt command = MapCmdIdToChilId( aCommand );

        if ( EVtUiCmdSwapImagesPlaces == command )
            {
            if ( !( iFeatureManager.AppUi().CanSwapImagePlaces() ) )
                {
                return;
                }
            }

        iFeatureManager.AppUi().HandleCommandL( command );

    __VTPRINTEXITR( "Toolbar.OfferToolbarEventL.cmd %d", aCommand )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::StartL
// Destructor.
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::StartL()
    {
    CVtUiFeatureBase::StartL();
    __VTPRINTENTER( "Toolbar.StartL" )
    TInt error;
    if ( iFeatureState == MVtUiFeature::EReady )
        { 
        TRAP( error, iFeatureManager.ComponentManager().
            RequestActivationL( MVtUiComponent::EComponentIdToolbar ) );

        // set state
        iFeatureState = MVtUiFeature::EActive;
        }
    __VTPRINTEXITR( "Toolbar.StartL error = %d", error )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::Stop
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::Stop()
    {
    __VTPRINTENTER( "Toolbar.Stop" )
    TInt error;
    if ( iFeatureState == MVtUiFeature::EActive )
        {
        TRAP( error, iFeatureManager.ComponentManager().
            DeActivateComponentL ( MVtUiComponent::EComponentIdToolbar ) );
        // set state
        iFeatureState = MVtUiFeature::EReady;
        }
    __VTPRINTEXITR( "Toolbar.Stop error = %d", error )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::InitFeature
// Delayed initialization of the feature
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::InitFeatureL()
    {
    __VTPRINTENTER( "Toolbar.InitFeatureL" )
    iFeatureState = EPreparing;
    iToolBarControls.ReserveL( iNumberOfToolbarButtons );

    //create toolbar
    //iToolbar = CAknToolbar::NewL( R_VIDEOTELUI_TOOLBAR );

    iToolbar->SetToolbarObserver( this );

    // Prohibit toolbar sliding on UI.    
    iToolbar->SetWithSliding( EFalse );

    // create toolbar context and policy
    iToolbarCtx =
         CVtUiToolbarContext::NewL( iFeatureManager.CommandManager() );

    iToolbarCmdPolicy = CVtUiToolbarCmdPolicy::NewL( *this );

    // create toolbaraction
    iHideToolbarItemAction = CVtUiHideToolbarItemAction::NewL( this,
        iFeatureManager.UiStates() );

    // create sofkey modifier
    iToolbarSKModifier = CVtUiToolbarSKModifier::
        NewL( iFeatureManager.AppUi(), iFeatureManager.UiStates() );

    // set supported commands
    PopulateCmdsIdsL();

    User::LeaveIfError(
       iFeatureManager.ComponentManager().ChangeComponentRegistration(
       iComponentState, MVtUiComponentManager::ERegister ) );

    User::LeaveIfError(
       iFeatureManager.ComponentManager().ChangeLayoutChangeRegistration(
       *this, MVtUiComponentManager::ERegister ) );

    iFeatureState = EReady;

    __VTPRINTEXIT( "Toolbar.InitFeatureL" )
    }


// -----------------------------------------------------------------------------
// CVtUiToolbarBase::MapCmdIdToChilId
// -----------------------------------------------------------------------------
//
TInt CVtUiToolbarBase::MapCmdIdToChilId( TInt aCmdId )
    {
    __VTPRINTENTER( "Toolbar.MapCmdIdToChilId" )
     __VTPRINT2( DEBUG_GEN, "Toolbar.MapCmdIdToChilId.aCmdId=%d", aCmdId )
    TInt result = aCmdId;

    CVtUiToolbarButton* tbButton = FindToolbarItemByCommandId( aCmdId );

    const TInt stateIndexValue( tbButton->StateIndex() );
    __VTPRINT2( DEBUG_GEN, "Toolbar.MapCmdIdToChilId.idx=%d", stateIndexValue )
    switch( aCmdId )
        {
        case EVtUiCmdToolbarToggleVideo:
            { 
            switch ( stateIndexValue )
                {
            case 0:  
            case 1:
                result = EVtUiCmdDisableVideo;
                break;
            case 2:
            case 3:
                result = EVtUiCmdEnableVideo;
                break;
                }    
            }
            break;

        case EVtUiCmdToolbarToggleMicrophone:
            { 
            switch ( stateIndexValue )
                {
            case 0:    
            case 1:
                result = EVtUiCmdDisableAudio;
                break;
            case 2:
            case 3:
                result = EVtUiCmdEnableAudio;
                break;
                }    
            }
            break;            

        case EVtUiCmdToolbarAudioRouting:
            {
            switch ( stateIndexValue )
                {
            case 0:
            case 1:
                result = EVtUiCmdDeactivateLoudspeaker;
                break;
            case 2:
            case 3:
                result = EVtUiCmdSwitchFromBTToIHF;
                break;
            case 4:
            case 5:
                result = EVtUiCmdActivateLoudspeaker;
                break;
            case 6:
            case 7:
                result = EVtUiCmdActivateBT;
                break;
            default:
                break;
                };
            }
            break;

        case EVtUiCmdToolbarToggleCamera:
            {
            switch ( stateIndexValue )
                {
            case 0:   
            case 1:
                result = EVtUiCmdUsePrimaryCamera;
                break;
            case 2:
            case 3:
                result = EVtUiCmdUseSecondaryCamera;
                break;
                }    
            }
            break;  
     
        default:
            break;
        }

    if ( aCmdId == result )
        {
        TInt index( stateIndexValue - 1 );
        if ( index < 0 )
            {
            index = tbButton->StatesCount() - 1;
            }
        tbButton->SetCurrentState( index, EFalse );
        }

    __VTPRINTEXITR( "Toolbar.MapCmdIdToChilId.result %d", (TInt)result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::MapCmdIdToParentId
// -----------------------------------------------------------------------------
//
TInt CVtUiToolbarBase::MapCmdIdToParentId( TInt aCmdId )
    {
    __VTPRINTENTER( "Toolbar.MapCmdIdToParentId" )
    TInt result = aCmdId;
        switch( aCmdId )
            {
            case EVtUiCmdDisableVideo:
            case EVtUiCmdEnableVideo:
                result = EVtUiCmdToolbarToggleVideo;
                break;

            case EVtUiCmdDisableAudio:
            case EVtUiCmdEnableAudio:
                result = EVtUiCmdToolbarToggleMicrophone;
                break;

            case EVtUiCmdActivateBT:
            case EVtUiCmdSwitchFromBTToIHF:
            case EVtUiCmdActivateLoudspeaker:
            case EVtUiCmdDeactivateLoudspeaker:
                result = EVtUiCmdToolbarAudioRouting;
                break;

            case EVtUiCmdUsePrimaryCamera:
            case EVtUiCmdUseSecondaryCamera:
                result = EVtUiCmdToolbarToggleCamera;
                break;

            default:
                break;
            }
    __VTPRINTEXITR( "Toolbar.MapCmdIdToParentId.result %d", (TInt)result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::IsCmdIdVisibleInToggleButton
// -----------------------------------------------------------------------------
//
TBool CVtUiToolbarBase::IsCmdIdVisibleInToggleButton( TInt aCmdId )
    {
    __VTPRINTENTER( "Toolbar.IsCMdIdVisibleInTogB" )
    TBool result( ETrue );
    TInt cmdId( MapCmdIdToParentId( aCmdId ) );
    TInt targetStateIndex( KErrNotFound );
    switch( aCmdId )
        {
        case EVtUiCmdActivateBT:
            targetStateIndex = 6;
            break;

        case EVtUiCmdActivateLoudspeaker:
            targetStateIndex = 4;
            break;

        case EVtUiCmdSwitchFromBTToIHF:
        case EVtUiCmdEnableVideo:
        case EVtUiCmdEnableAudio:
        case EVtUiCmdUseSecondaryCamera:
            targetStateIndex = 2;
            break;

        case EVtUiCmdDisableVideo:
        case EVtUiCmdDisableAudio:
        case EVtUiCmdUsePrimaryCamera:
        case EVtUiCmdDeactivateLoudspeaker:
            targetStateIndex = 0;
            break;

        default:
            break;
        }

    if ( targetStateIndex != KErrNotFound )
        {
        result = ( FindToolbarItemByCommandId( cmdId )
            ->StateIndex() == targetStateIndex );
        }

    __VTPRINTEXITR( "Toolbar.IsCMdIdVisibleInTogB.result %d", (TInt)result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::PopulateCmdsIdsL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::PopulateCmdsIdsL()
    {
    __VTPRINTENTER( "Toolbar.PopulateCmdsIdsL" )
    CVtUiAppUi& appUi = iFeatureManager.AppUi();

    // default commands
    iCmdIds.AppendL( EVtUiCmdDisableVideo );
    iCmdIds.AppendL( EVtUiCmdEnableVideo );
    iCmdIds.AppendL( EVtUiCmdDisableAudio );
    iCmdIds.AppendL( EVtUiCmdEnableAudio );

    __VTPRINTEXIT( "Toolbar.PopulateCmdsIdsL" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::SetToolbarVisibilityAfterLayoutChangeL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::SetToolbarVisibilityAfterLayoutChangeL( TBool /*aVisible*/ )
    {
    __VTPRINTENTER( "Toolbar.SetToolbarVisibilityAfterLayoutChangeL" )
    __VTPRINTEXIT( "Toolbar.SetToolbarVisibilityAfterLayoutChangeL" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::IsToggleButtonHidden
// -----------------------------------------------------------------------------
//
TBool CVtUiToolbarBase::IsToggleButtonHidden(TInt aFirstCmdId, TInt aSecondCmdId )
    {
    __VTPRINTENTER( "Toolbar.IsToggleButtonHidden" )
    TInt count = 0;
    TBool result = EFalse;
    for ( TInt i = 0; i < iCmdStates.Count(); i++ )
        {
        if ( iCmdStates[ i ].iCmdId == aFirstCmdId ||
            iCmdStates[ i ].iCmdId == aSecondCmdId )
            {
            if ( iCmdStates[ i ].iNewState == EHidden )
                {
                count++;
                }
            }
        }

    if ( count > 1 )
        {
        __VTPRINT(DEBUG_GEN, "IsToggleButtonHidden.Count>1" )
        result = ETrue;
        }
   __VTPRINTEXITR( "Toolbar.IsToggleButtonHidden.result%d", result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::Clean
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::Clean()
    {
    __VTPRINTENTER( "Toolbar.Clean" )
    TRAP_IGNORE( CVtUiToolbarBase::DoDeactivateL() );
    // unregister component change registration
    iFeatureManager.ComponentManager().ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::EUnregister );
    __VTPRINTEXIT( "Toolbar.Clean" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::CreateToolbarButtons
// -----------------------------------------------------------------------------
//

void CVtUiToolbarBase::CreateToolbarButtonsL()
    {
    __VTPRINTENTER( "Toolbar.CreateToolbarButtons" )
    CVtUiAppUi& appUi = iFeatureManager.AppUi();

    // two default buttons
    // toggle video
    CreateToolbarItemL( R_AVKONBUTTON_TOGGLE_VIDEO_BUTTON,
        EVtUiCmdToolbarToggleVideo, appUi );

    // toggle microphone
    CreateToolbarItemL( R_AVKONBUTTON_TOGGLE_MICROPHONE_BUTTON,
        EVtUiCmdToolbarToggleMicrophone, appUi );

    __VTPRINTEXIT( "Toolbar.CreateToolbarButtons" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::CreateToolbarItemL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::CreateToolbarItemL( TInt aResourceId, TInt aCommandId,
    CVtUiAppUi& appUi  )
    {
    __VTPRINTENTER( "Toolbar.CreateToolbarItemL" )

    CVtUiToolbarButton* toolbarItem = NULL;
    TLinearOrder< CVtUiToolbarButton > linOrder( ::ToolbarCmpFunc );

    // create toolbaritem
    toolbarItem = CVtUiToolbarButton::NewLC( aResourceId, appUi, aCommandId );

    // add toolbar item to toolbar
    // CVtUiToolbarButton  ownership is transferred to akntoolbar
    iToolbar->AddItemL( toolbarItem, EAknCtButton,
                          aCommandId , NULL );

    // add toolbar item to array
    iToolBarControls.InsertInOrderL( toolbarItem, linOrder );

    CleanupStack::Pop(); // toolbaritem

    __VTPRINTEXIT( "Toolbar.CreateToolbarItemL" )
    }



// -----------------------------------------------------------------------------
// CVtUiToolbarBase::HideToolbarButton
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::HideToolbarButton( const TInt aCommandId, const TBool aHide,
    const TBool aDrawNow )
    {
    __VTPRINTENTER( "Toolbar.HideToolbarButton" )
    __VTPRINT2( DEBUG_GEN, "Toolbar.HideToolbarButton.aCommandId=%d", aCommandId )
    TInt cmdId = MapCmdIdToParentId( aCommandId );

    // unhide for toggle buttons not handled
    if ( !aHide && cmdId != aCommandId )
       {
       return;
       }

    // Get toolbar item
    CVtUiToolbarButton* tbItem = FindToolbarItemByCommandId( cmdId );

    // get button's current state
    TInt stateIndex = tbItem->StateIndex();

    switch ( cmdId )
        {
        case EVtUiCmdToolbarToggleVideo:
            // if both items should be hidden in togglebutton,
            // then dim togglebutton
            if ( IsToggleButtonHidden( EVtUiCmdDisableVideo,
                    EVtUiCmdEnableVideo ) )
                {
                // update visibility state
                TRAP_IGNORE(
                    SetCmdIdVisibilityStateL( EVtUiCmdDisableVideo, EDimmed );
                    SetCmdIdVisibilityStateL( EVtUiCmdEnableVideo, EDimmed );
                    );
                iToolbar->SetItemDimmed( cmdId, ETrue, EFalse );
                return;
                }
            if ( ( stateIndex == 0 || stateIndex == 1 ) && 
                EVtUiCmdDisableVideo == aCommandId )
                {
                tbItem->SetCurrentState ( 2, EFalse );
                }
             else if( ( stateIndex == 2 || stateIndex == 3 )&& 
                EVtUiCmdEnableVideo == aCommandId )
                {
                tbItem->SetCurrentState ( 0, EFalse );
                }
            break;

        case EVtUiCmdToolbarToggleMicrophone:
            // if both items should be hidden in togglebutton,
            // then dim togglebutton
            if ( IsToggleButtonHidden( EVtUiCmdDisableAudio,
                    EVtUiCmdEnableAudio ) )
                {
                // update visibility state
                TRAP_IGNORE(
                    SetCmdIdVisibilityStateL( EVtUiCmdDisableAudio, EDimmed );
                    SetCmdIdVisibilityStateL( EVtUiCmdEnableAudio, EDimmed );
                    );
                iToolbar->SetItemDimmed( cmdId, ETrue, EFalse );
                return;
                }
            if ( ( stateIndex == 0 || stateIndex == 1 ) && 
                EVtUiCmdDisableAudio == aCommandId )
                {
                tbItem->SetCurrentState ( 2, EFalse );
                }
             else if( ( stateIndex == 2 || stateIndex == 3 ) &&
                EVtUiCmdEnableAudio == aCommandId )
                {
                tbItem->SetCurrentState ( 0, EFalse );
                }
            break;

        case EVtUiCmdToolbarAudioRouting:
            {
            const TBool isToggleButtonHidden(
                IsToggleButtonHidden( EVtUiCmdActivateBT,
                    EVtUiCmdSwitchFromBTToIHF ) &&
                IsToggleButtonHidden( EVtUiCmdActivateLoudspeaker,
                    EVtUiCmdDeactivateLoudspeaker )
            );

            if ( isToggleButtonHidden )
                {
                TRAP_IGNORE(
                    SetCmdIdVisibilityStateL( EVtUiCmdActivateBT, EDimmed );
                    SetCmdIdVisibilityStateL( EVtUiCmdDeactivateLoudspeaker,
                        EDimmed );
                    SetCmdIdVisibilityStateL( EVtUiCmdSwitchFromBTToIHF, EDimmed );
                    SetCmdIdVisibilityStateL( EVtUiCmdActivateLoudspeaker,
                        EDimmed );
                    );
                iToolbar->SetItemDimmed( cmdId, ETrue, EFalse );
                return;
                }
            else
                {
                if ( tbItem )
                    {
                    const TVtUiAudioState& audioState(
                        iFeatureManager.UiStates().AudioState() );

                    TInt state( 0 ); // Deactivate loudspeaker

                    if ( audioState.CanDeactivateBtHf() )
                        {
                        state = 2; //  Deactivate bthf
                        }
                    else if ( audioState.CanActivateBtHf() )
                        {
                        state = 6; // Activate bthf
                        }
                    else if ( audioState.CanActivateLoudspeaker() )
                        {
                        state = 4; // Activate loudspeaker
                        }
                    __VTPRINT2( DEBUG_GEN,
                        "Toolbar.HideToolbarButton.AudioRoutingState=%d",
                        state )
                    tbItem->SetCurrentState ( state, EFalse );
                    }
                }
            }
            break;

        case EVtUiCmdToolbarToggleCamera:
            // if both items should be hidden in togglebutton,
            // then dim togglebutton
            if ( IsToggleButtonHidden( EVtUiCmdUsePrimaryCamera,
                    EVtUiCmdUseSecondaryCamera ) )
                {
                // update visibility state
                TRAP_IGNORE(
                    SetCmdIdVisibilityStateL( EVtUiCmdUsePrimaryCamera, EDimmed );
                    SetCmdIdVisibilityStateL( EVtUiCmdUseSecondaryCamera, EDimmed );
                    );
                iToolbar->SetItemDimmed( cmdId, ETrue, EFalse );
                return;
                }
            if ( ( stateIndex == 0 || stateIndex == 1 ) && 
                EVtUiCmdUsePrimaryCamera == aCommandId )
                {
                tbItem->SetCurrentState ( 2, EFalse );
                }
             else if( ( stateIndex == 2 || stateIndex == 3 ) &&
                EVtUiCmdUseSecondaryCamera == aCommandId )
                {
                tbItem->SetCurrentState ( 0, EFalse );
                }
            break;

        default:
            iToolbar->HideItem( cmdId, aHide, aDrawNow);
            __VTPRINT( DEBUG_GEN, "Toolbar.HideToolbarButton" )
            break;
        }
    __VTPRINTEXIT( "Toolbar.HideToolbarButton" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::DimToolbar
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::DimToolbar( const TBool aDimmed, const TBool aDrawNow )
    {
    __VTPRINTENTER( "Toolbar.DimToolbar" )
    __VTPRINT2( DEBUG_GEN, "Toolbar.DimToolbar.aDimmed=%d", (TInt)aDimmed )

    TInt count = iCmdStates.Count();
    for( TInt i = 0; i < count; i++ )
        {
        __VTPRINT2( DEBUG_GEN, "iCmdId = %d", iCmdStates[ i ].iCmdId )
        __VTPRINT3( DEBUG_GEN, "iCmdStates.iOldState=%d iCmdStates.iNewState=%d", 
                iCmdStates[ i ].iOldState, iCmdStates[ i ].iNewState )
        // dim item
        if ( iCmdStates[ i ].iNewState == EShown )
            {
            DimToolbarButton( iCmdStates[ i ].iCmdId, aDimmed, aDrawNow );
            }
        }
    __VTPRINTEXIT( "Toolbar.DimToolbar" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::DimToolbarButton
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::DimToolbarButton( const TInt aCommandId, const TBool aDimmed,
    const TBool aDrawNow )
    {
    __VTPRINTENTER( "Toolbar.DimToolbarButton" )
    __VTPRINT2( DEBUG_GEN, "Toolbar.DimToolbarButton.aCmdId=%d", aCommandId )

    // command not visible, no need to update button
    if ( !IsCmdIdVisibleInToggleButton( aCommandId ) )
        {
        __VTPRINTEXIT("Toolbar.DimToolbarButton.NotVisible" )
        return;
        }
    TInt cmdId = MapCmdIdToParentId( aCommandId );
    // dim item
    iToolbar->SetItemDimmed( cmdId, aDimmed, aDrawNow );
    __VTPRINTEXIT( "Toolbar.DimToolbarButton" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::FindToolbaItemByCommandId
// -----------------------------------------------------------------------------
//
CVtUiToolbarButton* CVtUiToolbarBase::FindToolbarItemByCommandId
    ( const TInt aCommandId )
    {
    __VTPRINTENTER( "Toolbar.FindToolbarItemByCmdId" )
    CVtUiToolbarButton* result = NULL;

    TInt index( iToolBarControls.
        FindInOrder( aCommandId,::ToolbarItemIdCmpFunc ) );

    if ( index != KErrNotFound )
        {
        result = iToolBarControls[ index ];
        }
    __VTPRINTEXITR( "Toolbar.FindToolbarItemByCmdId.result %d", (TInt)result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::StartBlocking
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::BlockPointerEvents( TBool aIsBlocking )
    {
     __VTPRINTENTER( "Toolbar.BlockPointerEvents" )
    for (TInt i = 0; i < iToolBarControls.Count(); ++i )
        {
        iToolBarControls[ i ]->BlockPointerEvents( aIsBlocking );
        }
    __VTPRINTEXITR( "Toolbar.BlockPointerEvents =%d", aIsBlocking )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::StopBlocking
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::BlockKeyEvents( TBool aIsBlocking )
    {
    __VTPRINTENTER( "Toolbar.BlockKeyEvents" )
    for ( TInt i = 0; i < iToolBarControls.Count(); ++i )
        {
        iToolBarControls[ i ]->BlockKeyEvents( aIsBlocking );
        }
    __VTPRINTEXITR( "Toolbar.BlockKeyEvents =%d", aIsBlocking )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::IsDialerActive
// -----------------------------------------------------------------------------
//
TBool CVtUiToolbarBase::IsDialerActive() const
    {
    __VTPRINTENTER( "Toolbar.IsDialerActive" )
    TBool ret( EFalse );
    MVtUiFeature* dialer = iFeatureManager.
        GetFeatureById( EVtUiFeatureIdDialer );
        if ( dialer )
            {
            if ( dialer->State() == MVtUiFeature::EActive  )
                {
                ret = ETrue;
                }
            } 
    __VTPRINTEXITR( "Toolbar.IsDialerActive =%d", ret )
    return ret;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::NumberOfToolbarControls
// -----------------------------------------------------------------------------
//
TInt CVtUiToolbarBase::NumberOfToolbarControls() const
    {
    __VTPRINTENTER( "Toolbar.NumberOfToolbarControls" )
    __VTPRINTEXIT( "Toolbar.NumberOfToolbarControls" )
    return iCmdIds.Count();
    }


// -----------------------------------------------------------------------------
// CVtUiToolbarBase::CommandIdByCmdIdsArrayIndex
// -----------------------------------------------------------------------------
//
 TInt CVtUiToolbarBase::CommandIdByCmdIdsArrayIndex( TInt aIndex ) const
    {
    __VTPRINTENTER( "Toolbar.CommandIdByCmdIdsArrayIndex" )
    __VTPRINTEXIT( "Toolbar.CommandIdByCmdIdsArrayIndex.cmdId" )
    return iCmdIds[aIndex];
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::UpdateToolbar
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::UpdateToolbarL()
    {
    __VTPRINTENTER( "Toolbar.UpdateToolbar" )
    TVtUiStates& uiStates = iFeatureManager.UiStates();

    // Zoom mode can be activated also from options menu
    // therefore set zoom buttons state to latched
    if ( uiStates.IsZoomModeOn() &&
         IsCommandInToolbar( EVtUiCmdZoom )&&
         FindToolbarItemByCommandId( EVtUiCmdZoom )
           ->StateIndex() == 0  )
        {
        FindToolbarItemByCommandId( EVtUiCmdZoom )
           ->SetCurrentState ( 1, ETrue );
        }


    if ( uiStates.IsCaptureModeOn() && IsCommandInToolbar( EVtUiCmdZoom ) )
        {
         __VTPRINT( DEBUG_GEN, "Toolbar.UpdateToolbarL.IsCaptureModeOn" )
        // remove zoom mode button tooltip
        FindToolbarItemByCommandId( EVtUiCmdZoom )
           ->State( 0 )->SetHelpTextL( KNullDesC() );
        // set zoom mode button to be focused
        iToolbar->SetFocusedItemL( EVtUiCmdZoom );
        }

    TInt count = iCmdStates.Count();
    for( TInt i = 0; i < count; i++ )
       {
       // no need to do anything
       if ( iCmdStates[ i ].iOldState == iCmdStates[ i ].iNewState  )
           {
           if ( ( iCmdStates[ i ].iCmdId == EVtUiCmdDisableVideo ||
                iCmdStates[ i ].iCmdId == EVtUiCmdEnableVideo ) &&
                iCmdStates[ i ].iNewState != EShown  &&
                !( iFeatureManager.UiStates().MediaState().IsSharing() ) )
                {
                CVtUiToolbarButton* tbButton =  static_cast< CVtUiToolbarButton* >(
                    FindToolbarItemByCommandId( EVtUiCmdToolbarToggleVideo ) );
                tbButton->SetCurrentState(
                iFeatureManager.UiStates().MediaState().IsVideo() ? 0 : 2 , ETrue );
                }
           // for the case that EVtUiCmdDisableVideo and
           // EVtUiCmdActivateBT command
           // need to be shown but it is not visible in
           // toogle button.
           if ( ( iCmdStates[ i ].iCmdId == EVtUiCmdSwitchFromBTToIHF ||
               iCmdStates[ i ].iCmdId == EVtUiCmdActivateBT ||
               iCmdStates[ i ].iCmdId == EVtUiCmdActivateLoudspeaker ||
               iCmdStates[ i ].iCmdId == EVtUiCmdDeactivateLoudspeaker ||
               iCmdStates[ i ].iCmdId == EVtUiCmdDisableAudio ||
               iCmdStates[ i ].iCmdId == EVtUiCmdEnableAudio  ||
               iCmdStates[ i ].iCmdId == EVtUiCmdDisableVideo  ||
               iCmdStates[ i ].iCmdId == EVtUiCmdEnableVideo) &&
                   iCmdStates[ i ].iNewState == EShown )
               {
               // Nothing goes here.
               }
           else
               {
               continue;
               }
           }
       // dim item
       if ( iCmdStates[ i ].iNewState == EDimmed )
           {
           DimToolbarButton( iCmdStates[ i ].iCmdId, ETrue, EFalse );
           }
       // hide item
       // currently used only for toggle buttons
       // otherwise EDrawNow parameter must be updated for last element
       else if ( iCmdStates[ i ].iNewState == EHidden )
           {
           HideToolbarButton( iCmdStates[ i ].iCmdId, ETrue, EFalse );
           }
       // show item
       else if ( iCmdStates[ i ].iNewState == EShown )
           {
           // items are undimmed if they were dimmed
           // iCmdStates[ i ].iOldState == EDimmed  comparison does
           // not work with toggle buttons.
           // That is why all buttons are undimmed.
           DimToolbarButton( iCmdStates[ i ].iCmdId, EFalse, EFalse );

           HideToolbarButton( iCmdStates[ i ].iCmdId, EFalse, EFalse );
           }
       }

    // capture mode ended remove zoom button's latched state
    if ( !uiStates.IsZoomModeOn() &&
         IsCommandInToolbar( EVtUiCmdZoom )&&
         FindToolbarItemByCommandId( EVtUiCmdZoom )->StateIndex() == 1 )
        {
        FindToolbarItemByCommandId( EVtUiCmdZoom )
            ->SetCurrentState ( 0, ETrue );
        }

    // if capture mode was activated set zoom mode button active
    if ( uiStates.IsCaptureModeOn() && IsCommandInToolbar( EVtUiCmdZoom ) )
       {
       // set latched (selected) state
       FindToolbarItemByCommandId( EVtUiCmdZoom )
            ->SetCurrentState ( 1, ETrue);
       }
    else
       {
       // tooltip must be returned to zoom mode button
       // only after zoom mode buttons latched state is changed
       // because changing the buttons state will draw the tooltip
       if ( IsCommandInToolbar( EVtUiCmdZoom ) &&
            ( KNullDesC() == ( FindToolbarItemByCommandId( EVtUiCmdZoom )
                ->State(0)->HelpText() ) ) )
            {
            HBufC* tooltip = StringLoader::LoadLC( R_VIDEOTELUI_TOOLTIP_ZOOM );
            FindToolbarItemByCommandId( EVtUiCmdZoom )
                ->State(0)->SetHelpTextL( *tooltip );
            CleanupStack::PopAndDestroy( ); // tooltip
            }
        }

    // draw toolbar
    //iToolbar->DrawDeferred();
    iToolbar->DrawNow();
    __VTPRINTEXIT( "Toolbar.UpdateToolbar" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::SetCmdIdVisibilityStateL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::SetCmdIdVisibilityStateL( TInt aCmdId,
    TCmdStateFlags aNewState )
    {
    __VTPRINTENTER( "Toolbar.SetCmdIdVisibilityStateL" )
    __VTPRINT2( DEBUG_GEN, "Toolbar.SetCmdIdVbStateL.aCmdId=%d", aCmdId )
    __VTPRINT2( DEBUG_GEN, "Toolbar.SetCmdIdVbStateL.aNewState=%d", aNewState )

    TInt result = KErrNotFound;
    for ( TInt i = 0; i < iCmdStates.Count(); i++ )
        {
        if ( iCmdStates[ i ].iCmdId == aCmdId )
            {
            // command found
            result = i;
            break;
            }
        }
    // new item
    // add to array
    if( result == KErrNotFound )
        {
        TCommandState state;
        state.iCmdId = aCmdId;
        state.iOldState = ENotInitialized;
        state.iNewState = aNewState;
        iCmdStates.AppendL( state );
        }
    else // old item
        {
        iCmdStates[ result ].iOldState = iCmdStates[ result ].iNewState;
        iCmdStates[ result ].iNewState = aNewState;
        }

    __VTPRINTEXIT( "Toolbar.SetCmdIdVbStateL" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::IsCommandInToolbar
// -----------------------------------------------------------------------------
//
TBool CVtUiToolbarBase::IsCommandInToolbar( TInt aCmdId ) const
    {
    __VTPRINTENTER( "Toolbar.SetCmdIdVisibilityStateL" )
    TBool result = EFalse;
    for ( TInt i = 0; i < iCmdIds.Count(); i++ )
        {
        if ( iCmdIds[ i ] == aCmdId )
            {
            result = ETrue;
            break;
            }
        }
    __VTPRINTEXITR( "Toolbar.IsCommandInToolbar.result %d", (TInt)result )
    return result;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::RefreshL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::RefreshL()
    {
    __VTPRINTENTER( "Toolbar.RefreshL" )
    iFeatureManager.CommandManager().
        ValidateToolbarItemsL( *iHideToolbarItemAction );
    __VTPRINTEXIT( "Toolbar.RefreshL" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::AddCommandModifier
// -----------------------------------------------------------------------------
//
TInt CVtUiToolbarBase::AddCommandModifier( CVtUiCommandModifyBase& /*aModifier*/ )
    {
    __VTPRINTENTER( "Toolbar.AddCommandModifier" )
    __VTPRINTEXIT( "Toolbar.AddCommandModifier" )
    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::RemoveCommandModifier
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::RemoveCommandModifier( CVtUiCommandModifyBase& /*aModifier*/ )
    {
    __VTPRINTENTER( "Toolbar.RemoveCommandModifier" )
    __VTPRINTEXIT( "Toolbar.RemoveCommandModifier" )
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::ComponentId
// -----------------------------------------------------------------------------
//
MVtUiComponent::TComponentId CVtUiToolbarBase::ComponentId() const
    {
    __VTPRINTENTER( "Toolbar.ComponentId" )
    __VTPRINTEXIT( "Toolbar.ComponentId" )
    return MVtUiComponent::EComponentIdToolbar;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::ComponentAsControl
// -----------------------------------------------------------------------------
//
CCoeControl* CVtUiToolbarBase::ComponentAsControl()
    {
    __VTPRINTENTER( "Toolbar.ComponentAsControl" )
    __VTPRINTEXIT( "Toolbar.ComponentAsControl" )
    return NULL;
    }

// -----------------------------------------------------------------------------
// CVtUiToolbarBase::DoActivateL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::DoActivateL()
    {
    __VTPRINTENTER( "Toolbar.DoActivateL" )
    // add command ui to commandmanager
    User::LeaveIfError(
        iFeatureManager.CommandManager().AddCommandUi( *this ) );
    // add command modifier
    User::LeaveIfError( iFeatureManager.
       CommandManager().AddCommandModifier( *iToolbarSKModifier ) );
    // add validator
    User::LeaveIfError( iFeatureManager.CommandManager().
        AddValidator( *iToolbarCmdPolicy ) );
    // refresh
    iFeatureManager.CommandManager().RefreshL();
    __VTPRINTEXIT( "Toolbar.DoActivateL" )
    }


// -----------------------------------------------------------------------------
// CVtUiToolbarBase::DoDeactivateL
// -----------------------------------------------------------------------------
//
void CVtUiToolbarBase::DoDeactivateL()
    {
    __VTPRINTENTER( "Toolbar.DoDeactivateL" )
    // remove command modifier
    iFeatureManager.CommandManager().
        RemoveCommandModifier( *iToolbarSKModifier );
    // remove command validator
    iFeatureManager.CommandManager().RemoveValidator( *iToolbarCmdPolicy );
     // remove commandui
    iFeatureManager.CommandManager().RemoveCommandUi( *this );
    if ( iToolbar )
        {
        __VTPRINT(DEBUG_GEN, "Toolbar.DoDeactivateL, iToolbar is not null" )
        iToolbar->DrawNow();
        }
    __VTPRINTEXIT( "Toolbar.DoDeactivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiToolbarBase::HandleLayoutChangeL
// ---------------------------------------------------------------------------
//
void CVtUiToolbarBase::HandleLayoutChangeL()
    {
    __VTPRINTENTER( "CVtUiToolbarBase.HandleLayoutChangeL" )
    TBool isLandscape  = Layout_Meta_Data::IsLandscapeOrientation();
    CEikMenuBar* menuBar = CEikonEnv::Static()->AppUiFactory()->MenuBar();
    
    // This check prevents toolbar from drawing over the dialer
    // when orientation is changed from landscape to portrait
    
    // Transition from landsacpe to portrait
    // toolbar must be hided
    if ( !isLandscape && IsDialerActive() )
        {
        __VTPRINT(DEBUG_GEN, "CVtUiToolbarBase.LayoutChangeL.Stop" )
        SetToolbarVisibilityAfterLayoutChangeL( EFalse );
        }
    else if ( iFeatureManager.UiStates().IsSelectingShare() )
        {
        __VTPRINT( DEBUG_GEN, "ToolbarBase::HandleLayoutChangeL ShareImage." )
        SetToolbarVisibilityAfterLayoutChangeL( EFalse );
        }
    else if ( !isLandscape && iFeatureManager.UiStates().IsVideoQualityModeOn() )
        {
        __VTPRINT( DEBUG_GEN, "ToolbarBase::HandleLayoutChangeL Video Quality." )
        SetToolbarVisibilityAfterLayoutChangeL( EFalse );
        }
    else if ( !isLandscape && iFeatureManager.UiStates().IsWhiteBalanceModeOn() )
        {
        __VTPRINT( DEBUG_GEN, "ToolbarBase::HandleLayoutChangeL White Balance." )
        SetToolbarVisibilityAfterLayoutChangeL( EFalse );
        }
    else if ( !isLandscape && iFeatureManager.UiStates().IsColorToneModeOn() )
        {
        __VTPRINT( DEBUG_GEN, "ToolbarBase::HandleLayoutChangeL Color Tone." )
        SetToolbarVisibilityAfterLayoutChangeL( EFalse );
        }
    else if ( !isLandscape && menuBar && menuBar->IsDisplayed() )
        {
        __VTPRINT( DEBUG_GEN, "ToolbarBase::HandleLayoutChangeL Menu Displayed." )
        SetToolbarVisibilityAfterLayoutChangeL( EFalse );
        }
    // Transition from portrait to landsacpe
    // toolbar must be set to visible
    else if ( isLandscape && IsDialerActive() )
        {
        __VTPRINT(DEBUG_GEN, "CVtUiToolbarBase.LayoutChangeL.StartL" )
        SetToolbarVisibilityAfterLayoutChangeL( ETrue );
        }
    __VTPRINTEXIT( "CVtUiToolbarBase.HandleLayoutChangeL" )
    }

//  End of File


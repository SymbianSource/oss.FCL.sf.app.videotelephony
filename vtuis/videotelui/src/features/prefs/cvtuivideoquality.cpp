/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Video quality UI feature implementation.
*
*/


#include    <badesca.h>
#include    <akniconarray.h>
#include    <aknsutils.h>
#include    <stringloader.h>
#include    <aknlists.h>
#include    <aknpopup.h>
#include    <aknselectionlist.h>
#include    <mvtengmedia.h>
#include    <cvtengmodel.h>
#include    <cvtlogger.h>

#include    <videotelui.rsg>
#include    "cvtuivideoquality.h"
#include    "tvtuifeatureids.h"
#include    "VtUiLayout.h"
#include    "VtUiUtility.h"
#include    "CVtUiAppUi.h"
#include    "cvtuifeaturemanager.h"
#include    "mvtuicomponentmanager.h"
#include	"tvtuilocalvariation.h"
#include    "tvtuistates.h"

// constants
_LIT( KVtUiFormatActive, "0\t%S" );
_LIT( KVtUiFormatInactive, "\t%S" );
const TInt KVtUiMaxListItemLength = 128;

// Implementation of TVtUiVideoQualityComponentState

// ---------------------------------------------------------------------------
// TVtUiVideoQualityComponentState::TVtUiVideoQualityComponentState
// ---------------------------------------------------------------------------
//
TVtUiVideoQualityComponentState::TVtUiVideoQualityComponentState(
    MVtUiComponent& aComponent ) :
    TVtUiComponentState( aComponent,
        TVtUiBlockListBitField(
            MVtUiComponent::EComponentIdDialer |
            MVtUiComponent::EComponentIdNumberEntry ) )
    {
    __VTPRINTENTER( "TVtUiVideoQualityComponentState.Ctor" )
    __VTPRINTEXIT( "TVtUiVideoQualityComponentState.Ctor" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::NewL
// ---------------------------------------------------------------------------
//
CVtUiVideoQuality* CVtUiVideoQuality::NewL( CVtUiFeatureManager&
    aFeatureManager )
    {
    __VTPRINTENTER( "CVtUiVideoQuality.NewL" )
    CVtUiVideoQuality* self =
        new ( ELeave ) CVtUiVideoQuality( aFeatureManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    __VTPRINTEXIT( "CVtUiVideoQuality.NewL" )
    return self;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::~CVtUiVideoQuality
// ---------------------------------------------------------------------------
//
CVtUiVideoQuality::~CVtUiVideoQuality()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.~CVtUiVideoQuality" )
    
	// Delete the callback
    delete iShowSelectionListCallback;
    
    // unregister component
    iFeatureManager.ComponentManager().ChangeComponentRegistration(
        iComponentState, MVtUiComponentManager::EUnregister );

    __VTPRINTEXIT( "CVtUiVideoQuality.~CVtUiVideoQuality" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::StartL
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::StartL()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.StartL" )
    if ( iFeatureState == MVtUiFeature::EReady )
        {
        iFeatureManager.UiStates().SetIsFixedToolbarVisible( EFalse );
        iFeatureManager.ComponentManager().
            RequestActivationL ( MVtUiComponent::EComponentIdVideoQuality );
        // set state
        iFeatureState  = MVtUiFeature::EActive;
        }
    __VTPRINTEXIT( "CVtUiVideoQuality.StartL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::Stop
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::Stop()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.Stop" )
    TRAP_IGNORE(
        {
        if ( iFeatureState  == MVtUiFeature::EActive )
            {
            iFeatureManager.ComponentManager().
            DeActivateComponentL ( MVtUiComponent::EComponentIdVideoQuality );
            // set state
            iFeatureState = MVtUiFeature::EReady;
            }
        } );
    __VTPRINTEXIT( "CVtUiVideoQuality.Stop" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::InitFeatureL
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::InitFeatureL()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.InitFeatureL" )
    // register component to conponent manager
    User::LeaveIfError(
       iFeatureManager.ComponentManager().ChangeComponentRegistration(
       iComponentState, MVtUiComponentManager::ERegister ) );
    iFeatureState  = EReady;
    __VTPRINTEXIT( "CVtUiVideoQuality.InitFeatureL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::ComponentId
// ---------------------------------------------------------------------------
//
MVtUiComponent::TComponentId CVtUiVideoQuality::ComponentId() const
    {
    __VTPRINTENTER( "CVtUiVideoQuality.ComponentId" )
    __VTPRINTEXIT( "CVtUiVideoQuality.ComponentId" )
    return MVtUiComponent::EComponentIdVideoQuality;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::ComponentAsControl
// ---------------------------------------------------------------------------
//
CCoeControl* CVtUiVideoQuality::ComponentAsControl()
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.ComponentAsControl" )
    __VTPRINTEXIT( "CVtUiVideoQuality.ComponentAsControl" )
    return NULL;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::DoActivateL
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::DoActivateL()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.DoActivateL" )
    __VTPRINTEXIT( "CVtUiVideoQuality.DoActivateL" )
    iFeatureManager.UiStates().SetVideoQualityModeOn( ETrue );
    iShowSelectionListCallback->CallBack();
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::DoDeactivateL
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::DoDeactivateL()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.DoDeactivateL" )
    iFeatureManager.UiStates().SetVideoQualityModeOn( EFalse );
    __VTPRINTEXIT( "CVtUiVideoQuality.DoDeactivateL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::CreateIconLC
// ---------------------------------------------------------------------------
//
CGulIcon* CVtUiVideoQuality::CreateIconLC( TVtUiBitmapId aIconId,
    TVtUiBitmapId aMaskId )
    {
    __VTPRINTENTER( "CVtUiVideoQuality.CreateIconLC" )
    TFileName fileName;
    TInt bitmapIndex;
    TInt bitmapMaskIndex;
	CFbsBitmap* newIconBmp;
	CFbsBitmap* newIconMaskBmp;
    VtUiLayout::Resolve( aIconId, fileName, bitmapIndex );
    TAknsItemID skinId = VtUiLayout::MapBitmapToSkinId( aIconId );
    VtUiLayout::Resolve( aMaskId, fileName, bitmapMaskIndex );
	AknsUtils::CreateIconL( AknsUtils::SkinInstance(), skinId, newIconBmp,
            newIconMaskBmp, fileName, bitmapIndex, bitmapMaskIndex );
    CleanupStack::PushL( newIconBmp );
    CleanupStack::PushL( newIconMaskBmp );
	CGulIcon* gulIcon = CGulIcon::NewL( newIconBmp, newIconMaskBmp );
    CleanupStack::Pop( newIconMaskBmp );
    CleanupStack::Pop( newIconBmp );
    CleanupStack::PushL( gulIcon );
    __VTPRINTEXIT( "CVtUiVideoQuality.CreateIconLC" )
    return gulIcon;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::ShowSelectionListL
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::ShowSelectionListL()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.ShowSelectionListL" )
    // create listbox
    CAknSingleGraphicPopupMenuStyleListBox* listBox =
        new ( ELeave ) CAknSingleGraphicPopupMenuStyleListBox();
    CleanupStack::PushL( listBox );

    // create popuplist
    CAknPopupList* popUpList =
        CAknPopupList::NewL( listBox, R_VIDEOTELUI_SOFTKEYS_SELECT_CANCEL );
    CleanupStack::PushL( popUpList );

    listBox->ConstructL( popUpList,
        EAknListBoxSelectionList | EAknListBoxLoopScrolling );

    // Create an array of icons, reading them from the file and
    // set them in the listbox
	CArrayPtr<CGulIcon>* icons = new(ELeave) CAknIconArray( 1 );
	CleanupStack::PushL(icons);
	CGulIcon* icon = CreateIconLC( EVtUiBitmap_qgn_prop_sub_current,
        EVtUiBitmap_qgn_prop_sub_current_mask );
    icons->AppendL( icon );
	listBox->ItemDrawer()->ColumnData()->SetIconArray( icons );
	CleanupStack::Pop(2); //icon + icons

    // Read item array from resources
    CDesCArray* textArray =
        iFeatureManager.AppUi().GetEikonEnv()->
            ReadDesCArrayResourceL( R_VIDEOTELUI_VIDEO_QUALITY_ARRAY );
    CleanupStack::PushL( textArray );

    CDesCArraySeg* listBoxRows =  new ( ELeave ) CDesCArraySeg( 3 );
    CleanupStack::PushL( listBoxRows );

    // Read items to array
    SetItemsL( *listBoxRows, *textArray );

    // Create listbox model.
    CTextListBoxModel* listBoxModel = listBox->Model();
    // Set item array
    listBoxModel->SetItemTextArray( listBoxRows );

    // Set ownership
    listBoxModel->SetOwnershipType( ELbmOwnsItemArray );

    // Enable marquee
	listBox->ItemDrawer()->ColumnData()->EnableMarqueeL( ETrue );

    CleanupStack::Pop(2); // listBoxRows + testArray

    TInt popupOk = popUpList->ExecuteLD();

    CleanupStack::Pop(); // popUpList
    popUpList = NULL;

    if ( popupOk )
        {
        ItemSelectedL( listBox->CurrentItemIndex() );
        }
    else
        {
        // Selection canceled.
        }

    // Reset arrays
    listBoxRows->Reset();
    textArray->Reset();
    icons->ResetAndDestroy(); // icons + icon

    // Delete listbox
    CleanupStack::PopAndDestroy( listBox ); // listBox

    iAsyncCallback->Set( TCallBack( &DoStop, this ) );
    iAsyncCallback->CallBack();
    __VTPRINTEXIT( "CVtUiVideoQuality.ShowSelectionListL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::AsyncShowSelectionListL
// ---------------------------------------------------------------------------
//
TInt CVtUiVideoQuality::AsyncShowSelectionList( TAny* aPtr )
    {
    CVtUiVideoQuality* self = reinterpret_cast< CVtUiVideoQuality* > ( aPtr );
    TRAPD( err, self->ShowSelectionListL() );
    return err;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::SetItemsL
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::SetItemsL( CDesCArray& aTarget,
    const CDesCArray& aSource )
    {
    __VTPRINTENTER( "CVtUiVideoQuality.SetItemsL" )
    TInt activeItem( ActiveItem() );
    TInt count( aSource.Count() );
    for ( TInt i = 0; i < count; i++ )
        {
        TBuf< KVtUiMaxListItemLength > item;
        TPtrC sourceItem( aSource[ i ] );
        if ( i == activeItem )
            {
            item.Format( KVtUiFormatActive(), &sourceItem );
            }
        else
            {
            item.Format( KVtUiFormatInactive(), &sourceItem );
            }
        aTarget.AppendL( item );
        }
    __VTPRINTEXIT( "CVtUiVideoQuality.SetItemsL" )
    }
// ---------------------------------------------------------------------------
// CVtUiVideoQuality::ActiveItem
// ---------------------------------------------------------------------------
//
TInt CVtUiVideoQuality::ActiveItem() const
    {
    __VTPRINTENTER( "CVtUiVideoQuality.ActiveItem" )
    TInt activeItem( 0 );
    MVtEngMedia::TVideoQuality videoQuality;
    VtUiUtility::GetVideoQuality(  iFeatureManager.AppUi().Model().Media(),
        videoQuality );
    switch( videoQuality )
        {
    case MVtEngMedia::EVideoQualityNormal:
        activeItem = 0;
        break;
    case MVtEngMedia::EVideoQualityDetail:
        activeItem = 1;
        break;
    case MVtEngMedia::EVideoQualityMotion:
        activeItem = 2;
        break;
    default:
        break;
        }
    __VTPRINTEXIT( "CVtUiVideoQuality.ActiveItem" )
    return activeItem;
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::ItemSelectedL
// ---------------------------------------------------------------------------
//
 void CVtUiVideoQuality::ItemSelectedL( TInt aItemIndex )
    {
    __VTPRINTENTER( "CVtUiVideoQuality.ItemSelectedL" )
    MVtEngMedia::TVideoQuality qualityLevel;
    switch( aItemIndex )
        {
    case 0:
        qualityLevel = MVtEngMedia::EVideoQualityNormal;
        break;

    case 1:
        qualityLevel = MVtEngMedia::EVideoQualityDetail;
        break;

    case 2:
        qualityLevel = MVtEngMedia::EVideoQualityMotion;
        break;
    default:
        break;
        }
    // cast the parameter
    TPtrC8 params( reinterpret_cast< TUint8* >( &qualityLevel ),
        sizeof( MVtEngMedia::TVideoQuality ) );
    iFeatureManager.AppUi().DoExecuteCmdL( KVtEngSetVideoQuality, &params );
    __VTPRINTEXIT( "CVtUiVideoQuality.ItemSelectedL" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::CVtUiVideoQuality
// ---------------------------------------------------------------------------
//
CVtUiVideoQuality::CVtUiVideoQuality( CVtUiFeatureManager& aFeatureManager ) :
    CVtUiFeatureBase( EVtUiFeatureIdVideoQuality, aFeatureManager ),
    iComponentState( *this )
    {
    __VTPRINTENTER( "CVtUiWhiteBalance.CVtUiVideoQuality" )
    __VTPRINTEXIT( "CVtUiVideoQuality.CVtUiVideoQuality" )
    }

// ---------------------------------------------------------------------------
// CVtUiVideoQuality::ConstructL
// ---------------------------------------------------------------------------
//
void CVtUiVideoQuality::ConstructL()
    {
    __VTPRINTENTER( "CVtUiVideoQuality.ConstructL" )
    BaseConstructL();
    iShowSelectionListCallback = new ( ELeave ) CAsyncCallBack(
            TCallBack( &AsyncShowSelectionList, this ),
            CActive::EPriorityStandard );
    __VTPRINTEXIT( "CVtUiVideoQuality.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiVideoQuality::DoStop
// -----------------------------------------------------------------------------
//
TInt CVtUiVideoQuality::DoStop( TAny* aAny )
    {
    __VTPRINTENTER( "CVtUiVideoQuality.DoStop" )
    CVtUiFeatureBase* self = static_cast< CVtUiFeatureBase* >( aAny );
    self->Stop();
    __VTPRINTEXIT( "CVtUiVideoQuality.DoStop" )
    return KErrNone;
    }


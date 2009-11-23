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
* Description:  Feature manager for Video Telephone application.
*
*/



// INCLUDE FILES
#include    "cvtuifeaturemanager.h"
#include    "CVtUiAppUi.h"
#include    "cvtuifixedtoolbar.h"
#include    "cvtuifloatingtoolbar.h"
#include    "cvtuimenus.h"
#include    "cvtuifeaturebase.h"
#include    "tvtuistates.h"
#include    <cvtlogger.h>
#include    "cvtuicommandpolicymanager.h"
#include    "cvtuisoftkeys.h"
#include    "cvtuinumberentry.h"
#include    "cvtuivideoquality.h"
#include    "cvtuiwhitebalance.h"
#include    "cvtuicolortone.h"
#include    "cvtuidialer.h"
#include    "cvtuibrightness.h"
#include    "cvtuicontrast.h"
#include    "cvtuivolume.h"
#include    "cvtuizoom.h"

#include    <featmgr.h>

// CONSTANTS
const TInt KFeatureCount = 9;

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// Used in Attach() method to compare two instances of MVtUiFeature.
// ---------------------------------------------------------------------------
//
TInt FeatureCmpFunc( const CVtUiFeatureBase& aV1, const CVtUiFeatureBase& aV2 )
    {
    return ( aV1.Id() - aV2.Id() );
    }

// ---------------------------------------------------------------------------
// Used in GetFeature() method to search feature by id.
// ---------------------------------------------------------------------------
//
TInt FeatureIdCmpFunc( const TInt* aId, const CVtUiFeatureBase& aFeature )
    {
    return ( *aId - aFeature.Id() );
    }


// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::NewL
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CVtUiFeatureManager* CVtUiFeatureManager::NewL( CVtUiAppUi& aAppUi,
    TVtUiStates& aUiStates,  MVtUiCommandManager& aCommandManager,
    MVtUiComponentManager& aComponentManager )
    {
    CVtUiFeatureManager* self = new( ELeave ) CVtUiFeatureManager( aAppUi,
    aUiStates, aCommandManager, aComponentManager );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::CVtUiFeatureManager
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiFeatureManager::CVtUiFeatureManager( CVtUiAppUi& aAppUi,
    TVtUiStates& aUiStates,  MVtUiCommandManager& aCommandManager,
    MVtUiComponentManager& aComponentManager )
    : iAppUi( aAppUi ), iUiStates( aUiStates ),
    iCommandManager( aCommandManager ), iComponentManager( aComponentManager )
    {
     __VTPRINTENTER( "CVtUiFeatureManager.CVtUiFeatureManager" )
     __VTPRINTEXIT( "CVtUiFeatureManager.CVtUiFeatureManager" )
    }


// -----------------------------------------------------------------------------
//CVtUiFeatureManager::~CVtUiFeatureManager()
// -----------------------------------------------------------------------------
//
CVtUiFeatureManager::~CVtUiFeatureManager()
    {
    __VTPRINTENTER( "CVtUiFeatureManager.~" )
    iFeatures.ResetAndDestroy();
    __VTPRINTEXIT( "CVtUiFeatureManager.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CVtUiFeatureManager::ConstructL()
    {
    __VTPRINTENTER( "CVtUiFeatureManager.ConstructL" )
    iFeatures.ReserveL( KFeatureCount );
    CreateFeaturesL();
     __VTPRINTEXIT( "CVtUiFeatureManager.ConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::CreateFeaturesL
// -----------------------------------------------------------------------------
//
void CVtUiFeatureManager::CreateFeaturesL()
    {
    __VTPRINTENTER( "CVtUiFeatureManager.CreateFeaturesL" )
    CVtUiFeatureBase* feature = NULL;
    TLinearOrder< CVtUiFeatureBase >
        linOrder( ::FeatureCmpFunc );

    if ( AknLayoutUtils::PenEnabled() )
        {
        feature = CVtUiFixedToolbar::NewL( *this );
        } 
    else
        {
        feature = CVtUiFloatingToolbar::NewL( *this );            
        }
    
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    feature = CVtUiMenus::NewL( *this );
    iFeatures.InsertInOrderL( feature, linOrder );

    feature = CVtUiSoftkeys::NewL( *this, *iAppUi.GetCba() );
    iFeatures.InsertInOrderL( feature, linOrder );

    feature = CVtUiNumberEntry::NewL( *this );
    iFeatures.InsertInOrderL( feature, linOrder );

    if ( FeatureManager::FeatureSupported( KFeatureIdOnScreenDialer ) )
        {
        feature = CVtUiDialer::NewL( *this );
        if ( feature )
            {
            iFeatures.InsertInOrderL( feature, linOrder );
            }
        }

    feature = CVtUiVideoQuality::NewL( *this );
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    feature = CVtUiWhiteBalance::NewL( *this );
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    feature = CVtUiColorTone::NewL( *this );
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    feature = CVtUiBrightness::NewL( *this );
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    feature = CVtUiContrast::NewL( *this );
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    feature = CVtUiVolume::NewL( *this );
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    feature = CVtUiZoom::NewL( *this );
    if ( feature )
        {
        iFeatures.InsertInOrderL( feature, linOrder );
        }

    __VTPRINTEXIT( "CVtUiFeatureManager.CreateFeaturesL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::AppUi
// -----------------------------------------------------------------------------
//
CVtUiAppUi& CVtUiFeatureManager::AppUi()
    {
    __VTPRINTENTER( "CVtUiFeatureManager.AppUi" )
    __VTPRINTEXIT( "CVtUiFeatureManager.AppUi" )
    return iAppUi;
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::GetFeatureById
// -----------------------------------------------------------------------------
//
MVtUiFeature* CVtUiFeatureManager::GetFeatureById( TInt aId )
    {
    __VTPRINTENTER( "CVtUiFeatureManager.GetFeatureById" )
    CVtUiFeatureBase* result = NULL;

    TInt index( iFeatures.FindInOrder( aId, ::FeatureIdCmpFunc ) );
    if ( index != KErrNotFound )
        {
        result = iFeatures[ index ];
        }
    __VTPRINTEXITR( "CVtUiFeatureManager.GetFeatureById %d", (TInt)result )
    return result;

    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::UiStates
// -----------------------------------------------------------------------------
//

TVtUiStates& CVtUiFeatureManager::UiStates()
    {
    return iUiStates;
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::CommandManager
// -----------------------------------------------------------------------------
//
MVtUiCommandManager& CVtUiFeatureManager::CommandManager()
    {
    return iCommandManager;
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::ComponentManager
// -----------------------------------------------------------------------------
//
MVtUiComponentManager& CVtUiFeatureManager::ComponentManager()
    {
    return iComponentManager;
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureManager::Model
// -----------------------------------------------------------------------------
//
CVtEngModel& CVtUiFeatureManager::Model()
    {
    return iAppUi.Model();
    }

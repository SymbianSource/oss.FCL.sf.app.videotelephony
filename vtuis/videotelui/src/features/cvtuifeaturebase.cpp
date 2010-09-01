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
* Description:  CVtUiFeatureBase implementation.
*
*/


// INCLUDE FILES

#include    "cvtuifeaturebase.h"
#include    "mvtuifeature.h"
#include    "cvtuicommandpolicymanager.h"
#include    <cvtlogger.h>
#include    "cvtuifeaturemanager.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiFeatureBase::CVtUiFeatureBase
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiFeatureBase::CVtUiFeatureBase( TVtUiFeatureId aId,
    CVtUiFeatureManager& aFeatureManager ) : iId( aId ), 
    iFeatureManager ( aFeatureManager ),
    iFeatureState ( EUnprepared )
    {
    __VTPRINTENTER( "CVtUiFeatureBase.CVtUiFeatureBase" )
    __VTPRINTEXIT( "CVtUiFeatureBase.CVtUiFeatureBase" )
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureBase::BaseConstructL
// -----------------------------------------------------------------------------
//
void CVtUiFeatureBase::StartL()
	{
	if ( iFeatureState == EUnprepared )
		{
		iAsyncCallback->Cancel();
		InitFeatureL();
		}
	}

// -----------------------------------------------------------------------------
// CVtUiFeatureBase::BaseConstructL
// -----------------------------------------------------------------------------
//
void CVtUiFeatureBase::BaseConstructL()
    {
    __VTPRINTENTER( "CVtUiFeatureBase.BaseConstructL" )
    iAsyncCallback = 
    	new ( ELeave ) CAsyncCallBack ( CActive::EPriorityLow );
    iAsyncCallback->Set( TCallBack( &DoInitFeaturesL, this ) );
    iAsyncCallback->CallBack(); 
    __VTPRINTEXIT( "CVtUiFeatureBase.BaseConstructL" )
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureBase::~CVtUiFeatureBase
// Destructor.
// -----------------------------------------------------------------------------
//
CVtUiFeatureBase::~CVtUiFeatureBase()
    {
    __VTPRINTENTER( "CVtUiFeatureBase.~" )
    delete iAsyncCallback;
    __VTPRINTEXIT( "CVtUiFeatureBase.~" )
    }

// -----------------------------------------------------------------------------
// CVtUiFeatureBase::State
// -----------------------------------------------------------------------------
//
MVtUiFeature::TVtUiFeatureState CVtUiFeatureBase::State() const
    {
    __VTPRINTENTER( "CVtUiFeatureBase.State" )
    __VTPRINTEXITR( "CVtUiFeatureBase.State. %d", (TInt)iFeatureState )
    return iFeatureState;
    }
        
// -----------------------------------------------------------------------------
// CVtUiFeatureBase::Id
// -----------------------------------------------------------------------------
//
TVtUiFeatureId CVtUiFeatureBase::Id() const
    {
    __VTPRINTENTER( "CVtUiFeatureBase.Id" )
    __VTPRINTEXITR( "CVtUiFeatureBase.Id %d", iId )
    return iId;
    }
    
// -----------------------------------------------------------------------------
// CVtUiFeatureBase::DoInitFeaturesL
// -----------------------------------------------------------------------------
//  
TInt CVtUiFeatureBase::DoInitFeaturesL( TAny* aAny )
    {
    __VTPRINTENTER( "CVtUiFeatureBase.DoInitFeaturesL" )
    CVtUiFeatureBase* self = static_cast< CVtUiFeatureBase* >( aAny );
    self->InitFeatureL();
    __VTPRINTEXIT( "CVtUiFeatureBase.DoInitFeaturesL" )
    return KErrNone;
    }   

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
* Description:  Video Telephone feature variation class definition.
*
*/


#include "tVtuifeaturevariation.h"

// TVtUiFeatureVariationBase

// -----------------------------------------------------------------------------
// TVtUiFeatureVariationBase::IsFeatureSupported
// -----------------------------------------------------------------------------
//   
TBool TVtUiFeatureVariationBase::IsFeatureSupported( const TUint32 aId ) const
		{
		return FeatureManager::FeatureSupported( aId );		
		}

//TVtUiHelpVariation
// -----------------------------------------------------------------------------
// TVtUiHelpVariation::FeatureId
// -----------------------------------------------------------------------------
//  	
TUint32 TVtUiHelpVariation::FeatureId() const
		{
		return KFeatureIdHelp;	
		}
// -----------------------------------------------------------------------------
// TVtUiHelpVariation::IsHelpSupported
// -----------------------------------------------------------------------------
//		
TBool TVtUiHelpVariation::IsHelpSupported() const
		{
		return IsFeatureSupported( FeatureId() );	
		}
//TVtUiDPVariation
// -----------------------------------------------------------------------------
// TVtUiDPVariation::FeatureId
// -----------------------------------------------------------------------------
//  	
TUint32 TVtUiDPVariation::FeatureId() const
		{
		return KFeatureIdDisplayPost;	
		}
// -----------------------------------------------------------------------------
// TVtUiDPVariation::IsDPSupported
// -----------------------------------------------------------------------------
//		
TBool TVtUiDPVariation::IsDPSupported() const
		{
		return IsFeatureSupported( FeatureId() );	
		}
//TVtUiBTVariation
// -----------------------------------------------------------------------------
// TVtUiBTVariation::FeatureId
// -----------------------------------------------------------------------------
//  	
TUint32 TVtUiBTVariation::FeatureId() const
		{
		return KFeatureIdBt;	
		}
// -----------------------------------------------------------------------------
// TVtUiBTVariation::IsBTSupported
// -----------------------------------------------------------------------------
//		
TBool TVtUiBTVariation::IsBTSupported() const
		{
		return IsFeatureSupported( FeatureId() );	
		}		
//TVtUiSideVolumeKeysVariation
// -----------------------------------------------------------------------------
// TVtUiSideVolumeKeysVariation::FeatureId
// -----------------------------------------------------------------------------
//  	
TUint32 TVtUiSideVolumeKeysVariation::FeatureId() const
		{
		return KFeatureIdSideVolumeKeys;	
		}
// -----------------------------------------------------------------------------
// TVtUiSideVolumeKeysVariation::IsSideVolumeKeysSupported
// -----------------------------------------------------------------------------
//		
TBool TVtUiSideVolumeKeysVariation::IsSideVolumeKeysSupported() const
		{
		return IsFeatureSupported( FeatureId() );	
		}
//TVtUiActiveIdleFetManVariation
// -----------------------------------------------------------------------------
// TVtUiActiveIdleFetManVariation::FeatureId
// -----------------------------------------------------------------------------
//  	
TUint32 TVtUiActiveIdleFetManVariation::FeatureId() const
		{
		return KFeatureIdActiveIdle;	
		}
// -----------------------------------------------------------------------------
// TVtUiActiveIdleFetManVariation::IsActiveIdleFetManSupported
// -----------------------------------------------------------------------------
//		
TBool TVtUiActiveIdleFetManVariation::IsActiveIdleFetManSupported() const
		{
		return IsFeatureSupported( FeatureId() );	
		}


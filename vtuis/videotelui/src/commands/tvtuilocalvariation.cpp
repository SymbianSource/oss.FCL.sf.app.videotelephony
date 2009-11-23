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
* Description:  Video Telephone local variation class.
*
*/


#include <centralrepository.h>
#include <settingsinternalcrkeys.h>
#include <cvtlogger.h>

#include "VideoTelephonyInternalCRKeys.h"
#include "tvtuilocalvariation.h"
#include "tVtuifeaturevariation.h"

// TVtUiVariationBase

// -----------------------------------------------------------------------------
// TVtUiVariationBase::ReadL
// -----------------------------------------------------------------------------
//    
void TVtUiVariationBase::ReadL( const TInt adefault ) 
    {
    __VTPRINTENTER( "VtUi.LocalVariation.ReadL" )
    CRepository* repository = CRepository::NewL( Uid() );
    TInt value( 0 );
    if ( !repository->Get( Key(), value ) )
        {
        SetValue( value );
        }
    // incase of error    
    else
    	{ 
    	// If default is set
    	if ( adefault != -1 )
    		{
    		__VTPRINT2( DEBUG_GEN, "VtUi.LocalVariation.ReadL def=%d", adefault )    
    		SetValue( adefault );    
    		}
    	}
    delete repository;
    __VTPRINTEXIT( "VtUi.LocalVariation.ReadL" )
    }    
// -----------------------------------------------------------------------------
// TVtUiVariationBase::Value
// -----------------------------------------------------------------------------
//
TUint32 TVtUiVariationBase::ReceiveValue() const
	{
	__VTPRINTENTER( "VtUi.LocalVariation.ReceiveValue" )
	__VTPRINTEXIT( "VtUi.LocalVariation.ReceiveValue" )
	return Value();
	}
	
// TVtUiVideoTelephonyVariation
// -----------------------------------------------------------------------------
// TVtUiVideoTelephonyVariation::Uid
// -----------------------------------------------------------------------------
//
const TUid& TVtUiVideoTelephonyVariation::Uid() const
    {
    return KCRUidVTVariation;
    }

// -----------------------------------------------------------------------------
// TVtUiVideoTelephonyVariation::Key
// -----------------------------------------------------------------------------
//
TUint32 TVtUiVideoTelephonyVariation::Key() const
    {
    return KVTLocalVariationFlags;
    }

// TVtUiActiveIdleVariation
// -----------------------------------------------------------------------------
// TVtUiActiveIdleVariation::IsActiveIdleEnabled
// -----------------------------------------------------------------------------
//
TBool TVtUiActiveIdleVariation::IsActiveIdleEnabled() 
    {
    __VTPRINTENTER( "VtUi.LocalVariation.AI.IsActiveIdleEnabled" )
    #ifndef RD_BOOT_CUSTOMIZABLE_AI
    	TVtUiActiveIdleFetManVariation featman;
    	TRAP_IGNORE( ReadL() );
    	__VTPRINTEXIT( "VtUi.LocalVariation.AI.IsActiveIdleEnabled" )
    	return featman.IsActiveIdleFetManSupported() && Value();
    	// AI 2 implementation always true
    #else
    	__VTPRINTEXIT( "VtUi.LocalVariation.AI.IsActiveIdleEnabled" )
    	return ETrue;
    #endif // RD_BOOT_CUSTOMIZABLE_AI
    }

// -----------------------------------------------------------------------------
// TVtUiActiveIdleVariation::Uid
// -----------------------------------------------------------------------------
//
const TUid& TVtUiActiveIdleVariation::Uid() const
    {
    return KCRUidPersonalizationSettings;
    }

// -----------------------------------------------------------------------------
// TVtUiActiveIdleVariation::Key
// -----------------------------------------------------------------------------
//
TUint32 TVtUiActiveIdleVariation::Key() const
    {
    return KSettingsActiveIdleState;
    }
    
// TVtUiGsMuteVariation
// -----------------------------------------------------------------------------
// TVtUiGsMuteVariation::GsMuteState
// -----------------------------------------------------------------------------
//
TUint32 TVtUiGsMuteVariation::GsMuteState() 
    {
    __VTPRINTENTER( "VtUi.LocalVariation.Gs.GsMuteState" )
    TRAP_IGNORE( ReadL( KAllwaysQuery ) );
    __VTPRINTEXIT( "VtUi.LocalVariation.Gs.GsMuteState" )
    return ReceiveValue();
    }
// -----------------------------------------------------------------------------
// TVtUiGsMuteVariation::Uid
// -----------------------------------------------------------------------------
//
const TUid& TVtUiGsMuteVariation::Uid() const
    {
    return KCRUidTelephonySettings;
    }

// -----------------------------------------------------------------------------
// TVtUiActiveIdleVariation::Key
// -----------------------------------------------------------------------------
//
TUint32 TVtUiGsMuteVariation::Key() const
    {
    return KSettingsVTVideoSending;
    }
// TVtUiToolbarVariation
// -----------------------------------------------------------------------------
// TVtUiToolbarVariation::NumberOfButtons
// -----------------------------------------------------------------------------
//
TUint32 TVtUiToolbarVariation::NumberOfButtons() 
    {
    __VTPRINTENTER( "VtUi.LocalVariation.Tb.NumberOfButtons" )
    TRAP_IGNORE( ReadL( KNumberOfTbButtons ) );
    __VTPRINTEXIT( "VtUi.LocalVariation.Tb.NumberOfButtons" )
    return ReceiveValue();
    }
// -----------------------------------------------------------------------------
// TVtUiToolbarVariation::Uid
// -----------------------------------------------------------------------------
//
const TUid& TVtUiToolbarVariation::Uid() const
    {
    return KCRUidVTConfiguration;
    }

// -----------------------------------------------------------------------------
// TVtUiActiveIdleVariation::Key
// -----------------------------------------------------------------------------
//
TUint32 TVtUiToolbarVariation::Key() const
    {
    return KVTToolbarCommands;
    }


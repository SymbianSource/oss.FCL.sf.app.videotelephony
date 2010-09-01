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
* Description:  Video Telephone local variation class inline methods.
*
*/


#include "VideoTelephonyVariant.hrh"

// TVtUiVideoTelephonyVariation

// -----------------------------------------------------------------------------
// TVtUiVideoTelephonyVariation::IsScalingMethodENearest
// -----------------------------------------------------------------------------
//
TBool TVtUiVideoTelephonyVariation::IsScalingMethodENearest() const
    {
    return IsFlag( KVTLVFlagScalingMethodENearest );
    }

// -----------------------------------------------------------------------------
// TVtUiVideoTelephonyVariation::IsScalingMethodEBilinear
// -----------------------------------------------------------------------------
//
TBool TVtUiVideoTelephonyVariation::IsScalingMethodEBilinear() const
    {
    return IsFlag( KVTLVFlagScalingMethodEBilinear );
    }

// -----------------------------------------------------------------------------
// TVtUiVideoTelephonyVariation::IsEnableBitReversal
// -----------------------------------------------------------------------------
//
TBool TVtUiVideoTelephonyVariation::IsEnableBitReversal() const
    {
    return IsFlag( KVTLVFlagEnableBitReversal );
    }

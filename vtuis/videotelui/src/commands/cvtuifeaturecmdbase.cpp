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
* Description:  Feature based UI command base class implementation.
*
*/


#include "cvtuifeaturecmdbase.h"
#include "mvtuifeature.h"

// ---------------------------------------------------------------------------
// CVtUiFeatureCmdBase::HandleL
// ---------------------------------------------------------------------------
//
void CVtUiFeatureCmdBase::HandleL()
    {
    iFeature.StartL();
    }

// ---------------------------------------------------------------------------
// CVtUiFeatureCmdBase::IsEnabled
// ---------------------------------------------------------------------------
//
TBool CVtUiFeatureCmdBase::IsEnabled() const
    {
    return ( iFeature.State() == MVtUiFeature::EReady ) ||
        ( iFeature.State() == MVtUiFeature::EUnprepared );
    }

// ---------------------------------------------------------------------------
// CVtUiFeatureCmdBase::CVtUiFeatureCmdBase
// ---------------------------------------------------------------------------
//
CVtUiFeatureCmdBase::CVtUiFeatureCmdBase( MVtUiFeature& aFeature,
    TInt aCommandId ) : CVtUiCmdBase( aCommandId ), iFeature( aFeature )
    {
    }

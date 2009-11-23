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
* Description:  Custom command validation action base class.
*
*/


#include <cvtlogger.h>

#include "cvtuicmdcustomvalidationactionbase.h"

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiCmdCustomValidationActionBase::CustomTypeId
// ---------------------------------------------------------------------------
//
CVtUiCmdCustomValidationActionBase::TCustomTypeId
CVtUiCmdCustomValidationActionBase::CustomTypeId() const
    {
    return iCustomTypeId;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdCustomValidationActionBase::BeginProcess
// ---------------------------------------------------------------------------
//
CVtUiCmdCustomValidationActionBase::CVtUiCmdCustomValidationActionBase(
    TCustomTypeId aCustomTypeId )
    : iCustomTypeId( aCustomTypeId )
    {
    }

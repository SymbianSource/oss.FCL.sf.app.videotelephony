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
* Description:  Command context base class.
*
*/


#include <cvtlogger.h>

#include "cvtuicommandmodifybase.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiCommandModifyBase::CVtUiCommandModifyBase
// ---------------------------------------------------------------------------
//
CVtUiCommandModifyBase::CVtUiCommandModifyBase( TInt aPriority )
    : iPriority( aPriority )
    {
    }

// ---------------------------------------------------------------------------
// CVtUiCommandModifyBase::PriorityOrder
// ---------------------------------------------------------------------------
//
TLinearOrder< CVtUiCommandModifyBase > CVtUiCommandModifyBase::PriorityOrder()
    {
    return TLinearOrder< CVtUiCommandModifyBase >( PriorityOrderFunc );
    }

// ---------------------------------------------------------------------------
// CVtUiCommandModifyBase::PriorityOrderFunc
// ---------------------------------------------------------------------------
//
TInt CVtUiCommandModifyBase::PriorityOrderFunc(
    const CVtUiCommandModifyBase& aM1, const CVtUiCommandModifyBase& aM2 )
    {
    return aM1.iPriority - aM2.iPriority;
    }


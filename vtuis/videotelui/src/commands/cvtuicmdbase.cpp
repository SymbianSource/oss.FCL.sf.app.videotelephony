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
* Description:  UI command bases class implementation.
*
*/


#include "cvtuicmdbase.h"

// ======== LOCAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// FindCVtUiCmdBaseById
// ---------------------------------------------------------------------------
//
TInt FindCVtUiCmdBaseById( const CVtUiCmdBase& aC1, const CVtUiCmdBase& aC2 )
    {
    return ( aC1.CommandId() - aC2.CommandId() );
    }

// ---------------------------------------------------------------------------
// FindCVtUiCmdBaseByKey
// ---------------------------------------------------------------------------
//
TInt FindCVtUiCmdBaseByKey( const TInt* aKey, const CVtUiCmdBase& aC )
    {
    return ( *aKey - aC.CommandId() );
    }

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CVtUiCmdBase::CommandId
// ---------------------------------------------------------------------------
//
TInt CVtUiCmdBase::CommandId() const
    {
    return iCommandId;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdBase::LinearOrder
// ---------------------------------------------------------------------------
//
TLinearOrder< CVtUiCmdBase > CVtUiCmdBase::LinearOrder()
    {
    return TLinearOrder< CVtUiCmdBase >( ::FindCVtUiCmdBaseById );
    }

// ---------------------------------------------------------------------------
// CVtUiCmdBase::LinearOrder
// ---------------------------------------------------------------------------
//
CVtUiCmdBase::TKeyOrder CVtUiCmdBase::KeyOrder()
    {
    return ::FindCVtUiCmdBaseByKey;
    }

// ---------------------------------------------------------------------------
// CVtUiCmdBase::CVtUiCmdBase
// ---------------------------------------------------------------------------
//
CVtUiCmdBase::CVtUiCmdBase( TInt aCommandId ) : iCommandId( aCommandId )
    {
    }

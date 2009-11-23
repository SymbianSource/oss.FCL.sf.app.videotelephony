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
* Description:  Menu command iterator.
*
*/


#include <eikmenup.h>

#include "tvtuimenucommanditerator.h"

// ======== LOCAL FUNCTIONS ========

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// TVtUiMenuCommandIterator::TVtUiMenuCommandIterator
// ---------------------------------------------------------------------------
//
TVtUiMenuCommandIterator::TVtUiMenuCommandIterator( CEikMenuPane& aMenuPane )
: iMenuPane( &aMenuPane ), iCurrent( 0 )
    {
    }

// ---------------------------------------------------------------------------
// TVtUiMenuCommandIterator::HasNext
// ---------------------------------------------------------------------------
//
TBool TVtUiMenuCommandIterator::HasNext() const
    {
    return ( iCurrent < iMenuPane->NumberOfItemsInPane() );
    }

// ---------------------------------------------------------------------------
// TVtUiMenuCommandIterator::Next
// ---------------------------------------------------------------------------
//
TInt TVtUiMenuCommandIterator::Next()
    {
    return iMenuPane->MenuItemCommandId( iCurrent++ );
    }


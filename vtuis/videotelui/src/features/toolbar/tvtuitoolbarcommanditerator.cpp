/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Toolbar command iterator implementation.
*
*/


#include "cvtuitoolbarbase.h"
#include "tvtuitoolbarcommanditerator.h"

// ======== LOCAL FUNCTIONS ========

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// TVtUiToolbarCommandIterator::TVtUiToolbarCommandIterator
// ---------------------------------------------------------------------------
//
TVtUiToolbarCommandIterator::TVtUiToolbarCommandIterator( CVtUiToolbarBase&
    aToolbar ) : iToolbar( &aToolbar ), iCurrent( 0 )
    {
    }

// ---------------------------------------------------------------------------
// TVtUiToolbarCommandIterator::HasNext
// ---------------------------------------------------------------------------
//
TBool TVtUiToolbarCommandIterator::HasNext() const
    {
    return ( iCurrent < iToolbar->NumberOfToolbarControls() );
    }

// ---------------------------------------------------------------------------
// TVtUiToolbarCommandIterator::Next
// ---------------------------------------------------------------------------
//
TInt TVtUiToolbarCommandIterator::Next()
    {
    return iToolbar->CommandIdByCmdIdsArrayIndex( iCurrent++ );
    }
    
//  End of File

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
* Description:  Component ID block lists implementation.
*
*/


#include "tvtuiblocklists.h"

const static TUint KNullBlockMask = 0;

// Implementation for TVtUiBlockList

// -----------------------------------------------------------------------------
// TVtUiBlockList::~TVtUiBlockList
// -----------------------------------------------------------------------------
//
TVtUiBlockList::~TVtUiBlockList()
    {
    }

// -----------------------------------------------------------------------------
// TVtUiBlockList::TVtUiBlockList
// -----------------------------------------------------------------------------
//
TVtUiBlockList::TVtUiBlockList()
    {
    }

// Implementation for TVtUiBlockListBitField

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::TVtUiBlockListBitField
// -----------------------------------------------------------------------------
//
TVtUiBlockListBitField::TVtUiBlockListBitField() : iBlockMask( KNullBlockMask )
    {
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::TVtUiBlockListBitField
// -----------------------------------------------------------------------------
//
TVtUiBlockListBitField::TVtUiBlockListBitField( TUint aBlockMask )
    : iBlockMask( aBlockMask )
    {
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::IsEmpty
// -----------------------------------------------------------------------------
//
TBool TVtUiBlockListBitField::IsEmpty() const
    {
    return !iBlockMask;
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::Contains
// -----------------------------------------------------------------------------
//
TBool TVtUiBlockListBitField::Contains( MVtUiComponent::TComponentId aId ) const
    {
    return ( iBlockMask & aId ) && ( aId != MVtUiComponent::EComponentIdNull );
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::Union
// -----------------------------------------------------------------------------
//
void TVtUiBlockListBitField::Union( const TVtUiBlockList& aBlockList )
    {
    iBlockMask |=
        static_cast< const TVtUiBlockListBitField& >( aBlockList ).iBlockMask;
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::IteratorLC
// -----------------------------------------------------------------------------
//
CVtUiBlockListIterator* TVtUiBlockListBitField::IteratorLC() const
    {
    return TVtUiBlockListBitField::CVtUiBListIteratorBF::NewLC( iBlockMask );
    }

// Implementation for TVtUiBlockListBitField::CVtUiBListIteratorBF

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::CVtUiBListIteratorBF::NewLC
// -----------------------------------------------------------------------------
//
TVtUiBlockListBitField::CVtUiBListIteratorBF*
TVtUiBlockListBitField::CVtUiBListIteratorBF::NewLC(
    const TUint& aBlockMask )
    {
    CVtUiBListIteratorBF* self = new ( ELeave )
        CVtUiBListIteratorBF( aBlockMask );
    CleanupStack::PushL( self );
    return self;
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::CVtUiBListIteratorBF::CVtUiBListIteratorBF
// -----------------------------------------------------------------------------
//
TVtUiBlockListBitField::CVtUiBListIteratorBF::CVtUiBListIteratorBF(
    const TUint& aBlockMask ) : iBlockMask( aBlockMask ), iCurrent( 1 )
    {
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::CVtUiBListIteratorBF::HasNext
// -----------------------------------------------------------------------------
//
TBool TVtUiBlockListBitField::CVtUiBListIteratorBF::HasNext() const
    {
    return ( iCurrent && ( iCurrent <= iBlockMask ) );
    }

// -----------------------------------------------------------------------------
// TVtUiBlockListBitField::CVtUiBListIteratorBF::Next
// -----------------------------------------------------------------------------
//
MVtUiComponent::TComponentId
TVtUiBlockListBitField::CVtUiBListIteratorBF::Next()
    {
    MVtUiComponent::TComponentId id( MVtUiComponent::EComponentIdNull );

    while ( HasNext() && !( iCurrent & iBlockMask ) )
        {
        iCurrent <<= 1;
        }

    if ( iCurrent )
        {
        id = static_cast< MVtUiComponent::TComponentId >( iCurrent );
        }

	iCurrent <<= 1;

    return id;
    }

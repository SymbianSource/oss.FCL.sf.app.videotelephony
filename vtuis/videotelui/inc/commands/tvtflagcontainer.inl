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
* Description:  Flag container class inline methods.
*
*/


// -----------------------------------------------------------------------------
// TVtFlagContainer::TVtFlagContainer
// -----------------------------------------------------------------------------
//
TVtFlagContainer::TVtFlagContainer()
    {
    Clear();
    }

// -----------------------------------------------------------------------------
// TVtFlagContainer::Clear
// -----------------------------------------------------------------------------
//
void TVtFlagContainer::Clear()
    {
    iFlags = 0;
    }

// -----------------------------------------------------------------------------
// TVtFlagContainer::IsFlag
// -----------------------------------------------------------------------------
//
TBool TVtFlagContainer::IsFlag( TUint32 aFlags ) const
    {
    return ( iFlags & aFlags );
    }

// -----------------------------------------------------------------------------
// TVtFlagContainer::SetFlag
// -----------------------------------------------------------------------------
//
void TVtFlagContainer::SetFlag( TUint32 aFlags )
    {
    iFlags |= aFlags;
    }

// -----------------------------------------------------------------------------
// TVtFlagContainer::ClearFlag
// -----------------------------------------------------------------------------
//
void TVtFlagContainer::ClearFlag( TUint32 aFlags )
    {
    iFlags &= ~aFlags;
    }

// -----------------------------------------------------------------------------
// TVtFlagContainer::Value
// -----------------------------------------------------------------------------
//
TUint32 TVtFlagContainer::Value() const
    {
    return iFlags;
    }

// -----------------------------------------------------------------------------
// TVtFlagContainer::SetValue
// -----------------------------------------------------------------------------
//
void TVtFlagContainer::SetValue( TUint32 aValue )
    {
    iFlags = aValue;
    }

// -----------------------------------------------------------------------------
// TVtUpdateableFlagContainer::Update
// -----------------------------------------------------------------------------
//
void TVtUpdateableFlagContainer::Update()
    {
    Clear();
    UpdateFlags();
    }

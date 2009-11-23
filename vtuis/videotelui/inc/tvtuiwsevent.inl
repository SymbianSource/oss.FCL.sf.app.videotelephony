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
* Description:  VT UI window server event inline methods.
*
*/


// -----------------------------------------------------------------------------
// TVtUiWsEvent::TVtUiWsEvent
// -----------------------------------------------------------------------------
//
template < class T >
TVtUiWsEvent< T >::TVtUiWsEvent( TInt aType, T* aData )
    {
    SetType( aType );
    Int()[ 0 ] = ( TInt ) aData;
    }

// -----------------------------------------------------------------------------
// TVtUiWsEvent::Data
// -----------------------------------------------------------------------------
//
template < class T >
T* TVtUiWsEvent< T >::Data() const
    {
    return ( T* )Int()[ 0 ];
    }

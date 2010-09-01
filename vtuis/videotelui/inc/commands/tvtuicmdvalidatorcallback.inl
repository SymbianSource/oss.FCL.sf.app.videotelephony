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
* Description:  Command validator callback class inline methods.
*
*/


// -----------------------------------------------------------------------------
// TVtUiCmdValidatorCallBack< T >::TVtUiCmdValidatorCallBack
// -----------------------------------------------------------------------------
//
template < class T >
TVtUiCmdValidatorCallBack< T >::TVtUiCmdValidatorCallBack(
    const T& aInstance, TCallBackMethod aMethod )
    : iInstance( &aInstance ), iMethod( aMethod )
    {
    }

// -----------------------------------------------------------------------------
// TVtUiCmdValidatorCallBack< T >::Call
// -----------------------------------------------------------------------------
//
template < class T >
TBool TVtUiCmdValidatorCallBack< T >::Call( TInt aCommandId ) const
    {
    return ( iInstance->*iMethod )( aCommandId );
    }


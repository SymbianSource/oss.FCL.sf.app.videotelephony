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
* Description:  Command validator callback class definition.
*
*/


#ifndef T_VTUICMDVALIDATORCALLBACK_H
#define T_VTUICMDVALIDATORCALLBACK_H

#include <e32base.h>

/**
 *  MVtUiCmdValidatorCallBack
 *
 *  Command validator callback API.
 *
 *  @since S60 v3.2
 */
class MVtUiCmdValidatorCallBack
    {

public:

    /**
     * Invokes callback call.
     */
    virtual TBool Call( TInt ) const = 0;

    };

/**
 *  TVtUiCmdValidatorCallBack
 *
 *  Validator callback wrapper to maintain type safety. Also allows use of
 *  different types of instances for invocation of callback.
 *
 *  @since S60 v3.2
 */
template < class T >
NONSHARABLE_CLASS( TVtUiCmdValidatorCallBack )
: public MVtUiCmdValidatorCallBack
    {

    // Callback method type definition
    typedef TBool ( T::*TCallBackMethod )( TInt ) const;

public:

    /**
     * Constructor
     *
     * @param aInstance Instance on which callback method will be called.
     * @param aMethod Callback method to be called.
     */
    TVtUiCmdValidatorCallBack( const T& aInstance, TCallBackMethod aMethod );

    /**
     * Executes callback.
     *
     * @param aParameter Callback parameter, e.g. command Id or resource Id.
     * @return Callback result.
     */
    TBool Call( TInt aParameter ) const;

private:

    // Instance from which callback method will be invoke
    const T* iInstance;

    // Callback method pointer
    TCallBackMethod iMethod;

    };

#include "tvtuicmdvalidatorcallback.inl"

#endif // T_VTUICMDVALIDATORCALLBACK_H

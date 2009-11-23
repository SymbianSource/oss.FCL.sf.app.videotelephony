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
* Description:  Command iterator API definition.
*
*/


#ifndef M_VTUICOMMANDITERATOR_H
#define M_VTUICOMMANDITERATOR_H

#include <e32base.h>

/**
 *  MVtUiCommandIterator
 *
 *  API for iterating through set of commands.
 *
 *  @since S60 v3.2
 */
class MVtUiCommandIterator
    {

public:

    /**
     * Returns ETrue if the iteration has more elements
     *
     * @return ETrue if iteration contains more commands (i.e. call to Next()
     * will return a valid command), EFalse otherwise.
     */
    virtual TBool HasNext() const = 0;

    /**
     * Returns the next command in the iteration.
     *
     * @return Next command in the iteration.
     */
    virtual TInt Next() = 0;

    };

#endif // M_VTUICOMMANDITERATOR_H

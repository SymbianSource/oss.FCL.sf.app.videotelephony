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
* Description:  Menu command iterator class definition.
*
*/


#ifndef T_VTUIMENUCOMMANDITERATOR_H
#define T_VTUIMENUCOMMANDITERATOR_H

#include "mvtuicommanditerator.h"

/**
 *  TVtUiMenuCommandIterator
 *
 *  Menu command iterator class definition.
 *
 *  @since S60 v3.2
 */
class TVtUiMenuCommandIterator : public MVtUiCommandIterator
    {

public: // public methods

    /**
     * C++ constructor
     *
     */
    TVtUiMenuCommandIterator( CEikMenuPane& aMenuPane );

public: // from MVtUiCommandIterator

    /**
     * @see MVtUiCommandIterator::HasNext
     */
    TBool HasNext() const;

    /**
     * @see MVtUiCommandIterator::Next
     */
    TInt Next();

private:

    // Pointer to menu pane to be iterated
    CEikMenuPane* iMenuPane;

    // Current iteration point
    TInt iCurrent;

    };

#endif // T_VTUIMENUCOMMANDITERATOR_H

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
* Description:  UI command bases class definition.
*
*/


#ifndef C_VTUICMDBASE_H
#define C_VTUICMDBASE_H

#include <e32base.h>

/**
 *  CVtUiCmdBase
 *
 *  Base class for UI commands.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCmdBase ) : public CBase
    {

public: // public methods

    /**
     * Returns command id.
     *
     * @return This command's id.
     */
    TInt CommandId() const;

public: // public abstract methods

    /**
     * Execute command
     *
     */
    virtual void HandleL() = 0;

    /**
     * Returns ETrue if command is enabled.
     *
     * @return ETrue if this command is enabled (can be executed), EFalse
     * otherwise.
     */
    virtual TBool IsEnabled() const = 0;

public: // public static methods

    /**
     * Key comparing function type definition.
     */
    typedef TInt ( *TKeyOrder ) ( const TInt*, const CVtUiCmdBase& );

    /**
     * Returns linear order object for ordered array inserting.
     *
     * @return TLinearOrder instance for searching and inserting CVtUiCmdBase
     * based objects into RArray.
     */
    static TLinearOrder< CVtUiCmdBase > LinearOrder();

    /**
     * Returns linear order object for ordered array inserting.
     *
     * @return Pointer to key comparaing function, that can be used in
     * FindInOrder() method call.
     */
    static TKeyOrder KeyOrder();

protected:

    /**
     * C++ constructor.
     *
     * @aCommandId Id of this command.
     *
     */
    CVtUiCmdBase( TInt aCommandId );

protected:

    // Command id
    const TInt iCommandId;

    };

#endif // C_VTUICMDBASE_H

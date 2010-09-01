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
* Description:  Command modifier base class definition.
*
*/


#ifndef C_VTUICOMMANDMODIFYBASE_H
#define C_VTUICOMMANDMODIFYBASE_H

#include <e32base.h>

#include "mvtuicommandsetting.h"

/**
 *  CVtUiCommandModifyBase
 *
 *  Command modifier base class. Command modifiers can be used for modifying
 *  different command sets. E.g. in toolbar and number entry a command modifiers
 *  are being used for modifying softkeys.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCommandModifyBase ) : public CBase
    {

public: // static methods

    /**
     * Returns TLinearOrder<> for priority ordering.
     */
    static TLinearOrder< CVtUiCommandModifyBase > PriorityOrder();

private: // static methods

    /**
     * Priority ordering function.
     */
    static TInt PriorityOrderFunc( const CVtUiCommandModifyBase& aM1,
        const CVtUiCommandModifyBase& aM2 );

public: // pure virtual methods

    /**
     * Modifies command set.
     */
    virtual void ModifyCommandsL( MVtUiCommandSetting& aCommandSettings ) = 0;

    /**
     * Returns ETrue if this modifier supports given command set type.
     */
    virtual TBool Supports( MVtUiCommandSetting::Type aType ) const = 0;

protected:

    /**
     * Constructor
     */
    CVtUiCommandModifyBase( TInt aPriority );

private:

    // Modifier priority
    const TInt iPriority;

    };

#endif // C_VTUICOMMANDMODIFYBASE_H

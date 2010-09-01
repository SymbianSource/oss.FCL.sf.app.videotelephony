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
* Description:  Menu context class definition.
*
*/


#ifndef C_VTUIMENUCONTEXT_H
#define C_VTUIMENUCONTEXT_H

#include <e32base.h>

#include "cvtuicmdcontext.h"

/**
 *  CVtUiMenuContext
 *
 *  Menu command context class definition.
 *
 *  @since S60 v3.2
 */
class CVtUiMenuContext : public CVtUiCmdContext
    {

public: // public methods

    /**
     * C++ destructor.
     *
     */
    ~CVtUiMenuContext();

    /**
     * Leave safe destructor.
     *
     */
    static CVtUiMenuContext* NewL( MVtUiCommandManager& aCommandManager );

public: // from CVtUiCmdContext

    /**
     *  @see CVtUiCmdContext::ValidateL
     */
    void ValidateL( CVtUiCmdValidationActionBase& aAction );

private:

    /**
     * C++ constructor
     *
     * @param aPriority Validator priority.
     */
    CVtUiMenuContext( MVtUiCommandManager& aCommandManager );

    /**
     * 2nd consttuctor, may leave.
     */
    void ConstructL();

private: // data

    };

#endif // C_VTUIMENUCONTEXT_H

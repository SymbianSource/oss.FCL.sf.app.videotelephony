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
* Description:  Softkey context class definition.
*
*/


#ifndef C_VTUISOFTKEYCONTEXT_H
#define C_VTUISOFTKEYCONTEXT_H

#include <e32base.h>

#include "cvtuicmdcontext.h"

/**
 *  CVtUiSoftkeyContext
 *
 *  Softkey command context class definition.
 *
 *  @since S60 v3.2
 */
class CVtUiSoftkeyContext : public CVtUiCmdContext
    {

public: // public methods

    /**
     * C++ destructor.
     */
    ~CVtUiSoftkeyContext();

    /**
     * Static constructor
     * @param aCommandManager Reference to command manager.
     */
    static CVtUiSoftkeyContext* NewL( MVtUiCommandManager& aCommandManager );

public: // virtual methods

    /**
     * Make validations.
     *
     * @param aAction Reference to validation action base.
     */
    void ValidateL( CVtUiCmdValidationActionBase& aAction );

private:

    /**
     * C++ constructor
     *
     *  @param aCommandManager Reference to command manager.
     */
    CVtUiSoftkeyContext( MVtUiCommandManager& aCommandManager );

    /**
     * 2nd consttuctor, may leave.
     */
    void ConstructL();

    };

#endif // C_VTUISOFTKEYCONTEXT_H

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
* Description:  Execution context class definition.
*
*/


#ifndef C_VTUIEXECUTIONCONTEXT_H
#define C_VTUIEXECUTIONCONTEXT_H

#include "cvtuicmdcontext.h"

/**
 *  CVtUiExecutionContext
 *
 *  Command execution context. This context is used for checking whether or not
 *  a command is allowed to be performed.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiExecutionContext ) : public CVtUiCmdContext
    {

public: // public methods

    /**
     * C++ destructor.
     */
    ~CVtUiExecutionContext();

    /**
     * Static constructor.
     *
     * @param aCommandManager Reference to command manager.
     * @return Newly created instance of CVtUiExecutionContext class.
     */
    static CVtUiExecutionContext* NewL( MVtUiCommandManager& aCommandManager );

public: // from CVtUiCmdContext

    /**
     * @see CVtUiCmdContext::ValidateL
     */
    void ValidateL( CVtUiCmdValidationActionBase& aAction );

private:

    /**
     * C++ constructor
     */
    CVtUiExecutionContext( MVtUiCommandManager& aCommandManager );

    /**
     * 2nd constructor, may leave.
     */
    void ConstructL();

private: // data

    };

#endif // C_VTUIEXECUTIONCONTEXT_H

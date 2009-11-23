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
* Description:  Command validation action base class definition.
*
*/


#ifndef C_VTUICMDVALIDATIONACTIONBASE_H
#define C_VTUICMDVALIDATIONACTIONBASE_H

#include <e32base.h>

class CVtUiCmdValidatorBase;
class MVtUiCmdValidatorCallBack;

/**
 *  CVtUiCmdValidationActionBase
 *
 *  Command validation action base class.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCmdValidationActionBase ) : public CBase
    {

public: // public methods

    /**
     * C++ destructor.
     */
    ~CVtUiCmdValidationActionBase();

    /**
     * Called when validation process is about to begin. Resets internal
     * variables.
     */
    virtual void BeginProcess();

    /**
     * Called when validation process has finished.
     */
    virtual void EndProcess();

public: // pure virtual methods

    /**
     * Execute validation process.
     *
     * @param aCallBack Action validation callback routine that will be called
     * for every item to be validated.
     */
    virtual void ProcessL( const MVtUiCmdValidatorCallBack& aCallBack ) = 0;

protected:

    /**
     * Mark command handled.
     *
     * @param aCommandId Id of command that was handled.
     */
    void CommandHandledL( TInt aCommandId );

    /**
     * Check whether command is already handled or not.
     *
     * @param aCommandId Id of command to be checked.
     * @return ETrue if command was already handler, EFalse otherwise.
     */
    TBool IsCommandHandled( TInt aCommandId ) const;

private: // data

    // Array of handled commands.
    RArray< TInt > iHandledCommands;

    };

#endif // C_VTUICMDVALIDATIONACTIONBASE_H

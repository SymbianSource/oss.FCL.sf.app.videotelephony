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
* Description:  Command state check action.
*
*/


#ifndef C_VTUICMDSTATECHECKACTION_H
#define C_VTUICMDSTATECHECKACTION_H

#include "cvtuicmdcustomvalidationactionbase.h"

/**
 *  CVtUiCmdStateCheckAction
 *
 *  Custom validation action that concludes whether or not a command is allowed.
 *  Command validness is checked from its current state.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCmdStateCheckAction )
: public CVtUiCmdCustomValidationActionBase
    {

public:

    /**
     * Static constructor.
     *
     * @return Pointer to newly created instance of CVtUiCmdStateCheckAction.
     */
    static CVtUiCmdStateCheckAction* NewL();

    /**
     * Sets command to be checked.
     *
     * @param aCommandId Id of command to be checked.
     */
    void SetCommand( TInt aCommandId );

    /**
     * Sets command to be checked.
     *
     * @return ETrue is command set with SetCommand() is allowed to be
     * executed.
     */
    TBool IsCommandAllowed() const;

public: // from CVtUiCmdValidationActionBase

    /**
     * @see CVtUiCmdValidationActionBase::ProcessL
     */
    void ProcessL( const MVtUiCmdValidatorCallBack& aCallBack );

private:

    /**
     * C++ constructor.
     */
    CVtUiCmdStateCheckAction();

private: // data

    // Id of command to be checked
    TInt iCommandId;

    // ETrue if command defined by iCommandId is allowed
    TBool iIsCommandAllowed;

    };

#endif // C_VTUICMDSTATECHECKACTION_H

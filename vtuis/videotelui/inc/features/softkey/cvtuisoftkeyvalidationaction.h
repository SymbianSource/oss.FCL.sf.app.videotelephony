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
* Description:  Softkey validation action class definition.
*
*/


#ifndef C_CVTUISOFTKEYVALIDATIONACTION_H
#define C_CVTUISOFTKEYVALIDATIONACTION_H

#include <e32base.h>

#include "cvtuicmdvalidationactionbase.h"

/**
 *  CVtUiSoftkeyValidationAction
 *
 *  Softkey validation action definition.
 *
 *  @since S60 v3.2
 */
class CVtUiSoftkeyValidationAction : public CVtUiCmdValidationActionBase
    {

public:

    /**
     * Static constructor
     */
    static CVtUiSoftkeyValidationAction* NewL();

public: // from CVtUiCmdValidationActionBase

    /**
     * @see CVtUiCmdValidationActionBase::BeginProcess
     */
    void BeginProcess();

    /**
     * @see CVtUiCmdValidationActionBase::ProcessL
     */
    void ProcessL( const MVtUiCmdValidatorCallBack& aCallBack );

public: // new methods

    /**
     * Returns resource id after validation process.
     */
    TInt ResourceId() const;

private:

    /**
     * C++ constructor.
     *
     */
    CVtUiSoftkeyValidationAction();

private: // data

    // Index to currently selected softkey
    TInt iCurrentIdx;

    };

#endif // C_CVTUISOFTKEYVALIDATIONACTION_H

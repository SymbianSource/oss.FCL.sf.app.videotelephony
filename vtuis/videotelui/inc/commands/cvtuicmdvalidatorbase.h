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
* Description:  Base class for command validators.
*
*/


#ifndef C_VTUICMDVALIDATORBASE_H
#define C_VTUICMDVALIDATORBASE_H

#include <e32base.h>

#include "tvtuicmdcontexttype.h"

class CVtUiCmdValidationActionBase;
class CVtUiCmdCustomValidationActionBase;

/**
 *  CVtUiCmdValidatorBase
 *
 *  Base class for all validators. Validator implementations validate commands
 *  and other properties (like softkey resource IDs) on context basis. E.g.
 *  primary validator will validate commands in all contexts, while toolbar
 *  validator will do fine tuning for commands only in menu context, so that
 *  commands that are visible in toolbar are not shown in menu.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCmdValidatorBase ) : public CBase
    {

public: // public methods

    /**
     * Returns validator priority.
     *
     * @return Validator priority.
     */
    TInt Priority() const;

public: // pure virtual methods

    /**
     * Validates menu items.
     *
     * @param aAction Reference to validation action.
     * @param aReferencePriority Context reference priority.
     */
    virtual void ValidateMenuItemsL( CVtUiCmdValidationActionBase& aAction,
        TInt aReferencePriority ) = 0;

    /**
     * Validates softkey items.
     *
     * @param aAction Reference to validation action.
     * @param aReferencePriority Context reference priority.
     */
    virtual void ValidateSoftkeyItemsL( CVtUiCmdValidationActionBase& aAction,
        TInt aReferencePriority ) = 0;

    /**
     * Validates toolbar items.
     *
     * @param aAction Reference to validation action.
     * @param aReferencePriority Context reference priority.
     */
    virtual void ValidateToolbarItemsL( CVtUiCmdValidationActionBase& aAction,
        TInt aReferencePriority ) = 0;

    /**
     * Custom validation.
     *
     * @param aAction Reference to custom validation action.
     * @param aReferencePriority Context reference priority.
     */
    virtual void CustomValidationL( CVtUiCmdCustomValidationActionBase& aAction,
        TInt aReferencePriority ) = 0;

    /**
     * Query for context validation.
     *
     * @param aCtxType Command context type.
     * @return ETrue if this instance validates given context type, EFalse
     * otherwise.
     */
    virtual TBool ValidatesContext( const TVtUiCmdContextType& aCtxType )
        const = 0;

protected:

    /**
     * C++ constructor
     *
     * @param aPriority Validator priority.
     */
    CVtUiCmdValidatorBase( TInt aPriority );

private: // data

    // Validator priority
    const TInt iPriority;

    };

#endif // C_VTUICMDVALIDATORBASE_H

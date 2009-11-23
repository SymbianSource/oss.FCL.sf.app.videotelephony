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
* Description:  Command context base class definition.
*
*/


#ifndef C_VTUICMDCONTEXT_H
#define C_VTUICMDCONTEXT_H

#include <e32base.h>

#include "tvtuicmdcontexttype.h"

class CVtUiCmdValidatorBase;
class CVtUiCmdValidationActionBase;
class MVtUiCommandManager;
class CVtUiCmdCustomValidationActionBase;

/**
 *  CVtUiCmdContext
 *
 *  Command context base class. This class defines context in which commands
 *  will be validated.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCmdContext ) : public CBase
    {

public: // public methods

    /**
     * C++ destructor.
     */
    ~CVtUiCmdContext();

    /**
     * Returns reference priority.
     *
     * @return Validator priority.
     */
     TInt ReferencePriority() const;

    /**
     * Returns context type.
     *
     * @return Context type.
     */
     TVtUiCmdContextType ContextType() const;

    /**
     * Adds validator to context.
     *
     * @param aValidator Validator reference to be added into this context.
     * @return KErrNone if validator supports this context and adding succeeded.
     * KErrNotSupported if validator does not support this context.
     * Other system wide error code that may happen during add.
     */
    TInt AddValidator( CVtUiCmdValidatorBase& aValidator );

    /**
     * Removes validator to context.
     *
     * @param aValidator Constant validator reference to be removed from this
     * context.
     * @return Validator priority.
     */
    void RemoveValidator( const CVtUiCmdValidatorBase& aValidator );

public: // pure virtual methods

    /**
     * Do validation.
     *
     * @param aAction Action to be validated.
     */
    virtual void ValidateL( CVtUiCmdValidationActionBase& aAction ) = 0;

protected:

    /**
     * C++ constructor
     */
    CVtUiCmdContext( MVtUiCommandManager& aCommandManager,
        TVtUiCmdContextType aCtxType, TInt aReferencePriority );

    /**
     * Validates menu items.
    */
    void ValidateMenuItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * Validates softkey items.
    */
    void ValidateSoftkeyItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * Validates toolbar items.
    */
    void ValidateToolbarItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * Custom action validation.
    */
    void CustomValidationL( CVtUiCmdCustomValidationActionBase& aAction );

    /**
     * Registers command context to command policy manager.
     */
    void RegisterCommandContextL();

    /**
     * Unregisters command context from command policy manager.
     */
    void UnregisterCommandContext();

protected: // data

    // Reference to policy manager (for cleanup)
    MVtUiCommandManager& iCommandManager;

private: // data

    // Validator list (ordered by priority)
    RPointerArray< CVtUiCmdValidatorBase > iValidators;

    // Validator priority
    const TInt iReferencePriority;

    // Context type.
    const TVtUiCmdContextType iContextType;

    };

#endif // C_VTUICMDCONTEXT_H

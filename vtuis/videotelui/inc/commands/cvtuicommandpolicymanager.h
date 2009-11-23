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
* Description:  Command policy manager class definition.
*
*/


#ifndef C_VTUICOMMANDPOLICYMANAGER_H
#define C_VTUICOMMANDPOLICYMANAGER_H

#include <e32base.h>

#include "tvtuicmdcontexttype.h"

class CVtUiCmdContext;
class CVtUiCmdValidatorBase;
class CVtUiCmdValidationActionBase;
class CVtUiCmdCustomValidationActionBase;
class CVtUiCommandManager;
class CVtUiPrimaryCmdPolicy;

/**
 * CVtUiCommandPolicyManager
 *
 * Contains pointers to all registered command contexts and commnd policy
 * instances. When validation is required, calls proper methods in proper
 * context for registered validators in validator priority order.
 *
 * @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCommandPolicyManager ) : public CBase
    {

public: // public methods

    /**
     * Static constructor.
     *
     * @param aCmdManager Constant reference to command manager instance.
     * @return Newly created instance of CVtUiCommandPolicyManager class.
     */
    static CVtUiCommandPolicyManager*
        NewL( const CVtUiCommandManager& aCmdManager );

    /**
     * C++ destructor.
     */
    ~CVtUiCommandPolicyManager();

    /**
     * Registers command context.
     *
     * @param aContext Reference to command context to be registered.
     * @return KErrNone if registration succeeded.
     */
    TInt RegisterCommandContext( CVtUiCmdContext& aContext );

    /**
     * Unregisters command context.
     *
     * @param aContext Constant reference to command context to be unregistered.
     */
    void UnregisterCommandContext( CVtUiCmdContext& aContext );

    /**
     * Adds validator to policy manager and registered contexts.
     *
     * @param aValidator Reference to validator to be added.
     * @return KErrNone if add succeeded.
     */
    TInt AddValidator( CVtUiCmdValidatorBase& aValidator );

    /**
     * Removes validator from policy manager and registered contexts.
     *
     * @param aValidator Constant reference to validator to be removed.
     */
    void RemoveValidator( CVtUiCmdValidatorBase& aValidator );

    /**
     * Validates menu items for given action.
     *
     * @param aAction Reference to validation action to be carried on menu
     * commmands.
     */
    void ValidateMenuItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * Validates softkey items for given action.
     *
     * @param aAction Reference to validation action to be carried on softkeys.
     */
    void ValidateSoftkeyItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * Validates toolbar items for given action.
     *
     * @param aAction Reference to validation action to be carried on toolbar
     * commands.
     */
    void ValidateToolbarItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * Custom validation for given action.
     *
     * @param Reference to custom validation action to be carried.
     */
    void CustomValidateL( CVtUiCmdCustomValidationActionBase& aAction );

private:

    /**
     * Constructor
     */
    CVtUiCommandPolicyManager( const CVtUiCommandManager& aCmdManager );

    /**
     * 2nd constructor
     */
    void ConstructL();

    /**
     * Called when RegisterCommandContext() succeeds.
     */
    void CommandContextRegistered( CVtUiCmdContext& aContext );

    /**
     * Called when UnregisterCommandContext() succeeds.
     */
    void CommandContextUnregistered( CVtUiCmdContext& aContext );

    /**
     * Called when AddValidator() succeeds.
     */
    void ValidatorAdded( CVtUiCmdValidatorBase& aValidator );

    /**
     * Called when RemoveValidator() succeeds.
     */
    void ValidatorRemoved( CVtUiCmdValidatorBase& aValidator );

    /**
     * Returns command context by type.
     */
    CVtUiCmdContext* FindCommandContextByType(
        TVtUiCmdContextType aContextType );

    /**
     * Called from different validation routines.
     */
    void ValidateL( TVtUiCmdContextType aContextType,
        CVtUiCmdValidationActionBase& aAction );

private: // data

    // Context list (ordered by context type)
    RPointerArray< CVtUiCmdContext > iContexts;

    // Validator list
    RPointerArray< CVtUiCmdValidatorBase > iValidators;

    // Reference to command manager
    const CVtUiCommandManager& iCommandManager;

    // Primary command policy, always exists.
    CVtUiPrimaryCmdPolicy* iPrimaryCommandPolicy;

    };

#endif // C_VTUICOMMANDPOLICYMANAGER_H

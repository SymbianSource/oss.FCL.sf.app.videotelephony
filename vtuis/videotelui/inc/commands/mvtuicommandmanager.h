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
* Description:  Command manager API definition.
*
*/


#ifndef M_VTUICOMMANDMANAGER_H
#define M_VTUICOMMANDMANAGER_H

#include <e32base.h>

class CEikMenuPane;
class CVtUiCmdContext;
class CVtUiCmdValidatorBase;
class CVtUiCmdValidationActionBase;
class MVtUiCommandUi;
class CVtUiCommandModifyBase;
class CVtUiCmdCustomValidationActionBase;
class CVtUiCmdBase;

/**
 *  MVtUiCommandManager
 *
 *  Command manager API for other components. Command manager holds command UI
 *  instances and does command validation for all registered commands.
 *
 *  @since S60 v3.2
 */
class MVtUiCommandManager
    {

public:

    /**
     * Adds new command ui to command manager.
     * @param aCommandUi Reference to command ui to be added.
     * @return KErrNone if command ui was added successfully.
     */
    virtual TInt AddCommandUi( MVtUiCommandUi& aCommandUi ) = 0;

    /**
     * Removes command ui from command manager.
     * @param aCommandUi Constant reference to command ui to be removed.
     *
     */
    virtual void RemoveCommandUi( MVtUiCommandUi& aCommandUi ) = 0;

    /**
     * Validate menu items in given manu pane.
     *
     * @param aAction Reference to action to be carried on all menu commands.
     */
    virtual void ValidateMenuItemsL(
        CVtUiCmdValidationActionBase& aAction ) = 0;

    /**
     * Validate softkeys.
     *
     * @param aAction Reference to action to be carried on all softkeys.
     */
    virtual void ValidateSoftkeyItemsL(
        CVtUiCmdValidationActionBase& aAction ) = 0;

    /**
     * Validate toolbar buttons.
     *
     * @param aAction Reference to action to be carried on all toolbar commands.
     */
    virtual void ValidateToolbarItemsL(
        CVtUiCmdValidationActionBase& aAction ) = 0;

    /**
     * Validate command.
     *
     * @param aCommandId Id of command that is being checked.
     * @return ETrue if command can be executed, EFalse otherwise.
     */
    virtual TBool IsCommandAllowedL( TInt aCommandId ) = 0;

    /**
     * Registers command context.
     *
     * @param aContext Reference to command context to be registered.
     * @return KErrNone if registration succeeded.
     */
    virtual TInt RegisterCommandContext( CVtUiCmdContext& aContext ) = 0;

    /**
     * Unregisters command context.
     *
     * @param aContext Reference to command context to be unregistered.
     */
    virtual void UnregisterCommandContext( CVtUiCmdContext& aContext ) = 0;

    /**
     * Adds validator to policy manager and registered contexts.
     *
     * @param aValidator Reference to validator to be added.
     * @return KErrNone if registration succeeded.
     */
    virtual TInt AddValidator( CVtUiCmdValidatorBase& aValidator ) = 0;

    /**
     * Removes validator from policy manager and registered contexts.
     *
     * @param aValidator Constant reference to validator to be removed.
     */
    virtual void RemoveValidator( CVtUiCmdValidatorBase& aValidator ) = 0;

    /**
     * Refresh command uis.
     */
    virtual void RefreshL() = 0;

    /**
     * Add new command modifier.
     *
     * @param aModifier Reference to command modifier to be added to every
     * registered command setting.
     * @return KErrNone if modifier could be added, KErrAlreadyExists if same
     * modifier is already added or KErrArgument if another modifier with
     * same priority is already added.
     */
    virtual TInt AddCommandModifier( CVtUiCommandModifyBase& aModifier ) = 0;

    /**
     * Remove command modifier.
     *
     * @param aModifier Reference to command modifier to be removed from every
     * registered command setting.
     */
    virtual void RemoveCommandModifier( CVtUiCommandModifyBase& aModifier ) = 0;

    /**
     * Registers new command to command manager.
     *
     * @param aCommand Reference to command to be registered.
     */
    virtual void RegisterCommandL( CVtUiCmdBase& aCommand ) = 0;

    /**
     * Unregisters command from command manager.
     *
     * @param aCommand Constant reference to command to be unregistered.
     */
    virtual void UnregisterCommand( const CVtUiCmdBase& aCommand ) = 0;

    };

#endif // M_VTUICOMMANDMANAGER_H

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
* Description:  Command manager class definition.
*
*/


#ifndef C_VTUICOMMANDMANAGER_H
#define C_VTUICOMMANDMANAGER_H

#include "mvtuicommandmanager.h"
#include "mvtuicommandui.h"
#include "tvtuilocalvariation.h"
#include "CVtUiAppUi.h"

class TVtUiStates;
class CVtUiCommandPolicyManager;
class CVtUiPrimaryCmdPolicy;
class CVtUiCmdStateCheckAction;
class CVtUiExecutionContext;

/**
 * CVtUiCommandManager
 *
 * Acts as a proxy for Command UIs and Validators.
 *
 * @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCommandManager ) : public CBase,
    public MVtUiCommandManager, public MVtUiCommandUi
    {

public:

    /**
    * Static constructor.
    *
    * @param aUiStates Constant reference to UI states object.
    */
    static CVtUiCommandManager* NewL( const TVtUiStates& aUiStates,
        CVtUiAppUi& aAppUi );

    /**
    * Destructor.
    */
    ~CVtUiCommandManager();

public:

    /**
     * Constant reference to UI states.
     *
     * @return Constant reference to UI states object.
     */
    const TVtUiStates& UiStates() const;

    /**
     * Constant reference to VT local variation.
     *
     * @return Constant reference to VT local variation object.
     */
    const TVtUiVideoTelephonyVariation& VideoTelephonyVariation() const;

    /**
     * Handles command.
     *
     * @param aCommandId Id of command to be handled. If given command is not
     * found, command will be silently ignored.
     */
    void HandleCommandL( TInt aCommandId );

    /**
     * Constant reference to CVtUiAppUi states.
     *
     * @return Constant reference to UI states object.
     */
    const CVtUiAppUi& AppUi() const;
    

public: // from MVtUiCommandManager

    /**
     * @see MVtUiCommandManager::AddCommandUi
     */
    TInt AddCommandUi( MVtUiCommandUi& aCommandUi );

    /**
     * @see MVtUiCommandManager::RemoveCommandUi
     */
    void RemoveCommandUi( MVtUiCommandUi& aCommandUi );

    /**
     * @see MVtUiCommandManager::ValidateMenuItemsL
     */
    void ValidateMenuItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * @see MVtUiCommandManager::ValidateSoftkeyItemsL
     */
    void ValidateSoftkeyItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * @see MVtUiCommandManager::ValidateToolbarItemsL
     */
    void ValidateToolbarItemsL( CVtUiCmdValidationActionBase& aAction );

    /**
     * @see MVtUiCommandManager::IsCommandAllowedL
     */
    TBool IsCommandAllowedL( TInt aCommandId );

    /**
     * @see MVtUiCommandManager::RegisterCommandContext
     */
    TInt RegisterCommandContext( CVtUiCmdContext& aContext );

    /**
     * @see MVtUiCommandManager::UnregisterCommandContext
     */
    void UnregisterCommandContext( CVtUiCmdContext& aContext );

    /**
     * @see MVtUiCommandManager::AddValidator
     */
    TInt AddValidator( CVtUiCmdValidatorBase& aValidator );

    /**
     * @see MVtUiCommandManager::RemoveValidator
     */
    void RemoveValidator( CVtUiCmdValidatorBase& aValidator );

    /**
     * @see MVtUiCommandManager::RefreshL
     */
    void RefreshL();

    /**
     * @see MVtUiCommandManager::AddCommandModifier
     */
    TInt AddCommandModifier( CVtUiCommandModifyBase& aModifier );

    /**
     * @see MVtUiCommandManager::RemoveCommandModifier
     */
    void RemoveCommandModifier( CVtUiCommandModifyBase& aModifier );

    /**
     * @see MVtUiCommandManager::RegisterCommandL
     */
    void RegisterCommandL( CVtUiCmdBase& aCommand );

    /**
     * @see MVtUiCommandManager::UnregisterCommand
     */
    void UnregisterCommand( const CVtUiCmdBase& aCommand );

private:

    /**
    * Constructor.
    */
    CVtUiCommandManager( const TVtUiStates& aUiStates, CVtUiAppUi& aAppUi );

    /**
    * Symbian OS constructor.
    * @param aModel Engine model.
    */
    void ConstructL();

    /**
     * Called when a new command modifier is added
     */
    TInt CommandModifierAdded( CVtUiCommandModifyBase& aModifier );

    /**
     * Called when a command modifier is removed
     */
    void CommandModifierRemoved( CVtUiCommandModifyBase& aModifier );

    /**
     * Called when a new command ui is added
     */
    TInt CommandUiAdded( MVtUiCommandUi& aCommandUi );

    /**
     * Called when a command ui is removed
     */
    void CommandUiRemoved( MVtUiCommandUi& aCommandUi );

private:

    // Commands Uis
    RPointerArray< MVtUiCommandUi > iCommandUis;

    // Command modifiers
    RPointerArray< CVtUiCommandModifyBase > iCommandModifiers;

    // Registered commands
    RPointerArray< CVtUiCmdBase > iCommands;

    // Command policy manager instance
    CVtUiCommandPolicyManager* iCmdPolicyMgr;

    // Reference to UI states instance
    const TVtUiStates& iUiStates;

    // Reference to VT local variation
    TVtUiVideoTelephonyVariation iVtVariation;

    // Command state validation action
    CVtUiCmdStateCheckAction* iCmdStateCheckAction;

    // Execution context (for command state validation)
    CVtUiExecutionContext* iExecutionContext;

    // Reference to appui
    const CVtUiAppUi& iAppUi;
    };

#endif // C_VTUICOMMANDMANAGER_H

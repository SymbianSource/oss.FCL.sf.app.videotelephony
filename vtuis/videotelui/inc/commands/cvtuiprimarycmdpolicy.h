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
* Description:  Primary command policy class definition.
*
*/


#ifndef C_VTUIPRIMARYCMDPOLICY_H
#define C_VTUIPRIMARYCMDPOLICY_H

#include <e32base.h>

#include "tvtuicmdpolicypriority.h"
#include "cvtuicmdvalidatorbase.h"
#include "tvtuilocalvariation.h"

class CVtUiCmdValidationActionBase;
class TVtUiStates;
class CVtUiAppUi;
/**
 * CVtUiPrimaryCmdPolicy
 *
 * Primary policy is the highest priority policy. It does the basic validation,
 * results of which can be modified by the lower priority validators.
 *
 * @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiPrimaryCmdPolicy ) : public CVtUiCmdValidatorBase
    {

public: // public methods

    /**
     * Static constructor.
     *
     * @param aUiStates Constant reference to UI states object.
     * @return Newly created instace of CVtUiPrimaryCmdPolicy class.
     */
    static CVtUiPrimaryCmdPolicy* NewL( const TVtUiStates& aUiStates, 
        const CVtUiAppUi& aAppUi );

    /**
     * Destructor
     */
    ~CVtUiPrimaryCmdPolicy();

public: // from CVtUiCmdValidatorBase

    /**
     * @see CVtUiCmdValidatorBase::ValidateMenuItemsL
     */
    void ValidateMenuItemsL( CVtUiCmdValidationActionBase& aAction,
        TInt aReferencePriority );

    /**
     * @see CVtUiCmdValidatorBase::ValidateSoftkeyItemsL
     */
    void ValidateSoftkeyItemsL( CVtUiCmdValidationActionBase& aAction,
        TInt aReferencePriority );

    /**
     * @see CVtUiCmdValidatorBase::ValidateToolbarItemsL
     */
    void ValidateToolbarItemsL( CVtUiCmdValidationActionBase& aAction,
        TInt aReferencePriority );

    /**
     * @see CVtUiCmdValidatorBase::CustomValidationL
     */
    void CustomValidationL( CVtUiCmdCustomValidationActionBase& aAction,
        TInt aReferencePriority );

    /**
     * @see CVtUiCmdValidatorBase::ValidatesContext
     */
    TBool ValidatesContext( const TVtUiCmdContextType& aCtxType )
        const;

private:

    /**
     * C++ constructor
     */
    CVtUiPrimaryCmdPolicy( const TVtUiStates& aUiStates, 
        const CVtUiAppUi& aAppUi );

    /**
     * 2nd constructor
     */
    void ConstructL();

    /**
     * Callback for menu validation.
     */
    TBool ValidateMenuCommand( TInt aCommandId ) const;

    /**
     * Callback for softkey resource id validation.
     */
    TBool ValidateSoftkey( TInt aResourceId ) const;

    /**
     * Callback for toolbar command validation.
     */
    TBool ValidateToolbarCommand( TInt aCommandId ) const;

    /**
     * Callback for command state validation.
     */
    TBool ValidateCommandState( TInt aCommandId ) const;

    /**
     * Callback for command validation.
     */
    TBool ValidateCommand( TInt aCommandId, TBool& aHandled ) const;

private: // data

    // UI states
    const TVtUiStates& iUiStates;

    // Active idle local variation    
    TBool iAIEnabled;
    
    // Reference to appui
    const CVtUiAppUi& iAppUi;

    };

#endif // C_VTUIPRIMARYCMDPOLICY_H

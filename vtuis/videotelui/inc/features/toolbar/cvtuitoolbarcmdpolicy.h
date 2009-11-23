/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Toolbar command policy implementation.
*
*/


#ifndef C_VTUITOOLBARCMDPOLICY_H
#define C_VTUITOOLBARCMDPOLICY_H

#include <e32base.h>

#include "tvtuicmdpolicypriority.h"
#include "cvtuicmdvalidatorbase.h"

class CVtUiCmdValidationActionBase;
class CVtUiToolbarBase;

/**
*  CVtUiToolbarCmdPolicy
*
*  Toolbar command policy implementation.
*
*  @since S60 v3.2
*/
class CVtUiToolbarCmdPolicy : public CVtUiCmdValidatorBase
    {
    public: // public methods

        /**
        * Static constructor.
        * @param aToolbar Reference to toolbar.
        */
        static CVtUiToolbarCmdPolicy* NewL( CVtUiToolbarBase& aToolbar );

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
        *
        */
        CVtUiToolbarCmdPolicy( CVtUiToolbarBase& aToolbar );

        /**
        * Callback for menu validation.
        *
        */
        TBool ValidateMenuCommand( TInt aCommandId ) const;

    private: // data

        // Reference to cvtuitoolbar
        CVtUiToolbarBase& iToolbar;
        
    };

#endif // C_VTUITOOLBARCMDPOLICY_H

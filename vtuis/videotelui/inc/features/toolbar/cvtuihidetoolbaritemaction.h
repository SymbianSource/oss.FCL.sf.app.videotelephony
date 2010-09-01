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
* Description:  Toolbar hide item action class definition.
*
*/


#ifndef C_VTUIHIDETOLLBARITEMACTION_H
#define C_VTUIHIDETOLLBARITEMACTION_H

#include    <e32base.h>
#include    "cvtuicmdvalidationactionbase.h"
#include    "tvtuistates.h"

class CVtUiToolbarBase;

/**
*  CVtUiHideToolbarItemAction
*
*  Toolbar hide item action definition.
*
*  @since S60 v3.2
*/
class CVtUiHideToolbarItemAction : public CVtUiCmdValidationActionBase
    {
    public:

        /**
        * Leave-safe constructor.
        * @param aToolbar Pointer to toolbar.
        * @param aUiStates Reference to uistates.
        */
        static CVtUiHideToolbarItemAction* NewL( CVtUiToolbarBase* aToolbar,
               const TVtUiStates& aUiStates );
         
        /**
        * Destructor
        *
        */
        ~CVtUiHideToolbarItemAction();

    public: // from CVtUiCmdValidationActionBase

        /**
        * @See CVtUiCmdValidationActionBase::ProcessL
        */
        void ProcessL( const MVtUiCmdValidatorCallBack& aCallBack );

        
         /**
         * @See CVtUiCmdValidationActionBase::EndProcess
         */
         virtual void EndProcess();
        
    private:

        /**
        * C++ constructor.
        *
        */
        CVtUiHideToolbarItemAction( CVtUiToolbarBase* aToolbar,
            const TVtUiStates& aUiStates );

        /**
        * Sets given toolbar control hidden in toolbar.
        *
        */
        void SetItemHiddenL( TInt aCommandId );
        
        /**
        * Decides if toolbar control should be dimmed or shown.
        *
        */
        void HideOrShowToolbarControlL( TInt aCommandId );

    private: // data

        // Toolbar instance this action is currently working on
        CVtUiToolbarBase* iToolbar;
        
        // Reference to UI states instance
        const TVtUiStates& iUiStates;
        };

#endif // C_VTUIHIDETOLLBARITEMACTION_H

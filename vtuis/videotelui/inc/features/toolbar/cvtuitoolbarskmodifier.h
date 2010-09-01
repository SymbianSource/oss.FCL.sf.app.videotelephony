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
* Description:  Toolbar softkey modifier class definition.
*
*/


#ifndef C_VTUITOOLBARSKMODIFIER_H
#define C_VTUITOOLBARSKMODIFIER_H

#include <e32base.h>
#include "cvtuicommandmodifybase.h"

class   CVtUiAppUi;
class   TVtUiStates;

/**
*  CVtUiToolbarSKModifier
*
* Toolbar softkey modifier class definition.
*
*  @since S60 v3.2
*/
class CVtUiToolbarSKModifier : public CVtUiCommandModifyBase
    {
    public: // static methods
        /**
        * Static constructor.
        * @param aAppUi Reference to command appui.
        * @param aUiStates Reference to uistates.
        */
        static CVtUiToolbarSKModifier* NewL( CVtUiAppUi& aAppUi,
                const TVtUiStates& aUiStates );

        /**
        * Destructor
        */
        ~CVtUiToolbarSKModifier();

    public: // from base class

        /**
        * @See CVtUiCommandModifyBase::ModifyCommandsL
        */
        virtual void ModifyCommandsL( MVtUiCommandSetting& aCommandSettings );

       /**
        * @See CVtUiCommandModifyBase::Supports
        */
        virtual TBool Supports( MVtUiCommandSetting::Type aType ) const;

    private:
        /**
         * C++ constructor
         *
         */
        CVtUiToolbarSKModifier( CVtUiAppUi& aAppUi,
                const TVtUiStates& aUiStates );

        /**
         * 2nd constructor
         */
        void ConstructL();

    private: // data

        // refrence to appui
        CVtUiAppUi& iAppUi;

        // UI states
        const TVtUiStates& iUiStates;

    };

#endif // C_VTUITOOLBARSKMODIFIER_H

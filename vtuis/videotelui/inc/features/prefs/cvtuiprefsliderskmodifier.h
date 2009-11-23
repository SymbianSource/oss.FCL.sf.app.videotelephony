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
* Description:  Video preference slider softkey modifier class definition.
*
*/


#ifndef C_VTUIPREFSLIDERMODIFIER_H
#define C_VTUIPREFSLIDERMODIFIER_H

#include <e32base.h>
#include "cvtuicommandmodifybase.h"

class   CVtUiAppUi;

/**
*  CVtUiPrefSliderSKModifier
*
* Video preference slider softkey modifier class definition.
*
*  @since S60 v3.2
*/
class CVtUiPrefSliderSKModifier : public CVtUiCommandModifyBase
    {
    public: // static methods
        /**
        * Static constructor.
        * @param aAppUi Reference to command appui.
        * @param aResourceId Reference resource id.
        */
        static CVtUiPrefSliderSKModifier* NewL( CVtUiAppUi& aAppUi,
            TInt aResourceId );

        /**
        * Destructor
        */
        ~CVtUiPrefSliderSKModifier();

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
        CVtUiPrefSliderSKModifier( CVtUiAppUi& aAppUi, TInt aResourceId  );

        /**
         * 2nd constructor
         */
        void ConstructL();

    private: // data

        // refrence to appui
        CVtUiAppUi& iAppUi;
        
        // softkey resource id
        TInt iResourceId;

    };

#endif // C_VTUIPREFSLIDERMODIFIER_H

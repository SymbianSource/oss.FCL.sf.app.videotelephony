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
* Description:  Toolbar context class definition.
*
*/


#ifndef C_VTUITOOLBARCONTEXT_H
#define C_VTUITOOLBARCONTEXT_H

#include <e32base.h>

#include "cvtuicmdcontext.h"

class CVtUiCmdValidatorBase;

/** Toolbar context reference priority */
const TInt KVtUiToolbarContextPriority = 50;

/**
*  CVtUiToolbarContext
*
*  Toolbar context class definition.
*
*  @since S60 v3.2
*/
class  CVtUiToolbarContext : public CVtUiCmdContext
    {
    public: // public methods

        /**
         * C++ destructor.
         *
         */
        ~CVtUiToolbarContext();

        /**
        * Leave safe destructor.
        * @param aCommandManager Reference to command manager.
        */
        static CVtUiToolbarContext* NewL(
            MVtUiCommandManager& aCommandManager );

    public: // from CVtUiCmdContext

        /**
        *  @see CVtUiCmdContext::ValidateL
        */
        void ValidateL( CVtUiCmdValidationActionBase& aAction );

    private:

        /**
        * C++ constructor
        *
        * @param aCommandManager Reference to command manager.
        */
        CVtUiToolbarContext( MVtUiCommandManager& aCommandManager );

        /**
         * 2nd consttuctor, may leave.
         */
        void ConstructL();
        
    };

#endif // C_VTUITOOLBARCONTEXT_H

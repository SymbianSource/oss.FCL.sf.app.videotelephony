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
* Description:  Dialer feature softkey modifier class.
*
*/


#ifndef C_VTUIDIALERSKMODIFIER_H
#define C_VTUIDIALERSKMODIFIER_H

//  INCLUDES
#include <e32base.h>
#include "cvtuicommandmodifybase.h"

// FORWARD DECLARATIONS
class   CVtUiFeatureManager;

/**
 *  CVtUiDialerSKModifier
 *
 *  Modifies softkeys for dialer control.
 *
 *  @since S60 v5.0
 */
class CVtUiDialerSKModifier : public CVtUiCommandModifyBase
    {

public: // static methods
    /**
     * Static constructor.
     *
     */
    static CVtUiDialerSKModifier* NewL( CVtUiFeatureManager& aFeatureMgr );

    /**
     * Destructor
     */
    ~CVtUiDialerSKModifier();

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
    CVtUiDialerSKModifier( CVtUiFeatureManager& aFeatureMgr );

private: // data

    // refrence to appui
    CVtUiFeatureManager& iFeatureMgr;

    };

#endif // C_VTUIDIALERSKMODIFIER_H

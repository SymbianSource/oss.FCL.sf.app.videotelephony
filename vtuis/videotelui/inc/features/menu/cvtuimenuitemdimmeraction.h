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
* Description:  Menu dimmer action class definition.
*
*/


#ifndef C_VTUIMENUITEMDIMMERACTION_H
#define C_VTUIMENUITEMDIMMERACTION_H

#include <e32base.h>

#include "cvtuicmdvalidationactionbase.h"

class CEikMenuPane;

/**
 *  CVtUiCmdValidationActionBase
 *
 *  Menu item dimmer action definition.
 *
 *  @since S60 v3.2
 */
class CVtUiMenuItemDimmerAction : public CVtUiCmdValidationActionBase
    {

public:

    /**
     * Leave-safe constructor.
     *
     */
    static CVtUiMenuItemDimmerAction* NewL();

    /**
     * Sets menu pane instance.
     *
     */
    void SetMenuPane( CEikMenuPane* aMenuPane );

public: // from CVtUiCmdValidationActionBase

    /**
     * @see CVtUiCmdValidationActionBase::ProcessL
     */
    void ProcessL( const MVtUiCmdValidatorCallBack& aCallBack );

    /**
     * @see CVtUiCmdValidationActionBase::EndProcess
     */
    void EndProcess();

private:

    /**
     * C++ constructor.
     *
     */
    CVtUiMenuItemDimmerAction();

    /**
     * Sets given menu command dimmed in menu.
     *
     */
    void SetItemDimmed( TInt aCommandId );

private: // data

    // Menu pane instance this action is currently working on
    CEikMenuPane* iMenuPane;

    };

#endif // C_VTUIMENUITEMDIMMERACTION_H

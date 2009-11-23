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
* Description:  Command iterator API definition.
*
*/


#ifndef M_VTUICOMMANDSETTING_H
#define M_VTUICOMMANDSETTING_H

#include <e32base.h>

/**
 *  MVtUiCommandSetting
 *
 *  Command Setting API.
 *
 *  @since S60 v3.2
 */
class MVtUiCommandSetting
    {

public:

    /**
     * Command types.
     */
    enum Type
        {
        /** Softkeys */
        ECommandTypeSoftkeys
        };

public: // pure virtual methods

    /**
     * Does the base command definition. If no modifiers are registered, then
     * this method is called from DefineCommandsL(), otherwise this method may
     * be called by the modifier, but it is not required to do so.
     */
    virtual void DoDefineCommandsL() = 0;

    };


#endif // M_VTUICOMMANDSETTING_H

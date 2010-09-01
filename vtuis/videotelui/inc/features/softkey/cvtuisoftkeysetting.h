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
* Description:  Softkey settings class definition.
*
*/


#ifndef C_VTUISOFTKEYSETTING_H
#define C_VTUISOFTKEYSETTING_H

#include "cvtuicommandsetting.h"

class CVtUiSoftkeys;
class CVtUiSoftkeyValidationAction;

/**
 *  CVtUiSoftkeySetting
 *
 *  Softkey setting class definition.
 *
 *  @since S60 v3.2
 */
class CVtUiSoftkeySetting :
    public CVtUiCommandSetting< CVtUiSoftkeyValidationAction >
    {

public:

    /**
     * Constructor
     * @param aSoftkeys Reference to softkeysr.
     */
    CVtUiSoftkeySetting( CVtUiSoftkeys& aSoftkeys );

    /**
     * Destructor
     */
    ~CVtUiSoftkeySetting();

public: // from CVtUiCommandSetting

    /**
     * @see CVtUiCommandSetting::DoDefineCommandsL
     */
    void DoDefineCommandsL();

private:

    // Softkey container
    CVtUiSoftkeys* iSoftkeys;

    };

#endif // C_VTUISOFTKEYSETTING_H

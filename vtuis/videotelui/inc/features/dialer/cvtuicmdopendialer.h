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
* Description:  Dialer open command.
*
*/


#ifndef C_VTUICMDOPENDIALER_H
#define C_VTUICMDOPENDIALER_H

#include "cvtuifeaturecmdbase.h"

class MVtUiCommandManager;

/**
 *  CVtUiCmdOpenDialer
 *
 *  @since S60 v5.0
 */
class CVtUiCmdOpenDialer : public CVtUiFeatureCmdBase
    {

public:

    /**
     * Static constructor
     *
     * @param aCommandManager Reference to command manager.
     * @param aFeature Reference to minidialer feature.
     * @return Newly created instance to CVtUiCmdOpenDialer.
     */
    static CVtUiCmdOpenDialer* NewL( MVtUiCommandManager& aCommandManager,
        MVtUiFeature& aFeature );

    /**
     * Destructor
     */
    ~CVtUiCmdOpenDialer();

private:

    /**
     * Constructor
     */
    CVtUiCmdOpenDialer( MVtUiCommandManager& aCommandManager,
        MVtUiFeature& aFeature );

    /**
     * 2nd constructor
     */
     void ConstructL();

private:

    // Reference to command manager API.
    MVtUiCommandManager& iCommandManager;

    };

#endif // C_VTUICMDOPENDIALER_H

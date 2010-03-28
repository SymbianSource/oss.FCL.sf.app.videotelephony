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
* Description:  Dialer close command.
*
*/


#ifndef C_VTUICMDCLOSEDIALER_H
#define C_VTUICMDCLOSEDIALER_H

#include "cvtuifeaturecmdbase.h"

class MVtUiCommandManager;

/**
 *  CVtUiCmdCloseDialer
 *
 *  @since S60 v5.0
 */
class CVtUiCmdCloseDialer : public CVtUiFeatureCmdBase
    {

public:

    /**
     * Static constructor
     *
     * @param aCommandManager Reference to command manager.
     * @param aFeature Reference to minidialer feature.
     * @return Newly created instance to CVtUiCmdCloseDialer.
     */
    static CVtUiCmdCloseDialer* NewL( MVtUiCommandManager& aCommandManager,
        MVtUiFeature& aFeature );

    /**
     * Destructor
     */
    ~CVtUiCmdCloseDialer();

private: // from CVtUiFeatureCmdBase

    /**
     * @see CVtUiFeatureCmdBase::HandleL
     */
    void HandleL();

    /**
    * @see CVtUiFeatureCmdBase::IsEnabled
    */
    TBool IsEnabled() const;

private:

    /**
     * Constructor
     */
    CVtUiCmdCloseDialer( MVtUiCommandManager& aCommandManager,
        MVtUiFeature& aFeature );

    /**
     * 2nd constructor
     */
     void ConstructL();

private:

    // Reference to command manager API.
    MVtUiCommandManager& iCommandManager;

    };

#endif // C_VTUICMDCLOSEDIALER_H

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
* Description:  Feature based UI command base class definition.
*
*/


#ifndef C_VTUIFEATURECMDBASE_H
#define C_VTUIFEATURECMDBASE_H

#include "cvtuicmdbase.h"

class MVtUiFeature;

/**
 *  CVtUiCmdBase
 *
 *  Base class for all UI commands that are feature based.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiFeatureCmdBase ) : public CVtUiCmdBase
    {

public: // from CVtUiCmdBase

    /**
     * @see CVtUiCmdBase::HandleL
     */
    void HandleL();

    /**
     * @see CVtUiCmdBase::IsEnabled
     */
    TBool IsEnabled() const;

protected:

    /**
     * C++ constructor.
     *
     * @aFeature Reference to a feature this command refers to.
     * @aCommandId Id of this command.
     *
     */
    CVtUiFeatureCmdBase( MVtUiFeature& aFeature, TInt aCommandId );

protected:

    // Reference to command feature
    MVtUiFeature& iFeature;

    };

#endif // C_VTUIFEATURECMDBASE_H

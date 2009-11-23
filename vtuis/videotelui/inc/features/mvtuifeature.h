/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Observer interface for handling features
*
*/


#ifndef MVTUIFEATURE_H
#define MVTUIFEATURE_H

//  INCLUDES
#include <e32std.h>

#include "tvtuifeatureids.h"

// CLASS DECLARATION

/**
*  Interface for handling features
*
*  @since S60 v3.2
*/
class MVtUiFeature
    {
    public:  // New functions
        /**
        * ENotSupported
        *  feature is not supported in current configuration.
        * EUnprepared
        *   starting may require some init code to run.
        * EPreparing
        *   running initialization code.
        * EReady
        *   feature can be started.
        * EActive
        *   feature is running.
        * EDisabled
        *   feature is supported but cannot be started at this time.
        * EFailed
        *   started but failed (maybe temporary or permanent, feature specific)
        */
        enum TVtUiFeatureState
            {
            ENotSupported,
            EUnprepared,
            EPreparing,
            EReady,
            EActive,
            EDisabled,
            EFailed
            };

        /**
        * Starts the feature.
        */
        virtual void StartL() = 0;

        /**
        * Stops the feature.
        */
        virtual void Stop() = 0;

        /**
        * Current state of the feature
        */
        virtual TVtUiFeatureState State() const = 0;

        /**
        * Id()
        */
        virtual TVtUiFeatureId Id() const = 0;
    };

#endif // MVTUIFEATURE_H
// End of File

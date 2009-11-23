/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Command manager class for Video Telephone application.
*
*/



#ifndef MVTUICOMMANDMANAGER_H
#define MVTUICOMMANDMANAGER_H

//  INCLUDES
#include    <e32base.h>

// FORWARD DECLARATIONS
class MVtEngCommandObserver;

// CLASS DECLARATION

/**
*  Command manager class for Video Telephone application.
*
*  @since Series 60 2.6
*/
class MVtUiEngineCommandManager
    {
    public: // New functions

        /**
        * Adds observer.
        * @param aObserver observer to be added.
        */
        virtual void AddObserverL( MVtEngCommandObserver& aObserver ) = 0;

        /**
        * Removes observer.
        * @param aObserver observer to be removed.
        */
        virtual void RemoveObserver( MVtEngCommandObserver& aObserver ) = 0;

    };

#endif      // MVTUICOMMANDMANAGER_H

// End of File

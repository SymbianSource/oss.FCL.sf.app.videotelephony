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
* Description:  Resource change observer API definition.
*
*/


#ifndef M_VTUIRESOURCECHANGEOBSERVER_H
#define M_VTUIRESOURCECHANGEOBSERVER_H

#include <e32def.h>

/**
 *  MVtUiResourceChangeObserver
 *
 *  Resource change observer API definition.
 *
 *  @since S60 v3.2
 */
class MVtUiResourceChangeObserver
    {

public:

    /**
     * Called when resources have been changed.
     *
     * @param aType The type of resources that have changed.
     */
    virtual void HandleResourceChangeL( TInt aType ) = 0;

    };

#endif // M_VTUIRESOURCECHANGEOBSERVER_H

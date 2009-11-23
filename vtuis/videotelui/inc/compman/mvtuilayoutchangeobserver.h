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
* Description:  Layout change observer API definition.
*
*/


#ifndef M_VTUILAYOUTCHANGEOBSERVER_H
#define M_VTUILAYOUTCHANGEOBSERVER_H

#include <e32def.h>

/**
 *  MVtUiLayoutChangeObserver
 *
 *  Layout change observer API definition.
 *
 *  @since S60 v3.2
 */
class MVtUiLayoutChangeObserver
    {

public:

    /**
     * Called when layout have been changed.
     *
     */
    virtual void HandleLayoutChangeL() = 0;

    };

#endif // M_VTUIRESOURCECHANGEOBSERVER_H

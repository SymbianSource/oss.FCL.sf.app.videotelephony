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
* Description:  Key event observer API for components.
*
*/


#ifndef M_VTUINUMBERENTRYCONTROLOBSERVER_H
#define M_VTUINUMBERENTRYCONTROLOBSERVER_H

/**
* MVtUiNumberEntryControlObserver
*
* Observer API for number entry control.
*
* @since S60 v3.2
*/
class MVtUiNumberEntryControlObserver
    {

public:

    /**
     * Called when number entry control is activated.
     */
    virtual void ControlActivatedL() = 0;

    /**
     * Called when number entry control is deactivated.
     */
    virtual void ControlDeactivated() = 0;

    };

#endif // M_VTUINUMBERENTRYCONTROLOBSERVER_H

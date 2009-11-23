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


#ifndef M_VTUIKEYEVENTOBSERVER_H
#define M_VTUIKEYEVENTOBSERVER_H

#include <w32std.h>
#include <coedef.h>

/**
 *  MVtUiKeyEventObserver
 *
 *  Keyevent observer API definition.
 *
 *  @since S60 v3.2
 */
class MVtUiKeyEventObserver
    {

public:

    /**
     * Called when key event handling is required.
     *
     * @param aEvent The key event.
     * @param aCode The type of key event: EEventKey, EEventKeyUp or
     * EEventKeyDown.
     * @return Indicates whether or not the key event was used.
     */
    virtual TKeyResponse OfferKeyEventL( const TKeyEvent& aEvent,
        TEventCode aCode ) = 0;

    };

#endif // M_VTUIKEYEVENTOBSERVER_H

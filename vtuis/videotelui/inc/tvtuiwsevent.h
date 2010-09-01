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
* Description:  VT UI window server event definition.
*
*/


#ifndef T_VTUIWSEVENT_H
#define T_VTUIWSEVENT_H

#include <w32std.h>

/**
 * TVtUiWsEvent
 *
 * VT UI WS event code enumerations. Name 'code' used instead of 'type' to keep
 * naming consistent with with window server.
 */
enum TVtUiWsEventCodes
    {
    // New number source activated
    EVtUiWsEventNumberSourceActivate = EEventUser + 6000,
    // Number source deactivated
    EVtUiWsEventNumberSourceDeactivate,
    // Enter rendering mode
    EVtUiWsEventBeginRenderingMode,
    // Leave rendering mode
    EVtUiWsEventEndRenderingMode
    };

/**
 *  TVtUiWsEvent
 *
 *  Base class for VT UI ws events
 *
 *  @since S60 v3.2
 */
template < class T >
class TVtUiWsEvent : public TWsEvent
    {

public:

    /**
     * Constructor
     *
     * @param aType Event type @see TVtUiWsEventCodes.
     */
    inline TVtUiWsEvent( TInt aType, T* aData );

    /**
     * Return data contained in this event.
     */
    inline T* Data() const;

    };

#include "tvtuiwsevent.inl"

#endif // T_VTUIWSEVENT_H

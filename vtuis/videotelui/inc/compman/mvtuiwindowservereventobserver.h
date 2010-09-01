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
* Description:  Window Server event observer API definition.
*
*/


#ifndef M_VTUIWINDOWSERVEREVENTOBSERVER_H
#define M_VTUIWINDOWSERVEREVENTOBSERVER_H

class TWsEvent;
class CCoeControl;

/**
 *  MVtUiWindowServerEventObserver
 *
 *  Window Server event observer API definition.
 *
 *  @since S60 v3.2
 */
class MVtUiWindowServerEventObserver
    {

public:

    /**
     * Called when window server event handling is required.
     *
     * @param aEvent A window server event.
     * @param aDestination The control associated with the event.
     * This is only relevant for pointer events.
     */
    virtual void HandleWsEventL( const TWsEvent& aEvent,
        CCoeControl* aDestination ) = 0;

    };

#endif // M_VTUIWINDOWSERVEREVENTOBSERVER_H

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
* Description:  VT UI Component manager API definition.
*
*/


#ifndef M_VTUICOMPONENTMANAGER_H
#define M_VTUICOMPONENTMANAGER_H

#include <e32base.h>

#include "mvtuicomponent.h"

class TVtUiComponentState;
class MVtUiWindowServerEventObserver;
class MVtUiResourceChangeObserver;
class MVtUiKeyEventObserver;
class MVtUiLayoutChangeObserver;

/**
 *  MVtUiComponentManager
 *
 *  Component manager API definition.
 *
 *  @since S60 v3.2
 */
class MVtUiComponentManager
    {

public: // enumerations

    /**
     * Registration action.
     */
    enum TAction
        {
        /** Register action */
        ERegister,

        /** Unregister action */
        EUnregister
        };

public: // public methods

    /**
     * Register or unregister Ws event listening.
     *
     * @param aComponent Observer whose registration will be changed.
     * @param aAction Registration action
     * @see MVtUiComponentManager::TAction
     * @return KErrNone if registration action succeeded.
     */
    virtual TInt ChangeWsEventRegistration(
        MVtUiWindowServerEventObserver& aComponent,
        TAction aAction ) = 0;

    /**
     * Register or unregister resource change event listening.
     *
     * @param aComponent Observer whose registration will be changed.
     * @param aAction Registration action
     * @see MVtUiComponentManager::TAction
     * @return KErrNone if registration action succeeded.
     */
    virtual TInt ChangeResourceChangeRegistration(
        MVtUiResourceChangeObserver& aComponent,
        TAction aAction ) = 0;

    /**
     * Register or unregister key event listening.
     *
     * @param aComponent Observer whose registration will be changed.
     * @param aAction Registration action
     * @see MVtUiComponentManager::TAction
     * @return KErrNone if registration action succeeded.
     */
    virtual TInt ChangeKeyEventRegistration( MVtUiKeyEventObserver& aComponent,
        TAction aAction ) = 0;

    /**
     * Register or unregister layout change listening.
     *
     * @param aComponent Observer whose registration will be changed.
     * @param aAction Registration action
     * @see MVtUiComponentManager::TAction
     * @return KErrNone if registration action succeeded.
     */
    virtual TInt ChangeLayoutChangeRegistration( MVtUiLayoutChangeObserver& aComponent,
        TAction aAction ) = 0;

    /**
     * Register or unregister component.
     *
     * @param aComponent Observer whose registration will be changed.
     * @param aAction Registration action
     * @see MVtUiComponentManager::TAction
     * @return KErrNone if registration action succeeded.
     */
    virtual TInt ChangeComponentRegistration( TVtUiComponentState& aComponent,
        TAction aAction ) = 0;

    /**
     * Request component activation.
     *
     * @param aId Id of component to be activated.
     */
    virtual void RequestActivationL( MVtUiComponent::TComponentId aId ) = 0;

    /**
     * Deactivate component.
     *
     * @param aId Id of component to be deactivated.
     */
    virtual void DeActivateComponentL( MVtUiComponent::TComponentId aId ) = 0;

    };

#endif // M_VTUICOMPONENTMANAGER_H

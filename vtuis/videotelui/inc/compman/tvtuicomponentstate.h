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
* Description:  VT UI component state definition.
*
*/


#ifndef T_VTUICOMPONENTSTATE_H
#define T_VTUICOMPONENTSTATE_H

#include <e32base.h>

#include "tvtuiblocklists.h"

/**
 *  TVtUiComponentState
 *
 *  Component state definition.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiComponentState )
    {

public: // enumerations

    enum TState
        {
        /** Component is inactive */
        EInactive,

        /** Component is activated but some other component is blocking it */
        EWaiting,

        /** Component is active */
        EActive
        };

public: // public methods

    /**
     * Activate component.
     */
    void ActivateComponentL();

    /**
     * Blocks component.
     */
    void BlockComponentL();

    /**
     * Deactivates component.
     */
    void DeActivateComponentL();

    /**
     * Returns component's state.
     *
     * @return Component's current state.
     */
    TState State() const;

    /**
     * Returns component.
     *
     * @return Constant reference to component.
     */
    const MVtUiComponent& Component() const;

    /**
     * Returns const reference to the block list.
     *
     * @return Constant reference to component's block list.
     */
    const TVtUiBlockList& BlockList() const;

    /**
     * Returns reference to the block list.
     *
     * @return Reference to component's block list.
     */
    TVtUiBlockList& BlockList();

protected: // protected methods

    /**
     * Constructor
     *
     * @param aComponent Component for this state instance.
     * @param aBlockList Block list for this state intance.
     */
    TVtUiComponentState( MVtUiComponent& aComponent,
        const TVtUiBlockList& aBlockList );

protected:

    // Reference to component
    MVtUiComponent& iComponent;

    // Blocklist
    TVtUiBlockListBitField iBlockList;

    // Component's state
    TState iState;

    };

#endif // T_VTUICOMPONENTSTATE_H

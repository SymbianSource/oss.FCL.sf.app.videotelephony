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
* Description:  Command UI API definition.
*
*/


#ifndef M_VTUICOMMANDUI_H
#define M_VTUICOMMANDUI_H

#include <e32base.h>

class CVtUiCommandModifyBase;

/**
 *  MVtUiCommandUi
 *
 *  Command UI API. Defines methods for adding/removing command modifiers and
 *  method to refresh related command UI.
 *
 *  @since S60 v3.2
 */
class MVtUiCommandUi
    {

public:

    /**
     * Refresh command ui.
     */
    virtual void RefreshL() = 0;

    /**
     * Add new command modifier.
     *
     * @param aModifier Reference to modifier to be added to this command ui.
     * @return KErrNone if modifier could be added, KErrAlreadyExists if same
     * modifier is already added or KErrArgument if another modifier with
     * same priority is already added.
     */
    virtual TInt AddCommandModifier( CVtUiCommandModifyBase& aModifier ) = 0;

    /**
     * Remove command modifier.
     *
     * @param aModifier Reference to modifier to be removed from this command
     * ui.
     */
    virtual void RemoveCommandModifier( CVtUiCommandModifyBase& aModifier ) = 0;

    };

#endif // M_VTUICOMMANDUI_H

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
* Description:  Command modifier priorities.
*
*/


#ifndef VTUICOMMANDMODIFIERPRIORITIES_H
#define VTUICOMMANDMODIFIERPRIORITIES_H

/**
 * Enumerates Modifier priorities
 *
 * @since S60 3.2
 */
enum TVtUiCmdModifierPriority
    {
    /** Undefined priority value */
    EVtUiCmdModifierPriorityUndefined = 0,

    /** Lowest possible priority */
    EVtUiCmdModifierPriorityLowest = 1,

    /** Menu Modifier priority */
    EVtUiCmdModifierPriorityToolbar = 100,

    /** Menu Modifier priority */
    EVtUiCmdModifierPriorityNumberEntry = 101,

    /** Highest possible priority */
    EVtUiCmdModifierPriorityHighest = 500,
    };

#endif      // VTUICOMMANDMODIFIERPRIORITIES_H

// End of File

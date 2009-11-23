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
* Description:  Command context types.
*
*/


#ifndef T_VTUICMDCONTEXTTYPE_H
#define T_VTUICMDCONTEXTTYPE_H

/**
 * Command context types
 *
 * @since S60 3.2
 */
enum TVtUiCmdContextType
    {
    /** Context type not defined yet */
    EVtUiCmdContextTypeUndefined = 0,

    /** Context type menu */
    EVtUiCmdContextTypeMenu,

    /** Context type softkey */
    EVtUiCmdContextTypeSoftkey,

    /** Context type toolbar */
    EVtUiCmdContextTypeToolbar,

    /** Context type execution */
    EVtUiCmdContextTypeExecution,

    /** Context type number entry */
    EVtUiCmdContextTypeNumberEntry

    };

#endif // T_VTUICMDCONTEXTTYPE_H

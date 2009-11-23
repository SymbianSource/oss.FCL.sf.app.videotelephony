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
* Description:  Command policy priorities.
*
*/


#ifndef T_VTUICMDPOLICYPRIORITY_H
#define T_VTUICMDPOLICYPRIORITY_H

/**
 * Command priority enumeration
 *
 * @since S60 3.2
 */
enum TVtUiCmdPolicyPriority
    {
    /** Undefined priority value */
    EVtUiCmdPolicyPriorityUndefined = 0,

    /** Lowest possible priority */
    EVtUiCmdPolicyPriorityLowest = 1,

    /** Number entry policy priority */
    EVtUiCmdPolicyPriorityNumberEntry,

    /** Menu policy priority */
    EVtUiCmdPolicyPriorityMenu = 100,

    /** Softkey policy priority */
    EVtUiCmdPolicyPrioritySoftkey = 200,

    /** Toolbar policy priority */
    EVtUiCmdPolicyPriorityToolbar = 300,

    /** Primary policy priority, must be highest */
    EVtUiCmdPolicyPriorityPrimary,

    /** Highest possible priority */
    EVtUiCmdPolicyPriorityHighest = EVtUiCmdPolicyPriorityPrimary

    };

#endif // T_VTUICMDPOLICYPRIORITY_H

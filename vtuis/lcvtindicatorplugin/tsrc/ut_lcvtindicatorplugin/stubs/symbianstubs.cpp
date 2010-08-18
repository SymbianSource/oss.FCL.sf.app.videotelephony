/*
* Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  HbMenu2 implementation.
*
*/


#include "symbianstubs_helper.h"
#include <apgtask.h>
#include <w32std.h>
#include <qglobal.h>

bool testVtTaskExists = false;

void SymbianStubHelper::reset()
{
    testVtTaskExists = false;
}

void SymbianStubHelper::setVtTaskExists(bool exists)
{
    testVtTaskExists = exists;
}


///////////////////////////////////////////////

TApaTask TApaTaskList::FindApp(TUid aAppUid)
{
    Q_UNUSED(aAppUid)
    RWsSession session;
    return TApaTask(session);
}


TBool TApaTask::Exists() const
{
    return testVtTaskExists;
}

void TApaTask::BringToForeground()
{
    
}

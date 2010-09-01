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
* Description:  Observer API for CVtUiTransparentSettingPage.
*
*/


#ifndef M_VTUISETTINGPAGEOBSERVER_H
#define M_VTUISETTINGPAGEOBSERVER_H

/**
* MVtUiSettingPageObserver
*
* Observer API for CVtUiTransparentSettingPage.
*
* @since S60 v3.2
*/
class MVtUiSettingPageObserver
    {

public:

    /**
    * Called when EEventStateChanged event occurs 
    * in setting page.
    */
    virtual void ListStateChangedL() = 0;

    };

#endif // M_VTUISETTINGPAGEOBSERVER_H
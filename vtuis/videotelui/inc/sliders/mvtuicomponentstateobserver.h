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
* Description:  Observer API for popup based controls
*
*/


#ifndef M_VTUICOMPONENTSTATEOBSERVER_H
#define M_VTUICOMPONENTSTATEOBSERVER_H

/**
* MVtUiComponentStateObserver
*
* Observer API for popup based controls
*
* @since S60 v3.2
*/
class MVtUiComponentStateObserver
    {

public:

    /**
    * Called when component state changes
    */
    virtual void ComponenStateChangedL() = 0;

    };

#endif // M_VTUICOMPONENTSTATEOBSERVER_H
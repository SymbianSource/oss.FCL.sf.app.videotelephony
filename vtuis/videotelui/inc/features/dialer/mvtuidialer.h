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
* Description:  Dialer API for VT application.
*
*/


#ifndef M_VTUIDIALER_H
#define M_VTUIDIALER_H

class MVtUiVideoWindow;
class CCoeControl;

/**
 *  MVtUiDialer
 *
 *  Mini dialer UI feature API for AppUi.
 *
 *  @since S60 v5.0
 */
class MVtUiDialer
    {

public:

    /**
    * Get reference to video window control
    * @return Reference to video window.
    */
    virtual MVtUiVideoWindow& VideoWindow() const = 0;

    /**
    * Get reference to video window control
    * @return Reference to video control.
    */
    virtual CCoeControl& VideoControl() const = 0;

    };

#endif //

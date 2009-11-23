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
* Description:  Number Source API
*
*/


#ifndef M_VTUINUMBERSOURCE_H
#define M_VTUINUMBERSOURCE_H

#include <e32base.h>

/**
 *  MVtUiNumberSource
 *
 *  @since S60 v3.2
 */
class MVtUiNumberSource
    {

public:

    /**
     * Gets number typed by the user.
     *
     */
    virtual void GetContents( TDes& aContents ) const = 0;

    };

#endif // M_VTUINUMBERSOURCE_H

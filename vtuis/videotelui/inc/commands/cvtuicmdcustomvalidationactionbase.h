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
* Description:  Custom command validation action class definition.
*
*/


#ifndef C_VTUICMDCUSTOMVALIDATIONACTIONBASE_H
#define C_VTUICMDCUSTOMVALIDATIONACTIONBASE_H

#include <e32base.h>

#include "cvtuicmdvalidationactionbase.h"

/**
 *  CVtUiCmdCustomValidationActionBase
 *
 *  Custom command validation action base class. This class is an extension to
 *  command validation action and defines new attribute Type ID that is used
 *  for defining type of the custom validation action.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiCmdCustomValidationActionBase )
    : public CVtUiCmdValidationActionBase
    {

public: // typedefs

    // Custom type id type definition.
    typedef TInt TCustomTypeId;

public:

    /**
     * Returns custom type id.
     * @return Custom type id.
     */
    TCustomTypeId CustomTypeId() const;

protected: // new protected methods

    /**
     * C++ constructor.
     */
    CVtUiCmdCustomValidationActionBase( TCustomTypeId aCustomTypeId );

private: // data

    // Custom type id.
    const TCustomTypeId iCustomTypeId;

    };

#endif // C_VTUICMDCUSTOMVALIDATIONACTIONBASE_H

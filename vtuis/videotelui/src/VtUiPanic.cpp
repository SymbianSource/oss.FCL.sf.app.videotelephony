/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the VtUiPanic class.
*
*/



// INCLUDE FILES
#include    "VtUiPanic.h"

// CONSTANTS

// Panic category for Video Telephone application.
_LIT( KVtUiPanicCategory, "Videotelui" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// VtUiPanic::Panic
// -----------------------------------------------------------------------------
//
void VtUiPanic::Panic( TVtUiPanicReason aReason )
    {
    User::Panic( KVtUiPanicCategory, aReason );
    }

//  End of File

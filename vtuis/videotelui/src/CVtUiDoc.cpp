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
* Description:  Implementation of the CVtUiDoc document class.
*
*/



// INCLUDE FILES
#include    "CVtUiDoc.h"
#include    "CVtUiAppUi.h"
#include    <apgwgnam.h>

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiDoc::CVtUiDoc
// C++ constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiDoc::CVtUiDoc( CEikApplication& aApp )
    : CAknDocument( aApp )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiDoc::CreateAppUiL
// Creates application UI instance.
// -----------------------------------------------------------------------------
//
CEikAppUi* CVtUiDoc::CreateAppUiL()
    {
    return new ( ELeave ) CVtUiAppUi;
    }

// -----------------------------------------------------------------------------
// CVtUiDoc::UpdateTaskNameL
// Creates application UI instance.
// -----------------------------------------------------------------------------
//
void CVtUiDoc::UpdateTaskNameL( CApaWindowGroupName* aWgName )
    {
    CAknDocument::UpdateTaskNameL( aWgName );
    aWgName->SetHidden( ETrue );
    }

//  End of File  

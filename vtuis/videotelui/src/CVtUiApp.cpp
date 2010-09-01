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
* Description:  Implementation of the CVtUiApp application class.
*
*/



// INCLUDE FILES
#include    "CVtUiApp.h"
#include    "CVtUiDoc.h"
#include    "videotelui.hrh"

#include    <eikstart.h>

// CONSTANTS

// UID of Video Telephone application.
const TUid KVtUiAppUid = { KVtUiAppUidValue };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiApp::CVtUiApp
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CVtUiApp::CVtUiApp()
    {
    }

// -----------------------------------------------------------------------------
// CVtUiApp::CreateDocumentL
// Creates CVtUiDoc instance.
// -----------------------------------------------------------------------------
//
CApaDocument* CVtUiApp::CreateDocumentL()
    {
    return new ( ELeave ) CVtUiDoc( *this );
    }

// -----------------------------------------------------------------------------
// CVtUiApp::AppDllUid
// Returns application uid.
// -----------------------------------------------------------------------------
//
TUid CVtUiApp::AppDllUid() const
    {
    return KVtUiAppUid;
    }

// ========================== OTHER EXPORTED FUNCTIONS =========================

// ---------------------------------------------------------
// NewApplication implements
// 
// Creates an instance of application.
//
// Returns: an instance of CVtUiApp
// ---------------------------------------------------------
//
LOCAL_C CApaApplication* NewApplication()
    {
    return new CVtUiApp;
    }

// ---------------------------------------------------------
// E32Main implements
// 
// It is called when executable is started. 
//
// Returns: error code.
// ---------------------------------------------------------
//
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

//  End of File

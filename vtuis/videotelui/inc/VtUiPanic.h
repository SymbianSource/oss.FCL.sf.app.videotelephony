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
* Description:  Panic methods and reasons for Video Telephone application.
*
*/



#ifndef VTUIPANIC_H
#define VTUIPANIC_H

//  INCLUDES
#include    <e32base.h>

// DATA TYPES

/**
* Enumerates all panic reasons.
*/
enum TVtUiPanicReason
    {
    // Invalid index passed to VtUiLayout::Resolve.
    EVtUiPanicInvalidBitmapId = 10,
    // Invalid bitmap file in VtUiLayout::Resolve.
    EVtUiPanicInvalidBitmapFile = 11,
    // Reset must not fail.
    EVtUiPanicResetFailed = 12,
    // Communication not supported.
    EVtUiPanicCommsNotSupported = 13,
    // EIKON server handle not found.
    EVtUiPanicEikonServerNotFound = 14,
    // Prepare view finder not supported.
    EVtUiPanicPrepareViewFinderNotSupported = 15,
    // Prepare remote render not supported.
    EVtUiPanicPrepareRemoteRenderNotSupported = 16,
    // Mismatch in bitmap file names.
    EVtUiPanicMismatchInBitmapFileNames = 17,
    // Default color requirement mismatch.
    EVtUiPanicDefaultColorRequireMismatch = 18,
    // Application shutdown has timeouted.
    EVtUiPanicApplicationShutdownTimeout = 100,
    // Engine functionality does not match with required.
    EVtUiPanicEngineFunctionalityAssert = 101,
    // Renderer instance is not available
    EVtUiPanicRendererNotFound = 200,
    // Values out of range
    EVtUiPanicOutOfRange = 300
    };

// CLASS DECLARATION

/**
*  Panic methods and reasons for Video Telephone application.
*
*  @since Series 60 2.6
*/
class VtUiPanic
    {
    public: // New functions

        /**
        * Panics this process.
        * @param aReason reason of panic.
        */
        static void Panic(
            TVtUiPanicReason aReason );

    };

#endif      // VTUIPANIC_H
            
// End of File

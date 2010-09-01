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
* Description:  Application class for Video Telephone application.
*
*/



#ifndef CVTUIAPP_H
#define CVTUIAPP_H

//  INCLUDES
#include    <aknapp.h>

// CLASS DECLARATION

/**
*  Application class for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiApp 
    : public CAknApplication
    {
    public: // Constructors and destructor

        /**
        * C++ default constructor.
        */
        CVtUiApp();

    public: // Functions from base classes

        /**
        * From CAknApplication, creates document instance.
        * @return document instance.
        */
        virtual CApaDocument* CreateDocumentL();

        /**
        * From CAknApplication, returns UID of the application.
        * @return UID of the application.
        */
        virtual TUid AppDllUid() const;

    };

#endif      // CVTUIAPP_H  

// End of File

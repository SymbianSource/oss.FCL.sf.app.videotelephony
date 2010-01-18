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
* Description:  Document class for Video Telephone application.
*
*/



#ifndef CVTUIDOC_H
#define CVTUIDOC_H

//  INCLUDES
#include    <AknDoc.h>

// CLASS DECLARATION

/**
*  Document class for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiDoc
    : public CAknDocument
    {
    public: // Constructors and destructor
        
        /**
        * C++ constructor.
        * @param aApp application instance.
        */
        CVtUiDoc( CEikApplication& aApp );

    public: // Functions from base classes

        /**
        * From CAknDocument, creates application UI instance.
        * @return application UI instance.
        */
        virtual CEikAppUi* CreateAppUiL();

        /**
        * From CAknDocument, updates task name.
        * @param aWgName window group name instance.
        */
        virtual void UpdateTaskNameL( CApaWindowGroupName* aWgName );

    };

#endif      // CVTUIDOC_H   
            
// End of File

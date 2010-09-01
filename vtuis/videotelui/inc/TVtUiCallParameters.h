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
* Description:  Call parameters class for Video Telephone application.
*
*/



#ifndef TVTUICALLPARAMETERS_H
#define TVTUICALLPARAMETERS_H

//  INCLUDES
#include    <e32base.h>

// CLASS DECLARATION

/**
*  Call parameters for Video Telephone application.
*
*  @since Series 60 2.6
*/
class TVtUiCallParameters
    {
    public: // Constructors and destructor
        
        /**
        * C++ constructor.
        */
        TVtUiCallParameters();

    public: // New functions

        /**
        * Resets parameters.
        */
        void Reset();

        /**
        * Sets audio status.
        * @param aEnabled ETrue if audio enabled, EFalse if disabled.
        */
        void SetAudioStatus( const TBool aEnabled );

        /**
        * Gets audio status.
        * @param aEnabled It will equal to ETrue if audio enabled, 
        *        EFalse if disabled.
        * @return error code, 
        *         KErrNone if audio status has been set,
        *         KErrNotFound if not.
        */
        TInt GetAudioStatus( TBool& aEnabled ) const;

        /**
        * Sets video status.
        * @param aEnabled enabled status.
        */
        void SetVideoStatus( const TBool aEnabled );

        /**
        * Gets video status.
        * @param aEnabled It will equal to ETrue if video enabled, 
        *        EFalse if disabled.
        * @return error code, 
        *         KErrNone if video status has been set,
        *         KErrNotFound if not.
        */
        TInt GetVideoStatus( TBool& aEnabled );

        /**
        * Sets selected camera.
        * @param aPrimary ETrue if primary, EFalse if secondary.
        */
        void SetSelectedCamera( const TBool aPrimary );

        /**
        * Gets selected camera.
        * @param aPrimary It will equal to ETrue if primary has been selected,
        *        EFalse if secondary.
        * @return error code,
        *         KErrNone if selected camera has been set,
        *         KErrNotFound if not.
        */
        TInt GetSelectedCamera( TBool& aPrimary );

    private:

        // Current flags.
        TInt iFlags;

    };

#endif      // TVTUICALLPARAMETERS_H   
            
// End of File

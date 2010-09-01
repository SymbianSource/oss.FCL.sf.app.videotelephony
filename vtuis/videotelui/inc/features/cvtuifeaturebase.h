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
* Description:  CVtUiFeatureBase implementation.
*
*/


#ifndef C_VTUIFEATUREBASE_H
#define C_VTUIFEATUREBASE_H

//  INCLUDES
#include <e32base.h>
#include "mvtuifeature.h"

// CLASS DECLARATION
class CVtUiAppUi;
class CVtUiFeatureManager;

/**
*   Base class for Video Telephone application features.
*
*  @since S60 3.2
*/
class CVtUiFeatureBase : public CBase, public MVtUiFeature
    {
    public: // public methods
        /**
        * C++ destructor.
        */
        ~CVtUiFeatureBase();
 
    public: // from MVtUiFeature

        /** @see MVtUiFeature */
        virtual void StartL();

        /** @see MVtUiFeature */
        virtual void Stop() = 0;
        
        /** @see MVtUiFeature */
        virtual void InitFeatureL() = 0;
        
        /** @see MVtUiFeature */
        TVtUiFeatureState State() const;
        
        /** @see MVtUiFeature */
        TVtUiFeatureId Id() const;

    protected:
        /**
        * C++ constructor
        *
        */
        CVtUiFeatureBase( TVtUiFeatureId aId,
            CVtUiFeatureManager& aFeatureManager );

        /**
        * BaseConstructL
        * For child class to use.
        * Calls constructL. 
        */
        void BaseConstructL();

        /**
        * Callback function that inits the features.
        * @param aAny pointer to an instance of the class.
        * @return always KErrNone.
        */
        static TInt DoInitFeaturesL( TAny* aAny );
    

    protected: // data
        
        // Feature's unique Id
        const TVtUiFeatureId iId;
        
        // Reference to featuremanager
        CVtUiFeatureManager& iFeatureManager;
                
        // Features current state
        MVtUiFeature::TVtUiFeatureState iFeatureState;
    
        // Owned asynch callback.
        CAsyncCallBack* iAsyncCallback;
        
    };

#endif // C_VTUIFEATUREBASE_H
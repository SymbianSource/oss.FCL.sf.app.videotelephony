/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Feature manager for Video Telephone application.
*
*/


#ifndef C_VTUIFEATUREMANAGER_H
#define C_VTUIFEATUREMANAGER_H

//  INCLUDES
#include    <e32std.h>
#include    <e32base.h>

// CLASS DECLARATION
class MVtUiFeature;
class CVtUiAppUi;
class CVtUiFeatureBase;
class TVtUiStates;
class MVtUiCommandManager;
class MVtUiComponentManager;
class CVtEngModel;
/**
*  Feature manager for Video Telephone application.
*
*  @since S60 v3.2
*/
class CVtUiFeatureManager : public CBase
    {
    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        */
        static CVtUiFeatureManager* NewL( CVtUiAppUi& aAppUi,
            TVtUiStates& aUiStates, MVtUiCommandManager& aCommandManager,
            MVtUiComponentManager& aComponentManager );

        /**
        * Destructor.
        */
        ~CVtUiFeatureManager();

    public:  // New functions

        /**
        * Return reference to CVtUiAppUi class.
        */
        CVtUiAppUi& AppUi();

        /**
        * GetFeatureById
        */
        MVtUiFeature* GetFeatureById( TInt aId );

        /**
        * TVtUiStates
        */
        TVtUiStates& UiStates();

        /**
        * Command Manager
        */
        MVtUiCommandManager& CommandManager();

        /**
        * Component Manager
        */
        MVtUiComponentManager& ComponentManager();
        
        /**
        *  Return reference to CVtEngModel class.
        */
        CVtEngModel& Model();

 private:

        /**
        * Second phase constructor
        */
        void ConstructL();

        /**
        * c++ constructor
        */
        CVtUiFeatureManager( CVtUiAppUi& aAppUi, TVtUiStates& aUiStates,
            MVtUiCommandManager& aCommandManager,
            MVtUiComponentManager& aComponentManager );

        /**
        * Creates all features
        */
        void CreateFeaturesL();

    private: // data

        // Feature list
        RPointerArray< CVtUiFeatureBase > iFeatures;

        // Ref to application ui.
        CVtUiAppUi& iAppUi;

        // Reference to UI states instance
        TVtUiStates& iUiStates;

         // Reference to command manager API
        MVtUiCommandManager& iCommandManager;

        // Reference to component manager API
        MVtUiComponentManager& iComponentManager;
        
        // Engine model.
        CVtEngModel* iModel;

    };

#endif // C_VTUIFEATUREMANAGER_H
// End of File
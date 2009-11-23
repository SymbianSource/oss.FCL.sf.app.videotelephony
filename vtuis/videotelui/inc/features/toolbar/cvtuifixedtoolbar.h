/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Fixed toolbar UI feature class definition.
*
*/


#ifndef C_VTUIFIXEDTOOLBAR_H
#define C_VTUIFIXEDTOOLBAR_H

#include "cvtuitoolbarbase.h"

/**
* CVtUiFixedToolbar
*
* Toolbar UI feature definition.
*
* @since S60 3.2
*/
class CVtUiFixedToolbar : public CVtUiToolbarBase
    {
    public: // public methods

        /**
        * Static constructor.
        * @param aFeatureManager feature manager.
        */
        static CVtUiFixedToolbar* NewL(CVtUiFeatureManager& aFeatureManager );

        /**
        * C++ destructor.
        */
        ~CVtUiFixedToolbar();

    public: // from CVtUiToolbarBase

        /**
        * @see CVtUiToolbarBase::DoActivateL
        */
        void DoActivateL();

        /**
        * @see CVtUiToolbarBase::DoDeactivateL
        */
        void DoDeactivateL();

        /**
        * @see CVtUiToolbarBase::CreateToolbarButtonsL
        */
        void CreateToolbarButtonsL();

        /**
        * @see CVtUiToolbarBase::PopulateCmdsIdsL
        */
        void PopulateCmdsIdsL();

        /**
        * @see CVtUiToolbarBase::SetToolbarVisibilityAfterLayoutChange
        */
        void SetToolbarVisibilityAfterLayoutChangeL( TBool aVisible );

    private:

        // Hides/shows toolbar
        void MakeToolbarVisible( const TBool aVisible );

        // Dimms/undimms all toolbar buttons
        void DimToolbarbuttons( TBool aIsDimmed );

        // Sets toolbar visible
        static TInt DoShowToolbarL( TAny* aAny );

        // Sets toolbar buttons dimmed
        static TInt DoDimToolbarButtons( TAny* aAny );

    private:

        /**
        * C++ constructor
        */
        CVtUiFixedToolbar( CVtUiFeatureManager& aFeatureManager );

        /**
        * 2nd phase constructor
        */
        void ConstructL();

    private: // data

        // for callback usage
        CIdle* iIdle;
    };

#endif // C_VTUIFIXEDTOOLBAR_H
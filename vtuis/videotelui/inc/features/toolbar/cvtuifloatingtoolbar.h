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
* Description:  Floating toolbar UI feature class definition.
*
*/


#ifndef C_VTUIFLOATINGTOOLBAR_H
#define C_VTUIFLOATINGTOOLBAR_H

#include "cvtuitoolbarbase.h"
#include "mvtuiresourcechangeobserver.h"
#include <aknlayoutscalable_avkon.cdl.h>

/**
* CVtUiFloatingToolbar  
* 
* Toolbar UI feature definition.
*
* @since S60 3.2
*/
class CVtUiFloatingToolbar : public CVtUiToolbarBase,
    public MVtUiResourceChangeObserver
    {
    public: // public methods

        /**
        * Static constructor.
        * @param aFeatureManager feature manager.
        */
        static CVtUiFloatingToolbar* NewL( CVtUiFeatureManager& 
            aFeatureManager );

        /**
        * C++ destructor.
        */
        ~CVtUiFloatingToolbar();
    
       
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

    public: // from MVtUiResourceChangeObserver

        /**
        * @see MVtUiComponent::HandleResourceChangeL
        */
        void HandleResourceChangeL( TInt aType );         
         
    private:

        /**
        * C++ constructor
        */
        CVtUiFloatingToolbar( CVtUiFeatureManager& aFeatureManager );

        /**
        * 2nd phase constructor
        */
        void ConstructL();
    
        /**

        /*
        * Gets rect from layout data.
        */
        TRect RectFromLayout( const TAknWindowComponentLayout&
            aComponentLayout ) const;

        /*
        * Sets toolbar layout.
        */
        void LayoutToolbarL();

        /*
        * Gets variety for layoutdata.
        */
        TInt GetVariety( TBool aIsLandscapeOrientation );
    
    private: // data

    
        
    };

#endif // C_VTUIFLOATINGTOOLBAR_H
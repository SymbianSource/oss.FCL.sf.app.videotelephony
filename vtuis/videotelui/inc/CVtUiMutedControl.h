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
* Description:  Navi pane control for Video Telephone application.
*
*/



#ifndef CVTUIMUTEDCONTROL_H
#define CVTUIMUTEDCONTROL_H

//  INCLUDES
#include    <coecntrl.h>
#include    <AknUtils.h>

// CLASS DECLARATION

/**
*  Navi pane control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiMutedControl
    : public CCoeControl
    {
    public: // Constructors and destructor
        
        /**
        * C++ constructor.
        */
        CVtUiMutedControl();

        /**
        * Symbian constructor.
        */
        void ConstructL();

        /**
        * C++ destructor.
        */
        ~CVtUiMutedControl();

    public: // Functions from base classes

        /**
        * From CCoeControl, handles resource change.
        * @param aType type of change.
        */ 
        virtual void HandleResourceChange(
            TInt aType );

    protected: // Functions from base classes

        /**
        * From CCoeControl, draws the control.
        * @param aRect area to be drawn.
        */
        virtual void Draw( const TRect& aRect ) const;

        /**
        * From CCoeControl, handles size changes.
        */
        virtual void SizeChanged();

        /**
        * From CCoeControl, handles position changes.
        */
        virtual void PositionChanged();

        /**
        * From CCoeControl, returns amount of component controls.
        * @return amount of component controls.
        */
        virtual TInt CountComponentControls() const;

        /**
        * From CCoeControl, returns specified control.
        * @param aIndex index of control.
        * @return control.
        */
        virtual CCoeControl* ComponentControl(
            TInt aIndex ) const;

    private:

        // Owned muted label.
        CEikLabel* iMutedLabel;

    };

#endif      // CVTUIMUTEDCONTROL_H
            
// End of File

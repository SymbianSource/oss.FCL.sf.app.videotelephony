/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Zoom popup definition
*
*/


#ifndef C_VTUIZOOMPOPUP_H
#define C_VTUIZOOMPOPUP_H

#include "tvtuicomponentstate.h"
#include "cvtuipopupbase.h"

class CVtUiFeatureManager;
class MVtEngMedia;

/**
*  CVtUiZoomPopup
*
*  Zoom popup definition.
*
*  @since S60 v3.2
*/
class CVtUiZoomPopup : public CVtUiPopupBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiZoomPopup* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiZoomPopup();

    /**
    * Refresh zoom popup status.
    */
    void RefreshL();

private: // from CVtUiPopupBase

    /**
    * @see CVtUiPopupBase::DoActivateL
    */
    void DoActivateL();

private: // from base class

    /**
    * @see CVtUiPopupBase::OfferKeyEventL
    */
    TKeyResponse OfferKeyEventL( const TKeyEvent& aEvent,
        TEventCode aCode );

    /**
    * @see CVtUiPopupBase::HandleControlEventL
    */
    void HandleControlEventL( CCoeControl* aControl, TCoeEvent aEventType );

private:

    /**
     * Constructor
     */
    CVtUiZoomPopup( CVtUiFeatureManager& aFeatureManager );

    /*
    * 2nd constructor
    */
    void ConstructL();

    /*
    * Updates zoom adjust range according to current active provider.
    */
    void UpdateAdjustRangeL();

    /**
    * Returns current zoom step or KErrNotFound if an error happens.
    */
    TInt CurrentZoomStep() const;

    /**
    * Returns maximum zoom step or KErrNotFound if an error happens.
    */
    TInt MaxZoomStep() const;
    
    void ScaleAndSetZoomFactorL( TInt aValue );

private:

    // Reference to feature manager
    CVtUiFeatureManager& iFeatureManager;

    // Engine media
    MVtEngMedia& iMedia;

    // Current zoom
    TInt iCurrent;

    // Maximum zoom value
    TInt iMax;

    };

#endif // C_VTUIZOOMPOPUP_H

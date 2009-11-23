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
* Description:  Volume popup definition
*
*/


#ifndef C_VTUIVOLUMEPOPUP_H
#define C_VTUIVOLUMEPOPUP_H

#include "tvtuicomponentstate.h"
#include "cvtuipopupbase.h"
#include "mvtengaudio.h"

class CVtUiFeatureManager;
class CVtEngModel;

/**
*  CVtUiVolumePopup
*
*  Volume popup definition.
*
*  @since S60 v3.2
*/
class CVtUiVolumePopup : public CVtUiPopupBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiVolumePopup* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiVolumePopup();

    /**
    * Refresh volume popup status.
    */
    void RefreshL();

    /**
    * Update volume popup and audio routing
    */
    void UpdateVolumeAndRoutingL();

private: // from base class

    /**
    * @see CVtUiPopupBase::DoActivateL
    */
    void DoActivateL();

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
    CVtUiVolumePopup( CVtUiFeatureManager& aFeatureManager );

    /*
    * 2nd constructor
    */
    void ConstructL();

    /**
    * Returns current output volume for given routing.
    */
    TInt OutputVolume( MVtEngAudio::TAudioRoutingState aRouting ) const;
        
    /**
    * Updates volume 
    */   
    void UpdateVolumeL();        

private:

    // Engine model
    CVtEngModel& iModel;

    // Stored audio routing state.
    MVtEngAudio::TAudioRoutingState iAudioRouting;

    // Stored volume
    TInt iVolume;
    
    // Reference to feature manager
    CVtUiFeatureManager& iFeatureManager;

    };

#endif // C_VTUIVOLUMEPOPUP_H

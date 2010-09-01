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
* Description:  Base class for video telephone sliders
*
*/


#ifndef     C_VTUISLIDERBASE_H
#define     C_VTUISLIDERBASE_H

#include    "cvtuifeaturebase.h"
#include    "mvtuicomponent.h"
#include    "mvtuicomponentstateobserver.h"

class CVtUiPopupBase;

/**
*  CVtUiSliderBase
*
*  Base class for vide telephone sliders
*
*  @since S60 v3.2
*/
class CVtUiSliderBase : public CVtUiFeatureBase, public MVtUiComponentStateObserver
    {

public:

    /**
    * Destructor
    */
    ~CVtUiSliderBase();
    
    /**
    * update slider itself
    */
    void UpdateSlider();
    
public: // from MVtUiFeature

    /**
    * @see MVtUiFeature::StartL
    */
    void StartL();

     /**
    * @see MVtUiFeature::Stop
    */
    void Stop();

     /**
    * @see MVtUiFeature::InitFeatureL
    */
    void InitFeatureL();

public: // from MVtUiComponentStateObserver

    /**
    * @see MVtUiComponentStateObserver::ComponenStateChangedL
    */
    virtual void ComponenStateChangedL();
    
    /**
    * @see CVtUiPopupBase::SetPermanenVisibility
    */
    void SetPermanenVisibility( TBool aPermanent );

protected:

    /*
    * Constructor
    */
    CVtUiSliderBase( CVtUiFeatureManager& aFeatureManager,
        TVtUiFeatureId aFeatureId );

    /**
    * 2nd constructor
    */
    void ConstructL();

    /**
    * Sets popup pointer.
    */
    void SetPopup( CVtUiPopupBase* aPopup );

    /**
    * Gets popup reference.
    */
    CVtUiPopupBase& Popup();

    /**
    * Gets popup const reference.
    */
    const CVtUiPopupBase& Popup() const;

private:

    // pop up base
    CVtUiPopupBase* iPopup;

    };

#endif // CVTUIPEFSLIDERBASE_H

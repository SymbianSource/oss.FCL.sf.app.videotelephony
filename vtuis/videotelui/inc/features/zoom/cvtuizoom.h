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
* Description:  Zoom ui feature
*
*/


#ifndef C_VTUIZOOM_H
#define C_VTUIZOOM_H

#include "cvtuisliderbase.h"

/**
*  CVtUiZoom
*
*  Zoom ui feature
*
*  @since S60 v3.2
*/
class CVtUiZoom : public CVtUiSliderBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiZoom* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiZoom();

    /**
    * Refresh zoom popup status.
    */
    void RefreshL();

public: // from CVtUiSliderBase

    /**
    * @see CVtUiSliderBase::StartL
    */
    void StartL();

    /**
    * @see CVtUiSliderBase::Stop
    */
    void Stop();
    
    /**
    * @see CVtUiSliderBase::ComponenStateChangedL
    */
    void ComponenStateChangedL();
    
protected:

    /*
    * Constructor
    */
    CVtUiZoom( CVtUiFeatureManager& aFeatureManager );

    /**
    * 2nd constructor
    */
    void ConstructL();

    };

#endif // C_VTUIZOOM_H

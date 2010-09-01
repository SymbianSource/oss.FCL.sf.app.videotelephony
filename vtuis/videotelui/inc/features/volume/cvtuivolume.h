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
* Description:  Volume ui feature
*
*/


#ifndef C_VTUIVOLUME_H
#define C_VTUIVOLUME_H

#include "cvtuisliderbase.h"

/**
*  CVtUiVolume
*
*  Volume ui feature
*
*  @since S60 v3.2
*/
class CVtUiVolume : public CVtUiSliderBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiVolume* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiVolume();

    /**
    * Refresh volume popup status.
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
    
    /*
    * Return current slider's volume value 
    */
    TInt GetVolumeValue();

protected:

    /*
    * Constructor
    */
    CVtUiVolume( CVtUiFeatureManager& aFeatureManager );

    /**
    * 2nd constructor
    */
    void ConstructL();

    };

#endif // C_VTUIVOLUME_H

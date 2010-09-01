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
* Description:  Brightness ui feature
*
*/


#ifndef     C_VTUIBRIGHTNESS_H
#define     C_VTUIBRIGHTNESS_H

#include    "cvtuiprefsliderbase.h"

/**
*  CVtUiBrightness
*
*  Brightness ui feature
*
*  @since S60 v3.2
*/
class CVtUiBrightness : public CVtUiPrefSliderBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiBrightness* NewL( CVtUiFeatureManager& aFeatureManager );
    
    /**
    * Destructor
    */
    ~CVtUiBrightness();

public: // from CVtUiPrefSliderBase
    
    /** 
    * @see CVtUiPrefSliderBase::StartL
    */
    void StartL();

    /** 
    * @see CVtUiPrefSliderBase::Stop
    */
    void Stop();
    
protected: 

    /*
    * Constructor
    */
    CVtUiBrightness( CVtUiFeatureManager& aFeatureManager );

    /**
    * 2nd constructor
    */
    void ConstructL(); 

    };

#endif // C_VTUIBRIGHTNESS_H

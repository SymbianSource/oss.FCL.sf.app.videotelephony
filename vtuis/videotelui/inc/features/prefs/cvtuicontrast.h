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
* Description:  Contrast ui feature
*
*/


#ifndef     C_VTUICONTRAST_H
#define     C_VTUICONTRAST_H

#include    "cvtuiprefsliderbase.h"


/**
*  CVtUiContrast
*
*  Contrast ui feature
*
*  @since S60 v3.2
*/
class CVtUiContrast : public CVtUiPrefSliderBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiContrast* NewL( CVtUiFeatureManager& aFeatureManager );
    
    /**
    * Destructor
    */
    ~CVtUiContrast();

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
    CVtUiContrast( CVtUiFeatureManager& aFeatureManager );

    /**
    * 2nd constructor
    */
    void ConstructL(); 

    };

#endif // C_VTUICONTRAST_H

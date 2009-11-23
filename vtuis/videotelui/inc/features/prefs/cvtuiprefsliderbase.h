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
* Description:  Base class for video pref sliders
*
*/


#ifndef     CVTUIPREFSLIDERBASE_H
#define     CVTUIPREFSLIDERBASE_H

#include    "cvtuisliderbase.h"

class CVtUiPopupBase;

/**
*  CVtUiPrefSliderBase
*
*  Base class for video pref sliders
*
*  @since S60 v3.2
*/
class CVtUiPrefSliderBase : public CVtUiSliderBase
    {

public:

    /**
    * Destructor
    */
    ~CVtUiPrefSliderBase();

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
    * @see CVtUiSliderBase::InitFeatureL
    */
    void InitFeatureL();

protected: 

    /*
    * Constructor
    */
    CVtUiPrefSliderBase( CVtUiFeatureManager& aFeatureManager,
        TVtUiFeatureId aFeatureId );

    /**
    * 2nd constructor
    */
    void BaseConstructL( ); 
    
    };

#endif // CVTUIPREFSLIDERBASE_H

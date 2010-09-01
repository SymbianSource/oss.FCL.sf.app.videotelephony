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
* Description:  Brightness popup
*
*/


#ifndef C_VTUIBRIGHTNESSPOPUP_H
#define C_VTUIBRIGHTNESSPOPUP_H

#include    "tvtuicomponentstate.h"
#include    "cvtuiprefpopupbase.h"


/**
*  CVtUiBrightnessPopup
*
*  Brightness popup definition.
*
*  @since S60 v3.2
*/
class CVtUiBrightnessPopup : public CVtUiPrefPopupBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiBrightnessPopup* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiBrightnessPopup();

protected: // from CVtUiPrefPopupBase 
    
    // @see CVtUiPrefPopupBase::CurrentValue
    TInt CurrentValue() ;
    
private:

    /**
     * Constructor
     */
    CVtUiBrightnessPopup( CVtUiFeatureManager& aFeatureManager );

    /*
    * 2nd constructor
    */
    void ConstructL();

    };

#endif // C_VTUIBRIGHTNESSPOPUP_H

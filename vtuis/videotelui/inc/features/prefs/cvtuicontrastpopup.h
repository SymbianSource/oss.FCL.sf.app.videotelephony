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
* Description:  Contrast popup
*
*/


#ifndef C_VTUICONTRASTPOPUP_H
#define C_VTUICONTRASTPOPUP_H

#include    "tvtuicomponentstate.h"
#include    "cvtuiprefpopupbase.h"


/**
*  CVtUiContrastPopup
*
*  Contrast popup definition.
*
*  @since S60 v3.2
*/
class CVtUiContrastPopup : public CVtUiPrefPopupBase
    {

public:

    /**
    * Static constructor
    * @param aFeatureManager Reference to feature manager.
    */
    static CVtUiContrastPopup* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
    * Destructor
    */
    ~CVtUiContrastPopup();

protected: // from CVtUiPrefPopupBase 
    
    // @see CVtUiPrefPopupBase::CurrentValue
    TInt CurrentValue();
    
private:

    /**
     * Constructor
     */
    CVtUiContrastPopup( CVtUiFeatureManager& aFeatureManager );

    /*
    * 2nd constructor
    */
    void ConstructL();

    };

#endif // C_VTUICONTRASTPOPUP_H

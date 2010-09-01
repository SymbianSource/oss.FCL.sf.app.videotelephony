/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Softkey UI feature.
*
*/


#ifndef C_VTUISOFTKEYS_H
#define C_VTUISOFTKEYS_H

#include "mvtuicommandui.h"
#include "cvtuifeaturebase.h"

class CEikButtonGroupContainer;
class CVtUiSoftkeySetting;
class CVtUiCommandModifyBase;
class CVtUiSoftkeyValidationAction;
class CVtUiSoftkeyContext;

/**
 *  CVtUiSoftkeys
 *
 *  Sofktey UI feature definition.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiSoftkeys ) : public CVtUiFeatureBase,
    public MVtUiCommandUi
    {

public:

    /**
     * Static constructor
     * @param aFeatureManager Reference to feature manager.
     * @param aButtonGroupContainer Reference to button group container.
     */
    static CVtUiSoftkeys* NewL( CVtUiFeatureManager& aFeatureManager,
        CEikButtonGroupContainer& aButtonGroupContainer );

    /**
     * Destructor
     */
    ~CVtUiSoftkeys();

public:

    /**
     * Returns reference to application button group container.
     */
    CEikButtonGroupContainer& ButtonGroup();

public: // from CVtUiFeatureBase

    /**
    * @see CVtUiFeatureBase::StartL
    */
    void StartL();

    /**
    * @see CVtUiFeatureBase::Stop
    */
    void Stop();

    /**
    * @see CVtUiFeatureBase::InitFeatureL
    */
    void InitFeatureL();

public: // from MVtUiCommandUi

    /**
     * @see MVtUiCommandUi::RefreshL
     */
    void RefreshL();

    /**
     * @see MVtUiCommandUi::AddCommandModifierL
     */
    TInt AddCommandModifier( CVtUiCommandModifyBase& aModifier );

    /**
     * @see MVtUiCommandUi::RemoveCommandModifierL
     */
    void RemoveCommandModifier( CVtUiCommandModifyBase& aModifier );

private:

    /**
     * Constructor
     */
    CVtUiSoftkeys( CVtUiFeatureManager& aFeatureManager,
        CEikButtonGroupContainer& aButtonGroupContainer );

    /**
     * 2nd constructor
     */
    void ConstructL();

private:

    // Softkey container
    CEikButtonGroupContainer& iButtonGroupContainer;

    // Softkey context instance
    CVtUiSoftkeyContext* iSoftkeyCommandContext;

    // Softkey setter
    CVtUiSoftkeySetting* iSoftkeySetting;

    // Softkey validation action instance
    CVtUiSoftkeyValidationAction* iSoftkeyValidationAction;

    };

#endif // C_VTUISOFTKEYS_H

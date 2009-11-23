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
* Description:  Menu UI feature.
*
*/


#ifndef C_VTUIMENUS_H
#define C_VTUIMENUS_H

#include "cvtuifeaturebase.h"
#include "mvtuicommandui.h"

class CVtUiMenuContext;
class CVtUiMenuItemDimmerAction;
class CEikMenuPane;
class CVtUiCommandModifyBase;

/**
 *  CVtUiMenus
 *
 *  Menu feature definition.
 *
 *  @since S60 v3.2
 */
class CVtUiMenus : public CVtUiFeatureBase, public MVtUiCommandUi
    {

public:

    /**
     * Static constructor
     */
    static CVtUiMenus* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
     * Destructor
     */
    ~CVtUiMenus();

public:

    /**
     * Sets menu context.
     */
    void SetMenuPane( CEikMenuPane* aMenuPane );

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
     * @see MVtUiCommandUi::AddCommandModifier
     */
    TInt AddCommandModifier( CVtUiCommandModifyBase& );

    /**
     * @see MVtUiCommandUi::RemoveCommandModifier
     */
    void RemoveCommandModifier( CVtUiCommandModifyBase& );

private:

    /**
     * Constructor
     */
    CVtUiMenus( CVtUiFeatureManager& aFeatureManager );

    /**
     * 2nd constructor
     */
    void ConstructL();

private:

    // Menu context instance
    CVtUiMenuContext* iMenuCommandContext;

    // Menu dimmer action instance
    CVtUiMenuItemDimmerAction* iMenuDimmerAction;

    };

#endif // C_VTUIMENUS_H

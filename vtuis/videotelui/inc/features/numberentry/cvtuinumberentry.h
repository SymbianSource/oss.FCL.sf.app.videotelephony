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
* Description:  Number entry UI feature definition.
*
*/


#ifndef C_VTUINUMBERENTRY_H
#define C_VTUINUMBERENTRY_H

#include "mvtuicommandui.h"
#include "cvtuifeaturebase.h"
#include "mvtuinumberentrycontrolobserver.h"
#include "cvtuifeaturemanager.h"

class CVtUiNumberEntryControl;

/**
 *  CVtUiNumberEntry
 *
 *  NumberEntry UI feature.
 *
 *  @since S60 v3.2
 */
 class CVtUiNumberEntry : public CVtUiFeatureBase,
    public MVtUiNumberEntryControlObserver
    {

public:

    /**
     * Static constructor
     */
    static CVtUiNumberEntry* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
     * Destructor
     */
    ~CVtUiNumberEntry();

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

public: // from MVtUiNumberEntryControlObserver

    /**
     * @see MVtUiNumberEntryControlObserver::ControlActivatedL
     */
    void ControlActivatedL();

    /**
     * @see MVtUiNumberEntryControlObserver::ControlDeactivated
     */
    void ControlDeactivated();

private:

    /**
     * Constructor
     */
    CVtUiNumberEntry( CVtUiFeatureManager& aFeatureManager );

    /**
     * 2nd constructor
     */
    void ConstructL();

    /**
     * Prepares feature
     */
    void PrepareL();

    /**
     * Unprepares feature
     */
     void Unprepare();

    /**
     * Creates number entry control instance
     */
    void CreateNumberEntryControlL();

    /**
     * Deletes number entry control instance
     */
    void DeleteNumberEntryControl();

private:

    // Owned number entry control instance.
    CVtUiNumberEntryControl* iNumberEntryControl;

    };

#endif // C_VTUINUMBERENTRY_H

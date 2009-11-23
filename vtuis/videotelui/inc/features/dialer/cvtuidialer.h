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
* Description:  Dialer UI feature.
*
*/


#ifndef C_VTUIDIALER_H
#define C_VTUIDIALER_H

#include "cvtuifeaturebase.h"
#include "mvtuidialer.h"

class CVtUiFeatureCmdBase;
class CVtUiDialerContainer;

/**
 *  CVtUiDialer
 *
 *  Mini dialer UI feature definition.
 *
 *  @since S60 v5.0
 */
class CVtUiDialer : public CVtUiFeatureBase, public MVtUiDialer
    {

public:

    /**
     * Static constructor
     * @param aFeatureManager Reference to featuremanager.
     * @return Newly created instance to CVtUiDialer.
     */
    static CVtUiDialer* NewL( CVtUiFeatureManager& aFeatureManager );

    /**
     * Destructor
     */
    ~CVtUiDialer();

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

private: // from MVtUiDialer

    /**
    * @see MVtUiDialer::VideoWindow
    */
    MVtUiVideoWindow& VideoWindow() const;

    /**
    * @see MVtUiDialer::VideoControl
    */
    CCoeControl& VideoControl() const;

private:

    /**
     * Constructor
     */
    CVtUiDialer( CVtUiFeatureManager& aFeatureManager );

    /**
     * 2nd constructor
     */
    void ConstructL();

    /**
     * Preapres feature before start.
     */
    void PrepareL();

    /**
     * Unprepares feature after stop.
     */
    void Unprepare();

private:

    // Open command
    CVtUiFeatureCmdBase* iCmdOpen;

    // Open command
    CVtUiFeatureCmdBase* iCmdClose;

    // Dialer container
    CVtUiDialerContainer* iDialerContainer;

    };

#endif // C_VTUIDIALER_H

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
* Description:  Video control.
*
*/


#ifndef C_VTUIDIALERVIDEOCONTROL_H
#define C_VTUIDIALERVIDEOCONTROL_H

#include    "cvtuivideocontrolbase.h"

/**
 *  CVtUiDialerVideoControl
 *
 *  Mini dialer UI feature definition.
 *
 *  @since S60 v5.0
 */
class CVtUiDialerVideoControl : public CVtUiVideoControlBase
    {

public:

    /**
     * Static constructor
     * @param aBitmapManager Reference to bitmap manager.
     * @return Newly created instance of CVtUiDialerVideoControl.
     */
    static CVtUiDialerVideoControl* NewL( CVtUiBitmapManager& aBitmapManager );

    /**
     * Destructor
     */
    ~CVtUiDialerVideoControl();
public:
    /**
    * LayoutRemoteVideo
    */
    void LayoutRemoteVideo();

private:

    /**
     * Constructor
     */
    CVtUiDialerVideoControl( CVtUiBitmapManager& aBitmapManager );

    /**
    * 2nd constructor
    */
    void ConstructL();

private: // from CVtUiVideoControlBase

    /**
    * @see CVtUiVideoControlBase::WaitingTextLayout
    */
    TAknTextLineLayout WaitingTextLayout( TInt aLine );

    };

#endif // C_VTUIDIALERVIDEOCONTROL_H

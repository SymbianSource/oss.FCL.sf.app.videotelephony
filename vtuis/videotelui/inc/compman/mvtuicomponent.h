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
* Description:  VT UI Component API definition.
*
*/


#ifndef M_VTUICOMPONENT_H
#define M_VTUICOMPONENT_H

#include <e32base.h>

class CCoeControl;

/**
 *  MVtUiComponent
 *
 *  UI component API definition.
 *
 *  @since S60 v3.2
 */
class MVtUiComponent
    {

public: // enumerations

    /**
     * Component Ids.
     */
    enum TComponentId
        {
        /** NULL component Id */
        EComponentIdNull =                  0,
        /** Toobar component Id */
        EComponentIdToolbar =               ( 1 << 0 ),
        /** Number entry component Id */
        EComponentIdNumberEntry =           ( 1 << 1 ),
        /** Video quality component id */
        EComponentIdVideoQuality  =         ( 1 << 2 ),
        /** White balance feature id */
        EComponentIdWhiteBalance =          ( 1 << 3 ),
        /** Color tone component id */
        EComponentIdColorTone =             ( 1 << 4 ),
        /** Brightness component id */
        EVComponentIdBrightness =           ( 1 << 5 ),
        /** Contrast component id */
        EVComponentIdContrast =             ( 1 << 6 ),
        /** Dialer component id  */
        EComponentIdDialer =                ( 1 << 7 ),
        /** Volume component id  */
        EComponentIdVolume =                ( 1 << 8 ),
        /** Zoom component id  */
        EComponentIdZoom =                  ( 1 << 9 )
        };

public: // public methods

    /**
     * Returns component id.
     *
     * @return Component's id.
     */
    virtual TComponentId ComponentId() const = 0;

    /**
     * Returns this component as a CCoeControl.
     *
     * @return Component as a pointer to CCoeControl or NULL if this component
     * is not inherited from CCoeControl.
     */
    virtual CCoeControl* ComponentAsControl() = 0;

    /**
     * Activates component.
     */
    virtual void DoActivateL() = 0;

    /**
     * Deactivates component.
     */
    virtual void DoDeactivateL() = 0;

    };

#endif // M_VTUICOMPONENT_H

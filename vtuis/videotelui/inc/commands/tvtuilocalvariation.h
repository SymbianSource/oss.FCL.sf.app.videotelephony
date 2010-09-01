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
* Description:  Video Telephone local variation class definition.
*
*/


#ifndef T_VTUILOCALVARIATION_H
#define T_VTUILOCALVARIATION_H

#include <e32base.h>

#include "tvtflagcontainer.h"

// User selectable Call answer status values
const TInt KAllwaysQuery = 0;
const TInt KAllwaysAllow = 2;
const TInt KNumberOfTbButtons = 6;

/**
 *  TVtUiVariationBase
 *
 *  Base class for local variation classes.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiVariationBase ) : public TVtFlagContainer
    {
public:

     /**
     * Reads variations from central reposityory.
     * and set default value in case error
     */
    virtual void ReadL( const TInt adefault = -1 );

protected:

    /**
     * Returns UID of the repository to be read.
     */
    virtual const TUid& Uid() const = 0;

    /**
     * ID of the key inside repository to be read.
     */
    virtual TUint32 Key() const = 0;

    /**
     * Gets key value.
     */
    virtual TUint32 ReceiveValue() const;

    };

/**
 *  TVtUiVideoTelephonyVariation
 *
 *  Video Telephony variation class. Reads VT local variation flags from the
 *  CenRep and contains methods to query flag states. This class should be
 *  instanced only once and same instance should be passesd as reference to
 *  modules that need this local variation information.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiVideoTelephonyVariation ) : public TVtUiVariationBase
    {

public:

    /**
     * Return whether or not ScalingMethodENearest is set in local variation.
     *
     * @return ETrue if ScalingMethodENearest local variation flag is set,
     * EFalse otherwise.
     */
    inline TBool IsScalingMethodENearest() const;

    /**
     * Return whether or not ScalingMethodEBilinear is set in local variation.
     *
     * @return ETrue if ScalingMethodEBilinear local variation flag is set,
     * EFalse otherwise.
     */
    inline TBool IsScalingMethodEBilinear() const;

    /**
     * Return whether or not EnableBitReversal is set in local variation.
     *
     * @return ETrue if EnableBitReversal local variation flag is set, EFalse
     * otherwise.
     */
    inline TBool IsEnableBitReversal() const;

private: // from TVtUiVariationBase

    /**
     * @see TVtUiVariationBase::Uid
     */
    const TUid& Uid() const;

    /**
     * @see TVtUiVariationBase::Key
     */
    TUint32 Key() const;
    };

/**
 *  TVtUiActiveIdleVariation
 *
 *  Active Idle variation class. Reads AI local variation flags from the
 *  CenRep and contains methods to query flag states. This class should be
 *  instanced only once and same instance should be passesd as reference to
 *  modules that need this local variation information.
  *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiActiveIdleVariation ) : public TVtUiVariationBase
    {

public:
    /**
     * Return whether or not active idle is enabled in local variation.
     *
     * @return ETrue if active idle is enabled in local variation.
     */
    TBool IsActiveIdleEnabled();

private: // from TVtUiVariationBase

    /**
     * @see TVtUiVariationBase::Uid
     */
    const TUid& Uid() const;

    /**
     * @see TVtUiVariationBase::Key
     */
    TUint32 Key() const;

private:
    };

/**
 *  TVtUiGsMuteVariation
 *
 *  General settings (Gs) variation class. Reads GS local variation flags from the
 *  CenRep and contains methods to query flag states and values. This class should be
 *  instanced only once and same instance should be passesd as reference to
 *  modules that need this local variation information.
  *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiGsMuteVariation ) : public TVtUiVariationBase
    {

public:

    /**
     * Returns Gs mute state value from CanRep.
     *
     * @return Gs mute state value.
     */
    TUint32 GsMuteState();

private: // from TVtUiVariationBase

    /**
     * @see TVtUiVariationBase::Uid
     */
    const TUid& Uid() const;

    /**
     * @see TVtUiVariationBase::Key
     */
    TUint32 Key() const;

private:
    };

/**
 *  TVtUiToolbarVariation
 *
 *  Toolbar variation class. Reads TB local variation flags from the
 *  CenRep and contains methods to query flag states and values. This class should be
 *  instanced only once and same instance should be passesd as reference to
 *  modules that need this local variation information.
  *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiToolbarVariation ) : public TVtUiVariationBase
    {

public:
    /**
     * Returns number of toolbar buttons from CanRep.
     *
     * @return number of toolbar buttons.
     */
    TUint32 NumberOfButtons();

private: // from TVtUiVariationBase

    /**
     * @see TVtUiVariationBase::Uid
     */
    const TUid& Uid() const;

    /**
     * @see TVtUiVariationBase::Key
     */
    TUint32 Key() const;

private:
    };


#include "tvtuilocalvariation.inl"

#endif // T_VTUILOCALVARIATION_H

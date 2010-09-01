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
* Description:  Video Telephone feature variation class definition.
*
*/


#ifndef T_VTUIFEATUREVARIATION_H
#define T_VTUIFEATUREVARIATION_H

#include <e32base.h>
#include <featmgr.h>

/**
 *  TVtUiVariationBase
 *
 *  Base class for feature variation classes.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiFeatureVariationBase )
    {

public:

    /**
     * Returns variation feature ID.
     */
    virtual TUint32 FeatureId() const = 0;

protected:

    /**
     * Return whether or not feature is supported by Featuremanager.
     * @return ETrue if feature is supported by Featuremanager.
     */
    virtual TBool IsFeatureSupported( const TUint32 aId) const;

    };

/**
 *  TVtUiHelpVariation
 *
 *  Help variation class. Uses Featuremanager to verify if feture is
 *  supported. This class should be instanced only once and same instance
 *  should be passesd as reference to modules that need this feature variation
 *  information.
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiHelpVariation ) : public TVtUiFeatureVariationBase
    {

public:

    /**
     * Return whether or help variation is supported.
     *
     * @return ETrue if help supported.
     */
    TBool IsHelpSupported() const;

private: // from TVtUiFeatureVariationBase

		TUint32 FeatureId() const;

    };
/**
 *  TVtUiDPVariation
 *
 *  Display Post (DP) variation class. Uses Featuremanager to verify if feture is
 *  supported. This class should be instanced only once and same instance
 *  should be passesd as reference to modules that need this feature variation
 *  information.
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiDPVariation ) : public TVtUiFeatureVariationBase
    {

public:

    /**
     * Return whether or DP variation is supported.
     *
     * @return ETrue if DP supported.
     */
    TBool IsDPSupported() const;

private: // from TVtUiFeatureVariationBase

		TUint32 FeatureId() const;

    };
/**
 *  TVtUiBTVariation
 *
 *  BlueTooth (BT) variation class. Uses Featuremanager to verify if feture is
 *  supported. This class should be instanced only once and same instance
 *  should be passesd as reference to modules that need this feature variation
 *  information.
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiBTVariation ) : public TVtUiFeatureVariationBase
    {

public:

    /**
     * Return whether or BT variation is supported.
     *
     * @return ETrue if BT supported.
     */
    TBool IsBTSupported() const;

private: // from TVtUiFeatureVariationBase

		TUint32 FeatureId() const;

    };
/**
 *  TVtUiSideVolumeKeysVariation
 *
 *  Side volume keys variation class. Uses Featuremanager to verify if feture is
 *  supported. This class should be instanced only once and same instance
 *  should be passesd as reference to modules that need this feature variation
 *  information.
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiSideVolumeKeysVariation ) : public TVtUiFeatureVariationBase
    {

public:

    /**
     * Return whether or Side volume keys variation is supported.
     *
     * @return ETrue if Side volume keys supported.
     */
    TBool IsSideVolumeKeysSupported() const;

private: // from TVtUiFeatureVariationBase

		TUint32 FeatureId() const;

    };
/**
 *  TVtUiActiveIdleFetManVariation
 *
 *  Active Idle feature manager variation class. Uses Featuremanager to verify if feture is
 *  supported. This class should be instanced only once and same instance
 *  should be passesd as reference to modules that need this feature variation
 *  information.
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiActiveIdleFetManVariation ) : public TVtUiFeatureVariationBase
    {

public:

    /**
     * Return whether or Acvtive Idle variation is supported.
     *
     * @return ETrue if Acvtive Idle  supported.
     */
    TBool IsActiveIdleFetManSupported() const;

private: // from TVtUiFeatureVariationBase

		TUint32 FeatureId() const;

    };         
#endif // T_VTUIFEATUREVARIATION_H
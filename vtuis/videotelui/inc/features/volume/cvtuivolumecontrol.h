/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Volume control adjusts engine side volume values.
*
*/



#ifndef CVTUIVOLUMECONTROL_H
#define CVTUIVOLUMECONTROL_H


#include    <e32base.h>
#include    <mvtengcommandobserver.h>
#include    <mvtengaudio.h>

class MVtEngCommandHandler;
class MVtUiEngineCommandManager;
class CVtUiFeatureManager;


/**
*  Volume control adjusts engine side volume values.
*
*  @since Series 60 v5.0
*/
class CVtUiVolumeControl
    : public CBase,
      private MVtEngCommandObserver
    {
    public: // Constructors and destructor

    // Type for volume settings.
    typedef MVtEngAudio::TVtEngOutputVolume TVolume;

    /**
    * Constructor.
    *
    * @param aSelfPtr optional pointer to itself.
    * @param aCommandHandler command handler.
    * @param aAudio audio interface.
    * @param aCommandManager command manager.
    * @param aFeatureManager Reference to feature manager.
    */
    CVtUiVolumeControl(
        MVtEngCommandHandler& aCommandHandler,
        MVtEngAudio& aAudio,
        MVtUiEngineCommandManager& aCommandManager,
        CVtUiFeatureManager& aFeatureManager );

    /*
    * 2nd phase constructor
    */
    void ConstructL();

    /**
    * Destructor.
    */
    ~CVtUiVolumeControl();

public: // New functions

    // Adjust volume to new value
    void AdjustVolumeL( TVolume aVolume );
        
private:

    /**
    * @see MVtEngCommandObserver::HandleVTCommandPerformedL.
    */
    virtual void HandleVTCommandPerformedL(
        TVtEngCommandId aCommand,
        const TInt aError );
    
    // Checks if volume is changed in slider
    TBool IsVolumeChangedL();

private:

    // Reference to command handler.
    MVtEngCommandHandler& iCommandHandler;

    // Reference to audio interface.
    MVtEngAudio& iAudio;

    // Reference to command manager.
    MVtUiEngineCommandManager& iCommandManager;

    // ETrue if command is performed.
    TBool iCommandPerformed;

    // Volume being updated to engine.
    TVolume iVolume;

    // Volume pointer descriptor.
    TPtrC8 iVolumePtr;
    
    // Reference to featuremanager
    CVtUiFeatureManager& iFeatureManager;
    
    // Is control adjusting volume
    TBool iIsActive;
    };

#endif      // CVtUiVolumeControl_H

// End of File

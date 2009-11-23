/*
* Copyright (c) 2004, 2005 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Controller for navi pane for Video Telephone application.
*
*/



#ifndef CVTUINAVIPANE_H
#define CVTUINAVIPANE_H

//  INCLUDES
#include    <e32base.h>
#include    <coedef.h>
#include    <w32std.h>
#include    <coecobs.h>

// FORWARD DECLARATIONS
class CAknNavigationControlContainer;
class CAknNavigationDecorator;
class CVtUiNaviPaneControl;
class CVtUiAppUi;

// CONSTANTS

// Minimum volume.
const TInt KVtUiVolumeMinimum = 0;

// Maximum volume.
const TInt KVtUiVolumeMaximum = 10;

// CLASS DECLARATION

/**
*  Controller for navi pane for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiNaviPane : public CActive
    {
    public: // Constructors and destructor

        /**
        * Two-phased constructor.
        * @param aNaviPane reference to navipane.
        * @param aAppUi application UI.
        */
        static CVtUiNaviPane* NewL(
            CAknNavigationControlContainer& aNaviPane,
            CVtUiAppUi& aAppUi );

        /**
        * C++ destructor.
        */
        ~CVtUiNaviPane();

    public: // New functions

        /**
        * Updates current speaker.
        * @param aLoudspeaker Loudspeaker if ETrue, handset otherwise.
        */
        void SetCurrentSpeaker(
            const TBool aLoudspeaker );

        /**
        * Changes muted status.
        * @param aStatus status.
        */
        void SetMuted(
            const TBool aStatus );

        /**
        * Updates call duration.
        * @param aDuration current duration.
        * @param aEnabled ETrue if call duration enabled.
        */
        void SetCallDuration(
            const TTimeIntervalSeconds& aDuration,
            const TBool aEnabled );

        /**
        * Commits changes. This method should be called after above
        * Set* methods to make sure that display is up to date.
        */
        void CommitL();

        /**
        * Gets speaker volume.
        * @param aLoudspeaker ETrue if loudspeaker, EFalse if handset.
        * @param aValue it will be updated to contain volume of the speaker.
        */
        void GetSpeakerVolume(
            const TBool aLoudspeaker,
            TInt& aValue ) const;

        /**
        * Handles resource changes.
        * @param aType type of change.
        */
        void HandleResourceChange(
            TInt aType );

    protected: // From base classes

        /**
        * Called by CActive when operation needs to be canceled.
        */
        void DoCancel();

        /**
        * Called by CActiveScheduler when operation has been
        * finished.
        */
        void RunL();

    private:

        /**
        * C++ constructor.
        * @param aNaviPane navipane instance.
        * @param aAppUi application UI.
        */
        CVtUiNaviPane(
            CAknNavigationControlContainer& aNaviPane,
            CVtUiAppUi& aAppUi );

        /**
        * Symbian constructor.
        */
        void ConstructL();

        /**
        * Pushes indicators after timeout.
        */
        void PushAfterTimeout();

        /**
        * Pushes new decorator to navi pane replacing the
        * previous one.
        * @param aNew new to replace the old one.
        */
        void PushL( CAknNavigationDecorator* aNew );

        /**
        * Returns indicator that should be used currently.
        * @return indicator to be shown.
        */
        CAknNavigationDecorator* DefaultIndicator() const;

    private:

        // Slider types in navipane
        enum TSliderControlType
                {
                ENone,
                EZoom,      // Zoom control visible
                EVolume     // Volume control visible
                };


        // Holds current slider type
        TSliderControlType iSliderType;

        // Ref to navi pane.
        CAknNavigationControlContainer& iNaviPane;

        // Ref to top navi pane element.
        CAknNavigationDecorator* iCurrent;

        // Owned controller for call duration
        CAknNavigationDecorator* iMainIndicators;

        // Reference to navi pane control.
        CVtUiNaviPaneControl* iNaviPaneControl;

        // Owned muted indicator.
        CAknNavigationDecorator* iMutedIndicator;

        // Owned timer instance.
        RTimer iTimer;

        // ETrue if call duration was enabled.
        TBool iOldCallDurationEnabled;

        // ETrue if call duration is enabled.
        TBool iCallDurationEnabled;

        // ETrue if loudspeaker, EFalse if handset.
        TBool iLoudspeaker;

        // Old microphone status.
        TBool iOldMicrophoneMuted;

        // ETrue if microphone is muted.
        TBool iMicrophoneMuted;

        // Reference to application UI.
        CVtUiAppUi& iAppUi;
    };

#endif      // CVtUiNaviPane_H

// End of File

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
* Description:  Navi pane zoom indicator control for 
*                Video Telephone application.
*
*/



#ifndef CVTUIZOOMCONTROL_H
#define CVTUIZOOMCONTROL_H

//  INCLUDES
#include    <coecntrl.h>
#include    <aknutils.h>
#include    "CVtUiBitmapManager.h"

// CLASS DECLARATION

/**
*  Navi pane zoom indicator control for Video Telephone application.
*
*  @since Series 60 2.6
*/
class CVtUiZoomControl
    : public CCoeControl
    {
    public: // Constructors and destructor
        
        /**
        * C++ constructor.
        * @param aBitmapManager bitmap manager.
        */
        CVtUiZoomControl( CVtUiBitmapManager& aBitmapManager );

        /**
        * Symbian constructor.
        */
        void ConstructL();

        /**
        * C++ destructor.
        */
        ~CVtUiZoomControl();

    public: // New functions

        /**
        * Sets zoom parameters.
        * @param aStepCount amount of steps, 0 if zooming disabled.
        * @param aCurrentStep current step, 0 .. aStepCount.
        */
        void SetZoomParams( 
            const TInt aStepCount, 
            const TInt aCurrentStep );

        /**
        * Commits changes.
        */
        void CommitL();

        /**
        * Returns ETrue if zooming is enabled.
        * @return ETrue if enabled.
        */
        TBool IsZoomEnabled() const;

        /**
        * Gets zoom parameters.
        * @param aStepCount amount of steps, 0 if zooming disabled.
        * @param aCurrentStep current step, 0 .. aStepCount.
        */
        void GetZoomParams(
            TInt& aStepCount,
            TInt& aCurrentStep ) const;

        /**
        * Updates zoom. This method should be called periodically during zooming.
        * @return ETrue if zoom step was updated.
        */
        TBool UpdateZoomL();

        /**
        * Stops zoom. 
        */
        void StopZoom();

    public: // Functions from base classes

        /**
        * From CCoeControl, handles key events.
        * @param aKeyEvent key event.
        * @param aType type of event.
        * @return response indicating if key was consumed.
        */
        virtual TKeyResponse OfferKeyEventL(
            const TKeyEvent& aKeyEvent,
            TEventCode aType );

        /**
        * From CCoeControl, handles resource change.
        * @param aType type of change.
        */ 
        virtual void HandleResourceChange(
            TInt aType );

    protected: // Functions from base classes

        /**
        * From CCoeControl, draws the control.
        * @param aRect area to be drawn.
        */
        virtual void Draw( const TRect& aRect ) const;

        /**
        * From CCoeControl, handles size changes.
        */
        virtual void SizeChanged();

        /**
        * From CCoeControl, handles position changes.
        */
        virtual void PositionChanged();

    private:

        /**
        * Calculates amount of steps to be shown.
        * @param aFullSteps amount of full steps.
        * @param aPartialStep partial steps, 0 .. 255.
        */
        void DetermineSteps(
            TInt& aFullSteps,
            TInt& aPartialStep ) const;

        /**
        * Generates zoom mask bitmap.
        * @param aAreaBitmap maximum bitmap, ownership not transferred.
        * @param aPartial partial amount.
        * @param aRow area row number.
        * @param aRowSize size of the row.
        * @return ETrue if successful, EFalse otherwise.
        */
        TBool GenerateZoomMaskBitmap(
            CFbsBitmap* aMaskBitmap,
            const TInt aPartial,
            const TInt aRow,
            const TSize& aRowSize ) const;

        /**
        * Generates zoom mask bitmap.
        * @param aAreaBitmap maximum bitmap, ownership not transferred.
        * @param aPartial partial amount.
        * @param aRow area row number.
        * @param aRowSize size of the row.
        */
        void DoGenerateZoomMaskBitmap(
            CFbsBitmap* aMaskBitmap,
            const TInt aPartial,
            const TInt aRow,
            const TSize& aRowSize ) const;

        /**
        * Creates bitmaps.
        * @return error code.
        */
        TInt CreateBitmaps();

        /**
        * Creates bitmaps.
        */
        void CreateBitmapsL();

        /**
        * Returns size of the temporary bitmaps.
        * @return size of the temporary bitmaps.
        */
        TSize SizeOfBitmap() const;

        /**
        * Gets position and source rect.
        * @param aPosition it will contain position.
        * @param aSourceRect it will contain source rectangle.
        * @param aZoomStep zoom step.
        */
        void GetPositionAndRect(
            TPoint& aPosition,
            TRect& aSourceRect,
            const TInt aZoomStep ) const;

    private:

        // Inner class.
        class CBitmap;

        // Reference to bitmap manager.
        CVtUiBitmapManager& iBitmapManager;

        // Zoom direction bitmap identifier.
        TVtUiBitmapPoolId iZoomDirId;

        // Zoom area bitmap identifier.
        TVtUiBitmapPoolId iZoomAreaId;

        // Zoom min bitmap identifier.
        TVtUiBitmapPoolId iZoomMinId;

        // Zoom max bitmap identifier.
        TVtUiBitmapPoolId iZoomMaxId;

        // Zoom pane rectangle.
        TRect iZoomPaneRect;

        // Zoom direction layout.
        TAknLayoutRect iZoomDirLayout;

        // Zoom area layout.
        TAknLayoutRect iZoomAreaLayout;

        // Current step, 0 .. iMaxZoomStep.
        TInt iCurrentZoomStep;
        
        // Maximum step.
        TInt iMaxZoomStep;

        // Used partial value used in iZoomMaskBitmap
        // generation.
        mutable TInt iZoomMaskPartial;

        // Used row value used in iZoomMaskBitmap
        // generation.
        mutable TInt iZoomMaskRow;

        // Owned partial soft mask.
        CBitmap* iZoomPartialMask;
        
        // Owned partial shade (soft mask).
        CBitmap* iZoomPartialShade;

        // Owned partial shade mask.
        CBitmap* iZoomPartialShadeMask;

        // Zoom direction +1 or -1. 0 if no
        // zoom ongoing.
        TInt iZoomDirection;

        // Zoom step at the start of zooming.
        TInt iZoomStepStart;

        // Start time of zooming.
        TTime iZoomStartTime;

    };

#endif      // CVTUIZOOMCONTROL_H

// End of File

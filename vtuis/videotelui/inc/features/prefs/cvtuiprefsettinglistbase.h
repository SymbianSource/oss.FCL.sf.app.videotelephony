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
* Description:  Base class for video preference setting list.
*
*/


#ifndef C_VTUIPEFSETTINGLISTBASE_H
#define C_VTUIPEFSETTINGLISTBASE_H

#include    <AknTransparentCameraSettingPage.h>
#include    "mvtuicommandui.h"
#include    "cvtuifeaturebase.h"
#include    "mvtuicomponent.h"
#include    "tvtuicomponentstate.h"
#include    "tvtuifeatureids.h"
#include    "mvtuisettingpageobserver.h"

class CVtUiAppUi;
class CVtUiTransparentSettingPage;
class MVtEngCameraPreferences;

/**
*  CVtUiPrefSettingListBase
*
*  Base class for color tone and white balance
*
*  @since S60 v3.2
*/
class CVtUiPrefSettingListBase : public CVtUiFeatureBase,
    public MAknSettingPageObserver, MVtUiSettingPageObserver
    {

public:

    /**
    * Destructor
    */
    ~CVtUiPrefSettingListBase();
    
    /**
    * has pending settingpange changed cmd cause camera cover switched.
    */
    TBool IsPendingCmd();
    
    /**
    * handle pending settingpange command
    */
    void HandlePendingCmdL();

public: // from MVtUiFeature

    /** 
    * @see MVtUiFeature::Stop 
    */
    virtual void Stop() = 0;
    
    /** 
    * @see MVtUiFeature::InitFeatureL
    */
    virtual void InitFeatureL();

protected: // from MAknSettingPageObserver
    
    /** 
    * @see MAknSettingPageObserver::HandleSettingPageEventL 
    */
    void HandleSettingPageEventL(
        CAknSettingPage* aSettingPage,
        TAknSettingPageEvent aEventType );    

protected: // from MVtUiSettingPageObserver
    
    /** 
    * @see MVtUiSettingPageObserver::ListStateChangedL
    */
    void ListStateChangedL();

protected:
     
     // Gets currently selected list item
     virtual TInt CurrentSelection() = 0;
     
     // Set items to setting page
     virtual void SetItemsL( CDesCArray& aArray ) = 0;
     
     // Gets resource id for selection list
     virtual TInt SettingPageResId() const = 0;
     
     // This function gets called when focus is moved
     // to new item in the settin page list
     virtual void SettingPageItemChangedL( TInt aIndex ) = 0;
     
     // Start function calls this
     void StartSettingPageL();
     
     // Stop function calls this
     void StopSettingPageL();
     
public: // from CCoeControl
    
    /* 
    * @see CCoeControl::SizeChanged
    */
    void SizeChanged();
    
public:  
 
    /** 
    * Updates setting pages background bitmap
    * @param aFrame Bitmap for setting page's backgound.
    */
    void UpdateBackground( CFbsBitmap* aFrame );
    
    /** 
    * Updates setting value
    * E.g disabling video will reset camera settings. and 
    * after enabling video camera setting value needs to be restored.
    */
    void UpdateSettingL();

protected:

    /**
     * Constructor
     */
    CVtUiPrefSettingListBase( CVtUiFeatureManager& aFeatureManager,
        TVtUiFeatureId aFeatureId );

     /**
     * 2nd constructor
     */
    void ConstructL();

    // Reads item from resource and appends it to the array
    void ReadAndAppendItemL( CDesCArray& aItems, TInt aResId );

private:
    
    // Does the initialisation of the setting page
    void CreateSettingPageL();
    
    // Resizes backround bitmap
    void ResizeBackroundBitmapRect( );

protected:    
    
    // Pointer to camera preferences
    MVtEngCameraPreferences* iCameraPref;
    
    // The original value (which was active when the
    // setting page was launched)
    TInt iOriginalSelection;
    
    // Supported color tone or white balance modes
    TUint32 iSupportedModes;
    
    // Contains currenltly supported items in setting page
    RArray< TInt> iActiveItems;
            
     // whether or not has a pending command
     TBool iPendingSettingChangeCmd;

private:
    
    // Owned setting page instance
    CVtUiTransparentSettingPage* iSettingPage;
    
    // Background bitmap for  setting page
    CFbsBitmap* iViewfinderBitmap;

    // Currently focused value 
    TInt iCurrentSelection;
    
    // Position of bitmap's top left corner
    TPoint iBitmapTopLeftCorner;
    
    // Background bitmap's clip rect
    TRect iBitmapClippingRect;
    
    // Reference to appui
    CVtUiAppUi& iAppUi;
    
    // Window priority for context control
    TInt iContextControlWindowPriority;
    
    // Window position for context control
    TInt iContextControlWindowPosition;
    
    // Window priority for context control
    TInt iRemoteVideoControlWindowPriority;
    
    // Window position for context control
    TInt iRemoteVideoControlWindowPosition;
    
    // Window priority for context control
    TInt iEndCallButtonPanePriority;
    
    // Window position for context control
    TInt iEndCallButtonPanePosition;
    };

#endif // CVTUIPEFSETTINGLISTBASE_H

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
* Description:  class for Remote Video Control.
*
*/

#ifndef CVTUIREMOTEVIDEOCONTROL_H_
#define CVTUIREMOTEVIDEOCONTROL_H_

#include    <coecntrl.h>
#include    <aknwseventobserver.h>

class CVtUiVideoControlBase;
class CVtUiAppUi;

/**
 *  CVtUiRemoteVideoControl
 *
 *  Remote Video control.
 *
 *  @since S60 v5.0
 */
class CVtUiRemoteVideoControl : public CCoeControl,
    public MAknWsEventObserver
    {
public:

    /**
    * Static Constructor.
    */
    static CVtUiRemoteVideoControl* NewL(CVtUiAppUi& aAppUi);
    
    RWindow& GetRWindow();

    /**
     * Destructor
     */
    ~CVtUiRemoteVideoControl();    

protected:

    /**
     * Constructor
     */
    CVtUiRemoteVideoControl(CVtUiAppUi& aAppUi);

    /**
     * 2nd constructor
     */
    void ConstructL();
    
public: // from CCoeControl

    /**
    * @see CCoeControl::HandlePointerEventL
    */
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );
    
public: // from MAknWsEventObserver

    /**
    * @see MAknWsEventObserver::HandleWsEventL
    */
    void HandleWsEventL( const TWsEvent& aEvent,
        CCoeControl* aDestination );    

protected: // virtual methods

    /**
    * The size changed method. If you need to do special handling after the
    * control's size has changed, overwrite this method.
    */
    virtual void HandleSizeChanged();

private: // from CCoeControl
    /**
    * @see CCoeControl::Draw
    */
    void Draw( const TRect& aRect ) const;

    /**
    * @see CCoeControl::SizeChanged
    */
    void SizeChanged();

    /**
    * @see CCoeControl::PositionChanged
    */
    void PositionChanged();
    
    /**
    * The draw method.
    */
    void DoDraw( CWindowGc& aGc ) const;

private:    
    
    // Reference to application UI.
    CVtUiAppUi& iAppUi;
    

    };

#endif /*CVTUIREMOTEVIDEOCONTROL_H_*/

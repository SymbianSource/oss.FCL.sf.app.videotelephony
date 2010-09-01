/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  End call button definition.
*
*/

#ifndef C_VTUIENDCALLBUTTON_H
#define C_VTUIENDCALLBUTTON_H

// INCLUDES
#include    <aknbutton.h>
#include    "videotelui.hrh"

// CLASS DECLARATION

/**
 *  CCVtUiEndCallButton
 * 
 */
class CVtUiEndCallButton : public CAknButton
    {
public:
    // Constructors and destructor

    /**
    * Static construction method.
    * @return Pointer to newly created instance of CVtUiEndCallButton.
    */
    static CVtUiEndCallButton* NewL();
    
    /**
    * C++ destructor.
    */
    ~CVtUiEndCallButton();

    /**
     * Constructs controls from a resource file.
     *
     * @param aReader The resource reader, with which to access the 
     *      control's resource values.
     */
    void ConstructFromResourceL( const TInt aResourceId );
    
    /**
    * The layout of text and the rectangle of icon setting method.
    * @param aLayoutText The text layout.
    * @param aIconRect The rectangle of icon to be set.
    */
    void SetLayout( const TAknLayoutText aLayoutText,
                    const TRect aIconRect);
    
protected: 
    //from base class CCoeControl
    /**
     * From CCoeControl. 
     * Draws the control. Called by window server.
    */
    void Draw(const TRect& aRect) const;
    
    /**
     * Handles a change to the control's resources.
     *
     * @param aType is a message UID value.
     */
    void HandleResourceChange( TInt aType );
    
private:
    
    /**
     * C++ constructor for the end call button.
     */
    CVtUiEndCallButton();
    
    /**
     * Symbian 2nd phase constructor.
     */
    void ConstructL();
    
    /**
     * Gets the correct text color.
     * 
     * @param aPenColor the RGB colour value
     */
    void GetTextColors( TRgb& aPenColor ) const;
    
    /**
     * Loads icons from the resource
     */
    void LoadButtonIcon( TVtUiBitmapId aIconId, TVtUiBitmapId aMaskId );
    
    /**
     * Draw text and icon according to the layout.
     * 
     * @param aGc the window graphics context
     */ 
    void LayoutIconAndText( CWindowGc& aGc ) const;
    
private:
    
    /**
     * Layout text
     */
    TAknLayoutText iLayoutText;
    
    /**
     * Rectangle of the icon of the button.
     */
    TRect iIconRect;
    };

#endif // C_VTUIENDCALLBUTTON_H

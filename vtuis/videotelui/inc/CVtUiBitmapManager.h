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
* Description:  Bitmap manager for Video Telephone application.
*
*/



#ifndef CVTUIBITMAPMANAGER_H
#define CVTUIBITMAPMANAGER_H

//  INCLUDES
#include    <e32base.h>
#include    <gdi.h>
#include    "videotelui.hrh"

// DATA TYPES

/**
* Type definition for bitmap pool identifier.
* Zero is reserved as invalid identifier.
*/
typedef TInt TVtUiBitmapPoolId;

// FORWARD DECLARATION
class CFbsBitmap;

// CLASS DECLARATION

/**
*  Bitmap manager for Video Telephone application.
*  @since Series 60 2.8
*/
class CVtUiBitmapManager
    : public CBase
    {
    public: // Constructors and destructor
        
        /**
        * Constructor.
        */
        CVtUiBitmapManager();

        /**
        * Destructor.
        */
        ~CVtUiBitmapManager();

    public: // New functions

        /**
        * Adds bitmaps to the pool.
        * @param aBitmapId bitmap identifier.
        * @param aBitmapMaskId bitmap mask identifier, 
        *        KErrNotFound if no mask.
        * @param aExpectDefaultColor ETrue if default color is to be expected.
        * @return bitmap pool identifier.
        */
        TVtUiBitmapPoolId AddBitmapsL(
            TVtUiBitmapId aBitmapId, 
            TVtUiBitmapId aBitmapMaskId,
            TBool aExpectDefaultColor );

        /**
        * Adds bitmap to the pool.Note that this bitmap does not have mask.
        * @param aBitmapId bitmap identifier.
        * @param aExpectDefaultColor ETrue if default color is to be expected.
        * @return bitmap pool identifier.
        */
        TVtUiBitmapPoolId AddBitmapL(
            TVtUiBitmapId aBitmapId,
            TBool aExpectDefaultColor );
        
        /**
        * Removes bitmap from the pool.
        * @param aId bitmap pool identifier.
        */
        void RemoveBitmap( TVtUiBitmapPoolId aId );

        /**
        * Sets size of the specified bitmap. This method must be 
        * called before bitmap is used.
        *
        * @param aId bitmap pool identifier.
        * @param aSize size of the bitmap.
        */
        void SetSize( 
            TVtUiBitmapPoolId aId, 
            const TSize& aSize );

        /**
        * Sets size and default color of the specified bitmap. 
        * This method must be called before bitmap is used.
        *
        * @param aId bitmap pool identifier.
        * @param aSize size of the bitmap.
        * @param aDefaultColor default color of the bitmap.
        */
        void SetSizeAndColor( 
            TVtUiBitmapPoolId aId,
            const TSize& aSize, 
            const TRgb& aDefaultColor );

        /**
        * Sets aspect ratio preservation status.
        * @param aId bitmap pool identifier.
        * @param aPreserve ETrue if aspect ration is to be preserved.
        */
        void SetAspectRatio( 
            TVtUiBitmapPoolId aId,
            TBool aPreserve );

        /**
        * This method is called to inform that bitmap is required.
        * @param aId bitmap pool identifier.
        */
        void RequireBitmap( TVtUiBitmapPoolId aId );

        /**
        * Gets bitmap & its mask.
        * @param aId bitmap pool identifier.
        * @param aBitmap it will be updated to hold bitmap pointer, 
        *        or NULL if bitmap is not available. This pointer
        *        must not be kept any longer than absolutely required.
        * @param aBitmapMask it will be updated to hold bitmap mask pointer, 
        *        or NULL if bitmap mask is not available. This pointer
        *        must not be kept any longer than absolutely required.
        */
        void GetBitmaps(
            TVtUiBitmapPoolId aId,
            CFbsBitmap*& aBitmap,
            CFbsBitmap*& aBitmapMask );

        /**
        * Gets bitmap & its mask.
        * @param aId bitmap pool identifier.
        * @param aBitmap it will be updated to hold bitmap pointer, 
        *        or NULL if bitmap is not available. This pointer
        *        must not be kept any longer than absolutely required.
        */
        void GetBitmap(
            TVtUiBitmapPoolId aId,
            CFbsBitmap*& aBitmap );

        /**
        * Invalidates bitmaps. This is called on theme / layout change.
        */
        void InvalidateBitmaps();

    private:

        // Inner class.
        class CBitmapInfo;

        /**
        * Finds bitmap based on pool identifier.
        * @param aId bitmap pool identifier.
        * @return KErrNotFound if not found, or index to array.
        */ 
        TInt Find( TVtUiBitmapPoolId aId ) const;

    private:

        // Owned array of bitmap information instances.
        RPointerArray< CBitmapInfo > iBitmapArray;

        // Bitmap pool identifier used to generate bitmaps.
        TVtUiBitmapPoolId iBitmapId;

        // Temporary instance for getting bitmap file name.
        TFileName iTmpFileName;

    };

#endif      // CVTUIBITMAPMANAGER_H

// End of File

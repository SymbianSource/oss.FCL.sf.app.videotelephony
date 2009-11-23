/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Implementation of the CVtUiBitmapManager class.
*
*/



// INCLUDE FILES
#include    "CVtUiBitmapManager.h"
#include    "VtUiLayout.h"
#include    "VtUiPanic.h"

#include    <aknsutils.h>
#include    <akniconutils.h>
#include    <fbs.h>

// CONSTANTS

// Granularity of bitmap manager array.
const TInt KVtUiBitmapManagerGranularity = 16;

// MODULE DATA STRUCTURES

/**
* CBitmapInfo instances hold information of a bitmap and its mask.
* @since Series 60 2.8
*/
class CVtUiBitmapManager::CBitmapInfo 
    : public CBase
    {
    public: // Constructors and destructor

        /**
        * Constructor.
        */
        inline CBitmapInfo(
            TVtUiBitmapPoolId aId );

        /**
        * Destructor.
        */
        ~CBitmapInfo();

        /**
        * Sets bitmap identifiers.
        * @param aBitmapId bitmap identifier.
        * @param aBitmapMaskId bitmap mask identifier.
        */
        inline void SetBitmaps( 
            TVtUiBitmapId aBitmapId, 
            TVtUiBitmapId aBitmapMaskId );

        /**
        * Sets bitmap identifier.
        * @param aBitmapId bitmap identifier.
        */
        inline void SetBitmap( 
            TVtUiBitmapId aBitmapId );

        /**
        * Sets size.
        * @param aSize size of the bitmaps.
        */
        inline void SetSize( const TSize& aSize );

        /**
        * Sets aspect ratio preservation.
        * @param aPreserve ETrue if aspect ratio preserved.
        */
        inline void SetAspectRatio( TBool aPreserve );

        /**
        * Sets default color required / not required for this bitmap.
        * By default, default color is not required.
        * @param aRequireDefaultColor ETrue if default color is required, 
        *        EFalse otherwise.
        */
        inline void SetDefaultColorRequired( 
            TBool aRequireDefaultColor );

        /**
        * Sets default color.
        * @param aDefaultColor default color.
        */
        inline void SetDefaultColor( const TRgb& aDefaultColor );

        /**
        * Returns bitmap pool identifier.
        * @return bitmap pool identifier.
        */
        inline TVtUiBitmapPoolId BitmapPoolId() const;

        /**
        * Gets a bitmap and its mask.
        * @param aBitmap bitmap.
        * @param aBitmapMask bitmap mask.
        */
        inline void GetBitmap(
            CFbsBitmap*& aBitmap,
            CFbsBitmap*& aBitmapMask );

        /**
        * Resets bitmap information.
        */
        void Reset();

        /**
        * Constructs bitmap as far as possible.
        * @param aTmpFileName temporary file name,
        */
        void Require( TFileName& aTmpFileName );

    private:

        /**
        * Creates bitmaps using AVKON methods.
        * @param aTmpFileName temporary file name,
        */
        void DoCreateBitmapsL( TFileName& aTmpFileName  );

        /**
        * Sets size to the bitmap using AVKON method.
        */
        void DoSetSize();

    private:

        // Bitmap pool identifier.
        TVtUiBitmapPoolId iBitmapPoolId;

        // Size has been defined.
        TBool iHasSize;

        // Size of the bitmap has been changed.
        TBool iSizeChanged;

        // Size of the bitmaps.
        TSize iSize;
        
        // ETrue if default color required.
        TBool iRequireDefaultColor;

        // Default color has been defined.
        TBool iHasDefaultColor;
        
        // Default color.
        TRgb iDefaultColor;

        // Bitmap identifier.
        TVtUiBitmapId iBitmapId;

        // Owned bitmap instance.
        CFbsBitmap* iBitmap;

        // Bitmap mask identifier.
        TVtUiBitmapId iBitmapMaskId;

        // Owned bitmap mask instance.
        CFbsBitmap* iBitmapMask;

        // ETrue if bitmaps have been created.
        TBool iDoCreateBitmaps;

        // ETrue if size has been set.
        TBool iDoSetSize;

        // ETrue if aspect ratio preservation has been updated.
        TBool iHasAspectRatioPreserve;

        // ETrue if aspect ratio should be preserved.
        TBool iAspectRatioPreserve;

    };

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CVtUiBitmapManager
// -----------------------------------------------------------------------------
//
CVtUiBitmapManager::CVtUiBitmapManager()
    : iBitmapArray( KVtUiBitmapManagerGranularity )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::~CVtUiBitmapManager
// -----------------------------------------------------------------------------
//
CVtUiBitmapManager::~CVtUiBitmapManager()
    {
    iBitmapArray.ResetAndDestroy();
    iBitmapArray.Close();
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::AddBitmapsL
// -----------------------------------------------------------------------------
//
TVtUiBitmapPoolId CVtUiBitmapManager::AddBitmapsL(
        TVtUiBitmapId aBitmapId, 
        TVtUiBitmapId aBitmapMaskId,
        TBool aExpectDefaultColor )
    {
    iBitmapId++;
    CBitmapInfo* bitmapInfo = new ( ELeave ) CBitmapInfo( iBitmapId );
    CleanupStack::PushL( bitmapInfo );
    bitmapInfo->SetBitmaps( aBitmapId, aBitmapMaskId );
    bitmapInfo->SetDefaultColorRequired( aExpectDefaultColor );
    bitmapInfo->Require( iTmpFileName );

    User::LeaveIfError( iBitmapArray.Append( bitmapInfo ) );
    CleanupStack::Pop( bitmapInfo );
    return iBitmapId;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::AddBitmapL
// -----------------------------------------------------------------------------
//
TVtUiBitmapPoolId CVtUiBitmapManager::AddBitmapL(
        TVtUiBitmapId aBitmapId,
        TBool aExpectDefaultColor )
    {
    iBitmapId++;
    CBitmapInfo* bitmapInfo = new ( ELeave ) CBitmapInfo( iBitmapId );
    CleanupStack::PushL( bitmapInfo );
    bitmapInfo->SetBitmap( aBitmapId );
    bitmapInfo->SetDefaultColorRequired( aExpectDefaultColor );
    bitmapInfo->Require( iTmpFileName );

    User::LeaveIfError( iBitmapArray.Append( bitmapInfo ) );
    CleanupStack::Pop( bitmapInfo );
    return iBitmapId;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::RemoveBitmap
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::RemoveBitmap( 
        TVtUiBitmapPoolId aId )
    {
    const TInt pos = Find( aId );
    if ( pos != KErrNotFound )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ pos ];
        iBitmapArray.Remove( pos );
        delete bitmapInfo;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::SetSize
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::SetSize( 
        TVtUiBitmapPoolId aId, 
        const TSize& aSize )
    {
    const TInt pos = Find( aId );
    if ( pos != KErrNotFound )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ pos ];
        bitmapInfo->SetSize( aSize );
        bitmapInfo->Require( iTmpFileName );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::SetAspectRatio
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::SetAspectRatio( 
        TVtUiBitmapPoolId aId,
        TBool aPreserve )
    {
    const TInt pos = Find( aId );
    if ( pos != KErrNotFound )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ pos ];
        bitmapInfo->SetAspectRatio( aPreserve );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::SetSizeAndColor
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::SetSizeAndColor( 
        TVtUiBitmapPoolId aId, 
        const TSize& aSize, 
        const TRgb& aDefaultColor )
    {
    const TInt pos = Find( aId );
    if ( pos != KErrNotFound )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ pos ];
        bitmapInfo->SetSize( aSize );
        bitmapInfo->SetDefaultColor( aDefaultColor );
        bitmapInfo->Require( iTmpFileName );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::RequireBitmap
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::RequireBitmap( TVtUiBitmapPoolId aId )
    {
    const TInt pos = Find( aId );
    if ( pos != KErrNotFound )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ pos ];
        bitmapInfo->Require( iTmpFileName );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::GetBitmaps
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::GetBitmaps(
        TVtUiBitmapPoolId aId,
        CFbsBitmap*& aBitmap,
        CFbsBitmap*& aBitmapMask )
    {
    aBitmap = NULL;
    aBitmapMask = NULL;

    const TInt pos = Find( aId );
    if ( pos != KErrNotFound )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ pos ];
        bitmapInfo->GetBitmap( aBitmap, aBitmapMask );
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::GetBitmap
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::GetBitmap(
        TVtUiBitmapPoolId aId,
        CFbsBitmap*& aBitmap )
    {
    CFbsBitmap* dummy = NULL;
    GetBitmaps( aId, aBitmap, dummy );
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::InvalidateBitmaps
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::InvalidateBitmaps()
    {
    const TInt count = iBitmapArray.Count();
    for ( TInt index = 0; index < count; index++ )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ index ];
        bitmapInfo->Reset();
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::Find
// -----------------------------------------------------------------------------
//
TInt CVtUiBitmapManager::Find( TVtUiBitmapPoolId aId ) const
    {
    TInt result = KErrNotFound;
    const TInt count = iBitmapArray.Count();
    for ( TInt index = 0; index < count; index++ )
        {
        CBitmapInfo* bitmapInfo = iBitmapArray[ index ];
        if ( bitmapInfo->BitmapPoolId() == aId )
            {
            result = index;
            index = count; // out of the loop
            }
        }

    return result;
    }

// Implementation of CBitmapInfo:

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::CBitmapInfo
// -----------------------------------------------------------------------------
//
inline CVtUiBitmapManager::CBitmapInfo::CBitmapInfo(
        TVtUiBitmapPoolId aId )
    : iBitmapPoolId( aId ), 
      iBitmapId( EVtUiBitmapNone ), 
      iBitmapMaskId( EVtUiBitmapNone )
    {
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::~CBitmapInfo
// -----------------------------------------------------------------------------
//
CVtUiBitmapManager::CBitmapInfo::~CBitmapInfo()
    {
    delete iBitmap;
    delete iBitmapMask;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::SetBitmaps
// -----------------------------------------------------------------------------
//
inline void CVtUiBitmapManager::CBitmapInfo::SetBitmaps( 
        TVtUiBitmapId aBitmapId, 
        TVtUiBitmapId aBitmapMaskId )
    {
    iBitmapId = aBitmapId;
    iBitmapMaskId = aBitmapMaskId;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::SetBitmap
// -----------------------------------------------------------------------------
//
inline void CVtUiBitmapManager::CBitmapInfo::SetBitmap( 
        TVtUiBitmapId aBitmapId )
    {
    iBitmapId = aBitmapId;
    iBitmapMaskId = EVtUiBitmapNone;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::SetSize
// -----------------------------------------------------------------------------
//
inline void CVtUiBitmapManager::CBitmapInfo::SetSize( 
        const TSize& aSize )
    {
    if ( iHasSize )
        {
        iSizeChanged = ( iSize != aSize );
        }

    iHasSize = ETrue;
    iSize = aSize;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::SetAspectRatio
// -----------------------------------------------------------------------------
//
inline void CVtUiBitmapManager::CBitmapInfo::SetAspectRatio( TBool aPreserve )
    {
    iHasAspectRatioPreserve = ETrue;
    iAspectRatioPreserve = aPreserve;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::SetDefaultColorRequired
// -----------------------------------------------------------------------------
//
inline void CVtUiBitmapManager::CBitmapInfo::SetDefaultColorRequired( 
        TBool aRequireDefaultColor )
    {
    iRequireDefaultColor = aRequireDefaultColor;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::SetDefaultColor
// -----------------------------------------------------------------------------
//
inline void CVtUiBitmapManager::CBitmapInfo::SetDefaultColor( 
        const TRgb& aDefaultColor )
    {
    __ASSERT_DEBUG( iRequireDefaultColor, 
        VtUiPanic::Panic( EVtUiPanicDefaultColorRequireMismatch ) );
    iHasDefaultColor = ETrue;
    iDefaultColor = aDefaultColor;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::BitmapPoolId
// -----------------------------------------------------------------------------
//
inline TVtUiBitmapPoolId CVtUiBitmapManager::CBitmapInfo::BitmapPoolId() const
    {
    return iBitmapPoolId;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::GetBitmap
// -----------------------------------------------------------------------------
//
inline void CVtUiBitmapManager::CBitmapInfo::GetBitmap(
        CFbsBitmap*& aBitmap,
        CFbsBitmap*& aBitmapMask )
    {
    if ( iDoCreateBitmaps && iDoSetSize )
        {
        aBitmap = iBitmap;
        aBitmapMask = iBitmapMask;
        }
    else
        {
        aBitmap = NULL;
        aBitmapMask = NULL;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::Reset
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::CBitmapInfo::Reset()
    {
    delete iBitmap;
    iBitmap = NULL;

    delete iBitmapMask;
    iBitmapMask = NULL;

    iSize = TSize();
    iHasSize = EFalse;
    iSizeChanged = EFalse;
    iHasDefaultColor = EFalse;
    iDefaultColor = TRgb();
    iDoCreateBitmaps = EFalse;
    iDoSetSize = EFalse;
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::Require
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::CBitmapInfo::Require( TFileName& aTmpFileName )
    {
    // Bitmap can be created when the following has been satisfied
    // a) It has not been created yet and default color is not required,
    // b) It has not been created yet and default color is required and 
    //    default color is available.
    if ( !iDoCreateBitmaps && !( iRequireDefaultColor && !iHasDefaultColor ) )
        {
        TRAP_IGNORE( DoCreateBitmapsL( aTmpFileName ) );
        }

    DoSetSize();
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::DoCreateBitmapsL
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::CBitmapInfo::DoCreateBitmapsL( 
        TFileName& aTmpFileName )
    {
    if ( !iDoCreateBitmaps )
        {
        TInt bitmapIndex = KErrNotFound;

        VtUiLayout::Resolve( iBitmapId, aTmpFileName, bitmapIndex );

        MAknsSkinInstance* skin = AknsUtils::SkinInstance();
        TAknsItemID skinId = VtUiLayout::MapBitmapToSkinId( iBitmapId );
        
        TAknsItemID colorId = KAknsIIDNone;
        TInt colorIndex = KErrNotFound;
        TBool colorAvailable = EFalse;
        if ( iHasDefaultColor )
            {
            colorAvailable = 
                VtUiLayout::MapBitmapToColorId( 
                    iBitmapId, colorId, colorIndex );
            }

        if ( iBitmapMaskId != EVtUiBitmapNone )
            {
            TInt bitmapMaskIndex = KErrNotFound;
#ifdef _DEBUG
            TFileName fileName;
            VtUiLayout::Resolve( iBitmapMaskId, fileName, bitmapMaskIndex );
            __ASSERT_ALWAYS( aTmpFileName == fileName, 
                VtUiPanic::Panic( EVtUiPanicMismatchInBitmapFileNames ) );
#else
            VtUiLayout::Resolve( iBitmapMaskId, aTmpFileName, bitmapMaskIndex );
#endif
            if ( colorAvailable )
                {
                AknsUtils::CreateColorIconL( 
                    skin, skinId,
                    colorId, colorIndex,
                    iBitmap, iBitmapMask,
                    aTmpFileName,
                    bitmapIndex,
                    bitmapMaskIndex,
                    iDefaultColor );
                }
            else
                {
                AknsUtils::CreateIconL(
                    skin, skinId,
                    iBitmap, iBitmapMask,
                    aTmpFileName,
                    bitmapIndex, 
                    bitmapMaskIndex );
                }
            }
        else
            {
            // Only normal skinning for these.
            AknsUtils::CreateIconL(
                skin,
                skinId,
                iBitmap,
                aTmpFileName,
                bitmapIndex );
            }

        iDoCreateBitmaps = ETrue;
        }
    }

// -----------------------------------------------------------------------------
// CVtUiBitmapManager::CBitmapInfo::DoSetSize
// -----------------------------------------------------------------------------
//
void CVtUiBitmapManager::CBitmapInfo::DoSetSize()
    {
    if ( iDoCreateBitmaps && iHasSize && ( !iDoSetSize || iSizeChanged ) )
        {
        iSizeChanged = EFalse;
        TInt retBitmap = KErrNone;
        if ( !iHasAspectRatioPreserve )
            {
            retBitmap = AknIconUtils::SetSize( iBitmap, iSize );
            }
        else
            {
            TScaleMode scaleMode = 
                iAspectRatioPreserve ? 
                    EAspectRatioPreserved : 
                    EAspectRatioNotPreserved;
            retBitmap = AknIconUtils::SetSize( iBitmap, iSize, scaleMode );
            }

        iDoSetSize = ( retBitmap == KErrNone );
        }
    }

//  End of File

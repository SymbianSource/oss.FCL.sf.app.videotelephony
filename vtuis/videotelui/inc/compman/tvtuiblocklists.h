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
* Description:  VT UI component state definition.
*
*/


#ifndef T_VTUIBLOCKLISTS_H
#define T_VTUIBLOCKLISTS_H

#include <e32base.h>

#include "mvtuicomponent.h"

/**
 *  CVtUiBlockListIterator
 *
 *  Class for iterating through component's block list.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( CVtUiBlockListIterator ) : public CBase
    {

public: // public abstract methods

    /**
     * Returns ETrue if there is more component Ids left in the iterator.
     *
     * @return ETrue if there is more Ids left, EFalse otherwise.
     */
    virtual TBool HasNext() const = 0;

    /**
     * Returns next component id.
     *
     * @return Next component Id.
     */
    virtual MVtUiComponent::TComponentId Next() = 0;

    };

/**
 *  TVtUiBlockList
 *
 *  Base class for component block lists.
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiBlockList )
    {

public: // public methods

    /**
     * Destructor.
     */
    virtual ~TVtUiBlockList();

public: // public abstract methods

    /**
     * Returns ETrue if block list is empty.
     *
     * @return ETrue if this block list is empty, EFalse otherwise.
     */
    virtual TBool IsEmpty() const = 0;

    /**
     * Returns ETrue if block list contains given component id.
     *
     * @param aId Component Id to check.
     * @return ETrue if this block list contains given component Id, EFalse
     * otherwise.
     */
    virtual TBool Contains( MVtUiComponent::TComponentId aId ) const = 0;

    /**
     * Merges this block list with given block list.
     *
     * @param aBlockList List to merge into this block list.
     */
    virtual void Union( const TVtUiBlockList& aBlockList ) = 0;

    /**
     * Returns new instance of block list iterator. Instance is owned by the
     * caller, but it is also pushed to cleanupstack.
     *
     * @return Instance to block list iterator. Iterator is for this block
     * list instance.
     */
    virtual CVtUiBlockListIterator* IteratorLC() const = 0;

protected: // protected methods

    /**
     * Constructor.
     */
    TVtUiBlockList();

    };

/**
 *  TVtUiBlockListBitField
 *
 *  Component block list in which component IDs are defined as bits (i.e.
 *  only single bit is set per ID).
 *
 *  @since S60 v3.2
 */
NONSHARABLE_CLASS( TVtUiBlockListBitField ) : public TVtUiBlockList
    {

public: // public methods

    /**
     * Default construct, initialized block list as empty.
     */
    TVtUiBlockListBitField();

    /**
     * Constructor that initializes block list.
     *
     * @param aBlockMask Component Ids that will be added to block list.
     */
    TVtUiBlockListBitField( TUint aBlockMask );

public: // from

    /**
     * @see TVtUiBlockList::IsEmpty
     */
    TBool IsEmpty() const;

    /**
     * @see TVtUiBlockList::Contains
     */
    TBool Contains( MVtUiComponent::TComponentId aId ) const;

    /**
     * @see TVtUiBlockList::Union
     */
    void Union( const TVtUiBlockList& aBlockList );

    /**
     * @see TVtUiBlockList::IteratorLC
     */
    CVtUiBlockListIterator* IteratorLC() const;

private: // inner classes

    /**
     * CVtUiBListIteratorBF
     *
     * @since S60 v3.2
     */
    class CVtUiBListIteratorBF : public CVtUiBlockListIterator
        {

    public: // public methods

        /**
         * Static constructor
         *
         * @param aBlockMask Components Ids.
         */
        static CVtUiBListIteratorBF* NewLC( const TUint& aBlockMask );

    private: // private methods

        /**
         * Constructor
         */
        CVtUiBListIteratorBF( const TUint& aBlockMask );

    private: // from CVtUiBlockListIterator

        /**
         * @see CVtUiBlockListIterator::HasNext
         */
        TBool HasNext() const;

        /**
         * @see CVtUiBlockListIterator::Next
         */
        MVtUiComponent::TComponentId Next();

    private:  // data

        // Blockmask from TVtUiBlockListBitField
        const TUint iBlockMask;

        // Current id
        TUint iCurrent;

        };

private: // data

    // Block list as bit field, this requires that component ids are defined
    // as bitfields.
    TUint iBlockMask;

    };

#endif // T_VTUIBLOCKLISTS_H

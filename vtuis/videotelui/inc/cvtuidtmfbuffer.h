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
* Description:  DTMF buffer definition.
*
*/


#ifndef C_VTUIDTMFBUFFER_H
#define C_VTUIDTMFBUFFER_H

#include <e32base.h>
#include "mvtuinumbersource.h"

class CCoeEnv;
class TKeyEvent;

// Maximum size of the DTMF buffer
const TInt KVtUiDTMFBufferSize = 64;

/**
*  MVtUiDTMFBufferObserver
*
*  Observer of DTMF chaning.
*/

class MVtUiDTMFBufferObserver
    {
public:
    /*
     * Buffer changed callback
     */
    virtual void NotifyDTMFBufferChangedL() = 0;
    };
    
/**
*  CVtUiDTMFBuffer
*
*  Base componentstate definition.
*
*  @since S60 v5.0
*/

class CVtUiDTMFBuffer : public CActive, public MVtUiNumberSource
    {

public:

    /**
    * Static construction method.
    * @param aCoeEnv Reference to CoeEnv object.
    * @return Pointer to newly created instance of CVtUiDTMFBuffer.
    */
    static CVtUiDTMFBuffer* NewL( const CCoeEnv& aCoeEnv );

    /**
    * Static construction method.
    * @param aCoeEnv Reference to CoeEnv object.
    * @param aObserver Pointer to buffer observer
    * @return Pointer to newly created instance of CVtUiDTMFBuffer.
    */
    static CVtUiDTMFBuffer* NewL( const CCoeEnv& aCoeEnv, MVtUiDTMFBufferObserver* aObserver );

    /**
    * C++ destructor.
    */
    ~CVtUiDTMFBuffer();

    /**
    * Append one character to DTMF buffer.
    * @param aChar Character to append.
    * @return ETrue if the given character was appended (i.e. it is a DTMF)
    */
    TBool Append( TChar aChar );

    /**
    * Clears the contents of the DTMF buffer.
    */
    void Reset();

    /**
    * Promote this instance as current number source.
    */
    void Activate();

    /**
    * Demote this instance from current number source position.
    */
    void Deactivate();

public: // from MVtUiNumberSource

    /**
    * @see MVtUiNumberSource::GetContents
    */
    void GetContents( TDes& aContents ) const;

private: // from CActive

    /**
    * @see CActive::DoCancel
    */
    void DoCancel();

    /**
    * @see CActive::RunL
    */
    void RunL();

private:

    /**
    * C++ constructor
    */
    CVtUiDTMFBuffer( const CCoeEnv& aCoeEnv );
    
    /**
    * C++ constructor
    */
    CVtUiDTMFBuffer( const CCoeEnv& aCoeEnv, MVtUiDTMFBufferObserver* aObserver );

    /**
    * 2nd constructor, may leave.
    */
    void ConstructL();

    /**
    * Starts buffer modification monitoring timer. If this timer expires,
    * buffer will be reset. Timer is restarted when new character is added to
    * the buffer.
    */
    void StartTimer();

    /**
    * Called when buffer modification monitoring timer has expired.
    */
    void TimerExpired( TInt aError );

    /**
    * Clears the contents of the DTMF buffer.
    */
    void ResetBuffer();

private:

    // Reference to coeenv
    const CCoeEnv& iCoeEnv;

    // Timer instance
    RTimer iTimer;

    // DTMF buffer
    TBuf< KVtUiDTMFBufferSize > iBuffer;
    
    // DTMF buffer observer
    MVtUiDTMFBufferObserver* iObserver;

    };

#endif // C_VTUIDTMFBUFFER_H

/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Listener for Publish and subscribe data.
*
*/


#ifndef CVTENGPUBSUBSGSETTINGS_H
#define CVTENGPUBSUBSGSETTINGS_H

//  INCLUDES
#include <e32base.h>
#include <e32std.h>
#include <e32property.h>

// FORWARD DECLARATIONS
class MVtEngSettingPSObserver;

// CLASS DECLARATION

/**
*  RProperty poller.
*
*  @lib videoteleng.lib
*  @since Series 60 2.8
*/
NONSHARABLE_CLASS( CVtEngPubSubsListener ) : public CActive
    {
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        * @param aUid the Uid to use
        * @param aKey item's key
        * @param aObserver callback interface for notification
        * @return instance of CVtEngPubSubsListener
        */
        static CVtEngPubSubsListener* NewL( const TUid aUid, const TInt aKey, 
            MVtEngSettingPSObserver* aObserver );
        
        /**
        * Destructor.
        */
        virtual ~CVtEngPubSubsListener();
        
    public: // New functions.

        /**
        * Gets integer value from P & S.
        * @param aVal a value in return
        * @return error code
        */       
        TInt Get( TInt& aVal );

        /**
        * Gets 8 bit string value from P&S.
        * @param aVal a value in return
        * @return error code
        */
        TInt Get( TDes8& aVal );
        
        /**
        * Gets 16 bit descriptor value from P&S.
        * @param aVal a value in return
        * @return error code
        */
        TInt Get( TDes16& aVal );

    private: // New functions.

        /**
        * Starts the listening (RunL).
        */
        void StartListening();

    private: // From CActive.

        /** @see CActive::RunL */
        virtual void RunL();

        /** @see CActive::Cancel */
        virtual void DoCancel();

        /** @see CActive::RunError */
        virtual TInt RunError( TInt aError );

    private:

        /**
        * C++ default constructor.
        * @param aUid the Uid to use
        * @param aKey item's key
        * @param aObserver callback interface for notification
        */
        CVtEngPubSubsListener( const TUid aUid,  TInt aKey, 
            MVtEngSettingPSObserver* aObserver );

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();
    
    private:    // Data
    
        // UID of the monitored item.
        TUid        iUid;
        
        // ID of the monitored item.
        TInt        iId;
        
        // Property to subscribe to.
        RProperty   iProperty;
        
        // The notification interface.
        MVtEngSettingPSObserver* iCallback;
    };

#endif // CVTENGPUBSUBSGSETTINGS_H
// End of File

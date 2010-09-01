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
* Description:  Base class for toolbar.
*
*/


#ifndef C_VTUITOOLBAR_H
#define C_VTUITOOLBAR_H

#include <e32base.h>
#include <aknappui.h>
#include <akntoolbarobserver.h>

#include "mvtuifeature.h"
#include "CVtUiAppUi.h"
#include "cvtuifeaturebase.h"
#include "mvtuicommandui.h"
#include "mvtuicomponent.h"
#include "mvtuiresourcechangeobserver.h"
#include "tvtuicomponentstate.h"
#include  "mvtuilayoutchangeobserver.h"
#include <aknlayoutscalable_avkon.cdl.h>

class MVtuiFeature;
class CAknToolbar;
class CVtUiToolbarItem;
class TVtUiFeatureState;
class TVtUiStates;
class CVtUiToolbarContext;
class CVtUiToolbarCmdPolicy;
class CVtUiHideToolbarItemAction;
class CVtUiFeatureManager;
class CVtUiToolbarSKModifier;
class CVtUiToolbarButton;

/**
*  TVtUiToolbarComponentState
*
* Toolbar componentstate definition.
*
*  @since S60 v3.2
*/
class TVtUiToolbarComponentState : public TVtUiComponentState
    {

public:

    /**
    * Constructor
    * @param aComponent Reference to component.
    */
    TVtUiToolbarComponentState( MVtUiComponent& aComponent );
    
    };

/**
* CVtUiToolbar  
* 
* Toolbar UI feature definition.
*
* @since S60 3.2
*/
class CVtUiToolbarBase : public CVtUiFeatureBase, public MAknToolbarObserver,
    public MVtUiCommandUi, public MVtUiComponent,
    public MVtUiLayoutChangeObserver
    {
    public: // public methods

        /**
        * C++ destructor.
        */
        ~CVtUiToolbarBase();
    
    public: // from MAknToolbarObserver 
    
        /**
        * @see MAknToolbarObserver::DynInitToolbarL
        */
        void DynInitToolbarL( 
            TInt aResourceId,
            CAknToolbar* aToolbar );
        
        /**
        * @see MAknToolbarObserver::DynInitToolbarL
        */
        void OfferToolbarEventL( TInt aCommand );
    
    public: // from MVtUiFeature
        /**
        * @see MVtUiFeature::StartL
        */
        void StartL();

        /**
        * @see MVtUiFeature::Stop
        */
        void Stop();
        
        /*
        * @see MVtUiFeature::InitFeatureL
        */
        void InitFeatureL();
        
    public: // from MVtUiCommandUi
    
        /**
        * @see MVtUiCommandUi::RefreshL
        */
        void RefreshL();

        /**
        *  @see MVtUiCommandUi::AddCommandModifier
        */
         TInt AddCommandModifier( CVtUiCommandModifyBase& aModifier );

        /**
        * @see MVtUiCommandUi::RemoveCommandModifier
        */
         void RemoveCommandModifier( CVtUiCommandModifyBase& aModifier );
        
    public: // from MVtUiComponent

        /**
        * @see MVtUiComponent::ComponentId
        */
        TComponentId ComponentId() const;

        /**
        * @see MVtUiComponent::ComponentAsControl
        */
        CCoeControl* ComponentAsControl();

        /**
        * @see MVtUiComponent::DoActivateL
        */
        virtual void DoActivateL();

        /**
        * @see MVtUiComponent::DoDeactivateL
        */
        virtual void DoDeactivateL();
    
    public: // from MVtUiComponentManager

        /**
        * @see MVtUiComponentManager::HandleLayoutChangeL
        */
        void HandleLayoutChangeL();

    public:

        /**
        * Return number of commands in toolbar.
        * @return Number of commands.
        */
        TInt NumberOfToolbarControls() const;
        
        /**
        * Maps command id array index to command id.
        * @param aIndex Command id array index.
        * @return Command id associated with index.
        */
        TInt CommandIdByCmdIdsArrayIndex( TInt aIndex ) const;
   
        /**
        * Updates toolbar's buttons states and
        * redraws the toolbar.
        */
        void UpdateToolbarL();
     
        /**
        * EHidden
        *  command is hidden
        * EDimmed
        *  command is dimmed
        * EShown
        * command is visible
        */
        enum TCmdStateFlags
            {
            ENotInitialized = -1,
            EHidden,
            EDimmed,
            EShown
            }; 

         /**
        * Sets visibility of toolbar commands.
        * @param aCmdId command id.
        * @param aNewState command's new state.
        * @return ETrue if command is available, otherwise EFalse.
        */
        void SetCmdIdVisibilityStateL( TInt aCmdId, TCmdStateFlags aNewState);
        
        /**
        * Cheks if command is available in toolbar.
        * @param aCmdId command id.
        * @return ETrue if command is available, otherwise EFalse.
        */
        TBool IsCommandInToolbar( TInt aCmdId ) const;
         
    protected:

        /**
        * C++ constructor
        */
        CVtUiToolbarBase( CVtUiFeatureManager& aFeatureManager );

        /**
        * 2nd phase constructor
        */
        void BaseConstructL();

    protected:    
  
        /**
        * Creates toolbar buttons
        */
        virtual void CreateToolbarButtonsL();

        /*
        * Appends all the commnands used by toolbar to an array.
        */
        virtual void PopulateCmdsIdsL();    
            
        /*
        * Sets toolbar visibility after layoutchange
        */    
        virtual void SetToolbarVisibilityAfterLayoutChangeL( TBool aVisible );
    
        /**
        * Creates all toolbar items()
        */
        void CreateToolbarItemL( TInt aResourceId,
            TInt aCommandId, CVtUiAppUi& appUi );
   
        /**
        * Finds command from array by command id.
        */
        CVtUiToolbarButton* FindToolbarItemByCommandId( const TInt aCommandId );
         
        /*
        * Starts or stops to block pointer events
        * @param aIsBlocking ETrue if events are blocked
        * otherwise EFalse
        */
        void BlockPointerEvents( TBool aIsBlocking );
           
        /*
        * Starts or stops to block key events
        * @param aIsBlocking ETrue if events are blocked
        * otherwise EFalse
        */
        void BlockKeyEvents( TBool aIsBlocking );
         
        /*
        * Cheks if dialer component is active
        * @return ETrue if dialer is aactive, otherwise EFalse. 
        */
        TBool IsDialerActive() const;
        
        /**
        * Dims toolbar.
        * @param aDimmed ETrue ETrue to dim the toolbar, 
        *      EFalse to set the toolbar as not dimmed
        */
        void DimToolbar( const TBool aDimmed, const TBool aDrawNow );
    private:
    
        /**
        * Hides command from toolbar.
        */
        void HideToolbarButton( const TInt aCommandId, const TBool aHide,
            const TBool aDrawNow );
        
        /**
        * Dims command from toolbar.
        */
        void DimToolbarButton( const TInt aCommandId, const TBool aDimmed,
            const TBool aDrawNow ); 
       
        /**
        * Maps toggle button id to single command id.
        */
        TInt MapCmdIdToChilId( TInt aCmdId );
        
        /**
        * Maps single command id to toggle button id.
        */
        TInt MapCmdIdToParentId( TInt aCmdId );
        
        /*
        * Checks if command id associated with toggle button is visible.
        * Togglle button has two states and two command ids which has their
        * own state values. See from .rss file.
        */
        TBool IsCmdIdVisibleInToggleButton( TInt aCmdId );
        
        /*
        * Checks if both command ids in togglebutton are dimmed.
        */
        TBool IsToggleButtonHidden( TInt aFirstCmdId, TInt aSecondCmdId );
        
        /*
        * Removes registrations.
        */
        void Clean();
        
    protected: // data
        
        // array of supported commmand ids
        RArray<TInt> iCmdIds;    
        
        // current focus id
        TInt iCmdFocus;
        
         // owned toolbar control
        CAknToolbar* iToolbar;
        
        // Number of supported toolbar buttons
        TInt iNumberOfToolbarButtons;
     
    private: // data
         
        // struct used by iCmdStates array
        class TCommandState 
            {
            public:
                TInt iCmdId;
                TCmdStateFlags iOldState;
                TCmdStateFlags iNewState;
            };     
        
         // owned toolbar item array
        RPointerArray<CVtUiToolbarButton> iToolBarControls;

        // toolbar context instance
        CVtUiToolbarContext* iToolbarCtx; 
       
        // owned hide toolbar item action
        CVtUiHideToolbarItemAction* iHideToolbarItemAction;
        
        // Toolbar command policy instance
        CVtUiToolbarCmdPolicy* iToolbarCmdPolicy;
        
        // owned softkey modifier
        CVtUiToolbarSKModifier* iToolbarSKModifier;
        
        // array which hold state information of the commands
        RArray<TCommandState> iCmdStates;
        
        // Component state
        TVtUiToolbarComponentState iComponentState;
        
        // ETrue if capture mode was on in previous update
        TBool iWasCaptureModePreviousState;
    
    };

#endif // C_VTUITOOLBAR_H
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
* Description:  Command settings class definition.
*
*/


#ifndef C_VTUICOMMANDSETTING_H
#define C_VTUICOMMANDSETTING_H

#include <e32base.h>

#include "mvtuicommandsetting.h"

class CVtUiCommandModifyBase;

/**
 *  CVtUiCommandSetting
 *
 *  Template commmand setting class that takes command setting action as a
 *  templated parameter.
 *
 *  @since S60 v3.2
 */
template < typename ACTION >
class CVtUiCommandSetting : public CBase, public MVtUiCommandSetting
    {

public:

    /**
     * Destructor
     */
    ~CVtUiCommandSetting();

    /**
     * Defines commands.
     *
     * @param aAction Action related to commands to be defined.
     */
    void DefineCommandsL( const ACTION& aAction );

    /**
     * Adds new modifer
     *
     * @param aModifier Reference to modifier to be added to this setting
     * instance.
     * @return KErrNone if modifier could be added, KErrAlreadyExists if same
     * modifier is already added or KErrArgument if another modifier with
     * same priority is already added.
     */
    TInt AddModifier( CVtUiCommandModifyBase& aModifier );

    /**
     * Removes modifier
     *
     * @param aModifier Constant reference to modifier to be removed.
     */
    void RemoveModifier( CVtUiCommandModifyBase& aModifier );

    /**
     * Return command type
     *
     * @return Type of commands this setting class instance is defining.
     */
    Type CommandType() const;

    /**
     * Returns reference to action
     *
     * @return Constant reference to action that is related to this command
     * definition process.
     */
    const ACTION& Action();

protected:

    /**
     * Constructor
     */
    CVtUiCommandSetting( Type aCommandType );

private:

    // Modifiers
    RPointerArray< CVtUiCommandModifyBase > iModifiers;

    // Command type
    const Type iCommandType;

    // Stored action
    const ACTION* iAction;

    };

#include "cvtuicommandsetting.inl"

#endif // C_VTUICOMMANDSETTING_H

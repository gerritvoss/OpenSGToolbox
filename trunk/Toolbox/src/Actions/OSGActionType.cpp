/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "OSGActionType.h"
#include "OSGActionFactory.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ActionType::ActionType(const Char8  *szName,
                   const Char8  *szParentName,
                   const UInt32  uiNameSpace ) :
    Inherited(szName, szParentName, uiNameSpace),
    _uiActionTypeId(0),
    _uiActionTypeRootId(0)
{
    _uiActionTypeId = ActionFactory::the()->registerType(this);
}

ActionType::ActionType(const ActionType &source) :
    Inherited(source),
    _uiActionTypeId(source._uiActionTypeId),
    _uiActionTypeRootId(source._uiActionTypeRootId)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ActionType::~ActionType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool ActionType::operator ==(const ActionType &other) const
{
    return *(static_cast<const Inherited *>(this)) == other;
}

bool ActionType::operator !=(const ActionType &other) const
{
    return ! (*this == other);
}



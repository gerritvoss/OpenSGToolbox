/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
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

#include "OSGEventType.h"
#include "OSGEventFactory.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

EventType::EventType(const Char8  *szName,
                   const Char8  *szParentName,
                   const UInt32  uiNameSpace ) :
    Inherited(szName, szParentName, uiNameSpace),
    _uiEventTypeId(0),
    _uiEventTypeRootId(0)
{
    _uiEventTypeId = EventFactory::the()->registerType(this);
}

EventType::EventType(const EventType &source) :
    Inherited(source),
    _uiEventTypeId(source._uiEventTypeId),
    _uiEventTypeRootId(source._uiEventTypeRootId)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

EventType::~EventType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool EventType::operator ==(const EventType &other) const
{
    return *(static_cast<const Inherited *>(this)) == other;
}

bool EventType::operator !=(const EventType &other) const
{
    return ! (*this == other);
}



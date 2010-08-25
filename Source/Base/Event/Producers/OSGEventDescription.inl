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

#ifndef _OSGEVENTDESCRIPTIONIMPL_INL_
#define _OSGEVENTDESCRIPTIONIMPL_INL_

OSG_BEGIN_NAMESPACE
inline
EventDescription::EventDescription(const std::string                  &szName,
                                     const std::string                  &Description,
                                     const UInt32           uiEventId,
                                     const TypeBase         &EventArgumentType,
                                           bool               bConsumable,
                                     EventGetMethod    fAccessFunctor) :

    _szName             (szName       ),
    _Description        (Description       ),
    _EventId           (uiEventId    ),
    _EventArgumentType  (EventArgumentType   ),
    _Consumable         (bConsumable   ),
    _fAccessFunctor     (fAccessFunctor)
{
}

inline
EventDescription::EventDescription(const EventDescription &source) :

    _szName             (source._szName           ),
    _Description        (source._Description      ),
    _EventId           (source._EventId         ),
    _EventArgumentType  (source._EventArgumentType),
    _Consumable         (source._Consumable       ),
    _fAccessFunctor     (source._fAccessFunctor   )
{
}

inline
EventDescription::~EventDescription(void)
{
} 

inline
const Char8 *EventDescription::getCName(void) const
{
    return _szName.c_str();
}

inline
const std::string &EventDescription::getName(void) const
{
    return _szName;
}

inline
const std::string &EventDescription::getDescription(void) const
{
    return _Description;
}

inline
UInt32 EventDescription::getEventId(void) const
{
    return _EventId;
}

inline
void EventDescription::setEventId(UInt32 uiEventId)
{
    _EventId = uiEventId;
}

inline
const TypeBase &EventDescription::getEventArgumentType   (void) const
{
    return _EventArgumentType;
}

inline
void EventDescription::setAccessFunctor(EventGetMethod fAccessFunctor)
{
    _fAccessFunctor = fAccessFunctor;
}
inline
EventGetMethod EventDescription::getAccessFunctor(void)
{
    return _fAccessFunctor;
}

inline
bool EventDescription::isValid(void)  const
{
    return (this != NULL && !_szName.empty()) ? true : false;
}

inline
bool EventDescription::getConsumable(void)  const
{
    return _Consumable;
}

inline
GetEventHandlePtr EventDescription::getEvent(const ReflexiveContainer &oContainer) const
{
    if(_fAccessFunctor != 0)
    {
        return ( (&oContainer)->*_fAccessFunctor) ();
    }
    return GetEventHandlePtr();
}

OSG_END_NAMESPACE

#endif /* _OSGEVENTDESCRIPTIONIMPL_INL_ */

/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *            Copyright (C) 2000-2002,2002 by the OpenSG Forum               *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGEVENTPRODUCERTYPE_INL_
#define _OSGEVENTPRODUCERTYPE_INL_

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGEventDescription.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt16 EventProducerType::getGroupId (void) const
{
    return _uiGroupId;
}

inline
EventProducerType *EventProducerType::getParent(void) const
{
    return _pParent;
}

inline
EventDescription *EventProducerType::getEventDescription(UInt32 uiEventId)
{
    EventDescription *foundDesc = NULL;
    EventDescription *testDesc;
    DescVecIt it;
    for ( it=_vDescVec.begin() ; it < _vDescVec.end(); it++ )
    {
        testDesc = *it;
        if(testDesc != NULL)
        {
            if(testDesc->getEventId() == uiEventId)
            {
                foundDesc = testDesc;
            }
        }
    }
    return foundDesc;
}

inline
const EventDescription *EventProducerType::getEventDescription(
    UInt32 uiEventId) const
{
    EventDescription *foundDesc = NULL;
    EventDescription *testDesc;
    DescVecConstIt it;
    for ( it=_vDescVec.begin() ; it < _vDescVec.end(); it++ )
    {
        testDesc = *it;
        if(testDesc != NULL)
        {
            if(testDesc->getEventId() == uiEventId)
            {
                foundDesc = testDesc;
            }
        }
    }
    return foundDesc;
}

inline
EventDescription *EventProducerType::findEventDescription(
    const std::string &szEventName)
{
    DescMapIt descIt = _mDescMap.find(szEventName);

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
const EventDescription *EventProducerType::findEventDescription(
    const std::string &szEventName) const
{
    DescMapConstIt descIt = _mDescMap.find(szEventName);

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
UInt32 EventProducerType::getNumEventDescs(void) const
{
    return _vDescVec.size();
}

inline
UInt32 EventProducerType::getProducedEventId(const std::string &ProducedEventName) const
{
    const EventDescription * EventDesc = findEventDescription(ProducedEventName);
    if(EventDesc == NULL)
    {
        return 0;
    }
    else
    {
        return EventDesc->getEventId();
    }
}


/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

inline
bool EventProducerType::isInitialized(void) const
{
    return _bInitialized;
}

inline
bool EventProducerType::isDerivedFrom(const TypeBase &other) const
{
    return Inherited::isDerivedFrom(other);
}

inline
bool EventProducerType::isDerivedFrom(const EventProducerType &other) const
{
    if(_uiTypeId == other._uiTypeId)
    {
        return true;
    }
    else
    {
        EventProducerType *pCurrType   = _pParent;
        while(pCurrType != NULL)
        {
            if(other._uiTypeId == pCurrType->_uiTypeId)
            {
                return true;
            }
            pCurrType = pCurrType->_pParent;
        }
    }
    return false;
}

inline
bool EventDescriptionPLT::operator()(const EventDescription *pElemDesc1, 
                const EventDescription *pElemDesc2) const
{
    return pElemDesc1->getEventId() < pElemDesc2->getEventId();
}

OSG_END_NAMESPACE


#endif /* _OSGEVENTPRODUCERTYPE_INL_ */

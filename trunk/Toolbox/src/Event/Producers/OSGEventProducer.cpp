/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILETOOLBOXLIB

#include <OpenSG/OSGConfig.h>

#include "OSGEventProducer.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::EventProducer

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

EventProducerType EventProducer::_ProducerClassType(
    "EventProducerType",
    NULL,
    NULL,
    InitEventProducerFunctor(),
    NULL,
    0);
    
/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
UInt32 EventProducer::getNumActivitiesAttached(UInt32 ProducedEventId) const
{
    ActivityMapConstItor SearchItor(_AttachedActivitys.find(ProducedEventId));
    if(SearchItor == _AttachedActivitys.end())
    {
        return 0;
    }
    else
    {
    }
    return SearchItor->second.size();
}

ActivityPtr EventProducer::getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
{
    ActivityMapConstItor SearchItor(_AttachedActivitys.find(ProducedEventId));
    if(SearchItor == _AttachedActivitys.end())
    {
        return ActivityPtr();
    }
    else
    {
        if(ActivityIndex >= SearchItor->second.size())
        {
            return ActivityPtr();
        }
        else
        {
            ActivitySetConstItor SetItor(SearchItor->second.begin());
            for(UInt32 i(0) ; i<ActivityIndex; ++i) ++SetItor;
            return *SetItor;
        }
    }
}

EventConnection EventProducer::attachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId)
{
    if(TheActivity == NullFC)
    {
        SWARNING << "EventProducer::attachActivity(): Cannot attach a NullFC Activity." << std::endl;
    }

    if(_AttachedActivitys.find(ProducedEventId) == _AttachedActivitys.end())
    {
        _AttachedActivitys[ProducedEventId] = std::set<ActivityPtr>();
    }

   _AttachedActivitys[ProducedEventId].insert(TheActivity);
   addRefCP(TheActivity);

   return EventConnection(
       boost::bind(&EventProducer::isActivityAttached, this, TheActivity, ProducedEventId),
       boost::bind(&EventProducer::detachActivity, this, TheActivity, ProducedEventId));
}

bool EventProducer::isActivityAttached(ActivityPtr TheActivity, UInt32 ProducedEventId) const
{
    return _AttachedActivitys.find(ProducedEventId)->second.find(TheActivity) != _AttachedActivitys.find(ProducedEventId)->second.end();
}

void EventProducer::detachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId)
{
    if(TheActivity == NullFC)
    {
        SWARNING << "EventProducer::detachActivity(): Cannot dettach a NullFC Activity." << std::endl;
    }

   ActivitySetItor EraseIter(_AttachedActivitys[ProducedEventId].find(TheActivity));
   if(EraseIter != _AttachedActivitys[ProducedEventId].end())
   {
      _AttachedActivitys[ProducedEventId].erase(EraseIter);
      subRefCP(TheActivity);
   }
}

void EventProducer::produceEvent(UInt32 ProducedEventId, const EventPtr TheEvent)
{
    ActivitySet TheActivitySet(_AttachedActivitys[ProducedEventId]);
    for(ActivitySetConstItor SetItor(TheActivitySet.begin()) ; SetItor != TheActivitySet.end() ; ++SetItor)
    {
        (*SetItor)->eventProduced(TheEvent, ProducedEventId);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

EventProducer::EventProducer(const EventProducerType* TheProducerType) : _ProducerType(TheProducerType)
{
}

EventProducer::EventProducer(const EventProducer &source) : _ProducerType(source._ProducerType)
{
}

EventProducer::~EventProducer(void)
{
}

OSG_END_NAMESPACE


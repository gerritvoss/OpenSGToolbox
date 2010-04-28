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

#include "OSGConfig.h"

#include "OSGEventProducer.h"
#include <boost/bind.hpp>

#include <boost/lexical_cast.hpp>
#include "OSGContainerUtils.h"
#include "OSGContainerPtrFuncs.h"

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
    "",
    "",
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
    return SearchItor->second.size();
}

ActivityRefPtr EventProducer::getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const
{
    ActivityMapConstItor SearchItor(_AttachedActivitys.find(ProducedEventId));
    if(SearchItor == _AttachedActivitys.end())
    {
        return ActivityRefPtr();
    }
    else
    {
        if(ActivityIndex >= SearchItor->second.size())
        {
            return ActivityRefPtr();
        }
        else
        {
            ActivitySetConstItor SetItor(SearchItor->second.begin());
            for(UInt32 i(0) ; i<ActivityIndex; ++i) ++SetItor;
            return *SetItor;
        }
    }
}

UInt32 EventProducer::getNumAttachedActivities(void) const
{
    UInt32 NumAttachedActivities(0);
    for(ActivityMapConstItor MapItor(_AttachedActivitys.begin());
            MapItor != _AttachedActivitys.end();
            ++MapItor)
    {
        NumAttachedActivities += MapItor->second.size();
    }
    return NumAttachedActivities;
}

void EventProducer::detachAllActivities(void)
{
    for(UInt32 ProdEventId(1) ; ProdEventId <= getNumProducedEvents() ; ++ProdEventId)
    {
        ActivityMapItor MapItor(_AttachedActivitys.find(ProdEventId));
        if(MapItor != _AttachedActivitys.end())
        {
            //Loop through all activies attached to this Event
            for(ActivitySetItor AttachedActivityItor(MapItor->second.begin()) ;
                    AttachedActivityItor != MapItor->second.end() ;
                    ++AttachedActivityItor)
            {
                //subRefCP(*AttachedActivityItor);
            }
            MapItor->second.clear();
        }
    }
}


EventConnection EventProducer::attachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    if(TheActivity == NULL)
    {
        SWARNING << "EventProducer::attachActivity(): Cannot attach a NULL Activity." << std::endl;
    }

    if(ProducedEventId < 1 || ProducedEventId > getNumProducedEvents())
    {
        SWARNING << "EventProducer::attachActivity(): There is no ProducedEventId: " << ProducedEventId << "." << std::endl;
    }

    if(_AttachedActivitys.find(ProducedEventId) == _AttachedActivitys.end())
    {
        _AttachedActivitys[ProducedEventId] = std::set<ActivityRefPtr>();
    }

   _AttachedActivitys[ProducedEventId].insert(TheActivity);
   //addRefCP(TheActivity);

   return EventConnection(
       boost::bind(static_cast<bool (EventProducer::*)(ActivityRefPtr, UInt32) const>(&EventProducer::isActivityAttached) , this, TheActivity, ProducedEventId),
       boost::bind(static_cast<void (EventProducer::*)(ActivityRefPtr, UInt32)>(&EventProducer::detachActivity), this, TheActivity, ProducedEventId));
}

bool EventProducer::isActivityAttached(ActivityRefPtr TheActivity, UInt32 ProducedEventId) const
{
    if(ProducedEventId < 1 || ProducedEventId > getNumProducedEvents())
    {
        SWARNING << "EventProducer::isActivityAttached(): There is no ProducedEventId: " << ProducedEventId << "." << std::endl;
    }

    return _AttachedActivitys.find(ProducedEventId)->second.find(TheActivity) != _AttachedActivitys.find(ProducedEventId)->second.end();
}

void EventProducer::detachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId)
{
    if(TheActivity == NULL)
    {
        SWARNING << "EventProducer::detachActivity(): Cannot dettach a NULL Activity." << std::endl;
    }

    if(ProducedEventId < 1 || ProducedEventId > getNumProducedEvents())
    {
        SWARNING << "EventProducer::detachActivity(): There is no ProducedEventId: " << ProducedEventId << "." << std::endl;
    }

   ActivitySetItor EraseIter(_AttachedActivitys[ProducedEventId].find(TheActivity));
   if(EraseIter != _AttachedActivitys[ProducedEventId].end())
   {
      _AttachedActivitys[ProducedEventId].erase(EraseIter);
      //subRefCP(TheActivity);
   }
}

//EventListeners
UInt32 EventProducer::getNumEventListenersAttached(UInt32 ProducedEventId) const
{
    EventListenerMapConstItor SearchItor(_AttachedEventListeners.find(ProducedEventId));
    if(SearchItor == _AttachedEventListeners.end())
    {
        return 0;
    }
    return SearchItor->second.size();
}

EventListenerPtr EventProducer::getAttachedEventListener(UInt32 ProducedEventId, UInt32 EventListenerIndex) const
{
    EventListenerMapConstItor SearchItor(_AttachedEventListeners.find(ProducedEventId));
    if(SearchItor == _AttachedEventListeners.end())
    {
        return EventListenerPtr();
    }
    else
    {
        if(EventListenerIndex >= SearchItor->second.size())
        {
            return EventListenerPtr();
        }
        else
        {
            EventListenerSetConstItor SetItor(SearchItor->second.begin());
            for(UInt32 i(0) ; i<EventListenerIndex; ++i) ++SetItor;
            return *SetItor;
        }
    }
}

UInt32 EventProducer::getNumAttachedEventListeners(void) const
{
    UInt32 NumAttachedEventListeners(0);
    for(EventListenerMapConstItor MapItor(_AttachedEventListeners.begin());
            MapItor != _AttachedEventListeners.end();
            ++MapItor)
    {
        NumAttachedEventListeners += MapItor->second.size();
    }
    return NumAttachedEventListeners;
}

void EventProducer::detachAllEventListeners(void)
{
    for(UInt32 ProdEventId(1) ; ProdEventId <= getNumProducedEvents() ; ++ProdEventId)
    {
        EventListenerMapItor MapItor(_AttachedEventListeners.find(ProdEventId));
        if(MapItor != _AttachedEventListeners.end())
        {
            MapItor->second.clear();
        }
    }
}


EventConnection EventProducer::attachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId)
{
    if(TheEventListener == NULL)
    {
        SWARNING << "EventProducer::attachEventListener(): Cannot attach a NULL EventListener." << std::endl;
    }

    if(ProducedEventId < 1 || ProducedEventId > getNumProducedEvents())
    {
        SWARNING << "EventProducer::attachEventListener(): There is no ProducedEventId: " << ProducedEventId << "." << std::endl;
    }

    if(_AttachedEventListeners.find(ProducedEventId) == _AttachedEventListeners.end())
    {
        _AttachedEventListeners[ProducedEventId] = std::set<EventListenerPtr>();
    }

   _AttachedEventListeners[ProducedEventId].insert(TheEventListener);

   return EventConnection(
       boost::bind(static_cast<bool (EventProducer::*)(EventListenerPtr, UInt32) const>(&EventProducer::isEventListenerAttached) , this, TheEventListener, ProducedEventId),
       boost::bind(static_cast<void (EventProducer::*)(EventListenerPtr, UInt32)>(&EventProducer::detachEventListener), this, TheEventListener, ProducedEventId));
}

bool EventProducer::isEventListenerAttached(EventListenerPtr TheEventListener, UInt32 ProducedEventId) const
{
    if(ProducedEventId < 1 || ProducedEventId > getNumProducedEvents())
    {
        SWARNING << "EventProducer::isEventListenerAttached(): There is no ProducedEventId: " << ProducedEventId << "." << std::endl;
    }

    return _AttachedEventListeners.find(ProducedEventId)->second.find(TheEventListener) != _AttachedEventListeners.find(ProducedEventId)->second.end();
}

void EventProducer::detachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId)
{
    if(TheEventListener == NULL)
    {
        SWARNING << "EventProducer::detachEventListener(): Cannot dettach a NULL EventListener." << std::endl;
    }

    if(ProducedEventId < 1 || ProducedEventId > getNumProducedEvents())
    {
        SWARNING << "EventProducer::detachEventListener(): There is no ProducedEventId: " << ProducedEventId << "." << std::endl;
    }

   EventListenerSetItor EraseIter(_AttachedEventListeners[ProducedEventId].find(TheEventListener));
   if(EraseIter != _AttachedEventListeners[ProducedEventId].end())
   {
      _AttachedEventListeners[ProducedEventId].erase(EraseIter);
   }
}

void EventProducer::produceEvent(UInt32 ProducedEventId, const EventUnrecPtr TheEvent)
{
    ActivitySet TheActivitySet(_AttachedActivitys[ProducedEventId]);
    for(ActivitySetConstItor SetItor(TheActivitySet.begin()) ; SetItor != TheActivitySet.end() ; ++SetItor)
    {
        (*SetItor)->eventProduced(TheEvent, ProducedEventId);
    }

    EventListenerSet TheEventListenerSet(_AttachedEventListeners[ProducedEventId]);
    for(EventListenerSetConstItor SetItor(TheEventListenerSet.begin()) ; SetItor != TheEventListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->eventProduced(TheEvent, ProducedEventId);
    }
}

void EventProducer::putToStream(OutStream &outVal)
{
    bool isFirstItemWritten(true);
    //Loop through all of the Produced Event Ids
    for(UInt32 ProdEventId(1) ; ProdEventId < getNumProducedEvents() ; ++ProdEventId)
    {
        //Loop through all activies attached to this Event
        for(UInt32 AttachedActivityIndex(0) ; AttachedActivityIndex < getNumActivitiesAttached(ProdEventId) ; ++AttachedActivityIndex)
        {
            if(!isFirstItemWritten)
            {
                outVal << ";";
            }
            else
            {
                isFirstItemWritten = false;
            }
            FieldTraits<UInt32>::putToStream( ProdEventId, outVal );

            outVal << ",";
            if(getAttachedActivity(ProdEventId, AttachedActivityIndex) == NULL)
            {
                FieldTraits<UInt32>::putToStream( 0, outVal );
            }
            else
            {
                FieldTraits<UInt32>::putToStream( getAttachedActivity(ProdEventId, AttachedActivityIndex)->getId(), outVal );
            }
        }
    }
}

bool EventProducer::getFromCString(const Char8     *&inVal)
{
    detachAllActivities();

    //Loop through all of the map elelments
    const Char8 *curInString(inVal);
    const Char8 *puncLoc(NULL);

    UInt32 ProdEventId;
    FieldContainerUnrecPtr Value;
    UInt32 FieldContainerID(0);
    
    std::string ProdEventString("");
    std::string FieldContainerIDString("");

    while(curInString != NULL)
    {
        puncLoc = strchr(curInString, ',');
        if(puncLoc == NULL)
        {
            return true;
        }
        ProdEventString = std::string(curInString, puncLoc-curInString);

        //Try to cast it to a UInt32
        try
        {
            ProdEventId = boost::lexical_cast<UInt32>(ProdEventString);
            
            //Check the Method Id
            if(ProdEventId == 0 || ProdEventId > getNumProducedEvents())
            {
                SWARNING <<
                    "ERROR in EventProducer::getFromString(): Cannot attach a Activity to a produced event with id: "
                     << ProdEventId << " because the valid MethodIds for this producer are 1-" << getNumProducedEvents() << " ProducedMethods that can be attached to."
                     << std::endl;
                return false;
            }
        }
        catch(boost::bad_lexical_cast &)
        {
            //Couldn't cast it to a UInt32, try to find a produced method by that name
            ProdEventId = getProducedEventId(ProdEventString.c_str());

            if(ProdEventId == 0)
            {
                SWARNING <<
                    "ERROR in EventProducer::getFromString(): Cannot attach a Activity to a produced event with id: "
                     << ProdEventString << " because there are produced methods by that name."
                     << std::endl;
                return false;
            }
        }

        
        //Move past the , seperator
        curInString = puncLoc;
        ++curInString;
        if(curInString == NULL)
        {
            return false;
        }

        //Get the Activity attached
        puncLoc = strchr(curInString, ';');
        if(!puncLoc)
        {
            FieldContainerIDString = std::string(curInString);
        }
        else
        {
            FieldContainerIDString = std::string(curInString, puncLoc-curInString);
        }


        //Try to cast it to a UInt32
        try
        {
            FieldContainerID = boost::lexical_cast<UInt32>(FieldContainerIDString);
            
            //Check the Method Id
            if(FieldContainerID == 0)
            {
                SWARNING <<
                    "EventProducer::getFromString(): Cannot attach a NULL Activity to an EventProducer."
                     << std::endl;
                return false;
            }

            Value = FieldContainerFactory::the()->getMappedContainer(FieldContainerID);

            if(Value == NULL)
            {
                SWARNING <<
                    "ERROR in EventProducer::getFromString(): Could not find Activity referenced with Id: " << FieldContainerID <<
                    std::endl;
                return false;
            }
        }
        catch(boost::bad_lexical_cast &)
        {
            //Couldn't cast it to a UInt32, try to find a Activity by that name
            Value = getFieldContainer(FieldContainerIDString);

            if(Value == NULL)
            {
                SWARNING << "ERROR in EventProducer::getFromString(): Cannot attach a Activity to a produced event with name: "
                         << FieldContainerIDString << " because there are no Activities by that name."
                         << std::endl;
                return false;
            }
        }

        if(!Value->getType().isDerivedFrom(Activity::getClassType()))
        {
            SWARNING <<
                "ERROR in EventProducer::getFromString(): Could not attach container because FieldContainer reverenced by id: "
                 << FieldContainerID << " is of type" << Value->getType().getCName() << ", is not derived from an Activity Type."
                 << std::endl;
            return false;
        }

        //Add the Key/Value pair
        attachActivity(dynamic_pointer_cast<Activity>(Value), ProdEventId);

        //Move past the ; seperator
        curInString = puncLoc;
        if(curInString != NULL)
        {
            ++curInString;
        }
    }
    return true;
}

UInt32 EventProducer::getProducedEventId(const std::string &ProducedEventName) const
{
    const MethodDescription * MethodDesc = getProducerType().findMethodDescription(ProducedEventName);
    if(MethodDesc == NULL)
    {
        return 0;
    }
    else
    {
        return MethodDesc->getMethodId();
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


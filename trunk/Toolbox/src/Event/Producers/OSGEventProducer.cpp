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

#include <boost/lexical_cast.hpp>
#include "Util/OSGFieldContainerUtils.h"

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
                subRefCP(*AttachedActivityItor);
            }
            MapItor->second.clear();
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
       boost::bind(static_cast<bool (EventProducer::*)(ActivityPtr, UInt32) const>(&EventProducer::isActivityAttached) , this, TheActivity, ProducedEventId),
       boost::bind(static_cast<void (EventProducer::*)(ActivityPtr, UInt32)>(&EventProducer::detachActivity), this, TheActivity, ProducedEventId));
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

void EventProducer::putToString(std::string &outVal)
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
                outVal.append(";");
            }
            else
            {
                isFirstItemWritten = false;
            }
            outVal.append(TypeTraits<UInt32>::putToString( ProdEventId ));

            outVal.append(",");
            if(getAttachedActivity(ProdEventId, AttachedActivityIndex) == NullFC)
            {
                outVal.append(TypeTraits<UInt32>::putToString( 0 ));
            }
            else
            {
                outVal.append(TypeTraits<UInt32>::putToString( getAttachedActivity(ProdEventId, AttachedActivityIndex).getFieldContainerId() ));
            }
        }
    }
}

bool EventProducer::getFromString(const Char8     *&inVal)
{
    detachAllActivities();

    //Loop through all of the map elelments
    const Char8 *curInString(inVal);
    const Char8 *puncLoc(NULL);

    Int32 ProdEventId;
    FieldContainerPtr Value;
    UInt32 FieldContainerID(0);
    
    std::string ProdEventString("");
    std::string FieldContainerIDString("");

    while(curInString != NULL)
    {
        puncLoc = strchr(curInString, ',');
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
            }
            return false;
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
                    "EventProducer::getFromString(): Cannot attach a NullFC Activity to an EventProducer."
                     << std::endl;
                return false;
            }

            Value = FieldContainerFactory::the()->getMappedContainer(FieldContainerID);

            if(Value == NullFC)
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

            if(Value == NullFC)
            {
                SWARNING <<
                    "ERROR in EventProducer::getFromString(): Cannot attach a Activity to a produced event with name: "
                     << FieldContainerIDString << " because there are Activities by that name."
                     << std::endl;
            }
            return false;
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
        attachActivity(ActivityPtr::dcast(Value), ProdEventId);

        //Move past the ; seperator
        curInString = puncLoc;
        if(curInString != NULL)
        {
            ++curInString;
        }
    }
    return true;
}

UInt32 EventProducer::getProducedEventId(const Char8 *ProducedEventName) const
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


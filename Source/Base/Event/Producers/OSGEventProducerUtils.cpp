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

#include "OSGEventProducerUtils.h"

#include <boost/lexical_cast.hpp>
#include "OSGContainerUtils.h"
#include "OSGContainerPtrFuncs.h"
#include "OSGActivity.h"
#include "OSGEventDescription.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                                    events                              *
\***************************************************************************/

void putEventProducerToStream(OutStream &outVal, const ReflexiveContainer& container)
{
    bool isFirstItemWritten(true);
    //Loop through all of the Produced Event Ids
    for(UInt32 ProdEventId(1) ; ProdEventId <= container.getNumEvents() ; ++ProdEventId)
    {
        //Loop through all activies attached to this Event
        /*for(UInt32 AttachedActivityIndex(0) ; AttachedActivityIndex < getNumActivitiesAttached(ProdEventId) ; ++AttachedActivityIndex)
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
        }*/
    }
}

bool getEventProducerFromCString(const Char8     *&inVal, ReflexiveContainer& container)
{
    container.disconnectAll();

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
            
            //Check the Event Id
            if(ProdEventId == 0 || ProdEventId > container.getNumEvents())
            {
                SWARNING <<
                    "ERROR in EventProducer::getFromString(): Cannot attach a Activity to a produced event with id: "
                     << ProdEventId << " because the valid EventIds for this producer are 1-" << container.getNumEvents() << " ProducedEvents that can be attached to."
                     << std::endl;
                return false;
            }
        }
        catch(boost::bad_lexical_cast &)
        {
            //Couldn't cast it to a UInt32, try to find a produced event by that name
            ProdEventId = container.getEventDescription(ProdEventString.c_str())->getEventId();

            if(ProdEventId == 0)
            {
                SWARNING <<
                    "ERROR in EventProducer::getFromString(): Cannot attach a Activity to a produced event with id: "
                     << ProdEventString << " because there are produced events by that name."
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
            
            //Check the Event Id
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
        container.attachActivity(ProdEventId, dynamic_pointer_cast<Activity>(Value));

        //Move past the ; seperator
        curInString = puncLoc;
        if(curInString != NULL)
        {
            ++curInString;
        }
    }
    return true;
}

OSG_END_NAMESPACE


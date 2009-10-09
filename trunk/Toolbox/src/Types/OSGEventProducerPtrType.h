/*---------------------------------------------------------------------------*\
 *                         OpenSG Toolbox Toolbox                            *
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
#ifndef _OSG_TOOLBOX_EVENT_PRODUCER_PTR_TYPE_H_
#define _OSG_TOOLBOX_EVENT_PRODUCER_PTR_TYPE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGFieldType.h>
#include <OpenSG/OSGBaseFieldDataType.h>

#include <OpenSG/OSGSField.h>
#include <OpenSG/OSGMField.h>

#include "Event/Producers/OSGEventProducer.h"

OSG_BEGIN_NAMESPACE

//typedef boost::filesystem::basic_path<std::string, boost::filesystem::path_traits> EventProducerPtr;

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldDataTraits<EventProducerPtr> : 
    public FieldTraitsRecurseBase<EventProducerPtr>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static const Char8          *getSName     (void) { return "SFEventProducerPtr"; }
    static const Char8          *getMName     (void) { return "MFEventProducerPtr"; }

    // Create a default instance of the class, needed for Field creation
    static EventProducerPtr       getDefault   (void) { return EventProducerPtr();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const EventProducerPtr   &inVal,
                                  std::string &outVal)
    {
        bool isFirstItemWritten(true);
		//Loop through all of the Produced Event Ids
        for(UInt32 ProdEventId(1) ; ProdEventId < inVal->getNumProducedEvents() ; ++ProdEventId)
        {
            //Loop through all activies attached to this Event
            for(UInt32 AttachedActivityIndex(0) ; AttachedActivityIndex < inVal->getNumActivitiesAttached(ProdEventId) ; ++AttachedActivityIndex)
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
                if(inVal->getAttachedActivity(ProdEventId, AttachedActivityIndex) == NullFC)
                {
                    outVal.append(TypeTraits<UInt32>::putToString( 0 ));
                }
                else
                {
                    outVal.append(TypeTraits<UInt32>::putToString( inVal->getAttachedActivity(ProdEventId, AttachedActivityIndex).getFieldContainerId() ));
                }
            }
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      EventProducerPtr  &outVal,
                              const Char8     *&inVal)
    {
        outVal->detachAllActivities();

        //Loop through all of the map elelments
        const Char8 *curInString(inVal);

        Int32 ProdEventId;
        FieldContainerPtr Value;
        UInt32 FieldContainerID(0);
        while(curInString != NULL)
        {
            //Get the key value
            ProdEventId = TypeTraits<UInt32>::getFromString( curInString );
            if(ProdEventId > outVal->getNumProducedEvents())
            {
                SWARNING <<
                    "ERROR in EventProducerPtrType::getFromString(): Cannot attach a Activity to a produced event with id: "
                     << ProdEventId << " because there are only " << outVal->getNumProducedEvents() << " ProducedMethods that can be attached to."
                     << std::endl;
                return false;
            }
            
            //Move past the ; seperator
            curInString = strchr(curInString, ',');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }

            //Get the map value
            FieldContainerID = TypeTraits<UInt32>::getFromString(curInString);
            Value = FieldContainerFactory::the()->getMappedContainer(FieldContainerID);
            if(Value == NullFC)
            {
                SWARNING <<
                    "ERROR in EventProducerPtrType::getFromString(): Could not find Activity referenced with Id: " << FieldContainerID <<
                    std::endl;
                return false;
            }
            if(Value->getType().isDerivedFrom(Activity::getClassType()))
            {
                SWARNING <<
                    "ERROR in EventProducerPtrType::getFromString(): Could not attach container because FieldContainer reverenced by id: "
                     << FieldContainerID << " is derived not derived from an Activity Type."
                     << std::endl;
                return false;
            }

            //Add the Key/Value pair
            outVal->attachActivity(ActivityPtr::dcast(Value), ProdEventId);

            //Move past the ; seperator
            curInString = strchr(curInString, ';');
            if(curInString != NULL)
            {
                ++curInString;
            }
        }
	    return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const EventProducerPtr & obj)
    {
		return obj->getNumAttachedActivities() * 2 * sizeof(UInt32);
    }

    static UInt32 getBinSize (const EventProducerPtr *pObjectStore, UInt32 uiNumObjects)
    {
        UInt32 size = 0;

        // defaut: individual field sizes
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const EventProducerPtr         &obj)
    {
        UInt32 id;
        UInt32 uiNumAttachedActivities = obj->getNumAttachedActivities();

        //Copy the number of Attached Activities
        bdh.putValue(uiNumAttachedActivities);  //Number of Key/Value pairs

		//Loop through all of the Produced Event Ids
        for(UInt32 ProdEventId(1) ; ProdEventId < obj->getNumProducedEvents() ; ++ProdEventId)
        {
            //Loop through all activies attached to this Event
            for(UInt32 AttachedActivityIndex(0) ; AttachedActivityIndex < obj->getNumActivitiesAttached(ProdEventId) ; ++AttachedActivityIndex)
            {
                id = obj->getAttachedActivity(ProdEventId,AttachedActivityIndex).getFieldContainerId();
                
                bdh.putValue(ProdEventId);
                bdh.putValue(id);
            }
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const EventProducerPtr         *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(bdh, pObjectStore[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            EventProducerPtr         &obj)
    {
        FieldContainerPtr fcp;

        UInt32 ProdEventId;
        UInt32 id;
        UInt32 size;

        bdh.getValue(size);

        obj->detachAllActivities();

        for(UInt32 i = 0; i < size; ++i)
        {
            bdh.getValue(ProdEventId);
            bdh.getValue(id);

            fcp = FieldContainerFactory::the()->getMappedContainer(id);

            obj->attachActivity(ActivityPtr::dcast(fcp), ProdEventId);
        }
    }

    static void copyFromBin(BinaryDataHandler &bdh,
                            EventProducerPtr         *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(bdh, pObjectStore[i]);
        }
    }
};

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<EventProducerPtr> SFEventProducerPtr;
typedef MField<EventProducerPtr> MFEventProducerPtr;


// Windows makes everything a lot more complicated than it needs to be,
// Thus you have to include the following Macro to make Windows happy.
// This is the variant for types which are directly used in an application,
// if the type should be included in a DLL, things need to be a little
// different.

// The define makes sure that the code is only included when the corresponding
// source is not compiled
#ifndef OSG_COMPILEPATHTYPEINST
OSG_DLLEXPORT_DECL1(SField, EventProducerPtr, OSG_TOOLBOXLIB_DLLTMPLMAPPING)
#endif

#ifndef OSG_COMPILEPATHTYPEINST
OSG_DLLEXPORT_DECL1(MField, EventProducerPtr, OSG_TOOLBOXLIB_DLLTMPLMAPPING)
#endif


OSG_END_NAMESPACE

#endif /* _OSG_TOOLBOX_EVENT_PRODUCER_PTR_TYPE_H_ */



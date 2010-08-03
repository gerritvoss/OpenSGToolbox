/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
#ifndef _OSG_EVENT_PRODUCER_PTR_TYPE_H_
#define _OSG_EVENT_PRODUCER_PTR_TYPE_H_

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGFieldType.h"
#include "OSGBaseFieldTraits.h"
#include "OSGDataType.h"

#include "OSGSField.h"
#include "OSGMField.h"

#include "OSGEventProducer.h"

OSG_BEGIN_NAMESPACE

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldTraits<EventProducerPtr> : public FieldTraitsTemplateBase<EventProducerPtr>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    typedef FieldTraits<EventProducerPtr>  Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING DataType       &getType      (void) { return _type;          }

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
    static void putToStream(const EventProducerPtr   &inVal,
                                  OutStream &outVal)
    {
        inVal->putToStream(outVal);
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromCString(      EventProducerPtr  &outVal,
                              const Char8     *&inVal)
    {
        return outVal->getFromCString(inVal);
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
                id = obj->getAttachedActivity(ProdEventId,AttachedActivityIndex)->getId();
                
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
        FieldContainerUnrecPtr fcp;

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

            obj->attachActivity(dynamic_pointer_cast<Activity>(fcp), ProdEventId);
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

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<EventProducerPtr> SFEventProducerPtr;
typedef MField<EventProducerPtr> MFEventProducerPtr;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFEventProducerPtr : public SField<EventProducerPtr> {};
struct MFEventProducerPtr : public MField<EventProducerPtr> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSG_EVENT_PRODUCER_PTR_TYPE_H_ */



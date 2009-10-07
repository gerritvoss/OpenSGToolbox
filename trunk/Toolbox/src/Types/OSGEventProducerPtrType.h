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
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      EventProducerPtr  &outVal,
                              const Char8     *&inVal)
    {
	    return false;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const EventProducerPtr & obj)
    {
		return 0;
    }

    static UInt32 getBinSize (const EventProducerPtr *obj, UInt32 num)
    {
        //Size:
        return 0;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const EventProducerPtr         &obj)
    {
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const EventProducerPtr         *objs,
                                UInt32             num)
    {
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            EventProducerPtr         &obj)
    {
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            EventProducerPtr         *objs,
                            UInt32             num)
    {
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



/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
#ifndef _OSG_TOOLBOX_FIELDCONTAINER_MAP_TYPE_H_
#define _OSG_TOOLBOX_FIELDCONTAINER_MAP_TYPE_H_
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
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldContainerFactory.h>

#include <OpenSG/OSGSField.h>
#include <OpenSG/OSGMField.h>

#include <map>

OSG_BEGIN_NAMESPACE

typedef std::map<Int32, FieldContainerPtr>  FieldContainerMap;

template <>
struct FieldDataTraits<FieldContainerMap> : 
    public FieldTraitsRecurseBase<FieldContainerMap>
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
    static char     *getSName(void) { return "SFFieldContainerMap"; }
    static char     *getMName(void) { return "MFFieldContainerMap"; }

    // Create a default instance of the class, needed for Field creation
    static FieldContainerMap       getDefault   (void) { return FieldContainerMap();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion
    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const FieldContainerMap   &inVal,
                                  std::string &outVal)
    {
		//Loop through all of the map elelments
        FieldContainerMap::const_iterator Itor(inVal.begin());
        std::string tempOut;
        for(; Itor != inVal.end(); ++Itor)
        {
			if(Itor != inVal.begin())
			{
				outVal.append(";");
			}
            outVal.append(TypeTraits<FieldContainerMap::key_type>::putToString( Itor->first ));

            outVal.append(",");
			if(Itor->second == NullFC)
			{
				outVal.append(TypeTraits<UInt32>::putToString( 0 ));
			}
			else
			{
				outVal.append(TypeTraits<UInt32>::putToString( Itor->second.getFieldContainerId() ));
			}
            outVal.append(tempOut);
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      FieldContainerMap  &outVal,
                              const Char8     *&inVal)
    {
        outVal.clear();

		//Loop through all of the map elelments
        const Char8 *curInString(inVal);

		Int32 Key;
		FieldContainerPtr Value;
		UInt32 FieldContainerID(0);
        while(curInString != NULL)
        {
			//Get the key value
			Key = TypeTraits<FieldContainerMap::key_type>::getFromString( curInString );
			
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
					"ERROR in FieldContainerMap::getFromString(): Could not find Container referenced with Id: " << FieldContainerID <<
					std::endl;
			}

			//Add the Key/Value pair
            outVal[Key] = Value;

			//Move past the ; seperator
			curInString = strchr(curInString, ';');
			if(curInString != NULL)
			{
				++curInString;
			}
        }
	}
    
    // Binary conversion
    static UInt32 getBinSize(const FieldContainerMap &oObject)
    {

        UInt32 uiNumPublicObjects = oObject.size();

        return sizeof(UInt32) +  // Number of elements in the map 
               uiNumPublicObjects * (sizeof(Int32) + sizeof(UInt32));
    }

    static UInt32 getBinSize(const FieldContainerMap *pObjectStore,
                                   UInt32         uiNumObjects)
    {
        UInt32 size = 0;

        // defaut: individual field sizes
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldContainerMap     &pObject)
    {
        UInt32 id;
        UInt32 uiNumPublicObjects = pObject.size();

        pMem.putValue(uiNumPublicObjects);  //Number of Key/Value pairs

        FieldContainerMap::const_iterator mapIt  = pObject.begin();
        FieldContainerMap::const_iterator mapEnd = pObject.end();

        for(; mapIt != mapEnd; ++mapIt)
        {
            id = mapIt->second.getFieldContainerId();
            
            pMem.putValue(mapIt->first);  //Key
            pMem.putValue(id); //Value = Field Container ID
        }
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldContainerMap *pObjectStore,
                                UInt32         uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldContainerMap     &pObject)
    {
        FieldContainerPtr fcp;

        Int32 key;
        UInt32 id;
        UInt32 size;

        pMem.getValue(size);

        pObject.clear();

        for(UInt32 i = 0; i < size; ++i)
        {
            pMem.getValue(key);
            pMem.getValue(id);

            fcp = FieldContainerFactory::the()->getMappedContainer(id);

            ((FieldContainerPtr &) pObject[key]) = fcp;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldContainerMap     *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<FieldContainerMap> SFFieldContainerMap;
typedef MField<FieldContainerMap> MFFieldContainerMap;


// Windows makes everything a lot more complicated than it needs to be,
// Thus you have to include the following Macro to make Windows happy.
// This is the variant for types which are directly used in an application,
// if the type should be included in a DLL, things need to be a little
// different.

// The define makes sure that the code is only included when the corresponding
// source is not compiled
#ifndef OSG_COMPILEFIELDCONTAINERMAPTYPEINST
OSG_DLLEXPORT_DECL1(SField, FieldContainerMap, OSG_TOOLBOXLIB_DLLTMPLMAPPING)
#endif

#ifndef OSG_COMPILEFIELDCONTAINERMAPTYPEINST
OSG_DLLEXPORT_DECL1(MField, FieldContainerMap, OSG_TOOLBOXLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#define OSG_TOOLBOX_FIELDCONTAINER_MAP_TYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_TOOLBOX_FIELDCONTAINER_MAP_TYPE_H_ */



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
#ifndef _OSG_INT32_TO_STRING_MAP_TYPE_H_
#define _OSG_INT32_TO_STRING_MAP_TYPE_H_
#ifdef __sgi
#pragma once
#endif

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

#include <string>
#include <map>

OSG_BEGIN_NAMESPACE

typedef std::map<Int32, std::string> Int32ToStringMap;

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldTraits<Int32ToStringMap> : public FieldTraitsTemplateBase<Int32ToStringMap>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    typedef FieldTraits<std::string>  Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static const Char8          *getSName     (void) { return "SFInt32ToStringMap"; }
    static const Char8          *getMName     (void) { return "MFInt32ToStringMap"; }

    // Create a default instance of the class, needed for Field creation
    static Int32ToStringMap       getDefault   (void) { return Int32ToStringMap();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToStream(const Int32ToStringMap   &inVal,
            OutStream &outVal)
    {
		//Put the Size of the map
        FieldTraits<UInt32>::putToStream(static_cast<UInt32>(inVal.size()),outVal);

		//Loop through all of the map elelments
        Int32ToStringMap::const_iterator Itor(inVal.begin());
        for(; Itor != inVal.end(); ++Itor)
        {
            outVal << ",";
            FieldTraits<Int32ToStringMap::key_type>::putToStream( Itor->first,outVal );

            outVal << ",";
            FieldTraits<Int32ToStringMap::mapped_type>::putToStream( Itor->second,outVal );
        }
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromCString(      Int32ToStringMap  &outVal,
            const Char8     *&inVal)
    {
		//Get Size of the map
        UInt32 Size(0);
        if(sscanf(inVal,"%d", &Size) != 1)
        {
        	return false;
        }

        outVal.clear();

		//Loop through all of the map elelments
        const Char8 *curInString(inVal);

		Int32 Key;
		std::string Value;
        for(UInt32 i(0) ; i<Size ; ++i)
        {
			//Move past the ; seperator
			curInString = strchr(curInString, ',');
			++curInString;
			if(curInString == NULL)
			{
				return false;
			}

			//Get the key value
			FieldTraits<Int32ToStringMap::key_type>::getFromCString(Key, curInString );
			
			//Move past the ; seperator
            curInString = strchr(curInString, ',');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }

			//Move past the ; seperator
            curInString = strchr(curInString, '\"');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }
			//Get the map value

			Value.assign(curInString, (strchr(curInString, '\"') - curInString));

			//Move past the map value
            curInString = strchr(curInString, '\"');
            ++curInString;
            //if(curInString == NULL)
            //{
            //    return false;
            //}

			//Add the Key/Value pair
            outVal[Key] = Value;
        }
        
        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const Int32ToStringMap & obj)
    {
        //Size:
        //Size of a Int32 -> number of items in the Map
        //Sum of all the sizes of the strings
		UInt32 StringSizeSum(0);
		Int32ToStringMap::const_iterator Itor(obj.begin());
		for( ; Itor != obj.end() ; ++Itor)
		{
			StringSizeSum += FieldTraits<std::string>::getBinSize(Itor->second);
		}

        return sizeof(UInt32) + obj.size()*sizeof(Int32) + StringSizeSum;
    }

    static UInt32 getBinSize (const Int32ToStringMap *obj, UInt32 num)
    {
        //Size:
		//Sum of all the objs
		UInt32 SizeSum(0);
    	for(UInt32 i = 0; i < num; ++i)
        {
            SizeSum += getBinSize(obj[i]);
        }
        return SizeSum;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const Int32ToStringMap         &obj)
    {
        //Number of items in the map
        bdh.putValue(static_cast<UInt32>(obj.size()));

		//Loop through all of the map elelments
        Int32ToStringMap::const_iterator Itor(obj.begin());
        for(; Itor != obj.end(); ++Itor)
        {
			bdh.putValue(static_cast<Int32ToStringMap::key_type>(Itor->first));

			bdh.putValue(static_cast<Int32ToStringMap::mapped_type>(Itor->second));
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const Int32ToStringMap         *objs,
                                UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyToBin(bdh, objs[i]);
        }
    }
    

    // Copy the object from the BinaryDataHandler
    // the BDH has a number of methods to get a simple type from the stream
    // just use those and use the same order you used to write them out.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyFromBin(BinaryDataHandler &bdh, 
                            Int32ToStringMap         &obj)
    {
        //Number of items in the list
        UInt32 Size(0);
        bdh.getValue(Size);

        obj.clear();


		Int32 Key;
		std::string Value;

		//Loop through all of the map elelments
        for(UInt32 i(0) ; i<Size ; ++i)
        {
			bdh.getValue(Key);
            FieldTraits<Int32ToStringMap::mapped_type>::copyFromBin( bdh, Value );

			obj[Key] = Value;
        }
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            Int32ToStringMap         *objs,
                            UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<Int32ToStringMap> SFInt32ToStringMap;
typedef MField<Int32ToStringMap> MFInt32ToStringMap;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFInt32ToStringMap : public SField<Int32ToStringMap> {};
struct MFInt32ToStringMap : public MField<Int32ToStringMap> {};

#endif // these are the doxygen hacks


OSG_END_NAMESPACE

#endif /* _OSG_TOOLBOX_STRING_MAP_TYPE_H_ */



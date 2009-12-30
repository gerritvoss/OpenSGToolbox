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
#ifndef _OSG_STRING_TO_UINT32_MAP_TYPE_H_
#define _OSG_STRING_TO_UINT32_MAP_TYPE_H_
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

typedef std::map<std::string, UInt32> StringToUInt32Map;

// The FieldTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldTraits<StringToUInt32Map> : public FieldTraitsTemplateBase<StringToUInt32Map>
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
    static const Char8          *getSName     (void) { return "SFStringToUInt32Map"; }
    static const Char8          *getMName     (void) { return "MFStringToUInt32Map"; }

    // Create a default instance of the class, needed for Field creation
    static StringToUInt32Map       getDefault   (void) { return StringToUInt32Map();   }


    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToStream(const StringToUInt32Map   &inVal,
            OutStream &outVal)
    {
        //Put the Size of the map
        FieldTraits<UInt32>::putToStream(static_cast<UInt32>(inVal.size()),outVal);

        //Loop through all of the map elelments
        StringToUInt32Map::const_iterator Itor(inVal.begin());
        for(; Itor != inVal.end(); ++Itor)
        {
            outVal << "," << Itor->first << ",";
            FieldTraits<StringToUInt32Map::mapped_type>::putToStream( Itor->second,outVal );
        }
    }

    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromCString(      StringToUInt32Map  &outVal,
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

        std::string Key;
        UInt32 Value;
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            //Move past the , seperator
            curInString = strchr(curInString, ',');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }

            //Move past the " seperator
            //curInString = strchr(curInString, '\"');
            //++curInString;
            if(curInString == NULL)
            {
                return false;
            }
            //Get the key value

            Key.assign(curInString, (strchr(curInString, ',') - curInString));

            //Move past the map value
            //curInString = strchr(curInString, '\"');
            //++curInString;
            
            //Move past the , seperator
            curInString = strchr(curInString, ',');
            ++curInString;
            if(curInString == NULL)
            {
                return false;
            }


            //Get the map value
            FieldTraits<StringToUInt32Map::mapped_type>::getFromCString(Value, curInString );

            //Add the Key/Value pair
            outVal[Key] = Value;
        }

        return true;
    }

    // Binary conversion

    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const StringToUInt32Map & obj)
    {
        //Size:
        //Size of a UInt32 -> number of items in the Map
        //Sum of all the sizes of the strings
        UInt32 StringSizeSum(0);
        StringToUInt32Map::const_iterator Itor(obj.begin());
        for( ; Itor != obj.end() ; ++Itor)
        {
            StringSizeSum += FieldTraits<std::string>::getBinSize(Itor->first);
        }

        return sizeof(UInt32) + obj.size()*sizeof(UInt32) + StringSizeSum;
    }

    static UInt32 getBinSize (const StringToUInt32Map *obj, UInt32 num)
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
            const StringToUInt32Map         &obj)
    {
        //Number of items in the map
        bdh.putValue(static_cast<UInt32>(obj.size()));

        //Loop through all of the map elelments
        StringToUInt32Map::const_iterator Itor(obj.begin());
        for(; Itor != obj.end(); ++Itor)
        {
            bdh.putValue(static_cast<StringToUInt32Map::key_type>(Itor->first));

            bdh.putValue(static_cast<StringToUInt32Map::mapped_type>(Itor->second));
        }
    }

    static void copyToBin(      BinaryDataHandler &bdh,
            const StringToUInt32Map         *objs,
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
            StringToUInt32Map         &obj)
    {
        //Number of items in the list
        UInt32 Size(0);
        bdh.getValue(Size);

        obj.clear();


        std::string Key;
        UInt32 Value;

        //Loop through all of the map elelments
        for(UInt32 i(0) ; i<Size ; ++i)
        {
            FieldTraits<StringToUInt32Map::key_type>::copyFromBin( bdh, Key );
            bdh.getValue(Value);

            obj[Key] = Value;
        }
    }
    static void copyFromBin(BinaryDataHandler &bdh,
            StringToUInt32Map         *objs,
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

typedef SField<StringToUInt32Map> SFStringToUInt32Map;
typedef MField<StringToUInt32Map> MFStringToUInt32Map;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFStringToUInt32Map : public SField<StringToUInt32Map> {};
struct MFStringToUInt32Map : public MField<StringToUInt32Map> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSG_STRING_TO_UINT32_MAP_TYPE_H_ */



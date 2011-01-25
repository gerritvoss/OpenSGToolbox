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

// Source file for new Field type

// This define is only set in this source file. It switches the
// Windows-specific declarations in the header for compiling the Field, 
// not for using it.
#define OSG_COMPILEINT32TOSTRINGMAPTYPEINST

// You need this in every OpenSG file
#include "OSGInt32ToStringMapType.h"

#include "OSGSField.ins"
#include "OSGMField.ins"

// The new field type include
#include "OSGFieldContainer.h"
#include "OSGFieldType.h"
#include "OSGBaseFieldTraits.h"
#include "OSGDataType.h"

OSG_BEGIN_NAMESPACE

// This is where the DataType for the new Fieldtype is defined.
// The parameters are the name of the type and the name of the parent type
DataType FieldTraits<Int32ToStringMap>::_type("Int32ToStringMap", "BaseType");

// These macros instantiate the necessary template methods for the fields
OSG_FIELDTRAITS_GETTYPE (        Int32ToStringMap)
OSG_FIELD_DLLEXPORT_DEF1(SField, Int32ToStringMap)
OSG_FIELD_DLLEXPORT_DEF1(MField, Int32ToStringMap)

// Output inVal into outVal
// the exact mapping doesn't matter, 
// Our recommendation is to output as a string, 
// i.e. start and stop with ", as this simplifies integration into the
// OSG Loader.
void FieldTraits<Int32ToStringMap>::putToStream(const Int32ToStringMap   &inVal,
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
bool FieldTraits<Int32ToStringMap>::getFromCString(      Int32ToStringMap  &outVal,
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
UInt32 FieldTraits<Int32ToStringMap>::getBinSize(const Int32ToStringMap & obj)
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

UInt32 FieldTraits<Int32ToStringMap>::getBinSize (const Int32ToStringMap *obj, UInt32 num)
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
void FieldTraits<Int32ToStringMap>::copyToBin(      BinaryDataHandler &bdh, 
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

void FieldTraits<Int32ToStringMap>::copyToBin(      BinaryDataHandler &bdh,
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
void FieldTraits<Int32ToStringMap>::copyFromBin(BinaryDataHandler &bdh, 
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
void FieldTraits<Int32ToStringMap>::copyFromBin(BinaryDataHandler &bdh,
                                                Int32ToStringMap         *objs,
                                                UInt32             num)
{
    for(UInt32 i = 0; i < num; ++i)
    {
        copyFromBin(bdh, objs[i]);
    }
}

OSG_END_NAMESPACE


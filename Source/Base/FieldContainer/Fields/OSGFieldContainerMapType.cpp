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
#define OSG_COMPILEFIELDCONTAINERMAPTYPEINST

// You need this in every OpenSG file
#include "OSGField.h"

#include "OSGSField.h"
#include "OSGSField.ins"

#include "OSGMField.h"
#include "OSGMField.ins"

// The new field type include
#include "OSGFieldContainerMapType.h"

OSG_BEGIN_NAMESPACE

// This is where the DataType for the new Fieldtype is defined.
// The parameters are the name of the type and the name of the parent type
DataType FieldTraits<FieldContainerMap>::_type("FieldContainerMap", "BaseType");

// These macros instantiate the necessary template methods for the fields
OSG_FIELD_DLLEXPORT_DEF1(SField, FieldContainerMap        )
OSG_FIELD_DLLEXPORT_DEF1(MField, FieldContainerMap        )

void FieldTraits<FieldContainerMap>::putToStream(const FieldContainerMap   &inVal,
                                                 OutStream &outVal)
{
    //Loop through all of the map elelments
    FieldContainerMap::const_iterator Itor(inVal.begin());
    for(; Itor != inVal.end(); ++Itor)
    {
        if(Itor != inVal.begin())
        {
            outVal << ",";
        }
        FieldTraits<FieldContainerMap::key_type>::putToStream( Itor->first,outVal );

        outVal << ",";
        if(Itor->second == NULL)
        {
            FieldTraits<UInt32>::putToStream( 0,outVal );
        }
        else
        {
            FieldTraits<UInt32>::putToStream( Itor->second->getId(),outVal );
        }
    }
}

void FieldTraits<FieldContainerMap>::putToStream(const FieldContainerMap   &inVal,
                                                 OutStream &outVal,
                                                 const ContainerIdMapper& IDMap)
{
    //Loop through all of the map elelments
    FieldContainerMap::const_iterator Itor(inVal.begin());
    for(; Itor != inVal.end(); ++Itor)
    {
        if(Itor != inVal.begin())
        {
            outVal << ",";
        }
        FieldTraits<FieldContainerMap::key_type>::putToStream(IDMap.map(Itor->first),outVal );

        outVal << ",";
        if(Itor->second == NULL)
        {
            FieldTraits<UInt32>::putToStream( 0,outVal );
        }
        else
        {
            FieldTraits<UInt32>::putToStream(IDMap.map(Itor->second->getId()),
                                              outVal );
        }
    }
}

// Setup outVal from the contents of inVal
// For complicated classes it makes sense to implement this function
// as a class method and just call that from here  
bool FieldTraits<FieldContainerMap>::getFromCString(      FieldContainerMap  &outVal,
                                                          const Char8     *&inVal)
{
    outVal.clear();

    //Loop through all of the map elelments
    const Char8 *curInString(inVal);

    Int32 Key;
    FieldContainerUnrecPtr Value;
    UInt32 FieldContainerID(0);
    while(curInString != NULL)
    {
        //Get the key value
        /*! \todo This is a hack so the Constraints field of SpringLayout loads
         * correctly */
        FieldTraits<FieldContainerMap::key_type>::getFromCString(Key, curInString );
        Value = FieldContainerFactory::the()->getMappedContainer(Key);
        if(Value != NULL)
        {
            Key = Value->getId();
        }

        //Move past the ; seperator
        curInString = strchr(curInString, ',');
        ++curInString;
        if(curInString == NULL)
        {
            return false;
        }

        //Get the map value
        FieldTraits<UInt32>::getFromCString(FieldContainerID, curInString);
        Value = FieldContainerFactory::the()->getMappedContainer(FieldContainerID);
        if(Value == NULL)
        {
            SWARNING <<
                "ERROR in FieldContainerMap::getFromCString(): Could not find Container referenced with Id: " << FieldContainerID <<
                                                               std::endl;
        }

        //Add the Key/Value pair
        outVal[Key] = Value;

        //Move past the ; seperator
        curInString = strchr(curInString, ',');
        if(curInString != NULL)
        {
            ++curInString;
        }
    }
    return true;
}

// Binary conversion
UInt32 FieldTraits<FieldContainerMap>::getBinSize(const FieldContainerMap &oObject)
{

    UInt32 uiNumPublicObjects = oObject.size();

    return sizeof(UInt32) +  // Number of elements in the map 
        uiNumPublicObjects * (sizeof(Int32) + sizeof(UInt32));
}

UInt32 FieldTraits<FieldContainerMap>::getBinSize(const FieldContainerMap *pObjectStore,
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

void FieldTraits<FieldContainerMap>::copyToBin(      BinaryDataHandler &pMem, 
                                               const FieldContainerMap &pObject)
{
    UInt32 id;
    UInt32 uiNumPublicObjects = pObject.size();

    pMem.putValue(uiNumPublicObjects);  //Number of Key/Value pairs

    FieldContainerMap::const_iterator mapIt  = pObject.begin();
    FieldContainerMap::const_iterator mapEnd = pObject.end();

    for(; mapIt != mapEnd; ++mapIt)
    {
        id = mapIt->second->getId();

        pMem.putValue(mapIt->first);  //Key
        pMem.putValue(id); //Value = Field Container ID
    }
}

void FieldTraits<FieldContainerMap>::copyToBin(      BinaryDataHandler &pMem, 
                                                     const FieldContainerMap *pObjectStore,
                                                     UInt32         uiNumObjects)
{
    for(UInt32 i = 0; i < uiNumObjects; ++i)
    {
        copyToBin(pMem, pObjectStore[i]);
    }
}

void FieldTraits<FieldContainerMap>::copyFromBin(BinaryDataHandler &pMem, 
                                                 FieldContainerMap     &pObject)
{
    FieldContainerUnrecPtr fcp;

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

        pObject[key] = fcp;
    }
}

void FieldTraits<FieldContainerMap>::copyFromBin(BinaryDataHandler &pMem, 
                                                 FieldContainerMap     *pObjectStore,
                                                 UInt32             uiNumObjects)
{
    for(UInt32 i = 0; i < uiNumObjects; ++i)
    {
        copyFromBin(pMem, pObjectStore[i]);
    }
}

OSG_END_NAMESPACE


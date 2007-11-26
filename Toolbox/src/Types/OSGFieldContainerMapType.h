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

#include <OpenSG/OSGSField.h>
#include <OpenSG/OSGMField.h>

#include <map>

OSG_BEGIN_NAMESPACE

typedef std::map<Int32, FieldContainerPtr>  FieldContainerMap;

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

template <>
struct FieldTraitsRecurseMapper<FieldContainerMap, false> : 
    public FieldTraitsRecurseBase<FieldContainerMap>
{
    enum                    { bHasParent        = 0x00   };

    static UInt32 getBinSize(const FieldContainerMap &oObject)
    {
        //FieldContainerMap::const_iterator mapIt  = oObject.begin();
        //FieldContainerMap::const_iterator mapEnd = oObject.end();

        UInt32 uiNumPublicObjects = oObject.size();

        /*while(mapIt != mapEnd)
        {
            //if(mapIt->second->getInternal().getValue() == false)
            //{
                ++uiNumPublicObjects;
            //}

            ++mapIt;
        }*/

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

        /*FieldContainerMap::const_iterator mapIt  = pObject.begin();
        FieldContainerMap::const_iterator mapEnd = pObject.end();

        while(mapIt != mapEnd)
        {
            if(mapIt->second->getInternal().getValue() == false)
            {
                ++uiNumPublicObjects;
            }

            ++mapIt;
        }*/

        pMem.putValue(uiNumPublicObjects);

        FieldContainerMap::const_iterator mapIt  = pObject.begin();
        FieldContainerMap::const_iterator mapEnd = pObject.end();

        for(; mapIt != mapEnd; ++mapIt)
        {
            //if(mapIt->second->getInternal().getValue() == false)
            //{
                id      = mapIt->second.getFieldContainerId();
                
                pMem.putValue(mapIt->first);
                pMem.putValue(id);
            //}
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

#if !defined(OSG_DOC_DEV_TRAITS)

#endif

#if !defined(OSG_DOC_DEV_TRAITS)

#endif

template <>
struct OSG_TOOLBOXLIB_DLLMAPPING FieldDataTraits<FieldContainerMap> : 
    public FieldTraitsRecurseMapper<FieldContainerMap, false>
{
    static DataType                  _type;

    enum                            { StringConvertable = 0x01  };
    enum                            { bHasParent        = 0x00  };

    static DataType &getType (void) { return _type;             }
    static char     *getSName(void) { return "SFFieldContainerMap"; }
    static char     *getMName(void) { return "MFFieldContainerMap"; }

    static bool        getFromString(      FieldContainerMap  &,
                                     const Char8         *&)
    {
        return false;
    }

    static void      putToString    (const FieldContainerMap &,
                                           std::string   &outStr)
    {
        outStr.assign("FieldContainerMap");
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

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSG_TOOLBOX_FIELDCONTAINER_MAP_TYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_TOOLBOX_FIELDCONTAINER_MAP_TYPE_H_ */

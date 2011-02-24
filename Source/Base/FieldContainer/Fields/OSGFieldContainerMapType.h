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
#ifndef _OSG_FIELDCONTAINER_MAP_TYPE_H_
#define _OSG_FIELDCONTAINER_MAP_TYPE_H_
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

#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainer.h"
#include "OSGContainerIdMapper.h"

#include <string>
#include <map>

OSG_BEGIN_NAMESPACE

typedef std::map<Int32, FieldContainerRecPtr>  FieldContainerMap;

// The FieldTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldTraits<FieldContainerMap> : public FieldTraitsTemplateBase<FieldContainerMap>
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
    static const Char8          *getSName     (void) { return "SFFieldContainerMap"; }
    static const Char8          *getMName     (void) { return "MFFieldContainerMap"; }

    // Create a default instance of the class, needed for Field creation
    static FieldContainerMap       getDefault   (void) { return FieldContainerMap();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion
    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static OSG_BASE_DLLMAPPING
        void putToStream(const FieldContainerMap   &inVal,
                         OutStream &outVal);

    static OSG_BASE_DLLMAPPING
        void putToStream(const FieldContainerMap   &inVal,
                         OutStream &outVal,
                         const ContainerIdMapper& IDMap);

    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static OSG_BASE_DLLMAPPING
        bool getFromCString(FieldContainerMap  &outVal,
                            const Char8     *&inVal);

    // Binary conversion
    static OSG_BASE_DLLMAPPING
        UInt32 getBinSize(const FieldContainerMap &oObject);

    static OSG_BASE_DLLMAPPING
        UInt32 getBinSize(const FieldContainerMap *pObjectStore,
                          UInt32         uiNumObjects);

    static OSG_BASE_DLLMAPPING
        void copyToBin(BinaryDataHandler &pMem, 
                       const FieldContainerMap     &pObject);

    static OSG_BASE_DLLMAPPING
        void copyToBin(BinaryDataHandler &pMem, 
                       const FieldContainerMap *pObjectStore,
                       UInt32         uiNumObjects);

    static OSG_BASE_DLLMAPPING
        void copyFromBin(BinaryDataHandler &pMem, 
                         FieldContainerMap     &pObject);

    static OSG_BASE_DLLMAPPING
        void copyFromBin(BinaryDataHandler &pMem, 
                         FieldContainerMap     *pObjectStore,
                         UInt32             uiNumObjects);
};


#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<FieldContainerMap> SFFieldContainerMap;
typedef MField<FieldContainerMap> MFFieldContainerMap;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFFieldContainerMap : public SField<FieldContainerMap> {};
struct MFFieldContainerMap : public MField<FieldContainerMap> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSG_FIELDCONTAINER_MAP_TYPE_H_ */



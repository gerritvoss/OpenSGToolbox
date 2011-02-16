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

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"
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

    typedef FieldTraits<StringToUInt32Map>  Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING DataType       &getType      (void);

    // Access to the names of the actual Fields
    static const Char8          *getSName     (void) { return "SFStringToUInt32Map"; }
    static const Char8          *getMName     (void) { return "MFStringToUInt32Map"; }

    // Create a default instance of the class, needed for Field creation
    static StringToUInt32Map       getDefault   (void) { return StringToUInt32Map();   }


    // String conversion

    // Output inVal into outVal
    static OSG_BASE_DLLMAPPING void putToStream(const StringToUInt32Map   &inVal,
                            OutStream &outVal);

    // Setup outVal from the contents of inVal
    static OSG_BASE_DLLMAPPING bool getFromCString(      StringToUInt32Map  &outVal,
                                     const Char8     *&inVal);

    // Binary conversion

    // Return the size of the binary version in byte   
    static OSG_BASE_DLLMAPPING UInt32 getBinSize(const StringToUInt32Map & obj);

    static OSG_BASE_DLLMAPPING UInt32 getBinSize (const StringToUInt32Map *obj, UInt32 num);

    // Copy the object into the BinaryDataHandler
    static OSG_BASE_DLLMAPPING void copyToBin(      BinaryDataHandler &bdh, 
                                const StringToUInt32Map         &obj);

    static OSG_BASE_DLLMAPPING void copyToBin(      BinaryDataHandler &bdh,
                                const StringToUInt32Map         *objs,
                                UInt32             num);


    // Copy the object from the BinaryDataHandler
    static OSG_BASE_DLLMAPPING void copyFromBin(BinaryDataHandler &bdh, 
                            StringToUInt32Map         &obj);

    static OSG_BASE_DLLMAPPING void copyFromBin(BinaryDataHandler &bdh,
                            StringToUInt32Map         *objs,
                            UInt32             num);
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



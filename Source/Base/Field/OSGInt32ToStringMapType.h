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

#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGFieldTraits.h"
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

    typedef FieldTraits<Int32ToStringMap>  Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING DataType       &getType      (void);

    // Access to the names of the actual Fields
    static const Char8          *getSName     (void) { return "SFInt32ToStringMap"; }
    static const Char8          *getMName     (void) { return "MFInt32ToStringMap"; }

    // Create a default instance of the class, needed for Field creation
    static Int32ToStringMap       getDefault   (void) { return Int32ToStringMap();   }

    
    // String conversion

    // Output inVal into outVal
    static OSG_BASE_DLLMAPPING void putToStream(const Int32ToStringMap   &inVal,
            OutStream &outVal);
    
    // Setup outVal from the contents of inVal
    static OSG_BASE_DLLMAPPING bool getFromCString(      Int32ToStringMap  &outVal,
            const Char8     *&inVal);
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    static OSG_BASE_DLLMAPPING UInt32 getBinSize(const Int32ToStringMap & obj);

    static OSG_BASE_DLLMAPPING UInt32 getBinSize (const Int32ToStringMap *obj, UInt32 num);

    // Copy the object into the BinaryDataHandler
    static OSG_BASE_DLLMAPPING void copyToBin(      BinaryDataHandler &bdh, 
                          const Int32ToStringMap         &obj);

    static OSG_BASE_DLLMAPPING void copyToBin(      BinaryDataHandler &bdh,
                          const Int32ToStringMap         *objs,
                                UInt32             num);
    

    // Copy the object from the BinaryDataHandler
    static OSG_BASE_DLLMAPPING void copyFromBin(BinaryDataHandler &bdh, 
                            Int32ToStringMap         &obj);
    static OSG_BASE_DLLMAPPING void copyFromBin(BinaryDataHandler &bdh,
                            Int32ToStringMap         *objs,
                            UInt32             num);
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



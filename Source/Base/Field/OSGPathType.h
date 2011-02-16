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
#ifndef _OSG_PATH_TYPE_H_
#define _OSG_PATH_TYPE_H_
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

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/exception.hpp>

OSG_BEGIN_NAMESPACE

typedef boost::filesystem::path BoostPath;

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have


template <>
struct FieldTraits<BoostPath> : public FieldTraitsTemplateBase<BoostPath>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    typedef FieldTraits<BoostPath>  Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING DataType       &getType      (void);

    // Access to the names of the actual Fields
    static const Char8          *getSName     (void) { return "SFBoostPath"; }
    static const Char8          *getMName     (void) { return "MFBoostPath"; }

    // Create a default instance of the class, needed for Field creation
    static BoostPath  getDefault   (void) { return BoostPath();   }


    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    static OSG_BASE_DLLMAPPING void putToStream(const BoostPath   &inVal,
            OutStream &outVal);
    
    // Setup outVal from the contents of inVal
    static OSG_BASE_DLLMAPPING bool getFromCString(      BoostPath  &outVal,
                              const Char8     *&inVal);
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    static OSG_BASE_DLLMAPPING UInt32 getBinSize(const BoostPath & obj);

    static OSG_BASE_DLLMAPPING UInt32 getBinSize (const BoostPath *obj, UInt32 num);

    // Copy the object into the BinaryDataHandler
    static OSG_BASE_DLLMAPPING void copyToBin(      BinaryDataHandler &bdh, 
                          const BoostPath         &obj);

    static OSG_BASE_DLLMAPPING void copyToBin(      BinaryDataHandler &bdh,
                          const BoostPath         *objs,
                                UInt32             num);
    

    // Copy the object from the BinaryDataHandler
    static OSG_BASE_DLLMAPPING void copyFromBin(BinaryDataHandler &bdh, 
                            BoostPath         &obj);
    static OSG_BASE_DLLMAPPING void copyFromBin(BinaryDataHandler &bdh,
                            BoostPath         *objs,
                            UInt32             num);
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<BoostPath> SFBoostPath;
typedef MField<BoostPath> MFBoostPath;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFBoostPath : public SField<BoostPath> {};
struct MFBoostPath : public MField<BoostPath> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSG_PATH_TYPE_H_ */



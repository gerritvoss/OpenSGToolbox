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

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGFieldType.h"
#include "OSGBaseFieldTraits.h"
#include "OSGDataType.h"

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

    typedef FieldTraits<std::string>  Self;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum             { Convertible = (Self::ToStreamConvertible |
                                      Self::FromStringConvertible)  };

    // access method for the DataType
    static OSG_BASE_DLLMAPPING DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static const Char8          *getSName     (void) { return "SFBoostPath"; }
    static const Char8          *getMName     (void) { return "MFBoostPath"; }

    // Create a default instance of the class, needed for Field creation
    static BoostPath  getDefault   (void) { return BoostPath();   }


    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToStream(const BoostPath   &inVal,
            OutStream &outVal)
    {
		FieldTraits<std::string>::putToStream(inVal.string(), outVal);
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromCString(      BoostPath  &outVal,
                              const Char8     *&inVal)
    {
		std::string PathString("");
		if( FieldTraits<std::string>::getFromCString(PathString, inVal) )
		{
			try
			{
				outVal = PathString;
				return true;
			}
			catch(boost::filesystem::filesystem_error& error)
			{
				SWARNING <<
					 "ERROR in creating file path from string:" << error.what() <<
					 std::endl;
				return false;
			}
		}
		else
		{
			return false;
		}
        
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const BoostPath & obj)
    {
		return FieldTraits<std::string>::getBinSize(obj.string());
    }

    static UInt32 getBinSize (const BoostPath *obj, UInt32 num)
    {
        //Size:
		//Sum of all the objs
		UInt32 SizeSum(0);
    	for(UInt32 i = 0; i < num; ++i)
        {
            SizeSum += FieldTraits<std::string>::getBinSize(obj[i].string());
        }
        return SizeSum;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const BoostPath         &obj)
    {
		FieldTraits<std::string>::copyToBin(bdh, obj.string());
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const BoostPath         *objs,
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
                            BoostPath         &obj)
    {
		std::string PathString("");
		FieldTraits<std::string>::copyFromBin(bdh, PathString);
		try
		{
			obj = PathString;
		}
		catch(boost::filesystem::filesystem_error& error)
		{
			SWARNING <<
                 "ERROR in creating file path from binary:" << error.what() <<
                 std::endl;
		}
    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            BoostPath         *objs,
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

typedef SField<BoostPath> SFBoostPath;
typedef MField<BoostPath> MFBoostPath;

#else // these are the doxygen hacks

/*! \ingroup GrpBaseFieldSingle \ingroup GrpLibOSGBase */
struct SFBoostPath : public SField<BoostPath> {};
struct MFBoostPath : public MField<BoostPath> {};

#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSG_PATH_TYPE_H_ */



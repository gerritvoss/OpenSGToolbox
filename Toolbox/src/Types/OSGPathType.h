#ifndef _OSG_TOOLBOX_PATH_TYPE_H_
#define _OSG_TOOLBOX_PATH_TYPE_H_
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

#include <OpenSG/OSGSField.h>
#include <OpenSG/OSGMField.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/exception.hpp>

OSG_BEGIN_NAMESPACE

typedef boost::filesystem::path Path;
//typedef boost::filesystem::basic_path<std::string, boost::filesystem::path_traits> Path;

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

Path OSG_TOOLBOXLIB_DLLMAPPING makeRelative(const Path& Root, const Path& ToPath);

template <>
struct FieldDataTraits<Path> : 
    public FieldTraitsRecurseBase<Path>
{
    // Static DataType descriptor, see OSGNewFieldType.cpp for implementation
    static DataType       _type;

    // Define whether string conversions are available. It is strongly
    // recommended to implement both.
    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    // access method for the DataType
    static DataType       &getType      (void) { return _type;          }

    // Access to the names of the actual Fields
    static Char8          *getSName     (void) { return "SFPath"; }
    static Char8          *getMName     (void) { return "MFPath"; }

    // Create a default instance of the class, needed for Field creation
    static Path       getDefault   (void) { return Path();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const Path   &inVal,
                                  std::string &outVal)
    {
		FieldDataTraits<std::string>::putToString(inVal.string(), outVal);
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      Path  &outVal,
                              const Char8     *&inVal)
    {
		std::string PathString("");
		if( FieldDataTraits<std::string>::getFromString(PathString, inVal) )
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
    static UInt32 getBinSize(const Path & obj)
    {
		return FieldDataTraits<std::string>::getBinSize(obj.string());
    }

    static UInt32 getBinSize (const Path *obj, UInt32 num)
    {
        //Size:
		//Sum of all the objs
		UInt32 SizeSum(0);
    	for(UInt32 i = 0; i < num; ++i)
        {
            SizeSum += FieldDataTraits<std::string>::getBinSize(obj[i].string());
        }
        return SizeSum;
    }

    // Copy the object into the BinaryDataHandler
    // the BDH has a number of methods to add a simple type to the stream
    // just use those and use the same order to read them back in.
    // Again there are two versions, one for a single object, one for an 
    // array of objects
    static void copyToBin(      BinaryDataHandler &bdh, 
                          const Path         &obj)
    {
		FieldDataTraits<std::string>::copyToBin(bdh, obj.string());
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const Path         *objs,
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
                            Path         &obj)
    {
		std::string PathString("");
		FieldDataTraits<std::string>::copyFromBin(bdh, PathString);
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
                            Path         *objs,
                            UInt32             num)
    {
    	for(UInt32 i = 0; i < num; ++i)
        {
            copyFromBin(bdh, objs[i]);
        }
    }
};

// Here the actual Field types are declared
// You don't always have to have both, either is fine

typedef SField<Path> SFPath;
typedef MField<Path> MFPath;


// Windows makes everything a lot more complicated than it needs to be,
// Thus you have to include the following Macro to make Windows happy.
// This is the variant for types which are directly used in an application,
// if the type should be included in a DLL, things need to be a little
// different.

// The define makes sure that the code is only included when the corresponding
// source is not compiled
#ifndef OSG_COMPILEPATHTYPEINST
OSG_DLLEXPORT_DECL1(SField, Path, OSG_TOOLBOXLIB_DLLTMPLMAPPING)
#endif

#ifndef OSG_COMPILEPATHTYPEINST
OSG_DLLEXPORT_DECL1(MField, Path, OSG_TOOLBOXLIB_DLLTMPLMAPPING)
#endif


OSG_END_NAMESPACE

#define OSG_TOOLBOX_PATH_TYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_TOOLBOX_PATH_TYPE_H_ */

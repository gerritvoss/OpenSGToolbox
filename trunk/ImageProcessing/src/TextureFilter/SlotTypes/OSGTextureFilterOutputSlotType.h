/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Metabolic                           *
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
#ifndef _OSG_TEXTUREFILTEROUTPUTSLOT_TYPE_H_
#define _OSG_TEXTUREFILTEROUTPUTSLOT_TYPE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>
#include "OSGImageProcessingDef.h"

#include <OpenSG/OSGFieldType.h>
#include <OpenSG/OSGBaseFieldDataType.h>

#include <OpenSG/OSGSField.h>
#include <OpenSG/OSGMField.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGFieldContainerPtr.h>
#include <OpenSG/OSGFieldContainerFactory.h>

#include <vector>

#include "TextureFilter/OSGTextureFilter.h"

OSG_BEGIN_NAMESPACE

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING TextureFilterOutputSlot
{
public:
    friend class TextureFilter;
    typedef std::vector<std::pair<TextureFilterPtr,UInt8> > OutSlotVec;
    typedef OutSlotVec::iterator OutSlotVecItor;

    TextureFilterOutputSlot(void);

    bool operator==(const TextureFilterOutputSlot& Right) const;

    const std::vector<std::pair<TextureFilterPtr,UInt8> >& getSinkFilters(void) const;
    TextureFilterPtr getSinkFilter(UInt32 Index) const;
    UInt32 getNumSinkFilters(void) const;
    UInt8 getSinkFilterInputSlot(UInt32 Index) const;

    UInt32 getTextureFormatClasses(void) const;
    UInt32 getTextureDataTypeClasses(void) const;
    const std::string& getDescription(void) const;

    void addSinkFilter(TextureFilterPtr Filter, UInt8 SinkInputSlot);
    void removeSinkFilter(TextureFilterPtr Filter, UInt8 SinkInputSlot);

    void setTextureFormatClasses(UInt32 value);
    void setTextureDataTypeClasses(UInt32 value);
    void setDescription(const std::string& value);

    void putToString(std::string &outVal) const;
    bool getFromString(const Char8     *&inVal);

    void copyFromBin(BinaryDataHandler &bdh);
    void copyToBin(BinaryDataHandler &bdh) const;

private:

    OutSlotVec  _SinkFilters;
	UInt32  _TextureFormatClasses;  //Color, Depth, or Stencil
	UInt32  _TextureDataTypeClasses;        //Unsigned Int, Signed Int, Float
    std::string  _Description;
};

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldDataTraits<TextureFilterOutputSlot> : 
    public FieldTraitsRecurseBase<TextureFilterOutputSlot>
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
    static const Char8          *getSName     (void) { return "SFTextureFilterOutputSlot"; }
    static const Char8          *getMName     (void) { return "MFTextureFilterOutputSlot"; }

    // Create a default instance of the class, needed for Field creation
    static TextureFilterOutputSlot       getDefault   (void) { return TextureFilterOutputSlot();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const TextureFilterOutputSlot   &inVal,
                                  std::string &outVal)
    {
        inVal.putToString(outVal);
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      TextureFilterOutputSlot  &outVal,
                              const Char8     *&inVal)
    {
        outVal.getFromString(inVal);
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const TextureFilterOutputSlot & obj)
    {
        UInt32 Size(0);
        Size += sizeof(UInt32)   //Number of Sink Filters
             + (sizeof(UInt32)+sizeof(UInt8))*obj.getNumSinkFilters()  //SinkFilters
             + sizeof(UInt32)    //TextureFormatClasses
             + sizeof(UInt32)    //TextureDataTypeClasses
             + FieldDataTraits<std::string>::getBinSize(obj.getDescription());    //Description

        return Size;
    }

    static UInt32 getBinSize (const TextureFilterOutputSlot *obj, UInt32 num)
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
                          const TextureFilterOutputSlot         &obj)
    {
        obj.copyToBin(bdh);
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const TextureFilterOutputSlot         *objs,
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
                            TextureFilterOutputSlot         &obj)
    {
        obj.copyFromBin(bdh);
    }

    static void copyFromBin(BinaryDataHandler &bdh,
                            TextureFilterOutputSlot         *objs,
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

typedef SField<TextureFilterOutputSlot> SFTextureFilterOutputSlot;
typedef MField<TextureFilterOutputSlot> MFTextureFilterOutputSlot;


// Windows makes everything a lot more complicated than it needs to be,
// Thus you have to include the following Macro to make Windows happy.
// This is the variant for types which are directly used in an application,
// if the type should be included in a DLL, things need to be a little
// different.

// The define makes sure that the code is only included when the corresponding
// source is not compiled
#ifndef OSG_COMPILETEXTUREFILTEROUTPUTSLOTTYPEINST
OSG_DLLEXPORT_DECL1(SField, TextureFilterOutputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING)
#endif

#ifndef OSG_COMPILETEXTUREFILTEROUTPUTSLOTTYPEINST
OSG_DLLEXPORT_DECL1(MField, TextureFilterOutputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGTextureFilterOutputSlotType.inl"

#endif /* _OSG_TEXTUREFILTEROUTPUTSLOT_TYPE_H_ */

/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
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
#ifndef _OSG_TEXTUREFILTERINPUTSLOT_TYPE_H_
#define _OSG_TEXTUREFILTERINPUTSLOT_TYPE_H_
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

#include "TextureFilter/OSGTextureFilter.h"

OSG_BEGIN_NAMESPACE

enum TextureFormatClasses {
    OSG_TEXTURE_INTERNAL_FORMAT_NONE = 0,
    OSG_TEXTURE_INTERNAL_FORMAT_COLOR = 1,
    OSG_TEXTURE_INTERNAL_FORMAT_DEPTH = 2,
    OSG_TEXTURE_INTERNAL_FORMAT_STENCIL = 4
};

enum TextureDataTypeClasses {
    OSG_TEXTURE_DATA_TYPE_NONE = 0,
    OSG_TEXTURE_DATA_TYPE_UINT = 1,
    OSG_TEXTURE_DATA_TYPE_INT = 2,
    OSG_TEXTURE_DATA_TYPE_FLOAT = 4,
};

class OSG_IMAGEPROCESSINGLIB_DLLMAPPING TextureFilterInputSlot
{
public:

    friend class TextureFilter;

    TextureFilterInputSlot(void);
	TextureFilterInputSlot(UInt32 TextureFormatClasses,UInt32 TextureDataTypeClasses, const std::string& Description);

    bool operator==(const TextureFilterInputSlot& Right) const;

    TextureFilterPtr getSourceFilter(void) const;
    bool isAttached(void) const;
    UInt8 getSourceFilterOutputSlot(void) const;
    UInt32 getTextureFormatClasses(void) const;
    UInt32 getTextureDataTypeClasses(void) const;
    const std::string& getDescription(void) const;

    void setSourceFilter(TextureFilterPtr value);
    void setSourceFilterOutputSlot(UInt8 value);
    void setTextureFormatClasses(UInt32 value);
    void setTextureDataTypeClasses(UInt32 value);
    void setDescription(const std::string& value);
private:

    TextureFilterPtr  _SourceFilter;
	UInt8  _SourceFilterOutputSlot;
	UInt32  _TextureFormatClasses;  //Color, Depth, or Stencil
	UInt32  _TextureDataTypeClasses;        //Unsigned Int, Signed Int, Float
    std::string  _Description;
};

// The FieldDataTraits class contains the methods needed to implement
// the features a Field data element needs to have

template <>
struct FieldDataTraits<TextureFilterInputSlot> : 
    public FieldTraitsRecurseBase<TextureFilterInputSlot>
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
    static const Char8          *getSName     (void) { return "SFTextureFilterInputSlot"; }
    static const Char8          *getMName     (void) { return "MFTextureFilterInputSlot"; }

    // Create a default instance of the class, needed for Field creation
    static TextureFilterInputSlot       getDefault   (void) { return TextureFilterInputSlot();   }

    
    // This is where it gets interesting: the conversion functions

    // String conversion

    // Output inVal into outVal
    // the exact mapping doesn't matter, 
    // Our recommendation is to output as a string, 
    // i.e. start and stop with ", as this simplifies integration into the
    // OSG Loader.
    static void putToString(const TextureFilterInputSlot   &inVal,
                                  std::string &outVal)
    {
		//Put the SourceFilter
        outVal.append(TypeTraits<UInt32>::putToString(inVal.getSourceFilter().getFieldContainerId()));
        outVal.append(",");
		
		//Put the SourceFilterOutputSlot
		outVal.append(TypeTraits<UInt8>::putToString(inVal.getSourceFilterOutputSlot()));
        outVal.append(",");

        //TextureFormatClasses
        outVal.append(TypeTraits<UInt32>::putToString(inVal.getTextureFormatClasses()));
        outVal.append(",");

        //TextureDataTypeClasses
        outVal.append(TypeTraits<UInt32>::putToString(inVal.getTextureDataTypeClasses()));
        outVal.append(",");

        //Description
        outVal.append(inVal.getDescription());
    }
    
    // Setup outVal from the contents of inVal
    // For complicated classes it makes sense to implement this function
    // as a class method and just call that from here  
    static bool getFromString(      TextureFilterInputSlot  &outVal,
                              const Char8     *&inVal)
    {
        const Char8 *curInString(inVal);
	    if(curInString == NULL) { return false; }

		//Get the SourceFilter
        UInt32 FieldContainerID = TypeTraits<UInt32>::getFromString(curInString);
        FieldContainerPtr Filter = FieldContainerFactory::the()->getMappedContainer(FieldContainerID);
        if(Filter == NullFC)
        {
            SWARNING <<
                "TextureFilterInputSlot::getFromString(): Could not find Container referenced with Id: " << FieldContainerID <<
                std::endl;
        }
        if(!Filter->getType().isDerivedFrom(TextureFilter::getClassType()))
        {
            SWARNING <<
                "TextureFilterInputSlot::getFromString(): Container referenced with Id: " << FieldContainerID <<
                " is not derived from TextureFilter.  It has type: " << Filter->getType().getCName() <<
                std::endl;
        }
        outVal.setSourceFilter(TextureFilterPtr::dcast(Filter));
		
		//Get the SourceFilterOutputSlot
		curInString = strchr(curInString, ',');
		++curInString;
        outVal.setSourceFilterOutputSlot(TypeTraits<UInt8>::getFromString(curInString));

        //Get the TextureFormatClasses
		curInString = strchr(curInString, ',');
		++curInString;
        outVal.setTextureFormatClasses(TypeTraits<UInt32>::getFromString(curInString));

        //Get the TextureDataTypeClasses
		curInString = strchr(curInString, ',');
		++curInString;
        outVal.setTextureDataTypeClasses(TypeTraits<UInt32>::getFromString(curInString));

        //Get the Description
		curInString = strchr(curInString, ',');
		++curInString;
        outVal.setDescription(std::string(curInString));

        return true;
    }
    
    // Binary conversion
    
    // Return the size of the binary version in byte   
    // There are two versions of this function, one for a single object, 
    // one for an array of objects
    static UInt32 getBinSize(const TextureFilterInputSlot & obj)
    {
        UInt32 Size(0);
        Size += sizeof(UInt32)   //SourceFilter
             + sizeof(UInt8) //SourceFilterOutputSlot
             + sizeof(UInt32)    //TextureFormatClasses
             + sizeof(UInt32)    //TextureDataTypeClasses
             + FieldDataTraits<std::string>::getBinSize(obj.getDescription());    //Description

        return Size;
    }

    static UInt32 getBinSize (const TextureFilterInputSlot *obj, UInt32 num)
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
                          const TextureFilterInputSlot         &obj)
    {
        //SourceFilter
        bdh.putValue(obj.getSourceFilter().getFieldContainerId());

        //SourceFilterOutputSlot
        bdh.putValue(obj.getSourceFilterOutputSlot());

        //TextureFormatClasses
        bdh.putValue(obj.getTextureFormatClasses());

        //TextureDataTypeClasses
        bdh.putValue(obj.getTextureDataTypeClasses());
        
        //Description
        bdh.putValue(obj.getDescription());
    }

    static void copyToBin(      BinaryDataHandler &bdh,
                          const TextureFilterInputSlot         *objs,
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
                            TextureFilterInputSlot         &obj)
    {
        //SourceFilter
        UInt32 FieldId;
        bdh.getValue(FieldId);
        FieldContainerPtr fcp = FieldContainerFactory::the()->getMappedContainer(FieldId);
        obj.setSourceFilter(TextureFilterPtr::dcast(fcp));

        //SourceFilterOutputSlot
        UInt8 SourceFilterOutputSlot;
        bdh.getValue(SourceFilterOutputSlot);
        obj.setSourceFilterOutputSlot(SourceFilterOutputSlot);

        //TextureFormatClasses
        UInt32 TextureFormatClasses;
        bdh.getValue(TextureFormatClasses);
        obj.setTextureFormatClasses(TextureFormatClasses);

        //TextureDataTypeClasses
        UInt32 TextureDataTypeClasses;
        bdh.getValue(TextureDataTypeClasses);
        obj.setTextureDataTypeClasses(TextureDataTypeClasses);
        
        //Description
        std::string Description;
        FieldDataTraits<std::string>::copyFromBin( bdh, Description );
        obj.setDescription(Description);

    }
    static void copyFromBin(BinaryDataHandler &bdh,
                            TextureFilterInputSlot         *objs,
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

typedef SField<TextureFilterInputSlot> SFTextureFilterInputSlot;
typedef MField<TextureFilterInputSlot> MFTextureFilterInputSlot;


// Windows makes everything a lot more complicated than it needs to be,
// Thus you have to include the following Macro to make Windows happy.
// This is the variant for types which are directly used in an application,
// if the type should be included in a DLL, things need to be a little
// different.

// The define makes sure that the code is only included when the corresponding
// source is not compiled
#ifndef OSG_COMPILETEXTUREFILTERINPUTSLOTTYPEINST
OSG_DLLEXPORT_DECL1(SField, TextureFilterInputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING)
#endif

#ifndef OSG_COMPILETEXTUREFILTERINPUTSLOTTYPEINST
OSG_DLLEXPORT_DECL1(MField, TextureFilterInputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING)
#endif

OSG_END_NAMESPACE

#include "OSGTextureFilterInputSlotType.inl"

#endif /* _OSG_TEXTUREFILTERINPUTSLOT_TYPE_H_ */

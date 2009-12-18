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

// Source file for new Field type

// This define is only set in this source file. It switches the
// Windows-specific declarations in the header for compiling the Field, 
// not for using it.
#define OSG_COMPILETEXTUREFILTEROUTPUTSLOTTYPEINST

// You need this in every OpenSG file
#include <OpenSG/OSGConfig.h>
#include "OSGImageProcessingDef.h"

// Some basic system headers
#include <OpenSG/OSGBaseTypes.h>

// The new field type include
#include "OSGTextureFilterOutputSlotType.h"

// Needed to instantiate some template functions on Windows
#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

TextureFilterOutputSlot::TextureFilterOutputSlot(void) : _SinkFilters(),
_TextureFormatClasses(0),
_TextureDataTypeClasses(0),
_Description("")
{
}

bool TextureFilterOutputSlot::operator==(const TextureFilterOutputSlot& Right) const
{
    return (_SinkFilters == Right._SinkFilters) &&
           (_TextureFormatClasses == Right._TextureFormatClasses) &&
           (_TextureDataTypeClasses == Right._TextureDataTypeClasses) &&
           (_Description == Right._Description);
}

void TextureFilterOutputSlot::addSinkFilter(TextureFilterPtr Filter, UInt8 SinkInputSlot)
{
    for(OutSlotVecItor Itor(_SinkFilters.begin()) ; Itor != _SinkFilters.end() ; ++Itor)
    {
        if(Itor->first == Filter &&
           Itor->second == SinkInputSlot)
        {
            return;
        }
    }
    _SinkFilters.push_back(std::pair<TextureFilterPtr,UInt8>(Filter, SinkInputSlot));
}

void TextureFilterOutputSlot::removeSinkFilter(TextureFilterPtr Filter, UInt8 SinkInputSlot)
{
    for(OutSlotVecItor Itor(_SinkFilters.begin()) ; Itor != _SinkFilters.end() ; ++Itor)
    {
        if(Itor->first == Filter &&
           Itor->second == SinkInputSlot)
        {
            _SinkFilters.erase(Itor);
            return;
        }
    }
}

void TextureFilterOutputSlot::putToString(std::string &outVal) const
{
    for(UInt32 i(0) ; i<getSinkFilters().size() ; ++i)
    {
        outVal.append("(");

        //Put the SinkFilter
        outVal.append(TypeTraits<UInt32>::putToString(getSinkFilter(i).getFieldContainerId()));
        outVal.append(",");

        //Put the Slot
        outVal.append(TypeTraits<UInt8>::putToString(getSinkFilter(i).getFieldContainerId()));

        outVal.append("),");
    }

    //TextureFormatClasses
    outVal.append(TypeTraits<UInt32>::putToString(getTextureFormatClasses()));
    outVal.append(",");

    //TextureDataTypeClasses
    outVal.append(TypeTraits<UInt32>::putToString(getTextureDataTypeClasses()));
    outVal.append(",");

    //Description
    outVal.append(getDescription());
}

bool TextureFilterOutputSlot::getFromString(const Char8     *&inVal)
{
    const Char8 *curInString(inVal);
    if(curInString == NULL) { return false; }

    //Get the SinkFilters
    curInString = strchr(curInString, '(');
    if(curInString == NULL)
    {
        curInString = inVal;
    }
    else
    {
        UInt32 FieldContainerID;
        FieldContainerPtr Filter;
        UInt8 InputSlot;
        while(curInString != NULL)
        {
            //Move Past the '('
            ++curInString;

            FieldContainerID = TypeTraits<UInt32>::getFromString(curInString);
            Filter = FieldContainerFactory::the()->getMappedContainer(FieldContainerID);
            if(Filter == NullFC)
            {
                SWARNING <<
                    "TextureFilterOutputSlot::getFromString(): Could not find Container referenced with Id: " << FieldContainerID <<
                    std::endl;
            }
            else if(!Filter->getType().isDerivedFrom(TextureFilter::getClassType()))
            {
                SWARNING <<
                    "TextureFilterOutputSlot::getFromString(): Container referenced with Id: " << FieldContainerID <<
                    " is not derived from TextureFilter.  It has type: " << Filter->getType().getCName() <<
                    std::endl;
            }
            else
            {
                //Get the Slot
                curInString = strchr(curInString, ',');
                ++curInString;
                InputSlot = TypeTraits<UInt8>::getFromString(curInString);

                _SinkFilters.push_back(std::pair<TextureFilterPtr,UInt8>(TextureFilterPtr::dcast(Filter),InputSlot));
            }

            curInString = strchr(curInString, '(');
        }
        curInString = strrchr(inVal, ')');
    }

    //Get the TextureFormatClasses
    curInString = strchr(curInString, ',');
    ++curInString;
    setTextureFormatClasses(TypeTraits<UInt32>::getFromString(curInString));

    //Get the TextureDataTypeClasses
    curInString = strchr(curInString, ',');
    ++curInString;
    setTextureDataTypeClasses(TypeTraits<UInt32>::getFromString(curInString));

    //Get the Description
    curInString = strchr(curInString, ',');
    ++curInString;
    setDescription(std::string(curInString));

    return true;
}

void TextureFilterOutputSlot::copyFromBin(BinaryDataHandler &bdh)
{
    //Num Sink Filters
    UInt32 NumSinkFilters(0);
    bdh.getValue(NumSinkFilters);

    //Sink Filters
    _SinkFilters.clear();

    UInt32 FieldId;
    FieldContainerPtr fcp;
    UInt8 SlotNum;
    for(UInt32 i(0) ; i<NumSinkFilters ; ++i)
    {
        //Get the SinkFilter
        bdh.getValue(FieldId);
        fcp = FieldContainerFactory::the()->getMappedContainer(FieldId);

        //Get the Slot
        bdh.getValue(SlotNum);

        //Add the SinkFilter
        _SinkFilters.push_back(std::pair<TextureFilterPtr,UInt8>(TextureFilterPtr::dcast(fcp),SlotNum));
    }

    //TextureFormatClasses
    UInt32 TextureFormatClasses;
    bdh.getValue(TextureFormatClasses);
    setTextureFormatClasses(TextureFormatClasses);

    //TextureDataTypeClasses
    UInt32 TextureDataTypeClasses;
    bdh.getValue(TextureDataTypeClasses);
    setTextureDataTypeClasses(TextureDataTypeClasses);
    
    //Description
    std::string Description;
    FieldDataTraits<std::string>::copyFromBin( bdh, Description );
    setDescription(Description);

}

void TextureFilterOutputSlot::copyToBin(BinaryDataHandler &bdh) const
{
    //Num Sink Filters
    bdh.putValue(getNumSinkFilters());

    //Sink Filters
    for(UInt32 i(0) ; i<getNumSinkFilters() ; ++i)
    {
        //Put the SinkFilter
        bdh.putValue(getSinkFilter(i).getFieldContainerId());

        //Put the Slot
        bdh.putValue(getSinkFilterInputSlot(i));
    }

    //TextureFormatClasses
    bdh.putValue(getTextureFormatClasses());

    //TextureDataTypeClasses
    bdh.putValue(getTextureDataTypeClasses());
    
    //Description
    bdh.putValue(getDescription());
}

// This is where the DataType for the new Fieldtype is defined.
// The parameters are the name of the type and the name of the parent type
DataType FieldDataTraits<TextureFilterOutputSlot>::_type("TextureFilterOutputSlot", "BaseType");

// These macros instantiate the necessary template methods for the fields
OSG_DLLEXPORT_SFIELD_DEF1(TextureFilterOutputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING );

OSG_DLLEXPORT_MFIELD_DEF1(TextureFilterOutputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING );

OSG_END_NAMESPACE


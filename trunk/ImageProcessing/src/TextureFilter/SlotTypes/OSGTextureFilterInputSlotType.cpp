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
#define OSG_COMPILETEXTUREFILTERINPUTSLOTTYPEINST

// You need this in every OpenSG file
#include <OpenSG/OSGConfig.h>
#include "OSGImageProcessingDef.h"

// Some basic system headers
#include <OpenSG/OSGBaseTypes.h>

// The new field type include
#include "OSGTextureFilterInputSlotType.h"

// Needed to instantiate some template functions on Windows
#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

TextureFilterInputSlot::TextureFilterInputSlot(void) : _SourceFilter(NullFC),
_SourceFilterOutputSlot(0),
_TextureFormatClasses(0),
_TextureDataTypeClasses(0),
_Description("")
{
}

TextureFilterInputSlot::TextureFilterInputSlot(UInt32 TextureFormatClasses,UInt32 TextureDataTypeClasses, const std::string& Description) : _SourceFilter(NullFC),
_SourceFilterOutputSlot(0),
_TextureFormatClasses(TextureFormatClasses),
_TextureDataTypeClasses(TextureDataTypeClasses),
_Description(Description)
{
}

bool TextureFilterInputSlot::operator==(const TextureFilterInputSlot& Right) const
{
    return (_SourceFilter == Right._SourceFilter) &&
           (_SourceFilterOutputSlot == Right._SourceFilterOutputSlot) &&
           (_TextureFormatClasses == Right._TextureFormatClasses) &&
           (_TextureDataTypeClasses == Right._TextureDataTypeClasses) &&
           (_Description == Right._Description);
}



// This is where the DataType for the new Fieldtype is defined.
// The parameters are the name of the type and the name of the parent type
DataType FieldDataTraits<TextureFilterInputSlot>::_type("TextureFilterInputSlot", "BaseType");

// These macros instantiate the necessary template methods for the fields
OSG_DLLEXPORT_SFIELD_DEF1(TextureFilterInputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING );

OSG_DLLEXPORT_MFIELD_DEF1(TextureFilterInputSlot, OSG_IMAGEPROCESSINGLIB_DLLMAPPING );

OSG_END_NAMESPACE


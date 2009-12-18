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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
TextureFilterPtr TextureFilterInputSlot::getSourceFilter(void) const
{
    return _SourceFilter;
}

inline
bool TextureFilterInputSlot::isAttached(void) const
{
    return _SourceFilter != NullFC;
}

inline
UInt8 TextureFilterInputSlot::getSourceFilterOutputSlot(void) const
{
    return _SourceFilterOutputSlot;
}

inline
UInt32 TextureFilterInputSlot::getTextureFormatClasses(void) const
{
    return _TextureFormatClasses;
}

inline
UInt32 TextureFilterInputSlot::getTextureDataTypeClasses(void) const
{
    return _TextureDataTypeClasses;
}

inline
const std::string& TextureFilterInputSlot::getDescription(void) const
{
    return _Description;
}


inline
void TextureFilterInputSlot::setSourceFilter(TextureFilterPtr value)
{
    _SourceFilter = value;
}

inline
void TextureFilterInputSlot::setSourceFilterOutputSlot(UInt8 value)
{
    _SourceFilterOutputSlot = value;
}

inline
void TextureFilterInputSlot::setTextureFormatClasses(UInt32 value)
{
    _TextureFormatClasses = value;
}

inline
void TextureFilterInputSlot::setTextureDataTypeClasses(UInt32 value)
{
    _TextureDataTypeClasses = value;
}

inline
void TextureFilterInputSlot::setDescription(const std::string& value)
{
    _Description = value;
}


OSG_END_NAMESPACE


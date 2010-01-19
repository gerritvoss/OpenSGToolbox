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
const std::vector<std::pair<TextureFilterPtr,UInt8> >& TextureFilterOutputSlot::getSinkFilters(void) const
{
    return _SinkFilters;
}
inline
TextureFilterPtr TextureFilterOutputSlot::getSinkFilter(UInt32 Index) const
{
    return _SinkFilters[Index].first;
}
inline
UInt32 TextureFilterOutputSlot::getNumSinkFilters(void) const
{
    return _SinkFilters.size();
}
inline
UInt8 TextureFilterOutputSlot::getSinkFilterInputSlot(UInt32 Index) const
{
    return _SinkFilters[Index].second;
}

inline
UInt32 TextureFilterOutputSlot::getTextureFormatClasses(void) const
{
    return _TextureFormatClasses;
}

inline
UInt32 TextureFilterOutputSlot::getTextureDataTypeClasses(void) const
{
    return _TextureDataTypeClasses;
}

inline
const std::string& TextureFilterOutputSlot::getDescription(void) const
{
    return _Description;
}

inline
void TextureFilterOutputSlot::setTextureFormatClasses(UInt32 value)
{
    _TextureFormatClasses = value;
}

inline
void TextureFilterOutputSlot::setTextureDataTypeClasses(UInt32 value)
{
    _TextureDataTypeClasses = value;
}

inline
void TextureFilterOutputSlot::setDescription(const std::string& value)
{
    _Description = value;
}


OSG_END_NAMESPACE


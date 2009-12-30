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
#include "TextureFilter/SlotTypes/OSGTextureFilterInputSlotType.h"
#include "TextureFilter/SlotTypes/OSGTextureFilterOutputSlotType.h"

OSG_BEGIN_NAMESPACE

inline
bool TextureFilter::isSource(void) const
{
    return getNumOutputSlots() != 0;
}

inline
bool TextureFilter::isSink(void) const
{
    return getNumInputSlots() != 0;
}

inline
const TextureFilterInputSlot* TextureFilter::getInputSlot(UInt32 InputSlot) const
{
    return const_cast<TextureFilter*>(this)->editInputSlot();
}

inline
const TextureFilterOutputSlot* TextureFilter::getOutputSlot(UInt32 OutputSlot) const
{
    return const_cast<TextureFilter*>(this)->editOutputSlot();
}

OSG_END_NAMESPACE


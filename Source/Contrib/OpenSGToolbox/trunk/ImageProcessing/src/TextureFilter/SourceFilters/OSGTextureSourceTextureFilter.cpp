/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEIMAGEPROCESSINGLIB

#include <OpenSG/OSGConfig.h>

#include "OSGTextureSourceTextureFilter.h"
#include "TextureFilter/SlotTypes/OSGTextureClassUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextureSourceTextureFilter

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureSourceTextureFilter::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


std::string TextureSourceTextureFilter::getDescription(void) const
{
    return std::string("");
}

TextureChunkPtr TextureSourceTextureFilter::pullTexture(UInt8 OutputSlot) const
{
    if(OutputSlot == 0)
    {
        return getTexture();
    }
    else
    {
        return NullFC;
    }
}

void TextureSourceTextureFilter::internalUpdate(RenderActionBase *action, const Vec2f& DrawnSize)
{
    //Nothing needed to do for a TextureSource
}

Int32 TextureSourceTextureFilter::getNumOutputSlots(void) const
{
    //Only 1 Texture Attached
    return 1;
}

TextureFilterOutputSlot* TextureSourceTextureFilter::editOutputSlot(UInt32 OutputSlot)
{
    if(OutputSlot == 0)
    {
        return &editTextureOutputSlot();
    }
    else
    {
        return NULL;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextureSourceTextureFilter::TextureSourceTextureFilter(void) :
    Inherited()
{
}

TextureSourceTextureFilter::TextureSourceTextureFilter(const TextureSourceTextureFilter &source) :
    Inherited(source)
{
}

TextureSourceTextureFilter::~TextureSourceTextureFilter(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureSourceTextureFilter::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & TextureFieldMask)
	{
		UInt32 FormatClasses(OSG_TEXTURE_INTERNAL_FORMAT_NONE);
		UInt32 DataTypeClasses(OSG_TEXTURE_DATA_TYPE_NONE);
		if(getTexture() != NullFC)
		{
			FormatClasses = determinTextureFormatClasses(getTexture());
			DataTypeClasses = determinTextureDataTypeClasses(getTexture());
		}

		editTextureOutputSlot().setTextureFormatClasses(FormatClasses);
		editTextureOutputSlot().setTextureDataTypeClasses(DataTypeClasses);
	}
}

void TextureSourceTextureFilter::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextureSourceTextureFilter NI" << std::endl;
}


OSG_END_NAMESPACE


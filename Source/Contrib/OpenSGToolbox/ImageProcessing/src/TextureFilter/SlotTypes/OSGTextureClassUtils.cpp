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
#include "OSGTextureClassUtils.h"
#include <OpenSG/OSGImage.h>

#ifndef GL_ARB_depth_texture
    #define GL_DEPTH_COMPONENT16_ARB 0x81A5
    #define GL_DEPTH_COMPONENT24_ARB 0x81A6
    #define GL_DEPTH_COMPONENT32_ARB 0x81A7
    #define GL_TEXTURE_DEPTH_SIZE_ARB 0x884A
    #define GL_DEPTH_TEXTURE_MODE_ARB 0x884B
#endif

OSG_BEGIN_NAMESPACE

UInt32 determinTextureFormatClasses(TextureChunkPtr tex)
{
	UInt32 Result(OSG_TEXTURE_INTERNAL_FORMAT_NONE);
	
	if(tex != NullFC)
	{
		switch(tex->getInternalFormat())
		{
		case GL_DEPTH_COMPONENT:
		case GL_DEPTH_COMPONENT16_ARB:
		case GL_DEPTH_COMPONENT24_ARB:
		case GL_DEPTH_COMPONENT32_ARB:
			Result = OSG_TEXTURE_INTERNAL_FORMAT_DEPTH;
			break;

		case GL_STENCIL_INDEX:
			Result = OSG_TEXTURE_INTERNAL_FORMAT_STENCIL;
			break;

		default:
			Result = OSG_TEXTURE_INTERNAL_FORMAT_COLOR;
			break;
		}
	}

	return Result;
}

UInt32 determinTextureDataTypeClasses(TextureChunkPtr tex)
{
	UInt32 Result(OSG_TEXTURE_DATA_TYPE_NONE);
	if(tex != NullFC && tex->getImage() != NullFC)
	{
		switch(tex->getImage()->getDataType())
		{
		case Image::OSG_UINT8_IMAGEDATA:
		case Image::OSG_UINT16_IMAGEDATA:
		case Image::OSG_UINT32_IMAGEDATA:
			Result = OSG_TEXTURE_DATA_TYPE_UINT;
			break;

		case Image::OSG_INT16_IMAGEDATA:
		case Image::OSG_INT32_IMAGEDATA:
			Result = OSG_TEXTURE_DATA_TYPE_INT;
			break;
			
		case Image::OSG_FLOAT16_IMAGEDATA:
		case Image::OSG_FLOAT32_IMAGEDATA:
			Result = OSG_TEXTURE_DATA_TYPE_FLOAT;
			break;

		default:
			SWARNING << "determinTextureDataTypeClasses(): Image Data Type: " << tex->getImage()->getDataType() << " not supported." << std::endl;
			break;
		}
	}
	return Result;
}

OSG_END_NAMESPACE


/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
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
#include "OSGImageUtils.h"
#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

Real32 getPixelIntensity(const Vec2f& coord, ImagePtr TheImage)
{
	if(TheImage->getDimension() != 2)
	{
		SWARNING << "getPixelIntensity not implemented for images with depth != 2" << std::endl;
	}

	Real32 Result(0.0f);
	
	UInt8 PixelStride(0);
	switch(TheImage->getPixelFormat())
	{
	case Image::OSG_A_PF:
	case Image::OSG_I_PF:
	case Image::OSG_L_PF:
		PixelStride = 1;
		break;
	case Image::OSG_LA_PF:
		PixelStride = 2;
		break;
	case Image::OSG_BGR_PF:
	case Image::OSG_RGB_PF:
		PixelStride = 3;
		break;
	case Image::OSG_RGBA_PF:
	case Image::OSG_BGRA_PF:
		PixelStride = 4;
		break;
	}

	Int32 Bpp(TheImage->getBpp());

	Int32 Index( (osgfloor(coord.x()*(TheImage->getWidth()-1)) + osgfloor(coord.y()*(TheImage->getHeight()-1))*TheImage->getWidth()) * PixelStride * Bpp);
	switch(TheImage->getDataType())
	{
	case Image::OSG_UINT8_IMAGEDATA:
		{
			UInt8 Value( *reinterpret_cast<UInt8*>(&(TheImage->getPixel(Index))));
			Result = static_cast<Real32>(Value)/static_cast<Real32>(TypeTraits<UInt8>::getMax() );
		}
		break;
	case Image::OSG_UINT16_IMAGEDATA:
		{
			UInt16 Value( *reinterpret_cast<UInt16*>(&(TheImage->getPixel(Index))));
			Result = static_cast<Real32>(Value)/static_cast<Real32>(TypeTraits<UInt16>::getMax() );
		}
		break;
	case Image::OSG_UINT32_IMAGEDATA:
		{
			UInt32 Value( *reinterpret_cast<UInt32*>(&(TheImage->getPixel(Index))));
			Result = static_cast<Real32>(Value)/static_cast<Real32>(TypeTraits<UInt32>::getMax() );
		}
		break;
	case Image::OSG_FLOAT32_IMAGEDATA:
		{
			Real32 Value( *reinterpret_cast<Real32*>(&(TheImage->getPixel(Index))));
			Result = Value;
		}
		break;
	case Image::OSG_FLOAT16_IMAGEDATA:
		{
			Real16 Value( *reinterpret_cast<Real16*>(&(TheImage->getPixel(Index))));
			Result = static_cast<Real32>(Value);
		}
		break;
	case Image::OSG_INT16_IMAGEDATA:
		{
			Int16 Value( *reinterpret_cast<Int16*>(&(TheImage->getPixel(Index))));
			Result = static_cast<Real32>(Value)/static_cast<Real32>(TypeTraits<Int16>::getMax() );
		}
		break;
	case Image::OSG_INT32_IMAGEDATA:
		{
			Int32 Value( *reinterpret_cast<Int32*>(&(TheImage->getPixel(Index))));
			Result = static_cast<Real32>(Value)/static_cast<Real32>(TypeTraits<Int32>::getMax() );
		}
		break;
	}
	return Result;
}

OSG_END_NAMESPACE


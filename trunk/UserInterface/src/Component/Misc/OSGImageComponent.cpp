/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <OpenSG/OSGConfig.h>
#include <OpenSG/Toolbox/OSGTextureUtils.h>

#include "OSGImageComponent.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ImageComponent
A UI Button. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ImageComponent::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ImageComponent::drawInternal(const GraphicsPtr TheGraphics) const
{
   
   //Get Border Insets
   Pnt2f TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);
   Vec2f ComponentSize(BottomRight-TopLeft);

   TextureChunkPtr DrawnTexture = getDrawnTexture();
   if(DrawnTexture == NullFC || DrawnTexture->getImage() == NullFC)
   {
	   return;
   }

   //Render the Image
   //Draw a quad on top of the background according to the alignment and scaling
   //Figure out Scaling
   Vec2f Size(0.0,0.0);
   switch(getScale())
   {
   case SCALE_NONE:
	   //Size in pixels Should be the Image size in pixels
	   Size.setValues(DrawnTexture->getImage()->getWidth(), DrawnTexture->getImage()->getHeight());
	   break;
   case SCALE_STRETCH:
	   Size.setValue(ComponentSize);
	   break;
   case SCALE_MIN_AXIS:
	   {
	   //Figure out the aspect ratio of this Component
	   Real32 AspectComponent = ComponentSize.x()/ComponentSize.y();
	   Real32 AspectImage = static_cast<Real32>(DrawnTexture->getImage()->getWidth())/static_cast<Real32>(DrawnTexture->getImage()->getHeight());

	   Vec2f vector(0,0);
	   if (AspectComponent < AspectImage)
	   {
		   vector[0] = ComponentSize.x();
		   vector[1] = (Real32)((Real32)ComponentSize.x()/AspectImage);
	   }
	   else
	   {
		   vector[0] = (Real32)((Real32)ComponentSize.y()*AspectImage);
		   vector[1] = ComponentSize.y();
	   }
	   Size.setValue(vector);
	   }
	   break;
   case SCALE_MAX_AXIS:
	   {
	   //Figure out the aspect ratio of this Component
	   Real32 AspectComponent = ComponentSize.x()/ComponentSize.y();
	   Real32 AspectImage = static_cast<Real32>(DrawnTexture->getImage()->getWidth())/static_cast<Real32>(DrawnTexture->getImage()->getHeight());

	   Vec2f vector(0,0);
	   if (AspectComponent > AspectImage)
	   {
		   vector[0] = ComponentSize.x();
		   vector[1] = (Real32)((Real32)ComponentSize.x()/AspectImage);
	   }
	   else
	   {
		   vector[0] = (Real32)((Real32)ComponentSize.y()*AspectImage);
		   vector[1] = ComponentSize.y();
	   }
	   Size.setValue(vector);
	   }
	   break;
   case SCALE_ABSOLUTE:
	   Size.setValue(getScaleAbsoluteSize());
	   break;
   default:
	   break;
   }

   //Figure out Position
   Pnt2f Pos( calculateAlignment(TopLeft,ComponentSize, Size,getAlignment().y(), getAlignment().x()) );

   Vec2f TexTopLeft(0.0,0.0),
	     TexTopRight(1.0,0.0),
		 TexBottomLeft(0.0,1.0),
		 TexBottomRight(1.0,1.0);

   //Figure out Clipping
   //Left
   /*if(Pos.x() < TopLeft.x())
   {
	   //Clip Tex Coordinates
	   TexTopLeft[0] = TexBottomLeft[0] = ((Real32)TopLeft[0]-(Real32)Pos[0])/((Real32)Size[0]);
	   //Clip Left X
	   Pos[0] = TopLeft[0];
   }
   //Top
   if(Pos.y() < TopLeft.y())
   {
	   //Clip Tex Coordinates
	   TexTopLeft[1] = TexTopRight[1] = ((Real32)TopLeft[1]-(Real32)Pos[1])/((Real32)Size[1]);
	   //Clip Top Y
	   Pos[1] = TopLeft[1];
   }
   //Right
   if(Pos.x()+Size.x() > BottomRight.x())
   {
	   //Clip Tex Coordinates
	   TexTopRight[0] = TexBottomRight[0] = ((Real32)Pos[0]+(Real32)Size[0]-(Real32)BottomRight[0])/((Real32)Size[0]);
	   //Clip Right X
	   Pos[0] = BottomRight[0];
	   Size[0] = ComponentSize[0];
   }
   //Bottom
   if(Pos.y()+Size.y() > BottomRight.y())
   {
	   //Clip Tex Coordinates
	   TexBottomLeft[1] = TexBottomRight[1] = ((Real32)Pos[1]+(Real32)Size[1]-(Real32)BottomRight[1])/((Real32)Size[1]);
	   //Clip Right X
	   Pos[1] = BottomRight[1];
	   Size[1] = ComponentSize[1];
   }*/

   //Draw the Image as a quad
   TheGraphics->drawQuad(Pos,
	                     Pnt2f(Pos[0]+Size[0],Pos[1]),
						 Pos+Size,Pnt2f(Pos[0],
						 Pos[1]+Size[1]),
						 TexTopLeft,TexTopRight, 
						 TexBottomRight, TexBottomLeft, DrawnTexture, getOpacity() );
}


TextureChunkPtr ImageComponent::getDrawnTexture(void) const
{
	TextureChunkPtr ReturnedTexture;
	if(getEnabled())
	{
        if(getFocused())
        {
            ReturnedTexture = getFocusedTexture();
        }
        else if(_MouseInComponentLastMouse)
        {
            ReturnedTexture = getRolloverTexture();
        }
        else
        {
            return getTexture();
        }
    }
    else
    {
        ReturnedTexture = getDisabledTexture();
    }

	if(ReturnedTexture == NullFC)
	{
		return getTexture();
	}
	else
	{
		return ReturnedTexture;
	}
}

void ImageComponent::setImage(ImagePtr Image)
{
	if(getTexture() == NullFC)
	{
		beginEditCP(ImageComponentPtr(this), TextureFieldMask);
			setTexture(createTexture(Image));
		endEditCP(ImageComponentPtr(this), TextureFieldMask);
	}
	else
	{
		beginEditCP(getTexture(), TextureChunk::ImageFieldMask);
			getTexture()->setImage(Image);
		endEditCP(getTexture(), TextureChunk::ImageFieldMask);
	}
}

void ImageComponent::setRolloverImage(ImagePtr Image)
{
	if(getRolloverTexture() == NullFC)
	{
		beginEditCP(ImageComponentPtr(this), RolloverTextureFieldMask);
			setRolloverTexture(createTexture(Image));
		endEditCP(ImageComponentPtr(this), RolloverTextureFieldMask);
	}
	else
	{
		beginEditCP(getRolloverTexture(), TextureChunk::ImageFieldMask);
			getRolloverTexture()->setImage(Image);
		endEditCP(getRolloverTexture(), TextureChunk::ImageFieldMask);
	}
}

void ImageComponent::setDisabledImage(ImagePtr Image)
{
	if(getDisabledTexture() == NullFC)
	{
		beginEditCP(ImageComponentPtr(this), DisabledTextureFieldMask);
			setDisabledTexture(createTexture(Image));
		endEditCP(ImageComponentPtr(this), DisabledTextureFieldMask);
	}
	else
	{
		beginEditCP(getDisabledTexture(), TextureChunk::ImageFieldMask);
			getDisabledTexture()->setImage(Image);
		endEditCP(getDisabledTexture(), TextureChunk::ImageFieldMask);
	}
}

void ImageComponent::setFocusedImage(ImagePtr Image)
{
	if(getFocusedTexture() == NullFC)
	{
		beginEditCP(ImageComponentPtr(this), FocusedTextureFieldMask);
			setFocusedTexture(createTexture(Image));
		endEditCP(ImageComponentPtr(this), FocusedTextureFieldMask);
	}
	else
	{
		beginEditCP(getFocusedTexture(), TextureChunk::ImageFieldMask);
			getFocusedTexture()->setImage(Image);
		endEditCP(getFocusedTexture(), TextureChunk::ImageFieldMask);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ImageComponent::ImageComponent(void) :
    Inherited()
{
}

ImageComponent::ImageComponent(const ImageComponent &source) :
    Inherited(source)
{
}

ImageComponent::~ImageComponent(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImageComponent::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ImageComponent::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ImageComponent NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGIMAGECOMPONENTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGIMAGECOMPONENTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGIMAGECOMPONENTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


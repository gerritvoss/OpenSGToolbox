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
#include <OpenSG/OSGTextureTransformChunk.h>

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

void ImageComponent::drawInternal(const GraphicsPtr TheGraphics, Real32 Opacity) const
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

   Real32 Left(getImageClippingOffsets()[2]/Size.x()),
          Right(1.0+(getImageClippingOffsets()[3]/Size.x())),
          Top(-getImageClippingOffsets()[1]/Size.y()),
          Bottom(1.0-(getImageClippingOffsets()[0]/Size.y()));

   Pos  = Pos + Vec2f(getImageClippingOffsets()[2],getImageClippingOffsets()[0]);
   Size = Size + Vec2f(-getImageClippingOffsets()[2]+getImageClippingOffsets()[3],
                       -getImageClippingOffsets()[0]+getImageClippingOffsets()[1]
                       );


   Vec2f TexTopLeft(Left,Top),
	     TexTopRight(Right,Top),
		 TexBottomLeft(Left,Bottom),
		 TexBottomRight(Right,Bottom);

    //Activate the Texture Transformation
    if(getTransformation() != NullFC)
    {
        getTransformation()->activate(TheGraphics->getDrawAction());
    }

   //Draw the Image as a quad
   TheGraphics->drawQuad(Pos,
	                     Pnt2f(Pos[0]+Size[0],Pos[1]),
						 Pos+Size,Pnt2f(Pos[0],
						 Pos[1]+Size[1]),
						 TexTopLeft,TexTopRight, 
						 TexBottomRight, TexBottomLeft, getColor(), DrawnTexture, getOpacity()*Opacity );

    //Deactivate the Texture Transformation
    if(getTransformation() != NullFC)
    {
        getTransformation()->deactivate(TheGraphics->getDrawAction());
    }
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

OSG_END_NAMESPACE


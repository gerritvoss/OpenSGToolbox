/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGImageComponent.h"
#include "OSGTextureTransformChunk.h"
#include "OSGTextureObjChunk.h"

#include "OSGImageComponent.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGImageComponentBase.cpp file.
// To modify it, please change the .fcd file (OSGImageComponent.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ImageComponent::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


TextureObjChunkTransitPtr ImageComponent::createTexture(Image* Image)
{
    TextureObjChunk* TexChunk = TextureObjChunk::createEmpty();

    TexChunk->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    TexChunk->setMagFilter(GL_LINEAR);
    TexChunk->setWrapS(GL_CLAMP);
    TexChunk->setWrapT(GL_CLAMP);
    //TexChunk->setEnvMode(GL_MODULATE);
    TexChunk->setImage(Image);

    return TextureObjChunkTransitPtr(TexChunk);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ImageComponent::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{

    //Get Border Insets
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);
    Vec2f ComponentSize(BottomRight-TopLeft);

    TextureBaseChunk* DrawnTexture = getDrawnTexture();
    if(DrawnTexture == NULL ||
       (DrawnTexture->getType() == TextureObjChunk::getClassType() &&
        dynamic_cast<TextureObjChunk*>(DrawnTexture)->getImage() == NULL))
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
            Size.setValues(dynamic_cast<TextureObjChunk*>(DrawnTexture)->getImage()->getWidth(),
                           dynamic_cast<TextureObjChunk*>(DrawnTexture)->getImage()->getHeight());
            break;
        case SCALE_STRETCH:
            Size.setValue(ComponentSize);
            break;
        case SCALE_MIN_AXIS:
            {
                //Figure out the aspect ratio of this Component
                Real32 AspectComponent = ComponentSize.x()/ComponentSize.y();
                Real32 AspectImage = static_cast<Real32>(dynamic_cast<TextureObjChunk*>(DrawnTexture)->getImage()->getWidth()) / 
                    static_cast<Real32>(dynamic_cast<TextureObjChunk*>(DrawnTexture)->getImage()->getHeight());

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
                Real32 AspectImage = static_cast<Real32>(dynamic_cast<TextureObjChunk*>(DrawnTexture)->getImage()->getWidth()) / 
                    static_cast<Real32>(dynamic_cast<TextureObjChunk*>(DrawnTexture)->getImage()->getHeight());

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
    if(getTransformation() != NULL)
    {
        getTransformation()->activate(TheGraphics->getDrawEnv());
    }

    //Draw the Image as a quad
    TheGraphics->drawQuad(Pos,
                          Pnt2f(Pos[0]+Size[0],Pos[1]),
                          Pos+Size,Pnt2f(Pos[0],
                                         Pos[1]+Size[1]),
                          TexTopLeft,TexTopRight, 
                          TexBottomRight, TexBottomLeft, getColor(), DrawnTexture, getOpacity()*Opacity );

    //Deactivate the Texture Transformation
    if(getTransformation() != NULL)
    {
        getTransformation()->deactivate(TheGraphics->getDrawEnv());
    }
}


TextureBaseChunk* ImageComponent::getDrawnTexture(void) const
{
    TextureBaseChunk* ReturnedTexture;
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

    if(ReturnedTexture == NULL)
    {
        return getTexture();
    }
    else
    {
        return ReturnedTexture;
    }
}

void ImageComponent::setImages(Image* const TheImage)
{
    setImage(TheImage);
    setRolloverTexture(getTexture());
    setDisabledTexture(getTexture());
    setFocusedTexture(getTexture());
}

void ImageComponent::setImages(const BoostPath& fileName, const char *mimeType)
{
    setImage(fileName.string().c_str(), mimeType);
    setRolloverTexture(getTexture());
    setDisabledTexture(getTexture());
    setFocusedTexture(getTexture());
}

void ImageComponent::setImage(Image* const Image)
{
    if(getTexture() == NULL)
    {
        TextureObjChunkUnrecPtr NewTexture(createTexture(Image));
        setTexture(NewTexture);
    }
    else if(getTexture()->getType() == TextureObjChunk::getClassType())
    {
        dynamic_cast<TextureObjChunk*>(getTexture())->setImage(Image);
    }
}

void ImageComponent::setRolloverImage(Image* const Image)
{
    if(getRolloverTexture() == NULL)
    {
        TextureObjChunkUnrecPtr NewTexture(createTexture(Image));
        setRolloverTexture(NewTexture);
    }
    else if(getTexture()->getType() == TextureObjChunk::getClassType())
    {
        dynamic_cast<TextureObjChunk*>(getRolloverTexture())->setImage(Image);
    }
}

void ImageComponent::setDisabledImage(Image* const Image)
{
    if(getDisabledTexture() == NULL)
    {
        TextureObjChunkUnrecPtr NewTexture(createTexture(Image));
        setDisabledTexture(NewTexture);
    }
    else if(getTexture()->getType() == TextureObjChunk::getClassType())
    {
        dynamic_cast<TextureObjChunk*>(getDisabledTexture())->setImage(Image);
    }
}

void ImageComponent::setFocusedImage(Image* const Image)
{
    if(getFocusedTexture() == NULL)
    {
        TextureObjChunkUnrecPtr NewTexture(createTexture(Image));
        setFocusedTexture(NewTexture);
    }
    else if(getTexture()->getType() == TextureObjChunk::getClassType())
    {
        dynamic_cast<TextureObjChunk*>(getFocusedTexture())->setImage(Image);
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

void ImageComponent::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & TextureFieldMask) &&
       getTexture() != NULL &&
       getTexture()->getType() != TextureObjChunk::getClassType() &&
       (getScale() == SCALE_NONE ||
        getScale() == SCALE_MIN_AXIS ||
        getScale() == SCALE_MAX_AXIS))
    {
        SWARNING << "Can only use scaling of SCALE_NONE, SCALE_MIN_AXIS, SCALE_MAX_AXIS, with TextureObjChunks." << std::endl;
        setScale(SCALE_STRETCH);
    }

    if((whichField & RolloverTextureFieldMask) &&
       getRolloverTexture() != NULL &&
       getRolloverTexture()->getType() != TextureObjChunk::getClassType() &&
       (getScale() == SCALE_NONE ||
        getScale() == SCALE_MIN_AXIS ||
        getScale() == SCALE_MAX_AXIS))
    {
        SWARNING << "Can only use scaling of SCALE_NONE, SCALE_MIN_AXIS, SCALE_MAX_AXIS, with TextureObjChunks." << std::endl;
        setScale(SCALE_STRETCH);
    }

    if((whichField & DisabledTextureFieldMask) &&
       getDisabledTexture() != NULL &&
       getDisabledTexture()->getType() != TextureObjChunk::getClassType() &&
       (getScale() == SCALE_NONE ||
        getScale() == SCALE_MIN_AXIS ||
        getScale() == SCALE_MAX_AXIS))
    {
        SWARNING << "Can only use scaling of SCALE_NONE, SCALE_MIN_AXIS, SCALE_MAX_AXIS, with TextureObjChunks." << std::endl;
        setScale(SCALE_STRETCH);
    }

    if((whichField & FocusedTextureFieldMask) &&
       getFocusedTexture() != NULL &&
       getFocusedTexture()->getType() != TextureObjChunk::getClassType() &&
       (getScale() == SCALE_NONE ||
        getScale() == SCALE_MIN_AXIS ||
        getScale() == SCALE_MAX_AXIS))
    {
        SWARNING << "Can only use scaling of SCALE_NONE, SCALE_MIN_AXIS, SCALE_MAX_AXIS, with TextureObjChunks." << std::endl;
        setScale(SCALE_STRETCH);
    }
}

void ImageComponent::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ImageComponent NI" << std::endl;
}

OSG_END_NAMESPACE

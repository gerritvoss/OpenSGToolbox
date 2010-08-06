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

#include "OSGTextureLayer.h"
#include "OSGTextureObjChunk.h"
#include "OSGTextureTransformChunk.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextureLayerBase.cpp file.
// To modify it, please change the .fcd file (OSGTextureLayer.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextureLayer::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TextureLayer::draw(Graphics* const TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const
{
    if(!getTexture())
    {
        return;
    }

	glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	GLdouble Plane0[4], Plane1[4], Plane2[4], Plane3[4];
	glGetClipPlane(GL_CLIP_PLANE0, Plane0);
	glGetClipPlane(GL_CLIP_PLANE1, Plane1);
	glGetClipPlane(GL_CLIP_PLANE2, Plane2);
	glGetClipPlane(GL_CLIP_PLANE3, Plane3);

	//bool WasClipPlane0Enabled = glIsEnabled(GL_CLIP_PLANE0);
 //   bool WasClipPlane1Enabled = glIsEnabled(GL_CLIP_PLANE1);
 //   bool WasClipPlane2Enabled = glIsEnabled(GL_CLIP_PLANE2);
 //   bool WasClipPlane3Enabled = glIsEnabled(GL_CLIP_PLANE3);

	//if(!WasClipPlane0Enabled) { glEnable(GL_CLIP_PLANE0); }
 //   if(!WasClipPlane1Enabled) { glEnable(GL_CLIP_PLANE1); }
 //   if(!WasClipPlane2Enabled) { glEnable(GL_CLIP_PLANE2); }
 //   if(!WasClipPlane3Enabled) { glEnable(GL_CLIP_PLANE3); }
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);

	// The clipping plane for the background must get set to inside the
	// border of the component. It was the outside of the component,
	// so it has to be reset to the stored values from above at the end.
	Vec4d LeftPlaneEquation(1.0,0.0,0.0,-TopLeft.x()),
          RightPlaneEquation(-1.0,0.0,0.0,BottomRight.x()),
          TopPlaneEquation(0.0,1.0,0.0,-TopLeft.y()),
          BottomPlaneEquation(0.0,-1.0,0.0,BottomRight.y());
    
    glClipPlane(GL_CLIP_PLANE0,LeftPlaneEquation.getValues());
    glClipPlane(GL_CLIP_PLANE1,RightPlaneEquation.getValues());
    glClipPlane(GL_CLIP_PLANE2,TopPlaneEquation.getValues());
    glClipPlane(GL_CLIP_PLANE3,BottomPlaneEquation.getValues());

    //Activate the Texture Transformation
    if(getTransformation() != NULL)
    {
        getTransformation()->activate(TheGraphics->getDrawEnv());
    }

	Vec2f BackgroundSize (BottomRight - TopLeft);

	Vec2f Size(0.0,0.0);
	switch(getScale())
	{
	case SCALE_NONE:
	   //Size in pixels Should be the Image size in pixels
	   Size.setValues(dynamic_cast<TextureObjChunk*>(getTexture())->getImage()->getWidth(),
                      dynamic_cast<TextureObjChunk*>(getTexture())->getImage()->getHeight());
	   break;
	case SCALE_STRETCH:
	   Size.setValue(BackgroundSize);
	   break;
	case SCALE_MIN_AXIS:
	   {
	   //Figure out the aspect ratio of this Component
	   Real32 AspectBackground = BackgroundSize.x()/BackgroundSize.y();
	   Real32 AspectImage = static_cast<Real32>(dynamic_cast<TextureObjChunk*>(getTexture())->getImage()->getWidth()) / 
           static_cast<Real32>(dynamic_cast<TextureObjChunk*>(getTexture())->getImage()->getHeight());

	   Vec2f vector(0,0);
	   if (AspectBackground < AspectImage)
	   {
		   vector[0] = BackgroundSize.x();
		   vector[1] = ((Real32)BackgroundSize.x()/AspectImage);
	   }
	   else
	   {
		   vector[0] = ((Real32)BackgroundSize.y()*AspectImage);
		   vector[1] = BackgroundSize.y();
	   }
	   Size.setValue(vector);
	   }
	   break;
	case SCALE_MAX_AXIS:
	   {
	   //Figure out the aspect ratio of this Component
	   Real32 AspectBackground = BackgroundSize.x()/BackgroundSize.y();
	   Real32 AspectImage = static_cast<Real32>(dynamic_cast<TextureObjChunk*>(getTexture())->getImage()->getWidth()) /
           static_cast<Real32>(dynamic_cast<TextureObjChunk*>(getTexture())->getImage()->getHeight());

	   Vec2f vector(0,0);
	   if (AspectBackground > AspectImage)
	   {
		   vector[0] = BackgroundSize.x();
		   vector[1] = ((Real32)BackgroundSize.x()/AspectImage);
	   }
	   else
	   {
		   vector[0] = ((Real32)BackgroundSize.y()*AspectImage);
		   vector[1] = BackgroundSize.y();
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

	Pnt2f Pos( calculateAlignment(TopLeft,BackgroundSize, Size, getVerticalAlignment(), getHorizontalAlignment()) );

	/*Vec2f TexTopLeft(0.0,0.0),
	      TexTopRight(1.0,0.0),
		  TexBottomLeft(0.0,1.0),
		  TexBottomRight(1.0,1.0);*/

	TheGraphics->drawQuad(Pos, Pnt2f(Pos.x()+Size.x(), Pos.y()), Pos+Size, Pnt2f(Pos.x(), Pos.y()+Size.y()),
            Vec2f(0.0, 0.0), Vec2f(1.0, 0.0), Vec2f(1.0, 1.0), Vec2f(0.0, 1.0),
            getColor(), getTexture(), Opacity);

	//if(!WasClipPlane0Enabled) { glDisable(GL_CLIP_PLANE0); }
 //   if(!WasClipPlane1Enabled) { glDisable(GL_CLIP_PLANE1); }
 //   if(!WasClipPlane2Enabled) { glDisable(GL_CLIP_PLANE2); }
 //   if(!WasClipPlane3Enabled) { glDisable(GL_CLIP_PLANE3); }

    //Deactivate the Texture Transformation
    if(getTransformation() != NULL)
    {
        getTransformation()->deactivate(TheGraphics->getDrawEnv());
    }
    
	glPopAttrib();
	//glClipPlane(GL_CLIP_PLANE0, Plane0);
	//glClipPlane(GL_CLIP_PLANE1, Plane1);
	//glClipPlane(GL_CLIP_PLANE2, Plane2);
	//glClipPlane(GL_CLIP_PLANE3, Plane3);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextureLayer::TextureLayer(void) :
    Inherited()
{
}

TextureLayer::TextureLayer(const TextureLayer &source) :
    Inherited(source)
{
}

TextureLayer::~TextureLayer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextureLayer::changed(ConstFieldMaskArg whichField, 
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
}

void TextureLayer::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextureLayer NI" << std::endl;
}

OSG_END_NAMESPACE

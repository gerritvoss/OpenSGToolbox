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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGImage.h>

#include "OSGPatternUIBackground.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PatternUIBackground
UI Texture Background. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PatternUIBackground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PatternUIBackground::draw(const GraphicsPtr TheGraphics, const Pnt2f& TopLeft, const Pnt2f& BottomRight, const Real32 Opacity) const
{
	glPushAttrib(GL_ENABLE_BIT | GL_TRANSFORM_BIT);
	GLdouble Plane0[4], Plane1[4], Plane2[4], Plane3[4];
	glGetClipPlane(GL_CLIP_PLANE0, Plane0);
	glGetClipPlane(GL_CLIP_PLANE1, Plane1);
	glGetClipPlane(GL_CLIP_PLANE2, Plane2);
	glGetClipPlane(GL_CLIP_PLANE3, Plane3);

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

	Vec2f BackgroundSize (BottomRight - TopLeft);
	Vec2f TopLeftTexCoords(0.0f,0.0f);
	Vec2f BottomRightTexCoords(1.0f,1.0f);

	GLenum WrapS;
	GLenum WrapT;

	Real32 RepeatHorizontal;
	switch(getHorizontalRepeat())
	{
	case PATTERN_REPEAT_ABSOLUTE:
		RepeatHorizontal = getHorizontalRepeatValue();
		break;
	case PATTERN_REPEAT_BY_POINT:
	default:
		RepeatHorizontal = static_cast<Real32>(BottomRight.x() - TopLeft.x())/static_cast<Real32>(getCorrectedPatternSize().x());
		break;
	}

	TopLeftTexCoords[0] = -getHorizontalAlignment() * (RepeatHorizontal -1.0f);
	BottomRightTexCoords[0] = TopLeftTexCoords[0] + RepeatHorizontal;
	
	Real32 RepeatVertical;
	switch(getVerticalRepeat())
	{
	case PATTERN_REPEAT_ABSOLUTE:
		RepeatVertical = getVerticalRepeatValue();
		break;
	case PATTERN_REPEAT_BY_POINT:
	default:
		RepeatVertical = static_cast<Real32>(BottomRight.y() - TopLeft.y())/static_cast<Real32>(getCorrectedPatternSize().y());
		break;
	}
	
	TopLeftTexCoords[1] = -getVerticalAlignment() * (RepeatVertical - 1.0f);
	BottomRightTexCoords[1] = TopLeftTexCoords[1] + RepeatVertical;

	TheGraphics->drawQuad(TopLeft, Pnt2f(BottomRight.x(), TopLeft.y()),BottomRight, Pnt2f(TopLeft.x(), BottomRight.y()),
		TopLeftTexCoords, Vec2f(BottomRightTexCoords.x(), TopLeftTexCoords.y()), BottomRightTexCoords, Vec2f(TopLeftTexCoords.x(), BottomRightTexCoords.y()),
		getTexture(), Opacity);

	glPopAttrib();
}

Vec2f PatternUIBackground::getCorrectedPatternSize(void) const
{
	Vec2f PatternSize(getPatternSize());
	if(PatternSize.x() == -1 &&
		getTexture() != NullFC &&
        getTexture()->getImage() != NullFC)
	{
		PatternSize[0] = getTexture()->getImage()->getWidth();
	}

	if(PatternSize.y() == -1 &&
		getTexture() != NullFC &&
        getTexture()->getImage() != NullFC)
	{
		PatternSize[1] = getTexture()->getImage()->getHeight();
	}

	return PatternSize;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PatternUIBackground::PatternUIBackground(void) :
    Inherited()
{
}

PatternUIBackground::PatternUIBackground(const PatternUIBackground &source) :
    Inherited(source)
{
}

PatternUIBackground::~PatternUIBackground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PatternUIBackground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PatternUIBackground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PatternUIBackground NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPATTERNUIBACKGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPATTERNUIBACKGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPATTERNUIBACKGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


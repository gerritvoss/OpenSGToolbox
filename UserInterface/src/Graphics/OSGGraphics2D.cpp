/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGGraphics2D.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Graphics2D
A Concrete 2D UI Graphics.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Graphics2D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Graphics2D::preDraw()
{
	_light = glIsEnabled(GL_LIGHTING);

	glGetIntegerv(GL_POLYGON_MODE, _fill);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	_depth = glIsEnabled(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_TEST);

	_colmat = glIsEnabled(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR_MATERIAL);

	glDisable(GL_TEXTURE_2D);
}

void Graphics2D::postDraw()
{
	if(_depth == GL_TRUE)
	{
		glEnable(GL_DEPTH_TEST);
	}
	if(_light == GL_TRUE)
	{
		glEnable(GL_LIGHTING);
	}
	if(_colmat == GL_TRUE)
	{
		glEnable(GL_COLOR_MATERIAL);
	}
	glPolygonMode(GL_FRONT, _fill[0]);
	glPolygonMode(GL_BACK , _fill[1]);
}

void Graphics2D::drawRect(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color4f& Color) const
{
	if(Color.alpha() < 1.0)
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	glBegin(GL_QUADS);
	   glColor4fv(Color.getValuesRGBA());
	   glVertex2sv(TopLeft.getValues());
	   glVertex2s(BottomRight.x(), TopLeft.y());
	   glVertex2sv(BottomRight.getValues());
	   glVertex2s(TopLeft.x(), BottomRight.y());
	glEnd();
	
	if(Color.alpha() < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawLine(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Real32& Width, const Color4f& Color) const
{
	GLfloat previousLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &previousLineWidth);
	if(Color.alpha() < 1.0)
	{
		//Setup the blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	glLineWidth(Width);
	glBegin(GL_LINES);
		glColor4fv(Color.getValuesRGBA());
		glVertex2sv(TopLeft.getValues());
		glVertex2sv(BottomRight.getValues());
	glEnd();
	if(Color.alpha() < 1.0)
	{
		glDisable(GL_BLEND);
	}
	glLineWidth(previousLineWidth);
}

void Graphics2D::drawPolygon(const MFPnt2s Verticies, const Color4f& Color) const
{
	if(Color.alpha() < 1.0)
	{
		//Setup the Blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	
	glBegin(GL_POLYGON);
	   glColor4fv(Color.getValuesRGBA());
	   for(UInt32 i=0 ; i<Verticies.size() ; ++i)
	   {
	      glVertex2sv(Verticies.getValue(i).getValues());
	   }
	glEnd();
	
	if(Color.alpha() < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawDisc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const UInt16& SubDivisions, const Color4f& Color) const
{
	Real32 angleNow = StartAngleRad;
	Real32 angleDiff = (EndAngleRad-StartAngleRad)/(Real32)SubDivisions;
	if(EndAngleRad-StartAngleRad > 2*3.1415926535)
		angleDiff = 2*3.1415926535;
	if(Color.alpha() < 1.0)
	{
		//Setup the blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	
	glBegin(GL_TRIANGLE_FAN);
		glColor4fv(Color.getValuesRGBA());
		glVertex2sv(Center.getValues());
		while(angleNow < EndAngleRad){
			glVertex2s(Center.x() + Width*osgcos(angleNow), Center.y() + Height*osgsin(angleNow));
			angleNow += angleDiff;
		}
	glEnd();

		if(Color.alpha() < 1.0)
	{
		glDisable(GL_BLEND);
	}
}

void Graphics2D::drawArc(const Pnt2s& Center, const Int16& Width, const Int16& Height, const Real32& StartAngleRad, const Real32& EndAngleRad, const Real32& LineWidth, const UInt16& SubDivisions, const Color4f& Color) const
{
	GLfloat previousLineWidth;
	glGetFloatv(GL_LINE_WIDTH, &previousLineWidth);
	Real32 angleNow = StartAngleRad;
	Real32 angleDiff = (EndAngleRad-StartAngleRad)/(Real32)SubDivisions;
	//If andle difference is bigger to a circle, set it to equal to a circle
	if(EndAngleRad-StartAngleRad > 2*3.1415926535)
		angleDiff = 2*3.1415926535;
	if(Color.alpha() < 1.0)
	{
		//Setup the blending equations properly
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}
	glLineWidth(LineWidth);
	glBegin(GL_LINE_STRIP);
		glColor4fv(Color.getValuesRGBA());
		//draw vertex lines
		while(angleNow + angleDiff  < EndAngleRad){
			glVertex2s( Center.x() + Width*osgcos(angleNow ),Center.y() +Height*osgsin(angleNow));
			//glVertex2s(Center.x() + Width*osgcos(angleNow + angleDiff), Center.y() + Height*osgsin(angleNow+angleDiff));
			angleNow += angleDiff;
		}
	glEnd();

	
		if(Color.alpha() < 1.0)
	{
		glDisable(GL_BLEND);
	}
			glLineWidth(previousLineWidth);
}

void Graphics2D::drawLoweredBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color3f& Color, const Int16& Width) const
{
}

void Graphics2D::drawRaisedBevel(const Pnt2s& TopLeft, const Pnt2s& BottomRight, const Color3f& Color, const Int16& Width) const
{
}

void Graphics2D::drawString(const Pnt2s& Position, const std::string& Text) const
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Graphics2D::Graphics2D(void) :
    Inherited()
{
}

Graphics2D::Graphics2D(const Graphics2D &source) :
    Inherited(source)
{
}

Graphics2D::~Graphics2D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Graphics2D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Graphics2D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Graphics2D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGRAPHICS2DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRAPHICS2DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRAPHICS2DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


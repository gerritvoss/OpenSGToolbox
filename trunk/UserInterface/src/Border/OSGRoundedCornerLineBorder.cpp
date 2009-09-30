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

#include "OSGRoundedCornerLineBorder.h"
#include "Graphics/OSGGraphics.h"
#include "Graphics/OSGGraphics3DExtrude.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RoundedCornerLineBorder
UI Line Border. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void RoundedCornerLineBorder::initMethod (void)
{
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void RoundedCornerLineBorder::draw(const GraphicsPtr g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity, bool Clipping) const
{
    if(Clipping)
    {
        deactivateInternalDrawConstraints(g,x,y,Width,Height);
    }

	//draw corners
	g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 3.14159265, 4.71238898, 10, getColor(), getColor(), Opacity);
	g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 1.57079633, 3.14159265, 10, getColor(), getColor(), Opacity);
	g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 0, 1.57079633, 10, getColor(), getColor(), Opacity);
	g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius(), 4.71238898,6.28318531, 10, getColor(), getColor(), Opacity);

	//draw sides
	g->drawRect(Pnt2f(x, y+getCornerRadius()), Pnt2f(x+getWidth(), y+Height-getCornerRadius()), getColor(), Opacity);
	g->drawRect(Pnt2f(x+getCornerRadius(), y), Pnt2f(x+Width-getCornerRadius(), y+getWidth()), getColor(), Opacity);
	g->drawRect(Pnt2f(x+Width-getWidth(), y+getCornerRadius()), Pnt2f(x+Width, y+Height-getCornerRadius()), getColor(), Opacity);
	g->drawRect(Pnt2f(x+getCornerRadius(), y+Height-getWidth()), Pnt2f(x+Width-getCornerRadius(), y+Height), getColor(), Opacity);
}

void RoundedCornerLineBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
	//TODO:Implement
	Left=Right=Top=Bottom = getWidth(); //wrong, but what else are you supposed to do?
}

void RoundedCornerLineBorder::activateInternalDrawConstraints(const GraphicsPtr g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    g->incrDrawBounderiesNesting();

    g->initAddDrawBounderies();

    glBegin(GL_QUADS);
       glVertex2s(x-1,y+getCornerRadius()-1);
       glVertex2s(x-1,y+Height-getCornerRadius()+1);
       glVertex2s(x+Width+1,y+Height-getCornerRadius()+1);
       glVertex2s(x+Width+1,y+getCornerRadius()-1);
       
       glVertex2s(x+getCornerRadius()-1,y-1);
       glVertex2s(x+getCornerRadius()-1,y+Height+1);
       glVertex2s(x+Width-getCornerRadius()+1,y+Height+1);
       glVertex2s(x+Width-getCornerRadius()+1,y-1);
    glEnd();

    g->drawDisc(Pnt2f(x+getCornerRadius(), y+getCornerRadius()),              getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 3.14159265, 4.71238898, 10, getColor(), getColor(), 1.0);
	g->drawDisc(Pnt2f(x+getCornerRadius(), y+Height-getCornerRadius()),       getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 1.57079633, 3.14159265, 10, getColor(), getColor(), 1.0);
	g->drawDisc(Pnt2f(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 0, 1.57079633, 10, getColor(), getColor(), 1.0);
	g->drawDisc(Pnt2f(x+Width-getCornerRadius(), y+getCornerRadius()),        getCornerRadius()-getWidth()+1, getCornerRadius()-getWidth()+1, 4.71238898,6.28318531, 10, getColor(), getColor(), 1.0);

    g->uninitAddDrawBounderies();

    g->initRemoveDrawBounderies();

	//Special case if the Graphics are 3dExtrude
	if(g->getType().isDerivedFrom(Graphics3DExtrude::getClassType()))
	{
		Real32 ExtrudeLength(Graphics3DExtrude::Ptr::dcast(g)->getExtrudeLength());
		beginEditCP(Graphics3DExtrude::Ptr::dcast(g), Graphics3DExtrude::ExtrudeLengthFieldMask);
			Graphics3DExtrude::Ptr::dcast(g)->setExtrudeLength(0.0f);
		endEditCP(Graphics3DExtrude::Ptr::dcast(g), Graphics3DExtrude::ExtrudeLengthFieldMask);
		//Front Side
		//draw corners
		g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 3.14159265, 4.71238898, 10, getColor(), getColor(), 1.0);
		g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 1.57079633, 3.14159265, 10, getColor(), getColor(), 1.0);
		g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 0, 1.57079633, 10, getColor(), getColor(), 1.0);
		g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 4.71238898,6.28318531, 10, getColor(), getColor(), 1.0);

		//draw sides
		g->drawRect(Pnt2f(x-1, y+getCornerRadius()), Pnt2f(x+getWidth(), y+Height-getCornerRadius()), getColor(), 1.0);
		g->drawRect(Pnt2f(x+getCornerRadius(), y-1), Pnt2f(x+Width-getCornerRadius(), y+getWidth()), getColor(), 1.0);
		g->drawRect(Pnt2f(x+Width-getWidth(), y+getCornerRadius()), Pnt2f(x+Width+1, y+Height-getCornerRadius()), getColor(), 1.0);
		g->drawRect(Pnt2f(x+getCornerRadius(), y+Height-getWidth()), Pnt2f(x+Width-getCornerRadius(), y+Height+1), getColor(), 1.0);

		//Back Side
		/*glPushMatrix();
			glTranslatef(0.0f,0.0f,ExtrudeLength);
			
			//draw corners
			g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 3.14159265, 4.71238898, 10, getColor(), getColor(), 1.0);
			g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 1.57079633, 3.14159265, 10, getColor(), getColor(), 1.0);
			g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 0, 1.57079633, 10, getColor(), getColor(), 1.0);
			g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 4.71238898,6.28318531, 10, getColor(), getColor(), 1.0);

			//draw sides
			g->drawRect(Pnt2f(x-1, y+getCornerRadius()), Pnt2f(x+getWidth(), y+Height-getCornerRadius()), getColor(), 1.0);
			g->drawRect(Pnt2f(x+getCornerRadius(), y-1), Pnt2f(x+Width-getCornerRadius(), y+getWidth()), getColor(), 1.0);
			g->drawRect(Pnt2f(x+Width-getWidth(), y+getCornerRadius()), Pnt2f(x+Width+1, y+Height-getCornerRadius()), getColor(), 1.0);
			g->drawRect(Pnt2f(x+getCornerRadius(), y+Height-getWidth()), Pnt2f(x+Width-getCornerRadius(), y+Height+1), getColor(), 1.0);
		glPopMatrix();*/

		
		beginEditCP(Graphics3DExtrude::Ptr::dcast(g), Graphics3DExtrude::ExtrudeLengthFieldMask);
			Graphics3DExtrude::Ptr::dcast(g)->setExtrudeLength(ExtrudeLength);
		endEditCP(Graphics3DExtrude::Ptr::dcast(g), Graphics3DExtrude::ExtrudeLengthFieldMask);
	}
	else
	{
		//draw corners
		g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 3.14159265, 4.71238898, 10, getColor(), getColor(), 1.0);
		g->drawComplexDisc(Pnt2f(x+getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 1.57079633, 3.14159265, 10, getColor(), getColor(), 1.0);
		g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+Height-getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 0, 1.57079633, 10, getColor(), getColor(), 1.0);
		g->drawComplexDisc(Pnt2f(x+Width-getCornerRadius(), y+getCornerRadius()), getCornerRadius()-getWidth(), getCornerRadius()+1, 4.71238898,6.28318531, 10, getColor(), getColor(), 1.0);

		//draw sides
		g->drawRect(Pnt2f(x-1, y+getCornerRadius()), Pnt2f(x+getWidth(), y+Height-getCornerRadius()), getColor(), 1.0);
		g->drawRect(Pnt2f(x+getCornerRadius(), y-1), Pnt2f(x+Width-getCornerRadius(), y+getWidth()), getColor(), 1.0);
		g->drawRect(Pnt2f(x+Width-getWidth(), y+getCornerRadius()), Pnt2f(x+Width+1, y+Height-getCornerRadius()), getColor(), 1.0);
		g->drawRect(Pnt2f(x+getCornerRadius(), y+Height-getWidth()), Pnt2f(x+Width-getCornerRadius(), y+Height+1), getColor(), 1.0);
	}

    g->uninitRemoveDrawBounderies();
    g->activateDrawBounderiesTest();
}

void RoundedCornerLineBorder::deactivateInternalDrawConstraints(const GraphicsPtr g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    g->decrDrawBounderiesNestring();

    g->initRemoveDrawBounderies();

    glBegin(GL_QUADS);
       glVertex2s(x-2,y-2);
       glVertex2s(x+Width+2,y-2);
       glVertex2s(x+Width+2,y+Height+2);
       glVertex2s(x-2,y+Height+2);
    glEnd();

    g->uninitRemoveDrawBounderies();

    g->deactivateDrawBounderiesTest();
}

bool RoundedCornerLineBorder::isContained(const Pnt2f& p, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    bool AreCornersContained(true);
    //TopLeft Corner
    if(p.x() >= x && p.x() <= x+getCornerRadius() &&
            p.y() >= y && p.y() <= y+getCornerRadius())
    {
        Real32 Length = p.dist(Pnt2f(x+getCornerRadius(),y+getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    //BottomLeft Corner
    if(p.x() >= x && p.x() <= x+getCornerRadius() &&
            p.y() >= y+Height-getCornerRadius() && p.y() <= y+Height)
    {
        Real32 Length = p.dist(Pnt2f(x+getCornerRadius(),y+Height-getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    //TopRight Corner
    if(p.x() >= x+Width-getCornerRadius() && p.x() <= x+Width &&
            p.y() >= y && p.y() <= y+getCornerRadius())
    {
        Real32 Length = p.dist(Pnt2f(x+Width-getCornerRadius(),y+getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    //BottomRight Corner
    if(p.x() >= x+Width-getCornerRadius() && p.x() <= x+Width &&
            p.y() >= y+Height-getCornerRadius() && p.y() <= y+Height)
    {
        Real32 Length = p.dist(Pnt2f(x+Width-getCornerRadius(),y+Height-getCornerRadius()));
        AreCornersContained = AreCornersContained && Length <= getCornerRadius();
    }
    return AreCornersContained &&
           (p.x() >= x && p.x() <= x+Width &&
            p.y() >= y && p.y() <= y+Height);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

RoundedCornerLineBorder::RoundedCornerLineBorder(void) :
    Inherited()
{
}

RoundedCornerLineBorder::RoundedCornerLineBorder(const RoundedCornerLineBorder &source) :
    Inherited(source)
{
}

RoundedCornerLineBorder::~RoundedCornerLineBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void RoundedCornerLineBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void RoundedCornerLineBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump RoundedCornerLineBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGROUNDEDCORNERLINEBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGROUNDEDCORNERLINEBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGROUNDEDCORNERLINEBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


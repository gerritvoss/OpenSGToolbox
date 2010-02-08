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

#include "OSGShadowBorder.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShadowBorder
UI Shadow Border. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShadowBorder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ShadowBorder::draw(const GraphicsPtr g, const Real32 x, const Real32 y , const Real32 Width, const Real32 Height, const Real32 Opacity, bool Clipping) const
{
	//Draw the Inside Border
    getInsideBorder()->draw(g, x+getLeftOffset(), y+getTopOffset(),Width-getRightOffset()-getLeftOffset(),Height-getTopOffset()-getBottomOffset(), Opacity);


}

void ShadowBorder::getInsets(Real32& Left, Real32& Right,Real32& Top,Real32& Bottom) const
{
    if(getInsideBorder() != NullFC)
    {
        getInsideBorder()->getInsets(Left, Right, Top, Bottom);
    }
    else
    {
        SWARNING << "Warning: ShadowBorder::getInsets: InsideBorder is NULL." << std::endl;
        Left = Right = Top = Bottom = 0.0f;
    }
    Left +=getLeftOffset();
    Right +=getRightOffset();
    Top +=getTopOffset();
    Bottom +=getBottomOffset();
}

void ShadowBorder::activateInternalDrawConstraints(const GraphicsPtr g, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    //Determine TopLeft and BottomRight of the Shadow
    Pnt2f ShadowTopLeft,
          ShadowBottomRight;

    //Top
    if(getTopOffset() > 0) { ShadowTopLeft[1] = y; }
    else { ShadowTopLeft[1] = y + getBottomOffset(); }
    
    //Bottom
    if(getBottomOffset() > 0) { ShadowBottomRight[1] = y+Height; }
    else { ShadowBottomRight[1] = y + Height - getTopOffset(); }

    //Left
    if(getLeftOffset() > 0) { ShadowTopLeft[0] = x; }
    else { ShadowTopLeft[0] = x + getRightOffset(); }

    //Right
    if(getRightOffset() > 0) { ShadowBottomRight[0] = x+Width; }
    else { ShadowBottomRight[0] = x + Width - getLeftOffset(); }

    //Draw the Shadow
    //TODO: Add some prettier drawing types for the shadow
    if(getCornerRadius() == 0)
    {
        //Corners
        //TopLeft
        g->drawQuad(Pnt2f(ShadowTopLeft.x(),ShadowTopLeft.y()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getInternalColor(), getEdgeColor(), 1.0f);
        //TopRight
        g->drawQuad(Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2f(ShadowBottomRight.x(),ShadowTopLeft.y()),
                    Pnt2f(ShadowBottomRight.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getEdgeColor(), getInternalColor(), 1.0f);
        //BottomRight
        g->drawQuad(Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x(),ShadowBottomRight.y()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    getInternalColor(), getEdgeColor(), getEdgeColor(), getEdgeColor(), 1.0f);
        //BottomLeft
        g->drawQuad(Pnt2f(ShadowTopLeft.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    Pnt2f(ShadowTopLeft.x(),ShadowBottomRight.y()),
                    getEdgeColor(), getInternalColor(), getEdgeColor(), getEdgeColor(), 1.0f);

        //Rectangles
        //Top
        g->drawQuad(Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getInternalColor(), getInternalColor(), 1.0f);
        //Bottom
        g->drawQuad(Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    getInternalColor(), getInternalColor(), getEdgeColor(), getEdgeColor(), 1.0f);
        //Left
        g->drawQuad(Pnt2f(ShadowTopLeft.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    getEdgeColor(), getInternalColor(), getInternalColor(), getEdgeColor(), 1.0f);
        //Right
        g->drawQuad(Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    getInternalColor(), getEdgeColor(), getEdgeColor(), getInternalColor(), 1.0f);
        //Center
	    g->drawRect(ShadowTopLeft+Vec2f(getInternalToEdgeColorLength(),getInternalToEdgeColorLength()), ShadowBottomRight-Vec2f(getInternalToEdgeColorLength(),getInternalToEdgeColorLength()), getInternalColor(), 1.0f);
    }
    else
    {
        //Corners
        UInt32 InternalCornerRadius(getCornerRadius() - getInternalToEdgeColorLength());
        //TopLeft
        g->drawComplexDisc(ShadowTopLeft + Vec2f(getCornerRadius(),getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            3.14159265, 4.71238898, 10,
            getInternalColor(), getEdgeColor(), 1.0f
            );
        //TopRight
        g->drawComplexDisc(Pnt2f(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y() + getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            4.71238898,6.28318531, 10,
            getInternalColor(), getEdgeColor(), 1.0f
            );
        //BottomRight
        g->drawComplexDisc(Pnt2f(ShadowBottomRight.x()-getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            0.0, 1.57079633, 10,
            getInternalColor(), getEdgeColor(), 1.0f
            );
        //BottomLeft
        g->drawComplexDisc(Pnt2f(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            1.57079633, 3.14159265, 10,
            getInternalColor(), getEdgeColor(), 1.0f
            );
        //Rectangles
        //Top
        g->drawQuad(Pnt2f(ShadowTopLeft.x()+getCornerRadius(),ShadowTopLeft.y()),
                    Pnt2f(ShadowBottomRight.x()-getCornerRadius(),ShadowTopLeft.y()),
                    Pnt2f(ShadowBottomRight.x()-getCornerRadius(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2f(ShadowTopLeft.x()+getCornerRadius(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getInternalColor(), getInternalColor(), 1.0f);
        
        //Bottom
        g->drawQuad(Pnt2f(ShadowTopLeft.x()+getCornerRadius(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x()-getCornerRadius(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2f(ShadowBottomRight.x()-getCornerRadius(),ShadowBottomRight.y()),
                    Pnt2f(ShadowTopLeft.x()+getCornerRadius(),ShadowBottomRight.y()),
                    getInternalColor(), getInternalColor(), getEdgeColor(), getEdgeColor(), 1.0f);
        //Left
        g->drawQuad(Pnt2f(ShadowTopLeft.x(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getCornerRadius()),
                    Pnt2f(ShadowTopLeft.x(),ShadowBottomRight.y()-getCornerRadius()),
                    getEdgeColor(), getInternalColor(), getInternalColor(), getEdgeColor(), 1.0f);
        //Right
        g->drawQuad(Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2f(ShadowBottomRight.x(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2f(ShadowBottomRight.x(),ShadowBottomRight.y()-getCornerRadius()),
                    Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getCornerRadius()),
                    getInternalColor(), getEdgeColor(), getEdgeColor(), getInternalColor(), 1.0f);
        //Center
	    g->drawRect(ShadowTopLeft+Vec2f(getCornerRadius(),getCornerRadius()), ShadowBottomRight-Vec2f(getCornerRadius(),getCornerRadius()), getInternalColor(), 1.0f);

        if(getInternalToEdgeColorLength() < getCornerRadius())
        {
            //TopLeft
            g->drawDisc(ShadowTopLeft + Vec2f(getCornerRadius(),getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                3.14159265, 4.71238898, 10,
                getInternalColor(), getInternalColor(), 1.0f
                );
            //TopRight
            g->drawDisc(Pnt2f(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y() + getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                4.71238898,6.28318531, 10,
                getInternalColor(), getInternalColor(), 1.0f
                );
            //BottomRight
            g->drawDisc(Pnt2f(ShadowBottomRight.x()-getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                0.0, 1.57079633, 10,
                getInternalColor(), getInternalColor(), 1.0f
                );
            //BottomLeft
            g->drawDisc(Pnt2f(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                1.57079633, 3.14159265, 10,
                getInternalColor(), getInternalColor(), 1.0f
                );
            //Top
            g->drawRect(Pnt2f(ShadowTopLeft.x()+getCornerRadius(), ShadowTopLeft.y()+getInternalToEdgeColorLength()), 
                        Pnt2f(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y()+getCornerRadius()),
                        getInternalColor(), 1.0f);
            //Bottom
            g->drawRect(Pnt2f(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y()-getCornerRadius()), 
                        Pnt2f(ShadowBottomRight.x()-getCornerRadius(), ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                        getInternalColor(), 1.0f);
            //Left
            g->drawRect(Pnt2f(ShadowTopLeft.x()+getInternalToEdgeColorLength(), ShadowTopLeft.y()+getCornerRadius()), 
                        Pnt2f(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y()-getCornerRadius()),
                        getInternalColor(), 1.0f);
            //Right
            g->drawRect(Pnt2f(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y()+getCornerRadius()), 
                        Pnt2f(ShadowBottomRight.x()-getInternalToEdgeColorLength(), ShadowBottomRight.y()-getCornerRadius()),
                        getInternalColor(), 1.0f);
        }
    
    }

    getInsideBorder()->activateInternalDrawConstraints(g, x+getLeftOffset(), y+getTopOffset(),Width-getRightOffset()-getLeftOffset(),Height-getTopOffset()-getBottomOffset());
}

bool ShadowBorder::isContained(const Pnt2f& p, const Real32& x, const Real32& y , const Real32& Width, const Real32& Height) const
{
    return getInsideBorder()->isContained(p, x+getLeftOffset(), y+getTopOffset(),Width-getRightOffset()-getLeftOffset(),Height-getTopOffset()-getBottomOffset());
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShadowBorder::ShadowBorder(void) :
    Inherited()
{
}

ShadowBorder::ShadowBorder(const ShadowBorder &source) :
    Inherited(source)
{
}

ShadowBorder::~ShadowBorder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShadowBorder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ShadowBorder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShadowBorder NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSHADOWBORDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADOWBORDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADOWBORDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


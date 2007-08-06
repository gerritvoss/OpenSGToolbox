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

void ShadowBorder::draw(const GraphicsPtr g, const Int16 x, const Int16 y , const UInt16 Width, const UInt16 Height, const Real32 Opacity) const
{
    //Determine TopLeft and BottomRight of the Shadow
    Pnt2s ShadowTopLeft,
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
        g->drawQuad(Pnt2s(ShadowTopLeft.x(),ShadowTopLeft.y()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getInternalColor(), getEdgeColor(), Opacity);
        //TopRight
        g->drawQuad(Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2s(ShadowBottomRight.x(),ShadowTopLeft.y()),
                    Pnt2s(ShadowBottomRight.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getEdgeColor(), getInternalColor(), Opacity);
        //BottomRight
        g->drawQuad(Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x(),ShadowBottomRight.y()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    getInternalColor(), getEdgeColor(), getEdgeColor(), getEdgeColor(), Opacity);
        //BottomLeft
        g->drawQuad(Pnt2s(ShadowTopLeft.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    Pnt2s(ShadowTopLeft.x(),ShadowBottomRight.y()),
                    getEdgeColor(), getInternalColor(), getEdgeColor(), getEdgeColor(), Opacity);

        //Rectangles
        //Top
        g->drawQuad(Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getInternalColor(), getInternalColor(), Opacity);
        //Bottom
        g->drawQuad(Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()),
                    getInternalColor(), getInternalColor(), getEdgeColor(), getEdgeColor(), Opacity);
        //Left
        g->drawQuad(Pnt2s(ShadowTopLeft.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    getEdgeColor(), getInternalColor(), getInternalColor(), getEdgeColor(), Opacity);
        //Right
        g->drawQuad(Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    getInternalColor(), getEdgeColor(), getEdgeColor(), getInternalColor(), Opacity);
        //Center
	    g->drawRect(ShadowTopLeft+Vec2s(getInternalToEdgeColorLength(),getInternalToEdgeColorLength()), ShadowBottomRight-Vec2s(getInternalToEdgeColorLength(),getInternalToEdgeColorLength()), getInternalColor(), Opacity);
    }
    else
    {
        //Corners
        UInt32 InternalCornerRadius(getCornerRadius() - getInternalToEdgeColorLength());
        //TopLeft
        g->drawComplexDisc(ShadowTopLeft + Vec2s(getCornerRadius(),getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            3.14159265, 4.71238898, 10,
            getInternalColor(), getEdgeColor(), Opacity
            );
        //TopRight
        g->drawComplexDisc(Pnt2s(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y() + getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            4.71238898,6.28318531, 10,
            getInternalColor(), getEdgeColor(), Opacity
            );
        //BottomRight
        g->drawComplexDisc(Pnt2s(ShadowBottomRight.x()-getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            0.0, 1.57079633, 10,
            getInternalColor(), getEdgeColor(), Opacity
            );
        //BottomLeft
        g->drawComplexDisc(Pnt2s(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
            InternalCornerRadius,getCornerRadius(),
            1.57079633, 3.14159265, 10,
            getInternalColor(), getEdgeColor(), Opacity
            );
        //Rectangles
        //Top
        g->drawQuad(Pnt2s(ShadowTopLeft.x()+getCornerRadius(),ShadowTopLeft.y()),
                    Pnt2s(ShadowBottomRight.x()-getCornerRadius(),ShadowTopLeft.y()),
                    Pnt2s(ShadowBottomRight.x()-getCornerRadius(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    Pnt2s(ShadowTopLeft.x()+getCornerRadius(),ShadowTopLeft.y()+getInternalToEdgeColorLength()),
                    getEdgeColor(), getEdgeColor(), getInternalColor(), getInternalColor(), Opacity);
        
        //Bottom
        g->drawQuad(Pnt2s(ShadowTopLeft.x()+getCornerRadius(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x()-getCornerRadius(),ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                    Pnt2s(ShadowBottomRight.x()-getCornerRadius(),ShadowBottomRight.y()),
                    Pnt2s(ShadowTopLeft.x()+getCornerRadius(),ShadowBottomRight.y()),
                    getInternalColor(), getInternalColor(), getEdgeColor(), getEdgeColor(), Opacity);
        //Left
        g->drawQuad(Pnt2s(ShadowTopLeft.x(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(),ShadowBottomRight.y()-getCornerRadius()),
                    Pnt2s(ShadowTopLeft.x(),ShadowBottomRight.y()-getCornerRadius()),
                    getEdgeColor(), getInternalColor(), getInternalColor(), getEdgeColor(), Opacity);
        //Right
        g->drawQuad(Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2s(ShadowBottomRight.x(),ShadowTopLeft.y()+getCornerRadius()),
                    Pnt2s(ShadowBottomRight.x(),ShadowBottomRight.y()-getCornerRadius()),
                    Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(),ShadowBottomRight.y()-getCornerRadius()),
                    getInternalColor(), getEdgeColor(), getEdgeColor(), getInternalColor(), Opacity);
        //Center
	    g->drawRect(ShadowTopLeft+Vec2s(getCornerRadius(),getCornerRadius()), ShadowBottomRight-Vec2s(getCornerRadius(),getCornerRadius()), getInternalColor(), Opacity);

        if(getInternalToEdgeColorLength() < getCornerRadius())
        {
            //TopLeft
            g->drawDisc(ShadowTopLeft + Vec2s(getCornerRadius(),getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                3.14159265, 4.71238898, 10,
                getInternalColor(), getInternalColor(), Opacity
                );
            //TopRight
            g->drawDisc(Pnt2s(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y() + getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                4.71238898,6.28318531, 10,
                getInternalColor(), getInternalColor(), Opacity
                );
            //BottomRight
            g->drawDisc(Pnt2s(ShadowBottomRight.x()-getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                0.0, 1.57079633, 10,
                getInternalColor(), getInternalColor(), Opacity
                );
            //BottomLeft
            g->drawDisc(Pnt2s(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y() - getCornerRadius()),
                InternalCornerRadius,InternalCornerRadius,
                1.57079633, 3.14159265, 10,
                getInternalColor(), getInternalColor(), Opacity
                );
            //Top
            g->drawRect(Pnt2s(ShadowTopLeft.x()+getCornerRadius(), ShadowTopLeft.y()+getInternalToEdgeColorLength()), 
                        Pnt2s(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y()+getCornerRadius()),
                        getInternalColor(), Opacity);
            //Bottom
            g->drawRect(Pnt2s(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y()-getCornerRadius()), 
                        Pnt2s(ShadowBottomRight.x()-getCornerRadius(), ShadowBottomRight.y()-getInternalToEdgeColorLength()),
                        getInternalColor(), Opacity);
            //Left
            g->drawRect(Pnt2s(ShadowTopLeft.x()+getInternalToEdgeColorLength(), ShadowTopLeft.y()+getCornerRadius()), 
                        Pnt2s(ShadowTopLeft.x()+getCornerRadius(), ShadowBottomRight.y()-getCornerRadius()),
                        getInternalColor(), Opacity);
            //Right
            g->drawRect(Pnt2s(ShadowBottomRight.x()-getCornerRadius(), ShadowTopLeft.y()+getCornerRadius()), 
                        Pnt2s(ShadowBottomRight.x()-getInternalToEdgeColorLength(), ShadowBottomRight.y()-getCornerRadius()),
                        getInternalColor(), Opacity);
        }
    
    }
    //Draw the Inside Border
    getInsideBorder()->draw(g, x+getLeftOffset(), y+getTopOffset(),Width-getRightOffset()-getLeftOffset(),Height-getTopOffset()-getBottomOffset(), Opacity);

}

void ShadowBorder::getInsets(UInt16& Left, UInt16& Right,UInt16& Top,UInt16& Bottom) const
{
    getInsideBorder()->getInsets(Left, Right, Top, Bottom);
    Left +=getLeftOffset();
    Right +=getRightOffset();
    Top +=getTopOffset();
    Bottom +=getBottomOffset();
}

void ShadowBorder::activateInternalDrawConstraints(const GraphicsPtr g, const Int16& x, const Int16& y , const UInt16& Width, const UInt16& Height) const
{
    return getInsideBorder()->activateInternalDrawConstraints(g, x+getLeftOffset(), y+getTopOffset(),Width-getRightOffset()-getLeftOffset(),Height-getTopOffset()-getBottomOffset());
}

void ShadowBorder::deactivateInternalDrawConstraints(const GraphicsPtr g, const Int16& x, const Int16& y , const UInt16& Width, const UInt16& Height) const
{
    return getInsideBorder()->deactivateInternalDrawConstraints(g, x+getLeftOffset(), y+getTopOffset(),Width-getRightOffset()-getLeftOffset(),Height-getTopOffset()-getBottomOffset());
}

bool ShadowBorder::isContained(const Pnt2s& p, const Int16& x, const Int16& y , const UInt16& Width, const UInt16& Height) const
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


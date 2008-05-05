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

#include "OSGSeparator.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Separator
A UI Separator. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Separator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Separator::drawInternal(const GraphicsPtr Graphics) const
{
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);
   
    //Calculate Alignment
    Pnt2f AlignedPosition;
    Pnt2f LineTopLeft(0,0), LineBottomRight(getSeparatorSize(),getSeparatorSize());

    if(getOrientation() == Separator::VERTICAL_ORIENTATION)
    {
        AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (LineBottomRight - LineTopLeft),0.5, 0.0);

        Graphics->drawRect(AlignedPosition, AlignedPosition + Vec2f(BottomRight.x() - TopLeft.x(),getSeparatorSize()), getColor(), getOpacity());
    }
    else
    {
        AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (LineBottomRight - LineTopLeft),0.0, 0.5);

        Graphics->drawRect(AlignedPosition, AlignedPosition + Vec2f(getSeparatorSize(),BottomRight.y() - TopLeft.y()), getColor(), getOpacity());
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Separator::Separator(void) :
    Inherited()
{
}

Separator::Separator(const Separator &source) :
    Inherited(source)
{
}

Separator::~Separator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Separator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Separator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Separator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSEPARATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSEPARATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSEPARATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


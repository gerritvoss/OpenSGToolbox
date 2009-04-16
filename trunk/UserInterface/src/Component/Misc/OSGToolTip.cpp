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

#include "OSGToolTip.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ToolTip
A UI Tooltip. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ToolTip::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ToolTip::drawInternal(const GraphicsPtr TheGraphics) const
{
    if(getText() != "" && getFont() != NullFC)
    {
        Pnt2f TopLeft, BottomRight;
        getInsideBorderBounds(TopLeft, BottomRight);

        Pnt2f TextTopLeft, TextBottomRight;
        getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
        TheGraphics->drawText(
           calculateAlignment(TopLeft, BottomRight-TopLeft, (TextBottomRight-TextTopLeft),getAlignment().y(), getAlignment().x())
   , getText(), getFont(), getTextColor(), getOpacity());
    }
}

Vec2f ToolTip::calculatePreferredSize(void) const
{
    if(getFont() == NullFC)
    {
        return getPreferredSize();
    }

    Real32 Top(0),Bottom(0),Left(0),Right(0);
    if(getDrawnBorder() != NullFC)
    {
        getDrawnBorder()->getInsets(Left, Right, Top, Bottom);
    }

    Pnt2f TextTopLeft, TextBottomRight;
    getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
    return TextBottomRight - TextTopLeft + Vec2f(Left+Right+2, Top+Bottom+2);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ToolTip::ToolTip(void) :
    Inherited()
{
}

ToolTip::ToolTip(const ToolTip &source) :
    Inherited(source)
{
}

ToolTip::~ToolTip(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ToolTip::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & TextFieldMask)
    {
        beginEditCP(ToolTipPtr(this), PreferredSizeFieldMask | SizeFieldMask);
            setPreferredSize(calculatePreferredSize());
            setSize(getPreferredSize());
        endEditCP(ToolTipPtr(this), PreferredSizeFieldMask | SizeFieldMask);
    }
}

void ToolTip::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ToolTip NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTOOLTIPBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTOOLTIPBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTOOLTIPFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


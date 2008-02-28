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

#include "OSGToolbar.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Toolbar
A UI Toolbar. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Toolbar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Toolbar::setOrientation(BoxLayout::Orientation TheOrientation)
{
	beginEditCP(BoxLayout::Ptr::dcast(getLayout()), BoxLayout::OrientationFieldMask);
		BoxLayout::Ptr::dcast(getLayout())->setOrientation(TheOrientation);
	endEditCP(BoxLayout::Ptr::dcast(getLayout()), BoxLayout::OrientationFieldMask);
}

BoxLayout::Orientation Toolbar::getOrientation(void) const
{
	return BoxLayout::Orientation(BoxLayout::Ptr::dcast(getLayout())->getOrientation());
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

BoxLayoutPtr Toolbar::createDefaultLayout(void) const
{
	BoxLayoutPtr TheLayout = BoxLayout::create();

	beginEditCP(TheLayout);
		TheLayout->setOrientation(BoxLayout::HORIZONTAL_ORIENTATION);
		TheLayout->setMajorAxisAlignment(0.0f);
		TheLayout->setMinorAxisAlignment(0.0f);
		TheLayout->setComponentAlignment(0.0f);
		TheLayout->setMajorAxisMinimumGap(2);
		TheLayout->setMajorAxisMaximumGap(2);
	endEditCP(TheLayout);

	return TheLayout;
}
/*----------------------- constructors & destructors ----------------------*/

Toolbar::Toolbar(void) :
    Inherited()
{
}

Toolbar::Toolbar(const Toolbar &source) :
    Inherited(source)
{
	beginEditCP(ToolbarPtr(this), Toolbar::LayoutFieldMask);
		setLayout(createDefaultLayout());
	endEditCP(ToolbarPtr(this), Toolbar::LayoutFieldMask);
}

Toolbar::~Toolbar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Toolbar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Toolbar::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Toolbar NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTOOLBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTOOLBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTOOLBARFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>
#include "Util/OSGUIDefines.h"

#include "OSGSplitPanel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SplitPanel
A UI Split Panel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SplitPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void SplitPanel::drawInternal(const GraphicsPtr Graphics) const
{
	// draw the divider

	// draw the two contained components
	getMinComponent()->draw(Graphics);
	getMaxComponent()->draw(Graphics);
}

void SplitPanel::updateLayout(void)
{
	Pnt2s TopLeft, BottomRight;
	getInsideBorderBounds(TopLeft, BottomRight);
	Vec2s BorderSize(BottomRight - TopLeft);

	UInt32 AxisIndex(0);
	if(getAlignment() != HORIZONTAL_ALIGNMENT ) AxisIndex = 1;

	Vec2s minSize;
	Vec2s maxSize;

	Pnt2s minPos(0,0);
	Pnt2s maxPos;

	//minSize[AxisIndex] = 

	beginEditCP(getMinComponent(), Component::SizeFieldMask|Component::PositionFieldMask);
		getMinComponent()->setSize(minSize);
		getMinComponent()->setPosition(minPos);
	endEditCP(getMinComponent(), Component::SizeFieldMask|Component::PositionFieldMask);

	beginEditCP(getMaxComponent(), Component::SizeFieldMask|Component::PositionFieldMask);
		getMaxComponent()->setSize(maxSize);
		getMaxComponent()->setPosition(maxPos);
	endEditCP(getMaxComponent(), Component::SizeFieldMask|Component::PositionFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SplitPanel::SplitPanel(void) :
    Inherited()
{
}

SplitPanel::SplitPanel(const SplitPanel &source) :
    Inherited(source)
{
}

SplitPanel::~SplitPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SplitPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SplitPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SplitPanel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGSPLITPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSPLITPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSPLITPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


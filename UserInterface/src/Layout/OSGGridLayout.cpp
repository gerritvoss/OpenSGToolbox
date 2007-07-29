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

#include "OSGGridLayout.h"
#include "Component/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GridLayout
A UI GridLayout. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GridLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void GridLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
	Pnt2s borderTopLeft, borderBottomRight;
	Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2s borderSize(borderBottomRight-borderTopLeft);

	Int32 Xpos = 0;
	Int32 Ypos = 0;
	Int32 maxSizeX = 0;
	Int32 maxSizeY = 0;
	Int32 debug = 10;
	Int32 numComp = Components.getSize();
	Int32 buttonXSize, buttonYSize;

	//set the size to the perfered sizes for the buttons
	for(UInt16 i = 0; i<Components.size(); i++){
		if (Components.getValue(i) != NullFC) 
		{
			if(Components.getValue(i)->getPreferredSize().x()>maxSizeX)
				maxSizeX = Components.getValue(i)->getPreferredSize().x();
			if(Components.getValue(i)->getPreferredSize().y()>maxSizeY)
				maxSizeY = Components.getValue(i)->getPreferredSize().y();
		}
	}
	//set the  size of the button
	for(UInt16 i = 0; i < Components.size(); i++){
		if (Components.getValue(i) != NullFC) 
		{
			if(maxSizeX < Components.getValue(i)->getMaxSize().x())
				buttonXSize = maxSizeX;
			else
				buttonXSize = Components.getValue(i)->getMaxSize().x();
			if(maxSizeY<Components.getValue(i)->getMaxSize().y())
				buttonYSize = maxSizeY;
			else
				buttonYSize = Components.getValue(i)->getMaxSize().y();
			beginEditCP(Components.getValue(i), Component::SizeFieldMask);
			   Components.getValue(i)->setSize(Vec2s(buttonXSize, buttonYSize));
			endEditCP(Components.getValue(i), Component::SizeFieldMask);
		}
	}


	//position each button
	for(UInt16 i = 0; i <= getRows()&& numComp>=0; i++){
		if (Components.getValue(i) != NullFC) 
		{
			for(UInt16 j = 0; j < getColumns()&& numComp>0; j++){
				debug = i*getColumns()+j;
			    beginEditCP(Components.getValue(i), Component::PositionFieldMask);
                   Components.getValue(i*getColumns()+j)->setPosition(borderTopLeft + Vec2s(Xpos, Ypos));
			    endEditCP(Components.getValue(i), Component::PositionFieldMask);
				numComp--;
				Xpos = Xpos + (maxSizeX+getHorizontalGap());
			}
			Xpos = 0;
			Ypos += maxSizeY+getVerticalGap();
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GridLayout::GridLayout(void) :
    Inherited()
{
}

GridLayout::GridLayout(const GridLayout &source) :
    Inherited(source)
{
}

GridLayout::~GridLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GridLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GridLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GridLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGRIDLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGRIDLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGRIDLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


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

#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"

#include "Util/OSGUIDefines.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BorderLayout
A UI BorderLayout. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BorderLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void BorderLayout::draw(const MFComponentPtr Components,const ComponentPtr ParentComponent, const GraphicsPtr TheGraphics) const
{
	Pnt2s borderOffset;
	Vec2s borderSize;
	ParentComponent->getInsideBorderBounds(borderOffset, borderSize);
	Int32 NorthHeight(0);
	Int32 SouthHeight(0);
	Int32 WestWidth(0);
	Int32 EastWidth(0);
	Vec2s size;
	Int32 offsetx(0);
	Int32 offsety(0);


	// the first pass through gets some crucial dimensions to determine
	// the sizes of the buttons
	for(UInt32 i = 0 ; i<Components.size(); ++i)
    {
		if(Components.getValue(i)->getConstraints() != NullFC)
		{
			switch (BorderLayoutConstraintsPtr::dcast(Components.getValue(i)->getConstraints())->getRegion()) {
				// don't need to do anything with the center quite yet
				case BorderLayoutConstraints::BORDER_NORTH:
					NorthHeight = Components.getValue(i)->getPreferredSize().y();
					break;
				case BorderLayoutConstraints::BORDER_EAST:
					EastWidth = Components.getValue(i)->getPreferredSize().x();
					break;
				case BorderLayoutConstraints::BORDER_SOUTH:
					SouthHeight = Components.getValue(i)->getPreferredSize().y();
					break;
				case BorderLayoutConstraints::BORDER_WEST:
					WestWidth = Components.getValue(i)->getPreferredSize().x();
					break;
				default:
					break; 
			}
		}
	}
	// this second pass sets its size and draws them
	glTranslatef(borderOffset.x(), borderOffset.y(), 0);
	for(UInt32 i = 0 ; i<Components.size(); ++i)
    {
		// Find its region and draw it accordingly
		if(Components.getValue(i)->getConstraints() != NullFC)
		{
			switch (BorderLayoutConstraintsPtr::dcast(Components.getValue(i)->getConstraints())->getRegion()) {
				case BorderLayoutConstraints::BORDER_CENTER: 
					// set up the size of the button and its extra displacement
					if (Components.getValue(i)->getMaxSize().x() < borderSize.x()-(WestWidth+EastWidth))
					{
						size[0] = Components.getValue(i)->getMaxSize().x();
						offsetx = (borderSize.x()-(WestWidth+EastWidth)-size[0])/2 + WestWidth;
					}
					else
					{
						size[0] = borderSize.x()-(WestWidth+EastWidth);
						offsetx = WestWidth;
					}
					if (Components.getValue(i)->getMaxSize().y() < borderSize.y()-(NorthHeight+SouthHeight))
					{
						size[1] = Components.getValue(i)->getMaxSize().y();
						offsety = (borderSize.y()-(NorthHeight+SouthHeight)-size[1])/2 + NorthHeight;
					}
					else
					{
						size[1] = borderSize.y()-(NorthHeight+SouthHeight);
						offsety = NorthHeight;
					}
					beginEditCP(Components.getValue(i), Component::SizeFieldMask);
						Components.getValue(i)->setSize(size);
					endEditCP(Components.getValue(i), Component::SizeFieldMask);

					if (size[0] >= Components.getValue(i)->getMinSize().x() && size[1] > Components.getValue(i)->getMinSize().y()) // only draw it if it isn't too small
					{
						// translate and draw, then translate back
						glTranslatef(offsetx, offsety, 0);
						Components.getValue(i)->draw(TheGraphics);
						glTranslatef(-offsetx, -offsety, 0);
					}
					break;
				case BorderLayoutConstraints::BORDER_NORTH:
					// set up the size of the button and its extra displacement
					size[1] = Components.getValue(i)->getPreferredSize().y();
					if (Components.getValue(i)->getMaxSize().x() < borderSize.x())
					{
						size[0] = Components.getValue(i)->getMaxSize().x();
						offsetx = (borderSize.x()-size[0])/2;
					}
					else
					{
						size[0] = borderSize.x();
						offsetx = 0;
					}
					beginEditCP(Components.getValue(i), Component::SizeFieldMask);
						Components.getValue(i)->setSize(size);
					endEditCP(Components.getValue(i), Component::SizeFieldMask);

					if (size[0] > Components.getValue(i)->getMinSize().x())
					{
						// translate and draw, then translate back
						glTranslatef(offsetx, 0, 0);
						Components.getValue(i)->draw(TheGraphics);
						glTranslatef(-offsetx, 0, 0);
					}
					break;
				case BorderLayoutConstraints::BORDER_EAST:
					// set up the size of the button and its extra displacement
					size[0] = Components.getValue(i)->getPreferredSize().x();
					offsetx = borderSize.x()-Components.getValue(i)->getSize().x();
					if (Components.getValue(i)->getMaxSize().y() < borderSize.y()-(NorthHeight+SouthHeight))
					{
						size[1] = Components.getValue(i)->getMaxSize().y();
						offsety = (borderSize.y()-size[1]-(NorthHeight+SouthHeight))/2+NorthHeight;
					}
					else
					{
						size[1] = borderSize.y()-(NorthHeight+SouthHeight);
						offsety = NorthHeight;
					}
					beginEditCP(Components.getValue(i), Component::SizeFieldMask);
						Components.getValue(i)->setSize(size);
					endEditCP(Components.getValue(i), Component::SizeFieldMask);

					if (size[1] > Components.getValue(i)->getMinSize().y())
					{
						// translate and draw, then translate back
						glTranslatef(offsetx, offsety, 0);
						Components.getValue(i)->draw(TheGraphics);
						glTranslatef(-offsetx, -offsety, 0);
					}
					break;
				case BorderLayoutConstraints::BORDER_SOUTH:
					// set up the size of the button and its extra displacement
					size[1] = Components.getValue(i)->getPreferredSize().y();
					offsety = borderSize.y()-Components.getValue(i)->getSize().y();
					if (Components.getValue(i)->getMaxSize().x() < borderSize.x())
					{
						size[0] = Components.getValue(i)->getMaxSize().x();
						offsetx = (borderSize.x()-size[0])/2;
					}
					else
					{
						size[0] = borderSize.x();
						offsetx = 0;
					}
					beginEditCP(Components.getValue(i), Component::SizeFieldMask);
						Components.getValue(i)->setSize(size);
					endEditCP(Components.getValue(i), Component::SizeFieldMask);

					if (size[0] > Components.getValue(i)->getMinSize().x())
					{
						// translate and draw, then translate back
						glTranslatef(offsetx, offsety, 0);
						Components.getValue(i)->draw(TheGraphics);
						glTranslatef(-offsetx, -offsety, 0);
					}
					break;
				case BorderLayoutConstraints::BORDER_WEST:
					// set up the size of the button and its extra displacement
					size[0] = Components.getValue(i)->getPreferredSize().x();
					if (Components.getValue(i)->getMaxSize().y() < borderSize.y()-(NorthHeight+SouthHeight))
					{
						size[1] = Components.getValue(i)->getMaxSize().y();
						offsety = (borderSize.y()-size[1]-(NorthHeight+SouthHeight))/2 + NorthHeight;
					}
					else
					{
						size[1] = borderSize.y()-(NorthHeight+SouthHeight);
						offsety = NorthHeight;
					}
					beginEditCP(Components.getValue(i), Component::SizeFieldMask);
						Components.getValue(i)->setSize(size);
					endEditCP(Components.getValue(i), Component::SizeFieldMask);

					if (size[1] > Components.getValue(i)->getMinSize().y())
					{
						// translate and draw, then translate back
						glTranslatef(0, offsety, 0);
						Components.getValue(i)->draw(TheGraphics);
						glTranslatef(0, -offsety, 0);
					}
					break;
				default:
					break; 
			}
		}
	}
	glTranslatef(-borderOffset.x(), -borderOffset.y(), 0);
}

void BorderLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BorderLayout::BorderLayout(void) :
    Inherited()
{
}

BorderLayout::BorderLayout(const BorderLayout &source) :
    Inherited(source)
{
}

BorderLayout::~BorderLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BorderLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BorderLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BorderLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGBORDERLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBORDERLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBORDERLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


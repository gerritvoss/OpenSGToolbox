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
#include "OSGUserInterfaceDef.h"
#include "OSGTabPanel.h"
#include "Util/OSGUIDefines.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TabPanel
A UI Tab Panel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TabPanel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TabPanel::drawInternal(const GraphicsPtr Graphics) const
{
	Vec2s pos;

	// translate past the border and inset
	//glTranslatef(TopLeft.x(), TopLeft.y(), 0);

	// draw the tabs
	for (UInt32 i = 0; i < getTabs().size(); ++i)
	{
		getTabs().getValue(i)->draw(Graphics);
	}
	
	// draw the active tab component
	getTabContents().getValue(getActiveTab())->draw(Graphics);
}

void TabPanel::addTab(const ComponentPtr Tab, const ComponentPtr TabContent)
{
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
		getTabs().addValue(Tab);
		getTabContents().addValue(TabContent);
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
}

void TabPanel::removeTab(const ComponentPtr Tab)
{
	UInt32 index(0);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
		// check if the component is a tab or tabcontent, then erase accordingly
		if (getTabs().end() == getTabs().find(Tab))
		{
			getTabContents().erase(getTabContents().find(Tab));
			for (UInt32 i = 0; i < getTabContents().size(); ++i)
			{
				if(getTabContents().find(Tab) == getTabContents().find(getTabContents().getValue(i)))
					index = i;
			}
			getTabs().erase(getTabs().find(getTabs().getValue(index)));
		}
		else
		{
			getTabs().erase(getTabs().find(Tab));
			for (UInt32 i = 0; i < getTabs().size(); ++i)
			{
				if(getTabs().find(Tab) == getTabs().find(getTabs().getValue(i)))
					index = i;
			}
			getTabContents().erase(getTabContents().find(getTabContents().getValue(index)));
		}
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
}

void TabPanel::removeTab(const UInt32 TabIndex)
{
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
		getTabs().erase(getTabs().find(getTabs().getValue(TabIndex))); // an incredibly ridiculous function call
		getTabContents().erase(getTabContents().find(getTabContents().getValue(TabIndex)));
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
}

void TabPanel::insertTab(const ComponentPtr TabInsert, const ComponentPtr Tab, const ComponentPtr TabContent)
{
	UInt32 index(0);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
		// check if the component is a tab or tabcontent, then insert accordingly
		if (getTabs().end() == getTabs().find(TabInsert))
		{
			getTabContents().insert(getTabContents().find(TabInsert), TabContent);
			for (UInt32 i = 0; i < getTabContents().size(); ++i)
			{
				if(getTabContents().find(TabInsert) == getTabContents().find(getTabContents().getValue(i)))
					index = i;
			}
			getTabs().insert(getTabs().find(getTabs().getValue(index)), Tab);
		}
		else
		{
			getTabs().insert(getTabs().find(TabInsert), Tab);
			for (UInt32 i = 0; i < getTabs().size(); ++i)
			{
				if(getTabs().find(TabInsert) == getTabs().find(getTabs().getValue(i)))
					index = i;
			}
			getTabContents().insert(getTabContents().find(getTabContents().getValue(index)), TabContent);
		}
		endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
}

void TabPanel::insertTab(const UInt32 TabIndex, const ComponentPtr Tab, const ComponentPtr TabContent)
{
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
		getTabs().insert(getTabs().find(getTabs().getValue(TabIndex)), Tab); // an incredibly ridiculous function call
		getTabContents().insert(getTabContents().find(getTabContents().getValue(TabIndex)), TabContent);
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask);
}

void TabPanel::updateTabLayout(void)
{
	Pnt2s borderOffset;
	Vec2s borderSize;
	getInsideBorderBounds(borderOffset, borderSize);

	UInt16 AxisIndex(0);
	if (getTabPlacement() == PLACEMENT_EAST || getTabPlacement() == PLACEMENT_WEST)
		AxisIndex=1;
	UInt32 largestMinorAxis(0);
	UInt32 cumMajorAxis(0);
	Pnt2s alignOffset(0,0);
	Pnt2s offset(0,0);
	
	// first layout all of the tabs
	// naturally the alignments and such is necessary
	// on the first sweep, get the maximum size and cumLength
	for (UInt32 i=0; i < getTabs().size(); ++i)
	{
		cumMajorAxis += getTabs().getValue(i)->getPreferredSize()[AxisIndex];
		if (getTabs().getValue(i)->getPreferredSize()[(AxisIndex+1)%2] > largestMinorAxis)
			largestMinorAxis = getTabs().getValue(i)->getPreferredSize()[(AxisIndex+1)%2];
	}
	// set up the alignment and offset
	if (getTabAlignment() == AXIS_CENTER_ALIGNMENT)
		alignOffset[AxisIndex] = (borderSize[AxisIndex] - cumMajorAxis)/2;
	else if (getTabAlignment() == AXIS_MAX_ALIGNMENT)
		alignOffset[AxisIndex] = borderSize[AxisIndex] - cumMajorAxis;
	if (getTabPlacement() == PLACEMENT_EAST || getTabPlacement() == PLACEMENT_SOUTH)
		alignOffset[(AxisIndex+1)%2] = borderSize[(AxisIndex+1)%2] - largestMinorAxis;
	offset = borderOffset;

	// set sizes and positions of all tabs
	for (UInt32 i=0; i < getTabs().size(); ++i)
	{
		if ( (getTabPlacement() == PLACEMENT_NORTH || getTabPlacement() == PLACEMENT_WEST) && getTabs().getValue(i)->getPreferredSize()[(AxisIndex+1)%2] < largestMinorAxis)
			offset[(AxisIndex+1)%2] += largestMinorAxis - getTabs().getValue(i)->getPreferredSize()[(AxisIndex+1)%2];
		beginEditCP(getTabs().getValue(i), Component::SizeFieldMask|Component::PositionFieldMask);
			getTabs().getValue(i)->setSize(getTabs().getValue(i)->getPreferredSize());
			getTabs().getValue(i)->setPosition(alignOffset + offset);
		endEditCP(getTabs().getValue(i), Component::SizeFieldMask|Component::PositionFieldMask);
		offset[AxisIndex] += getTabs().getValue(i)->getSize()[AxisIndex];
		if ( (getTabPlacement() == PLACEMENT_NORTH || getTabPlacement() == PLACEMENT_WEST) && getTabs().getValue(i)->getPreferredSize()[(AxisIndex+1)%2] < largestMinorAxis)
			offset[(AxisIndex+1)%2] -= largestMinorAxis - getTabs().getValue(i)->getPreferredSize()[(AxisIndex+1)%2];
	}

	// now set size and position of the active tab's contents
	offset = borderOffset;
	if (getTabPlacement() == PLACEMENT_NORTH || getTabPlacement() == PLACEMENT_WEST)
		offset[(AxisIndex+1)%2] += largestMinorAxis;
	borderSize[(AxisIndex+1)%2] -= largestMinorAxis;
	beginEditCP(getTabs().getValue(getActiveTab()), Component::SizeFieldMask|Component::PositionFieldMask);
		getTabContents().getValue(getActiveTab())->setSize(borderSize);
		getTabContents().getValue(getActiveTab())->setPosition(offset);
	endEditCP(getTabContents().getValue(getActiveTab()), Component::SizeFieldMask|Component::PositionFieldMask);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TabPanel::TabPanel(void) :
    Inherited()
{
}

TabPanel::TabPanel(const TabPanel &source) :
    Inherited(source)
{
}

TabPanel::~TabPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TabPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if( (whichField & SizeFieldMask) || (whichField & TabsFieldMask) || (whichField & TabContentsFieldMask) )
    {
		updateTabLayout();
	}
}

void TabPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TabPanel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTABPANELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTABPANELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTABPANELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


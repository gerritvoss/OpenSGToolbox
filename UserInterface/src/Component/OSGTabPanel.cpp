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
#include "Util/OSGUIDrawUtils.h"

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
	Pnt2s TopLeft, BottomRight;
	getInsideInsetsBounds(TopLeft, BottomRight);
	Vec2s pos;

	// draw the tabs
	for (UInt32 i = 0; i < getTabs().size(); ++i)
	{
		getTabs().getValue(i)->draw(Graphics);
	}
	
	// draw the active tab component
	getTabContents().getValue(getActiveTab())->draw(Graphics);
}

void TabPanel::focusGained(const FocusEvent& e)
{
	ComponentPtr Tab = Component::Ptr::dcast(e.getSource());
	Int32 index(-1);

	for (UInt32 i = 0; i < getTabs().size(); ++i)
	{
		if(getTabs().find(Tab) == getTabs().find(getTabs().getValue(i)))
			index = i;
	}
	if (index != -1)
	{
		beginEditCP(TabPanelPtr(this), ActiveTabFieldMask);
			setActiveTab(index);
		endEditCP(TabPanelPtr(this), ActiveTabFieldMask);
	}
	updateTabLayout();
}

void TabPanel::focusLost(const FocusEvent& e)
{
}

void TabPanel::addTab(const ComponentPtr Tab, const ComponentPtr TabContent)
{
	// three lists of components are actually kept
	// every component, whether tab or tabcontent is kept in the children list
	// this is for clipping and clicking purposes
	// for drawing, the tabs and tabcontents are kept seperately in two other lists
	// so, there are three lists, and every component is kept in two of them
	Tab->addFocusListener(this);

	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
		getTabs().addValue(Tab);
		getTabContents().addValue(TabContent);
		getChildren().addValue(Tab);
		getChildren().addValue(TabContent);
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::removeTab(const ComponentPtr Tab)
{
	UInt32 index(0);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
		// also erase the the tab from the components list
		getChildren().erase(getChildren().find(Tab));
		// check if the component is a tab or tabcontent, then erase accordingly
		if (getTabs().end() == getTabs().find(Tab))
		{	// so it isn't in tabs
			for (UInt32 i = 0; i < getTabContents().size(); ++i)
			{
				if(getTabContents().find(Tab) == getTabContents().find(getTabContents().getValue(i)))
					index = i;
			}
			getTabContents().erase(getTabContents().find(Tab));
			// also erase the the tab from the components list
			getTabs().getValue(index)->removeFocusListener(this);
			getChildren().erase(getChildren().find(getTabs().getValue(index)));
			getTabs().erase(getTabs().find(getTabs().getValue(index)));
		}
		else
		{
			for (UInt32 i = 0; i < getTabs().size(); ++i)
			{
				if(getTabs().find(Tab) == getTabs().find(getTabs().getValue(i)))
					index = i;
			}
			Tab->removeFocusListener(this);
			getTabs().erase(getTabs().find(Tab));
			// also erase the the tab from the components list
			getChildren().erase(getChildren().find(getTabContents().getValue(index))); 
			getTabContents().erase(getTabContents().find(getTabContents().getValue(index)));
		}
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::removeTab(const UInt32 TabIndex)
{
	getTabs().getValue(TabIndex)->removeFocusListener(this);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
		getChildren().erase(getChildren().find(getTabs().getValue(TabIndex))); // an incredibly ridiculous function call
		getChildren().erase(getChildren().find(getTabContents().getValue(TabIndex)));
		getTabs().erase(getTabs().find(getTabs().getValue(TabIndex))); // an incredibly ridiculous function call
		getTabContents().erase(getTabContents().find(getTabContents().getValue(TabIndex)));
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::insertTab(const ComponentPtr TabInsert, const ComponentPtr Tab, const ComponentPtr TabContent)
{
	Tab->addFocusListener(this);
	UInt32 index(0);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask | ChildrenFieldMask);
		getChildren().addValue(Tab);
		getChildren().addValue(TabContent);
		// check if the component is a tab or tabcontent, then insert accordingly
		if (getTabs().end() == getTabs().find(TabInsert))
		{
			for (UInt32 i = 0; i < getTabContents().size(); ++i)
			{
				if(getTabContents().find(TabInsert) == getTabContents().find(getTabContents().getValue(i)))
					index = i;
			}
			getTabContents().insert(getTabContents().find(TabInsert), TabContent);
			getTabs().insert(getTabs().find(getTabs().getValue(index)), Tab);
		}
		else
		{
			for (UInt32 i = 0; i < getTabs().size(); ++i)
			{
				if(getTabs().find(TabInsert) == getTabs().find(getTabs().getValue(i)))
					index = i;
			}
			getTabs().insert(getTabs().find(TabInsert), Tab);
			getTabContents().insert(getTabContents().find(getTabContents().getValue(index)), TabContent);
		}
		endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::insertTab(const UInt32 TabIndex, const ComponentPtr Tab, const ComponentPtr TabContent)
{
	Tab->addFocusListener(this);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
		getChildren().addValue(Tab);
		getChildren().addValue(TabContent);
		getTabs().insert(getTabs().find(getTabs().getValue(TabIndex)), Tab); // an incredibly ridiculous function call
		getTabContents().insert(getTabContents().find(getTabContents().getValue(TabIndex)), TabContent);
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask| ChildrenFieldMask);
}

void TabPanel::updateTabLayout(void)
{
	Pnt2s borderOffset;
	Vec2s borderSize;
	getInsideInsetsBounds(borderOffset, borderSize);

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
			getTabs().getValue(i)->setPosition(alignOffset + Vec2s(offset));
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

void TabPanel::mouseClicked(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isContainedClipBounds(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
		if(isContained)
		{
			getTabs().getValue(i)->mouseClicked(e);
		}
    }

	isContained = isContainedClipBounds(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);
	if(isContained)
	{
		getTabContents().getValue(getActiveTab())->mouseClicked(e);
	}

	Component::mouseClicked(e);
}

void TabPanel::mouseEntered(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isPointInComponent(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
		if(isContained)
		{
			getTabs().getValue(i)->mouseDragged(e);
		}
    }

	isContained = isPointInComponent(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);
	if(isContained)
	{
		getTabContents().getValue(getActiveTab())->mouseDragged(e);
	}

	Component::mouseEntered(e);
}

void TabPanel::mouseExited(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isPointInComponent(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
		if(isContained)
		{
			getTabs().getValue(i)->mouseDragged(e);
		}
    }

	isContained = isPointInComponent(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);
	if(isContained)
	{
		getTabContents().getValue(getActiveTab())->mouseDragged(e);
	}

	Component::mouseExited(e);
}

void TabPanel::mousePressed(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getTabs().size()-1) ; i>=0 ; --i)
    {   // going backwards through through elements, so only top button is pressed
		isContained = isPointInComponent(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
		if(isContained)
		{
			//Give myself temporary focus
			takeFocus(true);
			if(!getTabs().getValue(i)->getType().isDerivedFrom(Container::getClassType()))
			{
				getTabs().getValue(i)->takeFocus();
			}
			getTabs().getValue(i)->mousePressed(e);
			break;
		}
    }
	if(isContained)
	{
		//Remove my temporary focus
		giveFocus(NullFC, false);
	}
	else
	{
		//Give myself permanant focus
		takeFocus();
	}

	// now do it for the content tab
	isContained = isPointInComponent(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);
	if(isContained)
	{
		//Give myself temporary focus
		takeFocus(true);
		if(!getTabContents().getValue(getActiveTab())->getType().isDerivedFrom(Container::getClassType()))
		{
			getTabContents().getValue(getActiveTab())->takeFocus();
		}
		getTabContents().getValue(getActiveTab())->mousePressed(e);

		giveFocus(NullFC, false);
	}
	else
	{
		//Give myself permanent focus
		takeFocus();
	}

	Component::mousePressed(e);
}

void TabPanel::mouseReleased(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isContainedClipBounds(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
		if(isContained)
		{
			getTabs().getValue(i)->mouseReleased(e);
		}
    }

	isContained = isContainedClipBounds(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);
	if(isContained)
	{
		getTabContents().getValue(getActiveTab())->mouseReleased(e);
	}

	Component::mouseReleased(e);
}


void TabPanel::mouseMoved(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isContainedClipBounds(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
		if(isContained)
		{
			getTabs().getValue(i)->mouseMoved(e);
		}
    }

	isContained = isContainedClipBounds(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);
	if(isContained)
	{
		getTabContents().getValue(getActiveTab())->mouseMoved(e);
	}

	Component::mouseMoved(e);
}

void TabPanel::mouseDragged(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isContainedClipBounds(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
		if(isContained)
		{
			getTabs().getValue(i)->mouseDragged(e);
		}
    }

	isContained = isContainedClipBounds(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);
	if(isContained)
	{
		getTabContents().getValue(getActiveTab())->mouseDragged(e);
	}

	Component::mouseDragged(e);
}

void TabPanel::mouseWheelMoved(const MouseWheelEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isContainedClipBounds(e.getLocation(), getTabs().getValue(i));
		checkMouseEnterExit(e,e.getLocation(),getTabs().getValue(i),isContained);
    }

	isContained = isContainedClipBounds(e.getLocation(), getTabContents().getValue(getActiveTab()));
	checkMouseEnterExit(e,e.getLocation(),getTabContents().getValue(getActiveTab()),isContained);

	Component::mouseWheelMoved(e);
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


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

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "OSGTabPanel.h"
#include "Util/OSGUIDrawUtils.h"
#include "Border/OSGBorder.h"
#include "Layer/OSGLayer.h"
#include "Models/SelectionModels/OSGSingleSelectionModel.h"

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

void TabPanel::calculateTabBorderLengths(BorderPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const
{
	if(TheBorder != NullFC)
	{
		TheBorder->getInsets(Left, Right,Top, Bottom);
	}
	else
	{
		Left = Right = Top = Bottom = 0.0f;
	}
	switch(getTabPlacement())
	{
	case PLACEMENT_SOUTH:
		Top = 0.0f;
		break;
	case PLACEMENT_EAST:
		Left = 0.0f;
		break;
	case PLACEMENT_NORTH:
		Bottom = 0.0f;
		break;
	case PLACEMENT_WEST:
		Right = 0.0f;
		break;
	}

	Left += getTabBorderInsets().x();
	Right += getTabBorderInsets().x();
	Top += getTabBorderInsets().y();
	Bottom += getTabBorderInsets().y();
}

void TabPanel::calculateContentBorderLengths(BorderPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const
{
	if(TheBorder != NullFC)
	{
		TheBorder->getInsets(Left, Right,Top, Bottom);
	}
	else
	{
		Left = Right = Top = Bottom = 0.0f;
	}

	Left += getContentBorderInsets().x();
	Right += getContentBorderInsets().x();
	Top += getContentBorderInsets().y();
	Bottom += getContentBorderInsets().y();
}

void TabPanel::calculateMaxTabBorderLengths(Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const
{
	std::vector<BorderPtr> Borders;
	Borders.push_back(getTabBorder());
	Borders.push_back(getTabActiveBorder());
	Borders.push_back(getTabDisabledBorder());
	Borders.push_back(getTabRolloverBorder());
	Borders.push_back(getTabFocusedBorder());

	Left = Right = Top = Bottom = 0.0f;
	Real32 BorderLeft, BorderRight, BorderTop, BorderBottom;
	for(UInt32 i(0) ; i<Borders.size() ; ++i)
	{
		if(Borders[i] != NullFC)
		{
			Borders[i]->getInsets(BorderLeft, BorderRight, BorderTop, BorderBottom);
			Left = osgMax(Left, BorderLeft);
			Right = osgMax(Right, BorderRight);
			Top = osgMax(Top, BorderTop);
			Bottom = osgMax(Bottom, BorderBottom);
		}
	}

	switch(getTabPlacement())
	{
	case PLACEMENT_SOUTH:
		Top = 0.0f;
		break;
	case PLACEMENT_EAST:
		Left = 0.0f;
		break;
	case PLACEMENT_NORTH:
		Bottom = 0.0f;
		break;
	case PLACEMENT_WEST:
		Right = 0.0f;
		break;
	}

	Left += getTabBorderInsets().x();
	Right += getTabBorderInsets().x();
	Top += getTabBorderInsets().y();
	Bottom += getTabBorderInsets().y();
}

void TabPanel::drawInternal(const GraphicsPtr Graphics) const
{
	//Draw the Tab Borders
	//Setup the Clip Planes
	Real32 TabBorderLeftWidth, TabBorderRightWidth,TabBorderTopWidth, TabBorderBottomWidth;

	Pnt2f TabPosition, TabBorderPosition;
	Vec2f TabSize, TabBorderSize;
	BorderPtr DrawnTabBorder;
	LayerPtr DrawnTabBackground;
	for (UInt32 i = 0; i < getTabs().size(); ++i)
	{
		TabPosition = getTabs()[i]->getPosition();
		TabSize = getTabs()[i]->getSize();

		DrawnTabBorder = getDrawnTabBorder(i);
		DrawnTabBackground = getDrawnTabBackground(i);
		
		calculateTabBorderLengths(DrawnTabBorder, TabBorderLeftWidth, TabBorderRightWidth,TabBorderTopWidth, TabBorderBottomWidth);
		
		TabBorderPosition.setValues(TabPosition.x() - TabBorderLeftWidth, TabPosition.y() - TabBorderTopWidth);
		TabBorderSize.setValues(TabSize.x() + TabBorderLeftWidth + TabBorderRightWidth,
			                    TabSize.y() + TabBorderTopWidth + TabBorderBottomWidth);

		if(DrawnTabBorder != NullFC)
		{
			DrawnTabBorder->draw(Graphics,
								 TabBorderPosition.x(), TabBorderPosition.y(),
								 TabBorderSize.x(), TabBorderSize.y(),
								 getOpacity());
			//DrawnTabBorder->activateInternalDrawConstraints(Graphics,
			//                 TabBorderPosition.x(), TabBorderPosition.y(),
			//				 TabBorderSize.x(), TabBorderSize.y());
		}

		if(DrawnTabBackground != NullFC)
		{
			DrawnTabBackground->draw(Graphics, TabPosition - getTabBorderInsets(), TabPosition + TabSize + getTabBorderInsets(), getOpacity());
		}

		//Draw the tab component
		getTabs()[i]->draw(Graphics);
		
		setupClipping(Graphics);

		if(DrawnTabBorder != NullFC)
		{
			DrawnTabBorder->deactivateInternalDrawConstraints(Graphics,
			                 TabBorderPosition.x(), TabBorderPosition.y(),
							 TabBorderSize.x(), TabBorderSize.y());
		}
	}
	
	//Draw the Content of the active tab
	if(getTabContents().size() > 0 &&
       getSelectedIndex() != -1)
	{
		ComponentPtr ContentComponent(getTabContents()[getSelectedIndex()]);

		BorderPtr DrawnContentBorder = getDrawnContentBorder();
		LayerPtr DrawnContentBackground = getDrawnContentBackground();
		
		Real32 ContentBorderLeftWidth, ContentBorderRightWidth,ContentBorderTopWidth, ContentBorderBottomWidth;
		calculateContentBorderLengths(DrawnContentBorder, ContentBorderLeftWidth, ContentBorderRightWidth,ContentBorderTopWidth, ContentBorderBottomWidth);

		Pnt2f ContentBorderPosition(ContentComponent->getPosition() - Vec2f(ContentBorderLeftWidth,ContentBorderTopWidth));
		Vec2f ContentBorderSize(ContentComponent->getSize() + Vec2f(ContentBorderLeftWidth+ContentBorderRightWidth,ContentBorderTopWidth+ContentBorderBottomWidth));
		if(DrawnContentBorder != NullFC)
		{
			DrawnContentBorder->draw(Graphics,
								 ContentBorderPosition.x(), ContentBorderPosition.y(),
								 ContentBorderSize.x(), ContentBorderSize.y(),
								 getOpacity());
		}
		if(DrawnContentBackground != NullFC)
		{
			DrawnContentBackground->draw(Graphics, ContentComponent->getPosition() - getContentBorderInsets(), ContentComponent->getPosition() + ContentComponent->getSize() + getContentBorderInsets(), getOpacity());
		}

		ContentComponent->draw(Graphics);
		
		if(DrawnContentBorder != NullFC)
		{
			DrawnContentBorder->deactivateInternalDrawConstraints(Graphics,
			                 ContentBorderPosition.x(), ContentBorderPosition.y(),
							 ContentBorderSize.x(), ContentBorderSize.y());
		}
	}
}

void TabPanel::focusGained(const FocusEvent& e)
{
	ComponentPtr Tab = Component::Ptr::dcast(e.getSource());
	Int32 index(-1);

	for (UInt32 i = 0; i < getTabs().size(); ++i)
	{
		if(getTabs().find(Tab) == getTabs().find(getTabs()[i]))
			index = i;
	}
	if (index != -1)
	{
        setSelectedIndex(index);
	}
}

ComponentPtr TabPanel::getSelectedComponent(void) const
{
    Int32 Index(getSelectedIndex());
    if(Index != -1)
    {
        return getTabContents()[Index];
    }
    else
    {
        return NullFC;
    }
}

Int32 TabPanel::getSelectedIndex(void) const
{
    if(getSelectionModel() != NullFC)
    {
        return getSelectionModel()->getSelectedIndex();
    }
    else
    {
        return -1;
    }
}

void TabPanel::setSelectedIndex(const Int32& Index)
{
    if(getSelectionModel() != NullFC)
    {
        getSelectionModel()->setSelectedIndex(Index);
    }
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
		getTabs().push_back(Tab);
		getTabContents().push_back(TabContent);
		getChildren().push_back(Tab);
		getChildren().push_back(TabContent);
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
				if(getTabContents().find(Tab) == getTabContents().find(getTabContents()[i]))
					index = i;
			}
			getTabContents().erase(getTabContents().find(Tab));
			// also erase the the tab from the components list
			getTabs()[index]->removeFocusListener(this);
			getChildren().erase(getChildren().find(getTabs()[index]));
			getTabs().erase(getTabs().find(getTabs()[index]));
		}
		else
		{
			for (UInt32 i = 0; i < getTabs().size(); ++i)
			{
				if(getTabs().find(Tab) == getTabs().find(getTabs()[i]))
					index = i;
			}
			Tab->removeFocusListener(this);
			getTabs().erase(getTabs().find(Tab));
			// also erase the the tab from the components list
			getChildren().erase(getChildren().find(getTabContents()[index])); 
			getTabContents().erase(getTabContents().find(getTabContents()[index]));
		}
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::removeTab(const UInt32 TabIndex)
{
	getTabs()[TabIndex]->removeFocusListener(this);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
		getChildren().erase(getChildren().find(getTabs()[TabIndex])); // an incredibly ridiculous function call
		getChildren().erase(getChildren().find(getTabContents()[TabIndex]));
		getTabs().erase(getTabs().find(getTabs()[TabIndex])); // an incredibly ridiculous function call
		getTabContents().erase(getTabContents().find(getTabContents()[TabIndex]));
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::removeAllTabs(void)
{
	for(UInt32 i(0) ; i<getTabs().size() ; ++i)
	{
		getTabs()[i]->removeFocusListener(this);
	}

	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
		getChildren().clear();
		getTabs().clear();
		getTabContents().clear();
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::insertTab(const ComponentPtr TabInsert, const ComponentPtr Tab, const ComponentPtr TabContent)
{
	Tab->addFocusListener(this);
	UInt32 index(0);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask | ChildrenFieldMask);
		getChildren().push_back(Tab);
		getChildren().push_back(TabContent);
		// check if the component is a tab or tabcontent, then insert accordingly
		if (getTabs().end() == getTabs().find(TabInsert))
		{
			for (UInt32 i = 0; i < getTabContents().size(); ++i)
			{
				if(getTabContents().find(TabInsert) == getTabContents().find(getTabContents()[i]))
					index = i;
			}
			getTabContents().insert(getTabContents().find(TabInsert), TabContent);
			getTabs().insert(getTabs().find(getTabs()[index]), Tab);
		}
		else
		{
			for (UInt32 i = 0; i < getTabs().size(); ++i)
			{
				if(getTabs().find(TabInsert) == getTabs().find(getTabs()[i]))
					index = i;
			}
			getTabs().insert(getTabs().find(TabInsert), Tab);
			getTabContents().insert(getTabContents().find(getTabContents()[index]), TabContent);
		}
		endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
}

void TabPanel::insertTab(const UInt32 TabIndex, const ComponentPtr Tab, const ComponentPtr TabContent)
{
	Tab->addFocusListener(this);
	beginEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask | ChildrenFieldMask);
		getChildren().push_back(Tab);
		getChildren().push_back(TabContent);
		getTabs().insert(getTabs().find(getTabs()[TabIndex]), Tab); // an incredibly ridiculous function call
		getTabContents().insert(getTabContents().find(getTabContents()[TabIndex]), TabContent);
	endEditCP(TabPanelPtr(this), TabsFieldMask | TabContentsFieldMask| ChildrenFieldMask);
}

void TabPanel::updateLayout(void)
{
	Pnt2f InsideInsetsTopLeft,InsideInsetsBottomRight;
	getInsideInsetsBounds(InsideInsetsTopLeft,InsideInsetsBottomRight);

	UInt16 AxisIndex(0);
	if (getTabPlacement() == PLACEMENT_EAST || getTabPlacement() == PLACEMENT_WEST)
	{
		AxisIndex=1;
	}
	Real32 largestMinorAxis(0.0f);
	Real32 cumMajorAxis(0.0f);
	Pnt2f alignOffset(0.0f,0.0f);
	Vec2f offset(0.0f,0.0f);
	
	Vec2f TabBorderTopLeftWidth, TabBorderBottomRightWidth;
	calculateMaxTabBorderLengths(TabBorderTopLeftWidth[0], TabBorderBottomRightWidth[0],TabBorderTopLeftWidth[1], TabBorderBottomRightWidth[1]);

	// first layout all of the tabs
	// naturally the alignments and such is necessary
	// on the first sweep, get the maximum size and cumLength
	for (UInt32 i=0; i < getTabs().size(); ++i)
	{
		cumMajorAxis += getTabs()[i]->getRequestedSize()[AxisIndex];
		if (getTabs()[i]->getRequestedSize()[(AxisIndex+1)%2] > largestMinorAxis)
		{
			largestMinorAxis = getTabs()[i]->getRequestedSize()[(AxisIndex+1)%2];
		}
	}
	cumMajorAxis += static_cast<Real32>(getTabs().size()) * (TabBorderTopLeftWidth[AxisIndex] + TabBorderBottomRightWidth[AxisIndex]);
	largestMinorAxis += (TabBorderTopLeftWidth[(AxisIndex+1)%2] + TabBorderBottomRightWidth[(AxisIndex+1)%2]);
		            

	// set up the alignment and offset
	Vec2f TabSize;
	TabSize[AxisIndex] = cumMajorAxis;
	TabSize[(AxisIndex+1)%2] = largestMinorAxis;
	Vec2f Alignment;
	Alignment[(AxisIndex+1)%2] = getTabAlignment();
	switch(getTabPlacement())
	{
	case PLACEMENT_SOUTH:
	case PLACEMENT_EAST:
		Alignment[AxisIndex] = 1.0;
		break;
	case PLACEMENT_NORTH:
	case PLACEMENT_WEST:
		Alignment[AxisIndex] = 0.0;
		break;
	}
	alignOffset = calculateAlignment(InsideInsetsTopLeft, (InsideInsetsBottomRight-InsideInsetsTopLeft),TabSize,Alignment.x(),Alignment.y());
	offset = Vec2f(InsideInsetsTopLeft);
	offset[(AxisIndex+1)%2] += TabBorderTopLeftWidth[(AxisIndex+1)%2];

	// set sizes and positions of all tabs
	for (UInt32 i=0; i < getTabs().size(); ++i)
	{
		offset[AxisIndex] += TabBorderTopLeftWidth[AxisIndex];
		beginEditCP(getTabs()[i], Component::SizeFieldMask|Component::PositionFieldMask);
			getTabs()[i]->setSize(getTabs()[i]->getRequestedSize());
			getTabs()[i]->setPosition(alignOffset + offset);
		endEditCP(getTabs()[i], Component::SizeFieldMask|Component::PositionFieldMask);
		offset[AxisIndex] += getTabs()[i]->getSize()[AxisIndex] + TabBorderBottomRightWidth[AxisIndex];
	}

	if(getTabContents().size() > 0 && getSelectedIndex() != -1)
	{
		Vec2f ContentBorderTopLeftWidth, ContentBorderBottomRightWidth;
		calculateContentBorderLengths(getContentBorder(), ContentBorderTopLeftWidth[0], ContentBorderBottomRightWidth[0],ContentBorderTopLeftWidth[1], ContentBorderBottomRightWidth[1]);
		// now set size and position of the active tab's contents
		offset = Vec2f(InsideInsetsTopLeft);
		if (getTabPlacement() == PLACEMENT_NORTH || getTabPlacement() == PLACEMENT_WEST)
		{
			offset[(AxisIndex+1)%2] += largestMinorAxis;
		}
		Vec2f ContentsSize(InsideInsetsBottomRight-InsideInsetsTopLeft);
		ContentsSize[(AxisIndex+1)%2] -= TabSize[(AxisIndex+1)%2];
		beginEditCP(getTabContents()[getSelectedIndex()], Component::SizeFieldMask|Component::PositionFieldMask);
			getTabContents()[getSelectedIndex()]->setSize(ContentsSize);
			getTabContents()[getSelectedIndex()]->setPosition(offset + ContentBorderTopLeftWidth);
		endEditCP(getTabContents()[getSelectedIndex()], Component::SizeFieldMask|Component::PositionFieldMask);
	}
}

void TabPanel::mouseClicked(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
		isContained = isContainedClipBounds(e.getLocation(), getTabs()[i]);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
		if(isContained)
		{
			getTabs()[i]->mouseClicked(e);
		}
    }

	isContained = isContainedClipBounds(e.getLocation(), getTabContents()[getSelectedIndex()]);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());
	if(isContained)
	{
		getTabContents()[getSelectedIndex()]->mouseClicked(e);
	}

	Component::mouseClicked(e);
}

void TabPanel::mouseEntered(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
        isContained = getTabs()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
		if(isContained)
		{
			getTabs()[i]->mouseDragged(e);
		}
    }

    isContained = getTabContents()[getSelectedIndex()]->isContained(e.getLocation(), true);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());
	if(isContained)
	{
		getTabContents()[getSelectedIndex()]->mouseDragged(e);
	}

	Component::mouseEntered(e);
}

void TabPanel::mouseExited(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
        isContained = getTabs()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
		if(isContained)
		{
			getTabs()[i]->mouseDragged(e);
		}
    }

    isContained = getTabContents()[getSelectedIndex()]->isContained(e.getLocation(), true);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());
	if(isContained)
	{
		getTabContents()[getSelectedIndex()]->mouseDragged(e);
	}

	Component::mouseExited(e);
}

void TabPanel::mousePressed(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getTabs().size()-1) ; i>=0 ; --i)
    {   // going backwards through through elements, so only top button is pressed
        isContained = getTabs()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
		if(isContained)
		{
			//Give myself temporary focus
			takeFocus(true);
			if(!getTabs()[i]->getType().isDerivedFrom(Container::getClassType()))
			{
				getTabs()[i]->takeFocus();
			}
			getTabs()[i]->mousePressed(e);
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
    isContained = getTabContents()[getSelectedIndex()]->isContained(e.getLocation(), true);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());
	if(isContained)
	{
		//Give myself temporary focus
		takeFocus(true);
		if(!getTabContents()[getSelectedIndex()]->getType().isDerivedFrom(Container::getClassType()))
		{
			getTabContents()[getSelectedIndex()]->takeFocus();
		}
		getTabContents()[getSelectedIndex()]->mousePressed(e);

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
        isContained = getTabs()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
		if(isContained)
		{
			getTabs()[i]->mouseReleased(e);
		}
    }

    isContained = getTabContents()[getSelectedIndex()]->isContained(e.getLocation(), true);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());
	if(isContained)
	{
		getTabContents()[getSelectedIndex()]->mouseReleased(e);
	}

	Component::mouseReleased(e);
}


void TabPanel::mouseMoved(const MouseEvent& e)
{
	Component::mouseMoved(e);
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
        isContained = getTabs()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
		if(isContained)
		{
			getTabs()[i]->mouseMoved(e);
		}
    }

    isContained = getTabContents()[getSelectedIndex()]->isContained(e.getLocation(), true);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());
	if(isContained)
	{
		getTabContents()[getSelectedIndex()]->mouseMoved(e);
	}

}

void TabPanel::mouseDragged(const MouseEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
        isContained = getTabs()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
		if(isContained)
		{
			getTabs()[i]->mouseDragged(e);
		}
    }

    isContained = getTabContents()[getSelectedIndex()]->isContained(e.getLocation(), true);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());
	if(isContained)
	{
		getTabContents()[getSelectedIndex()]->mouseDragged(e);
	}

	Component::mouseDragged(e);
}

void TabPanel::mouseWheelMoved(const MouseWheelEvent& e)
{
	bool isContained;
    for(UInt32 i(0) ; i<getTabs().size() ; ++i)
    {
        isContained = getTabs()[i]->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getTabs()[i],isContained,e.getViewport());
    }

    isContained = getTabContents()[getSelectedIndex()]->isContained(e.getLocation(), true);
	checkMouseEnterExit(e,e.getLocation(),getTabContents()[getSelectedIndex()],isContained,e.getViewport());

	Component::mouseWheelMoved(e);
}

BorderPtr TabPanel::getDrawnTabBorder(const UInt32& Index) const
{
    if(getEnabled())
    {
        if(Index == getSelectedIndex())
        {
            return getTabActiveBorder();
        }
        else if(Index == _MouseInTabLastMouse)
        {
            return getTabRolloverBorder();
        }
		else if(getTabs()[Index]->getFocused())
        {
            return getTabFocusedBorder();
        }
        else
        {
            return getTabBorder();
        }
    }
    else
    {
        return getTabDisabledBorder();
    }
}

LayerPtr TabPanel::getDrawnTabBackground(const UInt32& Index) const
{
    if(getEnabled())
    {
        if(Index == getSelectedIndex())
        {
            return getTabActiveBackground();
        }
        else if(Index == _MouseInTabLastMouse)
        {
            return getTabRolloverBackground();
        }
		else if(getTabs()[Index]->getFocused())
        {
            return getTabFocusedBackground();
        }
        else
        {
            return getTabBackground();
        }
    }
    else
    {
        return getTabDisabledBackground();
    }
}

BorderPtr TabPanel::getDrawnContentBorder(void) const
{
    if(getEnabled())
    {
        if(false) //TODO: Implement
        {
            return getContentRolloverBorder();
        }
        else
        {
            return getContentBorder();
        }
    }
    else
    {
        return getContentDisabledBorder();
    }
}

LayerPtr TabPanel::getDrawnContentBackground(void) const
{
    if(getEnabled())
    {
        if(false) //TODO: Implement
        {
            return getContentRolloverBackground();
        }
        else
        {
            return getContentBackground();
        }
    }
    else
    {
        return getContentDisabledBackground();
    }
}

void TabPanel::addSelectionListener(SelectionListenerPtr listener)
{
    if(getSelectionModel() != NullFC)
    {
        getSelectionModel()->addSelectionListener(listener);
    }
}

void TabPanel::removeSelectionListener(SelectionListenerPtr listener)
{
    if(getSelectionModel() != NullFC)
    {
        getSelectionModel()->removeSelectionListener(listener);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TabPanel::TabPanel(void) :
    Inherited(),
		_MouseInTabLastMouse(-1),
    _TabSelectionListener(TabPanelPtr(this))
{
}

TabPanel::TabPanel(const TabPanel &source) :
    Inherited(source),
		_MouseInTabLastMouse(-1),
    _TabSelectionListener(TabPanelPtr(this))
{
    if(getSelectionModel() != NullFC)
    {
        beginEditCP(TabPanelPtr(this), TabPanel::SelectionModelFieldMask);
            setSelectionModel(SingleSelectionModel::Ptr::dcast(getSelectionModel()->shallowCopy()));
        endEditCP(TabPanelPtr(this), TabPanel::SelectionModelFieldMask);
    }
}

TabPanel::~TabPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TabPanel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if( (whichField & TabsFieldMask) || (whichField & TabContentsFieldMask))
    {
		updateLayout();
	}

    if(whichField & TabPanel::SelectionModelFieldMask && getSelectionModel() != NullFC)
    {
        getSelectionModel()->addSelectionListener(&_TabSelectionListener);
    }
}

void TabPanel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TabPanel NI" << std::endl;
}

void TabPanel::TabSelectionListener::selectionChanged(const SelectionEvent& e)
{
    _TabPanel->updateLayout();
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


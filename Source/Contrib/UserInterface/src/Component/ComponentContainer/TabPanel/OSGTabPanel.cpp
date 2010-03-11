/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGTabPanel.h"
#include "OSGUIDrawUtils.h"
#include "OSGBorder.h"
#include "OSGLayer.h"
#include "OSGDefaultSingleSelectionModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTabPanelBase.cpp file.
// To modify it, please change the .fcd file (OSGTabPanel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TabPanel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TabPanel::calculateTabBorderLengths(BorderRefPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const
{
    if(TheBorder != NULL)
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

    Left   += getTabBorderInsets().x();
    Right  += getTabBorderInsets().x();
    Top    += getTabBorderInsets().y();
    Bottom += getTabBorderInsets().y();
}

void TabPanel::calculateContentBorderLengths(BorderRefPtr TheBorder, Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const
{
    if(TheBorder != NULL)
    {
        TheBorder->getInsets(Left, Right,Top, Bottom);
    }
    else
    {
        Left = Right = Top = Bottom = 0.0f;
    }

    Left   += getContentBorderInsets().x();
    Right  += getContentBorderInsets().x();
    Top    += getContentBorderInsets().y();
    Bottom += getContentBorderInsets().y();
}

void TabPanel::calculateMaxTabBorderLengths(Real32& Left, Real32& Right, Real32& Top, Real32& Bottom) const
{
    std::vector<BorderRefPtr> Borders;
    Borders.push_back(getTabBorder());
    Borders.push_back(getTabActiveBorder());
    Borders.push_back(getTabDisabledBorder());
    Borders.push_back(getTabRolloverBorder());
    Borders.push_back(getTabFocusedBorder());

    Left = Right = Top = Bottom = 0.0f;
    Real32 BorderLeft, BorderRight, BorderTop, BorderBottom;
    for(UInt32 i(0) ; i<Borders.size() ; ++i)
    {
        if(Borders[i] != NULL)
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

void TabPanel::drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity) const
{
    //Draw the Tab Borders
    //Setup the Clip Planes
    Real32 TabBorderLeftWidth, TabBorderRightWidth,TabBorderTopWidth, TabBorderBottomWidth;

    Pnt2f TabPosition, TabBorderPosition;
    Vec2f TabSize, TabBorderSize;
    BorderRefPtr DrawnTabBorder;
    LayerRefPtr DrawnTabBackground;
    for (UInt32 i = 0; i < getMFTabs()->size(); ++i)
    {
        TabPosition = getTabs(i)->getPosition();
        TabSize = getTabs(i)->getSize();

        DrawnTabBorder = getDrawnTabBorder(i);
        DrawnTabBackground = getDrawnTabBackground(i);

        calculateTabBorderLengths(DrawnTabBorder, TabBorderLeftWidth, TabBorderRightWidth,TabBorderTopWidth, TabBorderBottomWidth);

        TabBorderPosition.setValues(TabPosition.x() - TabBorderLeftWidth, TabPosition.y() - TabBorderTopWidth);
        TabBorderSize.setValues(TabSize.x() + TabBorderLeftWidth + TabBorderRightWidth,
                                TabSize.y() + TabBorderTopWidth + TabBorderBottomWidth);

        if(DrawnTabBorder != NULL)
        {
            DrawnTabBorder->draw(Graphics,
                                 TabBorderPosition.x(), TabBorderPosition.y(),
                                 TabBorderSize.x(), TabBorderSize.y(),
                                 getOpacity()*Opacity);
            //DrawnTabBorder->activateInternalDrawConstraints(Graphics,
            //                 TabBorderPosition.x(), TabBorderPosition.y(),
            //				 TabBorderSize.x(), TabBorderSize.y());
        }

        if(DrawnTabBackground != NULL)
        {
            DrawnTabBackground->draw(Graphics, TabPosition - getTabBorderInsets(), TabPosition + TabSize + getTabBorderInsets(), getOpacity()*Opacity);
        }

        //Draw the tab component
        getTabs(i)->draw(Graphics, getOpacity()*Opacity);

        setupClipping(Graphics);

        if(DrawnTabBorder != NULL)
        {
            DrawnTabBorder->deactivateInternalDrawConstraints(Graphics,
                                                              TabBorderPosition.x(), TabBorderPosition.y(),
                                                              TabBorderSize.x(), TabBorderSize.y());
        }
    }

    //Draw the Content of the active tab
    if(getMFTabContents()->size() > 0 &&
       getSelectedIndex() != -1)
    {
        ComponentRefPtr ContentComponent(getTabContents(getSelectedIndex()));

        BorderRefPtr DrawnContentBorder = getDrawnContentBorder();
        LayerRefPtr DrawnContentBackground = getDrawnContentBackground();

        Real32 ContentBorderLeftWidth, ContentBorderRightWidth,ContentBorderTopWidth, ContentBorderBottomWidth;
        calculateContentBorderLengths(DrawnContentBorder, ContentBorderLeftWidth, ContentBorderRightWidth,ContentBorderTopWidth, ContentBorderBottomWidth);

        Pnt2f ContentBorderPosition(ContentComponent->getPosition() - Vec2f(ContentBorderLeftWidth,ContentBorderTopWidth));
        Vec2f ContentBorderSize(ContentComponent->getSize() + Vec2f(ContentBorderLeftWidth+ContentBorderRightWidth,ContentBorderTopWidth+ContentBorderBottomWidth));
        if(DrawnContentBorder != NULL)
        {
            DrawnContentBorder->draw(Graphics,
                                     ContentBorderPosition.x(), ContentBorderPosition.y(),
                                     ContentBorderSize.x(), ContentBorderSize.y(),
                                     getOpacity()*Opacity);
        }
        if(DrawnContentBackground != NULL)
        {
            DrawnContentBackground->draw(Graphics, ContentComponent->getPosition() - getContentBorderInsets(), ContentComponent->getPosition() + ContentComponent->getSize() + getContentBorderInsets(), getOpacity()*Opacity);
        }

        ContentComponent->draw(Graphics, getOpacity()*Opacity);

        if(DrawnContentBorder != NULL)
        {
            DrawnContentBorder->deactivateInternalDrawConstraints(Graphics,
                                                                  ContentBorderPosition.x(), ContentBorderPosition.y(),
                                                                  ContentBorderSize.x(), ContentBorderSize.y());
        }
    }
}

void TabPanel::focusGained(const FocusEventUnrecPtr e)
{
    ComponentRefPtr Tab = dynamic_cast<Component*>(e->getSource());
    Int32 index(-1);

    for (UInt32 i = 0; i < getMFTabs()->size(); ++i)
    {
        if(editMFTabs()->find(Tab) == editMFTabs()->find(getTabs(i)))
            index = i;
    }
    if (index != -1)
    {
        setSelectedIndex(index);
    }
}

ComponentRefPtr TabPanel::getSelectedComponent(void) const
{
    Int32 Index(getSelectedIndex());
    if(Index != -1)
    {
        return getTabContents(Index);
    }
    else
    {
        return NULL;
    }
}

Int32 TabPanel::getSelectedIndex(void) const
{
    if(getSelectionModel() != NULL)
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
    if(getSelectionModel() != NULL)
    {
        getSelectionModel()->setSelectedIndex(Index);
    }
}

void TabPanel::focusLost(const FocusEventUnrecPtr e)
{
}

void TabPanel::addTab(const ComponentRefPtr Tab, const ComponentRefPtr TabContent)
{
    // three lists of components are actually kept
    // every component, whether tab or tabcontent is kept in the children list
    // this is for clipping and clicking purposes
    // for drawing, the tabs and tabcontents are kept seperately in two other lists
    // so, there are three lists, and every component is kept in two of them
    Tab->addFocusListener(this);

    pushToTabs(Tab);
    pushToTabContents(TabContent);
    pushToChildren(Tab);
    pushToChildren(TabContent);
}

void TabPanel::removeTab(const ComponentRefPtr Tab)
{
    UInt32 index(0);
    // also erase the the tab from the components list
    editMFChildren()->erase(editMFChildren()->find(Tab));
    // check if the component is a tab or tabcontent, then erase accordingly
    if (editMFTabs()->end() == editMFTabs()->find(Tab))
    {	// so it isn't in tabs
        for (UInt32 i = 0; i < getMFTabContents()->size(); ++i)
        {
            if(editMFTabContents()->find(Tab) == editMFTabContents()->find(getTabContents(i)))
                index = i;
        }
        editMFTabContents()->erase(editMFTabContents()->find(Tab));
        // also erase the the tab from the components list
        getTabs(index)->removeFocusListener(this);
        editMFChildren()->erase(editMFChildren()->find(getTabs(index)));
        editMFTabs()->erase(editMFTabs()->find(getTabs(index)));
    }
    else
    {
        for (UInt32 i = 0; i < getMFTabs()->size(); ++i)
        {
            if(editMFTabs()->find(Tab) == editMFTabs()->find(getTabs(i)))
                index = i;
        }
        Tab->removeFocusListener(this);
        editMFTabs()->erase(editMFTabs()->find(Tab));
        // also erase the the tab from the components list
        editMFChildren()->erase(editMFChildren()->find(getTabContents(index))); 
        editMFTabContents()->erase(editMFTabContents()->find(getTabContents(index)));
    }
}

void TabPanel::removeTab(const UInt32 TabIndex)
{
    getTabs(TabIndex)->removeFocusListener(this);
    editMFChildren()->erase(editMFChildren()->find(getTabs(TabIndex))); // an incredibly ridiculous function call
    editMFChildren()->erase(editMFChildren()->find(getTabContents(TabIndex)));
    editMFTabs()->erase(editMFTabs()->find(getTabs(TabIndex))); // an incredibly ridiculous function call
    editMFTabContents()->erase(editMFTabContents()->find(getTabContents(TabIndex)));
}

void TabPanel::removeAllTabs(void)
{
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        getTabs(i)->removeFocusListener(this);
    }

    clearChildren();
    clearTabs();
    clearTabContents();
}

void TabPanel::insertTab(const ComponentRefPtr TabInsert, const ComponentRefPtr Tab, const ComponentRefPtr TabContent)
{
    Tab->addFocusListener(this);
    UInt32 index(0);
    pushToChildren(Tab);
    pushToChildren(TabContent);
    // check if the component is a tab or tabcontent, then insert accordingly
    if (editMFTabs()->end() == editMFTabs()->find(TabInsert))
    {
        for (UInt32 i = 0; i < getMFTabContents()->size(); ++i)
        {
            if(editMFTabContents()->find(TabInsert) == editMFTabContents()->find(getTabContents(i)))
                index = i;
        }
        editMFTabContents()->insert(editMFTabContents()->find(TabInsert), TabContent);
        editMFTabs()->insert(editMFTabs()->find(getTabs(index)), Tab);
    }
    else
    {
        for (UInt32 i = 0; i < getMFTabs()->size(); ++i)
        {
            if(editMFTabs()->find(TabInsert) == editMFTabs()->find(getTabs(i)))
                index = i;
        }
        editMFTabs()->insert(editMFTabs()->find(TabInsert), Tab);
        editMFTabContents()->insert(editMFTabContents()->find(getTabContents(index)), TabContent);
    }
}

void TabPanel::insertTab(const UInt32 TabIndex, const ComponentRefPtr Tab, const ComponentRefPtr TabContent)
{
    Tab->addFocusListener(this);
    pushToChildren(Tab);
    pushToChildren(TabContent);
    editMFTabs()->insert(editMFTabs()->find(getTabs(TabIndex)), Tab); // an incredibly ridiculous function call
    editMFTabContents()->insert(editMFTabContents()->find(getTabContents(TabIndex)), TabContent);
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
    for (UInt32 i=0; i < getMFTabs()->size(); ++i)
    {
        cumMajorAxis += getTabs(i)->getRequestedSize()[AxisIndex];
        if (getTabs(i)->getRequestedSize()[(AxisIndex+1)%2] > largestMinorAxis)
        {
            largestMinorAxis = getTabs(i)->getRequestedSize()[(AxisIndex+1)%2];
        }
    }
    cumMajorAxis += static_cast<Real32>(getMFTabs()->size()) * (TabBorderTopLeftWidth[AxisIndex] + TabBorderBottomRightWidth[AxisIndex]);
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
    for (UInt32 i=0; i < getMFTabs()->size(); ++i)
    {
        offset[AxisIndex] += TabBorderTopLeftWidth[AxisIndex];
        getTabs(i)->setSize(getTabs(i)->getRequestedSize());
        getTabs(i)->setPosition(alignOffset + offset);
        offset[AxisIndex] += getTabs(i)->getSize()[AxisIndex] + TabBorderBottomRightWidth[AxisIndex];
    }

    if(getMFTabContents()->size() > 0 && getSelectedIndex() != -1)
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
        getTabContents(getSelectedIndex())->setSize(ContentsSize);
        getTabContents(getSelectedIndex())->setPosition(offset + ContentBorderTopLeftWidth);
    }
}

void TabPanel::mouseClicked(const MouseEventUnrecPtr e)
{
    bool isContained;
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        isContained = isContainedClipBounds(e->getLocation(), getTabs(i));
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            getTabs(i)->mouseClicked(e);
        }
    }

    isContained = isContainedClipBounds(e->getLocation(), getTabContents(getSelectedIndex()));
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        getTabContents(getSelectedIndex())->mouseClicked(e);
    }

    Component::mouseClicked(e);
}

void TabPanel::mouseEntered(const MouseEventUnrecPtr e)
{
    bool isContained;
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        isContained = getTabs(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            getTabs(i)->mouseDragged(e);
        }
    }

    isContained = getTabContents(getSelectedIndex())->isContained(e->getLocation(), true);
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        getTabContents(getSelectedIndex())->mouseDragged(e);
    }

    Component::mouseEntered(e);
}

void TabPanel::mouseExited(const MouseEventUnrecPtr e)
{
    bool isContained;
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        isContained = getTabs(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            getTabs(i)->mouseDragged(e);
        }
    }

    isContained = getTabContents(getSelectedIndex())->isContained(e->getLocation(), true);
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        getTabContents(getSelectedIndex())->mouseDragged(e);
    }

    Component::mouseExited(e);
}

void TabPanel::mousePressed(const MouseEventUnrecPtr e)
{
    bool isContained;
    for(Int32 i(getMFTabs()->size()-1) ; i>=0 ; --i)
    {   // going backwards through through elements, so only top button is pressed
        isContained = getTabs(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            //Give myself temporary focus
            takeFocus(true);
            if(!getTabs(i)->getType().isDerivedFrom(ComponentContainer::getClassType()))
            {
                getTabs(i)->takeFocus();
            }
            getTabs(i)->mousePressed(e);
            break;
        }
    }
    if(isContained)
    {
        //Remove my temporary focus
        giveFocus(NULL, false);
    }
    else
    {
        //Give myself permanant focus
        takeFocus();
    }

    // now do it for the content tab
    isContained = getTabContents(getSelectedIndex())->isContained(e->getLocation(), true);
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        //Give myself temporary focus
        takeFocus(true);
        if(!getTabContents(getSelectedIndex())->getType().isDerivedFrom(ComponentContainer::getClassType()))
        {
            getTabContents(getSelectedIndex())->takeFocus();
        }
        getTabContents(getSelectedIndex())->mousePressed(e);

        giveFocus(NULL, false);
    }
    else
    {
        //Give myself permanent focus
        takeFocus();
    }

    Component::mousePressed(e);
}

void TabPanel::mouseReleased(const MouseEventUnrecPtr e)
{
    bool isContained;
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        isContained = getTabs(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            getTabs(i)->mouseReleased(e);
        }
    }

    isContained = getTabContents(getSelectedIndex())->isContained(e->getLocation(), true);
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        getTabContents(getSelectedIndex())->mouseReleased(e);
    }

    Component::mouseReleased(e);
}


void TabPanel::mouseMoved(const MouseEventUnrecPtr e)
{
    Component::mouseMoved(e);
    bool isContained;
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        isContained = getTabs(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            getTabs(i)->mouseMoved(e);
        }
    }

    isContained = getTabContents(getSelectedIndex())->isContained(e->getLocation(), true);
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        getTabContents(getSelectedIndex())->mouseMoved(e);
    }

}

void TabPanel::mouseDragged(const MouseEventUnrecPtr e)
{
    bool isContained;
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        isContained = getTabs(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            getTabs(i)->mouseDragged(e);
        }
    }

    isContained = getTabContents(getSelectedIndex())->isContained(e->getLocation(), true);
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        getTabContents(getSelectedIndex())->mouseDragged(e);
    }

    Component::mouseDragged(e);
}

void TabPanel::mouseWheelMoved(const MouseWheelEventUnrecPtr e)
{
    bool isContained;
    for(UInt32 i(0) ; i<getMFTabs()->size() ; ++i)
    {
        isContained = getTabs(i)->isContained(e->getLocation(), true);
        checkMouseEnterExit(e,e->getLocation(),getTabs(i),isContained,e->getViewport());
        if(isContained)
        {
            getTabs(i)->mouseWheelMoved(e);
        }
    }

    isContained = getTabContents(getSelectedIndex())->isContained(e->getLocation(), true);
    checkMouseEnterExit(e,e->getLocation(),getTabContents(getSelectedIndex()),isContained,e->getViewport());
    if(isContained)
    {
        getTabContents(getSelectedIndex())->mouseWheelMoved(e);
    }

    Component::mouseWheelMoved(e);
}

BorderRefPtr TabPanel::getDrawnTabBorder(const UInt32& Index) const
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
        else if(getTabs(Index)->getFocused())
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

LayerRefPtr TabPanel::getDrawnTabBackground(const UInt32& Index) const
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
        else if(getTabs(Index)->getFocused())
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

BorderRefPtr TabPanel::getDrawnContentBorder(void) const
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

LayerRefPtr TabPanel::getDrawnContentBackground(void) const
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

EventConnection TabPanel::addSelectionListener(SelectionListenerPtr listener)
{
    if(getSelectionModel() != NULL)
    {
        return getSelectionModel()->addSelectionListener(listener);
    }
    return EventConnection();
}

void TabPanel::removeSelectionListener(SelectionListenerPtr listener)
{
    if(getSelectionModel() != NULL)
    {
        getSelectionModel()->removeSelectionListener(listener);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void TabPanel::onCreate(const TabPanel * Id)
{
    DefaultSingleSelectionModelUnrecPtr Model(DefaultSingleSelectionModel::create());
    setSelectionModel(Model);
}

void TabPanel::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

TabPanel::TabPanel(void) :
    Inherited(),
    _MouseInTabLastMouse(-1),
    _TabSelectionListener(this)
{
}

TabPanel::TabPanel(const TabPanel &source) :
    Inherited(source),
    _MouseInTabLastMouse(-1),
    _TabSelectionListener(this)
{
}

TabPanel::~TabPanel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TabPanel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if( (whichField & TabsFieldMask) || (whichField & TabContentsFieldMask))
    {
		updateLayout();
	}

    if(whichField & TabPanel::SelectionModelFieldMask && getSelectionModel() != NULL)
    {
        getSelectionModel()->addSelectionListener(&_TabSelectionListener);
    }
}

void TabPanel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TabPanel NI" << std::endl;
}

void TabPanel::TabSelectionListener::selectionChanged(const SelectionEventUnrecPtr e)
{
    _TabPanel->updateLayout();
}

OSG_END_NAMESPACE

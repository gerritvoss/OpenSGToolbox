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

#include "OSGMenuBar.h"
#include "OSGDefaultSingleSelectionModel.h"

#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMenuBarBase.cpp file.
// To modify it, please change the .fcd file (OSGMenuBar.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MenuBar::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MenuBar::updateLayout(void)
{
	//Determine the Max Preferred Height of my MenuItems
	Real32 MaxHeight(0);
	Real32 TotalWidth(0);
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(MaxHeight < getChildren(i)->getPreferredSize().y())
        {
            MaxHeight = getChildren(i)->getPreferredSize().y();
	    }
	    TotalWidth += getChildren(i)->getPreferredSize().x();
	}

    //Set My preferred Size
	Pnt2f TopLeft, BottomRight;
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getBounds(TopLeft, BottomRight);
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	Vec2f InsetSize( (BottomRight-TopLeft) - (InsetsBottomRight-InsetsTopLeft) );

    Vec2f NewSize( TotalWidth+InsetSize.x(), MaxHeight+InsetSize.y());
    if(getPreferredSize() != NewSize)
    {
        setPreferredSize(NewSize);
    }
    
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
	
	//Now position and size the Items
	Real32 LeftOffset(InsetsTopLeft.x());
    Vec2f Size;
    Pnt2f Pos;
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        Size.setValues(getChildren(i)->getPreferredSize().x(), MaxHeight);
        if(getChildren(i)->getSize() != Size)
        {
            getChildren(i)->setSize(Size);
        }
        Pos.setValues(LeftOffset, InsetsTopLeft.y());
        if(getChildren(i)->getPosition() != Pos)
        {
            getChildren(i)->setPosition(Pos);
        }

        LeftOffset += getChildren(i)->getPreferredSize().x();
    }
}

ComponentContainer* MenuBar::getParentContainer(void) const
{
    return getParentWindow();
}

void MenuBar::updateClipBounds(void)
{
	Pnt2f TopLeft, BottomRight;
	if(getParentWindow() == NULL)
	{
		//If I have no parent container use my bounds
		getBounds(TopLeft, BottomRight);
	}
	else
	{
		//Get the intersection of:
		     //My Bounds
		     //My Parent Containers Clip Bounds
		     //My Parent Containers Inset Bounds
        Pnt2f MyTopLeft,MyBottomRight;
        getBounds(MyTopLeft,MyBottomRight);

		//Update my Parent ComponentContainer's Clip Bounds
		//dynamic_cast<ComponentContainer*>(getParentWindow())->updateClipBounds();

		//Get Parent ComponentContainer's Clip Bounds
		Pnt2f ContainerClipTopLeft, ContainerClipBottomRight;
		dynamic_cast<InternalWindow*>(getParentContainer())->getMenuBarBounds(ContainerClipTopLeft,ContainerClipBottomRight);
		
        //Parent ComponentContainer's Clip Bounds are in the Parent ComponentContainer's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerClipTopLeft -= Vec2f(getPosition());
		ContainerClipBottomRight -= Vec2f(getPosition());

		//Get Parent ComponentContainer's MenuBar Bounds
		Pnt2f ContainerInsetTopLeft, ContainerInsetBottomRight;
		dynamic_cast<InternalWindow*>(getParentContainer())->getMenuBarBounds(ContainerInsetTopLeft, ContainerInsetBottomRight);
		
        //Parent ComponentContainer's Inset Bounds are in the Parent ComponentContainer's Coordinate space
        //We need to convert them to this Components Coordinate space
        ContainerInsetTopLeft -= Vec2f(getPosition());
		ContainerInsetBottomRight -= Vec2f(getPosition());

		//Get the intersection of my bounds with my parent containers clip bounds
		quadIntersection(MyTopLeft,MyBottomRight,
			ContainerClipTopLeft,ContainerClipBottomRight,
			TopLeft, BottomRight);

		quadIntersection(TopLeft,BottomRight,
			ContainerInsetTopLeft,ContainerInsetBottomRight,
			TopLeft, BottomRight);
	}

	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
	setClipTopLeft(TopLeft);
	setClipBottomRight(BottomRight);
}

void MenuBar::addMenu(Menu* const menu)
{
    pushToChildren(menu);
    menu->setTopLevelMenu(true);
    _PopupMenuCanceledConnections[menu] = menu->getInternalPopupMenu()->connectPopupMenuCanceled(boost::bind(&MenuBar::handleMenuArmedPopupMenuCanceled, this, _1));
}

void MenuBar::addMenu(Menu* const menu, const UInt32& Index)
{
    if(Index < getMFChildren()->size())
    {
        insertIntoChildren(Index, menu);
        menu->setTopLevelMenu(true);
        _PopupMenuCanceledConnections[menu] = menu->getInternalPopupMenu()->connectPopupMenuCanceled(boost::bind(&MenuBar::handleMenuArmedPopupMenuCanceled, this, _1));
    }
}

void MenuBar::removeMenu(Menu* const menu)
{
    removeObjFromChildren(menu);
    menu->setTopLevelMenu(false);
    if(_PopupMenuCanceledConnections.find(menu) != _PopupMenuCanceledConnections.end())
    {
        _PopupMenuCanceledConnections[menu].disconnect();
        _PopupMenuCanceledConnections.erase(_PopupMenuCanceledConnections.find(menu));
    }
}

void MenuBar::removeMenu(const UInt32& Index)
{
    if(Index < getMFChildren()->size())
    {
        MenuRefPtr Item(dynamic_cast<Menu*>(getChildren(Index)));
        removeFromChildren(Index);

        Item->setTopLevelMenu(false);
        if(_PopupMenuCanceledConnections.find(Item) != _PopupMenuCanceledConnections.end())
        {
            _PopupMenuCanceledConnections[Item].disconnect();
            _PopupMenuCanceledConnections.erase(_PopupMenuCanceledConnections.find(Item));
        }
    }
}

void MenuBar::mousePressed(MouseEventDetails* const e)
{
    UInt32 i(0);
    while (i<getMFChildren()->size())
    {
        if(getChildren(i)->isContained(e->getLocation(), true))
        {
            getSelectionModel()->setSelectedIndex(i);
            _MouseMovedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseMoved(boost::bind(&MenuBar::handleMenuArmedMouseMoved, this, _1));
            _MouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&MenuBar::handleMenuArmedMouseDragged, this, _1));
            break;
        }
        ++i;
    }
    ComponentContainer::mousePressed(e);
}

void MenuBar::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _SelectionChangedConnection.disconnect();
    _MouseMovedConnection.disconnect();
    _MouseDraggedConnection.disconnect();
    for(std::map<Menu*, boost::signals2::connection>::iterator MapItor(_PopupMenuCanceledConnections.begin()) ;
        MapItor != _PopupMenuCanceledConnections.end();
        ++MapItor)
    {
        MapItor->second.disconnect();
    }
    _PopupMenuCanceledConnections.clear();
    _KeyTypedConnection.disconnect();
}

void MenuBar::setParentWindow(InternalWindow* const parent)
{
    _KeyTypedConnection.disconnect();

    Inherited::setParentWindow(parent);

    if(getParentWindow() != NULL)
    {
        _KeyTypedConnection = getParentWindow()->connectKeyTyped(boost::bind(&MenuBar::handleMenuArmedKeyTyped, this, _1));
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void MenuBar::onCreate(const MenuBar * Id)
{
	Inherited::onCreate(Id);

    DefaultSingleSelectionModelUnrecPtr TheModel(DefaultSingleSelectionModel::create());
    setSelectionModel(TheModel);
}

void MenuBar::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

MenuBar::MenuBar(void) :
    Inherited()
{
}

MenuBar::MenuBar(const MenuBar &source) :
    Inherited(source)
{
}

MenuBar::~MenuBar(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MenuBar::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & SelectionModelFieldMask)
    {
        _SelectionChangedConnection.disconnect();
        if(getSelectionModel() != NULL)
        {
            _SelectionChangedConnection = getSelectionModel()->connectSelectionChanged(boost::bind(&MenuBar::handleMenuArmedSelectionChanged, this, _1));
        }
    }
}

void MenuBar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MenuBar NI" << std::endl;
}

void MenuBar::handleMenuArmedSelectionChanged(SelectionEventDetails* const e)
{
    for(UInt32 i(0) ; i<e->getMFPreviouslySelected()->size() ; ++i)
    {
        if(dynamic_cast<MenuItem*>(getChildren(e->getPreviouslySelected(i)))->getSelected())
        {
            dynamic_cast<MenuItem*>(getChildren(e->getPreviouslySelected(i)))->setSelected(false);
        }
    }

    for(UInt32 i(0) ; i<e->getMFSelected()->size() ; ++i)
    {
        if(!dynamic_cast<MenuItem*>(getChildren(e->getSelected(i)))->getSelected())
        {
            dynamic_cast<MenuItem*>(getChildren(e->getSelected(i)))->setSelected(true);
        }
    }
}

void MenuBar::handleMenuArmedMouseMoved(MouseEventDetails* const e)
{
    UInt32 i(0);
    while (i<getMFChildren()->size())
    {
        if(getChildren(i)->isContained(e->getLocation(), true))
        {
            getSelectionModel()->setSelectedIndex(i);
            break;
        }
        ++i;
    }
}

void MenuBar::handleMenuArmedMouseDragged(MouseEventDetails* const e)
{
    UInt32 i(0);
    while (i<getMFChildren()->size())
    {
        if(getChildren(i)->isContained(e->getLocation(), true))
        {
            getSelectionModel()->setSelectedIndex(i);
            break;
        }
        ++i;
    }
}

void MenuBar::handleMenuArmedPopupMenuCanceled(PopupMenuEventDetails* const e)
{
    _MouseMovedConnection.disconnect();
    _MouseDraggedConnection.disconnect();
    
    getSelectionModel()->clearSelection();
}

void MenuBar::handleMenuArmedKeyTyped(KeyEventDetails* const e)
{
    //UInt32 RelevantModifiers = (e->getModifiers() & KeyEventDetails::KEY_MODIFIER_ALT) |
    //                           (e->getModifiers() & KeyEventDetails::KEY_MODIFIER_CONTROL) |
    //                           (e->getModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT) |
    //                           (e->getModifiers() & KeyEventDetails::KEY_MODIFIER_META);

    if(e->getModifiers() & KeyEventDetails::KEY_MODIFIER_ALT)
    {
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            if(dynamic_cast<MenuItem*>(getChildren(i))->getMnemonicKey() == e->getKey() )
            {
                //std::cout << e->getKeyChar() << std::endl;
            }
        }
    }
}

OSG_END_NAMESPACE

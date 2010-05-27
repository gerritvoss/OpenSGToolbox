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
            //Sneakily set my size
            //setSize(NewSize);
    }
    
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
	
	//Now position and size the Items
	Real32 LeftOffset(InsetsTopLeft.x());
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
            getChildren(i)->setSize(Vec2f(getChildren(i)->getPreferredSize().x(), MaxHeight));
            getChildren(i)->setPosition(Pnt2f(LeftOffset, InsetsTopLeft.y()));

        LeftOffset += getChildren(i)->getPreferredSize().x();
    }
}

void MenuBar::updateClipBounds(void)
{
	Pnt2f TopLeft, BottomRight;
	if(getParentContainer() == NULL)
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
		//dynamic_cast<ComponentContainer*>(getParentContainer())->updateClipBounds();

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

void MenuBar::addMenu(MenuRefPtr Menu)
{
    pushToChildren(Menu);
    Menu->setTopLevelMenu(true);
    Menu->getInternalPopupMenu()->addPopupMenuListener(&_MenuSelectionListener);
}

void MenuBar::addMenu(MenuRefPtr Menu, const UInt32& Index)
{
    if(Index < getMFChildren()->size())
    {
        MFChildrenType::iterator Itor = editMFChildren()->begin();
        for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
        
        editMFChildren()->insert(Itor, Menu);
        Menu->setTopLevelMenu(true);
        Menu->getInternalPopupMenu()->addPopupMenuListener(&_MenuSelectionListener);
    }
}

void MenuBar::removeMenu(MenuRefPtr Menu)
{
    MenuBar::MFChildrenType::iterator FindResult = editMFChildren()->find(Menu);
    if(FindResult != editMFChildren()->end())
    {
        editMFChildren()->erase(FindResult);
        Menu->setTopLevelMenu(false);
        Menu->getInternalPopupMenu()->removePopupMenuListener(&_MenuSelectionListener);
    }
}

void MenuBar::removeMenu(const UInt32& Index)
{
    if(Index < getMFChildren()->size())
    {
        MenuRefPtr Item(dynamic_cast<Menu*>(getChildren(Index)));
        removeFromChildren(Index);

        Item->setTopLevelMenu(false);
        Item->getInternalPopupMenu()->removePopupMenuListener(&_MenuSelectionListener);
    }
}

void MenuBar::mousePressed(const MouseEventUnrecPtr e)
{
    UInt32 i(0);
    while (i<getMFChildren()->size())
    {
        if(getChildren(i)->isContained(e->getLocation(), true))
        {
            getSelectionModel()->setSelectedIndex(i);
            _SelectionMouseEventConnection = getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_MenuSelectionListener);
            break;
        }
        ++i;
    }
    ComponentContainer::mousePressed(e);
}

void MenuBar::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _SelectionMouseEventConnection.disconnect();
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
    Inherited(),
    _MenuSelectionListener(this)
{
}

MenuBar::MenuBar(const MenuBar &source) :
    Inherited(source),
    _MenuSelectionListener(this)
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

    if((whichField & ParentWindowFieldMask) && getParentWindow() != NULL)
    {
        getParentWindow()->addKeyListener(&_MenuSelectionListener);
    }

    if(whichField & SelectionModelFieldMask && getSelectionModel() != NULL)
    {
        getSelectionModel()->addSelectionListener(&_MenuSelectionListener);
    }
}

void MenuBar::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MenuBar NI" << std::endl;
}

void MenuBar::MenuSelectionListener::selectionChanged(const SelectionEventUnrecPtr e)
{
    for(UInt32 i(0) ; i<e->getMFPreviouslySelected()->size() ; ++i)
    {
        if(dynamic_cast<MenuItem*>(_MenuBar->getChildren(e->getPreviouslySelected(i)))->getSelected())
        {
                dynamic_cast<MenuItem*>(_MenuBar->getChildren(e->getPreviouslySelected(i)))->setSelected(false);
        }
    }

    for(UInt32 i(0) ; i<e->getMFSelected()->size() ; ++i)
    {
        if(!dynamic_cast<MenuItem*>(_MenuBar->getChildren(e->getSelected(i)))->getSelected())
        {
                dynamic_cast<MenuItem*>(_MenuBar->getChildren(e->getSelected(i)))->setSelected(true);
        }
    }
}

void MenuBar::MenuSelectionListener::mouseMoved(const MouseEventUnrecPtr e)
{
    UInt32 i(0);
    while (i<_MenuBar->getMFChildren()->size())
    {
        if(_MenuBar->getChildren(i)->isContained(e->getLocation(), true))
        {
            _MenuBar->getSelectionModel()->setSelectedIndex(i);
            break;
        }
        ++i;
    }
}

void MenuBar::MenuSelectionListener::mouseDragged(const MouseEventUnrecPtr e)
{
    UInt32 i(0);
    while (i<_MenuBar->getMFChildren()->size())
    {
        if(_MenuBar->getChildren(i)->isContained(e->getLocation(), true))
        {
            _MenuBar->getSelectionModel()->setSelectedIndex(i);
            break;
        }
        ++i;
    }
}

void MenuBar::MenuSelectionListener::popupMenuCanceled(const PopupMenuEventUnrecPtr e)
{
	if(_MenuBar->getParentWindow()->getDrawingSurface()->getEventProducer() != NULL)
	{
		_MenuBar->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
	}
    
    _MenuBar->getSelectionModel()->clearSelection();
}

void MenuBar::MenuSelectionListener::popupMenuWillBecomeInvisible(const PopupMenuEventUnrecPtr e)
{
    //Do Nothing
}

void MenuBar::MenuSelectionListener::popupMenuWillBecomeVisible(const PopupMenuEventUnrecPtr e)
{
    //Do Nothing
}

void MenuBar::MenuSelectionListener::popupMenuContentsChanged(const PopupMenuEventUnrecPtr e)
{
    //Do Nothing
}

void MenuBar::MenuSelectionListener::keyTyped(const KeyEventUnrecPtr e)
{
    //UInt32 RelevantModifiers = (e->getModifiers() & KeyEvent::KEY_MODIFIER_ALT) |
    //                           (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL) |
    //                           (e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT) |
    //                           (e->getModifiers() & KeyEvent::KEY_MODIFIER_META);

    if(e->getModifiers() & KeyEvent::KEY_MODIFIER_ALT)
    {
        for(UInt32 i(0) ; i<_MenuBar->getMFChildren()->size() ; ++i)
        {
            if(dynamic_cast<MenuItem*>(_MenuBar->getChildren(i))->getMnemonicKey() == e->getKey() )
            {
                //std::cout << e->getKeyChar() << std::endl;
            }
        }
    }
}

OSG_END_NAMESPACE

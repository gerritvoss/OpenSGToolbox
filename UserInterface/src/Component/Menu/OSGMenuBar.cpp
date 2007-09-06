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

#include "OSGMenuBar.h"
#include "OSGDefaultSingleSelectionModel.h"

#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MenuBar
A UI MenuBar. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MenuBar::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void MenuBar::updateLayout(void)
{
	//Determine the Max Preferred Height of my MenuItems
	UInt16 MaxHeight(0);
	UInt16 TotalWidth(0);
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(MaxHeight < getChildren().getValue(i)->getPreferredSize().y())
        {
            MaxHeight = getChildren().getValue(i)->getPreferredSize().y();
	    }
	    TotalWidth += getChildren().getValue(i)->getPreferredSize().x();
	}

    //Set My preferred Size
	Pnt2s TopLeft, BottomRight;
	Pnt2s InsetsTopLeft, InsetsBottomRight;
	getBounds(TopLeft, BottomRight);
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	Vec2s InsetSize( (BottomRight-TopLeft) - (InsetsBottomRight-InsetsTopLeft) );

    Vec2s NewSize( TotalWidth+InsetSize.x(), MaxHeight+InsetSize.y());
    /*if(getPreferredSize() != NewSize ||
       getSize() != NewSize)
    {
        beginEditCP(MenuBarPtr(this), PreferredSizeFieldMask);
            setPreferredSize(NewSize);
            //Sneakily set my size
            setSize(NewSize);
        endEditCP(MenuBarPtr(this), PreferredSizeFieldMask);
    }*/
    
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
	
	//Now position and size the Items
	UInt16 LeftOffset(InsetsTopLeft.x());
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        beginEditCP(getChildren().getValue(i), SizeFieldMask | PositionFieldMask);
            getChildren().getValue(i)->setSize(Vec2s(getChildren().getValue(i)->getPreferredSize().x(), MaxHeight));
            getChildren().getValue(i)->setPosition(Pnt2s(LeftOffset, InsetsTopLeft.y()));
        endEditCP(getChildren().getValue(i), SizeFieldMask | PositionFieldMask);

        LeftOffset += getChildren().getValue(i)->getPreferredSize().x();
    }
}

void MenuBar::addMenu(MenuPtr Menu)
{
    beginEditCP(MenuBarPtr(this), ChildrenFieldMask);
        getChildren().push_back(Menu);
    endEditCP(MenuBarPtr(this), ChildrenFieldMask);
    beginEditCP(Menu, Menu::TopLevelMenuFieldMask);
        Menu->setTopLevelMenu(true);
    endEditCP(Menu, Menu::TopLevelMenuFieldMask);
    Menu->getInternalPopupMenu()->addPopupMenuListener(&_MenuSelectionListener);
}

void MenuBar::addMenu(MenuPtr Menu, const UInt32& Index)
{
    if(Index < getChildren().size())
    {
        MFComponentPtr::iterator Itor;
        for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
        beginEditCP(MenuBarPtr(this), ChildrenFieldMask);
            getChildren().insert(Itor, Menu);
        endEditCP(MenuBarPtr(this), ChildrenFieldMask);
        beginEditCP(Menu, Menu::TopLevelMenuFieldMask);
            Menu->setTopLevelMenu(true);
        endEditCP(Menu, Menu::TopLevelMenuFieldMask);
        Menu->getInternalPopupMenu()->addPopupMenuListener(&_MenuSelectionListener);
    }
}

void MenuBar::removeMenu(MenuPtr Menu)
{
    MFComponentPtr::iterator FindResult = getChildren().find(Menu);
    if(FindResult != getChildren().end())
    {
        beginEditCP(MenuBarPtr(this), ChildrenFieldMask);
            getChildren().erase(FindResult);
        endEditCP(MenuBarPtr(this), ChildrenFieldMask);
        beginEditCP(Menu, Menu::TopLevelMenuFieldMask);
            Menu->setTopLevelMenu(false);
        endEditCP(Menu, Menu::TopLevelMenuFieldMask);
        Menu->getInternalPopupMenu()->removePopupMenuListener(&_MenuSelectionListener);
    }
}

void MenuBar::removeMenu(const UInt32& Index)
{
    if(Index < getChildren().size())
    {
        MFComponentPtr::iterator Itor;
        for(UInt32 i(0) ; i<Index ; ++i){++Itor;}
        beginEditCP(MenuBarPtr(this), ChildrenFieldMask);
            getChildren().erase(Itor);
        endEditCP(MenuBarPtr(this), ChildrenFieldMask);

        beginEditCP((*Itor), Menu::TopLevelMenuFieldMask);
            Menu::Ptr::dcast( (*Itor) )->setTopLevelMenu(false);
        endEditCP((*Itor), Menu::TopLevelMenuFieldMask);
        Menu::Ptr::dcast( (*Itor) )->getInternalPopupMenu()->removePopupMenuListener(&_MenuSelectionListener);
    }
}

void MenuBar::mousePressed(const MouseEvent& e)
{
    UInt32 i(0);
    while (i<getChildren().size())
    {
        if(getChildren().getValue(i)->isContained(e.getLocation(), true))
        {
            _SelectionModel->setSelectedIndex(i);
            getParentFrame()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_MenuSelectionListener);
            break;
        }
        ++i;
    }
    Container::mousePressed(e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MenuBar::MenuBar(void) :
    Inherited(),
    _MenuSelectionListener(MenuBarPtr(this))
{
    _SelectionModel = new DefaultSingleSelectionModel();
    _SelectionModel->addChangeListener(&_MenuSelectionListener);
}

MenuBar::MenuBar(const MenuBar &source) :
    Inherited(source),
    _MenuSelectionListener(MenuBarPtr(this))
{
    _SelectionModel = new DefaultSingleSelectionModel();
    _SelectionModel->addChangeListener(&_MenuSelectionListener);
}

MenuBar::~MenuBar(void)
{
    delete _SelectionModel;
}

/*----------------------------- class specific ----------------------------*/

void MenuBar::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void MenuBar::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MenuBar NI" << std::endl;
}

void MenuBar::MenuSelectionListener::stateChanged(const ChangeEvent& e)
{
    for(UInt32 i(0) ; i<_MenuBar->getChildren().size() ; ++i)
    {
        if(i == _MenuBar->_SelectionModel->getSelectedIndex() &&
           !Menu::Ptr::dcast(_MenuBar->getChildren().getValue(i))->getSelected())
        {
            beginEditCP(_MenuBar->getChildren().getValue(i), Menu::SelectedFieldMask);
                Menu::Ptr::dcast(_MenuBar->getChildren().getValue(i))->setSelected(true);
            endEditCP(_MenuBar->getChildren().getValue(i), Menu::SelectedFieldMask);
        }
        if(i != _MenuBar->_SelectionModel->getSelectedIndex() &&
           Menu::Ptr::dcast(_MenuBar->getChildren().getValue(i))->getSelected())
        {
            beginEditCP(_MenuBar->getChildren().getValue(i), Menu::SelectedFieldMask);
                Menu::Ptr::dcast(_MenuBar->getChildren().getValue(i))->setSelected(false);
            endEditCP(_MenuBar->getChildren().getValue(i), Menu::SelectedFieldMask);
        }
    }
}

void MenuBar::MenuSelectionListener::mouseMoved(const MouseEvent& e)
{
    UInt32 i(0);
    while (i<_MenuBar->getChildren().size())
    {
        if(_MenuBar->getChildren().getValue(i)->isContained(e.getLocation(), true))
        {
            _MenuBar->_SelectionModel->setSelectedIndex(i);
            break;
        }
        ++i;
    }
}

void MenuBar::MenuSelectionListener::mouseDragged(const MouseEvent& e)
{
    UInt32 i(0);
    while (i<_MenuBar->getChildren().size())
    {
        if(_MenuBar->getChildren().getValue(i)->isContained(e.getLocation(), true))
        {
            _MenuBar->_SelectionModel->setSelectedIndex(i);
            break;
        }
        ++i;
    }
}

void MenuBar::MenuSelectionListener::popupMenuCanceled(const PopupMenuEvent& e)
{
    _MenuBar->getParentFrame()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
    _MenuBar->_SelectionModel->clearSelection();
}

void MenuBar::MenuSelectionListener::popupMenuWillBecomeInvisible(const PopupMenuEvent& e)
{
    //Do Nothing
}

void MenuBar::MenuSelectionListener::popupMenuWillBecomeVisible(const PopupMenuEvent& e)
{
    //Do Nothing
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
    static Char8 cvsid_hpp       [] = OSGMENUBARBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMENUBARBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMENUBARFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


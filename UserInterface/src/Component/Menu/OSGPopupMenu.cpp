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
#include <deque>

#include "OSGPopupMenu.h"
#include "Component/Container/OSGContainer.h"
#include "OSGDefaultSingleSelectionModel.h"
#include "Component/Misc/OSGSeparator.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PopupMenu
A UI Menu. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PopupMenu::initMethod (void)
{
}
/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void PopupMenu::updateLayout(void)
{
	//Determine the Max Preferred Width of my MenuItems
	Real32 MaxWidth(0);
	Real32 TotalHeight(0);
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(MaxWidth < getChildren()[i]->getRequestedSize().x())
        {
            MaxWidth = getChildren()[i]->getRequestedSize().x();
	    }
	    TotalHeight += getChildren()[i]->getRequestedSize().y();
		if(i!=0)
		{
			TotalHeight += 1.0f;
		}
	}

    //Set My preferred Size
	Pnt2f TopLeft, BottomRight;
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getBounds(TopLeft, BottomRight);
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	Vec2f InsetSize( (BottomRight-TopLeft) - (InsetsBottomRight-InsetsTopLeft) );
    beginEditCP(PopupMenuPtr(this), PreferredSizeFieldMask);
        setPreferredSize(Vec2f(MaxWidth+InsetSize.x(), TotalHeight+InsetSize.y()));
        //Sneakily set my size
        setSize(getPreferredSize());
    endEditCP(PopupMenuPtr(this), PreferredSizeFieldMask);
    
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);
	
	//Now position and size the Items
	Real32 TopOffset(InsetsTopLeft.y());
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        beginEditCP(getChildren()[i], SizeFieldMask | PositionFieldMask);
            getChildren()[i]->setSize(Vec2f(MaxWidth, getChildren()[i]->getRequestedSize().y()));
            getChildren()[i]->setPosition(Pnt2f(InsetsTopLeft.x(), TopOffset));
        endEditCP(getChildren()[i], SizeFieldMask | PositionFieldMask);

        TopOffset += getChildren()[i]->getRequestedSize().y() +1;
    }
}

void PopupMenu::updateClipBounds(void)
{
	Pnt2f TopLeft, BottomRight;
	
    //Treat myself as having no Parent
	getBounds(TopLeft, BottomRight);

	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
	beginEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
	endEditCP(ComponentPtr(this), Component::ClipTopLeftFieldMask | Component::ClipBottomRightFieldMask);
}

void PopupMenu::addItem(MenuItemPtr Item)
{
    beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
        getChildren().push_back(Item);
    endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
	producePopupMenuContentsChanged(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
}

void PopupMenu::addItem(MenuItemPtr Item, const UInt32& Index)
{
    if(Index < getChildren().size())
    {
        MFComponentPtr::iterator InsertItor(getChildren().begin());
        UInt32 ItemCount(0);
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            if(getChildren()[i]->getType() != Separator::getClassType())
            {
                ++ItemCount;
            }
            if(ItemCount == Index)
            {
                break;
            }
            ++InsertItor;
        }

        if(InsertItor != getChildren().end())
        {
            beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
                getChildren().insert(InsertItor, Item);
            endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
	        producePopupMenuContentsChanged(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
        }
    }
}

void PopupMenu::removeItem(MenuItemPtr Item)
{
    MFComponentPtr::iterator FindResult = getChildren().find(Item);
    if(FindResult != getChildren().end())
    {
        beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
            getChildren().erase(FindResult);
        endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
	    producePopupMenuContentsChanged(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
    }
}

void PopupMenu::removeItem(const UInt32& Index)
{
    if(Index < getChildren().size())
    {
        MFComponentPtr::iterator RemoveItor(getChildren().begin());
        UInt32 ItemCount(0);
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            if(getChildren()[i]->getType() != Separator::getClassType())
            {
                ++ItemCount;
            }
            if(ItemCount == Index)
            {
                break;
            }
            ++RemoveItor;
        }
        if(RemoveItor != getChildren().end())
        {
            beginEditCP(PopupMenuPtr(this), ChildrenFieldMask);
                getChildren().erase(RemoveItor);
            endEditCP(PopupMenuPtr(this), ChildrenFieldMask);
	        producePopupMenuContentsChanged(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
        }
    }
}

void PopupMenu::removeAllItems(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() != Separator::getClassType())
        {
            RemoveIndecies.push_front(i);
        }
    }
    for(UInt32 i(0) ; i<RemoveIndecies.size() ; ++i)
    {
        removeItem(RemoveIndecies[i]);
    }
}


void PopupMenu::addSeparator(void)
{
    SeparatorPtr TheSeparator;
    if(getDefaultSeparator() != NullFC)
    {
        TheSeparator = Separator::Ptr::dcast(getDefaultSeparator()->shallowCopy());
    }
    else
    {
        TheSeparator = Separator::create();
    }
    beginEditCP(TheSeparator, Separator::OrientationFieldMask);
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    endEditCP(TheSeparator, Separator::OrientationFieldMask);

    beginEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
        getChildren().push_back(TheSeparator);
    endEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
}

void PopupMenu::addSeparator(SeparatorPtr TheSeparator)
{
    beginEditCP(TheSeparator, Separator::OrientationFieldMask);
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);
    endEditCP(TheSeparator, Separator::OrientationFieldMask);

    beginEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
        getChildren().push_back(TheSeparator);
    endEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
}

void PopupMenu::removeSeparator(const UInt32&  Index)
{
    if(Index < getNumSeparators())
    {
        MFComponentPtr::iterator RemoveItor(getChildren().begin());
        UInt32 SeparatorCount(0);
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            if(getChildren()[i]->getType() == Separator::getClassType())
            {
                ++SeparatorCount;
            }
            if(SeparatorCount == Index)
            {
                break;
            }
            ++RemoveItor;
        }

        beginEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
            getChildren().erase(RemoveItor);
        endEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
    }
}

void PopupMenu::removeSeparator(SeparatorPtr TheSeparator)
{
    MFComponentPtr::iterator RemoveItor(getChildren().find(TheSeparator));
    if(RemoveItor != getChildren().end())
    {
        beginEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
            getChildren().erase(RemoveItor);
        endEditCP(PopupMenuPtr(this), PopupMenu::ChildrenFieldMask);
    }
}

void PopupMenu::removeAllSeparators(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() == Separator::getClassType())
        {
            RemoveIndecies.push_front(i);
        }
    }
    for(UInt32 i(0) ; i<RemoveIndecies.size() ; ++i)
    {
        removeSeparator(RemoveIndecies[i]);
    }
}

UInt32 PopupMenu::getNumSeparators(void) const
{
    UInt32 NumSeparators(0);
    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() == Separator::getClassType())
        {
            ++NumSeparators;
        }
    }
    return NumSeparators;
}

void PopupMenu::updateSeparatorSizes(void)
{
    Pnt2f InsideInsetsTopLeft, InsideInsetsBottomRight;
    getInsideInsetsBounds(InsideInsetsTopLeft, InsideInsetsBottomRight);
    Vec2f InsideInsetsSize(InsideInsetsBottomRight - InsideInsetsTopLeft);

    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        if(getChildren()[i]->getType() == Separator::getClassType())
        {
            beginEditCP(getChildren()[i], Separator::PreferredSizeFieldMask);
                Separator::Ptr::dcast(getChildren()[i])->setPreferredSize(Vec2f(InsideInsetsSize.x(), getChildren()[i]->getRequestedSize().y()));
            endEditCP(getChildren()[i], Separator::PreferredSizeFieldMask);
        }
    }
}
void PopupMenu::mouseMoved(const MouseEvent& e)
{
    UInt32 i(0);
    while (i<getChildren().size() && !getChildren()[i]->isContained(e.getLocation(), true))
    {
        ++i;
    }
	
	if(i<getChildren().size() && _SelectionModel->getSelectedIndex() != i)
	{
        if(_SelectionModel->getSelectedIndex() != i)
        {
		    _SelectionModel->setSelectedIndex(i);
        }
	}

    Container::mouseMoved(e);
}

void PopupMenu::mouseDragged(const MouseEvent& e)
{
    UInt32 i(0);
    while (i<getChildren().size() && !getChildren()[i]->isContained(e.getLocation(), true))
    {
        ++i;
    }
	
	if(i<getChildren().size() && _SelectionModel->getSelectedIndex() != i)
	{
		_SelectionModel->setSelectedIndex(i);
	}
    Container::mouseDragged(e);
}

void PopupMenu::removePopupMenuListener(PopupMenuListenerPtr Listener)
{
   PopupMenuListenerSetItor EraseIter(_PopupMenuListeners.find(Listener));
   if(EraseIter != _PopupMenuListeners.end())
   {
      _PopupMenuListeners.erase(EraseIter);
   }
}

void PopupMenu::cancel(void)
{
    if(getVisible())
    {
        beginEditCP(PopupMenuPtr(this), VisibleFieldMask);
            setVisible(false);
        endEditCP(PopupMenuPtr(this), VisibleFieldMask);
        producePopupMenuCanceled(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
    }
}

void PopupMenu::clearSelection(void)
{
    _SelectionModel->clearSelection();
}

void PopupMenu::setSelection(const Int32& Index)
{
	if(Index >= 0 && Index < getNumItems())
	{
		_SelectionModel->setSelectedIndex(Index);
	}
	else
	{
		clearSelection();
	}
}


MenuItemPtr PopupMenu::getItem(const UInt32& Index)
{
    if(Index < getChildren().size())
    {
        MFComponentPtr::iterator FindItor(getChildren().begin());
        UInt32 ItemCount(0);
        for(UInt32 i(0) ; i<getChildren().size() ; ++i)
        {
            if(getChildren()[i]->getType() != Separator::getClassType())
            {
                ++ItemCount;
            }
            if(ItemCount == Index)
            {
                break;
            }
            ++FindItor;
        }
        if(FindItor != getChildren().end())
        {
            return MenuItem::Ptr::dcast(*FindItor);
        }
    }
    return NullFC;
}

UInt32 PopupMenu::getNumItems(void) const
{
    return getChildren().size() - getNumSeparators();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PopupMenu::PopupMenu(void) :
    Inherited(),
    _MenuSelectionListener(PopupMenuPtr(this))
{
    _SelectionModel = new DefaultSingleSelectionModel();
    _SelectionModel->addChangeListener(&_MenuSelectionListener);
}

PopupMenu::PopupMenu(const PopupMenu &source) :
    Inherited(source),
    _MenuSelectionListener(PopupMenuPtr(this))
{
    _SelectionModel = new DefaultSingleSelectionModel();
    _SelectionModel->addChangeListener(&_MenuSelectionListener);
}

PopupMenu::~PopupMenu(void)
{
    delete _SelectionModel;
}

void  PopupMenu::producePopupMenuWillBecomeVisible(const PopupMenuEvent& e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuWillBecomeVisible(e);
    }
}

void  PopupMenu::producePopupMenuWillBecomeInvisible(const PopupMenuEvent& e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuWillBecomeInvisible(e);
    }
}

void  PopupMenu::producePopupMenuCanceled(const PopupMenuEvent& e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuCanceled(e);
    }
}
    
void PopupMenu::producePopupMenuContentsChanged(const PopupMenuEvent& e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuContentsChanged(e);
    }
}
/*----------------------------- class specific ----------------------------*/

void PopupMenu::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & VisibleFieldMask)
    {
        if(getVisible())
        {
            producePopupMenuWillBecomeVisible(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
        }
        else
        {
            producePopupMenuWillBecomeInvisible(PopupMenuEvent(PopupMenuPtr(this), getSystemTime()));
            _SelectionModel->clearSelection();
            removeMousePresenceOnComponents();
        }
    }

    if(whichField & SizeFieldMask)
    {
        updateSeparatorSizes();
    }
}

void PopupMenu::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PopupMenu NI" << std::endl;
}

void PopupMenu::MenuSelectionListener::stateChanged(const ChangeEvent& e)
{
    for(UInt32 i(0) ; i<_PopupMenu->getChildren().size() ; ++i)
    {
        if(i == _PopupMenu->_SelectionModel->getSelectedIndex() &&
            _PopupMenu->getChildren()[i]->getType().isDerivedFrom(MenuItem::getClassType()) &&
           !MenuItem::Ptr::dcast(_PopupMenu->getChildren()[i])->getSelected())
        {
            beginEditCP(_PopupMenu->getChildren()[i], MenuItem::SelectedFieldMask);
                MenuItem::Ptr::dcast(_PopupMenu->getChildren()[i])->setSelected(true);
            endEditCP(_PopupMenu->getChildren()[i], MenuItem::SelectedFieldMask);
        }
        if(i != _PopupMenu->_SelectionModel->getSelectedIndex() &&
            _PopupMenu->getChildren()[i]->getType().isDerivedFrom(MenuItem::getClassType()) &&
           MenuItem::Ptr::dcast(_PopupMenu->getChildren()[i])->getSelected())
        {
            beginEditCP(_PopupMenu->getChildren()[i], MenuItem::SelectedFieldMask);
                MenuItem::Ptr::dcast(_PopupMenu->getChildren()[i])->setSelected(false);
            endEditCP(_PopupMenu->getChildren()[i], MenuItem::SelectedFieldMask);
        }
    }
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
    static Char8 cvsid_hpp       [] = OSGPOPUPMENUBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPOPUPMENUBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPOPUPMENUFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


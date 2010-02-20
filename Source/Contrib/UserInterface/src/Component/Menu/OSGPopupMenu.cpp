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

#include "OSGPopupMenu.h"
#include <deque>

#include "OSGPopupMenu.h"
#include "OSGComponentContainer.h"
#include "OSGDefaultSingleSelectionModel.h"
#include "OSGSeparator.h"
#include "OSGSingleSelectionModel.h"
#include "OSGMenuItem.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPopupMenuBase.cpp file.
// To modify it, please change the .fcd file (OSGPopupMenu.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PopupMenu::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection PopupMenu::addPopupMenuListener(PopupMenuListenerPtr Listener)
{
   _PopupMenuListeners.insert(Listener);
   return EventConnection(
       boost::bind(&PopupMenu::isPopupMenuListenerAttached, this, Listener),
       boost::bind(&PopupMenu::removePopupMenuListener, this, Listener));
}

void PopupMenu::updateLayout(void)
{
    //Determine the Max Preferred Width of my MenuItems
    Real32 MaxWidth(0);
    Real32 TotalHeight(0);
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(MaxWidth < getChildren(i)->getRequestedSize().x())
        {
            MaxWidth = getChildren(i)->getRequestedSize().x();
        }
        TotalHeight += getChildren(i)->getRequestedSize().y();
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
    setPreferredSize(Vec2f(MaxWidth+InsetSize.x(), TotalHeight+InsetSize.y()));

    //Sneakily set my size
    _sfSize.setValue(getPreferredSize());

    getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    //Now position and size the Items
    Real32 TopOffset(InsetsTopLeft.y());
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        getChildren(i)->setSize(Vec2f(MaxWidth, getChildren(i)->getRequestedSize().y()));
        getChildren(i)->setPosition(Pnt2f(InsetsTopLeft.x(), TopOffset));

        TopOffset += getChildren(i)->getRequestedSize().y() +1;
    }
}

void PopupMenu::updateClipBounds(void)
{
	Pnt2f TopLeft, BottomRight;
	
    //Treat myself as having no Parent
	getBounds(TopLeft, BottomRight);

	//The Clip Bounds calculated are in my Parent Containers coordinate space
	//Translate these bounds into my own coordinate space
		setClipTopLeft(TopLeft);
		setClipBottomRight(BottomRight);
}

void PopupMenu::addItem(MenuItemRefPtr Item)
{
    pushToChildren(Item);
	producePopupMenuContentsChanged(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
}

void PopupMenu::addItem(MenuItemRefPtr Item, const UInt32& Index)
{
    if(Index < getMFChildren()->size())
    {
        MFChildrenType::iterator InsertItor(editMFChildren()->begin());
        UInt32 ItemCount(0);
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            if(getChildren(i)->getType() != Separator::getClassType())
            {
                ++ItemCount;
            }
            if(ItemCount == Index)
            {
                break;
            }
            ++InsertItor;
        }

        if(InsertItor != editMFChildren()->end())
        {
                editMFChildren()->insert(InsertItor, Item);
	        producePopupMenuContentsChanged(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
        }
    }
}

void PopupMenu::removeItem(MenuItemRefPtr Item)
{
    MFChildrenType::iterator FindResult = editMFChildren()->find(Item);
    if(FindResult != editMFChildren()->end())
    {
            editMFChildren()->erase(FindResult);
	    producePopupMenuContentsChanged(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
    }
}

void PopupMenu::removeItem(const UInt32& Index)
{
    if(Index < getMFChildren()->size())
    {
        MFChildrenType::iterator RemoveItor(editMFChildren()->begin());
        UInt32 ItemCount(0);
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            if(getChildren(i)->getType() != Separator::getClassType())
            {
                ++ItemCount;
            }
            if(ItemCount == Index)
            {
                break;
            }
            ++RemoveItor;
        }
        if(RemoveItor != editMFChildren()->end())
        {
                editMFChildren()->erase(RemoveItor);
	        producePopupMenuContentsChanged(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
        }
    }
}

void PopupMenu::removeAllItems(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() != Separator::getClassType())
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
    SeparatorRefPtr TheSeparator;
    if(getDefaultSeparator() != NULL)
    {
        FieldContainerUnrecPtr TheSeperator(getDefaultSeparator()->shallowCopy());
        TheSeparator = dynamic_pointer_cast<Separator>(TheSeperator);
    }
    else
    {
        TheSeparator = Separator::create();
    }
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);

        pushToChildren(TheSeparator);
}

void PopupMenu::addSeparator(SeparatorRefPtr TheSeparator)
{
        TheSeparator->setOrientation(Separator::HORIZONTAL_ORIENTATION);

        pushToChildren(TheSeparator);
}

void PopupMenu::removeSeparator(const UInt32&  Index)
{
    if(Index < getNumSeparators())
    {
        MFChildrenType::iterator RemoveItor(editMFChildren()->begin());
        UInt32 SeparatorCount(0);
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            if(getChildren(i)->getType() == Separator::getClassType())
            {
                ++SeparatorCount;
            }
            if(SeparatorCount == Index)
            {
                break;
            }
            ++RemoveItor;
        }

            editMFChildren()->erase(RemoveItor);
    }
}

void PopupMenu::removeSeparator(SeparatorRefPtr TheSeparator)
{
    MFChildrenType::iterator RemoveItor(editMFChildren()->find(TheSeparator));
    if(RemoveItor != editMFChildren()->end())
    {
            editMFChildren()->erase(RemoveItor);
    }
}

void PopupMenu::removeAllSeparators(void)
{
    std::deque<UInt32> RemoveIndecies;
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() == Separator::getClassType())
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
    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        if(getChildren(i)->getType() == Separator::getClassType())
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

    for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
    {
        Vec2f NewSize(Vec2f(InsideInsetsSize.x(), getChildren(i)->getRequestedSize().y()));
        if(getChildren(i)->getType() == Separator::getClassType() &&
           dynamic_cast<Separator*>(getChildren(i))->getPreferredSize() != NewSize)
        {
            dynamic_cast<Separator*>(getChildren(i))->setPreferredSize(NewSize);
        }
    }
}
void PopupMenu::mouseMoved(const MouseEventUnrecPtr e)
{
    UInt32 i(0);
    while (i<getMFChildren()->size() && !getChildren(i)->isContained(e->getLocation(), true))
    {
        ++i;
    }
	
	if(i<getMFChildren()->size() && getSelectionModel()->getSelectedIndex() != i)
	{
        if(getSelectionModel()->getSelectedIndex() != i)
        {
		    getSelectionModel()->setSelectedIndex(i);
        }
	}

    ComponentContainer::mouseMoved(e);
}

void PopupMenu::mouseDragged(const MouseEventUnrecPtr e)
{
    UInt32 i(0);
    while (i<getMFChildren()->size() && !getChildren(i)->isContained(e->getLocation(), true))
    {
        ++i;
    }
	
	if(i<getMFChildren()->size() && getSelectionModel()->getSelectedIndex() != i)
	{
		getSelectionModel()->setSelectedIndex(i);
	}
    ComponentContainer::mouseDragged(e);
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
        clearSelection();
            setVisible(false);
        producePopupMenuCanceled(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
    }
}

void PopupMenu::clearSelection(void)
{
    if(getSelectionModel() != NULL)
    {
        getSelectionModel()->clearSelection();
    }
}

void PopupMenu::setSelection(const Int32& Index)
{
	if(Index >= 0 && Index < getNumItems())
	{
        if(getSelectionModel() != NULL)
        {
		    getSelectionModel()->setSelectedIndex(Index);
        }
	}
	else
	{
		clearSelection();
	}
}


MenuItem* PopupMenu::getItem(const UInt32& Index)
{
    if(Index < getMFChildren()->size())
    {
        UInt32 ItemCount(0);
        for(UInt32 i(0) ; i<getMFChildren()->size() ; ++i)
        {
            if(getChildren(i)->getType() != Separator::getClassType())
            {
                if(ItemCount == Index)
                {
                    break;
                }
                ++ItemCount;
            }
        }
        if(ItemCount < getMFChildren()->size())
        {
            return dynamic_cast<MenuItem*>(getChildren(ItemCount));
        }
    }
    return NULL;
}

UInt32 PopupMenu::getNumItems(void) const
{
    return getMFChildren()->size() - getNumSeparators();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void  PopupMenu::producePopupMenuWillBecomeVisible(const PopupMenuEventUnrecPtr e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuWillBecomeVisible(e);
    }
    _Producer.produceEvent(PopupMenuWillBecomeVisibleMethodId,e);
}

void  PopupMenu::producePopupMenuWillBecomeInvisible(const PopupMenuEventUnrecPtr e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuWillBecomeInvisible(e);
    }
    _Producer.produceEvent(PopupMenuWillBecomeInvisibleMethodId,e);
}

void  PopupMenu::producePopupMenuCanceled(const PopupMenuEventUnrecPtr e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuCanceled(e);
    }
    _Producer.produceEvent(PopupMenuCanceledMethodId,e);
}
    
void PopupMenu::producePopupMenuContentsChanged(const PopupMenuEventUnrecPtr e)
{
	PopupMenuListenerSet ListenerSet(_PopupMenuListeners);
    for(PopupMenuListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->popupMenuContentsChanged(e);
    }
    _Producer.produceEvent(PopupMenuContentsChangedMethodId,e);
}

void PopupMenu::onCreate(const PopupMenu * Id)
{
    DefaultSingleSelectionModelUnrecPtr TheModel(DefaultSingleSelectionModel::create());
    setSelectionModel(TheModel);
}

void PopupMenu::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

PopupMenu::PopupMenu(void) :
    Inherited(),
    _MenuSelectionListener(this)
{
}

PopupMenu::PopupMenu(const PopupMenu &source) :
    Inherited(source),
    _MenuSelectionListener(this)
{
}

PopupMenu::~PopupMenu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PopupMenu::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & VisibleFieldMask)
    {
        if(getVisible())
        {
            producePopupMenuWillBecomeVisible(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
        }
        else
        {
            producePopupMenuWillBecomeInvisible(PopupMenuEvent::create(PopupMenuRefPtr(this), getSystemTime()));
            if(getSelectionModel() != NULL)
            {
                getSelectionModel()->clearSelection();
            }
            removeMousePresenceOnComponents();
        }
    }

    if(whichField & SizeFieldMask)
    {
        updateSeparatorSizes();
    }

    if(whichField & SelectionModelFieldMask && getSelectionModel() != NULL)
    {
        getSelectionModel()->addSelectionListener(&_MenuSelectionListener);
    }
}

void PopupMenu::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PopupMenu NI" << std::endl;
}

void PopupMenu::MenuSelectionListener::selectionChanged(const SelectionEventUnrecPtr e)
{
    for(UInt32 i(0) ; i<e->getMFPreviouslySelected()->size() ; ++i)
    {
        if(_PopupMenu->getChildren(e->getPreviouslySelected(i))->getType().isDerivedFrom(MenuItem::getClassType()) &&
           dynamic_cast<MenuItem*>(_PopupMenu->getChildren(e->getPreviouslySelected(i)))->getSelected())
        {
                dynamic_cast<MenuItem*>(_PopupMenu->getChildren(e->getPreviouslySelected(i)))->setSelected(false);
        }
    }

    for(UInt32 i(0) ; i<e->getMFSelected()->size() ; ++i)
    {
        if(_PopupMenu->getChildren(e->getSelected(i))->getType().isDerivedFrom(MenuItem::getClassType()) &&
           !dynamic_cast<MenuItem*>(_PopupMenu->getChildren(e->getSelected(i)))->getSelected())
        {
                dynamic_cast<MenuItem*>(_PopupMenu->getChildren(e->getSelected(i)))->setSelected(true);
        }
    }
}

OSG_END_NAMESPACE

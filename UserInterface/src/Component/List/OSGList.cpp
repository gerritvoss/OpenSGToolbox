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

#include "OSGList.h"
#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::List
A UI List. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void List::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr List::getComponentAtPoint(const MouseEvent& e)
{
    Pnt2s PointInComponent(ViewportToComponent(e.getLocation(), ListPtr(this), e.getViewport()));
    UInt16 OrientationAxisIndex;
    if(getCellLayout() == VERTICAL_ALIGNMENT)
    {
        OrientationAxisIndex = 1;
    }
    else
    {
        OrientationAxisIndex = 0;
    }

	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
    
    UInt32 CumulativeDistance(BorderTopLeft[OrientationAxisIndex]);

    if(PointInComponent[OrientationAxisIndex] <= CumulativeDistance)
    {
        return NullFC;
    }

    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        CumulativeDistance += getChildren()[i]->getSize()[OrientationAxisIndex];
        if(PointInComponent[OrientationAxisIndex] <= CumulativeDistance)
        {
            return getChildren()[i];
        }
    }

    return NullFC;
}

SharedFieldPtr List::getValueAtPoint(const MouseEvent& e)
{
    Pnt2s PointInComponent(ViewportToComponent(e.getLocation(), ListPtr(this), e.getViewport()));

    UInt16 OrientationAxisIndex;
    if(getCellLayout() == VERTICAL_ALIGNMENT)
    {
        OrientationAxisIndex = 1;
    }
    else
    {
        OrientationAxisIndex = 0;
    }

	Pnt2s BorderTopLeft, BorderBottomRight;
	getInsideInsetsBounds(BorderTopLeft, BorderBottomRight);
    
    UInt32 CumulativeDistance(BorderTopLeft[OrientationAxisIndex]);

    if(PointInComponent[OrientationAxisIndex] <= CumulativeDistance)
    {
        return SharedFieldPtr();
    }

    for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
        CumulativeDistance += getChildren()[i]->getSize()[OrientationAxisIndex];
        if(PointInComponent[OrientationAxisIndex] <= CumulativeDistance)
        {
            return _Model->getElementAt(i);
        }
    }

    return SharedFieldPtr();
}

void List::updateItem(const UInt32& index)
{
	//Transfer focus, enabled, Listeners
	ComponentPtr PrevComponent = getChildren().getValue(index);
	getChildren().getValue(index)->removeFocusListener(this);
	getChildren().setValue(
				getCellRenderer()->getListCellRendererComponent(ListPtr(this),getModel()->getElementAt(index),index,getSelectionModel()->isSelectedIndex(index),PrevComponent->getFocused())
				,index);
	if(PrevComponent->getFocused())
	{
		//getChildren().getValue(index)->takeFocus();
		getParentFrame()->setFocusedComponent(getChildren().getValue(index));
	}
	getChildren().getValue(index)->addFocusListener(this);
	getChildren().getValue(index)->setFocused(PrevComponent->getFocused());
	getChildren().getValue(index)->setPosition(PrevComponent->getPosition());
	getChildren().getValue(index)->setSize(PrevComponent->getSize());
	getChildren().getValue(index)->setParentContainer(PrevComponent->getParentContainer());
	getChildren().getValue(index)->setParentFrame(PrevComponent->getParentFrame());
	getChildren().getValue(index)->updateClipBounds();
}

void List::selectionChanged(const ListSelectionEvent& e)
{
	beginEditCP(ListPtr(this), ChildrenFieldMask);
		for(UInt32 i(e.getFirstIndex()) ; i<=e.getLastIndex() ; ++i)
		{
			updateItem(i);
		}
	endEditCP(ListPtr(this), ChildrenFieldMask);
}

void List::focusGained(const FocusEvent& e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e.getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren().getValue(index))
			{
				break;
			}
		}
		updateItem(index);
	}
}

void List::focusLost(const FocusEvent& e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e.getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren().getValue(index))
			{
				break;
			}
		}
		updateItem(index);
	}
}

void List::mousePressed(const MouseEvent& e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren().getValue(i)->isContained(e.getLocation(), true);
		checkMouseEnterExit(e,e.getLocation(),getChildren().getValue(i),isContained,e.getViewport());
		if(isContained)
		{
			//Give myself temporary focus
			takeFocus(true);
			if(!getChildren().getValue(i)->getType().isDerivedFrom(Container::getClassType()))
			{
				getChildren().getValue(i)->takeFocus();
				if(getParentFrame() != NullFC &&
				   getParentFrame()->getDrawingSurface() != NullFC &&
				   getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
				{
					if(getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
					{
						getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionIndex(), i);
					}
					else if(getParentFrame()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
					{
						getSelectionModel()->removeSelectionInterval(i,i);// this toggles the interval
					}
					else
					{
						getSelectionModel()->setSelectionInterval(i,i);
					}
				}
			}
			getChildren().getValue(i)->mousePressed(e);
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
		//Give myself permanent focus
		takeFocus();
	}
	Component::mousePressed(e);
}

void List::keyTyped(const KeyEvent& e)
{
	bool noFocus = true;
	if (e.getKey() == KeyEvent::KEY_UP || 
        e.getKey() == KeyEvent::KEY_DOWN || 
        e.getKey() == KeyEvent::KEY_RIGHT || 
        e.getKey() == KeyEvent::KEY_LEFT || 
        e.getKey() == KeyEvent::KEY_ENTER)
	{
		for(Int32 i(getChildren().size()-1) ; i>=0 && noFocus; --i)
		{
			if (getChildren().getValue(i)->getFocused())
			{
				noFocus = false; // this exits the loop
				UInt32 index(0);
                bool UpdateSelectionIndex(false);
			    if ( (getCellLayout() == VERTICAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_UP) ||
                    (getCellLayout() == HORIZONTAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_LEFT))
			    {
                    index = (i-1+getChildren().size()) % getChildren().size();
                    UpdateSelectionIndex = true;
			    }
			    else if ((getCellLayout() == VERTICAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_DOWN) ||
                    (getCellLayout() == HORIZONTAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_RIGHT))
			    {
                    index = (i+1) % getChildren().size();
                    UpdateSelectionIndex = true;
			    }
                else if(e.getKey() == KeyEvent::KEY_ENTER)
                {
					if (e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
					{
						getSelectionModel()->removeSelectionInterval(i,i);// this toggles the interval
					}
					else
					{
						getSelectionModel()->setSelectionInterval(i, i);
					}
                }

                if(UpdateSelectionIndex)
                {
					getChildren().getValue(index)->takeFocus();
					getSelectionModel()->setLeadSelectionIndex(index);
					if (e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
					{
						getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionIndex(), index);
					}
					else
					{
						getSelectionModel()->setAnchorSelectionIndex(index);
					}
                }
			}
		}	
		if (noFocus)
		{
			UInt32 index(0);
			if ( (getCellLayout() == VERTICAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_UP) ||
                (getCellLayout() == HORIZONTAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_LEFT))
			{
				index = getChildren().size() - 1;
				getChildren().getValue(getChildren().size() - 1)->takeFocus();
			}
			else if ((getCellLayout() == VERTICAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_DOWN) ||
                (getCellLayout() == HORIZONTAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_RIGHT))
			{
				getChildren().getValue(0)->takeFocus();
			}
		}
	}
	Component::keyTyped(e);
}

void List::contentsChanged(ListDataEvent e)
{
	if(getModel() != NULL)
	{
		if(getModel()->getSize() != getChildren().size())
		{
			beginEditCP(ListPtr(this), ChildrenFieldMask);
				for(UInt32 i(e.getIndex0()) ; i<getModel()->getSize() && i<=e.getIndex1() ; ++i )
				{
		            updateItem(i);
				}
			endEditCP(ListPtr(this), ChildrenFieldMask);
		}
		Pnt2s Position(0,0);
		for(UInt32 i(0) ; i<getModel()->getSize() && i<=e.getIndex1() ; ++i )
		{
			beginEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);
			   getChildren().getValue(i)->setPosition(Position);
               if(getCellLayout() == VERTICAL_ALIGNMENT)
               {
			      getChildren().getValue(i)->setSize( Vec2s(getSize().x(), getCellMajorAxisLength()) );
               }
               else
               {
                  getChildren().getValue(i)->setSize( Vec2s(getCellMajorAxisLength(), getSize().y()) );
               }
			endEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);

            if(getCellLayout() == VERTICAL_ALIGNMENT)
            {
			    Position[1] += getChildren().getValue(i)->getSize()[1];
            }
            else
            {
			    Position[0] += getChildren().getValue(i)->getSize()[0];
            }
		}
	}
}

void List::intervalAdded(ListDataEvent e)
{
	//TODO: Implement
	updateLayout();
}

void List::intervalRemoved(ListDataEvent e)
{
	//TODO: Implement
	updateLayout();
}

void List::setModel(ListModelPtr Model)
{
	beginEditCP(ListPtr(this), ChildrenFieldMask);
		getChildren().clear();
	endEditCP(ListPtr(this), ChildrenFieldMask);
	//Should through a ListDataEvent of removeInterval

	if(_Model != NULL)
	{
		_Model->removeListDataListener(this);
	}

	_Model = Model;

	if(_Model != NULL)
	{
		_Model->addListDataListener(this);
	}
}


void List::setSelectionModel(ListSelectionModelPtr SelectionModel)
{
	if(_SelectionModel != NULL)
	{
		_SelectionModel->removeListSelectionListener(this);
	}
   _SelectionModel = SelectionModel;
   
	if(_SelectionModel != NULL)
	{
		_SelectionModel->addListSelectionListener(this);
	}
}

void List::updateLayout(void)
{
    //Update Layout
	if(getModel() != NULL)
	{
		if(getModel()->getSize() != getChildren().size())
		{
			beginEditCP(ListPtr(this), ChildrenFieldMask);
				for(UInt32 i(0) ; i<getModel()->getSize() ; ++i )
				{
					getChildren().addValue(getCellRenderer()->getListCellRendererComponent(ListPtr(this),getModel()->getElementAt(i),i,getSelectionModel()->isSelectedIndex(i),false));
					getChildren().getValue(i)->addFocusListener(this);
				}
			endEditCP(ListPtr(this), ChildrenFieldMask);
		}
		Pnt2s Position(0,0);
		for(UInt32 i(0) ; i<getChildren().size() ; ++i )
		{
			beginEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);
			   getChildren().getValue(i)->setPosition(Position);
               if(getCellLayout() == VERTICAL_ALIGNMENT)
               {
			      getChildren().getValue(i)->setSize( Vec2s(getSize().x(), getCellMajorAxisLength()) );
               }
               else
               {
                  getChildren().getValue(i)->setSize( Vec2s(getCellMajorAxisLength(), getSize().y()) );
               }
			endEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);

            if(getCellLayout() == VERTICAL_ALIGNMENT)
            {
			    Position[1] += getChildren().getValue(i)->getSize()[1];
            }
            else
            {
			    Position[0] += getChildren().getValue(i)->getSize()[0];
            }
		}
	}
}

Vec2s List::getPreferredScrollableViewportSize(void)
{
    return getPreferredSize();
}

Int32 List::getScrollableBlockIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    
    return direction * (VisibleRectBottomRight[MajorAxis] - VisibleRectTopLeft[MajorAxis]);
}

bool List::getScrollableTracksViewportHeight(void)
{
    return getCellLayout() != VERTICAL_ALIGNMENT;
}

bool List::getScrollableTracksViewportWidth(void)
{
    return getCellLayout() == VERTICAL_ALIGNMENT;
}

Int32 List::getScrollableUnitIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    if(orientation == getCellLayout())
    {
        return getCellMajorAxisLength();
    }
    else
    {
        return Container::getScrollableUnitIncrement(VisibleRectTopLeft, VisibleRectBottomRight, orientation, direction);
    }
    
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

List::List(void) :
    Inherited(),
		_Model(NULL),
		_CellRenderer(NULL),
		_SelectionModel()
{
}

List::List(const List &source) :
    Inherited(source),
		_Model(source._Model),
		_CellRenderer(source._CellRenderer),
		_SelectionModel(source._SelectionModel)
{
}

List::~List(void)
{
}

/*----------------------------- class specific ----------------------------*/

void List::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & ChildrenFieldMask) &&
        getChildren().size() > 0)
    {
        beginEditCP(ListPtr(this), PreferredSizeFieldMask);
            if(getCellLayout() == VERTICAL_ALIGNMENT)
            {
                setPreferredSize(Vec2s(getChildren().front()->getSize().x(), getCellMajorAxisLength()*getChildren().size()));
            }
            else
            {
                setPreferredSize(Vec2s(getCellMajorAxisLength()*getChildren().size(), getChildren().front()->getSize().y()));
            }
        endEditCP(ListPtr(this), PreferredSizeFieldMask);
    }
}

void List::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump List NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLISTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLISTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLISTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


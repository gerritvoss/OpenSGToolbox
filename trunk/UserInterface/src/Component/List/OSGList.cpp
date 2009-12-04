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
#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "Util/OSGUIDrawUtils.h"
#include "Component/List/ComponentGenerators/OSGListComponentGenerator.h"
#include "Component/List/Models/OSGListModel.h"
#include "Component/Scroll/OSGScrollBar.h"

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

ComponentPtr List::getComponentAtPoint(const MouseEventPtr e)
{
    Pnt2f PointInComponent(ViewportToComponent(e->getLocation(), ListPtr(this), e->getViewport()));

	Int32 Index(getIndexForLocation(PointInComponent));

	if(Index >= _TopDrawnIndex && Index <= _BottomDrawnIndex)
	{
		return getChildren()[getDrawnIndexFromListIndex(Index)];
	}
	else
	{
		return NullFC;
	}
}

boost::any List::getValueAtPoint(const MouseEventPtr e)
{
    Pnt2f PointInComponent(ViewportToComponent(e->getLocation(), ListPtr(this), e->getViewport()));

	Int32 Index(getIndexForLocation(PointInComponent));
	if(Index > 0 && Index < getModel()->getSize())
	{
		return getModel()->getElementAt(Index);
	}
	else
	{
        return boost::any();
	}

}

void List::updateItem(const UInt32& Index)
{
	if(Index >= 0 && getListIndexFromDrawnIndex(Index) < getModel()->getSize())
    {
	    cleanItem(Index);
	    _DrawnIndices[Index] = createIndexComponent(getListIndexFromDrawnIndex(Index));
	    initItem(Index);
    }
}

void List::cleanItem(const UInt32& Index)
{
	if(Index >= 0 && Index < getChildren().size())
    {
	    _DrawnIndices[Index]->removeFocusListener(this);
    }
}

void List::initItem(const UInt32& Index)
{
	if(Index >= 0 && Index < getChildren().size())
    {
	    Pnt2f InsetsTopLeft, InsetsBottomRight;
	    getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	    if(getListIndexFromDrawnIndex(Index) == _FocusedIndex)
	    {
		    getParentWindow()->setFocusedComponent(_DrawnIndices[Index]);
	    }
	    _DrawnIndices[Index]->addFocusListener(this);
	    _DrawnIndices[Index]->setFocused(getListIndexFromDrawnIndex(Index) == _FocusedIndex);
    	
        UInt16 OrientationMajorAxisIndex;
        UInt16 OrientationMinorAxisIndex;
        if(getOrientation() == List::VERTICAL_ORIENTATION)
        {
            OrientationMajorAxisIndex = 1;
        }
        else
        {
            OrientationMajorAxisIndex = 0;
        }
	    OrientationMinorAxisIndex = (OrientationMajorAxisIndex +1) %2;

        //Update the Position and Size of the Index
	    Pnt2f Pos;
	    Vec2f Size;
	    Pos[OrientationMajorAxisIndex] = getCellMajorAxisLength()*getListIndexFromDrawnIndex(Index);
	    Pos[OrientationMinorAxisIndex] = InsetsTopLeft[OrientationMinorAxisIndex];

	    Size[OrientationMajorAxisIndex] = getCellMajorAxisLength();
	    Size[OrientationMinorAxisIndex] = getSize()[OrientationMinorAxisIndex];

	    beginEditCP(_DrawnIndices[Index], Component::PositionFieldMask | Component::SizeFieldMask | Component::ParentContainerFieldMask | Component::ParentWindowFieldMask);
            _DrawnIndices[Index]->setPosition(Pos);
            _DrawnIndices[Index]->setSize(Size);
		    _DrawnIndices[Index]->setParentContainer(ListPtr(this));
		    _DrawnIndices[Index]->setParentWindow(getParentWindow());
        endEditCP(_DrawnIndices[Index], Component::PositionFieldMask | Component::SizeFieldMask | Component::ParentContainerFieldMask | Component::ParentWindowFieldMask);

	    //_DrawnIndices[Index]->updateClipBounds();

	    getChildren()[Index] = _DrawnIndices[Index];
    }
}



void List::selectionChanged(const ListSelectionEventPtr e)
{
	beginEditCP(ListPtr(this), ChildrenFieldMask);
		for(Int32 i(e->getFirstIndex()) ; i<=e->getLastIndex() ; ++i)
		{
			updateItem(getDrawnIndexFromListIndex(i));
		}
	endEditCP(ListPtr(this), ChildrenFieldMask);
}

void List::focusGained(const FocusEventPtr e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e->getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren()[index])
			{
				break;
			}
		}
		updateItem(index);
	}
}

void List::focusLost(const FocusEventPtr e)
{
	//Find this component
	MFComponentPtr::iterator Child = getChildren().find(Component::Ptr::dcast(e->getSource()));
	if(Child != getChildren().end())
	{
		UInt32 index(0);
		for( ; index< getChildren().size(); ++index)
		{
			if((*Child) == getChildren()[index])
			{
				break;
			}
		}
		updateItem(index);
	}
}

Int32 List::getListIndexFromDrawnIndex(const Int32& Index) const
{
	Int32 ListIndex = _TopDrawnIndex + Index;
	if(Index < 0 || ListIndex > _BottomDrawnIndex)
	{
		return -1;
	}
	else
	{
		return ListIndex;
	}
}

Int32 List::getDrawnIndexFromListIndex(const Int32& Index) const
{
	Int32 DrawnIndex = Index - _TopDrawnIndex;
	if(Index < 0 || DrawnIndex > _BottomDrawnIndex)
	{
		return -1;
	}
	else
	{
		return DrawnIndex;
	}
}

void List::mousePressed(const MouseEventPtr e)
{
	bool isContained;
    for(Int32 i(getChildren().size()-1) ; i>=0 ; --i)
    {
        isContained = getChildren()[i]->isContained(e->getLocation(), true);
		checkMouseEnterExit(e,e->getLocation(),getChildren()[i],isContained,e->getViewport());
		if(isContained)
		{
			//Give myself temporary focus
			takeFocus(true);
			//if(!getChildren()[i]->getType().isDerivedFrom(Container::getClassType()))
			//{
				if(getParentWindow() != NullFC &&
				   getParentWindow()->getDrawingSurface() != NullFC &&
				   getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
				{
					if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
					{
						getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionIndex(), getListIndexFromDrawnIndex(i));
					}
					else if(getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
					{
						getSelectionModel()->removeSelectionInterval(getListIndexFromDrawnIndex(i),i);// this toggles the interval
					}
					else
					{
						getSelectionModel()->setSelectionInterval(getListIndexFromDrawnIndex(i),getListIndexFromDrawnIndex(i));
					}
				}
				focusIndex(getListIndexFromDrawnIndex(i));
			//}
			getChildren()[i]->mousePressed(e);
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

void List::keyTyped(const KeyEventPtr e)
{
	bool UpdateSelectionIndex(false);
	Int32 ListIndex(0);
	switch(e->getKey())
	{
	case KeyEvent::KEY_UP:
	case KeyEvent::KEY_DOWN:
	case KeyEvent::KEY_RIGHT:
	case KeyEvent::KEY_LEFT:
		if ( (getOrientation() == List::VERTICAL_ORIENTATION && e->getKey() == KeyEvent::KEY_UP) ||
			(getOrientation() == List::HORIZONTAL_ORIENTATION && e->getKey() == KeyEvent::KEY_LEFT))
		{
			ListIndex = osgMax(_FocusedIndex-1,0);
			UpdateSelectionIndex = true;
		}
		else if ((getOrientation() == List::VERTICAL_ORIENTATION && e->getKey() == KeyEvent::KEY_DOWN) ||
			(getOrientation() == List::HORIZONTAL_ORIENTATION && e->getKey() == KeyEvent::KEY_RIGHT))
		{
			ListIndex = osgMin<Int32>((_FocusedIndex+1), getModel()->getSize()-1);
			UpdateSelectionIndex = true;
		}
		break;
	case KeyEvent::KEY_ENTER:
		if (e->getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
		{
			getSelectionModel()->removeSelectionInterval(_FocusedIndex,_FocusedIndex);// this toggles the interval
		}
		else
		{
			getSelectionModel()->setSelectionInterval(_FocusedIndex, _FocusedIndex);
		}
		break;
	case KeyEvent::KEY_HOME:
		ListIndex = 0;
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_END:
		ListIndex = getModel()->getSize()-1;
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_PAGE_UP:
		ListIndex = osgMax(_FocusedIndex-(_BottomDrawnIndex - _TopDrawnIndex),0);
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_PAGE_DOWN:
		ListIndex = osgMin<Int32>(_FocusedIndex+(_BottomDrawnIndex - _TopDrawnIndex), getModel()->getSize()-1);
		UpdateSelectionIndex = true;
		break;
	}
	
	if(UpdateSelectionIndex)
	{
		focusIndex(ListIndex);
		getSelectionModel()->setLeadSelectionIndex(ListIndex);
		if (e->getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
		{
			getSelectionModel()->setSelectionInterval(getSelectionModel()->getAnchorSelectionIndex(), ListIndex);
		}
		else
		{
			getSelectionModel()->setAnchorSelectionIndex(ListIndex);
		}
	}

	Component::keyTyped(e);
}

void List::updateIndiciesDrawnFromModel(void)
{
	//Clear Drawn indicies from the old model
	_DrawnIndices.clear();
	_TopDrawnIndex = _BottomDrawnIndex = -1;

	//Fill the drawn indicies with the new model
	updateIndicesDrawn();
}

void List::contentsChanged(const ListDataEventPtr e)
{
    updateIndiciesDrawnFromModel();

	if(getSelectionModel() != NULL)
	{
		getSelectionModel()->clearSelection();
	}
	/*if(getModel() != NULL)
	{
		if(_BottomDrawnIndex >= 0)
		{
			for(Int32 i(osgMax(e->getIndex0(),_TopDrawnIndex)) ; i<=osgMin(e->getIndex1(),_BottomDrawnIndex) ; ++i)
			{
				updateItem(i);
			}
		}
	}*/
}

void List::intervalAdded(const ListDataEventPtr e)
{
	updatePreferredSize();
	UInt32 NumInserted(e->getIndex1() - e->getIndex0() + 1);

	getSelectionModel()->incrementValuesAboveIndex(e->getIndex0(), NumInserted);

	if(e->getIndex0() <= _FocusedIndex)
	{
		_FocusedIndex += NumInserted;
	}

	if(e->getIndex0() <= _BottomDrawnIndex)
	{
		//Pop from the back the number of items inserted
		for(UInt32 i(0) ; i<NumInserted ; ++i)
		{
			cleanItem(_DrawnIndices.size()-1);
			_DrawnIndices.pop_back();
		}
		if(e->getIndex0() <= _TopDrawnIndex)
		{
			//Push To the front the number of items inserted
			for(UInt32 i(1) ; i<=NumInserted ; ++i)
			{
				_DrawnIndices.push_front(createIndexComponent(_TopDrawnIndex + (NumInserted-i)));
			}
		}
		else
		{
			//Pop off the Items that will slide down
			std::deque<ComponentPtr> SlideDownList;
			UInt32 NumToSlideDown(_BottomDrawnIndex-e->getIndex0()-NumInserted+1);
			for(UInt32 i(0) ; i<NumToSlideDown ; ++i)
			{
				SlideDownList.push_front(_DrawnIndices.back());
				_DrawnIndices.pop_back();
			}

			//Push the new Items
			for(UInt32 i(0) ; i<NumInserted ; ++i)
			{
				_DrawnIndices.push_back(createIndexComponent(e->getIndex0() + i));
			}
			//Push the slid Items
			for(UInt32 i(0) ; i<NumToSlideDown ; ++i)
			{
				_DrawnIndices.push_back(SlideDownList[i]);
			}
		}

		if(_BottomDrawnIndex >= 0)
		{
			for(Int32 i(osgMax(e->getIndex0(),_TopDrawnIndex)) ; i<=_BottomDrawnIndex ; ++i)
			{
				updateItem(i);
			}
		}

		beginEditCP(ListPtr(this), ChildrenFieldMask);
			getChildren().clear();
			for(UInt32 i(0) ; i<_DrawnIndices.size() ; ++i)
			{
				getChildren().push_back(_DrawnIndices[i]);
			}
		endEditCP(ListPtr(this), ChildrenFieldMask);
		for(UInt32 i(0) ; i<_DrawnIndices.size() ; ++i)
		{
			initItem(i);
		}
	}

	
}

void List::intervalRemoved(const ListDataEventPtr e)
{
	UInt32 NumRemoved(e->getIndex1() - e->getIndex0() + 1);
	//The Selected Items
	getSelectionModel()->decrementValuesAboveIndex(e->getIndex0(), NumRemoved);

	if(e->getIndex0() < _FocusedIndex)
	{
		_FocusedIndex -= NumRemoved;
	}

    Int32 NewTopDrawnIndex,
          NewBottomDrawnIndex;
    Int32 OldTopDrawnIndex(_TopDrawnIndex),
          OldBottomDrawnIndex(_BottomDrawnIndex);
    getDrawnIndices(NewTopDrawnIndex, NewBottomDrawnIndex);
    _TopDrawnIndex = NewTopDrawnIndex;
    _BottomDrawnIndex = NewBottomDrawnIndex;

	if(e->getIndex0() <= OldBottomDrawnIndex)
	{
		//Push to the back the number of items removed
		UInt32 NumToPush(0);
		if(OldBottomDrawnIndex==NewBottomDrawnIndex)
		{
			NumToPush = NumRemoved;
		}
		for(UInt32 i(0) ; i<NumToPush ; ++i)
		{
			_DrawnIndices.push_back(createIndexComponent(NewBottomDrawnIndex - (NumToPush-i)+1));
		}

		if(e->getIndex0() <= OldTopDrawnIndex)
		{
			//Pop From the front the number of items removed
			for(UInt32 i(1) ; i<=osgMin<Int32>(NumRemoved,OldBottomDrawnIndex-OldTopDrawnIndex) ; ++i)
			{
				cleanItem(0);
				_DrawnIndices.pop_front();
			}
		}
		else
		{
			//Pop off the Items that will slide up
			std::deque<ComponentPtr> SlideUpList;
			UInt32 NumToSlideUp(NewBottomDrawnIndex-e->getIndex1()+NumRemoved);
			for(UInt32 i(0) ; i<NumToSlideUp ; ++i)
			{
				SlideUpList.push_front(_DrawnIndices.back());
				_DrawnIndices.pop_back();
			}

			//Pop off the removed Items
			//Pop From the back the number of items removed
			for(UInt32 i(1) ; i<=NumRemoved ; ++i)
			{
				cleanItem(_DrawnIndices.size()-1);
				_DrawnIndices.pop_back();
			}

			//Push the slid Items
			for(UInt32 i(0) ; i<NumToSlideUp ; ++i)
			{
				_DrawnIndices.push_back(SlideUpList[i]);
			}
		}
		
		if(NewBottomDrawnIndex >= 0)
		{
			for(Int32 i(osgMax(e->getIndex0(),NewTopDrawnIndex)) ; i<=NewBottomDrawnIndex ; ++i)
			{
				updateItem(i);
			}
		}

		beginEditCP(ListPtr(this), ChildrenFieldMask);
			getChildren().clear();
			for(UInt32 i(0) ; i<_DrawnIndices.size() ; ++i)
			{
				getChildren().push_back(_DrawnIndices[i]);
			}
		endEditCP(ListPtr(this), ChildrenFieldMask);
		for(UInt32 i(0) ; i<_DrawnIndices.size() ; ++i)
		{
			initItem(i);
		}
	}
	
	updatePreferredSize();
    getSelectionModel()->removeIndexInterval(e->getIndex0(), e->getIndex1());
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
	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    UInt16 OrientationMajorAxisIndex;
    UInt16 OrientationMinorAxisIndex;
    if(getOrientation() == List::VERTICAL_ORIENTATION)
    {
        OrientationMajorAxisIndex = 1;
    }
    else
    {
        OrientationMajorAxisIndex = 0;
    }
	OrientationMinorAxisIndex = (OrientationMajorAxisIndex +1) %2;

    //Update the Position and Size of all the Drawn Rows
	Pnt2f Pos;
	Vec2f Size;
	for(UInt32 i(0) ; i<getChildren().size() ; ++i)
    {
		Pos[OrientationMajorAxisIndex] = getCellMajorAxisLength()*(i+_TopDrawnIndex);
		Pos[OrientationMinorAxisIndex] = InsetsTopLeft[OrientationMinorAxisIndex];

		Size[OrientationMajorAxisIndex] = getCellMajorAxisLength();
		Size[OrientationMinorAxisIndex] = getSize()[OrientationMinorAxisIndex];

        beginEditCP(getChildren(i), Component::PositionFieldMask | Component::SizeFieldMask);
            getChildren(i)->setPosition(Pos);
            getChildren(i)->setSize(Size);
        endEditCP(getChildren(i), Component::PositionFieldMask | Component::SizeFieldMask);
    }
}

Vec2f List::getPreferredScrollableViewportSize(void)
{
    return getPreferredSize();
}

Int32 List::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
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
    return getOrientation() != List::VERTICAL_ORIENTATION;
}

bool List::getScrollableTracksViewportWidth(void)
{
    return getOrientation() == List::VERTICAL_ORIENTATION;
}


bool List::getScrollableHeightMinTracksViewport(void)
{
    return getOrientation() == List::VERTICAL_ORIENTATION;
}

bool List::getScrollableWidthMinTracksViewport(void)
{
    return getOrientation() != List::VERTICAL_ORIENTATION;
}

Int32 List::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    if(orientation == getOrientation())
    {
        return getCellMajorAxisLength();
    }
    else
    {
        return Container::getScrollableUnitIncrement(VisibleRectTopLeft, VisibleRectBottomRight, orientation, direction);
    }
    
}

void List::updateIndicesDrawn(void)
{
    Int32 NewTopDrawnIndex,
          NewBottomDrawnIndex;
    Int32 OldTopDrawnIndex(_TopDrawnIndex),
          OldBottomDrawnIndex(_BottomDrawnIndex);
    getDrawnIndices(NewTopDrawnIndex, NewBottomDrawnIndex);
    _TopDrawnIndex = NewTopDrawnIndex;
    _BottomDrawnIndex = NewBottomDrawnIndex;

    if(NewTopDrawnIndex > OldTopDrawnIndex  && _DrawnIndices.size() != 0 )
    {
        //Remove all of the Drawn Indices above NewTopDrawnIndex
        for(Int32 i(OldTopDrawnIndex) ; i<osgMin(NewTopDrawnIndex, OldBottomDrawnIndex+1) ; ++i)
        {
			cleanItem(0);
            _DrawnIndices.pop_front();
        }
    }

    if(NewBottomDrawnIndex < OldBottomDrawnIndex && _DrawnIndices.size() != 0)
    {
        //Remove all of the Drawn Indices below NewBottomDrawnIndex
        for(Int32 i(osgMax(NewBottomDrawnIndex+1, OldTopDrawnIndex)) ; i<=OldBottomDrawnIndex ; ++i)
        {
			cleanItem(_DrawnIndices.size()-1);
            _DrawnIndices.pop_back();
        }
    }


    if(NewTopDrawnIndex < OldTopDrawnIndex)
    {
        //Insert all of the Drawn Indices between NewTopDrawnIndex and OldTopDrawnIndex
        for(Int32 i(osgMin(OldTopDrawnIndex-1, NewBottomDrawnIndex)) ; i>=NewTopDrawnIndex ; --i)
        {
            _DrawnIndices.push_front(createIndexComponent(i));
        }
    }

    if(NewBottomDrawnIndex > OldBottomDrawnIndex)
    {
        //Insert all of the Drawn Indices between OldBottomDrawnIndex and NewBottomDrawnIndex
        for(Int32 i(osgMax(NewTopDrawnIndex, OldBottomDrawnIndex+1)) ; i<=NewBottomDrawnIndex ; ++i)
        {
            _DrawnIndices.push_back(createIndexComponent(i));
        }
    }


    beginEditCP(ListPtr(this), ChildrenFieldMask);
        getChildren().clear();
        for(UInt32 i(0) ; i<_DrawnIndices.size() ; ++i)
        {
            getChildren().push_back(_DrawnIndices[i]);
        }
    endEditCP(ListPtr(this), ChildrenFieldMask);
    for(UInt32 i(0) ; i<_DrawnIndices.size() ; ++i)
    {
		initItem(i);
    }
}

void List::getDrawnIndices(Int32& Beginning, Int32& End) const
{
    //Get My Clip Bounds
    Pnt2f ClipTopLeft, ClipBottomRight;
    getClipBounds(ClipTopLeft, ClipBottomRight);

    Beginning = getIndexClosestToLocation(ClipTopLeft);
    End = getIndexClosestToLocation(ClipBottomRight);
}

Int32 List::getIndexClosestToLocation(const Pnt2f& Location) const
{
	if(getModel() == NULL) {return -1;}

    UInt16 MajorAxis;
    if(getOrientation() == List::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }

    //Determine the index
    Int32 Index(osgMax(-1, osgMin<Int32>(Location[MajorAxis]/static_cast<Int32>(getCellMajorAxisLength()),getModel()->getSize()-1)));

	return Index;
}

Int32 List::getIndexForLocation(const Pnt2f& Location) const
{
	if(getModel() == NULL) {return -1;}

    UInt16 MajorAxis;
    if(getOrientation() == List::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }

    //Determine the index
    Int32 Index(Location[MajorAxis]/static_cast<Int32>(getCellMajorAxisLength()));

	if(Index < 0 || Index >= getModel()->getSize())
	{
		return -1;
	}
	else
	{
		return Index;
	}

}

ComponentPtr List::createIndexComponent(const UInt32& Index)
{
    if(getModel() != NULL && getCellGenerator() != NullFC)
    {
        bool Selected;

        if(_SelectionModel != NULL)
        {
            Selected = _SelectionModel->isSelectedIndex(Index);
        }
        else
        {
            Selected = false;
        }
		if(getCellGenerator()->getType().isDerivedFrom(ListComponentGenerator::getClassType()))
        {
            return ListComponentGenerator::Ptr::dcast(getCellGenerator())->getListComponent(ListPtr(this), getModel()->getElementAt(Index), Index, Selected, Index == _FocusedIndex);
        }
        else
        {
            return getCellGenerator()->getComponent(ListPtr(this),getModel()->getElementAt(Index), Index, 0,Selected, Index == _FocusedIndex);
        }
    }
    else
    {
        return NullFC;
    }
}

void List::updatePreferredSize(void)
{
	UInt32 ListLength;
	if(getModel() != NULL)
	{
		ListLength = getModel()->getSize();
	}
	else
	{
		ListLength = 0;
	}
    beginEditCP(ListPtr(this), PreferredSizeFieldMask);
        if(getOrientation() == List::VERTICAL_ORIENTATION)
        {
            setPreferredSize(Vec2f(getPreferredSize().x(), getCellMajorAxisLength()*ListLength));
        }
        else
        {
            setPreferredSize(Vec2f(getCellMajorAxisLength()*ListLength, getPreferredSize().y()));
        }
    endEditCP(ListPtr(this), PreferredSizeFieldMask);
}

void List::focusIndex(const Int32& Index)
{
	Int32 OldFocused(_FocusedIndex);
	_FocusedIndex = Index;

	//Unfocus the old index
	if(OldFocused >= _TopDrawnIndex && OldFocused <= _BottomDrawnIndex )
	{
		takeFocus();
	}


	//Focus the new index
	if(_FocusedIndex >= _TopDrawnIndex && _FocusedIndex <= _BottomDrawnIndex )
	{
		getChildren()[getDrawnIndexFromListIndex(_FocusedIndex)]->takeFocus();
	}

	if(getAutoScrollToFocused())
	{
		scrollToFocused();
	}
}

void List::scrollToIndex(const UInt32& Index)
{
    UInt16 MajorAxis;
    UInt16 MinorAxis;
    if(getOrientation() == List::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
	MinorAxis = (MajorAxis+1)%2;

	Pnt2f InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	Pnt2f ClipTopLeft, ClipBottomRight;
	getClipBounds(ClipTopLeft, ClipBottomRight);
	
	Pnt2f UnionTopLeft, UnionBottomRight;
	//Get the intersection of my bounds with my parent containers clip bounds
	quadIntersection(InsetsTopLeft, InsetsBottomRight,
		ClipTopLeft, ClipBottomRight,
		UnionTopLeft, UnionBottomRight);

	//Check if any scrolling is needed
	if(Index <= _TopDrawnIndex)
	{
		//Scroll Up so that this Index is The First Visible
		Pnt2f Pos;
		Pos[MajorAxis] = Index * getCellMajorAxisLength();
		Pos[MinorAxis] = UnionTopLeft[MinorAxis];

		scrollToPoint(Pos);
	}
	else if(Index >= _BottomDrawnIndex && _BottomDrawnIndex != -1)
	{
		UInt32 CorrectedIndex;
		if(Index >= getModel()->getSize())
		{
			CorrectedIndex = getModel()->getSize()-1;
		}
		else
		{
			CorrectedIndex = Index;
		}

		//Scroll Down so that this Index is the last Visible
		Pnt2f Pos;
		Pos[MajorAxis] = (CorrectedIndex * getCellMajorAxisLength()) - (UnionBottomRight[MajorAxis]-UnionTopLeft[MajorAxis]) + getCellMajorAxisLength();
		Pos[(MajorAxis+1)%2] = UnionTopLeft[MinorAxis];

		scrollToPoint(Pos);
	}
}

void List::scrollToFocused(void)
{
	if(_FocusedIndex >= 0)
	{
		scrollToIndex(static_cast<UInt32>(_FocusedIndex));
	}
}

void List::scrollToSelection(void)
{
	if(_SelectionModel != NULL)
	{
		Int32 Index(_SelectionModel->getMinSelectionIndex());

		if(Index >= 0)
		{
			scrollToIndex(static_cast<UInt32>(Index));
		}
	}
}

ComponentPtr List::getComponentAtIndex(const UInt32& Index)
{
	if(getModel() != NULL && Index < getModel()->getSize())
	{
		return getChildren()[Index];
	}
	else
	{
		return NullFC;
	}
}

boost::any List::getValueAtIndex(const UInt32& Index)
{
	if(getModel() != NULL && Index < getModel()->getSize())
	{
		return getModel()->getElementAt(Index);
	}
	else
	{
        return boost::any();
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

List::List(void) :
    Inherited(),
		_SelectionModel(),
        _TopDrawnIndex(-1),
        _BottomDrawnIndex(-1),
		_FocusedIndex(-1)
{
}

List::List(const List &source) :
    Inherited(source),
		_SelectionModel(source._SelectionModel),
        _TopDrawnIndex(-1),
        _BottomDrawnIndex(-1),
		_FocusedIndex(-1)
{
}

List::~List(void)
{
}

/*----------------------------- class specific ----------------------------*/

void List::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & CellMajorAxisLengthFieldMask) &&
        getModel() != NULL)
    {
		updatePreferredSize();
    }
	
    if(whichField & List::ClipBoundsFieldMask)
    {
        updateIndicesDrawn();
    }

	if((whichField & AutoScrollToFocusedFieldMask) &&
		getAutoScrollToFocused())
	{
		scrollToFocused();
	}

	if(whichField & ModelFieldMask)
	{
		beginEditCP(ListPtr(this), ChildrenFieldMask);
			getChildren().clear();
		endEditCP(ListPtr(this), ChildrenFieldMask);

		if(getModel() != NULL)
		{
			getModel()->addListDataListener(this);
		}
		
		updateIndiciesDrawnFromModel();
		updatePreferredSize();
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


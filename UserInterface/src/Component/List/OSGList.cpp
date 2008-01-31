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

	Int32 Index(getIndexForLocation(PointInComponent));

	if(Index >= _TopDrawnIndex && Index <= _BottomDrawnIndex)
	{
		return getChildren().getValue(getDrawnIndexFromListIndex(Index));
	}
	else
	{
		return NullFC;
	}
}

SharedFieldPtr List::getValueAtPoint(const MouseEvent& e)
{
    Pnt2s PointInComponent(ViewportToComponent(e.getLocation(), ListPtr(this), e.getViewport()));

	Int32 Index(getIndexForLocation(PointInComponent));
	if(Index > 0 && Index < _Model->getSize())
	{
		return _Model->getElementAt(Index);
	}
	else
	{
		return SharedFieldPtr();
	}

}

void List::updateItem(const UInt32& Index)
{
	if(Index < 0 || Index >= getChildren().size()) {return;}

	cleanItem(Index);
	_DrawnIndices[Index] = createIndexComponent(getListIndexFromDrawnIndex(Index));
	initItem(Index);
}

void List::cleanItem(const UInt32& Index)
{
	if(Index < 0 || Index >= getChildren().size()) {return;}
	_DrawnIndices[Index]->removeFocusListener(this);
}

void List::initItem(const UInt32& Index)
{
	Pnt2s InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	if(Index < 0 || Index >= getChildren().size()) {return;}
	if(getListIndexFromDrawnIndex(Index) == _FocusedIndex)
	{
		getParentWindow()->setFocusedComponent(_DrawnIndices[Index]);
	}
	_DrawnIndices[Index]->addFocusListener(this);
	_DrawnIndices[Index]->setFocused(getListIndexFromDrawnIndex(Index) == _FocusedIndex);
	
    UInt16 OrientationMajorAxisIndex;
    UInt16 OrientationMinorAxisIndex;
    if(getCellOrientation() == VERTICAL_ALIGNMENT)
    {
        OrientationMajorAxisIndex = 1;
    }
    else
    {
        OrientationMajorAxisIndex = 0;
    }
	OrientationMinorAxisIndex = (OrientationMajorAxisIndex +1) %2;

    //Update the Position and Size of the Index
	Pnt2s Pos;
	Vec2s Size;
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

	getChildren().setValue(_DrawnIndices[Index], Index);
}



void List::selectionChanged(const ListSelectionEvent& e)
{
	beginEditCP(ListPtr(this), ChildrenFieldMask);
		for(UInt32 i(e.getFirstIndex()) ; i<=e.getLastIndex() ; ++i)
		{
			updateItem(getDrawnIndexFromListIndex(i));
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
				focusIndex(getListIndexFromDrawnIndex(i));
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
	bool UpdateSelectionIndex(false);
	Int32 ListIndex(0);
	switch(e.getKey())
	{
	case KeyEvent::KEY_UP:
	case KeyEvent::KEY_DOWN:
	case KeyEvent::KEY_RIGHT:
	case KeyEvent::KEY_LEFT:
		if ( (getCellOrientation() == VERTICAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_UP) ||
			(getCellOrientation() == HORIZONTAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_LEFT))
		{
			ListIndex = osgMax(_FocusedIndex-1,0);
			UpdateSelectionIndex = true;
		}
		else if ((getCellOrientation() == VERTICAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_DOWN) ||
			(getCellOrientation() == HORIZONTAL_ALIGNMENT && e.getKey() == KeyEvent::KEY_RIGHT))
		{
			ListIndex = osgMin<Int32>((_FocusedIndex+1), _Model->getSize()-1);
			UpdateSelectionIndex = true;
		}
		break;
	case KeyEvent::KEY_ENTER:
		if (e.getModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
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
		ListIndex = _Model->getSize()-1;
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_PAGE_UP:
		ListIndex = osgMax(_FocusedIndex-(_BottomDrawnIndex - _TopDrawnIndex),0);
		UpdateSelectionIndex = true;
		break;
	case KeyEvent::KEY_PAGE_DOWN:
		ListIndex = osgMin<Int32>(_FocusedIndex+(_BottomDrawnIndex - _TopDrawnIndex), _Model->getSize()-1);
		UpdateSelectionIndex = true;
		break;
	}
	
	if(UpdateSelectionIndex)
	{
		focusIndex(ListIndex);
		getSelectionModel()->setLeadSelectionIndex(ListIndex);
		if (e.getModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
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

void List::contentsChanged(ListDataEvent e)
{
	if(getModel() != NULL)
	{
		if(getModel()->getSize() != getChildren().size())
		{
			updateIndiciesDrawnFromModel();
			/*beginEditCP(ListPtr(this), ChildrenFieldMask);
				for(UInt32 i(e.getIndex0()) ; i<getModel()->getSize() && i<=e.getIndex1() ; ++i )
				{
		            updateItem(i);
				}
			endEditCP(ListPtr(this), ChildrenFieldMask);*/
		}
		Pnt2s Position(0,0);
		for(UInt32 i(0) ; i<getModel()->getSize() && i<=e.getIndex1() ; ++i )
		{
			beginEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);
			   getChildren().getValue(i)->setPosition(Position);
               if(getCellOrientation() == VERTICAL_ALIGNMENT)
               {
			      getChildren().getValue(i)->setSize( Vec2s(getSize().x(), getCellMajorAxisLength()) );
               }
               else
               {
                  getChildren().getValue(i)->setSize( Vec2s(getCellMajorAxisLength(), getSize().y()) );
               }
			endEditCP(getChildren().getValue(i), PositionFieldMask | SizeFieldMask);

            if(getCellOrientation() == VERTICAL_ALIGNMENT)
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
	
	updateIndiciesDrawnFromModel();
	updatePreferredSize();
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
	Pnt2s InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

    UInt16 OrientationMajorAxisIndex;
    UInt16 OrientationMinorAxisIndex;
    if(getCellOrientation() == VERTICAL_ALIGNMENT)
    {
        OrientationMajorAxisIndex = 1;
    }
    else
    {
        OrientationMajorAxisIndex = 0;
    }
	OrientationMinorAxisIndex = (OrientationMajorAxisIndex +1) %2;

    //Update the Position and Size of all the Drawn Rows
	Pnt2s Pos;
	Vec2s Size;
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
    return getCellOrientation() != VERTICAL_ALIGNMENT;
}

bool List::getScrollableTracksViewportWidth(void)
{
    return getCellOrientation() == VERTICAL_ALIGNMENT;
}

Int32 List::getScrollableUnitIncrement(const Pnt2s& VisibleRectTopLeft, const Pnt2s& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    if(orientation == getCellOrientation())
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
        //for(Int32 i(osgMin(OldTopDrawnIndex-1, NewBottomDrawnIndex)) ; i>=NewTopDrawnIndex ; --i)
        //{
		//	initItem(i-NewTopDrawnIndex);
        //}
    }

    if(NewBottomDrawnIndex > OldBottomDrawnIndex)
    {
        //Insert all of the Drawn Indices between OldBottomDrawnIndex and NewBottomDrawnIndex
        for(Int32 i(osgMax(NewTopDrawnIndex, OldBottomDrawnIndex+1)) ; i<=NewBottomDrawnIndex ; ++i)
        {
            _DrawnIndices.push_back(createIndexComponent(i));
        }
        //for(Int32 i(osgMax(NewTopDrawnIndex, OldBottomDrawnIndex+1)) ; i<=NewBottomDrawnIndex ; ++i)
        //{
        //}
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
    Pnt2s ClipTopLeft, ClipBottomRight;
    getClipBounds(ClipTopLeft, ClipBottomRight);

    Beginning = getIndexClosestToLocation(ClipTopLeft);
    End = getIndexClosestToLocation(ClipBottomRight);
}

Int32 List::getIndexClosestToLocation(const Pnt2s& Location) const
{
	if(_Model == NULL) {return -1;}

    UInt16 MajorAxis;
    if(getCellOrientation() == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }

    //Determine the index
    Int32 Index(osgMax(-1, osgMin<Int32>(Location[MajorAxis]/static_cast<Int32>(getCellMajorAxisLength()),_Model->getSize()-1)));

	return Index;
}

Int32 List::getIndexForLocation(const Pnt2s& Location) const
{
	if(_Model == NULL) {return -1;}

    UInt16 MajorAxis;
    if(getCellOrientation() == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }

    //Determine the index
    Int32 Index(Location[MajorAxis]/static_cast<Int32>(getCellMajorAxisLength()));

	if(Index < 0 || Index >= _Model->getSize())
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
    if(_Model != NULL && getCellGenerator() != NullFC)
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
	if(_Model != NULL)
	{
		ListLength = _Model->getSize();
	}
	else
	{
		ListLength = 0;
	}
    beginEditCP(ListPtr(this), PreferredSizeFieldMask);
        if(getCellOrientation() == VERTICAL_ALIGNMENT)
        {
            setPreferredSize(Vec2s(getPreferredSize().x(), getCellMajorAxisLength()*ListLength));
        }
        else
        {
            setPreferredSize(Vec2s(getCellMajorAxisLength()*ListLength, getPreferredSize().y()));
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
		getChildren().getValue(getDrawnIndexFromListIndex(_FocusedIndex))->takeFocus();
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
    if(getCellOrientation() == VERTICAL_ALIGNMENT)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
	MinorAxis = (MajorAxis+1)%2;

	Pnt2s InsetsTopLeft, InsetsBottomRight;
	getInsideInsetsBounds(InsetsTopLeft, InsetsBottomRight);

	Pnt2s ClipTopLeft, ClipBottomRight;
	getClipBounds(ClipTopLeft, ClipBottomRight);
	
	Pnt2s UnionTopLeft, UnionBottomRight;
	//Get the intersection of my bounds with my parent containers clip bounds
	quadIntersection(InsetsTopLeft, InsetsBottomRight,
		ClipTopLeft, ClipBottomRight,
		UnionTopLeft, UnionBottomRight);

	//Check if any scrolling is needed
	if(Index <= _TopDrawnIndex)
	{
		//Scroll Up so that this Index is The First Visible
		Pnt2s Pos;
		Pos[MajorAxis] = Index * getCellMajorAxisLength();
		Pos[MinorAxis] = UnionTopLeft[MinorAxis];

		scrollToPoint(Pos);
	}
	else if(Index >= _BottomDrawnIndex && _BottomDrawnIndex != -1)
	{
		UInt32 CorrectedIndex;
		if(Index >= _Model->getSize())
		{
			CorrectedIndex = _Model->getSize()-1;
		}
		else
		{
			CorrectedIndex = Index;
		}

		//Scroll Down so that this Index is the last Visible
		Pnt2s Pos;
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

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

List::List(void) :
    Inherited(),
		_Model(NULL),
		_SelectionModel(),
        _TopDrawnIndex(-1),
        _BottomDrawnIndex(-1),
		_FocusedIndex(-1)
{
}

List::List(const List &source) :
    Inherited(source),
		_Model(source._Model),
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
        _Model != NULL)
    {
		updatePreferredSize();
    }
	
    if((whichField & List::ClipTopLeftFieldMask) ||
       (whichField & List::ClipBottomRightFieldMask))
    {
        updateIndicesDrawn();
    }

	if((whichField & AutoScrollToFocusedFieldMask) &&
		getAutoScrollToFocused())
	{
		scrollToFocused();
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


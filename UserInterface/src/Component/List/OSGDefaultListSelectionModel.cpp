/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include "OSGDefaultListSelectionModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultListSelectionModel
A DefaultListSelectionModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void 	DefaultListSelectionModel::addSelectionInterval(UInt32 index0, UInt32 index1)
{
	// it is necessary to have two versions of range
	// if newRange is needed, it is set so that index0 is smaller than index1
	// range is still necessary so that anchor and lead get set correctly
	IndexRange range(index0, index1);
	IndexRange newRange(index0, index1);
   //TODO:Implement
	if (index0 >= 0 && index1 >= 0)
	{
		switch (_SelectionMode)
		{
			case SINGLE_SELECTION:
				range.StartIndex = range.EndIndex;
				if (_RangeSelectionList.empty())
				{
					_RangeSelectionList.push_back(range);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), range.StartIndex, range.EndIndex, _ValueIsAdjusting));
				}
				else if (_RangeSelectionList.front() != range)
				{
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), range));
					updateMinMax();
					minMax = getMinMaxSelection(minMax, IndexRange(_MinSelectionIndex, _MaxSelectionIndex));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(range);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), minMax.StartIndex, minMax.EndIndex, _ValueIsAdjusting));
				}
				break;
			case SINGLE_INTERVAL_SELECTION:
				if (range.EndIndex < range.StartIndex)
				{
					newRange.EndIndex = range.StartIndex;
					newRange.StartIndex = range.EndIndex;
				}
				if (_RangeSelectionList.empty())
				{
					_RangeSelectionList.push_back(newRange);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), newRange.StartIndex, newRange.EndIndex, _ValueIsAdjusting));
				}
				else if (_RangeSelectionList.front() != newRange)
				{
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), newRange));
					updateMinMax();
					minMax = getMinMaxSelection(minMax, IndexRange(_MinSelectionIndex, _MaxSelectionIndex));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(newRange);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), minMax.StartIndex, minMax.EndIndex, _ValueIsAdjusting));
				}
				break;
			case MULTIPLE_INTERVAL_SELECTION:
				range.StartIndex = range.EndIndex;
				if (!isSelectedIndex(index1))
				{
					_RangeSelectionList.push_back(range);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), range.StartIndex, range.EndIndex, _ValueIsAdjusting));
				}
				break;
			default:
				break;
		}
		// update indices
		_AnchorSelectionIndex = range.StartIndex;
		_LeadSelectionIndex = range.EndIndex;
	}
}

void 	DefaultListSelectionModel::clearSelection(void)
{
	_RangeSelectionList.clear();
}

UInt32 	DefaultListSelectionModel::getAnchorSelectionIndex(void) const
{
   return _AnchorSelectionIndex;
}

UInt32 	DefaultListSelectionModel::getLeadSelectionIndex(void) const
{
   return _LeadSelectionIndex;
}

UInt32 	DefaultListSelectionModel::getMaxSelectionIndex(void) const
{
   return _MaxSelectionIndex;
}

UInt32 	DefaultListSelectionModel::getMinSelectionIndex(void) const
{
   return _MinSelectionIndex;
}

UInt32 	DefaultListSelectionModel::getSelectionMode(void) const
{
   return _SelectionMode;
}

bool 	DefaultListSelectionModel::getValueIsAdjusting(void) const
{
   return _ValueIsAdjusting;
}

void 	DefaultListSelectionModel::insertIndexInterval(UInt32 index, UInt32 length, bool before)
{
   //TODO:Implement
	IndexRange range(0,0);
	if (before)
	{
		range.StartIndex = index - length + 1;
		range.EndIndex = index;
	}
	else
	{
		range.StartIndex = index;
		range.EndIndex = index + length - 1;
	}
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			if (before)
				range.StartIndex = range.EndIndex;
			else
				range.EndIndex = range.StartIndex;
			if (_RangeSelectionList.empty())
			{
				_RangeSelectionList.push_back(range);
				produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), range.StartIndex, range.EndIndex, _ValueIsAdjusting));
			}
			else if (_RangeSelectionList.front() != range)
			{
				IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), range));
				_RangeSelectionList.clear();
				_RangeSelectionList.push_back(range);
				produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), minMax.StartIndex, minMax.EndIndex, _ValueIsAdjusting));
			}
			break;
		case SINGLE_INTERVAL_SELECTION:
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			break;
		default:
			break;
	}
}

bool 	DefaultListSelectionModel::isSelectedIndex(UInt32 index) const
{
	RangeSelectionListConstItor ListItor;
	for(ListItor = _RangeSelectionList.begin() ; ListItor != _RangeSelectionList.end() ; ++ListItor )
	{
		if(index >= (*ListItor).StartIndex && index<= (*ListItor).EndIndex)
		{
			return true;
		};
	}
   return false;
}

bool 	DefaultListSelectionModel::isSelectionEmpty(void) const
{
	return _RangeSelectionList.empty();
}

void 	DefaultListSelectionModel::removeIndexInterval(UInt32 index0, UInt32 index1)
{
	RangeSelectionListItor ListItor;
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			_RangeSelectionList.clear();
			break;
		case SINGLE_INTERVAL_SELECTION:
			_RangeSelectionList.clear();
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			// presently this only works for intervals of length 1
			index0 = index1;
			for(ListItor = _RangeSelectionList.begin() ; ListItor != _RangeSelectionList.end() ; ++ListItor )
			{
				if(index1 >= (*ListItor).StartIndex && index1 <= (*ListItor).EndIndex)
				{
					//IndexRange range(index1, index1);
					if (index1 == (*ListItor).StartIndex)
						++(*ListItor).StartIndex;
					else if (index1 == (*ListItor).EndIndex)
						--(*ListItor).EndIndex;
					else
					{
						_RangeSelectionList.push_back(IndexRange(index1 + 1, (*ListItor).EndIndex));
						(*ListItor).EndIndex = index1 - 1;
					}
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), index1, index1, _ValueIsAdjusting));
				}
			}
			break;
		default:
			break;
	}
	_AnchorSelectionIndex = index0;
	_LeadSelectionIndex = index1;
}

void 	DefaultListSelectionModel::removeSelectionInterval(UInt32 index0, UInt32 index1)
{
   //TODO:Implement
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			_RangeSelectionList.clear();
			break;
		case SINGLE_INTERVAL_SELECTION:
			_RangeSelectionList.clear();
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			// basically, this toggles all of them across the interval
			if (index1 < index0);
			{
				UInt32 temp(index0);
				index0 = index1;
				index1 = temp;
			}
			for (UInt32 i(index0); i <= index1; ++i)
				if (isSelectedIndex(i))
					removeIndexInterval(i,i);
				else
					addSelectionInterval(i,i);
			break;
		default:
			break;
	}
}

void 	DefaultListSelectionModel::setAnchorSelectionIndex(UInt32 index)
{
   //TODO:Implement
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			_LeadSelectionIndex = _AnchorSelectionIndex = index;
			break;
		case MULTIPLE_INTERVAL_SELECTION:
		case SINGLE_INTERVAL_SELECTION:
			_AnchorSelectionIndex = index;
			break;
		default:
			break;
	}
}

void 	DefaultListSelectionModel::setLeadSelectionIndex(UInt32 index)
{
   //TODO:Implement
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			_LeadSelectionIndex = _AnchorSelectionIndex = index;
			break;
		case MULTIPLE_INTERVAL_SELECTION:
		case SINGLE_INTERVAL_SELECTION:
			_LeadSelectionIndex = index;
			break;
		default:
			break;
	}
}

void 	DefaultListSelectionModel::setSelectionInterval(UInt32 index0, UInt32 index1)
{
	IndexRange range(index0, index1);
	IndexRange newRange(index0, index1);
	if (index0 >= 0 && index1 >= 0) // it is possible to have the anchor or lead be negative
	{
		switch (_SelectionMode)
		{
			case SINGLE_SELECTION:
				range.StartIndex = range.EndIndex;
				if (_RangeSelectionList.empty())
				{
					_RangeSelectionList.push_back(range);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), range.StartIndex, range.EndIndex, _ValueIsAdjusting));
				}
				else if (_RangeSelectionList.front() != range)
				{
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), range));
					updateMinMax();
					minMax = getMinMaxSelection(minMax, IndexRange(_MinSelectionIndex, _MaxSelectionIndex));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(range);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), minMax.StartIndex, minMax.EndIndex, _ValueIsAdjusting));
				}
				break;
			case MULTIPLE_INTERVAL_SELECTION:
			case SINGLE_INTERVAL_SELECTION:
				if (range.EndIndex < range.StartIndex)
				{
					newRange.EndIndex = range.StartIndex;
					newRange.StartIndex = range.EndIndex;
				}
				if (_RangeSelectionList.empty())
				{
					_RangeSelectionList.push_back(newRange);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), newRange.StartIndex, newRange.EndIndex, _ValueIsAdjusting));
				}
				else if (_RangeSelectionList.front() != newRange)
				{
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), newRange));
					updateMinMax();
					minMax = getMinMaxSelection(minMax, IndexRange(_MinSelectionIndex, _MaxSelectionIndex));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(newRange);
					produceSelectionChanged(ListSelectionEvent(NullFC, getSystemTime(), minMax.StartIndex, minMax.EndIndex, _ValueIsAdjusting));
				}
				break;
			default:
				break;
		}
		// update indices
		_AnchorSelectionIndex = range.StartIndex;
		_LeadSelectionIndex = range.EndIndex;
	}
}

void 	DefaultListSelectionModel::setSelectionMode(UInt32 selectionMode)
{
	_SelectionMode = static_cast<SelectionMode>(selectionMode);
	_RangeSelectionList.clear();
}

void 	DefaultListSelectionModel::setValueIsAdjusting(bool valueIsAdjusting)
{
   _ValueIsAdjusting = valueIsAdjusting;
}

void DefaultListSelectionModel::produceSelectionChanged(const ListSelectionEvent& e)
{
   for(ListSelectionListenerSetConstItor SetItor(_ListSelectionListeners.begin()) ; SetItor != _ListSelectionListeners.end() ; ++SetItor)
   {
	   (*SetItor)->selectionChanged(e);
   }
}

void DefaultListSelectionModel::updateMinMax(void)
{
	if (!_RangeSelectionList.empty())
	{
		_MinSelectionIndex = _RangeSelectionList.front().StartIndex;
		_MaxSelectionIndex = _RangeSelectionList.front().EndIndex;
		RangeSelectionListConstItor ListItor;
		for (ListItor = _RangeSelectionList.begin() ; ListItor != _RangeSelectionList.end() ; ++ListItor )
		{
			if (_MinSelectionIndex > (*ListItor).StartIndex)
				_MinSelectionIndex = (*ListItor).StartIndex;
			if (_MaxSelectionIndex < (*ListItor).EndIndex)
				_MaxSelectionIndex = (*ListItor).EndIndex;
		}
	}
	else
	{
		_MaxSelectionIndex = _MinSelectionIndex = 0;
	}
}

DefaultListSelectionModel::IndexRange DefaultListSelectionModel::getMinMaxSelection(const IndexRange& range1, const IndexRange& range2)
{
	IndexRange range(0,0);
	if (range1.StartIndex > range2.StartIndex)
		range.StartIndex = range2.StartIndex;
	else
		range.StartIndex = range1.StartIndex;
	if (range1.EndIndex < range2.EndIndex)
		range.EndIndex = range2.EndIndex;
	else
		range.EndIndex = range1.EndIndex;
	return range;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListSelectionModel::DefaultListSelectionModel(void) :
_SelectionMode(SINGLE_SELECTION)
{
	_AnchorSelectionIndex = -1;
	_LeadSelectionIndex = -1;
	_MaxSelectionIndex = -1;
	_MinSelectionIndex = -1;
	_ValueIsAdjusting = false;
}

DefaultListSelectionModel::~DefaultListSelectionModel(void)
{
}

OSG_END_NAMESPACE


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
	IndexRange range(index0, index1);
   //TODO:Implement
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
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
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
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
   //TODO:Implement
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			break;
		case SINGLE_INTERVAL_SELECTION:
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			break;
		default:
			break;
	}
}

void 	DefaultListSelectionModel::removeSelectionInterval(UInt32 index0, UInt32 index1)
{
   //TODO:Implement
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			break;
		case SINGLE_INTERVAL_SELECTION:
			break;
		case MULTIPLE_INTERVAL_SELECTION:
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
			break;
		case SINGLE_INTERVAL_SELECTION:
			break;
		case MULTIPLE_INTERVAL_SELECTION:
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
			break;
		case SINGLE_INTERVAL_SELECTION:
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			break;
		default:
			break;
	}
}

void 	DefaultListSelectionModel::setSelectionInterval(UInt32 index0, UInt32 index1)
{
    // first deselect the current selection

	// now select the new selection

	IndexRange range(index0, index1);
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
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
		case MULTIPLE_INTERVAL_SELECTION:
			break;
		default:
			break;
	}
}

void 	DefaultListSelectionModel::setSelectionMode(UInt32 selectionMode)
{
	_SelectionMode = static_cast<SelectionMode>(selectionMode);
	switch (_SelectionMode)
	{
		case SINGLE_SELECTION:
			break;
		case SINGLE_INTERVAL_SELECTION:
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			break;
		default:
			break;
	}
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


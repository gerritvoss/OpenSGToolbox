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

#include "OSGDefaultListSelectionModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultListSelectionModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultListSelectionModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultListSelectionModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


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
	if (index0 >= 0 && index1 >= 0)
	{
        bool ShouldProduceSelectionChangeEvent(false);
        std::vector<UInt32> PrevSelectedIndexes(getSelectedIndexes());
	    IndexRange changedRange(index0, index1);
		switch (getSelectionMode())
		{
			case SINGLE_SELECTION:
				// you can only select one, so choose the second because the first is often the anchor
				range.StartIndex = range.EndIndex;
				if (_RangeSelectionList.empty())
				{   // if it's empty, then you only have to push onto the list
					_RangeSelectionList.push_back(range);
					// the only objects changed is in the range itself
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = range;
				}
				else if (_RangeSelectionList.front() != range) // if the new range is the same as the first one, then nothing has to be done
				{
					// this is necessary to make sure that the entire range is noted as changed for later
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), range));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(range);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = minMax;
				}
				break;
			case SINGLE_INTERVAL_SELECTION:
				// this is where newRange gets switched if it is necessary
				if (range.EndIndex < range.StartIndex)
				{
					newRange.EndIndex = range.StartIndex;
					newRange.StartIndex = range.EndIndex;
				}
				if (_RangeSelectionList.empty())
				{
					// if it is empty, then the new range merely needs to be pushed onto the list
					_RangeSelectionList.push_back(newRange);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = newRange;
				}
				else if (_RangeSelectionList.front() != newRange)
				{
					// this is necessary to make sure that the entire range is noted as changed for later
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), newRange));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(newRange);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = minMax;
				}
				break;
			case MULTIPLE_INTERVAL_SELECTION:
				// at this moment, you can only add single intervals, and it is the leading not the anchor index
				//if (!isSelectedIndex(index1))
				//{
					_RangeSelectionList.push_back(range);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = range;
				//}
				break;
			default:
				break;
		}
		// update indices
		_AnchorSelectionIndex = range.StartIndex;
		_LeadSelectionIndex = range.EndIndex;
		updateMinMax();
        if(ShouldProduceSelectionChangeEvent)
        {
            std::vector<UInt32> SelectedIndexes(getSelectedIndexes());
		    ListSelectionEventDetailsUnrecPtr TheListSelectionEvent = ListSelectionEventDetails::create(this, getSystemTime(), changedRange.StartIndex, changedRange.EndIndex, SelectedIndexes, PrevSelectedIndexes, _ValueIsAdjusting);
            produceSelectionChanged(TheListSelectionEvent);
        }
	}
}

void 	DefaultListSelectionModel::clearSelection(void)
{
    std::vector<UInt32> PrevSelectedIndexes(getSelectedIndexes());
	_RangeSelectionList.clear();
    updateMinMax();
    _AnchorSelectionIndex = _LeadSelectionIndex = -1;
    std::vector<UInt32> SelectedIndexes(getSelectedIndexes());
    ListSelectionEventDetailsUnrecPtr Details(ListSelectionEventDetails::create(this, getSystemTime(), _MinSelectionIndex, _MaxSelectionIndex, SelectedIndexes, PrevSelectedIndexes, _ValueIsAdjusting));
    produceSelectionChanged(Details);
}

Int32 	DefaultListSelectionModel::getAnchorSelectionIndex(void) const
{
   return _AnchorSelectionIndex;
}

Int32 	DefaultListSelectionModel::getLeadSelectionIndex(void) const
{
   return _LeadSelectionIndex;
}

Int32 	DefaultListSelectionModel::getMaxSelectionIndex(void) const
{
   return _MaxSelectionIndex;
}

Int32 	DefaultListSelectionModel::getMinSelectionIndex(void) const
{
   return _MinSelectionIndex;
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
	switch (getSelectionMode())
	{
		case SINGLE_SELECTION:
			if (before)
				range.StartIndex = range.EndIndex;
			else
				range.EndIndex = range.StartIndex;
			if (_RangeSelectionList.empty())
			{
                std::vector<UInt32> PrevSelectedIndexes(getSelectedIndexes());
				_RangeSelectionList.push_back(range);
                std::vector<UInt32> SelectedIndexes(getSelectedIndexes());
                ListSelectionEventDetailsUnrecPtr Details(ListSelectionEventDetails::create(this, getSystemTime(), range.StartIndex, range.EndIndex, SelectedIndexes, PrevSelectedIndexes, _ValueIsAdjusting));
                produceSelectionChanged(Details);
			}
			else if (_RangeSelectionList.front() != range)
			{
                std::vector<UInt32> PrevSelectedIndexes(getSelectedIndexes());
				IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), range));
				_RangeSelectionList.clear();
				_RangeSelectionList.push_back(range);
				updateMinMax();
                std::vector<UInt32> SelectedIndexes(getSelectedIndexes());
                ListSelectionEventDetailsUnrecPtr Details(ListSelectionEventDetails::create(this, getSystemTime(), minMax.StartIndex, minMax.EndIndex, SelectedIndexes, PrevSelectedIndexes, _ValueIsAdjusting));
                produceSelectionChanged(Details);
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
		}
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
	IndexRange range(index0, index1);
    bool ShouldProduceSelectionChangeEvent(false);
    std::vector<UInt32> PrevSelectedIndexes(getSelectedIndexes());
    IndexRange changedRange(index0, index1);
	switch (getSelectionMode())
	{
		case SINGLE_INTERVAL_SELECTION:
		case SINGLE_SELECTION:
			// presently, these two options merely removes the existing range
			if (!_RangeSelectionList.empty())
			{   // only necessary to do anything if it isn't already empty
				range = _RangeSelectionList.front();
				_RangeSelectionList.clear();
                ShouldProduceSelectionChangeEvent = true;
                changedRange = range;
			}
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			// presently this only works for intervals of length 1
			index0 = index1;
			for(ListItor = _RangeSelectionList.begin() ; ListItor != _RangeSelectionList.end() ; ++ListItor )
			{
				if(index1 >= (*ListItor).StartIndex && index1 <= (*ListItor).EndIndex)
				{
					if (index1 == (*ListItor).StartIndex)
						++(*ListItor).StartIndex;
					else if (index1 == (*ListItor).EndIndex)
						--(*ListItor).EndIndex;
					else
					{
						_RangeSelectionList.push_back(IndexRange(index1 + 1, (*ListItor).EndIndex));
						(*ListItor).EndIndex = index1 - 1;
					}
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange.StartIndex = changedRange.EndIndex = index1;
				}
			}
			break;
		default:
			break;
	}
	_AnchorSelectionIndex = index0;
	_LeadSelectionIndex = index1;
	updateMinMax();
    if(ShouldProduceSelectionChangeEvent)
    {
        std::vector<UInt32> SelectedIndexes(getSelectedIndexes());
        ListSelectionEventDetailsUnrecPtr TheListSelectionEvent = ListSelectionEventDetails::create(this, getSystemTime(), changedRange.StartIndex, changedRange.EndIndex, SelectedIndexes, PrevSelectedIndexes, _ValueIsAdjusting);
        produceSelectionChanged(TheListSelectionEvent);
    }
}

void 	DefaultListSelectionModel::removeSelectionInterval(UInt32 index0, UInt32 index1)
{
	switch (getSelectionMode())
	{
		case SINGLE_INTERVAL_SELECTION:
		case SINGLE_SELECTION:
			// presently, these two options merely removes the existing range if there is something there
			if (!_RangeSelectionList.empty())
			{
                std::vector<UInt32> PrevSelectedIndexes(getSelectedIndexes());
			    if (index1 < index0)
			    {
				    UInt32 temp(index0);
				    index0 = index1;
				    index1 = temp;
			    }
                // only necessary to do anything if it isn't already empty
				IndexRange range( _RangeSelectionList.front());
				if (isSelectedIndex(index0))
                {
				    _RangeSelectionList.clear();
                }
                else
                {
				    _RangeSelectionList.clear();
                    IndexRange range(index0, index0);
                    _RangeSelectionList.push_back(range);
                }
				updateMinMax();
                std::vector<UInt32> SelectedIndexes(getSelectedIndexes());
                ListSelectionEventDetailsUnrecPtr Details(ListSelectionEventDetails::create(this, getSystemTime(), osgMin(index0,range.StartIndex), osgMax(index0,range.EndIndex), SelectedIndexes, PrevSelectedIndexes, _ValueIsAdjusting));
                produceSelectionChanged(Details);
			}
			else
			{
				setSelectionInterval(index0, index1);
			}
			break;
		case MULTIPLE_INTERVAL_SELECTION:
			// basically, this toggles all of them across the interval
			if (index1 < index0)
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
	switch (getSelectionMode())
	{
		case SINGLE_SELECTION:
			// in SINGLE_SELECTION, the anchor and lead are always forced to be the same
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
	switch (getSelectionMode())
	{
		case SINGLE_SELECTION:
			// in SINGLE_SELECTION, the anchor and lead are always forced to be the same
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
	if (index0 >= 0 && index1 >= 0) // anchor and lead are initiated to -1
	{
        bool ShouldProduceSelectionChangeEvent(false);
        std::vector<UInt32> PrevSelectedIndexes(getSelectedIndexes());
        IndexRange changedRange(index0, index1);
		switch (getSelectionMode())
		{
			case SINGLE_SELECTION:
				// for single selection, setting and adding intervals are the same thing
				range.StartIndex = range.EndIndex;
				if (_RangeSelectionList.empty())
				{
					_RangeSelectionList.push_back(range);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = range;
				}
				else if (_RangeSelectionList.front() != range)
				{
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), range));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(range);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = minMax;
				}
				break;
			case MULTIPLE_INTERVAL_SELECTION:
			case SINGLE_INTERVAL_SELECTION:
				// when setting the interval, MULTIPLE_INTERVAL_SELECTION and SINGLE_INTERVAL_SELECTION
				// do the same thing, which replaces everything 
				if (range.EndIndex < range.StartIndex)
				{
					newRange.EndIndex = range.StartIndex;
					newRange.StartIndex = range.EndIndex;
				}
				if (_RangeSelectionList.empty())
				{
					_RangeSelectionList.push_back(newRange);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = newRange;
				}
				else if (_RangeSelectionList.front() != newRange)
				{
					// updateMinMax is necessary for the MULTIPLE_INTERVAL_SELECTION, since there
					// might be some selected outside of any range
					IndexRange minMax(getMinMaxSelection(_RangeSelectionList.front(), newRange));
					updateMinMax();
					minMax = getMinMaxSelection(minMax, IndexRange(_MinSelectionIndex, _MaxSelectionIndex));
					_RangeSelectionList.clear();
					_RangeSelectionList.push_back(newRange);
                    ShouldProduceSelectionChangeEvent = true;
                    changedRange = minMax;
				}
				break;
			default:
				break;
		}
		// update indices
		_AnchorSelectionIndex = index0;
		_LeadSelectionIndex = index1;
		updateMinMax();
        if(ShouldProduceSelectionChangeEvent)
        {
            std::vector<UInt32> SelectedIndexes(getSelectedIndexes());
            ListSelectionEventDetailsUnrecPtr TheListSelectionEvent = ListSelectionEventDetails::create(this, getSystemTime(), changedRange.StartIndex, changedRange.EndIndex, SelectedIndexes, PrevSelectedIndexes, _ValueIsAdjusting);
            produceSelectionChanged(TheListSelectionEvent);
        }
	}
}

void 	DefaultListSelectionModel::setValueIsAdjusting(bool valueIsAdjusting)
{
   _ValueIsAdjusting = valueIsAdjusting;
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
		// in the event of _RangeSelectionList being empty, just set
		// them both to zero
		_MaxSelectionIndex = _MinSelectionIndex = -1;
	}
}

DefaultListSelectionModel::IndexRange DefaultListSelectionModel::getMinMaxSelection(const IndexRange& range1, const IndexRange& range2)
{
	// this function returns a range that has the minimum of the
	// two ranges and the maximum of the two ranges
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

void DefaultListSelectionModel::incrementValuesAboveIndex(const UInt32& index, const UInt32& NumberToIncrement)
{
	RangeSelectionListItor ListItor(_RangeSelectionList.begin());

	for(ListItor ; ListItor != _RangeSelectionList.end() ; ++ListItor)
	{
		if(ListItor->StartIndex >= index)
		{
			ListItor->StartIndex += NumberToIncrement;
			ListItor->EndIndex += NumberToIncrement;
		}
		else if(ListItor->EndIndex >= index)
		{
			assert(false);
		}
	}
}

void DefaultListSelectionModel::decrementValuesAboveIndex(const UInt32& index, const UInt32& NumberToDecrement)
{
	RangeSelectionListItor ListItor(_RangeSelectionList.begin());

	for(ListItor ; ListItor != _RangeSelectionList.end() ; ++ListItor)
	{
		if(ListItor->StartIndex > index)
		{
			ListItor->StartIndex -= NumberToDecrement;
			ListItor->EndIndex -= NumberToDecrement;
		}
		else if(ListItor->EndIndex > index)
		{
			assert(false);
		}
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListSelectionModel::DefaultListSelectionModel(void) :
    Inherited(),
    _AnchorSelectionIndex(-1),
    _LeadSelectionIndex(-1),
    _MaxSelectionIndex(-1),
    _MinSelectionIndex(-1),
    _ValueIsAdjusting(false)
{
}

DefaultListSelectionModel::DefaultListSelectionModel(const DefaultListSelectionModel &source) :
    Inherited(source),
    _AnchorSelectionIndex(source._AnchorSelectionIndex),
    _LeadSelectionIndex(source._LeadSelectionIndex),
    _MaxSelectionIndex(source._MaxSelectionIndex),
    _MinSelectionIndex(source._MinSelectionIndex),
    _ValueIsAdjusting(false)
{
}

DefaultListSelectionModel::~DefaultListSelectionModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultListSelectionModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & SelectionModeFieldMask)
    {
		switch (getSelectionMode())
		{
			case SINGLE_SELECTION:
                if(getMinSelectionIndex() != -1)
                {
                    setSelectionInterval(getMinSelectionIndex(),getMinSelectionIndex());
                }
                break;
			case SINGLE_INTERVAL_SELECTION:
                if(getMinSelectionIndex() != -1)
                {
                    setSelectionInterval(getMinSelectionIndex(),getMinSelectionIndex());
                }
                break;
			case MULTIPLE_INTERVAL_SELECTION:
                //No need to do anything
                break;
        }
    }
}

void DefaultListSelectionModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultListSelectionModel NI" << std::endl;
}

DefaultListSelectionModel::IndexRange::IndexRange(UInt32 start, UInt32 end)
{
    if(start > end)
    {
	    StartIndex = end;
	    EndIndex = start;
    }
    else
    {
	    StartIndex = start;
	    EndIndex = end;
    }
}

OSG_END_NAMESPACE

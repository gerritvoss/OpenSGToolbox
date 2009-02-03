/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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
#include "OSGNumberRangeSet.h"

#include <OpenSG/OSGBaseFunctions.h>
#include <iostream>

OSG_BEGIN_NAMESPACE

NumberRange::NumberRange(void) : _Min(0), _Max(0), _IsEmpty(true)
{
}

NumberRange::NumberRange(Int32 start, Int32 end) : _IsEmpty(false)
{
    if(start > end)
    {
	    _Min = end;
	    _Max = start;
    }
    else
    {
	    _Min = start;
	    _Max = end;
    }
}


NumberRange::NumberRange(const NumberRange& r) : _Min(r._Min), _Max(r._Max), _IsEmpty(r._IsEmpty)
{
}

bool NumberRange::operator== (const NumberRange& right) const
{
    if(_IsEmpty && right._IsEmpty)
    {
        return true;
    }
    else if((_IsEmpty && !right._IsEmpty) || (!_IsEmpty && right._IsEmpty))
    {
        return false;
    }
    else
    {
    	return _Min == right._Min && _Max == right._Max;
    }
}

void NumberRange::setMin(Int32 Min)
{
    _Min = Min;
    _IsEmpty = false;
}

void NumberRange::setMax(Int32 Max)
{
    _Max = Max;
    _IsEmpty = false;
}

void NumberRange::setValues(Int32 Min, Int32 Max)
{
    _Min = Min;
    _Max = Max;
    _IsEmpty = false;
}

UInt32 NumberRange::size(void) const
{
    if(_IsEmpty)
    {
        return 0;
    }
    else
    {
        return _Max - _Min + 1;
    }
}

bool NumberRange::isContained(Int32 value) const
{
    if(_IsEmpty)
    {
        return false;
    }
    else
    {
        return (value >= _Min && value <= _Max);
    }
}

NumberRange intersection(const NumberRange& left, const NumberRange& right)
{
    NumberRange Result;

    if(right.getMin() >= left.getMin() &&
       right.getMin() <= left.getMax())
    {
        Result.setMin(right.getMin());
    }
    else if(left.getMin() >= right.getMin() &&
       left.getMin() <= right.getMax())
    {
        Result.setMin(left.getMin());
    }
    if(right.getMax() >= left.getMin() &&
       right.getMax() <= left.getMax())
    {
        Result.setMax(right.getMax());
    }
    else if(left.getMax() >= right.getMin() &&
       left.getMax() <= right.getMax())
    {
        Result.setMax(left.getMax());
    }
    return Result;
}


NumberRange getMinMax(const NumberRange& range1, const NumberRange& range2)
{
	// this function returns a range that has the minimum of the
	// two ranges and the maximum of the two ranges
	NumberRange range;
	if (range1.getMin() > range2.getMin() && !range2.isEmpty())
		range.setMin(range2.getMin());
	else if(!range1.isEmpty())
		range.setMin(range1.getMin());
	if (range1.getMax() < range2.getMax() && !range2.isEmpty())
		range.setMax(range2.getMax());
	else if(!range1.isEmpty())
		range.setMax(range1.getMax());
	return range;
}

NumberSet::NumberSet(void)
{
}

NumberSet::NumberSet(const NumberSet& c) : _List(c._List)
{
}

bool NumberSet::getMin(Int32& Min) const
{
    if(!_List.empty())
    {
		Min = _List.front().getMin();
		RangeListTypeConstItor ListItor;
		for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
		{
			if (Min > (*ListItor).getMin())
				Min = (*ListItor).getMin();
		}
        return true;
    }
    else
    {
        return false;
    }
}

bool NumberSet::getMax(Int32& Max) const
{
    if(!_List.empty())
    {
		Max = _List.front().getMax();
		RangeListTypeConstItor ListItor;
		for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
		{
			if (Max < (*ListItor).getMax())
				Max = (*ListItor).getMax();
		}
        return true;
    }
    else
    {
        return false;
    }
}

bool NumberSet::getMinMax(Int32& Min, Int32& Max) const
{
    if(!_List.empty())
    {
		Min = _List.front().getMin();
		Max = _List.front().getMax();
		RangeListTypeConstItor ListItor;
		for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
		{
			if (Min > (*ListItor).getMin())
				Min = (*ListItor).getMin();
			if (Max < (*ListItor).getMax())
				Max = (*ListItor).getMax();
		}
        return true;
    }
    else
    {
        return false;
    }
}

bool NumberSet::isNonNegative(void) const
{
    if(isEmpty())
    {
        return true;
    }
    else
    {
        return _List.front().getMin() >= 0;
    }
}

bool NumberSet::addRange(NumberRange r)
{
    if(isRangeContained(r))
    {
        return false;
    }
    else if(isEmpty())
    {
        _List.push_back(r);
        collapseIntersectingRanges();
        return true;
    }
    else if(!r.isEmpty())
    {
	    RangeListTypeItor ListItor;
	    for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
	    {
            //Does the range straggle over it
            if(r.getMin() < ListItor->getMin() &&
                r.getMax() > ListItor->getMax())
            {
                //Then replace the Min and max of this range
                ListItor->setMin(r.getMin());
                ListItor->setMax(r.getMax());

                //Collapse any intersecting ranges that may result
                collapseIntersectingRanges();
                return true;
            }

            //Does this range strattle it over the front
            if(r.getMin() < ListItor->getMin() &&
               r.getMax() >= ListItor->getMin()-1 &&
               r.getMax() <= ListItor->getMax())
            {
                //Then replace the Min and max of this range
                ListItor->setMin(r.getMin());

                //Collapse any intersecting ranges that may result
                collapseIntersectingRanges();
                return true;
            }

            //Does this range straggle it over the end
            if(r.getMax() > ListItor->getMax() &&
               r.getMin() >= ListItor->getMin() &&
               r.getMin() <= ListItor->getMax()+1)
            {
                //Then replace the Min and max of this range
                ListItor->setMax(r.getMax());

                //Collapse any intersecting ranges that may result
                collapseIntersectingRanges();
                return true;
            }

            //Range is between two ranges
            if(r.getMax() < ListItor->getMin())
            {
                break;
            }
	    }
        //Insert this range before this ListItor
        _List.insert(ListItor,r);
    }
    return true;
}

bool NumberSet::isEmpty(void) const
{
    RangeListTypeConstItor ListItor;
    for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
    {
        if(!ListItor->isEmpty())
        {
            return false;
        }
    }
    return true;
}

bool NumberSet::isContained(Int32 value) const
{
	RangeListTypeConstItor ListItor;
	for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
	{
		if (ListItor->isContained(value))
        {
            return true;
        }
	}
    return false;
}

UInt32 NumberSet::size(void) const
{
    UInt32 Size(0);

	RangeListTypeConstItor ListItor;
	for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
	{
        Size += ListItor->size();
    }

    return Size;
}

bool NumberSet::isRangeContained(const NumberRange& r) const
{
    if(r.isEmpty())
    {
        return true;
    }

	RangeListTypeConstItor ListItor;
	for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
	{
		if (r.getMin() >= ListItor->getMin() &&
            r.getMax() <= ListItor->getMax())
        {
            return true;
        }
	}
    return false;
}

bool NumberSet::isIntersectionEmpty(const NumberRange& r) const
{
	RangeListTypeConstItor ListItor;
	for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
	{
		if (r.getMin() >= ListItor->getMin() ||
            r.getMax() <= ListItor->getMax())
        {
            return false;
        }
	}
    return true;
}

void NumberSet::collapseIntersectingRanges(void)
{
    if(_List.size() < 2)
    {
        //No collapsing possible
        return;
    }
    
    RangeListTypeItor ListItor,NextListItor;
    ListItor = _List.begin();
    NextListItor = ++_List.begin();
    while (NextListItor != _List.end())
    {
        if(ListItor->getMax() >= NextListItor->getMin())
        {
            NextListItor->setMin(osgMin(ListItor->getMin(), NextListItor->getMin()));
            NextListItor->setMax(osgMax(ListItor->getMax(), NextListItor->getMax()));
            _List.erase(ListItor);
        }
        else if(ListItor->isEmpty())
        {
            _List.erase(ListItor);
        }
        ListItor = NextListItor;
        ++NextListItor;
    }
}

std::vector<NumberRange> NumberSet::getIntersection(const NumberRange& r) const
{
    std::vector<NumberRange> Result;
	RangeListTypeConstItor ListItor;
	
    NumberRange Intersection(0,0);
    for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
	{
        Intersection = intersection( (*ListItor),r);
        if(!Intersection.isEmpty())
        {
            Result.push_back(Intersection);
        }
    }
    return Result;
}

void NumberSet::print(void) const
{
	RangeListTypeConstItor ListItor;
    for (ListItor = _List.begin() ; ListItor != _List.end() ; ++ListItor )
	{
        std::cout << "   " << ListItor->getMin() << " - " << ListItor->getMax() << std::endl;
    }
}

NumberSet intersection_NumberSet(const NumberRange& left, const NumberRange& right)
{
    NumberSet Result;
    Result.addRange(intersection(left,right));

    return Result;
}

NumberSet union_NumberSet(const NumberRange& left, const NumberRange& right)
{
    NumberSet Result;
    Result.addRange(left);
    Result.addRange(right);

    return Result;
}

NumberSet difference_NumberSet(const NumberRange& left, const NumberRange& right)
{
    NumberSet Result;
    
    NumberRange MinRange, MaxRange;

    if(left.getMin() < right.getMin())
    {
        MinRange.setMin(left.getMin());
    }

    if(left.getMax() < right.getMin())
    {
        MinRange.setMax(left.getMax());
    }
    else if(left.isContained(right.getMin()-1))
    {
        MinRange.setMax(right.getMin()-1);
    }

    if(left.getMax() > right.getMax())
    {
        MaxRange.setMax(left.getMax());
    }

    if(left.getMin() > right.getMax())
    {
        MaxRange.setMin(left.getMin());
    }
    else if(left.isContained(right.getMax()+1))
    {
        MaxRange.setMin(right.getMax()+1);
    }

    if(MinRange.getMin() > MinRange.getMax())
    {
        MinRange.setEmpty();
    }
    if(MaxRange.getMin() > MaxRange.getMax())
    {
        MaxRange.setEmpty();
    }

    Result.addRange(MinRange);
    Result.addRange(MaxRange);

    return Result;
}

NumberSet intersection_NumberSet(const NumberSet& left, const NumberSet& right)
{
    NumberSet Result;
    NumberSet::RangeListTypeConstItor ListItor;
    for (ListItor = right._List.begin() ; ListItor != right._List.end() ; ++ListItor )
	{
        NumberSet Intersection = intersection_NumberSet(left,*ListItor);
        NumberSet::RangeListTypeConstItor InnerListItor;
        for (InnerListItor = Intersection._List.begin() ; InnerListItor != Intersection._List.end() ; ++InnerListItor )
	    {
            Result.addRange(*InnerListItor);
        }
    }
    return Result;
}

NumberSet union_NumberSet(const NumberSet& left, const NumberSet& right)
{
    NumberSet Result;
    
    NumberSet::RangeListTypeConstItor ListItor;
    for (ListItor = left._List.begin() ; ListItor != left._List.end() ; ++ListItor )
	{
        Result.addRange(*ListItor);
    }
    for (ListItor = right._List.begin() ; ListItor != right._List.end() ; ++ListItor )
	{
        Result.addRange(*ListItor);
    }

    return Result;
}

NumberSet difference_NumberSet(const NumberSet& left, const NumberSet& right)
{
    NumberSet Result(left);
    NumberSet::RangeListTypeConstItor ListItor;
    for (ListItor = right._List.begin() ; ListItor != right._List.end() ; ++ListItor )
	{
        Result = difference_NumberSet(Result,*ListItor);
    }
    return Result;
}

NumberSet intersection_NumberSet(const NumberSet& left, const NumberRange& right)
{
    NumberSet Result;

    NumberSet::RangeListTypeConstItor ListItor;
    for (ListItor = left._List.begin() ; ListItor != left._List.end() ; ++ListItor )
	{
        Result.addRange(intersection(*ListItor, right));
    }

    return Result;
}

NumberSet union_NumberSet(const NumberSet& left, const NumberRange& right)
{
    NumberSet Result(left);

    Result.addRange(right);

    return Result;
}

NumberSet difference_NumberSet(const NumberSet& left, const NumberRange& right)
{
    NumberSet Result;

    NumberSet::RangeListTypeConstItor ListItor;
    for (ListItor = left._List.begin() ; ListItor != left._List.end() ; ++ListItor )
	{
        NumberSet::RangeListTypeConstItor InnerListItor;
        NumberSet Diff = difference_NumberSet(*ListItor, right);
        for (InnerListItor = Diff._List.begin() ; InnerListItor != Diff._List.end() ; ++InnerListItor )
	    {
            Result.addRange(*InnerListItor);
        }
    }

    return Result;
}


OSG_END_NAMESPACE

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
#ifndef _OSG_UI_NUMBER_RANGE_SET_H_
#define _OSG_UI_NUMBER_RANGE_SET_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <list>
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING NumberRange
{  //Inclusive
public:
	NumberRange(Int32 start, Int32 end);
	NumberRange(const NumberRange& r);
	NumberRange(void);

    Int32 getMin(void) const;
    Int32 getMax(void) const;
    UInt32 size(void) const;
    bool isEmpty(void) const;
    void setEmpty(void);
    void setMin(Int32 Min);
    void setMax(Int32 Max);
    void setValues(Int32 Min, Int32 Max);

    bool isContained(Int32 value) const;

	bool operator== (const NumberRange& right) const;

	bool operator!= (const NumberRange& right) const;
    
private:
	Int32 _Min;
	Int32 _Max;
    bool _IsEmpty;
};

NumberRange OSG_USERINTERFACELIB_DLLMAPPING intersection(const NumberRange& left, const NumberRange& right);
NumberRange OSG_USERINTERFACELIB_DLLMAPPING getMinMax(const NumberRange& range1, const NumberRange& range2);

class OSG_USERINTERFACELIB_DLLMAPPING NumberSet
{
public:
	typedef std::list<NumberRange> RangeListType;
	typedef RangeListType::iterator RangeListTypeItor;
	typedef RangeListType::const_iterator RangeListTypeConstItor;
    
    NumberSet(void);
    NumberSet(const NumberSet& c);

    bool getMin(Int32& Min) const;
    bool getMax(Int32& Max) const;
    bool getMinMax(Int32& Min, Int32& Max) const;

    NumberRange front(void) const;
    NumberRange back(void) const;

    RangeListTypeConstItor begin(void) const;
    RangeListTypeConstItor end(void) const;

    bool isContained(Int32 value) const;
    bool isNonNegative(void) const;
    void clear(void);
    UInt32 size(void) const;
    bool isEmpty(void) const;

    bool addRange(NumberRange r);

    bool isRangeContained(const NumberRange& r) const;
    bool isIntersectionEmpty(const NumberRange& r) const;

    //std::vector<NumberRange> getUnion(const NumberRange& r) const;
    std::vector<NumberRange> getIntersection(const NumberRange& r) const;

    void print(void) const;
    friend NumberSet OSG_USERINTERFACELIB_DLLMAPPING intersection_NumberSet(const NumberSet& left, const NumberSet& right);
    friend NumberSet OSG_USERINTERFACELIB_DLLMAPPING union_NumberSet(const NumberSet& left, const NumberSet& right);
    friend NumberSet OSG_USERINTERFACELIB_DLLMAPPING difference_NumberSet(const NumberSet& left, const NumberSet& right);
    
    friend NumberSet OSG_USERINTERFACELIB_DLLMAPPING intersection_NumberSet(const NumberSet& left, const NumberRange& right);
    friend NumberSet OSG_USERINTERFACELIB_DLLMAPPING union_NumberSet(const NumberSet& left, const NumberRange& right);
    friend NumberSet OSG_USERINTERFACELIB_DLLMAPPING difference_NumberSet(const NumberSet& left, const NumberRange& right);


private:
    RangeListType _List;

    void collapseIntersectingRanges(void);
};


NumberSet OSG_USERINTERFACELIB_DLLMAPPING intersection_NumberSet(const NumberRange& left, const NumberRange& right);
NumberSet OSG_USERINTERFACELIB_DLLMAPPING union_NumberSet(const NumberRange& left, const NumberRange& right);
NumberSet OSG_USERINTERFACELIB_DLLMAPPING difference_NumberSet(const NumberRange& left, const NumberRange& right);

NumberSet OSG_USERINTERFACELIB_DLLMAPPING intersection_NumberSet(const NumberSet& left, const NumberSet& right);
NumberSet OSG_USERINTERFACELIB_DLLMAPPING union_NumberSet(const NumberSet& left, const NumberSet& right);
NumberSet OSG_USERINTERFACELIB_DLLMAPPING difference_NumberSet(const NumberSet& left, const NumberSet& right);

NumberSet OSG_USERINTERFACELIB_DLLMAPPING intersection_NumberSet(const NumberSet& left, const NumberRange& right);
NumberSet OSG_USERINTERFACELIB_DLLMAPPING union_NumberSet(const NumberSet& left, const NumberRange& right);
NumberSet OSG_USERINTERFACELIB_DLLMAPPING difference_NumberSet(const NumberSet& left, const NumberRange& right);

	
OSG_END_NAMESPACE

#include "OSGNumberRangeSet.inl"

#endif /* _OSG_UI_NUMBER_RANGE_SET_H_ */

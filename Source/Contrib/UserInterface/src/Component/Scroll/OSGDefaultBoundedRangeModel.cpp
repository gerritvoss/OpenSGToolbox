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

#include "OSGDefaultBoundedRangeModel.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultBoundedRangeModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultBoundedRangeModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultBoundedRangeModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 DefaultBoundedRangeModel::getExtent(void) const
{
    return getInternalExtent();
}

Int32 DefaultBoundedRangeModel::getMaximum(void) const
{
    return getInternalMaximum();
}

Int32 DefaultBoundedRangeModel::getMinimum(void) const
{
    return getInternalMinimum();
}

Int32 DefaultBoundedRangeModel::getValue(void) const
{
    return getInternalValue();
}

bool DefaultBoundedRangeModel::getValueIsAdjusting(void) const
{
    return getInternalValueIsAdjusting();
}

void DefaultBoundedRangeModel::setExtent(UInt32 newExtent)
{
    if(getInternalExtent() != newExtent)
    {
        setInternalExtent(newExtent);
    }
    if(getInternalValue() + static_cast<Int32>(getInternalExtent()) > getInternalMaximum())
    {
        setInternalValue(getInternalMaximum() - getInternalExtent());
    }
}

void DefaultBoundedRangeModel::setMaximum(Int32 newMaximum)
{
    if(getInternalMaximum() != newMaximum);
    {
        setInternalMaximum(newMaximum);
    }
    if(getInternalValue() + static_cast<Int32>(getInternalExtent()) > getInternalMaximum())
    {
        setInternalValue(getInternalMaximum() - getInternalExtent());
    }
}

void DefaultBoundedRangeModel::setMinimum(Int32 newMinimum)
{
    if(getInternalMinimum() != newMinimum)
    {
        setInternalMinimum(newMinimum);
    }
    if(getInternalValue() < getInternalMinimum())
    {
        setInternalValue(getInternalMinimum());
    }
}

void DefaultBoundedRangeModel::setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting)
{
    if(getInternalExtent() != extent ||
       getInternalMaximum() != max ||
       getInternalMinimum() != min ||
       getInternalValue() != value ||
       getInternalValueIsAdjusting() != adjusting)
    {

        setInternalExtent(extent);
        setInternalMaximum(max);
        setInternalMinimum(min);
        setInternalValueIsAdjusting(adjusting);
        if(value + static_cast<Int32>(getInternalExtent()) > getInternalMaximum() && getInternalExtent() < getInternalMaximum() - getInternalMinimum())
        {
            setInternalValue( getInternalMaximum() - getInternalExtent());
        }
        else if(value < getInternalMinimum())
        {
            setInternalValue(getInternalMinimum());
        }
        else
        {
            setInternalValue(value);
        }
    }
}

void DefaultBoundedRangeModel::setValue(Int32 newValue)
{
    if(getInternalValue() != newValue)
    {
        if(newValue + static_cast<Int32>(getInternalExtent()) > getInternalMaximum())
        {
            setInternalValue(getInternalMaximum() - getInternalExtent());
        }
        else if(newValue < getInternalMinimum())
        {
            setInternalValue(getInternalMinimum());
        }
        else
        {
            setInternalValue(newValue);
        }
    }
}

void DefaultBoundedRangeModel::setValueIsAdjusting(bool b)
{
    if(getInternalValueIsAdjusting() != b)
    {
        setInternalValueIsAdjusting(b);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void DefaultBoundedRangeModel::produceStateChanged(ChangeEventDetails* const Details)
{
   Inherited::produceStateChanged(Details);
}

/*----------------------- constructors & destructors ----------------------*/

DefaultBoundedRangeModel::DefaultBoundedRangeModel(void) :
    Inherited()
{
}

DefaultBoundedRangeModel::DefaultBoundedRangeModel(const DefaultBoundedRangeModel &source) :
    Inherited(source)
{
}

DefaultBoundedRangeModel::~DefaultBoundedRangeModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultBoundedRangeModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & InternalValueFieldMask) ||
       (whichField & InternalValueIsAdjustingFieldMask) ||
       (whichField & InternalMaximumFieldMask) ||
       (whichField & InternalMinimumFieldMask) ||
       (whichField & InternalExtentFieldMask))
    {
        ChangeEventDetailsUnrecPtr Details(ChangeEventDetails::create(NULL, getSystemTime()));
        produceStateChanged(Details);
    }
}

void DefaultBoundedRangeModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultBoundedRangeModel NI" << std::endl;
}

OSG_END_NAMESPACE

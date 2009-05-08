/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include "OSGDefaultBoundedRangeModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultBoundedRangeModel
A UI DefaultBoundedRangeModel. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultBoundedRangeModel::initMethod (void)
{
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
    bool isStateChange(getInternalExtent() != newExtent);
    beginEditCP(DefaultBoundedRangeModelPtr(this), InternalExtentFieldMask);
        setInternalExtent(newExtent);
    endEditCP(DefaultBoundedRangeModelPtr(this), InternalExtentFieldMask);

    if(getInternalValue() + static_cast<Int32>(getInternalExtent()) > getInternalMaximum())
    {
        beginEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
            setInternalValue(getInternalMaximum() - getInternalExtent());
        endEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
    }
    if(isStateChange)
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void DefaultBoundedRangeModel::setMaximum(Int32 newMaximum)
{
    bool isStateChange(getInternalMaximum() != newMaximum);
    beginEditCP(DefaultBoundedRangeModelPtr(this), InternalMaximumFieldMask);
        setInternalMaximum(newMaximum);
    endEditCP(DefaultBoundedRangeModelPtr(this), InternalMaximumFieldMask);
    if(getInternalValue() + static_cast<Int32>(getInternalExtent()) > getInternalMaximum())
    {
        beginEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
            setInternalValue(getInternalMaximum() - getInternalExtent());
        endEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
    }
    if(isStateChange)
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void DefaultBoundedRangeModel::setMinimum(Int32 newMinimum)
{
    bool isStateChange(getInternalMinimum() != newMinimum);
    beginEditCP(DefaultBoundedRangeModelPtr(this), InternalMinimumFieldMask);
        setInternalMinimum(newMinimum);
    endEditCP(DefaultBoundedRangeModelPtr(this), InternalMinimumFieldMask);
    if(getInternalValue() < getInternalMinimum())
    {
        beginEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
            setInternalValue(getInternalMinimum());
        endEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
    }
    if(isStateChange)
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void DefaultBoundedRangeModel::setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting)
{
    bool isStateChange(getInternalExtent() != extent ||
                       getInternalMaximum() != max ||
                       getInternalMinimum() != min ||
                       getInternalValue() != value ||
                       getInternalValueIsAdjusting() != adjusting);
    beginEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask | InternalExtentFieldMask | InternalMinimumFieldMask | InternalMaximumFieldMask | InternalValueIsAdjustingFieldMask);

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
    endEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask | InternalExtentFieldMask | InternalMinimumFieldMask | InternalMaximumFieldMask | InternalValueIsAdjustingFieldMask);
    if(isStateChange)
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void DefaultBoundedRangeModel::setValue(Int32 newValue)
{
    bool isStateChange(getInternalValue() != newValue);
    beginEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
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
    endEditCP(DefaultBoundedRangeModelPtr(this), InternalValueFieldMask);
    if(isStateChange)
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void DefaultBoundedRangeModel::setValueIsAdjusting(bool b)
{
    bool isStateChange(getInternalValueIsAdjusting() != b);
    beginEditCP(DefaultBoundedRangeModelPtr(this), InternalValueIsAdjustingFieldMask);
        setInternalValueIsAdjusting(b);
    endEditCP(DefaultBoundedRangeModelPtr(this), InternalValueIsAdjustingFieldMask);
    if(isStateChange)
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

EventConnection DefaultBoundedRangeModel::addChangeListener(ChangeListenerPtr Listener)
{
   _ChangeListeners.insert(Listener);
   return EventConnection(
       boost::bind(&DefaultBoundedRangeModel::isChangeListenerAttached, this, Listener),
       boost::bind(&DefaultBoundedRangeModel::removeChangeListener, this, Listener));
}

bool DefaultBoundedRangeModel::isChangeListenerAttached(ChangeListenerPtr Listener) const
{
    return _ChangeListeners.find(Listener) != _ChangeListeners.end();
}

void DefaultBoundedRangeModel::removeChangeListener(ChangeListenerPtr Listener)
{
   ChangeListenerSetItor EraseIter(_ChangeListeners.find(Listener));
   if(EraseIter != _ChangeListeners.end())
   {
      _ChangeListeners.erase(EraseIter);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void DefaultBoundedRangeModel::produceStateChanged(const ChangeEvent& e)
{
   ChangeListenerSet ModelListenerSet(_ChangeListeners);
   for(ChangeListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
	   (*SetItor)->stateChanged(e);
   }
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

void DefaultBoundedRangeModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultBoundedRangeModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultBoundedRangeModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTBOUNDEDRANGEMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTBOUNDEDRANGEMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTBOUNDEDRANGEMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


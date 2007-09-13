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

#ifndef _OSG_UI_DEFAULT_BOUNDEDRANGE_MODEL_H_
#define _OSG_UI_DEFAULT_BOUNDEDRANGE_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGBoundedRangeModel.h"
#include "Event/OSGChangeListener.h"
#include <set>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING DefaultBoundedRangeModel : public BoundedRangeModel
{
private:
protected:
    UInt32 _Extent;
    Int32 _Maximum;
    Int32 _Minimum;
    Int32 _Value;
    bool _ValueIsAdjusting;

    
	typedef std::set<ChangeListenerPtr> ChangeListenerSet;
    typedef ChangeListenerSet::iterator ChangeListenerSetItor;
    typedef ChangeListenerSet::const_iterator ChangeListenerSetConstItor;
	
    ChangeListenerSet       _ChangeListeners;
    void produceStateChanged(const ChangeEvent& e);
public:
    //Returns the model's extent, the length of the inner range that begins at the model's value.
    virtual UInt32 getExtent(void) const;
    
    //Returns the model's maximum.
    virtual Int32 getMaximum(void) const;
    
    //Returns the minimum acceptable value.
    virtual Int32 getMinimum(void) const;
    
    //Returns the model's current value.
    virtual Int32 getValue(void) const;
    
    //Returns true if the current changes to the value property are part of a series of changes.
    virtual bool getValueIsAdjusting(void) const;
    
    //Sets the model's extent.
    virtual void setExtent(UInt32 newExtent);
    
    //Sets the model's maximum to newMaximum.
    virtual void setMaximum(Int32 newMaximum);
    
    //Sets the model's minimum to newMinimum.
    virtual void setMinimum(Int32 newMinimum);
    
    //This method sets all of the model's data with a single method call.
    virtual void setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting);
    
    //Sets the model's current value to newValue if newValue satisfies the model's constraints.
    virtual void setValue(Int32 newValue);
    
    //This attribute indicates that any upcoming changes to the value of the model should be considered a single event
    virtual void setValueIsAdjusting(bool b);
    
	virtual void addChangeListener(ChangeListenerPtr Listener);
	virtual void removeChangeListener(ChangeListenerPtr Listener);
    DefaultBoundedRangeModel(void);
    ~DefaultBoundedRangeModel(void);
};

typedef DefaultBoundedRangeModel* DefaultBoundedRangeModelPtr;

OSG_END_NAMESPACE

#include "OSGDefaultBoundedRangeModel.inl"

#endif /* _OSG_UI_DEFAULT_BOUNDEDRANGE_MODEL_H_ */


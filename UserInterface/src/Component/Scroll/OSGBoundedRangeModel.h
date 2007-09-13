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

#ifndef _OSG_UI_BOUNDEDRANGE_MODEL_H_
#define _OSG_UI_BOUNDEDRANGE_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGBaseTypes.h>
#include "OSGUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE
class ChangeListener;
typedef ChangeListener* ChangeListenerPtr;
	 
class OSG_USERINTERFACELIB_DLLMAPPING BoundedRangeModel
{
private:
protected:
public:
    //Returns the model's extent, the length of the inner range that begins at the model's value.
    virtual UInt32 getExtent(void) const = 0;
    
    //Returns the model's maximum.
    virtual Int32 getMaximum(void) const = 0;
    
    //Returns the minimum acceptable value.
    virtual Int32 getMinimum(void) const = 0;
    
    //Returns the model's current value.
    virtual Int32 getValue(void) const = 0;
    
    //Returns true if the current changes to the value property are part of a series of changes.
    virtual bool getValueIsAdjusting(void) const = 0;
    
    //Sets the model's extent.
    virtual void setExtent(UInt32 newExtent) = 0;
    
    //Sets the model's maximum to newMaximum.
    virtual void setMaximum(Int32 newMaximum) = 0;
    
    //Sets the model's minimum to newMinimum.
    virtual void setMinimum(Int32 newMinimum) = 0;
    
    //This method sets all of the model's data with a single method call.
    virtual void setRangeProperties(Int32 value, UInt32 extent, Int32 min, Int32 max, bool adjusting) = 0;
    
    //Sets the model's current value to newValue if newValue satisfies the model's constraints.
    virtual void setValue(Int32 newValue) = 0;
    
    //This attribute indicates that any upcoming changes to the value of the model should be considered a single event
    virtual void setValueIsAdjusting(bool b) = 0;
    
	virtual void addChangeListener(ChangeListenerPtr l) = 0;
	virtual void removeChangeListener(ChangeListenerPtr l) = 0;
};

typedef BoundedRangeModel* BoundedRangeModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_BOUNDEDRANGE_MODEL_H_ */


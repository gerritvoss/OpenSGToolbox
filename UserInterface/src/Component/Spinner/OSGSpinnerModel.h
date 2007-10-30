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

#ifndef _OSG_UI_SPINNER_MODEL_H_
#define _OSG_UI_SPINNER_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>
#include "Event/OSGChangeListener.h"

#include <OpenSG/Toolbox/OSGIntrusivePtrImplBase.h>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING SpinnerModel : public IntrusivePtrImplBase
{
private:
protected:
public:

    //Adds a ChangeListener to the model's listener list.
    virtual void addChangeListener(ChangeListenerPtr l) = 0;
    
    //Removes a ChangeListener from the model's listener list.
    virtual void removeChangeListener(ChangeListenerPtr l) = 0;
    
    //Return the object in the sequence that comes after the object returned by getValue().
    virtual SharedFieldPtr getNextValue(void) = 0;
    
    //Return the object in the sequence that comes before the object returned by getValue().
    virtual SharedFieldPtr getPreviousValue(void) = 0;
    
    //The current element of the sequence.
    virtual SharedFieldPtr getValue(void) = 0;
    
    //Changes current value of the model, typically this value is displayed by the editor part of a Spinner.
    virtual void setValue(SharedFieldPtr value) = 0;
};

typedef boost::intrusive_ptr<SpinnerModel> SpinnerModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_SPINNER_MODEL_H_ */


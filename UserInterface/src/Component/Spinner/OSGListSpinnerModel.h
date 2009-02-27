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

#ifndef _OSG_UI_LIST_SPINNER_MODEL_H_
#define _OSG_UI_LIST_SPINNER_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGAbstractSpinnerModel.h"

#include <list>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING ListSpinnerModel : public AbstractSpinnerModel
{
public:
    typedef std::list<boost::any> AnyList;
    typedef AnyList::iterator AnyListIter;
    
    //Return the object in the sequence that comes after the object returned by getValue().
    virtual boost::any getNextValue(void);
    
    //Return the object in the sequence that comes before the object returned by getValue().
    virtual boost::any getPreviousValue(void);
    
    //The current element of the sequence.
    virtual boost::any getValue(void);
    
    //Changes current value of the model, typically this value is displayed by the editor part of a Spinner.
    virtual void setValue(const boost::any& value);

    //Changes current value of the model, typically this value is displayed by the editor part of a Spinner.
    virtual void setValue(const std::string& value);
    
    //Changes the list that defines this sequence and resets the index of the models value to zero.
    void setList(const AnyList& list);
    
    //Returns the List that defines the sequence for this model.
    AnyList getList(void) const;
	
	virtual std::string getModelName(void) const;

	static std::string getClassModelName(void);
    
protected:
    AnyList _List;
    AnyListIter _CurrentListValue;
};

typedef boost::intrusive_ptr<ListSpinnerModel> ListSpinnerModelPtr;

OSG_END_NAMESPACE

#include "OSGListSpinnerModel.inl"

#endif /* _OSG_UI_LIST_SPINNER_MODEL_H_ */


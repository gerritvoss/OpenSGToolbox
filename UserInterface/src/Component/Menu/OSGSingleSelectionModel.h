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

#ifndef _OSG_UI_SINGLE_SELECTION_MODEL_H_
#define _OSG_UI_SINGLE_SELECTION_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "Event/OSGChangeListener.h"
#include <OpenSG/OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING SingleSelectionModel
{
private:
protected:
public:

    //Adds listener as a listener to changes in the model.
    virtual void addChangeListener(ChangeListenerPtr listener) = 0;

    //Clears the selection (to -1).
    virtual void clearSelection(void) = 0;
    
    //Returns the model's selection.
    virtual Int32 getSelectedIndex(void) = 0;
    
    //Returns true if the selection model currently has a selected value.
    virtual bool isSelected(void) = 0;
    
    //Removes listener as a listener to changes in the model.
    virtual void removeChangeListener(ChangeListenerPtr listener) = 0;
    
    //Sets the model's selected index to index.
    virtual void setSelectedIndex(Int32 index) = 0;
   
};

typedef SingleSelectionModel* SingleSelectionModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_SINGLE_SELECTION_MODEL_H_ */



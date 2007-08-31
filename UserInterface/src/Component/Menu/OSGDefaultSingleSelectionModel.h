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

#ifndef _OSG_UI_DEFAULT_SINGLE_SELECTION_MODEL_H_
#define _OSG_UI_DEFAULT_SINGLE_SELECTION_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"
#include "OSGSingleSelectionModel.h"
#include <set>

OSG_BEGIN_NAMESPACE
	 
class OSG_USERINTERFACELIB_DLLMAPPING DefaultSingleSelectionModel : public SingleSelectionModel
{
private:
protected:
	typedef std::set<ChangeListenerPtr> ChangeListenerSet;
    typedef ChangeListenerSet::iterator ChangeListenerSetItor;
    typedef ChangeListenerSet::const_iterator ChangeListenerSetConstItor;
	
    ChangeListenerSet       _ChangeListeners;
    
    virtual void produceStateChanged(const ChangeEvent& e);
    
    Int32 _SelectedIndex;
public:
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultSingleSelectionModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultSingleSelectionModel(void); 

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/

    //Adds listener as a listener to changes in the model.
    virtual void addChangeListener(ChangeListenerPtr listener);

    //Clears the selection (to -1).
    virtual void clearSelection(void);
    
    //Returns the model's selection.
    virtual Int32 getSelectedIndex(void);
    
    //Returns true if the selection model currently has a selected value.
    virtual bool isSelected(void);
    
    //Removes listener as a listener to changes in the model.
    virtual void removeChangeListener(ChangeListenerPtr listener);
    
    //Sets the model's selected index to index.
    virtual void setSelectedIndex(Int32 index);
   
};

typedef DefaultSingleSelectionModel* DefaultSingleSelectionModelPtr;

OSG_END_NAMESPACE

#include "OSGDefaultSingleSelectionModel.inl"

#endif /* _OSG_UI_DEFAULT_SINGLE_SELECTION_MODEL_H_ */



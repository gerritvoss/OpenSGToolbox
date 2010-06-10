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

#ifndef _OSG_UI_ABSTRACT_SPINNER_MODEL_H_
#define _OSG_UI_ABSTRACT_SPINNER_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGSpinnerModel.h"
#include <set>

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE
	 
class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractSpinnerModel : public SpinnerModel
{
  protected:
    typedef std::set<ChangeListenerPtr> ChangeListenerSet;
    typedef ChangeListenerSet::iterator ChangeListenerSetItor;
    typedef ChangeListenerSet::const_iterator ChangeListenerSetConstItor;
    ChangeListenerSet _ChangeListeners;

    void produceStateChanged(void);

  public:

    //Adds a ChangeListener to the model's listener list.
    virtual EventConnection addChangeListener(ChangeListenerPtr l);
    virtual bool isChangeListenerAttached(ChangeListenerPtr l) const;

    //Removes a ChangeListener from the model's listener list.
    virtual void removeChangeListener(ChangeListenerPtr l);

};

typedef boost::shared_ptr<AbstractSpinnerModel> AbstractSpinnerModelPtr;

OSG_END_NAMESPACE

#endif /* _OSG_UI_ABSTRACT_SPINNER_MODEL_H_ */


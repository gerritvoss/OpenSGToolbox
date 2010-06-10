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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEUSERINTERFACELIB

#include "OSGConfig.h"

#include "OSGAbstractSpinnerModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::AbstractSpinnerModel
A AbstractSpinnerModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


EventConnection AbstractSpinnerModel::addChangeListener(ChangeListenerPtr l)
{
    _ChangeListeners.insert(l);
    return EventConnection(
                           boost::bind(&AbstractSpinnerModel::isChangeListenerAttached, this, l),
                           boost::bind(&AbstractSpinnerModel::removeChangeListener, this, l));
}

bool AbstractSpinnerModel::isChangeListenerAttached(ChangeListenerPtr l) const
{
    return _ChangeListeners.find(l) != _ChangeListeners.end();
}

void AbstractSpinnerModel::removeChangeListener(ChangeListenerPtr l)
{
    ChangeListenerSetItor EraseIter(_ChangeListeners.find(l));
    if(EraseIter != _ChangeListeners.end())
    {
        _ChangeListeners.erase(EraseIter);
    }
}

void AbstractSpinnerModel::produceStateChanged(void)
{
    const ChangeEventUnrecPtr TheEvent = ChangeEvent::create(NULL, getSystemTime());
    ChangeListenerSet ModelListenerSet(_ChangeListeners);
    for(ChangeListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->stateChanged(TheEvent);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/


OSG_END_NAMESPACE


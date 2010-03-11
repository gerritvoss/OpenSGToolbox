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

#include "OSGBoundedRangeSpinnerModel.h"
#include "OSGDefaultBoundedRangeModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::DefaultChangeModel
A DefaultChangeModel. 
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


Int32 BoundedRangeSpinnerModel::getMaximum(void) const
{
    return _TheBoundedRangeModel->getMaximum();
}

Int32 BoundedRangeSpinnerModel::getMinimum(void) const
{
    return _TheBoundedRangeModel->getMinimum();
}

Int32 BoundedRangeSpinnerModel::getValue(void) const
{
    return _TheBoundedRangeModel->getValue();
}

void BoundedRangeSpinnerModel::setMaximum(Int32 newMaximum)
{
    dettachListenersFromModels();

    _TheBoundedRangeModel->setMaximum(newMaximum);
    _TheSpinnerModel->setMaximum(newMaximum);

    attachListenersToModels();
}

void BoundedRangeSpinnerModel::setMinimum(Int32 newMinimum)
{
    dettachListenersFromModels();

    _TheBoundedRangeModel->setMinimum(newMinimum);
    _TheSpinnerModel->setMinimum(newMinimum);

    attachListenersToModels();
}

void BoundedRangeSpinnerModel::setValue(Int32 newValue)
{
    dettachListenersFromModels();

    _TheBoundedRangeModel->setValue(newValue);
    _TheSpinnerModel->setValue(boost::any(newValue));

    attachListenersToModels();

    produceStateChanged();
}

EventConnection BoundedRangeSpinnerModel::addChangeListener(ChangeListenerPtr l)
{
    _ChangeListeners.insert(l);
    return EventConnection(
                           boost::bind(&BoundedRangeSpinnerModel::isChangeListenerAttached, this, l),
                           boost::bind(&BoundedRangeSpinnerModel::removeChangeListener, this, l));
}

void BoundedRangeSpinnerModel::removeChangeListener(ChangeListenerPtr l)
{
    ChangeListenerSetItor EraseIter(_ChangeListeners.find(l));
    if(EraseIter != _ChangeListeners.end())
    {
        _ChangeListeners.erase(EraseIter);
    }
}

void BoundedRangeSpinnerModel::produceStateChanged(void)
{
    const ChangeEventUnrecPtr TheEvent = ChangeEvent::create(NULL, getSystemTime());
    ChangeListenerSet ModelListenerSet(_ChangeListeners);
    for(ChangeListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->stateChanged(TheEvent);
    }
}

void BoundedRangeSpinnerModel::attachListenersToModels(void)
{
    _TheBoundedRangeModel->addChangeListener(&_BoundedRangeModelChangeListener);
    _TheSpinnerModel->addChangeListener(&_SpinnerModelChangeListener);
}

void BoundedRangeSpinnerModel::dettachListenersFromModels(void)
{
    _TheBoundedRangeModel->removeChangeListener(&_BoundedRangeModelChangeListener);
    _TheSpinnerModel->removeChangeListener(&_SpinnerModelChangeListener);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BoundedRangeSpinnerModel::BoundedRangeSpinnerModel(void) :
    _BoundedRangeModelChangeListener(this),
    _SpinnerModelChangeListener(this)
{
    _TheBoundedRangeModel = DefaultBoundedRangeModel::create();
    _TheBoundedRangeModel->setExtent(0);

    _TheSpinnerModel = Int32SpinnerModelPtr(new Int32SpinnerModel());
    _TheSpinnerModel->setStepSize(1);

    attachListenersToModels();
}

BoundedRangeSpinnerModel::BoundedRangeSpinnerModel(const BoundedRangeSpinnerModel &source) :
    _BoundedRangeModelChangeListener(this),
    _SpinnerModelChangeListener(this)
{
    _TheBoundedRangeModel = DefaultBoundedRangeModel::create();
    _TheBoundedRangeModel->setExtent(source._TheBoundedRangeModel->getExtent());

    _TheSpinnerModel = Int32SpinnerModelPtr(new Int32SpinnerModel());
    _TheSpinnerModel->setStepSize(source._TheSpinnerModel->getStepSize());

    attachListenersToModels();

    setMinimum(source.getMinimum());
    setMaximum(source.getMaximum());
    setValue(source.getValue());
}

BoundedRangeSpinnerModel::~BoundedRangeSpinnerModel(void)
{
    dettachListenersFromModels();
}


void BoundedRangeSpinnerModel::BoundedRangeModelChangeListener::stateChanged(const ChangeEventUnrecPtr e)
{
    _BoundedRangeSpinnerModel->dettachListenersFromModels();

    _BoundedRangeSpinnerModel->_TheSpinnerModel->setMinimum(_BoundedRangeSpinnerModel->_TheBoundedRangeModel->getMinimum());
    _BoundedRangeSpinnerModel->_TheSpinnerModel->setMaximum(_BoundedRangeSpinnerModel->_TheBoundedRangeModel->getMaximum());
    _BoundedRangeSpinnerModel->_TheSpinnerModel->setValue(boost::any(_BoundedRangeSpinnerModel->_TheBoundedRangeModel->getValue()));

    _BoundedRangeSpinnerModel->attachListenersToModels();
    _BoundedRangeSpinnerModel->produceStateChanged();
}

void BoundedRangeSpinnerModel::SpinnerModelChangeListener::stateChanged(const ChangeEventUnrecPtr e)
{
    _BoundedRangeSpinnerModel->dettachListenersFromModels();

    _BoundedRangeSpinnerModel->_TheBoundedRangeModel->setMinimum(_BoundedRangeSpinnerModel->_TheSpinnerModel->getMinimum());
    _BoundedRangeSpinnerModel->_TheBoundedRangeModel->setMaximum(_BoundedRangeSpinnerModel->_TheSpinnerModel->getMaximum());
    _BoundedRangeSpinnerModel->_TheBoundedRangeModel->setValue(_BoundedRangeSpinnerModel->_TheSpinnerModel->getNumber());

    _BoundedRangeSpinnerModel->attachListenersToModels();
    _BoundedRangeSpinnerModel->produceStateChanged();
}

OSG_END_NAMESPACE


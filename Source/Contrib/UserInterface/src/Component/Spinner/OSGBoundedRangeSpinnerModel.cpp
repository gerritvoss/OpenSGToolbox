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


EventDescription *BoundedRangeSpinnerModel::_eventDesc[] =
{
    new EventDescription("StateChanged", 
                          "StateChanged",
                          StateChangedEventId, 
                          FieldTraits<StateChangedEventDetailsType *>::getType(),
                          true,
                          NULL),
};

EventProducerType BoundedRangeSpinnerModel::_producerType(
                                            "BoundedRangeSpinnerModelProducerType",
                                            "EventProducerType",
                                            "",
                                            InitEventProducerFunctor(),
                                            _eventDesc,
                                            sizeof(_eventDesc));

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/
const EventProducerType &BoundedRangeSpinnerModel::getProducerType(void) const
{
    return _producerType;
}

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

void BoundedRangeSpinnerModel::attachListenersToModels(void)
{
    _RangeModelStateChangedConnection = _TheBoundedRangeModel->connectStateChanged(boost::bind(&BoundedRangeSpinnerModel::handleRangeModelStateChanged, this, _1));
    _SpinnerModelStateChangedConnection = _TheSpinnerModel->connectStateChanged(boost::bind(&BoundedRangeSpinnerModel::handleSpinnerModelStateChanged, this, _1));
}

void BoundedRangeSpinnerModel::dettachListenersFromModels(void)
{
    _RangeModelStateChangedConnection.disconnect();
    _SpinnerModelStateChangedConnection.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BoundedRangeSpinnerModel::BoundedRangeSpinnerModel(void)
{
    _TheBoundedRangeModel = DefaultBoundedRangeModel::create();
    _TheBoundedRangeModel->setExtent(0);

    _TheSpinnerModel = Int32SpinnerModelPtr(new Int32SpinnerModel());
    _TheSpinnerModel->setStepSize(1);

    attachListenersToModels();
}

BoundedRangeSpinnerModel::BoundedRangeSpinnerModel(const BoundedRangeSpinnerModel &source)
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


void BoundedRangeSpinnerModel::handleRangeModelStateChanged(ChangeEventDetails* const e)
{
    dettachListenersFromModels();

    _TheSpinnerModel->setMinimum(_TheBoundedRangeModel->getMinimum());
    _TheSpinnerModel->setMaximum(_TheBoundedRangeModel->getMaximum());
    _TheSpinnerModel->setValue(boost::any(_TheBoundedRangeModel->getValue()));

    attachListenersToModels();
    produceStateChanged();
}

void BoundedRangeSpinnerModel::handleSpinnerModelStateChanged(ChangeEventDetails* const e)
{
    dettachListenersFromModels();

    _TheBoundedRangeModel->setMinimum(_TheSpinnerModel->getMinimum());
    _TheBoundedRangeModel->setMaximum(_TheSpinnerModel->getMaximum());
    _TheBoundedRangeModel->setValue(_TheSpinnerModel->getNumber());

    attachListenersToModels();
    produceStateChanged();
}

OSG_END_NAMESPACE


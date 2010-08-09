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

#ifndef _OSG_UI_BOUNDED_RANGE_SPINNER_MODEL_H_
#define _OSG_UI_BOUNDED_RANGE_SPINNER_MODEL_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGBoundedRangeModel.h"
#include "OSGNumberSpinnerModel.h"

OSG_BEGIN_NAMESPACE

class BoundedRangeSpinnerModel;

typedef boost::shared_ptr<BoundedRangeSpinnerModel> BoundedRangeSpinnerModelPtr;

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING BoundedRangeSpinnerModel
{
  public:
    typedef ChangeEventDetails StateChangedEventDetailsType;
    typedef boost::signals2::signal<void (StateChangedEventDetailsType* const, UInt32), ConsumableEventCombiner> StateChangedEventType;

    enum
    {
        StateChangedEventId = 1,
        NextEventId     = StateChangedEventId            + 1
    };
    static const  EventProducerType  &getProducerClassType  (void); 
    static        UInt32              getProducerClassTypeId(void); 
    virtual const EventProducerType &getProducerType(void) const; 

    boost::signals2::connection          attachActivity(UInt32 eventId,
                                                       Activity* TheActivity);
    UInt32                   getNumProducedEvents(void)          const;
    const EventDescription *getProducedEventDescription(const   Char8 *ProducedEventName) const;
    const EventDescription *getProducedEventDescription(UInt32  ProducedEventId) const;
    UInt32                   getProducedEventId(const            Char8 *ProducedEventName) const;

    boost::signals2::connection connectStateChanged(const StateChangedEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    boost::signals2::connection connectStateChanged(const StateChangedEventType::group_type &group,
                                                       const StateChangedEventType::slot_type &listener,
                                                       boost::signals2::connect_position at= boost::signals2::at_back);
    void   disconnectStateChanged       (const StateChangedEventType::group_type &group);
    void   disconnectAllSlotsStateChanged(void);
    bool   isEmptyStateChanged          (void) const;
    UInt32 numSlotsStateChanged         (void) const;
    //Returns the model's maximum.
    virtual Int32 getMaximum(void) const;

    //Returns the minimum acceptable value.
    virtual Int32 getMinimum(void) const;

    //Returns the model's current value.
    virtual Int32 getValue(void) const;

    //Sets the model's maximum to newMaximum.
    virtual void setMaximum(Int32 newMaximum);

    //Sets the model's minimum to newMinimum.
    virtual void setMinimum(Int32 newMinimum);

    //Sets the model's current value to newValue if newValue satisfies the model's constraints.
    virtual void setValue(Int32 newValue);

    BoundedRangeModel* getBoundedRangeModel(void);

    SpinnerModelPtr getSpinnerModel(void);

    BoundedRangeSpinnerModel(void);
    BoundedRangeSpinnerModel(const BoundedRangeSpinnerModel &source);
    ~BoundedRangeSpinnerModel(void);
  private:

  protected:
    BoundedRangeModelRefPtr _TheBoundedRangeModel;
    Int32SpinnerModelPtr _TheSpinnerModel;

    void produceStateChanged(void);

    //BoundedRangeModel
    void handleRangeModelStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _RangeModelStateChangedConnection;

    //BoundedRangeSpinnerModel
    void handleSpinnerModelStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _SpinnerModelStateChangedConnection;

    void attachListenersToModels(void);

    void dettachListenersFromModels(void);

    static EventDescription   *_eventDesc[];
    static EventProducerType _producerType;
    StateChangedEventType _StateChangedEvent;
    
    void produceStateChanged(StateChangedEventDetailsType* const e);

};


OSG_END_NAMESPACE

#include "OSGBoundedRangeSpinnerModel.inl"

#endif /* _OSG_UI_BOUNDED_RANGE_SPINNER_MODEL_H_ */


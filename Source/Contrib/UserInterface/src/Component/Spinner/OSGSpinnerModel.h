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
 
#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/function.hpp>
#include "OSGEventDescription.h"
#include "OSGConsumableEventCombiner.h"
#include "OSGChangeEventDetailsFields.h"
#include "OSGEventProducerType.h"
#include "OSGActivity.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING IllegalArgumentException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "IllegalArgumentException";
    }
};

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SpinnerModel
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


    //Return the object in the sequence that comes after the object returned by getValue().
    virtual boost::any getNextValue(void) = 0;

    //Return the object in the sequence that comes before the object returned by getValue().
    virtual boost::any getPreviousValue(void) = 0;

    //The current element of the sequence.
    virtual boost::any getValue(void) = 0;

    //Changes current value of the model, typically this value is displayed by the editor part of a Spinner.
    virtual void setValue(const boost::any& value) = 0;

    //Changes current value of the model, typically this value is displayed by the editor part of a Spinner.
    virtual void setValue(const std::string& value) = 0;

    virtual std::string getModelName(void) const = 0;

    //The current element of the sequence as a string
    virtual std::string getValueAsString(void) const;
  private:
  protected:

    static EventDescription   *_eventDesc[];
    static EventProducerType _producerType;
    StateChangedEventType _StateChangedEvent;
    
    void produceStateChanged(StateChangedEventDetailsType* const e);

};

typedef boost::shared_ptr<SpinnerModel> SpinnerModelPtr;


SpinnerModelPtr OSG_CONTRIBUSERINTERFACE_DLLMAPPING createDefaultNumberSpinnerModel(const DataType& TheType);

SpinnerModelPtr OSG_CONTRIBUSERINTERFACE_DLLMAPPING createDefaultNumberSpinnerModel(GetFieldHandlePtr TheFieldHandle);

OSG_END_NAMESPACE

#include "OSGSpinnerModel.inl"

#endif /* _OSG_UI_SPINNER_MODEL_H_ */


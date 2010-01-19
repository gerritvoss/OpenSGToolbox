/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#ifndef _OSGEVENTPRODUCER_H_
#define _OSGEVENTPRODUCER_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGEventProducerType.h"
#include "OSGEventConnection.h"
#include "OSGEvent.h"
#include "OSGEventListener.h"
#include "OSGActivity.h"
#include "OSGMethodDescription.h"
#include "OSGBaseFieldTraits.h"

#include <map>
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief EventProducer class. See \ref 
           PageToolboxEventProducer for a description.
*/

class OSG_BASE_DLLMAPPING EventProducer
{
  private:

    /*==========================  PUBLIC  =================================*/
  public:

    //Attaching Activities
    EventConnection attachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId);
    bool isActivityAttached(ActivityRefPtr TheActivity, UInt32 ProducedEventId) const;
    UInt32 getNumActivitiesAttached(UInt32 ProducedEventId) const;
    ActivityRefPtr getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const;
    void detachActivity(ActivityRefPtr TheActivity, UInt32 ProducedEventId);

    EventConnection attachActivity(ActivityRefPtr TheActivity, const std::string &ProducedEventName);
    bool isActivityAttached(ActivityRefPtr TheActivity, const std::string &ProducedEventName) const;
    UInt32 getNumActivitiesAttached(const std::string &ProducedEventName) const;
    ActivityRefPtr getAttachedActivity(const std::string &ProducedEventName, UInt32 ActivityIndex) const;
    void detachActivity(ActivityRefPtr TheActivity, const std::string &ProducedEventName);
    void detachAllActivities(void);
    UInt32 getNumAttachedActivities(void) const;

    //Attaching EventListeners
    EventConnection attachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId);
    bool isEventListenerAttached(EventListenerPtr TheEventListener, UInt32 ProducedEventId) const;
    UInt32 getNumEventListenersAttached(UInt32 ProducedEventId) const;
    EventListenerPtr getAttachedEventListener(UInt32 ProducedEventId, UInt32 EventListenerIndex) const;
    void detachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId);

    EventConnection attachEventListener(EventListenerPtr TheEventListener, const std::string &ProducedEventName);
    bool isEventListenerAttached(EventListenerPtr TheEventListener, const std::string &ProducedEventName) const;
    UInt32 getNumEventListenersAttached(const std::string &ProducedEventName) const;
    EventListenerPtr getAttachedEventListener(const std::string &ProducedEventName, UInt32 EventListenerIndex) const;
    void detachEventListener(EventListenerPtr TheEventListener, const std::string &ProducedEventName);
    void detachAllEventListeners(void);
    UInt32 getNumAttachedEventListeners(void) const;


    const EventProducerType &getProducerType(void) const;

    UInt32 getNumProducedEvents(void) const;
    const MethodDescription *getProducedEventDescription(const std::string &ProducedEventName) const;
    const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const;
    UInt32 getProducedEventId(const std::string &ProducedEventName) const;

    static const EventProducerType &getProducerClassType(void);
    static UInt32                   getProducerClassTypeId(void);

    EventProducer(const EventProducerType* TheProducerType);
     ~EventProducer(void); 
    void produceEvent(UInt32 ProducedEventId, const EventUnrecPtr TheEvent);

    void setType(const EventProducerType* TheProducerType);
    
    void putToStream(OutStream &outVal);
    bool getFromCString(const Char8     *&inVal);

    /*=========================  PROTECTED  ===============================*/
  protected:
      typedef std::set<ActivityRefPtr> ActivitySet;
      typedef ActivitySet::iterator ActivitySetItor;
      typedef ActivitySet::const_iterator ActivitySetConstItor;

      typedef std::map<UInt32, ActivitySet > ActivityMap;
      typedef ActivityMap::iterator ActivityMapItor;
      typedef ActivityMap::const_iterator ActivityMapConstItor;

      typedef std::set<EventListenerPtr> EventListenerSet;
      typedef EventListenerSet::iterator EventListenerSetItor;
      typedef EventListenerSet::const_iterator EventListenerSetConstItor;

      typedef std::map<UInt32, EventListenerSet > EventListenerMap;
      typedef EventListenerMap::iterator EventListenerMapItor;
      typedef EventListenerMap::const_iterator EventListenerMapConstItor;
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    EventProducer(const EventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */


    /*! \}                                                                 */

    ActivityMap _AttachedActivitys;

    EventListenerMap _AttachedEventListeners;
    
    /*==========================  PRIVATE  ================================*/
  private:

    static EventProducerType _ProducerClassType;

    const EventProducerType* _ProducerType;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const EventProducer &source);
};

typedef EventProducer *EventProducerPtr;

OSG_END_NAMESPACE

#include "OSGEventProducer.inl"

#endif /* _OSGEVENTPRODUCER_H_ */

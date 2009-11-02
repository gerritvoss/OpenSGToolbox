/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include "OSGEventProducerType.h"
#include "OSGEventConnection.h"
#include "Event/OSGEvent.h"
#include "Event/Listeners/OSGEventListener.h"
#include "Activity/OSGActivity.h"
#include "OSGMethodDescription.h"

#include <map>
#include <set>

OSG_BEGIN_NAMESPACE

/*! \brief EventProducer class. See \ref 
           PageToolboxEventProducer for a description.
*/

class OSG_TOOLBOXLIB_DLLMAPPING EventProducer
{
  private:

    /*==========================  PUBLIC  =================================*/
  public:

    //Attaching Activities
    EventConnection attachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);
    bool isActivityAttached(ActivityPtr TheActivity, UInt32 ProducedEventId) const;
    UInt32 getNumActivitiesAttached(UInt32 ProducedEventId) const;
    ActivityPtr getAttachedActivity(UInt32 ProducedEventId, UInt32 ActivityIndex) const;
    void detachActivity(ActivityPtr TheActivity, UInt32 ProducedEventId);

    EventConnection attachActivity(ActivityPtr TheActivity, const Char8 *ProducedEventName);
    bool isActivityAttached(ActivityPtr TheActivity, const Char8 *ProducedEventName) const;
    UInt32 getNumActivitiesAttached(const Char8 *ProducedEventName) const;
    ActivityPtr getAttachedActivity(const Char8 *ProducedEventName, UInt32 ActivityIndex) const;
    void detachActivity(ActivityPtr TheActivity, const Char8 *ProducedEventName);
    void detachAllActivities(void);
    UInt32 getNumAttachedActivities(void) const;

    //Attaching EventListeners
    EventConnection attachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId);
    bool isEventListenerAttached(EventListenerPtr TheEventListener, UInt32 ProducedEventId) const;
    UInt32 getNumEventListenersAttached(UInt32 ProducedEventId) const;
    EventListenerPtr getAttachedEventListener(UInt32 ProducedEventId, UInt32 EventListenerIndex) const;
    void detachEventListener(EventListenerPtr TheEventListener, UInt32 ProducedEventId);

    EventConnection attachEventListener(EventListenerPtr TheEventListener, const Char8 *ProducedEventName);
    bool isEventListenerAttached(EventListenerPtr TheEventListener, const Char8 *ProducedEventName) const;
    UInt32 getNumEventListenersAttached(const Char8 *ProducedEventName) const;
    EventListenerPtr getAttachedEventListener(const Char8 *ProducedEventName, UInt32 EventListenerIndex) const;
    void detachEventListener(EventListenerPtr TheEventListener, const Char8 *ProducedEventName);
    void detachAllEventListeners(void);
    UInt32 getNumAttachedEventListeners(void) const;


    const EventProducerType &getProducerType(void) const;

    UInt32 getNumProducedEvents(void) const;
    const MethodDescription *getProducedEventDescription(const Char8 *ProducedEventName) const;
    const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const;
    UInt32 getProducedEventId(const Char8 *ProducedEventName) const;

    static const EventProducerType &getProducerClassType(void);
    static UInt32                   getProducerClassTypeId(void);

    EventProducer(const EventProducerType* TheProducerType);
     ~EventProducer(void); 
    void produceEvent(UInt32 ProducedEventId, const EventPtr TheEvent);

    void setType(const EventProducerType* TheProducerType);
    
    void putToString(std::string &outVal);
    bool getFromString(const Char8     *&inVal);

    /*=========================  PROTECTED  ===============================*/
  protected:
      typedef std::set<ActivityPtr> ActivitySet;
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

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
    enum
    {
        NextMethodId                 = 1
    };

    EventConnection attachEventListener(EventListenerPtr Listener, UInt32 ProducedEventId);
    bool isEventListenerAttached(EventListenerPtr Listener, UInt32 ProducedEventId) const;
    UInt32 getNumListenersAttached(UInt32 ProducedEventId) const;
    EventListenerPtr getAttachedListener(UInt32 ProducedEventId, UInt32 ListenerIndex) const;
    void detachEventListener(EventListenerPtr Listener, UInt32 ProducedEventId);

    virtual const EventProducerType &getProducerType(void) const = 0;

    UInt32 getNumProducedEvents(void) const;
    const MethodDescription *getProducedEventDescription(const Char8 *ProducedEventName) const;
    const MethodDescription *getProducedEventDescription(UInt32 ProducedEventId) const;
    UInt32 getProducedEventId(const Char8 *ProducedEventName) const;

    static const EventProducerType &getProducerClassType(void);
    static UInt32                   getProducerClassTypeId(void);

    /*=========================  PROTECTED  ===============================*/
  protected:
      typedef std::set<EventListenerPtr> ListenerSet;
      typedef ListenerSet::iterator ListenerSetItor;
      typedef ListenerSet::const_iterator ListenerSetConstItor;

      typedef std::map<UInt32, ListenerSet > ListenerMap;
      typedef ListenerMap::iterator ListenerMapItor;
      typedef ListenerMap::const_iterator ListenerMapConstItor;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    EventProducer(void);
    EventProducer(const EventProducer &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~EventProducer(void); 

    /*! \}                                                                 */

    ListenerMap _AttachedListeners;
    void produceEvent(UInt32 ProducedEventId, const EventPtr TheEvent);
    
    /*==========================  PRIVATE  ================================*/
  private:

    static EventProducerType _ProducerType;

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const EventProducer &source);
};

typedef EventProducer *EventProducerPtr;

OSG_END_NAMESPACE

#include "OSGEventProducer.inl"

#endif /* _OSGEVENTPRODUCER_H_ */

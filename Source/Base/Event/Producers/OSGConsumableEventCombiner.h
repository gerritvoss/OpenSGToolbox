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

<<<<<<< Updated upstream:Source/Base/Event/Listeners/OSGEventListener.cpp
#include "OSGConfig.h"

#include "OSGEventListener.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

void EventListener::eventProduced(const EventUnrecPtr EventDetails, UInt32 ProducedEventId)
{
    //Do Nothing
}

=======
#ifndef _OSGCONSUMABLEEVENTCOMBINER_H_
#define _OSGCONSUMABLEEVENTCOMBINER_H_

#include "OSGConfig.h"
#include "OSGBaseDef.h"

#include "OSGEvent.h"


OSG_BEGIN_NAMESPACE

class OSG_BASE_DLLMAPPING ConsumableEventCombiner
{
private:
    mutable const Event const * _pEvent;

public:
    ConsumableEventCombiner(void);

    ConsumableEventCombiner(Event const * e);

    ConsumableEventCombiner(const ConsumableEventCombiner& );

    typedef void result_type;

    template<typename InputIterator>
    result_type operator()(InputIterator first, InputIterator last) const
    {
        while (first != last) 
        {
            if(_pEvent->isConsumed())
            {
                break;
            }
            ++first;
        }
        _pEvent = NULL;
    }
};
OSG_END_NAMESPACE

#endif /* _OSGCONSUMABLEEVENTCOMBINER_H_ */
>>>>>>> Stashed changes:Source/Base/Event/Producers/OSGConsumableEventCombiner.h

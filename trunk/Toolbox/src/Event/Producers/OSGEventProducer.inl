/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
const EventProducerType &EventProducer::getProducerClassType(void)
{
    return _ProducerType;
}

inline
UInt32 EventProducer::getProducerClassTypeId(void)
{
    return _ProducerType.getId();
}

inline
UInt32 EventProducer::getNumProducedEvents(void) const
{
    return getProducerType().getNumMethodDescs();
}

inline
const MethodDescription *EventProducer::getProducedEventDescription(const Char8 *ProducedEventName) const
{
    return getProducerType().findMethodDescription(ProducedEventName);
}

inline
const MethodDescription *EventProducer::getProducedEventDescription(UInt32 ProducedEventId) const
{
    return getProducerType().getMethodDescription(ProducedEventId);
}

inline
UInt32 EventProducer::getProducedEventId(const Char8 *ProducedEventName) const
{
    return getProducerType().findMethodDescription(ProducedEventName)->getMethodId();
}

OSG_END_NAMESPACE


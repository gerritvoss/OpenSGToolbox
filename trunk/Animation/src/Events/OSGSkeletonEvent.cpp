/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Animation                               *
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
 * by the Free Software Foundation, version 3.                               *
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
#include "OSGSkeletonEvent.h"
#include "SkeletalAnimation/OSGSkeleton.h"

OSG_BEGIN_NAMESPACE

EventType SkeletonEvent::_Type("SkeletonEvent", "EventType");

const EventType &SkeletonEvent::getType(void) const
{
    return _Type;
}


SkeletonEvent::SkeletonEvent(FieldContainerPtr Source, Time TimeStamp,
	   SkeletonPtr TheSkeleton) :
   Event(Source, TimeStamp),
   _Skeleton(TheSkeleton)
{
}


SkeletonPtr SkeletonEvent::getSkeleton(void) const
{
	return _Skeleton;
}
OSG_END_NAMESPACE

/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
#ifndef _OSGCARETEVENT_H_
#define _OSGCARETEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Toolbox/OSGEvent.h>

#include "Component/OSGComponentFields.h"

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING CaretEvent : public Event
{
    /*=========================  PUBLIC  ===============================*/
    public:
        CaretEvent(FieldContainerPtr Source, Time TimeStamp, UInt32 ThePos);

        UInt32 getPosition(void) const;

        virtual const EventType &getType(void) const;

        static const EventType &getClassType(void);
    protected:
        UInt32 _Pos;
    private:
        static EventType _Type;
};

OSG_END_NAMESPACE

#include "OSGCaretEvent.inl"

#endif /* _OSGCARETEVENT_H_ */

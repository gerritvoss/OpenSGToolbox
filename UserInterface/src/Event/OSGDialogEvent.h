/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *   contact: dkabala@vrac.iastate.edu                                       *
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
#ifndef _OSGDIALOGEVENT_H_
#define _OSGDIALOGEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include <OpenSG/Input/OSGEvent.h>

#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

class OSG_USERINTERFACELIB_DLLMAPPING DialogEvent : public Event
{
  /*=========================  PUBLIC  ===============================*/
  public:

    enum Options{DIALOG_OPTION_OK, DIALOG_OPTION_YES, DIALOG_OPTION_NO, DIALOG_OPTION_CANCEL, DIALOG_OPTION_CLOSED};

    DialogEvent(FieldContainerPtr Source, Time TimeStamp, const UInt32& Option, const std::string& Input);
    
    virtual const EventType &getType(void) const;
    
    static const EventType &getClassType(void);

    UInt32 getOption(void) const;

    std::string getInput(void) const;
    
  private:
     static EventType _Type;

  protected:
     UInt32 _Option;
     std::string _Input;
};

OSG_END_NAMESPACE

#include "OSGDialogEvent.inl"

#endif /* _OSGDIALOGEVENT_H_ */

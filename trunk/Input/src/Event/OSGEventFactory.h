/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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


#ifndef _OSGEVENT_FACTORY_H_
#define _OSGEVENT_FACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include <OpenSG/OSGTypeFactory.h>

OSG_BEGIN_NAMESPACE

class OSG_INPUTLIB_DLLMAPPING EventFactory : public TypeFactory
{
    /*==========================  PUBLIC  =================================*/

  public :
    static EventFactory *the(void);

    /*=========================  PROTECTED  ===============================*/

  protected:
    typedef TypeFactory Inherited;
  
    EventFactory(void);
    
    /*---------------------------------------------------------------------*/
    virtual ~EventFactory(void);
    
    static EventFactory   *_the;
    
    /*==========================  PRIVATE  ================================*/
  private:
    EventFactory(const EventFactory &source);
    void operator =(const EventFactory &source);
};

typedef EventFactory *EventFactoryP;

OSG_END_NAMESPACE

#endif /* _OSGEVENT_FACTORY_H_ */

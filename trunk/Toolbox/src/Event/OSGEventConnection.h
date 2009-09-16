/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
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


#ifndef _OSGEVENTCONNECTION_H_
#define _OSGEVENTCONNECTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"
#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING EventConnection
{
    /*=========================  PUBLIC  ===============================*/
  public:
      typedef boost::function<bool (void)> IsConnectedFunctionType;
      typedef boost::function<void (void)> DisconnectFunctionType;

      EventConnection(IsConnectedFunctionType isConnectedFunc, DisconnectFunctionType disconnectedFunc);
      
      EventConnection(void);
      
      EventConnection(const EventConnection& c);

      const EventConnection& operator=(const EventConnection& c);

      bool isValid(void) const;

      bool isConnected(void) const;

      void disconnect(void);
protected:
    IsConnectedFunctionType _isConnectedFunc;
    DisconnectFunctionType _disconnectedFunc;

};

OSG_END_NAMESPACE

#include "OSGEventConnection.inl"

#endif /* _OSGEVENTCONNECTION_H_ */



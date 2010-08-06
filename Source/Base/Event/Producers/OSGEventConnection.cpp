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

#include "OSGEventConnection.h"

OSG_BEGIN_NAMESPACE

EventConnection::EventConnection(IsConnectedFunctionType isConnectedFunc, DisconnectFunctionType disconnectedFunc) :
    _isConnectedFunc(isConnectedFunc),
    _disconnectedFunc(disconnectedFunc)
{
}
    
EventConnection::EventConnection(void)
{
}

EventConnection::EventConnection(const EventConnection& c) :
    _isConnectedFunc(c._isConnectedFunc),
    _disconnectedFunc(c._disconnectedFunc)
{
}
    
const EventConnection& EventConnection::operator=(const EventConnection& c)
{
    if(&c != this)
    {
        _isConnectedFunc = c._isConnectedFunc;
        _disconnectedFunc = c._disconnectedFunc;
    }

    return c;
}

bool EventConnection::isValid(void) const
{
    return _isConnectedFunc.empty() || _disconnectedFunc.empty();
}

bool EventConnection::isConnected(void) const
{
    if(_isConnectedFunc.empty())
    {
        return false;
    }
    else
    {
        return _isConnectedFunc();
    }
}

void EventConnection::disconnect(void)
{
    if(isConnected() && !_disconnectedFunc.empty())
    {
        _disconnectedFunc();
    }
}

OSG_END_NAMESPACE



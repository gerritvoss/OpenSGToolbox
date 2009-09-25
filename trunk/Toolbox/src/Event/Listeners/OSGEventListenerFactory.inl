/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGEVENTLISTENERFACTORYIMPL_INL_
#define _OSGEVENTLISTENERFACTORYIMPL_INL_

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              Mapper                                     */

inline
void EventListenerFactory::setMapper(EventListenerMapper *pMapper)
{
    _pMapper = pMapper;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
EventListenerPtr EventListenerFactory::getContainer(
    UInt32 uiContainerId) const
{
    EventListenerPtr returnValue = NullFC;

    _pStoreLock->aquire();

    if(uiContainerId < _pEventListenerStore->size())
    {
        returnValue = (*_pEventListenerStore)[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

inline
EventListenerPtr EventListenerFactory::getMappedContainer(
    UInt32 uiContainerId) const
{
    if(_pMapper != NULL)
    {
        return getContainer(_pMapper->map(uiContainerId));
    }
    else
    {
        return getContainer(uiContainerId);
    }
}

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

inline
UInt32 EventListenerFactory::registerEventListener(
    const EventListenerPtr &pEventListener)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pEventListenerStore == NULL)
    {
        _pEventListenerStore = new EventListenerStore;

        _pEventListenerStore->push_back(NullFC);
    }

    _pEventListenerStore->push_back(pEventListener);

    returnValue = _pEventListenerStore->size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

inline
bool EventListenerFactory::unregisterEventListener(
    const EventListenerPtr &pEventListener)
{
    if(pEventListener == NullFC)
        return false;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pEventListenerStore != NULL)
    {
#ifdef OSG_DEBUG
        if (pEventListener.getEventListenerId() >=
                    (*_pEventListenerStore).size())
        {
            FWARNING(("EventListenerFactory::unregisterEventListener:"
                "id %d inconsistent with store size %d!\n", 
                pEventListener.getEventListenerId(), 
                (*_pEventListenerStore).size() ));   
            return true;         
        }
        else
#endif

        (*_pEventListenerStore)[pEventListener.getEventListenerId()] =
            NullFC;
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();
    
    return false;
}

/*-------------------------------------------------------------------------*/
/*                            Invalid Pointer                              */

inline
void EventListenerFactory::setThrowInvalidPointerException(bool s)
{
#ifndef OSG_INVALID_PTR_CHECK
    FFATAL(("EventListenerFactory::setThrowInvalidPointerException: invalid pointer check is not enabled, use the 'invalid_pointer_check' option in the scons build system!\n"));
#else
    _throw_invalid_pointer_exception = s;
#endif
}

inline
bool EventListenerFactory::getThrowInvalidPointerException(void) const
{
    return _throw_invalid_pointer_exception;
}

inline
void EventListenerFactory::checkThrowInvalidPointerException(void) const
{
    if(!_throw_invalid_pointer_exception)
        return;

    throw InvalidPointerException();
}

OSG_END_NAMESPACE

#endif /* _OSGEVENTLISTENERFACTORYIMPL_INL_ */

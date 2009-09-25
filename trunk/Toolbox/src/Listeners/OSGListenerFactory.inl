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

#ifndef _OSGLISTENERFACTORYIMPL_INL_
#define _OSGLISTENERFACTORYIMPL_INL_

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              Mapper                                     */

inline
void ListenerFactory::setMapper(ListenerMapper *pMapper)
{
    _pMapper = pMapper;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
ListenerPtr ListenerFactory::getContainer(
    UInt32 uiContainerId) const
{
    ListenerPtr returnValue = NullFC;

    _pStoreLock->aquire();

    if(uiContainerId < _pListenerStore->size())
    {
        returnValue = (*_pListenerStore)[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

inline
ListenerPtr ListenerFactory::getMappedContainer(
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
UInt32 ListenerFactory::registerListener(
    const ListenerPtr &pListener)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pListenerStore == NULL)
    {
        _pListenerStore = new ListenerStore;

        _pListenerStore->push_back(NullFC);
    }

    _pListenerStore->push_back(pListener);

    returnValue = _pListenerStore->size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

inline
bool ListenerFactory::unregisterListener(
    const ListenerPtr &pListener)
{
    if(pListener == NullFC)
        return false;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pListenerStore != NULL)
    {
#ifdef OSG_DEBUG
        if (pListener.getListenerId() >=
                    (*_pListenerStore).size())
        {
            FWARNING(("ListenerFactory::unregisterListener:"
                "id %d inconsistent with store size %d!\n", 
                pListener.getListenerId(), 
                (*_pListenerStore).size() ));   
            return true;         
        }
        else
#endif

        (*_pListenerStore)[pListener.getListenerId()] =
            NullFC;
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();
    
    return false;
}

/*-------------------------------------------------------------------------*/
/*                            Invalid Pointer                              */

inline
void ListenerFactory::setThrowInvalidPointerException(bool s)
{
#ifndef OSG_INVALID_PTR_CHECK
    FFATAL(("ListenerFactory::setThrowInvalidPointerException: invalid pointer check is not enabled, use the 'invalid_pointer_check' option in the scons build system!\n"));
#else
    _throw_invalid_pointer_exception = s;
#endif
}

inline
bool ListenerFactory::getThrowInvalidPointerException(void) const
{
    return _throw_invalid_pointer_exception;
}

inline
void ListenerFactory::checkThrowInvalidPointerException(void) const
{
    if(!_throw_invalid_pointer_exception)
        return;

    throw InvalidPointerException();
}

OSG_END_NAMESPACE

#endif /* _OSGLISTENERFACTORYIMPL_INL_ */

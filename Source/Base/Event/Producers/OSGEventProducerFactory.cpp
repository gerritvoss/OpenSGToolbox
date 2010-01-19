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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGEventProducerFactory.cpp
    \ingroup GrpSystemEventProducer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <string>

#include "OSGEventProducerFactory.h"
#include "OSGEventProducerType.h"
#include "OSGMethodDescription.h"

#include "OSGFieldType.h"

OSG_USING_NAMESPACE

EventProducerFactory *EventProducerFactory::_the = NULL;

EventProducerFactory::TypeMapIterator 
                       EventProducerFactory::_defaultTypeMapIt;

EventProducerMapper::~EventProducerMapper()
{
}

/*-------------------------------------------------------------------------*/
/*                                The                                      */

EventProducerFactory *EventProducerFactory::the(void)
{
    if(_the == NULL)
        _the = new EventProducerFactory();

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                               Types                                     */

EventProducerType *EventProducerFactory::findType(UInt32 uiTypeId) const
{
    TypeIdMapConstIt  typeIt;
    EventProducerType    *pType = NULL;

    if(_pTypeIdMap)
    {
        typeIt = _pTypeIdMap->find(uiTypeId);
        pType   = (typeIt == _pTypeIdMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

EventProducerType *EventProducerFactory::findType(const std::string &szName) const
{
    TypeNameMapCnstIt   typeIt;
    EventProducerType *pType = NULL;

    if(_pTypeNameMap)
    {
        typeIt = _pTypeNameMap->find(szName);
        pType  = (typeIt == _pTypeNameMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

UInt32 EventProducerFactory::getNumTypes(void) const
{
    return _pTypeNameMap ? _pTypeNameMap->size() : 0;
}

EventProducerType *EventProducerFactory::findUninitializedType(
    const std::string &szName) const
{
    EventProducerType *returnValue = NULL;

    if(_pUnitTypesStore == NULL || szName.empty())
        return returnValue;

    for(UInt32 i = 0; i < _pUnitTypesStore->size(); i++)
    {
        if(szName.compare((*_pUnitTypesStore)[i]->getName()) == 0)
        {
            returnValue = (*_pUnitTypesStore)[i];
            break;
        }
    }

    return returnValue;
}

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

bool EventProducerFactory::initializePendingTypes(void)
{
    bool                returnValue = true;
    EventProducerType *pType       = NULL;

    if(_bInitialized == false)
        return false;

    SINFO << "OSGEventProducerFactory init pending types" << std::endl;

    if(_pUnitTypesStore != NULL)
    {
#ifndef OSG_EMBEDDED
        if(_pMapLock != NULL)
            _pMapLock->acquire();
#endif

        UninitTypeStoreIt uninitIt = _pUnitTypesStore->begin();

        while(uninitIt != _pUnitTypesStore->end())
        {
            pType = *uninitIt;

            if(pType->isInitialized() == true)
            {
                uninitIt = _pUnitTypesStore->erase(uninitIt);

//                (*_pTypeIdMap  )[pType->getId()                 ] = pType;

                TypeIdMap::value_type val(pType->getId(), pType);

                _pTypeIdMap->insert(val);

                (*_pTypeNameMap)[pType->getName()] = pType;
            }
            else
            {
                if(pType->initialize() == true)
                {
                    uninitIt = _pUnitTypesStore->erase(uninitIt);

//                  (*_pTypeIdMap  )[pType->getId()                 ] = pType;

                    TypeIdMap::value_type val(pType->getId(), pType);
                    
                    _pTypeIdMap->insert(val);

                    (*_pTypeNameMap)[pType->getName()] = pType;
                }
                else
                {
                    returnValue = false;

                    uninitIt++;
                }
            }
        }

#ifndef OSG_EMBEDDED
        if(_pMapLock != NULL)
            _pMapLock->release();
#endif

        PINFO << "("
                 << returnValue
                 << "|"
                 << _pUnitTypesStore->size()
                 << ")"
                 << std::endl;
    }

    return returnValue;
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

EventProducerFactory::TypeMapIterator EventProducerFactory::beginTypes(void)
{
    TypeMapIterator returnValue = _defaultTypeMapIt;

    if(_pTypeIdMap != NULL)
    {
        returnValue = _pTypeIdMap->begin();
    }

    return returnValue;
}

EventProducerFactory::TypeMapIterator EventProducerFactory::endTypes(void)
{
    TypeMapIterator returnValue = _defaultTypeMapIt;

    if(_pTypeIdMap != NULL)
    {
        returnValue = _pTypeIdMap->end();
    }

    return returnValue;
}


/*-------------------------------------------------------------------------*/
/*                               Groups                                    */

UInt16 EventProducerFactory::findGroupId(const std::string &szName) const
{
    GroupMapConstIt gIt;

    if (_pGroupMap)
    {
        gIt = _pGroupMap->find(szName);
        return ((gIt == _pGroupMap->end()) ? 0 : (*gIt).second);
    }

    return 0;
}

const std::string &EventProducerFactory::findGroupName(UInt16 uiGroupId) const
{
    GroupMapConstIt gIt;

    for(gIt = _pGroupMap->begin(); gIt != _pGroupMap->end(); gIt++)
    {
        if((*gIt).second == uiGroupId)
            return (*gIt).first;
    }

    return std::string("");
}

UInt16 EventProducerFactory::getNumGroups (void) const
{
    return _pGroupMap ? _pGroupMap->size() : 0;
}


/*-------------------------------------------------------------------------*/
/*                               Create                                    */

/*EventProducerPtr EventProducerFactory::createEventProducer(
    const std::string &name) const
{
    EventProducerPtr returnValue;

    const EventProducerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createEventProducer();

    return returnValue;
}*/

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

/*const EventProducerFactory::EventProducerStore *
    EventProducerFactory::getEventProducerStore(void) const
{
    return _pEventProducerStore;
}*/


/*-------------------------------------------------------------------------*/
/*                            Static Init                                  */

bool EventProducerFactory::initializeFactory(void)
{
    bool returnValue = the()->initialize();

    return returnValue;
}

bool EventProducerFactory::terminateFactory(void)
{
    return the()->terminate();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

EventProducerFactory::EventProducerFactory(void) :
    _bInitialized        (false),
    _pTypeIdMap          (NULL ),
    _pTypeNameMap        (NULL ),
    _pGroupMap           (NULL ),
    _pUnitTypesStore     (NULL ),
    //_pEventProducerStore(NULL ),
    _pStoreLock          (NULL ),
    _pMapLock            (NULL ),
    _pMapper             (NULL ),
    _throw_invalid_pointer_exception(false)
{
    addPostFactoryInitFunction      (&EventProducerFactory::initializeFactory);

    addPostFactoryExitFunction(&EventProducerFactory::terminateFactory );

    initTypeMap();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

EventProducerFactory::~EventProducerFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

bool EventProducerFactory::initialize(void)
{
    TypeIdMapIt typeIt;

    if(_bInitialized == true)
        return true;

    SINFO << "init singleton EventProducerFactory" << std::endl;

    _pStoreLock = ThreadManager::the()->getLock(
        "OSGEventProducerFactory::_pStoreLock",false);

    //addRefP(_pStoreLock);

    _pMapLock   = ThreadManager::the()->getLock(
        "OSGEventProducerFactory::_pMapLock",false);

    //addRefP(_pMapLock);

    //FDEBUG( ("Got shore lock %p, Got map %p",
             //_pStoreLock, _pMapLock) );

    _bInitialized = true;

    initializePendingTypes();

    return _pStoreLock != NULL && _pMapLock != NULL;
}

bool EventProducerFactory::terminate(void)
{
    TypeIdMapIt typeIt;

    SINFO << "terminate singleton EventProducerFactory" << std::endl;

    if(_bInitialized == false)
        return true;

    if(_pTypeIdMap != NULL)
    {
        int i = 0;
        for(  typeIt  = _pTypeIdMap->begin();
              typeIt != _pTypeIdMap->end();
            ++typeIt)
        {
            (*typeIt).second->terminate();

            i++;
        }
    }

    //subRefP(_pStoreLock);
    //subRefP(_pMapLock);

    _bInitialized = false;

    return true;
}

void EventProducerFactory::initTypeMap(void)
{
    if(_pTypeIdMap   == NULL &&
       _pTypeNameMap == NULL)
    {
        _pTypeIdMap      = new TypeIdMap;
        _pTypeNameMap    = new TypeNameMap;
        _pGroupMap       = new GroupMap;
        _pUnitTypesStore = new UninitializedTypeStore;
    }
}

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

UInt32 EventProducerFactory::registerType(EventProducerType *pType)
{
    UInt32 returnValue = 0;
#ifndef OSG_EMBEDDED
    if(_pMapLock != NULL)
        _pMapLock->acquire();
#endif

    if(pType->getId() != 0)
    {
        _pUnitTypesStore->push_back(pType);
    }

#ifndef OSG_EMBEDDED
    if(_pMapLock != NULL)
        _pMapLock->release();
#endif

    return returnValue;
}

UInt16 EventProducerFactory::registerGroup(const std::string &szName)
{
    UInt16 returnValue;

    if(szName.empty())
    {
        SWARNING << "EventProducer Group without name" << std::endl;
        return 0;
    }

    returnValue = findGroupId(szName);

    if(returnValue == 0)
    {
#ifndef OSG_EMBEDDED
        if(_pMapLock != NULL)
            _pMapLock->acquire();
#endif

        returnValue                         = _pGroupMap->size() + 1;

        (*_pGroupMap)[szName] = returnValue;

#ifndef OSG_EMBEDDED
        if(_pMapLock != NULL)
            _pMapLock->release();
#endif
    }

    return returnValue;
}

void EventProducerFactory::unregisterType(EventProducerType *pType)
{
    TypeIdMapIt   typeIdIt;
    TypeNameMapIt typeNameIt;

    if(pType == NULL)
        return;

    if(_pTypeIdMap)
    {
        UInt32 uiId =  pType->getId();

        typeIdIt    = _pTypeIdMap->find(uiId);

        if(typeIdIt != _pTypeIdMap->end())
        {
            _pTypeIdMap->erase(typeIdIt);
        }
    }

    if(_pTypeNameMap)
    {
        typeNameIt = _pTypeNameMap->find(pType->getName());

        if(typeNameIt != _pTypeNameMap->end())
        {
            _pTypeNameMap->erase(typeNameIt);
        }
    }
}

bool EventProducerFactory::pluginInit(void)
{
    return EventProducerFactory::the()->initializePendingTypes();
}

bool EventProducerFactory::registerPlugin(void)
{
    if(GlobalSystemState == Running)
        addPostFactoryInitFunction(&EventProducerFactory::pluginInit);

    return true;
}

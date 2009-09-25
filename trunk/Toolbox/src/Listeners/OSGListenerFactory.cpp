/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGListenerFactory.cpp
    \ingroup GrpSystemListener
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include <iostream>
#include <string>

#include "OSGListenerFactory.h"
#include "OSGListenerType.h"
#include "OSGMethodDescription.h"

#include <OpenSG/OSGFieldFactory.h>
#include <OpenSG/OSGFieldType.h>

OSG_USING_NAMESPACE

ListenerFactory *ListenerFactory::_the = NULL;

ListenerFactory::TypeMapIterator 
                       ListenerFactory::_defaultTypeMapIt;

ListenerMapper::~ListenerMapper()
{
}

/*-------------------------------------------------------------------------*/
/*                                The                                      */

ListenerFactory *ListenerFactory::the(void)
{
    if(_the == NULL)
        _the = new ListenerFactory();

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                               Types                                     */

ListenerType *ListenerFactory::findType(UInt32 uiTypeId) const
{
    TypeIdMapConstIt  typeIt;
    ListenerType    *pType = NULL;

    if(_pTypeIdMap)
    {
        typeIt = _pTypeIdMap->find(uiTypeId);
        pType   = (typeIt == _pTypeIdMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

ListenerType *ListenerFactory::findType(const Char8 *szName) const
{
    TypeNameMapCnstIt   typeIt;
    ListenerType *pType = NULL;

    if(_pTypeNameMap)
    {
        typeIt = _pTypeNameMap->find(IDStringLink(szName));
        pType  = (typeIt == _pTypeNameMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

UInt32 ListenerFactory::getNumTypes(void) const
{
    return _pTypeNameMap ? _pTypeNameMap->size() : 0;
}

ListenerType *ListenerFactory::findUninitializedType(
    const Char8  *szName) const
{
    ListenerType *returnValue = NULL;

    if(_pUnitTypesStore == NULL || szName == NULL)
        return returnValue;

    for(UInt32 i = 0; i < _pUnitTypesStore->size(); i++)
    {
        if(stringcmp(szName, (*_pUnitTypesStore)[i]->getCName()) == 0)
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

bool ListenerFactory::initializePendingTypes(void)
{
    bool                returnValue = true;
    ListenerType *pType       = NULL;

    if(_bInitialized == false)
        return false;

    SINFO << "OSGListenerFactory init pending types" << std::endl;

    if(_pUnitTypesStore != NULL)
    {
        if(_pMapLock != NULL)
            _pMapLock->aquire();

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

                (*_pTypeNameMap)[IDStringLink(pType->getCName())] = pType;
            }
            else
            {
                if(pType->initialize() == true)
                {
                    uninitIt = _pUnitTypesStore->erase(uninitIt);

//                  (*_pTypeIdMap  )[pType->getId()                 ] = pType;

                    TypeIdMap::value_type val(pType->getId(), pType);
                    
                    _pTypeIdMap->insert(val);

                    (*_pTypeNameMap)[IDStringLink(pType->getCName())] = pType;
                }
                else
                {
                    returnValue = false;

                    uninitIt++;
                }
            }
        }

        if(_pMapLock != NULL)
            _pMapLock->release();

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

ListenerFactory::TypeMapIterator ListenerFactory::beginTypes(void)
{
    TypeMapIterator returnValue = _defaultTypeMapIt;

    if(_pTypeIdMap != NULL)
    {
        returnValue = _pTypeIdMap->begin();
    }

    return returnValue;
}

ListenerFactory::TypeMapIterator ListenerFactory::endTypes(void)
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

UInt16 ListenerFactory::findGroupId(const Char8 *szName) const
{
    GroupMapConstIt gIt;

    if (_pGroupMap)
    {
        gIt = _pGroupMap->find(IDStringLink(szName));
        return ((gIt == _pGroupMap->end()) ? 0 : (*gIt).second);
    }

    return 0;
}

const Char8 *ListenerFactory::findGroupName(UInt16 uiGroupId) const
{
    GroupMapConstIt gIt;

    for(gIt = _pGroupMap->begin(); gIt != _pGroupMap->end(); gIt++)
    {
        if((*gIt).second == uiGroupId)
            return (*gIt).first.str();
    }

    return NULL;
}

UInt16 ListenerFactory::getNumGroups (void) const
{
    return _pGroupMap ? _pGroupMap->size() : 0;
}


/*-------------------------------------------------------------------------*/
/*                               Create                                    */

/*ListenerPtr ListenerFactory::createListener(
    const Char8 *name) const
{
    ListenerPtr returnValue;

    const ListenerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createListener();

    return returnValue;
}*/

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

/*const ListenerFactory::ListenerStore *
    ListenerFactory::getListenerStore(void) const
{
    return _pListenerStore;
}*/


/*-------------------------------------------------------------------------*/
/*                            Static Init                                  */

bool ListenerFactory::initializeFactory(void)
{
    bool returnValue = the()->initialize();

    // CHECKCHECK
    // clear changelist from prototypes, move this to a different place soon
    OSG::Thread::getCurrentChangeList()->clearAll();

    return returnValue;
}

bool ListenerFactory::terminateFactory(void)
{
    return the()->terminate();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

ListenerFactory::ListenerFactory(void) :
    _bInitialized        (false),
    _pTypeIdMap          (NULL ),
    _pTypeNameMap        (NULL ),
    _pGroupMap           (NULL ),
    _pUnitTypesStore     (NULL ),
    //_pListenerStore(NULL ),
    _pStoreLock          (NULL ),
    _pMapLock            (NULL ),
    _pMapper             (NULL ),
    _throw_invalid_pointer_exception(false)
{
    //addInitFunction      (&ListenerPtr::initialize           );
    addInitFunction      (&ListenerFactory::initializeFactory);

    //addSystemExitFunction(&ListenerPtr::terminate            );
    addSystemExitFunction(&ListenerFactory::terminateFactory );

    initTypeMap();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

ListenerFactory::~ListenerFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

bool ListenerFactory::initialize(void)
{
    TypeIdMapIt typeIt;

    if(_bInitialized == true)
        return true;

    SINFO << "init singleton ListenerFactory" << std::endl;

    _pStoreLock = ThreadManager::the()->getLock(
        "OSGListenerFactory::_pStoreLock");

    addRefP(_pStoreLock);

    _pMapLock   = ThreadManager::the()->getLock(
        "OSGListenerFactory::_pMaoLock");

    addRefP(_pMapLock);

    FDEBUG( ("Got shore lock %p, Got map %p",
             _pStoreLock, _pMapLock) );

    _bInitialized = true;

    initializePendingTypes();

    return _pStoreLock != NULL && _pMapLock != NULL;
}

bool ListenerFactory::terminate(void)
{
    TypeIdMapIt typeIt;

    SINFO << "terminate singleton ListenerFactory" << std::endl;

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

    subRefP(_pStoreLock);
    subRefP(_pMapLock);

    _bInitialized = false;

    return true;
}

void ListenerFactory::initTypeMap(void)
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

UInt32 ListenerFactory::registerType(ListenerType *pType)
{
    UInt32 returnValue = 0;

    if(_pMapLock != NULL)
        _pMapLock->aquire();

    if(pType->getId() != 0)
    {
        _pUnitTypesStore->push_back(pType);
    }

    if(_pMapLock != NULL)
        _pMapLock->release();

    return returnValue;
}

UInt16 ListenerFactory::registerGroup(const Char8 *szName)
{
    UInt16 returnValue;

    if(szName == NULL || *szName == '\0')
    {
        SWARNING << "Group without name" << std::endl;
        return 0;
    }

    returnValue = findGroupId(szName);

    if(returnValue == 0)
    {
        if(_pMapLock != NULL)
            _pMapLock->aquire();

        returnValue                         = _pGroupMap->size() + 1;

        (*_pGroupMap)[IDStringLink(szName)] = returnValue;

        if(_pMapLock != NULL)
            _pMapLock->release();
    }

    return returnValue;
}

void ListenerFactory::unregisterType(ListenerType *pType)
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
        typeNameIt = _pTypeNameMap->find(IDStringLink(pType->getCName()));

        if(typeNameIt != _pTypeNameMap->end())
        {
            _pTypeNameMap->erase(typeNameIt);
        }
    }
}

bool ListenerFactory::pluginInit(void)
{
    return ListenerFactory::the()->initializePendingTypes();
}

bool ListenerFactory::registerPlugin(void)
{
    if(GlobalSystemState == Running)
        addInitFunction(&ListenerFactory::pluginInit);

    return true;
}

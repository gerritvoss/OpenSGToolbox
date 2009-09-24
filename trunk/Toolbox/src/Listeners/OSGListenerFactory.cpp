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
/*! \file OSGFieldContainerFactory.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <string>

#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerType.h"
#include "OSGFieldDescription.h"

#include "OSGNodePtr.h"
#include "OSGAttachmentPtr.h"

#include "OSGFieldFactory.h"
#include "OSGFieldType.h"

OSG_USING_NAMESPACE

FieldContainerFactory *FieldContainerFactory::_the = NULL;

FieldContainerFactory::TypeMapIterator 
                       FieldContainerFactory::_defaultTypeMapIt;

FieldContainerMapper::~FieldContainerMapper()
{
}

InvalidPointerException::InvalidPointerException() : Exception()
{
    _what += "FieldContainerFactory: invalid pointer access!";
}

/*-------------------------------------------------------------------------*/
/*                                The                                      */

FieldContainerFactory *FieldContainerFactory::the(void)
{
    if(_the == NULL)
        _the = new FieldContainerFactory();

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                               Types                                     */

FieldContainerType *FieldContainerFactory::findType(UInt32 uiTypeId) const
{
    TypeIdMapConstIt  typeIt;
    FieldContainerType    *pType = NULL;

    if(_pTypeIdMap)
    {
        typeIt = _pTypeIdMap->find(uiTypeId);
        pType   = (typeIt == _pTypeIdMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

FieldContainerType *FieldContainerFactory::findType(const Char8 *szName) const
{
    TypeNameMapCnstIt   typeIt;
    FieldContainerType *pType = NULL;

    if(_pTypeNameMap)
    {
        typeIt = _pTypeNameMap->find(IDStringLink(szName));
        pType  = (typeIt == _pTypeNameMap->end()) ? NULL : (*typeIt).second;
    }

    return pType;
}

UInt32 FieldContainerFactory::getNumTypes(void) const
{
    return _pTypeNameMap ? _pTypeNameMap->size() : 0;
}

FieldContainerType *FieldContainerFactory::findUninitializedType(
    const Char8  *szName) const
{
    FieldContainerType *returnValue = NULL;

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

bool FieldContainerFactory::initializePendingTypes(void)
{
    bool                returnValue = true;
    FieldContainerType *pType       = NULL;

    if(_bInitialized == false)
        return false;

    SINFO << "OSGFieldContainerFactory init pending types" << std::endl;

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

FieldContainerFactory::TypeMapIterator FieldContainerFactory::beginTypes(void)
{
    TypeMapIterator returnValue = _defaultTypeMapIt;

    if(_pTypeIdMap != NULL)
    {
        returnValue = _pTypeIdMap->begin();
    }

    return returnValue;
}

FieldContainerFactory::TypeMapIterator FieldContainerFactory::endTypes(void)
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

UInt16 FieldContainerFactory::findGroupId(const Char8 *szName) const
{
    GroupMapConstIt gIt;

    if (_pGroupMap)
    {
        gIt = _pGroupMap->find(IDStringLink(szName));
        return ((gIt == _pGroupMap->end()) ? 0 : (*gIt).second);
    }

    return 0;
}

const Char8 *FieldContainerFactory::findGroupName(UInt16 uiGroupId) const
{
    GroupMapConstIt gIt;

    for(gIt = _pGroupMap->begin(); gIt != _pGroupMap->end(); gIt++)
    {
        if((*gIt).second == uiGroupId)
            return (*gIt).first.str();
    }

    return NULL;
}

UInt16 FieldContainerFactory::getNumGroups (void) const
{
    return _pGroupMap ? _pGroupMap->size() : 0;
}


/*-------------------------------------------------------------------------*/
/*                               Create                                    */

FieldContainerPtr FieldContainerFactory::createFieldContainer(
    const Char8 *name) const
{
    FieldContainerPtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createFieldContainer();

    return returnValue;
}

NodePtr FieldContainerFactory::createNode(const Char8 *name) const
{
    NodePtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createNode();

    return returnValue;
}

NodeCorePtr FieldContainerFactory::createNodeCore(
    const Char8 *name) const
{
    NodeCorePtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createNodeCore();

    return returnValue;
}

AttachmentPtr FieldContainerFactory::createAttachment(
    const Char8 *name) const
{
    AttachmentPtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = pType->createAttachment();

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                            Write FCD                                    */

/* type output */
/* name given: output only the given type,
   out given: output all types into the stream,
   no name, no out: output all types into separate files
*/

void FieldContainerFactory::writeFCD(const Char8 * name, std::ostream *out)
{
          TypeIdMapIt         type;
    const FieldContainerType *pType = NULL;

    if(_pTypeIdMap == NULL)
        return;

    if(name != NULL)
    {
        pType  = findType(name);

        if(pType == NULL)
        {
            SWARNING << "FieldContainerFactory::writeFCD: type " << name
                     << " is unknown!" << std::endl;
            return;
        }

        if(out != NULL)
        {
            writeSingleTypeFCD(*out, pType);
        }
        else
        {
            std::string s(pType->getCName());

            s.append(".fcd");

            std::ofstream f(s.c_str());

            writeSingleTypeFCD(f, pType);
        }

        return;
    }

    // write header once?
    if(out != NULL)
    {
        *out << "<?xml version=\"1.0\" ?>" << std::endl << std::endl;
    }

    for(  type  = _pTypeIdMap->begin();
          type != _pTypeIdMap->end  ();
        ++type)
    {
        if(out != NULL)
        {
            writeSingleTypeFCD(*out, (*type).second);
        }
        else
        {
            std::string s((*type).second->getCName());

            s.append(".fcd");

            std::ofstream f(s.c_str());

            f << "<?xml version=\"1.0\" ?>" << std::endl << std::endl;

            writeSingleTypeFCD(f, (*type).second);
        }

        if(out != NULL)
        {
            *out << std::endl;
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

const FieldContainerFactory::FieldContainerStore *
    FieldContainerFactory::getFieldContainerStore(void) const
{
    return _pFieldContainerStore;
}


/*-------------------------------------------------------------------------*/
/*                            Static Init                                  */

bool FieldContainerFactory::initializeFactory(void)
{
    bool returnValue = the()->initialize();

    // CHECKCHECK
    // clear changelist from prototypes, move this to a different place soon
    OSG::Thread::getCurrentChangeList()->clearAll();

    return returnValue;
}

bool FieldContainerFactory::terminateFactory(void)
{
    return the()->terminate();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FieldContainerFactory::FieldContainerFactory(void) :
    _bInitialized        (false),
    _pTypeIdMap          (NULL ),
    _pTypeNameMap        (NULL ),
    _pGroupMap           (NULL ),
    _pUnitTypesStore     (NULL ),
    _pFieldContainerStore(NULL ),
    _pStoreLock          (NULL ),
    _pMapLock            (NULL ),
    _pMapper             (NULL ),
    _throw_invalid_pointer_exception(false)
{
    addInitFunction      (&FieldContainerPtr::initialize           );
    addInitFunction      (&FieldContainerFactory::initializeFactory);

    addSystemExitFunction(&FieldContainerPtr::terminate            );
    addSystemExitFunction(&FieldContainerFactory::terminateFactory );

    initTypeMap();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FieldContainerFactory::~FieldContainerFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

bool FieldContainerFactory::initialize(void)
{
    TypeIdMapIt typeIt;

    if(_bInitialized == true)
        return true;

    SINFO << "init singleton FieldContainerFactory" << std::endl;

    _pStoreLock = ThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_pStoreLock");

    addRefP(_pStoreLock);

    _pMapLock   = ThreadManager::the()->getLock(
        "OSGFieldContainerFactory::_pMaoLock");

    addRefP(_pMapLock);

    FDEBUG( ("Got shore lock %p, Got map %p",
             _pStoreLock, _pMapLock) );

    _bInitialized = true;

    initializePendingTypes();

    return _pStoreLock != NULL && _pMapLock != NULL;
}

bool FieldContainerFactory::terminate(void)
{
    TypeIdMapIt typeIt;

    SINFO << "terminate singleton FieldContainerFactory" << std::endl;

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

void FieldContainerFactory::initTypeMap(void)
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

UInt32 FieldContainerFactory::registerType(FieldContainerType *pType)
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

UInt16 FieldContainerFactory::registerGroup(const Char8 *szName)
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

void FieldContainerFactory::unregisterType(FieldContainerType *pType)
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

bool FieldContainerFactory::pluginInit(void)
{
    return FieldContainerFactory::the()->initializePendingTypes();
}

bool FieldContainerFactory::registerPlugin(void)
{
    if(GlobalSystemState == Running)
        addInitFunction(&FieldContainerFactory::pluginInit);

    return true;
}

/*-------------------------------------------------------------------------*/
/*                      Write Single FCD                                   */

void FieldContainerFactory::writeSingleTypeFCD(      std::ostream       &out, 
                                               const FieldContainerType *t  )
{
    FieldContainerType *parent = t->getParent();

    out << "<FieldContainer"                          << std::endl;
    out << "\tname=\""       << t->getCName() << "\"" << std::endl;

    if(parent != NULL)
        out << "\tparent=\"" << parent->getCName() << "\"" << std::endl;
    
    out << "\tlibrary=\""
        << "???"
        << "\"" 
        << std::endl;
    out << "\tstructure=\"" 
        << ( t->isAbstract()?"abstract":"concrete" ) 
        << "\""
        << std::endl;

    // look for pointerfield types
           std::string s;
           Int32       pt        = 0;
    static const Char8 *pftypes[] = {"none", "single", "multi", "both"};

    s  = "SF";
    s += t->getCName();
    s += "Ptr";

    if(FieldFactory::the().getFieldType(s.c_str()) != NULL)
    {
        pt |= 1;
    }

    s  = "MF";
    s += t->getCName();
    s += "Ptr";
    
    if(FieldFactory::the().getFieldType(s.c_str()) != NULL)
    {
        pt |= 2;
    }

    out << "\tpointerfieldtypes=\"" << pftypes[pt] << "\"" << std::endl;
    out << ">"                                             << std::endl;

    // Print the fields in this FC, ignore the parents' fields
    // !!! This should start at 0, FIX ME

    for(UInt32 i  = parent ? parent->getNumFieldDescs() + 1 : 1;
               i <= t->getNumFieldDescs();
               i++)
    {
        const FieldDescription *f  = t->getFieldDescription(i);
              FieldType        *ft = NULL;

        ft = FieldFactory::the().getFieldType(f->getTypeId());

        out << "\t<Field"                             << std::endl;
        out << "\t\tname=\"" << f->getCName() << "\"" << std::endl;

        // Filter the SF/MF from the type
        const Char8 *c = ft->getCName();

        if (! strncmp(c, "SF", 2) || ! strncmp(c, "MF", 2))
        {
            c += 2;
        }

        out << "\t\ttype=\"" << c << "\"" << std::endl;

        out << "\t\tcardinality=\""
            << (ft->getCardinality() ? "multi" : "single")
            << "\"" << std::endl;

        out << "\t\tvisibility=\"" 
            << (f->isInternal() ? "internal" : "external")
            << "\"" 
            << std::endl;
        
        out << "\t>"        << std::endl;
        out << "\t</Field>" << std::endl;
    }

    out << "</FieldContainer>" << std::endl;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINERFACTORY_HEADER_CVSID;
}

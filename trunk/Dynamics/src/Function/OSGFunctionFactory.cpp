#ifdef OSG_DOC_FILES_IN_MODULE

#endif

#include "OSGFunctionFactory.h"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGFieldDescription.h>

#include <OpenSG/OSGFieldFactory.h>
#include <OpenSG/OSGFieldType.h>

OSG_USING_NAMESPACE

FunctionFactory *FunctionFactory::_the = NULL;

FunctionFactory::TypeMapIterator 
                       FunctionFactory::_defaultTypeMapIt;

FieldContainerMapper::~FieldContainerMapper()
{
}
 
/*-------------------------------------------------------------------------*/
/*                                The                                      */

FunctionFactory *FunctionFactory::the(void)
{
    if(_the == NULL)
        _the = new FunctionFactory();

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                               Types                                     */

FieldContainerType *FunctionFactory::findType(UInt32 uiTypeId) const
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

FieldContainerType *FunctionFactory::findType(const Char8 *szName) const
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

UInt32 FunctionFactory::getNumTypes(void) const
{
    return _pTypeNameMap ? _pTypeNameMap->size() : 0;
}

/*FieldContainerType *FunctionFactory::findUninitializedType(
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
}*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

/*bool FunctionFactory::initializePendingTypes(void)
{
    bool                returnValue = true;
    FieldContainerType *pType       = NULL;

    if(_bInitialized == false)
        return false;

    SINFO << "OSGFunctionFactory init pending types" << std::endl;

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
}*/

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

FunctionFactory::TypeMapIterator FunctionFactory::beginTypes(void)
{
    TypeMapIterator returnValue = _defaultTypeMapIt;

    if(_pTypeIdMap != NULL)
    {
        returnValue = _pTypeIdMap->begin();
    }

    return returnValue;
}

FunctionFactory::TypeMapIterator FunctionFactory::endTypes(void)
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

UInt16 FunctionFactory::findGroupId(const Char8 *szName) const
{
    GroupMapConstIt gIt;

    if (_pGroupMap)
    {
        gIt = _pGroupMap->find(IDStringLink(szName));
        return ((gIt == _pGroupMap->end()) ? 0 : (*gIt).second);
    }

    return 0;
}

const Char8 *FunctionFactory::findGroupName(UInt16 uiGroupId) const
{
    GroupMapConstIt gIt;

    for(gIt = _pGroupMap->begin(); gIt != _pGroupMap->end(); gIt++)
    {
        if((*gIt).second == uiGroupId)
            return (*gIt).first.str();
    }

    return NULL;
}

UInt16 FunctionFactory::getNumGroups (void) const
{
    return _pGroupMap ? _pGroupMap->size() : 0;
}


/*-------------------------------------------------------------------------*/
/*                               Create                                    */

FunctionPtr FunctionFactory::createFunction(
    const Char8 *name) const
{
    FunctionPtr returnValue;

    const FieldContainerType *pType = findType(name);

    if(pType != NULL)
        returnValue = Function::Ptr::dcast(pType->createFieldContainer());

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                            Write FCD                                    */

/* type output */
/* name given: output only the given type,
   out given: output all types into the stream,
   no name, no out: output all types into separate files
*/

void FunctionFactory::writeFCD(Char8 * name, std::ostream *out)
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
            SWARNING << "FunctionFactory::writeFCD: type " << name
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

const FunctionFactory::FunctionStore *
    FunctionFactory::getFunctionStore(void) const
{
    return _pFunctionStore;
}


/*-------------------------------------------------------------------------*/
/*                            Static Init                                  */

bool FunctionFactory::initializeFactory(void)
{
    bool returnValue = the()->initialize();

    // CHECKCHECK
    // clear changelist from prototypes, move this to a different place soon
    OSG::Thread::getCurrentChangeList()->clearAll();

    return returnValue;
}

bool FunctionFactory::terminateFactory(void)
{
    return the()->terminate();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

FunctionFactory::FunctionFactory(void) :
    _bInitialized        (false),
    _pTypeIdMap          (NULL ),
    _pTypeNameMap        (NULL ),
    _pGroupMap           (NULL ),
    _pUnitTypesStore     (NULL ),
    _pFunctionStore(NULL ),
    _pStoreLock          (NULL ),
    _pMapLock            (NULL ),
    _pMapper             (NULL )
{
    //addInitFunction      (&FunctionPtr::initialize           );
    addInitFunction      (&FunctionFactory::initializeFactory);

    //addSystemExitFunction(&FunctionPtr::terminate            );
    addSystemExitFunction(&FunctionFactory::terminateFactory );

    initTypeMap();
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

FunctionFactory::~FunctionFactory(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Init                                     */

bool FunctionFactory::initialize(void)
{
    TypeIdMapIt typeIt;

    if(_bInitialized == true)
        return true;

    SINFO << "init singleton FunctionFactory" << std::endl;

    _pStoreLock = ThreadManager::the()->getLock(
        "OSGFunctionFactory::_pStoreLock");

    addRefP(_pStoreLock);

    _pMapLock   = ThreadManager::the()->getLock(
        "OSGFunctionFactory::_pMaoLock");

    addRefP(_pMapLock);

    FDEBUG( ("Got shore lock %p, Got map %p",
             _pStoreLock, _pMapLock) );

    _bInitialized = true;

    //initializePendingTypes();

    return _pStoreLock != NULL && _pMapLock != NULL;
}

bool FunctionFactory::terminate(void)
{
    TypeIdMapIt typeIt;

    SINFO << "terminate singleton FunctionFactory" << std::endl;

    if(_bInitialized == false)
        return true;

    /*if(_pTypeIdMap != NULL)
    {
        int i = 0;
        for(  typeIt  = _pTypeIdMap->begin();
              typeIt != _pTypeIdMap->end();
            ++typeIt)
        {
            (*typeIt).second->terminate();

            i++;
        }
    }*/

    subRefP(_pStoreLock);
    subRefP(_pMapLock);

    _bInitialized = false;

    return true;
}

void FunctionFactory::initTypeMap(void)
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

UInt32 FunctionFactory::registerType(FieldContainerType *pType)
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

UInt16 FunctionFactory::registerGroup(const Char8 *szName)
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

void FunctionFactory::unregisterType(FieldContainerType *pType)
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

/*-------------------------------------------------------------------------*/
/*                      Write Single FCD                                   */

void FunctionFactory::writeSingleTypeFCD(      std::ostream       &out, 
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
    static Char8 *pftypes[] = {"none", "single", "multi", "both"};

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

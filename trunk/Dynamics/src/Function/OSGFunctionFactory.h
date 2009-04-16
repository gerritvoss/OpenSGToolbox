#ifndef _OSGFUNCTIONFACTORY_H_
#define _OSGFUNCTIONFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGDynamicsDef.h"

#include "OSGFunction.h"
#include <OpenSG/OSGBase.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGIDStringLink.h>

#include <map>

OSG_BEGIN_NAMESPACE

class OSG_DYNAMICSLIB_DLLMAPPING FunctionFactory
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map   <UInt32,       
                        FieldContainerType        *> TypeIdMap;
    typedef std::map   <IDStringLink, 
                        FieldContainerType        *> TypeNameMap;
    typedef std::map   <IDStringLink, 
                        UInt16                     > GroupMap;

    typedef std::vector<FieldContainerType        *> UninitializedTypeStore;
    typedef std::vector<FunctionPtr          > FunctionStore;

    typedef TypeIdMap             ::iterator         TypeIdMapIt;
    typedef TypeNameMap           ::iterator         TypeNameMapIt;
    typedef GroupMap              ::iterator         GroupMapIt;
    typedef UninitializedTypeStore::iterator         UninitTypeStoreIt;
    typedef FunctionStore   ::iterator         FunctionStoreIt;

    typedef TypeIdMap             ::const_iterator   TypeIdMapConstIt;
    typedef TypeNameMap           ::const_iterator   TypeNameMapCnstIt;
    typedef GroupMap              ::const_iterator   GroupMapConstIt;


    /*==========================  PUBLIC  =================================*/

  public :

    typedef TypeIdMapIt TypeMapIterator;

    static FunctionFactory *the(void);

    /*---------------------------------------------------------------------*/
    FieldContainerType *findType    (      UInt32  uiTypeId) const;
    FieldContainerType *findType    (const Char8  *szName  ) const;
    UInt32              getNumTypes (void                  ) const;


    //FieldContainerType *findUninitializedType (const Char8  *szName) const;

    //bool                initializePendingTypes(      void          );

    TypeMapIterator     beginTypes            (      void          );
    TypeMapIterator     endTypes              (      void          );

    /*---------------------------------------------------------------------*/
          UInt16  findGroupId  (const Char8  *szName   ) const;
    const Char8  *findGroupName(      UInt16  uiGroupId) const;
        
          UInt16  getNumGroups (      void             ) const;

    /*---------------------------------------------------------------------*/
    void setMapper(FieldContainerMapper *pMapper);

    /*---------------------------------------------------------------------*/
    FunctionPtr getFunction      (UInt32 uiFieldContainerId) const;
    FunctionPtr getMappedFunction(UInt32 uiFieldContainerId) const;

    /*---------------------------------------------------------------------*/
    FunctionPtr createFunction(const Char8 *name) const;

    /*---------------------------------------------------------------------*/
    void writeFCD(Char8 *name = NULL, std::ostream *out = NULL);
    
    /*---------------------------------------------------------------------*/
    const FunctionStore *getFunctionStore(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    static FunctionFactory *_the;

    static TypeMapIterator        _defaultTypeMapIt;

    /*---------------------------------------------------------------------*/
    static bool initializeFactory(void);
    static bool terminateFactory (void);

    /*---------------------------------------------------------------------*/
    bool                    _bInitialized;

    TypeIdMap              *_pTypeIdMap;
    TypeNameMap            *_pTypeNameMap;
    GroupMap               *_pGroupMap;
    UninitializedTypeStore *_pUnitTypesStore;
    FunctionStore    *_pFunctionStore;

    Lock                   *_pStoreLock;
    Lock                   *_pMapLock;

    FieldContainerMapper   *_pMapper;

    /*---------------------------------------------------------------------*/
    FunctionFactory(void);

    /*---------------------------------------------------------------------*/
    virtual ~FunctionFactory(void); 

    /*---------------------------------------------------------------------*/
    bool   initialize (void);
    bool   terminate  (void);

    void   initTypeMap(void);

    /*---------------------------------------------------------------------*/
    bool   unregisterFunction(const FunctionPtr  &pFieldContainer);
    UInt32   registerFunction(const FunctionPtr  &pFieldContainer);

    UInt32 registerType            (      FieldContainerType *pType          );
    UInt16 registerGroup           (const Char8              *szName         );
    void   unregisterType          (      FieldContainerType *pType          );

    /*---------------------------------------------------------------------*/
    void writeSingleTypeFCD(std::ostream &out, const FieldContainerType *type);

    /*==========================  PRIVATE  ================================*/

  private:

    friend class Function;

    FunctionFactory(const FunctionFactory &source);
    void operator =(const FunctionFactory &source);
};

OSG_END_NAMESPACE

#include "OSGFunctionFactory.inl"

#define OSGFUNCTIONFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFUNCTIONFACTORY_H_ */
        

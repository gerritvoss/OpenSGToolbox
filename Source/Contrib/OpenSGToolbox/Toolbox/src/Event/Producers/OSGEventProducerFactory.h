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

#ifndef _OSGEVENTPRODUCERFACTORYIMPL_H_
#define _OSGEVENTPRODUCERFACTORYIMPL_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGException.h>
#include <OpenSG/OSGIDStringLink.h>
#include <OpenSG/OSGFieldContainerFactory.h>
#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

class Lock;
class EventProducerType;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemEventProducer
 */

struct OSG_TOOLBOXLIB_DLLMAPPING EventProducerMapper
{
    virtual ~EventProducerMapper();
    
    virtual UInt32 map(UInt32 uiId) = 0;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemEventProducer
 */

class OSG_TOOLBOXLIB_DLLMAPPING EventProducerFactory
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map   <UInt32,       
                        EventProducerType        *> TypeIdMap;
    typedef std::map   <IDStringLink, 
                        EventProducerType        *> TypeNameMap;
    typedef std::map   <IDStringLink, 
                        UInt16                     > GroupMap;

    typedef std::vector<EventProducerType        *> UninitializedTypeStore;
    //typedef std::vector<EventProducerPtr          > EventProducerStore;

    typedef TypeIdMap             ::iterator         TypeIdMapIt;
    typedef TypeNameMap           ::iterator         TypeNameMapIt;
    typedef GroupMap              ::iterator         GroupMapIt;
    typedef UninitializedTypeStore::iterator         UninitTypeStoreIt;
    //typedef EventProducerStore   ::iterator         EventProducerStoreIt;

    typedef TypeIdMap             ::const_iterator   TypeIdMapConstIt;
    typedef TypeNameMap           ::const_iterator   TypeNameMapCnstIt;
    typedef GroupMap              ::const_iterator   GroupMapConstIt;


    /*==========================  PUBLIC  =================================*/

  public :

    typedef TypeIdMapIt TypeMapIterator;

    static EventProducerFactory *the(void);

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */
        
    EventProducerType *findType    (      UInt32  uiTypeId) const;
    EventProducerType *findType    (const Char8  *szName  ) const;
    UInt32              getNumTypes (void                  ) const;


    EventProducerType *findUninitializedType (const Char8  *szName) const;

    bool                initializePendingTypes(      void          );

    TypeMapIterator     beginTypes            (      void          );
    TypeMapIterator     endTypes              (      void          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Groups                                   */
    /*! \{                                                                 */

          UInt16  findGroupId  (const Char8  *szName   ) const;
    const Char8  *findGroupName(      UInt16  uiGroupId) const;
        
          UInt16  getNumGroups (      void             ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Mapper                                  */
    /*! \{                                                                 */

    void setMapper(EventProducerMapper *pMapper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get EventProducer                          */
    /*! \{                                                                 */

    //EventProducerPtr getContainer      (UInt32 uiEventProducerId) const;
    //EventProducerPtr getMappedContainer(UInt32 uiEventProducerId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Create Base EventProducer                      */
    /*! \{                                                                 */

    //EventProducerPtr createEventProducer(const Char8 *name) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Write FCD From Name                            */
    /*! \{                                                                 */

    void writeFCD(const Char8 *name = NULL, std::ostream *out = NULL);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Get Containerstore                             */
    /*! \{                                                                 */

    //const EventProducerStore *getEventProducerStore(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Invalid Pointer                              */
    /*! \{                                                                 */

    void setThrowInvalidPointerException(bool s);
    bool getThrowInvalidPointerException(void) const;
    void checkThrowInvalidPointerException(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Plugin init                                  */
    /*! \{                                                                 */

    static bool registerPlugin(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    static EventProducerFactory *_the;

    static TypeMapIterator        _defaultTypeMapIt;

    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    static bool initializeFactory(void);
    static bool terminateFactory (void);
    static bool pluginInit       (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    bool                    _bInitialized;

    TypeIdMap              *_pTypeIdMap;
    TypeNameMap            *_pTypeNameMap;
    GroupMap               *_pGroupMap;
    UninitializedTypeStore *_pUnitTypesStore;
    //EventProducerStore    *_pEventProducerStore;

    Lock                   *_pStoreLock;
    Lock                   *_pMapLock;

    EventProducerMapper   *_pMapper;

    bool                    _throw_invalid_pointer_exception;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    EventProducerFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~EventProducerFactory(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name         Instance Initialization / Termination                */
    /*! \{                                                                 */

    bool   initialize (void);
    bool   terminate  (void);

    void   initTypeMap(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    //bool   unregisterEventProducer(const EventProducerPtr  &pEventProducer);
    //UInt32   registerEventProducer(const EventProducerPtr  &pEventProducer);

    UInt32 registerType            (      EventProducerType *pType          );
    UInt16 registerGroup           (const Char8              *szName         );
    void   unregisterType          (      EventProducerType *pType          );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class EventProducerType;
    friend class EventProducer;

    /*!\brief prohibit default function (move to 'public' if needed) */
    EventProducerFactory(const EventProducerFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const EventProducerFactory &source);
};

OSG_END_NAMESPACE

#endif /* _OSGEVENTPRODUCERFACTORYIMPL_H_ */

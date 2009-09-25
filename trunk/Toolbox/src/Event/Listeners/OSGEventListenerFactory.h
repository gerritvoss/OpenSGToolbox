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

#ifndef _OSGEVENTLISTENERFACTORYIMPL_H_
#define _OSGEVENTLISTENERFACTORYIMPL_H_

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
class EventListenerType;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemEventListener
 */

struct OSG_TOOLBOXLIB_DLLMAPPING EventListenerMapper
{
    virtual ~EventListenerMapper();
    
    virtual UInt32 map(UInt32 uiId) = 0;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemEventListener
 */

class OSG_TOOLBOXLIB_DLLMAPPING EventListenerFactory
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map   <UInt32,       
                        EventListenerType        *> TypeIdMap;
    typedef std::map   <IDStringLink, 
                        EventListenerType        *> TypeNameMap;
    typedef std::map   <IDStringLink, 
                        UInt16                     > GroupMap;

    typedef std::vector<EventListenerType        *> UninitializedTypeStore;
    //typedef std::vector<EventListenerPtr          > EventListenerStore;

    typedef TypeIdMap             ::iterator         TypeIdMapIt;
    typedef TypeNameMap           ::iterator         TypeNameMapIt;
    typedef GroupMap              ::iterator         GroupMapIt;
    typedef UninitializedTypeStore::iterator         UninitTypeStoreIt;
    //typedef EventListenerStore   ::iterator         EventListenerStoreIt;

    typedef TypeIdMap             ::const_iterator   TypeIdMapConstIt;
    typedef TypeNameMap           ::const_iterator   TypeNameMapCnstIt;
    typedef GroupMap              ::const_iterator   GroupMapConstIt;


    /*==========================  PUBLIC  =================================*/

  public :

    typedef TypeIdMapIt TypeMapIterator;

    static EventListenerFactory *the(void);

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */
        
    EventListenerType *findType    (      UInt32  uiTypeId) const;
    EventListenerType *findType    (const Char8  *szName  ) const;
    UInt32              getNumTypes (void                  ) const;


    EventListenerType *findUninitializedType (const Char8  *szName) const;

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

    void setMapper(EventListenerMapper *pMapper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get EventListener                          */
    /*! \{                                                                 */

    //EventListenerPtr getContainer      (UInt32 uiEventListenerId) const;
    //EventListenerPtr getMappedContainer(UInt32 uiEventListenerId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Create Base EventListener                      */
    /*! \{                                                                 */

    //EventListenerPtr createEventListener(const Char8 *name) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Write FCD From Name                            */
    /*! \{                                                                 */

    void writeFCD(const Char8 *name = NULL, std::ostream *out = NULL);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Get Containerstore                             */
    /*! \{                                                                 */

    //const EventListenerStore *getEventListenerStore(void) const;

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

    static EventListenerFactory *_the;

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
    //EventListenerStore    *_pEventListenerStore;

    Lock                   *_pStoreLock;
    Lock                   *_pMapLock;

    EventListenerMapper   *_pMapper;

    bool                    _throw_invalid_pointer_exception;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    EventListenerFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~EventListenerFactory(void); 

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

    //bool   unregisterEventListener(const EventListenerPtr  &pEventListener);
    //UInt32   registerEventListener(const EventListenerPtr  &pEventListener);

    UInt32 registerType            (      EventListenerType *pType          );
    UInt16 registerGroup           (const Char8              *szName         );
    void   unregisterType          (      EventListenerType *pType          );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class EventListenerType;
    friend class EventListener;

    /*!\brief prohibit default function (move to 'public' if needed) */
    EventListenerFactory(const EventListenerFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const EventListenerFactory &source);
};

OSG_END_NAMESPACE

#endif /* _OSGEVENTLISTENERFACTORYIMPL_H_ */

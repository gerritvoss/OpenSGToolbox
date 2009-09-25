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

#ifndef _OSGLISTENERFACTORYIMPL_H_
#define _OSGLISTENERFACTORYIMPL_H_

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
class ListenerType;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemListener
 */

struct OSG_TOOLBOXLIB_DLLMAPPING ListenerMapper
{
    virtual ~ListenerMapper();
    
    virtual UInt32 map(UInt32 uiId) = 0;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemListener
 */

class OSG_TOOLBOXLIB_DLLMAPPING ListenerFactory
{
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map   <UInt32,       
                        ListenerType        *> TypeIdMap;
    typedef std::map   <IDStringLink, 
                        ListenerType        *> TypeNameMap;
    typedef std::map   <IDStringLink, 
                        UInt16                     > GroupMap;

    typedef std::vector<ListenerType        *> UninitializedTypeStore;
    //typedef std::vector<ListenerPtr          > ListenerStore;

    typedef TypeIdMap             ::iterator         TypeIdMapIt;
    typedef TypeNameMap           ::iterator         TypeNameMapIt;
    typedef GroupMap              ::iterator         GroupMapIt;
    typedef UninitializedTypeStore::iterator         UninitTypeStoreIt;
    //typedef ListenerStore   ::iterator         ListenerStoreIt;

    typedef TypeIdMap             ::const_iterator   TypeIdMapConstIt;
    typedef TypeNameMap           ::const_iterator   TypeNameMapCnstIt;
    typedef GroupMap              ::const_iterator   GroupMapConstIt;


    /*==========================  PUBLIC  =================================*/

  public :

    typedef TypeIdMapIt TypeMapIterator;

    static ListenerFactory *the(void);

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */
        
    ListenerType *findType    (      UInt32  uiTypeId) const;
    ListenerType *findType    (const Char8  *szName  ) const;
    UInt32              getNumTypes (void                  ) const;


    ListenerType *findUninitializedType (const Char8  *szName) const;

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

    void setMapper(ListenerMapper *pMapper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get Listener                          */
    /*! \{                                                                 */

    //ListenerPtr getContainer      (UInt32 uiListenerId) const;
    //ListenerPtr getMappedContainer(UInt32 uiListenerId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Create Base Listener                      */
    /*! \{                                                                 */

    //ListenerPtr createListener(const Char8 *name) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Write FCD From Name                            */
    /*! \{                                                                 */

    void writeFCD(const Char8 *name = NULL, std::ostream *out = NULL);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Get Containerstore                             */
    /*! \{                                                                 */

    //const ListenerStore *getListenerStore(void) const;

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

    static ListenerFactory *_the;

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
    //ListenerStore    *_pListenerStore;

    Lock                   *_pStoreLock;
    Lock                   *_pMapLock;

    ListenerMapper   *_pMapper;

    bool                    _throw_invalid_pointer_exception;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ListenerFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~ListenerFactory(void); 

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

    //bool   unregisterListener(const ListenerPtr  &pListener);
    //UInt32   registerListener(const ListenerPtr  &pListener);

    UInt32 registerType            (      ListenerType *pType          );
    UInt16 registerGroup           (const Char8              *szName         );
    void   unregisterType          (      ListenerType *pType          );

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class ListenerType;
    friend class Listener;

    /*!\brief prohibit default function (move to 'public' if needed) */
    ListenerFactory(const ListenerFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ListenerFactory &source);
};

OSG_END_NAMESPACE

#endif /* _OSGLISTENERFACTORYIMPL_H_ */

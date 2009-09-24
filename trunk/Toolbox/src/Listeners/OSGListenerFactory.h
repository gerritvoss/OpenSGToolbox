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

#ifndef _OSGFIELDCONTAINERFACTORYIMPL_H_
#define _OSGFIELDCONTAINERFACTORYIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerFactoryImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGException.h>
#include <OSGIDStringLink.h>
#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

class Lock;
class FieldContainerType;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class OSG_SYSTEMLIB_DLLMAPPING InvalidPointerException : public Exception 
{
    /*==========================  PUBLIC  =================================*/
public:
    InvalidPointerException();
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainer
 */

struct OSG_SYSTEMLIB_DLLMAPPING FieldContainerMapper
{
    virtual ~FieldContainerMapper();
    
    virtual UInt32 map(UInt32 uiId) = 0;
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GrpSystemFieldContainer
 */

class OSG_SYSTEMLIB_DLLMAPPING FieldContainerFactory
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
    typedef std::vector<FieldContainerPtr          > FieldContainerStore;

    typedef TypeIdMap             ::iterator         TypeIdMapIt;
    typedef TypeNameMap           ::iterator         TypeNameMapIt;
    typedef GroupMap              ::iterator         GroupMapIt;
    typedef UninitializedTypeStore::iterator         UninitTypeStoreIt;
    typedef FieldContainerStore   ::iterator         FieldContainerStoreIt;

    typedef TypeIdMap             ::const_iterator   TypeIdMapConstIt;
    typedef TypeNameMap           ::const_iterator   TypeNameMapCnstIt;
    typedef GroupMap              ::const_iterator   GroupMapConstIt;


    /*==========================  PUBLIC  =================================*/

  public :

    typedef TypeIdMapIt TypeMapIterator;

    static FieldContainerFactory *the(void);

    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */
        
    FieldContainerType *findType    (      UInt32  uiTypeId) const;
    FieldContainerType *findType    (const Char8  *szName  ) const;
    UInt32              getNumTypes (void                  ) const;


    FieldContainerType *findUninitializedType (const Char8  *szName) const;

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

    void setMapper(FieldContainerMapper *pMapper);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Get FieldContainer                          */
    /*! \{                                                                 */

    FieldContainerPtr getContainer      (UInt32 uiFieldContainerId) const;
    FieldContainerPtr getMappedContainer(UInt32 uiFieldContainerId) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Create Base FieldContainer                      */
    /*! \{                                                                 */

    FieldContainerPtr createFieldContainer(const Char8 *name) const;
    NodePtr           createNode          (const Char8 *name) const;
    NodeCorePtr       createNodeCore      (const Char8 *name) const;
    AttachmentPtr     createAttachment    (const Char8 *name) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Write FCD From Name                            */
    /*! \{                                                                 */

    void writeFCD(const Char8 *name = NULL, std::ostream *out = NULL);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Get Containerstore                             */
    /*! \{                                                                 */

    const FieldContainerStore *getFieldContainerStore(void) const;

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

    static FieldContainerFactory *_the;

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
    FieldContainerStore    *_pFieldContainerStore;

    Lock                   *_pStoreLock;
    Lock                   *_pMapLock;

    FieldContainerMapper   *_pMapper;

    bool                    _throw_invalid_pointer_exception;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    FieldContainerFactory(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~FieldContainerFactory(void); 

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

    bool   unregisterFieldContainer(const FieldContainerPtr  &pFieldContainer);
    UInt32   registerFieldContainer(const FieldContainerPtr  &pFieldContainer);

    UInt32 registerType            (      FieldContainerType *pType          );
    UInt16 registerGroup           (const Char8              *szName         );
    void   unregisterType          (      FieldContainerType *pType          );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Write FCD From Type                          */
    /*! \{                                                                 */

    void writeSingleTypeFCD(std::ostream &out, const FieldContainerType *type);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainerType;
    friend class FieldContainer;
    friend class FieldContainerPtrBase;

    /*!\brief prohibit default function (move to 'public' if needed) */
    FieldContainerFactory(const FieldContainerFactory &source);
    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const FieldContainerFactory &source);
};

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFACTORY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERFACTORYIMPL_H_ */

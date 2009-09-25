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

#ifndef _OSGEVENTLISTENERTYPE_H_
#define _OSGEVENTLISTENERTYPE_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGTypeBase.h>
#include <OpenSG/OSGIDStringLink.h>

#include <map>
#include <boost/function.hpp>

OSG_BEGIN_NAMESPACE

class MethodDescription;

/*! \ingroup GrpSystemFieldContainerFuncs
 */

//typedef void              (*InitContainerF)  (void);

/*! \ingroup GrpSystemFieldContainerFuncs
 */

//typedef FieldContainerPtr (*PrototypeCreateF)(void);

/*! \ingroup GrpSystemFieldContainer
 */
typedef boost::function<void ( void )> InitEventListenerFunctor;

class OSG_TOOLBOXLIB_DLLMAPPING EventListenerType : public TypeBase
{
    /*==========================  PUBLIC  =================================*/

  public :

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
   
    EventListenerType(const Char8                *szName,
                       const Char8    *szParentName      = NULL,
                       const Char8    *szGroupName       = NULL,
                       //PrototypeCreateF    fPrototypeCreate  = NULL,
                       InitEventListenerFunctor      fInitMethod       = InitEventListenerFunctor(),
                       MethodDescription **pDesc             = NULL,
                       UInt32              uiDescByteCounter = 0);

    EventListenerType(const EventListenerType &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~EventListenerType(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Type Information                            */
    /*! \{                                                                 */

    UInt16              getGroupId(void) const;
    EventListenerType *getParent (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Description                                  */
    /*! \{                                                                 */

          MethodDescription *getMethodDescription (UInt32 uiMethodId);
    const MethodDescription *getMethodDescription (UInt32 uiMethodId) const;

          MethodDescription *findMethodDescription(const Char8 *szMethodName);

    const MethodDescription *findMethodDescription(
        const Char8 *szMethodName) const; 

    UInt32                 getNumMethodDescs(void) const;

    UInt32                 addDescription  (const MethodDescription &desc     );
    bool                   subDescription  (      UInt32            uiMethodId);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Prototype                                    */
    /*! \{                                                                 */

    //FieldContainerPtr getPrototype(void                        ) const;
    //bool              setPrototype(FieldContainerPtr pPrototype);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Query Properties                              */
    /*! \{                                                                 */

    bool isInitialized(void                           ) const;

    bool isAbstract   (void                           ) const;

    bool isDerivedFrom(const TypeBase           &other) const;
    bool isDerivedFrom(const EventListenerType &other) const;    

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef std::map   <IDStringLink,  MethodDescription *> DescMap;
    typedef std::vector<              MethodDescription *> DescVec;

    typedef DescMap::iterator                             DescMapIt;
    typedef DescVec::iterator                             DescVecIt;

    typedef DescMap::const_iterator                       DescMapConstIt;
    typedef DescVec::const_iterator                       DescVecConstIt;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt16              _uiGroupId;

    bool                _bInitialized;
    //bool                _bDescsAddable;

    EventListenerType *_pParent;
    IDString                _szParentName;
    const Char8            *_szGroupName;

    //FieldContainerPtr   _pPrototype;
    //PrototypeCreateF    _fPrototypeCreate;

    MethodDescription  **_pDesc;
    UInt32              _uiDescByteCounter;

    DescMap             _mDescMap;
    DescVec             _vDescVec;

    bool                _bCopy;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Register                                  */
    /*! \{                                                                 */

    void registerType(const Char8 *szGroupName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Intialization / Termination                      */
    /*! \{                                                                 */

    //bool initPrototype   (void);
    bool initMethods      (void);
    bool initParentMethods(void);

    bool initialize      (void);
    void terminate       (void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    typedef TypeBase Inherited;

    friend class EventListenerFactory;

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const EventListenerType &source);
};

struct OSG_TOOLBOXLIB_DLLMAPPING MethodDescriptionPLT
{
    bool operator()(const MethodDescription *pElemDesc1, 
                    const MethodDescription *pElemDesc2) const;
};

OSG_END_NAMESPACE

#include "OSGEventListenerType.inl"

#endif /* _OSGEVENTLISTENERTYPE_H_ */

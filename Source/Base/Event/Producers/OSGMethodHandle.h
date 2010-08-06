/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2003 by the OpenSG Forum                          *
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

#ifndef _OSGMETHODHANDLE_H_
#define _OSGMETHODHANDLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLog.h"
#include "OSGMethodDescription.h"

#include "boost/shared_ptr.hpp"
#include "boost/signals2.hpp"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING MethodHandle
{
    /*==========================  PRIVATE  ================================*/

  private:

    void operator =(const MethodHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    const MethodDescription *_pDescription;
    
    /*==========================  PUBLIC  =================================*/

  public:

    MethodHandle(const MethodHandle          &source);

    MethodHandle(const MethodDescription *pDescription);

    virtual ~MethodHandle(void);

    /*---------------------------------------------------------------------*/

    bool               isConsumable        (void) const;
    UInt32             getMethodId         (void) const;
    const std::string &getName             (void) const;
    TypeBase const    *getEventArgumentType(void) const;


    /*---------------------------------------------------------------------*/

    const MethodDescription *getDescription(void);

    /*---------------------------------------------------------------------*/

    /*---------------------------------------------------------------------*/

};


class EditMethodHandle;

/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING GetMethodHandle : public MethodHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const GetMethodHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    friend class EditMethodHandle;

    typedef MethodHandle Inherited;

    /*---------------------------------------------------------------------*/

    FieldContainer *_pContainer;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetMethodHandle > Ptr;

    /*---------------------------------------------------------------------*/

    GetMethodHandle(const GetMethodHandle       &source);
    GetMethodHandle(const MethodDescription *pDescription,
                          FieldContainer    *pContainer  );


    virtual ~GetMethodHandle(void);

    /*---------------------------------------------------------------------*/

          FieldContainer *getContainer(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Ptr rhs) const = 0;

    bool operator ==(const EditMethodHandle &rhs);
    bool operator ==(const GetMethodHandle  &rhs);
};

/*! \ingroup GrpBaseFieldContainerHandle
 */

typedef boost::shared_ptr<GetMethodHandle > GetMethodHandlePtr;


/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING EditMethodHandle : public MethodHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const EditMethodHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    friend class GetMethodHandle;

    typedef MethodHandle Inherited;

    /*---------------------------------------------------------------------*/

    FieldContainer *_pContainer;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditMethodHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditMethodHandle(const EditMethodHandle      &source);
    EditMethodHandle(const MethodDescription *pDescription,
                           FieldContainer    *pContainer);


    virtual ~EditMethodHandle(void);

    /*---------------------------------------------------------------------*/

    FieldContainer *getContainer(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Ptr rhs) const = 0;

    bool operator ==(const EditMethodHandle &rhs);
    bool operator ==(const GetMethodHandle  &rhs);

    /*---------------------------------------------------------------------*/

};

/*! \ingroup GrpBaseFieldContainerHandle
 */

typedef boost::shared_ptr<EditMethodHandle> EditMethodHandlePtr;

/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

template<class MethodSignalType>
class EditTypedMethodHandle : public EditMethodHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    void operator =(const EditTypedMethodHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditMethodHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:
    
    typedef boost::shared_ptr<EditTypedMethodHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditTypedMethodHandle(const EditTypedMethodHandle     &source);
    EditTypedMethodHandle(      MethodSignalType  *pMethodSignal,
                          const MethodDescription *pDescription,
                                FieldContainer    *pContainer  );


    virtual ~EditTypedMethodHandle(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    MethodSignalType *getMethodSignal(void);

    /*---------------------------------------------------------------------*/

    MethodSignalType * operator ->(void);
    MethodSignalType & operator * (void);

  protected:

    MethodSignalType *_pMethodSignal;
};

template<class MethodSignalType>
class GetTypedMethodHandle : public GetMethodHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    void operator =(const GetTypedMethodHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetMethodHandle Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    typedef boost::shared_ptr<GetTypedMethodHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetTypedMethodHandle(const GetTypedMethodHandle      &source);
    GetTypedMethodHandle(      MethodSignalType  *pMethodSignal,
                          const MethodDescription *pDescription,
                          FieldContainer       *pContainer  );

    virtual ~GetTypedMethodHandle(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    MethodSignalType const *getMethodSignal(void);

    /*---------------------------------------------------------------------*/

    MethodSignalType const * operator ->(void);
    MethodSignalType const & operator * (void);

  protected:

    MethodSignalType *_pMethodSignal;
};

OSG_END_NAMESPACE

#include "OSGMethodHandle.inl"

#endif /* _OSGMETHODHANDLE_H_ */

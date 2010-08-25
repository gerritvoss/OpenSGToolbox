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

#ifndef _OSGEVENTHANDLE_H_
#define _OSGEVENTHANDLE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLog.h"
#include "OSGEventDescription.h"

#include "boost/shared_ptr.hpp"
#include "boost/signals2.hpp"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Class         
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING EventHandle
{
    /*==========================  PRIVATE  ================================*/

  private:

    void operator =(const EventHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    const EventDescription *_pDescription;
    
    /*==========================  PUBLIC  =================================*/

  public:

    EventHandle(const EventHandle          &source);

    EventHandle(const EventDescription *pDescription);

    virtual ~EventHandle(void);

    /*---------------------------------------------------------------------*/

    bool               isConsumable        (void) const;
    UInt32             getEventId         (void) const;
    std::string        getName             (void) const;
    TypeBase const    *getEventArgumentType(void) const;


    /*---------------------------------------------------------------------*/

    const EventDescription *getDescription(void);

    /*---------------------------------------------------------------------*/

    /*---------------------------------------------------------------------*/

};


class EditEventHandle;

/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING GetEventHandle : public EventHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const GetEventHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    friend class EditEventHandle;

    typedef EventHandle Inherited;

    /*---------------------------------------------------------------------*/

    FieldContainer *_pContainer;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<GetEventHandle > Ptr;

    /*---------------------------------------------------------------------*/

    GetEventHandle(const GetEventHandle       &source);
    GetEventHandle(const EventDescription *pDescription,
                          FieldContainer    *pContainer  );


    virtual ~GetEventHandle(void);

    /*---------------------------------------------------------------------*/

          FieldContainer *getContainer(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Ptr rhs) const = 0;

    bool operator ==(const EditEventHandle &rhs);
    bool operator ==(const GetEventHandle  &rhs);
};

/*! \ingroup GrpBaseFieldContainerHandle
 */

typedef boost::shared_ptr<GetEventHandle > GetEventHandlePtr;


/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

class OSG_BASE_DLLMAPPING EditEventHandle : public EventHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    
    void operator =(const EditEventHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    friend class GetEventHandle;

    typedef EventHandle Inherited;

    /*---------------------------------------------------------------------*/

    FieldContainer *_pContainer;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef boost::shared_ptr<EditEventHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditEventHandle(const EditEventHandle      &source);
    EditEventHandle(const EventDescription *pDescription,
                           FieldContainer    *pContainer);


    virtual ~EditEventHandle(void);

    /*---------------------------------------------------------------------*/

    FieldContainer *getContainer(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Ptr rhs) const = 0;

    bool operator ==(const EditEventHandle &rhs);
    bool operator ==(const GetEventHandle  &rhs);

    /*---------------------------------------------------------------------*/

};

/*! \ingroup GrpBaseFieldContainerHandle
 */

typedef boost::shared_ptr<EditEventHandle> EditEventHandlePtr;

/*! \ingroup GrpBaseFieldContainerHandle
    \ingroup GrpLibOSGBase
 */

template<class EventSignalType>
class EditTypedEventHandle : public EditEventHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    void operator =(const EditTypedEventHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef EditEventHandle Inherited;

    /*==========================  PUBLIC  =================================*/

  public:
    
    typedef boost::shared_ptr<EditTypedEventHandle> Ptr;

    /*---------------------------------------------------------------------*/

    EditTypedEventHandle(const EditTypedEventHandle     &source);
    EditTypedEventHandle(      EventSignalType  *pEventSignal,
                          const EventDescription *pDescription,
                                FieldContainer    *pContainer  );


    virtual ~EditTypedEventHandle(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    EventSignalType *getEventSignal(void);

    /*---------------------------------------------------------------------*/

    EventSignalType * operator ->(void);
    EventSignalType & operator * (void);

  protected:

    EventSignalType *_pEventSignal;
};

template<class EventSignalType>
class GetTypedEventHandle : public GetEventHandle
{
    /*==========================  PRIVATE  ================================*/

  private:
    void operator =(const GetTypedEventHandle &source);

    /*=========================  PROTECTED  ===============================*/

  protected:

    typedef GetEventHandle Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    typedef boost::shared_ptr<GetTypedEventHandle> Ptr;

    /*---------------------------------------------------------------------*/

    GetTypedEventHandle(const GetTypedEventHandle      &source);
    GetTypedEventHandle(      EventSignalType  *pEventSignal,
                          const EventDescription *pDescription,
                          FieldContainer       *pContainer  );

    virtual ~GetTypedEventHandle(void);

    /*---------------------------------------------------------------------*/

    virtual bool equal(Inherited::Ptr rhs) const;

    /*---------------------------------------------------------------------*/

    EventSignalType const *getEventSignal(void);

    /*---------------------------------------------------------------------*/

    EventSignalType const * operator ->(void);
    EventSignalType const & operator * (void);

  protected:

    EventSignalType *_pEventSignal;
};

OSG_END_NAMESPACE

#include "OSGEventHandle.inl"

#endif /* _OSGEVENTHANDLE_H_ */

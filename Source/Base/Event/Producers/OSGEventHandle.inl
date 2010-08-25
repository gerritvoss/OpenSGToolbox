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

OSG_BEGIN_NAMESPACE

inline
EventHandle::EventHandle(const EventHandle &source) :
    _pDescription(source._pDescription)
{
}

inline
EventHandle::EventHandle(const EventDescription *pDescription) :
    _pDescription(pDescription)
{
}

inline
EventHandle::~EventHandle(void)
{
}


inline
bool EventHandle::isConsumable(void) const
{
    if(_pDescription != NULL)
    {
        return _pDescription->getConsumable();
    }
    else
    {
        return false;
    }
}

inline
UInt32 EventHandle::getEventId(void) const
{
    if(_pDescription != NULL)
    {
        return _pDescription->getEventId();
    }
    else
    {
        return 0;
    }
}


inline
TypeBase const    *EventHandle::getEventArgumentType(void) const
{
    if(_pDescription != NULL)
    {
        return &_pDescription->getEventArgumentType();
    }
    else
    {
        return NULL;
    }
}

inline
std::string EventHandle::getName(void) const
{
    if(_pDescription != NULL)
    {
        return _pDescription->getName();
    }
    else
    {
        return "";
    }
}

inline
const EventDescription *EventHandle::getDescription(void)
{
    return _pDescription;
}

/*---------------------------------------------------------------------*/

inline
GetEventHandle::GetEventHandle(const GetEventHandle &source) :
     Inherited (source            ),
    _pContainer(source._pContainer)
{
}

inline
GetEventHandle::GetEventHandle(const EventDescription *pDescription,
                                     FieldContainer       *pContainer  ) :
     Inherited (pDescription),
    _pContainer(pContainer  )
{
}

inline
GetEventHandle::~GetEventHandle(void)
{
}

inline
FieldContainer *GetEventHandle::getContainer(void)
{
    return _pContainer;
}

inline
bool GetEventHandle::operator ==(const EditEventHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

inline
bool GetEventHandle::operator ==(const GetEventHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

/*---------------------------------------------------------------------*/

inline
EditEventHandle::EditEventHandle(const EditEventHandle &source) :
     Inherited (source            ),
    _pContainer(source._pContainer)
{
}

inline
EditEventHandle::EditEventHandle(const EventDescription *pDescription,
                                       FieldContainer       *pContainer  ) :
     Inherited (pDescription),
    _pContainer(pContainer  )
{
}

inline
EditEventHandle::~EditEventHandle(void)
{
}

inline
FieldContainer *EditEventHandle::getContainer(void)
{
    return _pContainer;
}

inline
bool EditEventHandle::operator ==(const EditEventHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

inline
bool EditEventHandle::operator ==(const GetEventHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

/*---------------------------------------------------------------------*/

template<class EventSignalType> inline
EditTypedEventHandle<EventSignalType>::EditTypedEventHandle(const EditTypedEventHandle &source) :
    Inherited(source),
        _pEventSignal(source._pEventSignal)
{
}

template<class EventSignalType> inline
EditTypedEventHandle<EventSignalType>::EditTypedEventHandle(     
          EventSignalType  *pEventSignal,
    const EventDescription *pDescription,
          FieldContainer       *pContainer  ) :
    
    Inherited(pDescription, pContainer),
        _pEventSignal(pEventSignal)
{
}


template<class EventSignalType> inline
EditTypedEventHandle<EventSignalType>::~EditTypedEventHandle(void)
{
}

//template<class EventSignalType> inline
//bool EditTypedEventHandle<EventSignalType>::equal(Inherited::Ptr rhs) const
//{
//    Ptr pOther = boost::dynamic_pointer_cast<EditTypedEventHandle>(rhs);
//
//    if(pOther == NULL)
//    {
//        return false;
//    }
//
//    EventSignalType *pLhs = static_cast<EventSignalType *>(        _pEventSignal);
//    EventSignalType *pRhs = static_cast<EventSignalType *>(pOther->_pEventSignal);
//
//    return (*pLhs) == (*pRhs);
//}

template<class EventSignalType> inline
EventSignalType *EditTypedEventHandle<EventSignalType>::getEventSignal(void)
{
    return static_cast<EventSignalType *>(_pEventSignal);
}

template<class EventSignalType> inline
EventSignalType *EditTypedEventHandle<EventSignalType>::operator ->(void)
{
    return static_cast<EventSignalType *>(_pEventSignal);
}


template<class EventSignalType> inline
EventSignalType &EditTypedEventHandle<EventSignalType>::operator * (void)
{
    return *(static_cast<EventSignalType *>(_pEventSignal));
}

/*---------------------------------------------------------------------*/

template<class EventSignalType> inline
GetTypedEventHandle<EventSignalType>::GetTypedEventHandle(const GetTypedEventHandle &source) :
    Inherited(source),
        _pEventSignal(source._pEventSignal)
{
}

template<class EventSignalType> inline
GetTypedEventHandle<EventSignalType>::GetTypedEventHandle(
          EventSignalType  *pEventSignal,
    const EventDescription *pDescription,
          FieldContainer    *pContainer  ) :

    Inherited(pDescription, pContainer),
        _pEventSignal(pEventSignal)
{
}

template<class EventSignalType> inline
GetTypedEventHandle<EventSignalType>::~GetTypedEventHandle(void)
{
}

template<class EventSignalType> inline
bool GetTypedEventHandle<EventSignalType>::equal(Inherited::Ptr rhs) const
{
    Ptr pOther = boost::dynamic_pointer_cast<GetTypedEventHandle>(rhs);

    if(pOther == NULL)
    {
        return false;
    }

    EventSignalType *pLhs = static_cast<EventSignalType *>(        _pEventSignal);
    EventSignalType *pRhs = static_cast<EventSignalType *>(pOther->_pEventSignal);

    return pLhs == pRhs;
}

template<class EventSignalType> inline
EventSignalType const *GetTypedEventHandle<EventSignalType>::getEventSignal(void)
{
    return static_cast<EventSignalType const *>(_pEventSignal);
}

template<class EventSignalType> inline
EventSignalType const *GetTypedEventHandle<EventSignalType>::operator ->(void)
{
    return static_cast<EventSignalType const *>(_pEventSignal);
}

template<class EventSignalType> inline
EventSignalType const &GetTypedEventHandle<EventSignalType>::operator * (void)
{
    return *(static_cast<EventSignalType const *>(_pEventSignal));
}

/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

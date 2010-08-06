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
MethodHandle::MethodHandle(const MethodHandle &source) :
    _pDescription(source._pDescription)
{
}

inline
MethodHandle::MethodHandle(const MethodDescription *pDescription) :
    _pDescription(pDescription)
{
}

inline
MethodHandle::~MethodHandle(void)
{
}


inline
bool MethodHandle::isConsumable(void) const
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
UInt32 MethodHandle::getMethodId(void) const
{
    if(_pDescription != NULL)
    {
        return _pDescription->getMethodId();
    }
    else
    {
        return 0;
    }
}


inline
TypeBase const    *MethodHandle::getEventArgumentType(void) const
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
const std::string &MethodHandle::getName(void) const
{
    if(_pDescription != NULL)
    {
        return _pDescription->getName();
    }
    else
    {
        return std::string();
    }
}

inline
const MethodDescription *MethodHandle::getDescription(void)
{
    return _pDescription;
}

/*---------------------------------------------------------------------*/

inline
GetMethodHandle::GetMethodHandle(const GetMethodHandle &source) :
     Inherited (source            ),
    _pContainer(source._pContainer)
{
}

inline
GetMethodHandle::GetMethodHandle(const MethodDescription *pDescription,
                                     FieldContainer       *pContainer  ) :
     Inherited (pDescription),
    _pContainer(pContainer  )
{
}

inline
GetMethodHandle::~GetMethodHandle(void)
{
}

inline
FieldContainer *GetMethodHandle::getContainer(void)
{
    return _pContainer;
}

inline
bool GetMethodHandle::operator ==(const EditMethodHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

inline
bool GetMethodHandle::operator ==(const GetMethodHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

/*---------------------------------------------------------------------*/

inline
EditMethodHandle::EditMethodHandle(const EditMethodHandle &source) :
     Inherited (source            ),
    _pContainer(source._pContainer)
{
}

inline
EditMethodHandle::EditMethodHandle(const MethodDescription *pDescription,
                                       FieldContainer       *pContainer  ) :
     Inherited (pDescription),
    _pContainer(pContainer  )
{
}

inline
EditMethodHandle::~EditMethodHandle(void)
{
}

inline
FieldContainer *EditMethodHandle::getContainer(void)
{
    return _pContainer;
}

inline
bool EditMethodHandle::operator ==(const EditMethodHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

inline
bool EditMethodHandle::operator ==(const GetMethodHandle &rhs)
{
    return (_pDescription == rhs._pDescription &&
            _pContainer   == rhs._pContainer        );
}

/*---------------------------------------------------------------------*/

template<class MethodSignalType> inline
EditTypedMethodHandle<MethodSignalType>::EditTypedMethodHandle(const EditTypedMethodHandle &source) :
    Inherited(source),
        _pMethodSignal(source._pMethodSignal)
{
}

template<class MethodSignalType> inline
EditTypedMethodHandle<MethodSignalType>::EditTypedMethodHandle(     
          MethodSignalType  *pMethodSignal,
    const MethodDescription *pDescription,
          FieldContainer       *pContainer  ) :
    
    Inherited(pDescription, pContainer),
        _pMethodSignal(pMethodSignal)
{
}


template<class MethodSignalType> inline
EditTypedMethodHandle<MethodSignalType>::~EditTypedMethodHandle(void)
{
}

//template<class MethodSignalType> inline
//bool EditTypedMethodHandle<MethodSignalType>::equal(Inherited::Ptr rhs) const
//{
//    Ptr pOther = boost::dynamic_pointer_cast<EditTypedMethodHandle>(rhs);
//
//    if(pOther == NULL)
//    {
//        return false;
//    }
//
//    MethodSignalType *pLhs = static_cast<MethodSignalType *>(        _pMethodSignal);
//    MethodSignalType *pRhs = static_cast<MethodSignalType *>(pOther->_pMethodSignal);
//
//    return (*pLhs) == (*pRhs);
//}

template<class MethodSignalType> inline
MethodSignalType *EditTypedMethodHandle<MethodSignalType>::getMethodSignal(void)
{
    return static_cast<MethodSignalType *>(_pMethodSignal);
}

template<class MethodSignalType> inline
MethodSignalType *EditTypedMethodHandle<MethodSignalType>::operator ->(void)
{
    return static_cast<MethodSignalType *>(_pMethodSignal);
}


template<class MethodSignalType> inline
MethodSignalType &EditTypedMethodHandle<MethodSignalType>::operator * (void)
{
    return *(static_cast<MethodSignalType *>(_pMethodSignal));
}

/*---------------------------------------------------------------------*/

template<class MethodSignalType> inline
GetTypedMethodHandle<MethodSignalType>::GetTypedMethodHandle(const GetTypedMethodHandle &source) :
    Inherited(source),
        _pMethodSignal(source._pMethodSignal)
{
}

template<class MethodSignalType> inline
GetTypedMethodHandle<MethodSignalType>::GetTypedMethodHandle(
          MethodSignalType  *pMethodSignal,
    const MethodDescription *pDescription,
          FieldContainer    *pContainer  ) :

    Inherited(pDescription, pContainer),
        _pMethodSignal(pMethodSignal)
{
}

template<class MethodSignalType> inline
GetTypedMethodHandle<MethodSignalType>::~GetTypedMethodHandle(void)
{
}

//template<class MethodSignalType> inline
//bool GetTypedMethodHandle<MethodSignalType>::equal(Inherited::Ptr rhs) const
//{
//    Ptr pOther = boost::dynamic_pointer_cast<EditTypedMethodHandle>(rhs);
//
//    if(pOther == NULL)
//    {
//        return false;
//    }
//
//    MethodSignalType *pLhs = static_cast<MethodSignalType *>(        _pMethodSignal);
//    MethodSignalType *pRhs = static_cast<MethodSignalType *>(pOther->_pMethodSignal);
//
//    return (*pLhs) == (*pRhs);
//}

template<class MethodSignalType> inline
MethodSignalType const *GetTypedMethodHandle<MethodSignalType>::getMethodSignal(void)
{
    return static_cast<MethodSignalType const *>(_pMethodSignal);
}

template<class MethodSignalType> inline
MethodSignalType const *GetTypedMethodHandle<MethodSignalType>::operator ->(void)
{
    return static_cast<MethodSignalType const *>(_pMethodSignal);
}

template<class MethodSignalType> inline
MethodSignalType const &GetTypedMethodHandle<MethodSignalType>::operator * (void)
{
    return *(static_cast<MethodSignalType const *>(_pMethodSignal));
}

/*---------------------------------------------------------------------*/

OSG_END_NAMESPACE

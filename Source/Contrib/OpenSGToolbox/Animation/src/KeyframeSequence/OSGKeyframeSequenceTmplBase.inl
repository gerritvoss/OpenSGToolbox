/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OpenSG/OSGConfig.h>
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

#ifndef WIN32
OSG_ABSTR_FIELD_CONTAINER_INL_TMPL_DEF(AbstractKeyframeSequenceTmpl,
                                       KeyframeSequenceDesc,
                                       PtrType)
#else
OSG_ABSTR_GEO_PROP_INL_TMPL_DEF(AbstractKeyframeSequenceTmpl,
                                KeyframeSequenceDesc,
                                PtrType)
#endif

template <class KeyframeSequenceDesc> inline
AbstractKeyframeSequenceTmpl<KeyframeSequenceDesc>::AbstractKeyframeSequenceTmpl(void) :
      LocalInherited()
{
}


template <class KeyframeSequenceDesc> inline
AbstractKeyframeSequenceTmpl<KeyframeSequenceDesc>::AbstractKeyframeSequenceTmpl(
    const AbstractKeyframeSequenceTmpl &source) :

      LocalInherited(source)
{
}


template <class KeyframeSequenceDesc> inline
AbstractKeyframeSequenceTmpl<KeyframeSequenceDesc>::~AbstractKeyframeSequenceTmpl(void)
{
}

template <class KeyframeSequenceDesc> inline
void AbstractKeyframeSequenceTmpl<KeyframeSequenceDesc>::dump(      UInt32    uiIndent, 
                                                const BitVector bvFlags) const
{
    LocalInherited::dump(uiIndent, bvFlags);
}

template <class KeyframeSequenceDesc> inline
bool KeyframeSequenceTmpl<KeyframeSequenceDesc>::isBlendable(void) const
{
    return KeyframeSequenceDesc::isBlendable();
}

/** \brief Property field description
 */

/** \brief Attachment type
 */

#ifndef WIN32
OSG_FIELD_CONTAINER_INL_TMPL_DEF(KeyframeSequenceTmpl,
                                 KeyframeSequenceDesc,
                                 PtrType)
#else
OSG_GEO_PROP_INL_TMPL_DEF(KeyframeSequenceTmpl,
                          KeyframeSequenceDesc,
                          PtrType)
#endif

#ifdef OSG_MICROSOFT_COMPILER_HACKS
template <class KeyframeSequenceDesc> inline 
FieldAccessMethod KeyframeSequenceTmpl<KeyframeSequenceDesc>::getFPtrAccessMethod(void)
{
    typedef KeyframeSequenceTmpl<KeyframeSequenceDesc> Self;
    typedef StoredFieldType *(Self::*GetFieldPtr)(void);

    GetFieldPtr       tmp       = &osg::KeyframeSequenceTmpl<KeyframeSequenceDesc>::getFieldPtr;

    FieldAccessMethod tmpMethod = (*((FieldAccessMethod *) &tmp));

    return tmpMethod;
}
#endif

#if defined(__hpux)
template <class KeyframeSequenceDesc> 
const BitVector KeyframeSequenceTmpl<KeyframeSequenceDesc>::KeyframePropDataFieldId;
#endif

template <class KeyframeSequenceDesc> inline 
KeyframeSequenceTmpl<KeyframeSequenceDesc>::KeyframeSequenceTmpl(void) :
     LocalInherited(),
    _field         ()
{
}

template <class KeyframeSequenceDesc> inline 
KeyframeSequenceTmpl<KeyframeSequenceDesc>::KeyframeSequenceTmpl(
    const KeyframeSequenceTmpl &source ) :

     LocalInherited(source),
    _field         (source._field)
{
}

template <class KeyframeSequenceDesc> inline 
KeyframeSequenceTmpl<KeyframeSequenceDesc>::~KeyframeSequenceTmpl(void)
{
}

#if !defined(OSG_FIXED_MFIELDSYNC)
template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::executeSync(
          FieldContainer &other,
    const BitVector      &whichField)
{
    this->executeSyncImpl(static_cast<KeyframeSequenceTmpl *>(&other), whichField);
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::executeSyncImpl(
          KeyframeSequenceTmpl *pOther,
    const BitVector   &whichField)
{
    LocalInherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (KeyframePropDataFieldId & whichField))
    {
        _field.syncWith(pOther->_field);
    }
}
#else
template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::executeSync(
          FieldContainer &other,
    const BitVector      &whichField,
    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((KeyframeSequenceTmpl *) &other, whichField, sInfo);
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::executeSyncImpl(
          KeyframeSequenceTmpl *pOther,
    const BitVector   &whichField,
    const SyncInfo    &sInfo     )
{
    LocalInherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (KeyframePropDataFieldId & whichField))
    {
        _field.syncWith(pOther->_field, sInfo);
    }
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::execBeginEditImpl(
    const BitVector &whichField, 
          UInt32     uiAspect,
          UInt32     uiContainerSize)
{
    LocalInherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

    if (FieldBits::NoField != (KeyframePropDataFieldId & whichField))
    {
        _field.beginEdit(uiAspect, uiContainerSize);
    }
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::execBeginEdit(
    const BitVector &whichField, 
          UInt32     uiAspect,
          UInt32     uiContainerSize)
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::onDestroyAspect(UInt32 uiId, 
                                                   UInt32 uiAspect)
{
    _field.terminateShare(uiAspect, this->getContainerSize());
}
#endif

template <class KeyframeSequenceDesc> inline 
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::changed(BitVector whichField, 
                                           UInt32    origin    )
{
    MFFieldContainerPtr::iterator parentsIt  = Self::_parents.begin();
    MFFieldContainerPtr::iterator parentsEnd = Self::_parents.end();

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
                TypeTraits<BitVector>::One << parentsIt->getParentFieldPos(),
                ChangedOrigin::Child);
        ++parentsIt;
    }

    LocalInherited::changed(whichField, origin);
}

template <class KeyframeSequenceDesc> inline 
UInt32 KeyframeSequenceTmpl<KeyframeSequenceDesc>::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = LocalInherited::getBinSize(whichField);

    if(FieldBits::NoField != (KeyframePropDataFieldId & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class KeyframeSequenceDesc> inline 
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::copyToBin(
          BinaryDataHandler &pMem,
    const BitVector         &whichField)
{
    LocalInherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (KeyframePropDataFieldId & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class KeyframeSequenceDesc> inline 
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::copyFromBin(
          BinaryDataHandler &pMem,
    const BitVector         &whichField)
{
    LocalInherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (KeyframePropDataFieldId & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractKeyframeSequenceTmpl provides, but it
    necessitates compile-time knowledge about the involved concrete types.
*/
template <class KeyframeSequenceDesc> inline 
typename KeyframeSequenceTmpl<KeyframeSequenceDesc>::StoredFieldType * 
    KeyframeSequenceTmpl<KeyframeSequenceDesc>::getFieldPtr(void)
{
    return &_field;
}

/*! Returns a reference to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractKeyframeSequenceTmpl provides, but it
    necessitates compile-time knowledge about the involved concrete types. 
*/
template <class KeyframeSequenceDesc> inline 
typename KeyframeSequenceTmpl<KeyframeSequenceDesc>::StoredFieldType & 
    KeyframeSequenceTmpl<KeyframeSequenceDesc>::getField(void)
{
    return _field;
}

/*! Returns a const reference to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractKeyframeSequenceTmpl provides, but it
    necessitates compile-time knowledge about the involved concrete types. 
*/
template <class KeyframeSequenceDesc> inline 
const typename KeyframeSequenceTmpl<KeyframeSequenceDesc>::StoredFieldType & 
    KeyframeSequenceTmpl<KeyframeSequenceDesc>::getField(void) const
{
    return _field;
}

template <class KeyframeSequenceDesc> inline
typename KeyframeSequenceTmpl<KeyframeSequenceDesc>::LocalInheritedPtr
KeyframeSequenceTmpl<KeyframeSequenceDesc>::clone(void)
{
    PtrType obj = KeyframeSequenceTmpl<KeyframeSequenceDesc>::create();
    
    obj->_field.setValues( _field );
    return obj;
}


/*! Returns the format of this property. 

    
*/

template <class KeyframeSequenceDesc> inline
UInt32 KeyframeSequenceTmpl<KeyframeSequenceDesc>::getSize(void) const
{
    return _field.size();
}


template <class KeyframeSequenceDesc> inline
UInt32 KeyframeSequenceTmpl<KeyframeSequenceDesc>::size(void) const
{
    return _field.size();
}

template <class KeyframeSequenceDesc> inline 
typename KeyframeSequenceTmpl<KeyframeSequenceDesc>::StoredGenericType
    KeyframeSequenceTmpl<KeyframeSequenceDesc>::getKeyValue(const UInt32 index)
{
//CHECKCHECK do conversion constructor iff necessary
    return StoredGenericType(_field[index]);
}

template <class KeyframeSequenceDesc> inline
typename KeyframeSequenceTmpl<KeyframeSequenceDesc>::StoredGenericType
    KeyframeSequenceTmpl<KeyframeSequenceDesc>::getKeyValue(const UInt32 index) const
{
//CHECKCHECK do conversion constructor iff necessary
    return StoredGenericType(_field[index]);
}

template <class KeyframeSequenceDesc> inline 
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::getKeyValue(      StoredGenericType &val,
                                            const UInt32             index)
{
    new (&val) StoredGenericType(_field[index]);
}


template <class KeyframeSequenceDesc> inline 
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::getKeyValue(
          StoredGenericType &val,
    const UInt32             index) const
{
    new (&val) StoredGenericType(_field[index]);
}

template <class KeyframeSequenceDesc> inline 
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::setKeyframe(const StoredGenericType &value,
                                          const Real32 &key,
                                            const UInt32             index)
{
//CHECKCHECK do conversion constructor iff necessary
    _field[index] = StoredType(value);
    this->_sfInternalKeys[index] = key;
}

template <class KeyframeSequenceDesc> inline 
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::addKeyframe(const StoredGenericType & value,
                                          const Real32 &key)
{
//CHECKCHECK do conversion constructor iff necessary
    _field.push_back( StoredType(value) );
    this->_sfInternalKeys.push_back( key );
}

template <class KeyframeSequenceDesc> inline
bool KeyframeSequenceTmpl<KeyframeSequenceDesc>::insertKeyframe(const StoredGenericType &val,
                                          const Real32 &key,
                                               const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addValue(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, StoredType(val));
        this->_sfInternalKeys.insert(this->_sfInternalKeys.begin() + index, key);
        return true;
    }
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::clear( void )
{
    _field.clear();
    this->_mfInternalKeys.clear();
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::push_back(
    const StoredGenericType &value,
                                          const Real32 &key)
{
    addKeyframe(value,key);
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::resize( size_t newsize )
{
    _field.resize(newsize);
    this->_mfInternalKeys.resize(newsize);
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::shrink( void )
{
    StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class KeyframeSequenceDesc> inline
void KeyframeSequenceTmpl<KeyframeSequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    LocalInherited::dump(uiIndent, bvFlags);
}

template <class KeyframeSequenceDesc> inline
RawInterpFuncion KeyframeSequenceTmpl<KeyframeSequenceDesc>::getStepInterpFuncion(void)
{
    typename KeyframeSequenceDesc::ConcreteInterpFunction f(KeyframeSequenceDesc::getStepConcreteInterpFuncion());
    if(f.empty())
    {
        return NULL;
    }
    else
    {
        return boost::bind(f, static_cast<const StoredFieldType&>(getKeyValues()),this->getKeys(),_1,_2,_3);
    }
}

template <class KeyframeSequenceDesc> inline
RawInterpFuncion KeyframeSequenceTmpl<KeyframeSequenceDesc>::getLinearInterpFuncion(void)
{
    typename KeyframeSequenceDesc::ConcreteInterpFunction f(KeyframeSequenceDesc::getLinearConcreteInterpFuncion());
    if(f.empty())
    {
        return NULL;
    }
    else
    {
        return boost::bind(f, static_cast<const StoredFieldType&>(getKeyValues()),this->getKeys(),_1,_2,_3);
    }
}

template <class KeyframeSequenceDesc> inline
RawInterpFuncion KeyframeSequenceTmpl<KeyframeSequenceDesc>::getCubicInterpFuncion(void)
{
    typename KeyframeSequenceDesc::ConcreteInterpFunction f(KeyframeSequenceDesc::getCubicConcreteInterpFuncion());
    if(f.empty())
    {
        return NULL;
    }
    else
    {
        return boost::bind(f, static_cast<const StoredFieldType&>(getKeyValues()),this->getKeys(),_1,_2,_3);
    }
}

template <class KeyframeSequenceDesc> inline
RawInterpFuncion KeyframeSequenceTmpl<KeyframeSequenceDesc>::getLinearNormalInterpFuncion(void)
{
    typename KeyframeSequenceDesc::ConcreteInterpFunction f(KeyframeSequenceDesc::getLinearNormalConcreteInterpFuncion());
    if(f.empty())
    {
        return NULL;
    }
    else
    {
        return boost::bind(f, static_cast<const StoredFieldType&>(getKeyValues()),this->getKeys(),_1,_2,_3);
    }
}

template <class KeyframeSequenceDesc> inline
ReplacementFuncion KeyframeSequenceTmpl<KeyframeSequenceDesc>::getReplacementFuncion(void)
{
    return &replacement<typename KeyframeSequenceDesc::SingleFieldType>;
}

template <class KeyframeSequenceDesc> inline
const osg::Field& KeyframeSequenceTmpl<KeyframeSequenceDesc>::getKeyValues(void) const
{
    return getField();
}

template <class KeyframeSequenceDesc> inline
const DataType &KeyframeSequenceTmpl<KeyframeSequenceDesc>::getDataType(void) const
{
    return KeyframeSequenceDesc::StoredFieldType::getClassType().getContentType();
}
OSG_END_NAMESPACE


/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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


template <class SequenceDesc> inline 
KeyframeNumberSequenceTmpl<SequenceDesc>::KeyframeNumberSequenceTmpl(void) :
     KeyframeNumberSequence(),
    _field         ()
{
}

template <class SequenceDesc> inline 
KeyframeNumberSequenceTmpl<SequenceDesc>::KeyframeNumberSequenceTmpl(
    const KeyframeNumberSequenceTmpl &source ) :

     KeyframeNumberSequence(source),
    _field         (source._field)
{
}

template <class SequenceDesc> inline 
KeyframeNumberSequenceTmpl<SequenceDesc>::~KeyframeNumberSequenceTmpl(void)
{
}

template <class SequenceDesc> inline 
typename KeyframeNumberSequenceTmpl<SequenceDesc>::StoredType 
  KeyframeNumberSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index )
{
    return _field[index];
}

template <class SequenceDesc> inline 
typename KeyframeNumberSequenceTmpl<SequenceDesc>::StoredType
  KeyframeNumberSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index ) const
{
    return _field[index];
}

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index )
{
    val = _field[index];
}

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index ) const
{
    val = _field[index];
}


template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::setRawKeyframe (const StoredType &val,
                           const Real32     &key,
                           const UInt32     index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::addRawKeyframe (const StoredType &val,
                           const Real32     &key )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::insertRawKeyframe(const StoredType &val,
                             const Real32     &key,
                             const UInt32     index)
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        addRawKeyframe(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, val);
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

#ifdef OSG_MT_CPTR_ASPECT
template <class SequenceDesc> inline 
typename KeyframeNumberSequenceTmpl<SequenceDesc>::ObjCPtr 
    KeyframeNumberSequenceTmpl<SequenceDesc>::createAspectCopy(
        const FieldContainer *pRefAspect) const
{
    ObjCPtr returnValue; 

    newAspectCopy(returnValue, 
                  dynamic_cast<const Self *>(pRefAspect),
                  dynamic_cast<const Self *>(this)); 

    return returnValue; 
}
#endif

#ifdef OSG_MT_CPTR_ASPECT
template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::execSync(
          Self              *pFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.syncWith(pFrom->_field, syncMode, uiSyncInfo, oOffsets);
    }
}

template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::execSyncV(     
          FieldContainer    &oFrom,
          ConstFieldMaskArg  whichField,
          AspectOffsetStore &oOffsets,
          ConstFieldMaskArg  syncMode  ,
    const UInt32             uiSyncInfo)
{
    this->execSync(static_cast<Self *>(&oFrom),
                   whichField,
                   oOffsets,
                   syncMode,
                   uiSyncInfo);
}

template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class SequenceDesc> inline 
UInt32 KeyframeNumberSequenceTmpl<SequenceDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = KeyframeNumberSequence::getBinSize(whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeNumberSequence::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeNumberSequence::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeNumberSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeNumberSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeNumberSequenceTmpl<SequenceDesc>::editFieldPtr(void)
{
    editMField(SequenceDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeNumberSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeNumberSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeNumberSequenceTmpl<SequenceDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeNumberSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeNumberSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeNumberSequenceTmpl<SequenceDesc>::editField(void)
{
    editMField(SequenceDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeNumberSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeNumberSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeNumberSequenceTmpl<SequenceDesc>::getField(void) const
{
    return _field;
}

//[>! Returns a copy of this property that holds the same data.

    //\return A copy of this property.
 //*/
//template <class SequenceDesc> inline
//SequenceTransitPtr
//KeyframeNumberSequenceTmpl<SequenceDesc>::clone(void)
//{
    //ObjTransitPtr obj = Self::create();

    //editMField(SequenceDataFieldMask, obj->_field);
    
    //obj->_field.setValues(_field);

    //return SequenceTransitPtr(obj);
//}

/*! \copydoc OSG::KeyframeNumberSequence::getFormat
 */
template <class SequenceDesc> inline 
bool KeyframeNumberSequenceTmpl<SequenceDesc>::isBlendable(void) const
{
    return SequenceDesc::isBlendable();
}

/*! \copydoc OSG::KeyframeNumberSequence::size
 */
template <class SequenceDesc> inline
UInt32 KeyframeNumberSequenceTmpl<SequenceDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::KeyframeNumberSequence::size
 */
template <class SequenceDesc> inline
const Field& KeyframeNumberSequenceTmpl<SequenceDesc>::getKeyValues(void) const
{
    return _field;
}

/*! \copydoc OSG::KeyframeNumberSequence::size
 */
template <class SequenceDesc> inline
const DataType& KeyframeNumberSequenceTmpl<SequenceDesc>::getDataType(void) const
{
    return SequenceDesc::StoredFieldType::getClassType().getContentType();
}

template <class SequenceDesc> inline 
void KeyframeNumberSequenceTmpl<SequenceDesc>::push_back (const GenericType &val,
                                                              const Real32 &key   )
{
    addKeyframe(val,key);
}

/*! Removes all Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::clear(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.clear();
    _mfInternalKeys.clear();
}

/*! Resizes the Number of Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::resize(size_t      newsize)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.resize(newsize);
    _mfInternalKeys.resize(newsize);
}

/*! Shrinks Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::shrink(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class SequenceDesc> inline
RawInterpFuncion KeyframeNumberSequenceTmpl<SequenceDesc>::bindInterpFunction(UInt32 InterpolationFunctionId) const
{
    typename SequenceDesc::ConcreteInterpFunction f(SequenceDesc::getInterpolationFuncMap()[InterpolationFunctionId]);
    if(f.empty())
    {
        return NULL;
    }
    else
    {
        return boost::bind(f, static_cast<const StoredFieldType&>(getKeyValues()),this->getKeys(),_1,_2,_3);
    }
}

template <class SequenceDesc> inline
ReplacementFuncion KeyframeNumberSequenceTmpl<SequenceDesc>::getReplacementFuncion(void) const
{
    return &replacement<typename SequenceDesc::SingleFieldType>;
}

template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    KeyframeNumberSequence::dump(uiIndent, bvFlags);
}

template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::initMethod(InitPhase ePhase)
{
    SequenceDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

template <class SequenceDesc> inline
void KeyframeNumberSequenceTmpl<SequenceDesc>::exitMethod(InitPhase ePhase)
{
    SequenceDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class SequenceDesc> inline
EditFieldHandlePtr KeyframeNumberSequenceTmpl<SequenceDesc>::editHandleField(
    void)
{
    StoredEditHandlePtr returnValue(
        new  StoredEditHandle(
             &_field, 
             this->getType().getFieldDesc(SequenceDataFieldId),
             this));

    editMField(SequenceDataFieldMask, _field);

    return returnValue;
}

template <class SequenceDesc> inline
GetFieldHandlePtr KeyframeNumberSequenceTmpl<SequenceDesc>::getHandleField(
    void) const
{
    StoredGetHandlePtr returnValue(
        new  StoredGetHandle(
             &_field, 
             this->getType().getFieldDesc(SequenceDataFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

/************************** Unsigned Integers  ********************/
/************************** UInt8  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFUInt8&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFUInt8&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<UInt8>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<UInt8>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt8DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<UInt8>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** UInt16  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFUInt16&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFUInt16&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<UInt16>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<UInt16>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt16DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<UInt16>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** UInt32  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFUInt32&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFUInt32&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<UInt32>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<UInt32>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt32DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<UInt32>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** UInt64  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFUInt64&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFUInt64&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<UInt64>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<UInt64>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceUInt64DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<UInt64>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Signed Integers  ********************/
/************************** Int8  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFInt8&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFInt8&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Int8>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Int8>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt8DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Int8>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Int16  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFInt16&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFInt16&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Int16>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Int16>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt16DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Int16>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Int32  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFInt32&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFInt32&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Int32>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Int32>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt32DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Int32>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Int64  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFInt64&>(*Result->getField()).setValue(0);
    }
    else
    {
        static_cast<MFInt64&>(*Result->getField())[Index] = 0;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Int64>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Int64>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceInt64DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Int64>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real Numbers  ********************/
/************************** Real16  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFReal16&>(*Result->getField()).setValue(0.0f);
    }
    else
    {
        static_cast<MFReal16&>(*Result->getField())[Index] = 0.0f;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Real16>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Real16>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal16DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Real16>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real32  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFReal32&>(*Result->getField()).setValue(0.0f);
    }
    else
    {
        static_cast<MFReal32&>(*Result->getField())[Index] = 0.0f;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Real32>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Real32>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal32DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Real32>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Fixed32  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(Fixed32::toDouble(_field[index]));
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(Fixed32::toDouble(_field[index]));
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(Fixed32::toDouble(_field[index]));
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(Fixed32::toDouble(_field[index]));
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFFixed32&>(*Result->getField()).setValue(0.0f);
    }
    else
    {
        static_cast<MFFixed32&>(*Result->getField())[Index] = 0.0f;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Fixed32>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Fixed32>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceFixed32DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Fixed32>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real64  ********************/
template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::getKeyValue (const UInt32       index ) const
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::GenericType 
      KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::getKeyValue (const UInt32       index )
{
    return static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = static_cast<GenericType>(_field[index]);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<SFReal64&>(*Result->getField()).setValue(0.0f);
    }
    else
    {
        static_cast<MFReal64&>(*Result->getField())[Index] = 0.0f;
    }
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = static_cast<Real64>(val);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(static_cast<Real64>(val));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeNumberSequenceTmpl<KeyframeNumberSequenceReal64DescBase>::insertKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    if(_field.size() < index)
    {
        assert(false && "Index Out of bounds.");
    }
    else if(_field.size() == index)
    {
        push_back(val,key);
    }
    else
    {
        editMField(SequenceDataFieldMask, _field);
        editMField(InternalKeysFieldMask, _mfInternalKeys);

        _field.insert(_field.begin() + index, static_cast<Real64>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

OSG_END_NAMESPACE

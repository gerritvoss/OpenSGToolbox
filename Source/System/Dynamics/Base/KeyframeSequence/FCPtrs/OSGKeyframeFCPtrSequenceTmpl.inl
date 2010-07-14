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
KeyframeFCPtrSequenceTmpl<SequenceDesc>::KeyframeFCPtrSequenceTmpl(void) :
     KeyframeFCPtrSequence(),
    _field         ()
{
}

template <class SequenceDesc> inline 
KeyframeFCPtrSequenceTmpl<SequenceDesc>::KeyframeFCPtrSequenceTmpl(
    const KeyframeFCPtrSequenceTmpl &source ) :

     KeyframeFCPtrSequence(source),
    _field         (source._field)
{
}

template <class SequenceDesc> inline 
KeyframeFCPtrSequenceTmpl<SequenceDesc>::~KeyframeFCPtrSequenceTmpl(void)
{
}

template <class SequenceDesc> inline 
typename KeyframeFCPtrSequenceTmpl<SequenceDesc>::StoredPtrType 
  KeyframeFCPtrSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index )
{
    return _field[index];
}

template <class SequenceDesc> inline 
typename KeyframeFCPtrSequenceTmpl<SequenceDesc>::StoredPtrType
  KeyframeFCPtrSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index ) const
{
    return _field[index];
}

template <class SequenceDesc> inline 
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::setRawKeyframe (StoredPtrType const val,
                           const Real32     &key,
                           const UInt32     index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template <class SequenceDesc> inline 
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::addRawKeyframe (StoredPtrType const val,
                           const Real32     &key )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <class SequenceDesc> inline 
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::insertRawKeyframe(StoredPtrType const val,
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
typename KeyframeFCPtrSequenceTmpl<SequenceDesc>::ObjCPtr 
    KeyframeFCPtrSequenceTmpl<SequenceDesc>::createAspectCopy(
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
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::execSync(
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
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::execSyncV(     
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
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class SequenceDesc> inline 
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class SequenceDesc> inline 
UInt32 KeyframeFCPtrSequenceTmpl<SequenceDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = KeyframeFCPtrSequence::getBinSize(whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class SequenceDesc> inline 
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeFCPtrSequence::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class SequenceDesc> inline 
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeFCPtrSequence::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeFCPtrSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeFCPtrSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeFCPtrSequenceTmpl<SequenceDesc>::editFieldPtr(void)
{
    editMField(SequenceDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeFCPtrSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeFCPtrSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeFCPtrSequenceTmpl<SequenceDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeFCPtrSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeFCPtrSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeFCPtrSequenceTmpl<SequenceDesc>::editField(void)
{
    editMField(SequenceDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeFCPtrSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeFCPtrSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeFCPtrSequenceTmpl<SequenceDesc>::getField(void) const
{
    return _field;
}

//[>! Returns a copy of this property that holds the same data.

    //\return A copy of this property.
 //*/
//template <class SequenceDesc> inline
//SequenceTransitPtr
//KeyframeFCPtrSequenceTmpl<SequenceDesc>::clone(void)
//{
    //ObjTransitPtr obj = Self::create();

    //editMField(SequenceDataFieldMask, obj->_field);
    
    //obj->_field.setValues(_field);

    //return SequenceTransitPtr(obj);
//}

/*! \copydoc OSG::KeyframeFCPtrSequence::getFormat
 */
template <class SequenceDesc> inline 
bool KeyframeFCPtrSequenceTmpl<SequenceDesc>::isBlendable(void) const
{
    return SequenceDesc::isBlendable();
}

/*! \copydoc OSG::KeyframeFCPtrSequence::size
 */
template <class SequenceDesc> inline
UInt32 KeyframeFCPtrSequenceTmpl<SequenceDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::KeyframeFCPtrSequence::size
 */
template <class SequenceDesc> inline
const Field& KeyframeFCPtrSequenceTmpl<SequenceDesc>::getKeyValues(void) const
{
    return _field;
}

/*! \copydoc OSG::KeyframeFCPtrSequence::size
 */
template <class SequenceDesc> inline
const DataType& KeyframeFCPtrSequenceTmpl<SequenceDesc>::getDataType(void) const
{
    return SequenceDesc::StoredFieldType::getClassType().getContentType();
}

template <class SequenceDesc> inline 
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::push_back (const GenericType &val,
                                                              const Real32 &key   )
{
    addKeyframe(val,key);
}

/*! Removes all Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::clear(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.clear();
    _mfInternalKeys.clear();
}

/*! Resizes the Number of Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::resize(size_t      newsize)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.resize(newsize);
    _mfInternalKeys.resize(newsize);
}

/*! Shrinks Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::shrink(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    //TODO
    //StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class SequenceDesc> inline
RawInterpFuncion KeyframeFCPtrSequenceTmpl<SequenceDesc>::bindInterpFunction(UInt32 InterpolationFunctionId) const
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
ReplacementFuncion KeyframeFCPtrSequenceTmpl<SequenceDesc>::getReplacementFuncion(void) const
{
    return &replacementOverwriteOnly<typename SequenceDesc::SingleFieldType,typename SequenceDesc::StoredFieldType>;
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    KeyframeFCPtrSequence::dump(uiIndent, bvFlags);
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::initMethod(InitPhase ePhase)
{
    SequenceDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::exitMethod(InitPhase ePhase)
{
    SequenceDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class SequenceDesc> inline
EditFieldHandlePtr KeyframeFCPtrSequenceTmpl<SequenceDesc>::editHandleField(
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
GetFieldHandlePtr KeyframeFCPtrSequenceTmpl<SequenceDesc>::getHandleField(
    void) const
{
    StoredGetHandlePtr returnValue(
        new  StoredGetHandle(
             &_field, 
             this->getType().getFieldDesc(SequenceDataFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = getKeyValue(index); 
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = getKeyValue(index); 
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        static_cast<typename SequenceDesc::SingleFieldType&>(*Result->getField()).setValue(NULL);
    }
    else
    {
        static_cast<typename SequenceDesc::StoredFieldType&>(*Result->getField())[Index] = NULL;
    }
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = dynamic_pointer_cast<typename SequenceDesc::StoredType>(val);
    _mfInternalKeys[index] = key;
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(dynamic_pointer_cast<typename SequenceDesc::StoredType>(val));
    _mfInternalKeys.push_back(key);
}

template <class SequenceDesc> inline
void KeyframeFCPtrSequenceTmpl<SequenceDesc>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, dynamic_pointer_cast<typename SequenceDesc::StoredType>(val));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Image  ********************/
template<> inline 
KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceImageDescBase>::GenericType 
      KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceImageDescBase>::getKeyValue (const UInt32       index ) const
{
    return ImageUnrecPtr(_field[index]);
}

template<> inline 
KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceImageDescBase>::GenericType 
      KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceImageDescBase>::getKeyValue (const UInt32       index )
{
    return ImageUnrecPtr(_field[index]);
}

/************************** StateChunk  ********************/
template<> inline 
KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceStateChunkDescBase>::GenericType 
      KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceStateChunkDescBase>::getKeyValue (const UInt32       index ) const
{
    return StateChunkUnrecPtr(_field[index]);
}

template<> inline 
KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceStateChunkDescBase>::GenericType 
      KeyframeFCPtrSequenceTmpl<KeyframeFCPtrSequenceStateChunkDescBase>::getKeyValue (const UInt32       index )
{
    return StateChunkUnrecPtr(_field[index]);
}
OSG_END_NAMESPACE

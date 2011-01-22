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
KeyframeColorSequenceTmpl<SequenceDesc>::KeyframeColorSequenceTmpl(void) :
     KeyframeColorSequence(),
    _field         ()
{
}

template <class SequenceDesc> inline 
KeyframeColorSequenceTmpl<SequenceDesc>::KeyframeColorSequenceTmpl(
    const KeyframeColorSequenceTmpl &source ) :

     KeyframeColorSequence(source),
    _field         (source._field)
{
}

template <class SequenceDesc> inline 
KeyframeColorSequenceTmpl<SequenceDesc>::~KeyframeColorSequenceTmpl(void)
{
}

template <class SequenceDesc> inline 
typename KeyframeColorSequenceTmpl<SequenceDesc>::StoredType 
  KeyframeColorSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index )
{
    return _field[index];
}

template <class SequenceDesc> inline 
typename KeyframeColorSequenceTmpl<SequenceDesc>::StoredType
  KeyframeColorSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index ) const
{
    return _field[index];
}

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index )
{
    val = _field[index];
}

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index ) const
{
    val = _field[index];
}


template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::setRawKeyframe (const StoredType &val,
                           const Real32     &key,
                           const UInt32     index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::addRawKeyframe (const StoredType &val,
                           const Real32     &key )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::insertRawKeyframe(const StoredType &val,
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
typename KeyframeColorSequenceTmpl<SequenceDesc>::ObjCPtr 
    KeyframeColorSequenceTmpl<SequenceDesc>::createAspectCopy(
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
void KeyframeColorSequenceTmpl<SequenceDesc>::execSync(
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
void KeyframeColorSequenceTmpl<SequenceDesc>::execSyncV(     
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
void KeyframeColorSequenceTmpl<SequenceDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class SequenceDesc> inline 
UInt32 KeyframeColorSequenceTmpl<SequenceDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = KeyframeColorSequence::getBinSize(whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeColorSequence::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeColorSequence::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeColorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeColorSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeColorSequenceTmpl<SequenceDesc>::editFieldPtr(void)
{
    editMField(SequenceDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeColorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeColorSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeColorSequenceTmpl<SequenceDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeColorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeColorSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeColorSequenceTmpl<SequenceDesc>::editField(void)
{
    editMField(SequenceDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeColorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeColorSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeColorSequenceTmpl<SequenceDesc>::getField(void) const
{
    return _field;
}

//[>! Returns a copy of this property that holds the same data.

    //\return A copy of this property.
 //*/
//template <class SequenceDesc> inline
//SequenceTransitPtr
//KeyframeColorSequenceTmpl<SequenceDesc>::clone(void)
//{
    //ObjTransitPtr obj = Self::create();

    //editMField(SequenceDataFieldMask, obj->_field);
    
    //obj->_field.setValues(_field);

    //return SequenceTransitPtr(obj);
//}

/*! \copydoc OSG::KeyframeColorSequence::getFormat
 */
template <class SequenceDesc> inline 
bool KeyframeColorSequenceTmpl<SequenceDesc>::isBlendable(void) const
{
    return SequenceDesc::isBlendable();
}

/*! \copydoc OSG::KeyframeColorSequence::size
 */
template <class SequenceDesc> inline
UInt32 KeyframeColorSequenceTmpl<SequenceDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::KeyframeColorSequence::size
 */
template <class SequenceDesc> inline
const Field& KeyframeColorSequenceTmpl<SequenceDesc>::getKeyValues(void) const
{
    return _field;
}

/*! \copydoc OSG::KeyframeColorSequence::size
 */
template <class SequenceDesc> inline
const DataType*  KeyframeColorSequenceTmpl<SequenceDesc>::getDataType(void) const
{
    return &SequenceDesc::StoredFieldType::getClassType().getContentType();
}

template <class SequenceDesc> inline 
void KeyframeColorSequenceTmpl<SequenceDesc>::push_back (const GenericType &val,
                                                              const Real32 &key   )
{
    addKeyframe(val,key);
}

/*! Removes all Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeColorSequenceTmpl<SequenceDesc>::clear(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.clear();
    _mfInternalKeys.clear();
}

/*! Resizes the Number of Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeColorSequenceTmpl<SequenceDesc>::resize(size_t      newsize)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.resize(newsize);
    _mfInternalKeys.resize(newsize);
}

/*! Shrinks Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeColorSequenceTmpl<SequenceDesc>::shrink(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class SequenceDesc> inline
bool KeyframeColorSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
                         Real32 time,
                         Real32 prevTime,
                         UInt32 ReplacePolicy,
                         bool isCyclic,
                         EditFieldHandlePtr Result,
                         UInt32 Index,
                         Real32 Blend)
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        return interpolate(Type,
                           time,
                           prevTime,
                           ReplacePolicy,
                           isCyclic,
                           static_cast<SingleFieldType&>(*Result->getField()).getValue(),
                           Blend);
    }
    else
    {
        return interpolate(Type,
                           time,
                           prevTime,
                           ReplacePolicy,
                           isCyclic,
                           static_cast<MField<typename SingleFieldType::StoredType>&>(*Result->getField())[Index],
                           Blend);
    }
}

template <class SequenceDesc> inline
void KeyframeColorSequenceTmpl<SequenceDesc>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        zeroField(static_cast<SingleFieldType&>(*Result->getField()).getValue());
    }
    else
    {
        zeroField(static_cast<MField<typename SingleFieldType::StoredType>&>(*Result->getField())[Index]);
    }
}

template <class SequenceDesc> inline
bool KeyframeColorSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
                                                           Real32 time,
                                                           Real32 prevTime,
                                                           UInt32 ReplacePolicy,
                                                           bool isCyclic,
                                                           StoredType& Result,
                                                           Real32 Blend)
{
    typename SequenceDesc::ConcreteInterpFunction InterpFunc(SequenceDesc::getInterpolationFuncMap()[Type]);
    if(InterpFunc.empty())
    {
        SWARNING << "KeyframeSequence::interpolate(...): No Interpolation function of type: " << Type << std::endl;
        return false;
    }
    typename SequenceDesc::InterpReplaceFunction InterpReplaceFunc(boost::bind(InterpFunc, static_cast<const StoredFieldType&>(getKeyValues()),this->getKeys(),_1,_2,_3));
    typename SequenceDesc::ConcreteReplaceFunction ReplaceFunc(SequenceDesc::getReplacementFuncMap()[ReplacePolicy]);
    if(ReplaceFunc.empty())
    {
        SWARNING << "KeyframeSequence::interpolate(...): No Replacement function." << std::endl;
        return false;
    }

    return ReplaceFunc(InterpReplaceFunc, time, prevTime, isCyclic, Result, Blend);
}

template <class SequenceDesc> inline
void KeyframeColorSequenceTmpl<SequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    KeyframeColorSequence::dump(uiIndent, bvFlags);
}

template <class SequenceDesc> inline
void KeyframeColorSequenceTmpl<SequenceDesc>::initMethod(InitPhase ePhase)
{
    SequenceDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

template <class SequenceDesc> inline
void KeyframeColorSequenceTmpl<SequenceDesc>::exitMethod(InitPhase ePhase)
{
    SequenceDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class SequenceDesc> inline
EditFieldHandlePtr KeyframeColorSequenceTmpl<SequenceDesc>::editHandleField(
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
GetFieldHandlePtr KeyframeColorSequenceTmpl<SequenceDesc>::getHandleField(
    void) const
{
    StoredGetHandlePtr returnValue(
        new  StoredGetHandle(
             &_field, 
             this->getType().getFieldDesc(SequenceDataFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

/************************** Int16  ********************/
/************************** Color3ub  ********************/
template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f);
}

template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::zeroField(StoredType& Result) const
{
    Result = Color3ub(0,0,0);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Color3ub(val[0],val[1],val[2]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Color3ub(val[0],val[1],val[2]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3ubDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Color3ub(val[0],val[1],val[2]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Color4ub  ********************/
template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
}

template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2],_field[index][3]); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2],_field[index][3]); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::zeroField(StoredType& Result) const
{
    Result = Color4ub(0,0,0,0);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Color4ub(val[0], val[1], val[2], val[3]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Color4ub(val[0], val[1], val[2], val[3]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4ubDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Color4ub(val[0], val[1], val[2], val[3]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real32  ********************/
/************************** Color3f  ********************/
template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f);
}

template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2],1.0f); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::zeroField(StoredType& Result) const
{
    Result = Color3f(0.0,0.0,0.0);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Color3f(val[0],val[1],val[2]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Color3f(val[0],val[1],val[2]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Color3f(val[0],val[1],val[2]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Color4f  ********************/
template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
}

template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2],_field[index][3]); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2],_field[index][3]); 
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::zeroField(StoredType& Result) const
{
    Result = Color4f(0.0,0.0,0.0,0.0);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Color4f(val[0], val[1], val[2], val[3]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Color4f(val[0], val[1], val[2], val[3]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Color4f(val[0], val[1], val[2], val[3]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Fixed32  ********************/
/************************** Color3fx  ********************/
template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]),
                       1.0f);
}

template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]),
                       1.0f);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  Fixed32::toFloat(_field[index][2]),
                  1.0f);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  Fixed32::toFloat(_field[index][2]),1.0f);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::zeroField(StoredType& Result) const
{
    Result = Color3fx(0.0f,0.0f,0.0f);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Color3fx(val[0],val[1],val[2]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Color3fx(val[0],val[1],val[2]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor3fxDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Color3fx(val[0],val[1],val[2]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Color4fx  ********************/
template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]),
                       Fixed32::toFloat(_field[index][3]));
}

template<> inline 
KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::GenericType 
      KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]),
                       Fixed32::toFloat(_field[index][3]));
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  Fixed32::toFloat(_field[index][2]),
                  Fixed32::toFloat(_field[index][3]));
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  Fixed32::toFloat(_field[index][2]),
                  Fixed32::toFloat(_field[index][3]));
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::zeroField(StoredType& Result) const
{
    Result = Color4fx(0.0f,0.0f,0.0f,0.0f);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Color4fx(val[0], val[1], val[2], val[3]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Color4fx(val[0], val[1], val[2], val[3]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeColorSequenceTmpl<KeyframeColorSequenceColor4fxDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Color4fx(val[0], val[1], val[2], val[3]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

OSG_END_NAMESPACE

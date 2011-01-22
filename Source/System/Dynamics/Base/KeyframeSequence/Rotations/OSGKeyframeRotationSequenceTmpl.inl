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
KeyframeRotationSequenceTmpl<SequenceDesc>::KeyframeRotationSequenceTmpl(void) :
     KeyframeRotationSequence(),
    _field         ()
{
}

template <class SequenceDesc> inline 
KeyframeRotationSequenceTmpl<SequenceDesc>::KeyframeRotationSequenceTmpl(
    const KeyframeRotationSequenceTmpl &source ) :

     KeyframeRotationSequence(source),
    _field         (source._field)
{
}

template <class SequenceDesc> inline 
KeyframeRotationSequenceTmpl<SequenceDesc>::~KeyframeRotationSequenceTmpl(void)
{
}

template <class SequenceDesc> inline 
typename KeyframeRotationSequenceTmpl<SequenceDesc>::StoredType 
  KeyframeRotationSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index )
{
    return _field[index];
}

template <class SequenceDesc> inline 
typename KeyframeRotationSequenceTmpl<SequenceDesc>::StoredType
  KeyframeRotationSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index ) const
{
    return _field[index];
}

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index )
{
    val = _field[index];
}

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index ) const
{
    val = _field[index];
}


template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::setRawKeyframe (const StoredType &val,
                           const Real32     &key,
                           const UInt32     index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::addRawKeyframe (const StoredType &val,
                           const Real32     &key )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::insertRawKeyframe(const StoredType &val,
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
typename KeyframeRotationSequenceTmpl<SequenceDesc>::ObjCPtr 
    KeyframeRotationSequenceTmpl<SequenceDesc>::createAspectCopy(
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
void KeyframeRotationSequenceTmpl<SequenceDesc>::execSync(
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
void KeyframeRotationSequenceTmpl<SequenceDesc>::execSyncV(     
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
void KeyframeRotationSequenceTmpl<SequenceDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class SequenceDesc> inline 
UInt32 KeyframeRotationSequenceTmpl<SequenceDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = KeyframeRotationSequence::getBinSize(whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeRotationSequence::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeRotationSequence::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeRotationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeRotationSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeRotationSequenceTmpl<SequenceDesc>::editFieldPtr(void)
{
    editMField(SequenceDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeRotationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeRotationSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeRotationSequenceTmpl<SequenceDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeRotationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeRotationSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeRotationSequenceTmpl<SequenceDesc>::editField(void)
{
    editMField(SequenceDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeRotationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeRotationSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeRotationSequenceTmpl<SequenceDesc>::getField(void) const
{
    return _field;
}

//[>! Returns a copy of this property that holds the same data.

    //\return A copy of this property.
 //*/
//template <class SequenceDesc> inline
//SequenceTransitPtr
//KeyframeRotationSequenceTmpl<SequenceDesc>::clone(void)
//{
    //ObjTransitPtr obj = Self::create();

    //editMField(SequenceDataFieldMask, obj->_field);
    
    //obj->_field.setValueAsQuat(_field);

    //return SequenceTransitPtr(obj);
//}

/*! \copydoc OSG::KeyframeRotationSequence::getFormat
 */
template <class SequenceDesc> inline 
bool KeyframeRotationSequenceTmpl<SequenceDesc>::isBlendable(void) const
{
    return SequenceDesc::isBlendable();
}

/*! \copydoc OSG::KeyframeRotationSequence::size
 */
template <class SequenceDesc> inline
UInt32 KeyframeRotationSequenceTmpl<SequenceDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::KeyframeRotationSequence::size
 */
template <class SequenceDesc> inline
const Field& KeyframeRotationSequenceTmpl<SequenceDesc>::getKeyValues(void) const
{
    return _field;
}

/*! \copydoc OSG::KeyframeRotationSequence::size
 */
template <class SequenceDesc> inline
const DataType*  KeyframeRotationSequenceTmpl<SequenceDesc>::getDataType(void) const
{
    return &SequenceDesc::StoredFieldType::getClassType().getContentType();
}

template <class SequenceDesc> inline 
void KeyframeRotationSequenceTmpl<SequenceDesc>::push_back (const GenericType &val,
                                                              const Real32 &key   )
{
    addKeyframe(val,key);
}

/*! Removes all Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeRotationSequenceTmpl<SequenceDesc>::clear(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.clear();
    _mfInternalKeys.clear();
}

/*! Resizes the Number of Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeRotationSequenceTmpl<SequenceDesc>::resize(size_t      newsize)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.resize(newsize);
    _mfInternalKeys.resize(newsize);
}

/*! Shrinks Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeRotationSequenceTmpl<SequenceDesc>::shrink(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class SequenceDesc> inline
bool KeyframeRotationSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
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
void KeyframeRotationSequenceTmpl<SequenceDesc>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
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
bool KeyframeRotationSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
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
void KeyframeRotationSequenceTmpl<SequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    KeyframeRotationSequence::dump(uiIndent, bvFlags);
}

template <class SequenceDesc> inline
void KeyframeRotationSequenceTmpl<SequenceDesc>::initMethod(InitPhase ePhase)
{
    SequenceDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

template <class SequenceDesc> inline
void KeyframeRotationSequenceTmpl<SequenceDesc>::exitMethod(InitPhase ePhase)
{
    SequenceDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class SequenceDesc> inline
EditFieldHandlePtr KeyframeRotationSequenceTmpl<SequenceDesc>::editHandleField(
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
GetFieldHandlePtr KeyframeRotationSequenceTmpl<SequenceDesc>::getHandleField(
    void) const
{
    StoredGetHandlePtr returnValue(
        new  StoredGetHandle(
             &_field, 
             this->getType().getFieldDesc(SequenceDataFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

/************************** Real32  ********************/
/************************** Quaternion  ********************/
template<> inline 
KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::GenericType 
      KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
}

template<> inline 
KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::GenericType 
      KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValueAsQuat(_field[index][0],_field[index][1],_field[index][2],_field[index][3]); 
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValueAsQuat(_field[index][0],_field[index][1],_field[index][2],_field[index][3]); 
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::zeroField(StoredType& Result) const
{
    Result = Quaternion(0.0,0.0,0.0,1.0);
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Quaternion(val[0], val[1], val[2], val[3]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Quaternion(val[0], val[1], val[2], val[3]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Quaternion(val[0], val[1], val[2], val[3]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Fixed32  ********************/
/************************** Quaternionfx  ********************/
template<> inline 
KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::GenericType 
      KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]),
                       Fixed32::toFloat(_field[index][3])
                       );
}

template<> inline 
KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::GenericType 
      KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]),
                       Fixed32::toFloat(_field[index][3])
                       );
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValueAsQuat(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  Fixed32::toFloat(_field[index][2]),
                  Fixed32::toFloat(_field[index][3])
                  );
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValueAsQuat(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  Fixed32::toFloat(_field[index][2]),
                  Fixed32::toFloat(_field[index][3])
                  );
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::zeroField(StoredType& Result) const
{
    Result = Quaternionfx(0.0f,0.0f,0.0f,1.0f);
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Quaternionfx(val[0], val[1], val[2], val[3]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Quaternionfx(val[0], val[1], val[2], val[3]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaternionfxDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Quaternionfx(val[0], val[1], val[2], val[3]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real64  ********************/
/************************** Quaterniond  ********************/
//template<> inline 
//KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::GenericType 
      //KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::getKeyValue (const UInt32       index ) const
//{
    //return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
//}

//template<> inline 
//KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::GenericType 
      //KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::getKeyValue (const UInt32       index )
//{
    //return GenericType(_field[index][0],_field[index][1],_field[index][2],_field[index][3]);
//}

//template<> inline 
//void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::getKeyValue (GenericType &val,
                              //const UInt32       index )      
//{
    //val.setValueAsQuat(_field[index][0],_field[index][1],_field[index][1],_field[index][1]); 
//}

//template<> inline 
//void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::getKeyValue (GenericType &val,
                              //const UInt32       index ) const
//{
    //val.setValueAsQuat(_field[index][0],_field[index][1],_field[index][1],_field[index][1]); 
//}

//template<> inline 
//void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::zeroField(StoredType& Result) const
//{
    //Result = Quaterniond(0.0,0.0,0.0,1.0);
//}

//template<> inline 
//void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::setKeyframe (const GenericType &val,
                                                              //const Real32 &key,
                                                              //const UInt32       index )
//{
    //editMField(SequenceDataFieldMask, _field);
    //editMField(InternalKeysFieldMask, _mfInternalKeys);

    //_field[index] = Quaterniond(val[0], val[1], val[2], val[3]);
    //_mfInternalKeys[index] = key;
//}

//template<> inline 
//void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::addKeyframe (const GenericType &val,
                                                              //const Real32 &key   )
//{
    //editMField(SequenceDataFieldMask, _field);
    //editMField(InternalKeysFieldMask, _mfInternalKeys);

    //_field.push_back(Quaterniond(val[0], val[1], val[2], val[3]));
    //_mfInternalKeys.push_back(key);
//}

//template<> inline 
//void KeyframeRotationSequenceTmpl<KeyframeRotationSequenceQuaterniondDescBase>::insertKeyframe (const GenericType &val,
                                                              //const Real32 &key,
                                                              //const UInt32       index )
//{
    //if(_field.size() < index)
    //{
        //assert(false && "Index Out of bounds.");
    //}
    //else if(_field.size() == index)
    //{
        //push_back(val,key);
    //}
    //else
    //{
        //editMField(SequenceDataFieldMask, _field);
        //editMField(InternalKeysFieldMask, _mfInternalKeys);

        //_field.insert(_field.begin() + index, Quaterniond(val[0], val[1], val[2], val[3]));
        //this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    //}
//}

OSG_END_NAMESPACE

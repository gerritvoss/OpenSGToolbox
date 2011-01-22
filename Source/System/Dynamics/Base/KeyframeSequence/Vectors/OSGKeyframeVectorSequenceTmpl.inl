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
KeyframeVectorSequenceTmpl<SequenceDesc>::KeyframeVectorSequenceTmpl(void) :
     KeyframeVectorSequence(),
    _field         ()
{
}

template <class SequenceDesc> inline 
KeyframeVectorSequenceTmpl<SequenceDesc>::KeyframeVectorSequenceTmpl(
    const KeyframeVectorSequenceTmpl &source ) :

     KeyframeVectorSequence(source),
    _field         (source._field)
{
}

template <class SequenceDesc> inline 
KeyframeVectorSequenceTmpl<SequenceDesc>::~KeyframeVectorSequenceTmpl(void)
{
}

template <class SequenceDesc> inline 
typename KeyframeVectorSequenceTmpl<SequenceDesc>::StoredType 
  KeyframeVectorSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index )
{
    return _field[index];
}

template <class SequenceDesc> inline 
typename KeyframeVectorSequenceTmpl<SequenceDesc>::StoredType
  KeyframeVectorSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index ) const
{
    return _field[index];
}

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index )
{
    val = _field[index];
}

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index ) const
{
    val = _field[index];
}


template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::setRawKeyframe (const StoredType &val,
                           const Real32     &key,
                           const UInt32     index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::addRawKeyframe (const StoredType &val,
                           const Real32     &key )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::insertRawKeyframe(const StoredType &val,
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
typename KeyframeVectorSequenceTmpl<SequenceDesc>::ObjCPtr 
    KeyframeVectorSequenceTmpl<SequenceDesc>::createAspectCopy(
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
void KeyframeVectorSequenceTmpl<SequenceDesc>::execSync(
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
void KeyframeVectorSequenceTmpl<SequenceDesc>::execSyncV(     
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
void KeyframeVectorSequenceTmpl<SequenceDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class SequenceDesc> inline 
UInt32 KeyframeVectorSequenceTmpl<SequenceDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = KeyframeVectorSequence::getBinSize(whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeVectorSequence::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeVectorSequence::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeVectorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeVectorSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeVectorSequenceTmpl<SequenceDesc>::editFieldPtr(void)
{
    editMField(SequenceDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeVectorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeVectorSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeVectorSequenceTmpl<SequenceDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeVectorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeVectorSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeVectorSequenceTmpl<SequenceDesc>::editField(void)
{
    editMField(SequenceDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeVectorSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeVectorSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeVectorSequenceTmpl<SequenceDesc>::getField(void) const
{
    return _field;
}

//[>! Returns a copy of this property that holds the same data.

    //\return A copy of this property.
 //*/
//template <class SequenceDesc> inline
//SequenceTransitPtr
//KeyframeVectorSequenceTmpl<SequenceDesc>::clone(void)
//{
    //ObjTransitPtr obj = Self::create();

    //editMField(SequenceDataFieldMask, obj->_field);
    
    //obj->_field.setValues(_field);

    //return SequenceTransitPtr(obj);
//}

/*! \copydoc OSG::KeyframeVectorSequence::getFormat
 */
template <class SequenceDesc> inline 
bool KeyframeVectorSequenceTmpl<SequenceDesc>::isBlendable(void) const
{
    return SequenceDesc::isBlendable();
}

/*! \copydoc OSG::KeyframeVectorSequence::size
 */
template <class SequenceDesc> inline
UInt32 KeyframeVectorSequenceTmpl<SequenceDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::KeyframeVectorSequence::size
 */
template <class SequenceDesc> inline
const Field& KeyframeVectorSequenceTmpl<SequenceDesc>::getKeyValues(void) const
{
    return _field;
}

/*! \copydoc OSG::KeyframeVectorSequence::size
 */
template <class SequenceDesc> inline
const DataType*  KeyframeVectorSequenceTmpl<SequenceDesc>::getDataType(void) const
{
    return &SequenceDesc::StoredFieldType::getClassType().getContentType();
}

template <class SequenceDesc> inline 
void KeyframeVectorSequenceTmpl<SequenceDesc>::push_back (const GenericType &val,
                                                              const Real32 &key   )
{
    addKeyframe(val,key);
}

/*! Removes all Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeVectorSequenceTmpl<SequenceDesc>::clear(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.clear();
    _mfInternalKeys.clear();
}

/*! Resizes the Number of Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeVectorSequenceTmpl<SequenceDesc>::resize(size_t      newsize)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.resize(newsize);
    _mfInternalKeys.resize(newsize);
}

/*! Shrinks Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeVectorSequenceTmpl<SequenceDesc>::shrink(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class SequenceDesc> inline
bool KeyframeVectorSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
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
                           static_cast<StoredFieldType&>(*Result->getField())[Index],
                           Blend);
    }
}

template <class SequenceDesc> inline
void KeyframeVectorSequenceTmpl<SequenceDesc>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        zeroField(static_cast<SingleFieldType&>(*Result->getField()).getValue());
    }
    else
    {
        zeroField(static_cast<StoredFieldType&>(*Result->getField())[Index]);
    }
}

template <class SequenceDesc> inline
bool KeyframeVectorSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
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
void KeyframeVectorSequenceTmpl<SequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    KeyframeVectorSequence::dump(uiIndent, bvFlags);
}

template <class SequenceDesc> inline
void KeyframeVectorSequenceTmpl<SequenceDesc>::initMethod(InitPhase ePhase)
{
    SequenceDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

template <class SequenceDesc> inline
void KeyframeVectorSequenceTmpl<SequenceDesc>::exitMethod(InitPhase ePhase)
{
    SequenceDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class SequenceDesc> inline
EditFieldHandlePtr KeyframeVectorSequenceTmpl<SequenceDesc>::editHandleField(
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
GetFieldHandlePtr KeyframeVectorSequenceTmpl<SequenceDesc>::getHandleField(
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
/************************** Vec2s  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],0);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec2s(0,0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec2s(val[0], val[1]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec2s(val[0], val[1]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2sDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec2s(val[0], val[1]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec3s  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec3s(0,0,0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec3s(val[0],val[1],val[2]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec3s(val[0],val[1],val[2]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3sDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec3s(val[0],val[1],val[2]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec4s  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec4s(0,0,0,0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec4s(val[0], val[1], val[2], 1.0);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec4s(val[0], val[1], val[2], 1.0));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4sDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec4s(val[0], val[1], val[2], 1.0));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real32  ********************/
/************************** Vec1f  ********************/
template<> inline 
bool KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::interpolate(UInt32 Type,
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
        assert(false);
        return false;
    }
    else
    {
        return interpolate(Type,
                           time,
                           prevTime,
                           ReplacePolicy,
                           isCyclic,
                           static_cast<StoredFieldType&>(*Result->getField())[Index],
                           Blend);
    }
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec1f(0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        assert(false);
    }
    else
    {
        zeroField(static_cast<StoredFieldType&>(*Result->getField())[Index]);
    }
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],0.0,0.0);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],0.0,0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],0.0,0.0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],0.0,0.0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec1f(val[0]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec1f(val[0]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec1fDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec1f(val[0]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec2f  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],0.0);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],0.0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],0.0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec2f(0.0,0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec2f(val[0], val[1]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec2f(val[0], val[1]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec2f(val[0], val[1]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec3f  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::getKeyValue (const UInt32       index ) const
{
    return _field[index];
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::getKeyValue (const UInt32       index )
{
    return _field[index];
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = _field[index]; 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = _field[index]; 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec3f(0.0,0.0,0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, val);
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec4f  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec4f(0.0,0.0,0.0,0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec4f(val[0], val[1], val[2], 1.0);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec4f(val[0], val[1], val[2], 1.0));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec4f(val[0], val[1], val[2], 1.0));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Fixed32  ********************/
/************************** Vec2fx  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       0.0f);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       0.0f);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  0.0f);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                  Fixed32::toFloat(_field[index][1]),
                  0.0f);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec2fx(0.0f,0.0f);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec2fx(val[0], val[1]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec2fx(val[0], val[1]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2fxDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec2fx(val[0], val[1]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec3fx  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec3fx(0.0f,0.0f,0.0f);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec3fx(val[0],val[1],val[2]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec3fx(val[0],val[1],val[2]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3fxDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec3fx(val[0],val[1],val[2]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec4fx  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(Fixed32::toFloat(_field[index][0]),
                       Fixed32::toFloat(_field[index][1]),
                       Fixed32::toFloat(_field[index][2]));
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec4fx(0.0f,0.0f,0.0f,0.0f);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec4fx(val[0], val[1], val[2], 1.0f);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec4fx(val[0], val[1], val[2], 1.0f));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4fxDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec4fx(val[0], val[1], val[2], 1.0f));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real64  ********************/
/************************** Vec2d  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],0.0);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],0.0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],0.0); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec2d(0.0,0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec2d(val[0], val[1]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec2d(val[0], val[1]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec2dDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec2d(val[0], val[1]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec3d  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = GenericType(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec3d(0.0,0.0,0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec3d(val[0],val[1],val[2]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec3d(val[0],val[1],val[2]));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec3dDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec3d(val[0],val[1],val[2]));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Vec4d  ********************/
template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::GenericType 
      KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0],_field[index][1],_field[index][2]);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValues(_field[index][0],_field[index][1],_field[index][2]); 
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::zeroField(StoredType& Result) const
{
    Result = Vec4d(0.0,0.0,0.0,0.0);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Vec4d(val[0], val[1], val[2], 1.0);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Vec4d(val[0], val[1], val[2], 1.0));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeVectorSequenceTmpl<KeyframeVectorSequenceVec4dDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, Vec4d(val[0], val[1], val[2], 1.0));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

OSG_END_NAMESPACE

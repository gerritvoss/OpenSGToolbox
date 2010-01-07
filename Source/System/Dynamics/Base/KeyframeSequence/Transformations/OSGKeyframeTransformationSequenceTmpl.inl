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
KeyframeTransformationSequenceTmpl<SequenceDesc>::KeyframeTransformationSequenceTmpl(void) :
     KeyframeTransformationSequence(),
    _field         ()
{
}

template <class SequenceDesc> inline 
KeyframeTransformationSequenceTmpl<SequenceDesc>::KeyframeTransformationSequenceTmpl(
    const KeyframeTransformationSequenceTmpl &source ) :

     KeyframeTransformationSequence(source),
    _field         (source._field)
{
}

template <class SequenceDesc> inline 
KeyframeTransformationSequenceTmpl<SequenceDesc>::~KeyframeTransformationSequenceTmpl(void)
{
}

#ifdef OSG_MT_CPTR_ASPECT
template <class SequenceDesc> inline 
typename KeyframeTransformationSequenceTmpl<SequenceDesc>::ObjCPtr 
    KeyframeTransformationSequenceTmpl<SequenceDesc>::createAspectCopy(
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
void KeyframeTransformationSequenceTmpl<SequenceDesc>::execSync(
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
void KeyframeTransformationSequenceTmpl<SequenceDesc>::execSyncV(     
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
void KeyframeTransformationSequenceTmpl<SequenceDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class SequenceDesc> inline 
void KeyframeTransformationSequenceTmpl<SequenceDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class SequenceDesc> inline 
UInt32 KeyframeTransformationSequenceTmpl<SequenceDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = KeyframeTransformationSequence::getBinSize(whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class SequenceDesc> inline 
void KeyframeTransformationSequenceTmpl<SequenceDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeTransformationSequence::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class SequenceDesc> inline 
void KeyframeTransformationSequenceTmpl<SequenceDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeTransformationSequence::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeTransformationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeTransformationSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeTransformationSequenceTmpl<SequenceDesc>::editFieldPtr(void)
{
    editMField(SequenceDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeTransformationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeTransformationSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeTransformationSequenceTmpl<SequenceDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeTransformationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeTransformationSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeTransformationSequenceTmpl<SequenceDesc>::editField(void)
{
    editMField(SequenceDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeTransformationSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeTransformationSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeTransformationSequenceTmpl<SequenceDesc>::getField(void) const
{
    return _field;
}

//[>! Returns a copy of this property that holds the same data.

    //\return A copy of this property.
 //*/
//template <class SequenceDesc> inline
//SequenceTransitPtr
//KeyframeTransformationSequenceTmpl<SequenceDesc>::clone(void)
//{
    //ObjTransitPtr obj = Self::create();

    //editMField(SequenceDataFieldMask, obj->_field);
    
    //obj->_field.setValues(_field);

    //return SequenceTransitPtr(obj);
//}

/*! \copydoc OSG::KeyframeTransformationSequence::getFormat
 */
template <class SequenceDesc> inline 
bool KeyframeTransformationSequenceTmpl<SequenceDesc>::isBlendable(void) const
{
    return SequenceDesc::isBlendable();
}

/*! \copydoc OSG::KeyframeTransformationSequence::size
 */
template <class SequenceDesc> inline
UInt32 KeyframeTransformationSequenceTmpl<SequenceDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::KeyframeTransformationSequence::size
 */
template <class SequenceDesc> inline
const Field& KeyframeTransformationSequenceTmpl<SequenceDesc>::getKeyValues(void) const
{
    return _field;
}

/*! \copydoc OSG::KeyframeTransformationSequence::size
 */
template <class SequenceDesc> inline
const DataType& KeyframeTransformationSequenceTmpl<SequenceDesc>::getDataType(void) const
{
    return SequenceDesc::StoredFieldType::getClassType().getContentType();
}

template <class SequenceDesc> inline 
void KeyframeTransformationSequenceTmpl<SequenceDesc>::push_back (const GenericType &val,
                                                              const Real32 &key   )
{
    addKeyframe(val,key);
}

/*! Removes all Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeTransformationSequenceTmpl<SequenceDesc>::clear(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.clear();
    _mfInternalKeys.clear();
}

/*! Resizes the Number of Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeTransformationSequenceTmpl<SequenceDesc>::resize(size_t      newsize)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.resize(newsize);
    _mfInternalKeys.resize(newsize);
}

/*! Shrinks Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeTransformationSequenceTmpl<SequenceDesc>::shrink(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class SequenceDesc> inline
RawInterpFuncion KeyframeTransformationSequenceTmpl<SequenceDesc>::bindInterpFunction(UInt32 InterpolationFunctionId) const
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
ReplacementFuncion KeyframeTransformationSequenceTmpl<SequenceDesc>::getReplacementFuncion(void) const
{
    return &matrixReplacement<typename SequenceDesc::SingleFieldType>;
}

template <class SequenceDesc> inline
void KeyframeTransformationSequenceTmpl<SequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    KeyframeTransformationSequence::dump(uiIndent, bvFlags);
}

template <class SequenceDesc> inline
void KeyframeTransformationSequenceTmpl<SequenceDesc>::initMethod(InitPhase ePhase)
{
    SequenceDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

template <class SequenceDesc> inline
void KeyframeTransformationSequenceTmpl<SequenceDesc>::exitMethod(InitPhase ePhase)
{
    SequenceDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class SequenceDesc> inline
EditFieldHandlePtr KeyframeTransformationSequenceTmpl<SequenceDesc>::editHandleField(
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
GetFieldHandlePtr KeyframeTransformationSequenceTmpl<SequenceDesc>::getHandleField(
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
/************************** Matrix4f  ********************/
template<> inline 
KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::GenericType 
      KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
}

template<> inline 
KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::GenericType 
      KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValue(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                 _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                 _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                 _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                );
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValue(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                 _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                 _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                 _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                );
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::zeroField(Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == FieldType::SingleField)
    {
        static_cast<SFMatrix&>(Result).setValue(Matrix::identity());
    }
    else
    {
        static_cast<MFMatrix&>(Result)[Index].setValue(Matrix::identity());
    }
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Matrix4f(val[0][0],val[1][0],val[2][0],val[3][0],
                             val[0][1],val[1][1],val[2][1],val[3][1],
                             val[0][2],val[1][2],val[2][2],val[3][2],
                             val[0][3],val[1][3],val[2][3],val[3][3]);
                
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Matrix4f(val[0][0],val[1][0],val[2][0],val[3][0],
                              val[0][1],val[1][1],val[2][1],val[3][1],
                              val[0][2],val[1][2],val[2][2],val[3][2],
                              val[0][3],val[1][3],val[2][3],val[3][3]
                             ));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index,
                Matrix4f(val[0][0],val[1][0],val[2][0],val[3][0],
                         val[0][1],val[1][1],val[2][1],val[3][1],
                         val[0][2],val[1][2],val[2][2],val[3][2],
                         val[0][3],val[1][3],val[2][3],val[3][3]
                        ));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Fixed32  ********************/
/************************** Matrix4fx  ********************/
template<> inline 
KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::GenericType 
      KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::getKeyValue (const UInt32       index ) const
{
#ifdef OSG_FLOAT_PROFILE
    return GenericType(Fixed32::toFloat(_field[index][0][0]),Fixed32::toFloat(_field[index][1][0]),Fixed32::toFloat(_field[index][2][0]),Fixed32::toFloat(_field[index][3][0]),
                       Fixed32::toFloat(_field[index][0][1]),Fixed32::toFloat(_field[index][1][1]),Fixed32::toFloat(_field[index][2][1]),Fixed32::toFloat(_field[index][3][1]),
                       Fixed32::toFloat(_field[index][0][2]),Fixed32::toFloat(_field[index][1][2]),Fixed32::toFloat(_field[index][2][2]),Fixed32::toFloat(_field[index][3][2]),
                       Fixed32::toFloat(_field[index][0][3]),Fixed32::toFloat(_field[index][1][3]),Fixed32::toFloat(_field[index][2][3]),Fixed32::toFloat(_field[index][3][3])
                      );
#else
    return GenericType(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
#endif
}

template<> inline 
KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::GenericType 
      KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::getKeyValue (const UInt32       index )
{
#ifdef OSG_FLOAT_PROFILE
    return GenericType(Fixed32::toFloat(_field[index][0][0]),Fixed32::toFloat(_field[index][1][0]),Fixed32::toFloat(_field[index][2][0]),Fixed32::toFloat(_field[index][3][0]),
                       Fixed32::toFloat(_field[index][0][1]),Fixed32::toFloat(_field[index][1][1]),Fixed32::toFloat(_field[index][2][1]),Fixed32::toFloat(_field[index][3][1]),
                       Fixed32::toFloat(_field[index][0][2]),Fixed32::toFloat(_field[index][1][2]),Fixed32::toFloat(_field[index][2][2]),Fixed32::toFloat(_field[index][3][2]),
                       Fixed32::toFloat(_field[index][0][3]),Fixed32::toFloat(_field[index][1][3]),Fixed32::toFloat(_field[index][2][3]),Fixed32::toFloat(_field[index][3][3])
                      );
#else
    return GenericType(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
#endif
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
#ifdef OSG_FLOAT_PROFILE
    val.setValue(Fixed32::toFloat(_field[index][0][0]),Fixed32::toFloat(_field[index][1][0]),Fixed32::toFloat(_field[index][2][0]),Fixed32::toFloat(_field[index][3][0]),
                       Fixed32::toFloat(_field[index][0][1]),Fixed32::toFloat(_field[index][1][1]),Fixed32::toFloat(_field[index][2][1]),Fixed32::toFloat(_field[index][3][1]),
                       Fixed32::toFloat(_field[index][0][2]),Fixed32::toFloat(_field[index][1][2]),Fixed32::toFloat(_field[index][2][2]),Fixed32::toFloat(_field[index][3][2]),
                       Fixed32::toFloat(_field[index][0][3]),Fixed32::toFloat(_field[index][1][3]),Fixed32::toFloat(_field[index][2][3]),Fixed32::toFloat(_field[index][3][3])
                      );
#else
    val.setValue(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
#endif
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
#ifdef OSG_FLOAT_PROFILE
    val.setValue(Fixed32::toFloat(_field[index][0][0]),Fixed32::toFloat(_field[index][1][0]),Fixed32::toFloat(_field[index][2][0]),Fixed32::toFloat(_field[index][3][0]),
                       Fixed32::toFloat(_field[index][0][1]),Fixed32::toFloat(_field[index][1][1]),Fixed32::toFloat(_field[index][2][1]),Fixed32::toFloat(_field[index][3][1]),
                       Fixed32::toFloat(_field[index][0][2]),Fixed32::toFloat(_field[index][1][2]),Fixed32::toFloat(_field[index][2][2]),Fixed32::toFloat(_field[index][3][2]),
                       Fixed32::toFloat(_field[index][0][3]),Fixed32::toFloat(_field[index][1][3]),Fixed32::toFloat(_field[index][2][3]),Fixed32::toFloat(_field[index][3][3])
                      );
#else
    val.setValue(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
#endif
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::zeroField(Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == FieldType::SingleField)
    {
        static_cast<SFMatrix4fx&>(Result).setValue(Matrix4fx::identity());
    }
    else
    {
        static_cast<MFMatrix4fx&>(Result)[Index] = Matrix4fx::identity();
    }
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Matrix4fx(val[0][0],val[1][0],val[2][0],val[3][0],
                             val[0][1],val[1][1],val[2][1],val[3][1],
                             val[0][2],val[1][2],val[2][2],val[3][2],
                             val[0][3],val[1][3],val[2][3],val[3][3]);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Matrix4fx(val[0][0],val[1][0],val[2][0],val[3][0],
                              val[0][1],val[1][1],val[2][1],val[3][1],
                              val[0][2],val[1][2],val[2][2],val[3][2],
                              val[0][3],val[1][3],val[2][3],val[3][3]
                             ));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4fxDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index,
                Matrix4fx(val[0][0],val[1][0],val[2][0],val[3][0],
                         val[0][1],val[1][1],val[2][1],val[3][1],
                         val[0][2],val[1][2],val[2][2],val[3][2],
                         val[0][3],val[1][3],val[2][3],val[3][3]
                        ));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** Real64  ********************/
/************************** Matrix4d  ********************/
template<> inline 
KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::GenericType 
      KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::getKeyValue (const UInt32       index ) const
{
    return GenericType(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
}

template<> inline 
KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::GenericType 
      KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::getKeyValue (const UInt32       index )
{
    return GenericType(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                       _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                       _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                       _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                      );
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val.setValue(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                 _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                 _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                 _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                );
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val.setValue(_field[index][0][0],_field[index][1][0],_field[index][2][0],_field[index][3][0],
                 _field[index][0][1],_field[index][1][1],_field[index][2][1],_field[index][3][1],
                 _field[index][0][2],_field[index][1][2],_field[index][2][2],_field[index][3][2],
                 _field[index][0][3],_field[index][1][3],_field[index][2][3],_field[index][3][3]
                );
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::zeroField(Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == FieldType::SingleField)
    {
        static_cast<SFMatrix4d&>(Result).setValue(Matrix4d::identity());
    }
    else
    {
        static_cast<MFMatrix4d&>(Result)[Index].setValue(Matrix4d::identity());
    }
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = Matrix4d(val[0][0],val[1][0],val[2][0],val[3][0],
                             val[0][1],val[1][1],val[2][1],val[3][1],
                             val[0][2],val[1][2],val[2][2],val[3][2],
                             val[0][3],val[1][3],val[2][3],val[3][3]);
                
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(Matrix4d(val[0][0],val[1][0],val[2][0],val[3][0],
                              val[0][1],val[1][1],val[2][1],val[3][1],
                              val[0][2],val[1][2],val[2][2],val[3][2],
                              val[0][3],val[1][3],val[2][3],val[3][3]
                             ));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeTransformationSequenceTmpl<KeyframeTransformationSequenceMatrix4dDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index,
                Matrix4d(val[0][0],val[1][0],val[2][0],val[3][0],
                         val[0][1],val[1][1],val[2][1],val[3][1],
                         val[0][2],val[1][2],val[2][2],val[3][2],
                         val[0][3],val[1][3],val[2][3],val[3][3]
                        ));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

OSG_END_NAMESPACE

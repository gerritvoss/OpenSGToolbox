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

#include "OSGGLDefineMapper.h"
#include <sstream>

OSG_BEGIN_NAMESPACE


template <class SequenceDesc> inline 
KeyframeBasicSequenceTmpl<SequenceDesc>::KeyframeBasicSequenceTmpl(void) :
     KeyframeBasicSequence(),
    _field         ()
{
}

template <class SequenceDesc> inline 
KeyframeBasicSequenceTmpl<SequenceDesc>::KeyframeBasicSequenceTmpl(
    const KeyframeBasicSequenceTmpl &source ) :

     KeyframeBasicSequence(source),
    _field         (source._field)
{
}

template <class SequenceDesc> inline 
KeyframeBasicSequenceTmpl<SequenceDesc>::~KeyframeBasicSequenceTmpl(void)
{
}

template <class SequenceDesc> inline 
typename KeyframeBasicSequenceTmpl<SequenceDesc>::StoredType 
  KeyframeBasicSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index )
{
    return _field[index];
}

template <class SequenceDesc> inline 
typename KeyframeBasicSequenceTmpl<SequenceDesc>::StoredType
  KeyframeBasicSequenceTmpl<SequenceDesc>::getRawKeyValue (const UInt32 index ) const
{
    return _field[index];
}

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index )
{
    val = _field[index];
}

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::getRawKeyValue (StoredType   &val,
                           const UInt32 index ) const
{
    val = _field[index];
}


template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::setRawKeyframe (const StoredType &val,
                           const Real32     &key,
                           const UInt32     index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::addRawKeyframe (const StoredType &val,
                           const Real32     &key )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::insertRawKeyframe(const StoredType &val,
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
typename KeyframeBasicSequenceTmpl<SequenceDesc>::ObjCPtr 
    KeyframeBasicSequenceTmpl<SequenceDesc>::createAspectCopy(
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
void KeyframeBasicSequenceTmpl<SequenceDesc>::execSync(
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
void KeyframeBasicSequenceTmpl<SequenceDesc>::execSyncV(     
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
void KeyframeBasicSequenceTmpl<SequenceDesc>::resolveLinks(void)
{
    Inherited::resolveLinks();

    AspectOffsetStore oOffsets;

    _pAspectStore->fillOffsetArray(oOffsets, this);

    _field.terminateShare(Thread::getCurrentAspect(), oOffsets);
}


#endif

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::changed(
    ConstFieldMaskArg whichField, 
    UInt32            origin,
    BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

template <class SequenceDesc> inline 
UInt32 KeyframeBasicSequenceTmpl<SequenceDesc>::getBinSize(
    ConstFieldMaskArg whichField)
{
    UInt32 returnValue = KeyframeBasicSequence::getBinSize(whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::copyToBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeBasicSequence::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::copyFromBin(
    BinaryDataHandler &pMem,
    ConstFieldMaskArg  whichField)
{
    KeyframeBasicSequence::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (SequenceDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeBasicSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeBasicSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeBasicSequenceTmpl<SequenceDesc>::editFieldPtr(void)
{
    editMField(SequenceDataFieldMask, _field);

    return &_field;
}

/*! Returns a pointer to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeBasicSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Pointer to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeBasicSequenceTmpl<SequenceDesc>::StoredFieldType * 
    KeyframeBasicSequenceTmpl<SequenceDesc>::getFieldPtr(void) const
{
    return &_field;
}

/*! Returns a reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeBasicSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
typename KeyframeBasicSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeBasicSequenceTmpl<SequenceDesc>::editField(void)
{
    editMField(SequenceDataFieldMask, _field);

    return _field;
}

/*! Returns a const reference to the stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the KeyframeBasicSequence provides, but it
    necessitates compile-time knowledge about the involved concrete types.

    \return Reference to the data field.
*/
template <class SequenceDesc> inline 
const typename KeyframeBasicSequenceTmpl<SequenceDesc>::StoredFieldType & 
    KeyframeBasicSequenceTmpl<SequenceDesc>::getField(void) const
{
    return _field;
}

//[>! Returns a copy of this property that holds the same data.

    //\return A copy of this property.
 //*/
//template <class SequenceDesc> inline
//SequenceTransitPtr
//KeyframeBasicSequenceTmpl<SequenceDesc>::clone(void)
//{
    //ObjTransitPtr obj = Self::create();

    //editMField(SequenceDataFieldMask, obj->_field);
    
    //obj->_field.setValues(_field);

    //return SequenceTransitPtr(obj);
//}

/*! \copydoc OSG::KeyframeBasicSequence::getFormat
 */
template <class SequenceDesc> inline 
bool KeyframeBasicSequenceTmpl<SequenceDesc>::isBlendable(void) const
{
    return SequenceDesc::isBlendable();
}

/*! \copydoc OSG::KeyframeBasicSequence::size
 */
template <class SequenceDesc> inline
UInt32 KeyframeBasicSequenceTmpl<SequenceDesc>::size(void) const
{
    return _field.size();
}

/*! \copydoc OSG::KeyframeBasicSequence::size
 */
template <class SequenceDesc> inline
const Field& KeyframeBasicSequenceTmpl<SequenceDesc>::getKeyValues(void) const
{
    return _field;
}

/*! \copydoc OSG::KeyframeBasicSequence::size
 */
template <class SequenceDesc> inline
const DataType*  KeyframeBasicSequenceTmpl<SequenceDesc>::getDataType(void) const
{
    return &SequenceDesc::StoredFieldType::getClassType().getContentType();
}

template <class SequenceDesc> inline 
void KeyframeBasicSequenceTmpl<SequenceDesc>::push_back (const GenericType &val,
                                                              const Real32 &key   )
{
    addKeyframe(val,key);
}

/*! Removes all Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeBasicSequenceTmpl<SequenceDesc>::clear(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.clear();
    _mfInternalKeys.clear();
}

/*! Resizes the Number of Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeBasicSequenceTmpl<SequenceDesc>::resize(size_t      newsize)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.resize(newsize);
    _mfInternalKeys.resize(newsize);
}

/*! Shrinks Keyframes.
 */
template <class SequenceDesc> inline
void KeyframeBasicSequenceTmpl<SequenceDesc>::shrink(void)
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    StoredFieldType(_field).swap(_field);
    this->_mfInternalKeys.swap(this->_mfInternalKeys);
}

template <class SequenceDesc> inline
bool KeyframeBasicSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
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
void KeyframeBasicSequenceTmpl<SequenceDesc>::zeroField(EditFieldHandlePtr Result, UInt32 Index) const
{
    if(Result->getCardinality() == FieldType::SingleField)
    {
        return zeroField(static_cast<SingleFieldType&>(*Result->getField()).getValue());
    }
    else
    {
        return zeroField(static_cast<MField<typename SingleFieldType::StoredType>&>(*Result->getField())[Index]);
    }
}

template <class SequenceDesc> inline
bool KeyframeBasicSequenceTmpl<SequenceDesc>::interpolate(UInt32 Type,
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
void KeyframeBasicSequenceTmpl<SequenceDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    KeyframeBasicSequence::dump(uiIndent, bvFlags);
}

template <class SequenceDesc> inline
void KeyframeBasicSequenceTmpl<SequenceDesc>::initMethod(InitPhase ePhase)
{
    SequenceDesc::initMethod(ePhase);

    Inherited::initMethod(ePhase);
}

template <class SequenceDesc> inline
void KeyframeBasicSequenceTmpl<SequenceDesc>::exitMethod(InitPhase ePhase)
{
    SequenceDesc::exitMethod(ePhase);

    Inherited::exitMethod(ePhase);
}

template <class SequenceDesc> inline
EditFieldHandlePtr KeyframeBasicSequenceTmpl<SequenceDesc>::editHandleField(
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
GetFieldHandlePtr KeyframeBasicSequenceTmpl<SequenceDesc>::getHandleField(
    void) const
{
    StoredGetHandlePtr returnValue(
        new  StoredGetHandle(
             &_field, 
             this->getType().getFieldDesc(SequenceDataFieldId),
             const_cast<Self *>(this)));

    return returnValue;
}

/************************** std::string  ********************/
template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::getKeyValue (const UInt32       index ) const
{
    return _field[index];
}

template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::getKeyValue (const UInt32       index )
{
    return _field[index];
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = _field[index]; 
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = _field[index]; 
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::zeroField(StoredType& Result) const
{
    Result = std::string("");
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = val;
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceStringDescBase>::insertKeyframe (const GenericType &val,
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

/************************** Bool  ********************/
template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::getKeyValue (const UInt32       index ) const
{
    return GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::getKeyValue (const UInt32       index )
{
    return GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::zeroField(StoredType& Result) const
{
    Result = GL_NONE;
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = GLDefineMapper::the()->fromString(val.c_str());
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(GLDefineMapper::the()->fromString(val.c_str()));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoolDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, GLDefineMapper::the()->fromString(val.c_str()));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** GLenum  ********************/
template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::getKeyValue (const UInt32       index ) const
{
    return GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::getKeyValue (const UInt32       index )
{
    return GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = GLDefineMapper::the()->toString(_field[index]);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::zeroField(StoredType& Result) const
{
    Result = GL_NONE;
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field[index] = GLDefineMapper::the()->fromString(val.c_str());
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    _field.push_back(GLDefineMapper::the()->fromString(val.c_str()));
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceGLenumDescBase>::insertKeyframe (const GenericType &val,
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

        _field.insert(_field.begin() + index, GLDefineMapper::the()->fromString(val.c_str()));
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

/************************** BoxVolume  ********************/
template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::getKeyValue (const UInt32       index ) const
{
    std::ostringstream  TheSStream;
    OutStream TheOutStream(TheSStream);
    FieldTraits<BoxVolume>::putToStream(_field[index], TheOutStream);
    return TheSStream.str();
}

template<> inline 
KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::GenericType 
      KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::getKeyValue (const UInt32       index )
{
    std::ostringstream  TheSStream;
    OutStream TheOutStream(TheSStream);
    FieldTraits<BoxVolume>::putToStream(_field[index], TheOutStream);
    return TheSStream.str();
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index )      
{
    val = getKeyValue(index);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::getKeyValue (GenericType &val,
                              const UInt32       index ) const
{
    val = getKeyValue(index);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::zeroField(StoredType& Result) const
{
    Result.setBounds(0.0f,0.0f,0.0f);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::setKeyframe (const GenericType &val,
                                                              const Real32 &key,
                                                              const UInt32       index )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    const Char8* TheCString(val.c_str());
    FieldTraits<BoxVolume>::getFromCString(_field[index], TheCString);
    _mfInternalKeys[index] = key;
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::addKeyframe (const GenericType &val,
                                                              const Real32 &key   )
{
    editMField(SequenceDataFieldMask, _field);
    editMField(InternalKeysFieldMask, _mfInternalKeys);

    BoxVolume NewVolume;
    const Char8* TheCString(val.c_str());
    FieldTraits<BoxVolume>::getFromCString(NewVolume, TheCString);
    _field.push_back(NewVolume);
    _mfInternalKeys.push_back(key);
}

template<> inline 
void KeyframeBasicSequenceTmpl<KeyframeBasicSequenceBoxVolumeDescBase>::insertKeyframe (const GenericType &val,
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

        BoxVolume NewVolume;
        const Char8* TheCString(val.c_str());
        FieldTraits<BoxVolume>::getFromCString(NewVolume, TheCString);
        _field.insert(_field.begin() + index, NewVolume);
        this->_mfInternalKeys.insert(this->_mfInternalKeys.begin() + index, key);
    }
}

OSG_END_NAMESPACE

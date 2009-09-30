/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox Animation                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

#ifndef DOXYGEN_SHOULD_SKIP_THIS

//NumbersUInt8
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFUInt8&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFUInt8&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersUInt16
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFUInt16&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFUInt16&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersUInt32
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFUInt32&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFUInt32&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersUInt64
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFUInt64&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFUInt64&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersUInt8
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFInt8&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFInt8&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersInt16
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFInt16&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFInt16&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersInt32
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFInt32&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFInt32&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersInt64
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFInt64&>(Result).setValue(0);
    }
    else
    {
        static_cast<MFInt64&>(Result)[Index] = 0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersReal32
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFReal32&>(Result).setValue(0.0f);
    }
    else
    {
        static_cast<MFReal32&>(Result)[Index] = 0.0f;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//NumbersReal64
template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFReal64&>(Result).setValue(0.0);
    }
    else
    {
        static_cast<MFReal64&>(Result)[Index] = 0.0;
    }
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Real32 KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::getKeyValue(
          Real32   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::getKeyValue(
          Real32  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::setKeyframe(const Real32  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::addKeyframe(const Real32 &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::insertKeyframe(const Real32 &val,
                                          const Real32 &key,
                                                          const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addKeyframe(val,key);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, val);
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

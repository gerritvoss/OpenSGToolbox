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

//Vectors2s
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec2s&>(Result).setValue(Vec2s(0,0));
    }
    else
    {
        static_cast<MFVec2s&>(Result)[Index] = Vec2s(0,0);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec2s(Int16(val[0]), Int16(val[1])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec2s(Int16(val[0]), 
                                                    Int16(val[1])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Vectors2f
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec2f&>(Result).setValue(Vec2f(0.0f,0.0f));
    }
    else
    {
        static_cast<MFVec2f&>(Result)[Index] = Vec2f(0.0f,0.0f);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real32(val[0]), Real32(val[1]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec2f(Real32(val[0]), Real32(val[1])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec2f(Real32(val[0]), 
                                                    Real32(val[1])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


//Vectors2d
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec2d&>(Result).setValue(Vec2d(0.0,0.0));
    }
    else
    {
        static_cast<MFVec2d&>(Result)[Index] = Vec2d(0.0,0.0);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real64(val[0]), Real64(val[1]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec2d(Real64(val[0]), Real64(val[1])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec2d(Real64(val[0]), 
                                                    Real64(val[1])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Vectors3s
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec3s&>(Result).setValue(Vec3s(0,0,0));
    }
    else
    {
        static_cast<MFVec3s&>(Result)[Index] = Vec3s(0,0,0);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]), Int16(val[2]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec3s(Int16(val[0]), Int16(val[1]), Int16(val[2])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec3s(Int16(val[0]), 
                                                    Int16(val[1]), Int16(val[2])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Vectors3f
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec3f&>(Result).setValue(Vec3f(0.0f,0.0f,0.0f));
    }
    else
    {
        static_cast<MFVec3f&>(Result)[Index] = Vec3f(0.0f,0.0f,0.0f);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real32(val[0]), Real32(val[1]), Real32(val[2]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec3f(Real32(val[0]), Real32(val[1]), Real32(val[2])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec3f(Real32(val[0]), 
                                                    Real32(val[1]), Real32(val[2])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


//Vectors3d
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec3d&>(Result).setValue(Vec3d(0.0,0.0,0.0));
    }
    else
    {
        static_cast<MFVec3d&>(Result)[Index] = Vec3d(0.0,0.0,0.0);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real64(val[0]), Real64(val[1]), Real64(val[2]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec3d(Real64(val[0]), Real64(val[1]), Real64(val[2])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec3d(Real64(val[0]), 
                                                    Real64(val[1]), 
                                                    Real64(val[2])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Vectors4s
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec4s&>(Result).setValue(Vec4s(0,0,0,0));
    }
    else
    {
        static_cast<MFVec4s&>(Result)[Index] = Vec4s(0,0,0,0);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]), Int16(val[2]), 0);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec4s(Int16(val[0]), Int16(val[1]), Int16(val[2]), 0));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec4s(Int16(val[0]), 
                                                    Int16(val[1]), Int16(val[2]), 0));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Vectors4f
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec4f&>(Result).setValue(Vec4f(0.0f,0.0f,0.0f,0.0f));
    }
    else
    {
        static_cast<MFVec4f&>(Result)[Index] = Vec4f(0.0f,0.0f,0.0f,0.0f);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real32(val[0]), Real32(val[1]), Real32(val[2]), 0.0f);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec4f(Real32(val[0]), Real32(val[1]), Real32(val[2]), 0.0f));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec4f(Real32(val[0]), 
                                                    Real32(val[1]), Real32(val[2]), 0.0f));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


//Vectors4d
template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFVec4d&>(Result).setValue(Vec4d(0.0,0.0,0.0,0.0));
    }
    else
    {
        static_cast<MFVec4d&>(Result)[Index] = Vec4d(0.0,0.0,0.0,0.0);
    }
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::getKeyValue(const UInt32 index)
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Vec3f KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Vec3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::getKeyValue(
          Vec3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::getKeyValue(
          Vec3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::setKeyframe(const Vec3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real64(val[0]), Real64(val[1]), Real64(val[2]), 0.0);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::addKeyframe(const Vec3f &val,
                                          const Real32 &key)
{
    _field.push_back(Vec4d(Real64(val[0]), Real64(val[1]), Real64(val[2]), 0.0));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::insertKeyframe(const Vec3f &val,
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
        _field.insert(_field.begin() + index, Vec4d(Real64(val[0]), 
                                                    Real64(val[1]), Real64(val[2]), 0.0));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

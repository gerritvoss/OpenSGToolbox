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

//Positions2s
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt2s&>(Result).setValue(Pnt2s(0,0));
    }
    else
    {
        static_cast<MFPnt2s&>(Result)[Index] = Pnt2s(0,0);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt2s(Int16(val[0]), Int16(val[1])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence2sDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt2s(Int16(val[0]), 
                                                    Int16(val[1])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Positions2f
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt2f&>(Result).setValue(Pnt2f(0.0f,0.0f));
    }
    else
    {
        static_cast<MFPnt2f&>(Result)[Index] = Pnt2f(0.0f,0.0f);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real32(val[0]), Real32(val[1]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt2f(Real32(val[0]), Real32(val[1])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence2fDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt2f(Real32(val[0]), 
                                                    Real32(val[1])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


//Positions2d
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt2d&>(Result).setValue(Pnt2d(0.0,0.0));
    }
    else
    {
        static_cast<MFPnt2d&>(Result)[Index] = Pnt2d(0.0,0.0);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real64(val[0]), Real64(val[1]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt2d(Real64(val[0]), Real64(val[1])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence2dDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt2d(Real64(val[0]), 
                                                    Real64(val[1])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Positions3s
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt3s&>(Result).setValue(Pnt3s(0,0,0));
    }
    else
    {
        static_cast<MFPnt3s&>(Result)[Index] = Pnt3s(0,0,0);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]), Int16(val[2]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt3s(Int16(val[0]), Int16(val[1]), Int16(val[2])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence3sDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt3s(Int16(val[0]), 
                                                    Int16(val[1]), Int16(val[2])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Positions3f
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt3f&>(Result).setValue(Pnt3f(0.0f,0.0f,0.0f));
    }
    else
    {
        static_cast<MFPnt3f&>(Result)[Index] = Pnt3f(0.0f,0.0f,0.0f);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real32(val[0]), Real32(val[1]), Real32(val[2]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt3f(Real32(val[0]), Real32(val[1]), Real32(val[2])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence3fDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt3f(Real32(val[0]), 
                                                    Real32(val[1]), Real32(val[2])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


//Positions3d
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt3d&>(Result).setValue(Pnt3d(0.0,0.0,0.0));
    }
    else
    {
        static_cast<MFPnt3d&>(Result)[Index] = Pnt3d(0.0,0.0,0.0);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], 0.0f);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real64(val[0]), Real64(val[1]), Real64(val[2]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt3d(Real64(val[0]), Real64(val[1]), Real64(val[2])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence3dDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt3d(Real64(val[0]), 
                                                    Real64(val[1]), 
                                                    Real64(val[2])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Positions4s
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt4s&>(Result).setValue(Pnt4s(0,0,0,0));
    }
    else
    {
        static_cast<MFPnt4s&>(Result)[Index] = Pnt4s(0,0,0,0);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Int16(val[0]), Int16(val[1]), Int16(val[2]), 0);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt4s(Int16(val[0]), Int16(val[1]), Int16(val[2]), 0));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence4sDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt4s(Int16(val[0]), 
                                                    Int16(val[1]), Int16(val[2]), 0));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Positions4f
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt4f&>(Result).setValue(Pnt4f(0.0f,0.0f,0.0f,0.0f));
    }
    else
    {
        static_cast<MFPnt4f&>(Result)[Index] = Pnt4f(0.0f,0.0f,0.0f,0.0f);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real32(val[0]), Real32(val[1]), Real32(val[2]), 0.0f);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt4f(Real32(val[0]), Real32(val[1]), Real32(val[2]), 0.0f));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence4fDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt4f(Real32(val[0]), 
                                                    Real32(val[1]), Real32(val[2]), 0.0f));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


//Positions4d
template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFPnt4d&>(Result).setValue(Pnt4d(0.0,0.0,0.0,0.0));
    }
    else
    {
        static_cast<MFPnt4d&>(Result)[Index] = Pnt4d(0.0,0.0,0.0,0.0);
    }
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::getKeyValue(const UInt32 index)
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
Pnt3f KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Pnt3f(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::getKeyValue(
          Pnt3f   &res,
    const UInt32   index)
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::getKeyValue(
          Pnt3f  &res,
    const UInt32  index) const
{
    res.setValues(_field[index][0], _field[index][1], _field[index][2]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::setKeyframe(const Pnt3f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValues(Real64(val[0]), Real64(val[1]), Real64(val[2]), 0.0);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::addKeyframe(const Pnt3f &val,
                                          const Real32 &key)
{
    _field.push_back(Pnt4d(Real64(val[0]), Real64(val[1]), Real64(val[2]), 0.0));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframePositionsSequence4dDesc>::insertKeyframe(const Pnt3f &val,
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
        _field.insert(_field.begin() + index, Pnt4d(Real64(val[0]), 
                                                    Real64(val[1]), Real64(val[2]), 0.0));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

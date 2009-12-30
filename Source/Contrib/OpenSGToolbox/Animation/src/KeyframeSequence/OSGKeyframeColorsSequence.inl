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

//Colors3ub
template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFColor3ub&>(Result).setValue(Color3ub(0,0,0));
    }
    else
    {
        static_cast<MFColor3ub&>(Result)[Index] = Color3ub(0,0,0);
    }
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::getKeyValue(const UInt32 index)
{
    return Color4f(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Color4f(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::getKeyValue(
          Color4f   &res,
    const UInt32   index)
{
    res.setValuesRGBA(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::getKeyValue(
          Color4f  &res,
    const UInt32  index) const
{
    res.setValuesRGBA(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::setKeyframe(const Color4f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValuesRGB(UInt8(val[0]), UInt8(val[1]), UInt8(val[2]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::addKeyframe(const Color4f &val,
                                          const Real32 &key)
{
    _field.push_back(Color3ub(UInt8(val[0]), UInt8(val[1]), UInt8(val[2])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeColorsSequence3ubDesc>::insertKeyframe(const Color4f &val,
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
        _field.insert(_field.begin() + index, Color3ub(UInt8(val[0]), UInt8(val[1]), UInt8(val[2])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Colors3f
template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFColor3f&>(Result).setValue(Color3f(0.0f,0.0f,0.0f));
    }
    else
    {
        static_cast<MFColor3f&>(Result)[Index] = Color3f(0.0f,0.0f,0.0f);
    }
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::getKeyValue(const UInt32 index)
{
    return Color4f(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Color4f(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::getKeyValue(
          Color4f   &res,
    const UInt32   index)
{
    res.setValuesRGBA(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::getKeyValue(
          Color4f  &res,
    const UInt32  index) const
{
    res.setValuesRGBA(_field[index][0], _field[index][1], _field[index][2], 1.0f);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::setKeyframe(const Color4f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValuesRGB(val[0], val[1], val[2]);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::addKeyframe(const Color4f &val,
                                          const Real32 &key)
{
    _field.push_back(Color3f(val[0], val[1], val[2]));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeColorsSequence3fDesc>::insertKeyframe(const Color4f &val,
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
        _field.insert(_field.begin() + index, Color3f(val[0], val[1], val[2]));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}


//Colors4ub
template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFColor4ub&>(Result).setValue(Color4ub(0,0,0,0));
    }
    else
    {
        static_cast<MFColor4ub&>(Result)[Index] = Color4ub(0,0,0,0);
    }
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::getKeyValue(const UInt32 index)
{
    return Color4f(_field[index][0], _field[index][1], _field[index][2], _field[index][3]);
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::getKeyValue( 
    const UInt32 index) const
{
    return Color4f(_field[index][0], _field[index][1], _field[index][2], _field[index][3]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::getKeyValue(
          Color4f   &res,
    const UInt32   index)
{
    res.setValuesRGBA(_field[index][0], _field[index][1], _field[index][2], _field[index][3]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::getKeyValue(
          Color4f  &res,
    const UInt32  index) const
{
    res.setValuesRGBA(_field[index][0], _field[index][1], _field[index][2], _field[index][3]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::setKeyframe(const Color4f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index].setValuesRGBA(UInt8(val[0]), UInt8(val[1]), UInt8(val[4]), UInt8(val[3]));
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::addKeyframe(const Color4f &val,
                                          const Real32 &key)
{
    _field.push_back(Color4ub(UInt8(val[0]), UInt8(val[1]), UInt8(val[4]), UInt8(val[3])));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeColorsSequence4ubDesc>::insertKeyframe(const Color4f &val,
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
        _field.insert(_field.begin() + index, Color4ub(UInt8(val[0]), UInt8(val[1]), UInt8(val[4]), UInt8(val[3])));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}

//Colors4f
template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFColor4f&>(Result).setValue(Color4f(0.0f,0.0f,0.0f,0.0f));
    }
    else
    {
        static_cast<MFColor4f&>(Result)[Index] = Color4f(0.0f,0.0f,0.0f,0.0f);
    }
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
Color4f KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::getKeyValue(
          Color4f   &res,
    const UInt32   index)
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::getKeyValue(
          Color4f  &res,
    const UInt32  index) const
{
    res=_field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::setKeyframe(const Color4f  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::addKeyframe(const Color4f &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeColorsSequence4fDesc>::insertKeyframe(const Color4f &val,
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

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

//std::string
template<> inline 
std::string KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
std::string KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::getKeyValue(
          std::string   &res,
    const UInt32   index)
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::getKeyValue(
          std::string  &res,
    const UInt32  index) const
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::setKeyframe(const std::string  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=val;
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::addKeyframe(const std::string &val,
                                          const Real32 &key)
{
    _field.push_back(val);
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::insertKeyframe(const std::string &val,
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

//std::strin
/*
template<> inline 
std::string KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::getKeyValue(const UInt32 index)
{
    return toString(_field[index]);
}


template<> inline 
std::string KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::getKeyValue( 
    const UInt32 index) const
{
    return toString(_field[index]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::getKeyValue(
          std::string   &res,
    const UInt32   index)
{
    res = toString(_field[index]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::getKeyValue(
          std::string  &res,
    const UInt32  index) const
{
    res = toString(_field[index]);
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::setKeyframe(const std::string  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    _field[index]=fromString(val);
    _mfInternalKeys[index] = key;
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::addKeyframe(const std::string &val,
                                          const Real32 &key)
{
    _field.push_back(fromString(val));
    _mfInternalKeys.push_back(key);
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::insertKeyframe(const std::string &val,
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
        _field.insert(_field.begin() + index, fromString(val));
        _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
        return true;
    }
}
*/
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

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

//FCPtrsTextureChunk
template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFTextureChunkPtr&>(Result).setValue(NullFC);
    }
    else
    {
        static_cast<MFTextureChunkPtr&>(Result)[Index] = NullFC;
    }
}

template<> inline 
FieldContainerPtr KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
FieldContainerPtr KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::getKeyValue(
          FieldContainerPtr   &res,
    const UInt32   index)
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::getKeyValue(
          FieldContainerPtr  &res,
    const UInt32  index) const
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::setKeyframe(const FieldContainerPtr  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    //if(val->getType().isDerivedFrom(TextureChunk::getClassType()))
    {
        _field[index] = TextureChunkPtr::dcast(val);
        _mfInternalKeys[index] = key;
    }
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::addKeyframe(const FieldContainerPtr &val,
                                          const Real32 &key)
{
    //if(val->getType().isDerivedFrom(TextureChunk::getClassType()))
    {
        _field.push_back(TextureChunkPtr::dcast(val));
        _mfInternalKeys.push_back(key);
    }
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeFCPtrsSequenceTextureChunkDesc>::insertKeyframe(const FieldContainerPtr &val,
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
        //if(val->getType().isDerivedFrom(TextureChunk::getClassType()))
        {
            _field.insert(_field.begin() + index, TextureChunkPtr::dcast(val));
            _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
            return true;
        }
        //else
        //{
        //    return false;
        //}
    }
}


//FCPtrsStateChunk
template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFStateChunkPtr&>(Result).setValue(NullFC);
    }
    else
    {
        static_cast<MFStateChunkPtr&>(Result)[Index] = NullFC;
    }
}

template<> inline 
FieldContainerPtr KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
FieldContainerPtr KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::getKeyValue(
          FieldContainerPtr   &res,
    const UInt32   index)
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::getKeyValue(
          FieldContainerPtr  &res,
    const UInt32  index) const
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::setKeyframe(const FieldContainerPtr  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    //if(val->getType().isDerivedFrom(StateChunk::getClassType()))
    {
        _field[index] = StateChunkPtr::dcast(val);
        _mfInternalKeys[index] = key;
    }
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::addKeyframe(const FieldContainerPtr &val,
                                          const Real32 &key)
{
    //if(val->getType().isDerivedFrom(StateChunk::getClassType()))
    {
        _field.push_back(StateChunkPtr::dcast(val));
        _mfInternalKeys.push_back(key);
    }
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeFCPtrsSequenceStateChunkDesc>::insertKeyframe(const FieldContainerPtr &val,
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
        //if(val->getType().isDerivedFrom(StateChunk::getClassType()))
        {
            _field.insert(_field.begin() + index, StateChunkPtr::dcast(val));
            _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
            return true;
        }
        //else
        //{
        //    return false;
        //}
    }
}

//FCPtrsImage
template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::zeroField(osg::Field& Result, UInt32 Index) const
{
    if(Result.getCardinality() == osg::FieldType::SINGLE_FIELD)
    {
        static_cast<SFImagePtr&>(Result).setValue(NullFC);
    }
    else
    {
        static_cast<MFImagePtr&>(Result)[Index] = NullFC;
    }
}

template<> inline 
FieldContainerPtr KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::getKeyValue(const UInt32 index)
{
    return _field[index];
}

template<> inline 
FieldContainerPtr KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::getKeyValue( 
    const UInt32 index) const
{
    return _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::getKeyValue(
          FieldContainerPtr   &res,
    const UInt32   index)
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::getKeyValue(
          FieldContainerPtr  &res,
    const UInt32  index) const
{
    res = _field[index];
}

template<> inline 
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::setKeyframe(const FieldContainerPtr  &val,
                                          const Real32 &key,
                                                       const UInt32  index)
{
    //if(val->getType().isDerivedFrom(Image::getClassType()))
    {
        _field[index] = ImagePtr::dcast(val);
        _mfInternalKeys[index] = key;
    }
}

template<>
inline
void KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::addKeyframe(const FieldContainerPtr &val,
                                          const Real32 &key)
{
    //if(val->getType().isDerivedFrom(Image::getClassType()))
    {
        _field.push_back(ImagePtr::dcast(val));
        _mfInternalKeys.push_back(key);
    }
}

template <> inline
bool KeyframeSequenceTmpl<KeyframeFCPtrsSequenceImageDesc>::insertKeyframe(const FieldContainerPtr &val,
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
        //if(val->getType().isDerivedFrom(Image::getClassType()))
        {
            _field.insert(_field.begin() + index, ImagePtr::dcast(val));
            _mfInternalKeys.insert(_mfInternalKeys.begin() + index, key);
            return true;
        }
        //else
        //{
        //    return false;
        //}
    }
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

OSG_END_NAMESPACE

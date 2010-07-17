/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),                            *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class MorphGeometry!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &MorphGeometryBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 MorphGeometryBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 MorphGeometryBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/


//! Get the value of the MorphGeometry::_sfBaseGeometry field.
inline
Geometry * MorphGeometryBase::getBaseGeometry(void) const
{
    return _sfBaseGeometry.getValue();
}

//! Set the value of the MorphGeometry::_sfBaseGeometry field.
inline
void MorphGeometryBase::setBaseGeometry(Geometry * const value)
{
    editSField(BaseGeometryFieldMask);

    _sfBaseGeometry.setValue(value);
}

//! Get the value of the MorphGeometry::_sfInternalWeights field.
inline
GeoVectorProperty * MorphGeometryBase::getInternalWeights(void) const
{
    return _sfInternalWeights.getValue();
}

//! Set the value of the MorphGeometry::_sfInternalWeights field.
inline
void MorphGeometryBase::setInternalWeights(GeoVectorProperty * const value)
{
    editSField(InternalWeightsFieldMask);

    _sfInternalWeights.setValue(value);
}

//! Get the value of the \a index element the MorphGeometry::_mfInternalTargetGeometries field.
inline
Geometry * MorphGeometryBase::getInternalTargetGeometries(const UInt32 index) const
{
    return _mfInternalTargetGeometries[index];
}

//! Get the value of the \a index element the MorphGeometry::_mfMorphProperties field.
inline
      UInt16  MorphGeometryBase::getMorphProperties(const UInt32 index) const
{
    return _mfMorphProperties[index];
}

inline
UInt16 &MorphGeometryBase::editMorphProperties(const UInt32 index)
{
    editMField(MorphPropertiesFieldMask, _mfMorphProperties);

    return _mfMorphProperties[index];
}



#ifdef OSG_MT_CPTR_ASPECT
inline
void MorphGeometryBase::execSync (      MorphGeometryBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (BaseGeometryFieldMask & whichField))
        _sfBaseGeometry.syncWith(pFrom->_sfBaseGeometry);

    if(FieldBits::NoField != (InternalTargetGeometriesFieldMask & whichField))
        _mfInternalTargetGeometries.syncWith(pFrom->_mfInternalTargetGeometries,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);

    if(FieldBits::NoField != (InternalWeightsFieldMask & whichField))
        _sfInternalWeights.syncWith(pFrom->_sfInternalWeights);

    if(FieldBits::NoField != (MorphPropertiesFieldMask & whichField))
        _mfMorphProperties.syncWith(pFrom->_mfMorphProperties,
                                syncMode,
                                uiSyncInfo,
                                oOffsets);
}
#endif


inline
const Char8 *MorphGeometryBase::getClassname(void)
{
    return "MorphGeometry";
}
OSG_GEN_CONTAINERPTR(MorphGeometry);

OSG_END_NAMESPACE


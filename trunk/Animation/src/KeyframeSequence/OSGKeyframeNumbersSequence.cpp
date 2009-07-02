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
#define OSG_COMPILEKEYFRAMENUMBERSEQUENCEINST

#include "OSGKeyframeNumbersSequence.h"

OSG_USING_NAMESPACE

FieldDescription *KeyframeNumbersSequenceUInt8Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt8Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt8Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt8Desc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeNumbersSequenceUInt16Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt16Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt16Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt16Desc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeNumbersSequenceUInt32Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt32Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt32Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt32Desc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeNumbersSequenceUInt64Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt64Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceUInt64Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceUInt64Desc>::getFieldPtr)
#endif
};


FieldDescription *KeyframeNumbersSequenceInt8Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt8Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceInt8Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt8Desc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeNumbersSequenceInt16Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt16Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceInt16Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt16Desc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeNumbersSequenceInt32Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt32Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceInt32Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt32Desc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeNumbersSequenceInt64Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt64Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceInt64Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceInt64Desc>::getFieldPtr)
#endif
};


FieldDescription *KeyframeNumbersSequenceReal32Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceReal32Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceReal32Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceReal32Desc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeNumbersSequenceReal64Desc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceReal64Desc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeNumbersSequenceReal64Desc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeNumbersSequenceReal64Desc>::getFieldPtr)
#endif
};

OSG_GEO_PROP_TYPE_TMPL_DEF(KeyframeSequenceTmpl, KeyframeSequenceDesc, PtrType)

//Deal with Exporting symbols
OSG_BEGIN_NAMESPACE

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceUInt8Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceUInt16Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceUInt32Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceUInt64Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceInt8Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceInt16Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceInt32Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceInt64Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceReal32Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeNumbersSequenceReal64Desc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_END_NAMESPACE



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
#define OSG_COMPILEKEYFRAMEVECTORSEQUENCEINST

#include "OSGKeyframeVectorsSequence.h"

OSG_USING_NAMESPACE

FieldDescription *KeyframeVectorsSequence2sDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence2sDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence2sDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence2sDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence2fDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence2fDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence2fDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence2fDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence2dDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence2dDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence2dDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence2dDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence3sDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence3sDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence3sDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence3sDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence3fDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence3fDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence3fDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence3fDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence3dDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence3dDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence3dDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence3dDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence4sDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence4sDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence4sDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence4sDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence4fDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence4fDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence4fDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence4fDesc>::getFieldPtr)
#endif
};

FieldDescription *KeyframeVectorsSequence4dDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeVectorsSequence4dDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeVectorsSequence4dDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeVectorsSequence4dDesc>::getFieldPtr)
#endif
};

OSG_GEO_PROP_TYPE_TMPL_DEF(KeyframeSequenceTmpl, KeyframeSequenceDesc, PtrType)

//Deal with Exporting symbols
OSG_BEGIN_NAMESPACE

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence2sDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence2fDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence2dDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence3sDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence3fDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence3dDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence4sDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence4fDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeVectorsSequence4dDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

OSG_END_NAMESPACE



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
#define OSG_COMPILEKEYFRAMEDISCREETSEQUENCEINST

#include "OSGKeyframeDiscreetSequence.h"

OSG_USING_NAMESPACE

FieldDescription *KeyframeDiscreetSequenceStringDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeDiscreetSequenceStringDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeDiscreetSequenceStringDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeDiscreetSequenceStringDesc>::getFieldPtr)
#endif
};

/*
FieldDescription *KeyframeDiscreetSequenceGLenumDesc::_desc[] =
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(KeyframeSequenceTmpl<
                                KeyframeDiscreetSequenceGLenumDesc>::KeyframePropDataField),
        false,
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        KeyframeSequenceTmpl<KeyframeDiscreetSequenceGLenumDesc>::getFPtrAccessMethod())
#else
        (FieldAccessMethod) &KeyframeSequenceTmpl<
                                KeyframeDiscreetSequenceGLenumDesc>::getFieldPtr)
#endif
};
*/

OSG_GEO_PROP_TYPE_TMPL_DEF(KeyframeSequenceTmpl, KeyframeSequenceDesc, PtrType)

//Deal with Exporting symbols
OSG_BEGIN_NAMESPACE

OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeDiscreetSequenceStringDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);

/*
OSG_KEYFRAMEPROP_DLLEXPORT_DEF (KeyframeSequenceTmpl        , 
                           KeyframeDiscreetSequenceGLenumDesc, 
                           OSG_ANIMATIONLIB_DLLMAPPING);
*/


OSG_END_NAMESPACE



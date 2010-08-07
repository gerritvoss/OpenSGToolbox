/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

//---------------------------------------------------------------------------
 //  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include "OSGKeyframeVectorSequenceTmpl.h"

#include "OSGKeyframeVectorSequenceTmplFuncs.ins"
#include "OSGKeyframeVectorSequenceTmpl.ins"
#include "OSGAnimator.h"
#include "OSGKeyframeInterpolations.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//
// Ideas:
// - Fully specialize the _type object

OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(KeyframeVectorSequenceTmpl, SequenceDesc)

#define EXPORT_SEQUENCE(TMPL_PARAM)                                         \
   OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(KeyframeVectorSequenceTmpl, TMPL_PARAM) \
   OSG_FC_CREATE_SPECIALIZED_TMPL_DEF(KeyframeVectorSequenceTmpl, TMPL_PARAM)   \
   template class OSG_DLL_EXPORT KeyframeVectorSequenceTmpl<TMPL_PARAM>;
   
//Int16
EXPORT_SEQUENCE(KeyframeVectorSequenceVec2sDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec3sDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec4sDescBase)

KeyframeVectorSequenceVec2sDescBase::InterpolationFuncMap KeyframeVectorSequenceVec2sDescBase::_interpolationFuncs = KeyframeVectorSequenceVec2sDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec2sDescBase::ReplaceFuncMap KeyframeVectorSequenceVec2sDescBase::_replacementFuncs = KeyframeVectorSequenceVec2sDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec3sDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3sDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3sDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec3sDescBase::ReplaceFuncMap KeyframeVectorSequenceVec3sDescBase::_replacementFuncs = KeyframeVectorSequenceVec3sDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec4sDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4sDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4sDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4sDescBase::ReplaceFuncMap KeyframeVectorSequenceVec4sDescBase::_replacementFuncs = KeyframeVectorSequenceVec4sDescBase::ReplaceFuncMap();

////Real32
EXPORT_SEQUENCE(KeyframeVectorSequenceVec1fDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec2fDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec3fDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec4fDescBase)

KeyframeVectorSequenceVec1fDescBase::InterpolationFuncMap KeyframeVectorSequenceVec1fDescBase::_interpolationFuncs = KeyframeVectorSequenceVec1fDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec1fDescBase::ReplaceFuncMap KeyframeVectorSequenceVec1fDescBase::_replacementFuncs = KeyframeVectorSequenceVec1fDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec2fDescBase::InterpolationFuncMap KeyframeVectorSequenceVec2fDescBase::_interpolationFuncs = KeyframeVectorSequenceVec2fDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec2fDescBase::ReplaceFuncMap KeyframeVectorSequenceVec2fDescBase::_replacementFuncs = KeyframeVectorSequenceVec2fDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec3fDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3fDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3fDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec3fDescBase::ReplaceFuncMap KeyframeVectorSequenceVec3fDescBase::_replacementFuncs = KeyframeVectorSequenceVec3fDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec4fDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4fDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4fDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4fDescBase::ReplaceFuncMap KeyframeVectorSequenceVec4fDescBase::_replacementFuncs = KeyframeVectorSequenceVec4fDescBase::ReplaceFuncMap();

//Fixed32
EXPORT_SEQUENCE(KeyframeVectorSequenceVec2fxDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec3fxDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec4fxDescBase)

KeyframeVectorSequenceVec2fxDescBase::InterpolationFuncMap KeyframeVectorSequenceVec2fxDescBase::_interpolationFuncs = KeyframeVectorSequenceVec2fxDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec2fxDescBase::ReplaceFuncMap KeyframeVectorSequenceVec2fxDescBase::_replacementFuncs = KeyframeVectorSequenceVec2fxDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec3fxDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3fxDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3fxDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec3fxDescBase::ReplaceFuncMap KeyframeVectorSequenceVec3fxDescBase::_replacementFuncs = KeyframeVectorSequenceVec3fxDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec4fxDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4fxDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4fxDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4fxDescBase::ReplaceFuncMap KeyframeVectorSequenceVec4fxDescBase::_replacementFuncs = KeyframeVectorSequenceVec4fxDescBase::ReplaceFuncMap();

//Real64
EXPORT_SEQUENCE(KeyframeVectorSequenceVec2dDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec3dDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec4dDescBase)

KeyframeVectorSequenceVec2dDescBase::InterpolationFuncMap KeyframeVectorSequenceVec2dDescBase::_interpolationFuncs = KeyframeVectorSequenceVec2dDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec2dDescBase::ReplaceFuncMap KeyframeVectorSequenceVec2dDescBase::_replacementFuncs = KeyframeVectorSequenceVec2dDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec3dDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3dDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3dDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec3dDescBase::ReplaceFuncMap KeyframeVectorSequenceVec3dDescBase::_replacementFuncs = KeyframeVectorSequenceVec3dDescBase::ReplaceFuncMap();

KeyframeVectorSequenceVec4dDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4dDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4dDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4dDescBase::ReplaceFuncMap KeyframeVectorSequenceVec4dDescBase::_replacementFuncs = KeyframeVectorSequenceVec4dDescBase::ReplaceFuncMap();

void KeyframeVectorSequenceVec2sDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec3sDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec4sDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec1fDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec2fDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec3fDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec4fDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec2fxDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec3fxDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec4fxDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec2dDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec3dDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

void KeyframeVectorSequenceVec4dDescBase::initMethod(InitPhase ePhase)
{
    if(ePhase == TypeObject::SystemPost)
    {
        _interpolationFuncs[Animator::STEP_INTERPOLATION]   = stepKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::LINEAR_INTERPOLATION] = lerpKeyframeSequence<StoredType>;
        _interpolationFuncs[Animator::CUBIC_INTERPOLATION]  = splineKeyframeSequence<StoredType>;

        _replacementFuncs[Animator::OVERWRITE]            = overwriteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_ABSOLUTE]    = additiveAbsoluteReplacement<StoredType>;
        _replacementFuncs[Animator::ADDITIVE_SINCE_LAST]  = additiveSinceLastReplacement<StoredType>;
    }
}

OSG_END_NAMESPACE


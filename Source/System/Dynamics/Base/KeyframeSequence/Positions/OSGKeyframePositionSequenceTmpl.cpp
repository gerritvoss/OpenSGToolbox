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

#include "OSGKeyframePositionSequenceTmpl.h"

#include "OSGKeyframePositionSequenceTmplFuncs.ins"
#include "OSGKeyframePositionSequenceTmpl.ins"
#include "OSGAnimator.h"
#include "OSGKeyframeInterpolations.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//
// Ideas:
// - Fully specialize the _type object

OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(KeyframePositionSequenceTmpl, SequenceDesc)

#define EXPORT_SEQUENCE(TMPL_PARAM)                                         \
   OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(KeyframePositionSequenceTmpl, TMPL_PARAM) \
   OSG_FC_CREATE_SPECIALIZED_TMPL_DEF(KeyframePositionSequenceTmpl, TMPL_PARAM)   \
   template class OSG_DLL_EXPORT KeyframePositionSequenceTmpl<TMPL_PARAM>;
   
//Int16
EXPORT_SEQUENCE(KeyframePositionSequencePnt2sDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt3sDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt4sDescBase)

KeyframePositionSequencePnt2sDescBase::InterpolationFuncMap KeyframePositionSequencePnt2sDescBase::_interpolationFuncs = KeyframePositionSequencePnt2sDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt2sDescBase::ReplaceFuncMap KeyframePositionSequencePnt2sDescBase::_replacementFuncs = KeyframePositionSequencePnt2sDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt3sDescBase::InterpolationFuncMap KeyframePositionSequencePnt3sDescBase::_interpolationFuncs = KeyframePositionSequencePnt3sDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt3sDescBase::ReplaceFuncMap KeyframePositionSequencePnt3sDescBase::_replacementFuncs = KeyframePositionSequencePnt3sDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt4sDescBase::InterpolationFuncMap KeyframePositionSequencePnt4sDescBase::_interpolationFuncs = KeyframePositionSequencePnt4sDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt4sDescBase::ReplaceFuncMap KeyframePositionSequencePnt4sDescBase::_replacementFuncs = KeyframePositionSequencePnt4sDescBase::ReplaceFuncMap();

//Real32
EXPORT_SEQUENCE(KeyframePositionSequencePnt2fDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt3fDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt4fDescBase)

KeyframePositionSequencePnt2fDescBase::InterpolationFuncMap KeyframePositionSequencePnt2fDescBase::_interpolationFuncs = KeyframePositionSequencePnt2fDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt2fDescBase::ReplaceFuncMap KeyframePositionSequencePnt2fDescBase::_replacementFuncs = KeyframePositionSequencePnt2fDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt3fDescBase::InterpolationFuncMap KeyframePositionSequencePnt3fDescBase::_interpolationFuncs = KeyframePositionSequencePnt3fDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt3fDescBase::ReplaceFuncMap KeyframePositionSequencePnt3fDescBase::_replacementFuncs = KeyframePositionSequencePnt3fDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt4fDescBase::InterpolationFuncMap KeyframePositionSequencePnt4fDescBase::_interpolationFuncs = KeyframePositionSequencePnt4fDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt4fDescBase::ReplaceFuncMap KeyframePositionSequencePnt4fDescBase::_replacementFuncs = KeyframePositionSequencePnt4fDescBase::ReplaceFuncMap();

//Fixed32
EXPORT_SEQUENCE(KeyframePositionSequencePnt2fxDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt3fxDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt4fxDescBase)

KeyframePositionSequencePnt2fxDescBase::InterpolationFuncMap KeyframePositionSequencePnt2fxDescBase::_interpolationFuncs = KeyframePositionSequencePnt2fxDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt2fxDescBase::ReplaceFuncMap KeyframePositionSequencePnt2fxDescBase::_replacementFuncs = KeyframePositionSequencePnt2fxDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt3fxDescBase::InterpolationFuncMap KeyframePositionSequencePnt3fxDescBase::_interpolationFuncs = KeyframePositionSequencePnt3fxDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt3fxDescBase::ReplaceFuncMap KeyframePositionSequencePnt3fxDescBase::_replacementFuncs = KeyframePositionSequencePnt3fxDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt4fxDescBase::InterpolationFuncMap KeyframePositionSequencePnt4fxDescBase::_interpolationFuncs = KeyframePositionSequencePnt4fxDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt4fxDescBase::ReplaceFuncMap KeyframePositionSequencePnt4fxDescBase::_replacementFuncs = KeyframePositionSequencePnt4fxDescBase::ReplaceFuncMap();

//Real64
EXPORT_SEQUENCE(KeyframePositionSequencePnt2dDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt3dDescBase)
EXPORT_SEQUENCE(KeyframePositionSequencePnt4dDescBase)

KeyframePositionSequencePnt2dDescBase::InterpolationFuncMap KeyframePositionSequencePnt2dDescBase::_interpolationFuncs = KeyframePositionSequencePnt2dDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt2dDescBase::ReplaceFuncMap KeyframePositionSequencePnt2dDescBase::_replacementFuncs = KeyframePositionSequencePnt2dDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt3dDescBase::InterpolationFuncMap KeyframePositionSequencePnt3dDescBase::_interpolationFuncs = KeyframePositionSequencePnt3dDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt3dDescBase::ReplaceFuncMap KeyframePositionSequencePnt3dDescBase::_replacementFuncs = KeyframePositionSequencePnt3dDescBase::ReplaceFuncMap();
KeyframePositionSequencePnt4dDescBase::InterpolationFuncMap KeyframePositionSequencePnt4dDescBase::_interpolationFuncs = KeyframePositionSequencePnt4dDescBase::InterpolationFuncMap();
KeyframePositionSequencePnt4dDescBase::ReplaceFuncMap KeyframePositionSequencePnt4dDescBase::_replacementFuncs = KeyframePositionSequencePnt4dDescBase::ReplaceFuncMap();

void KeyframePositionSequencePnt2sDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt3sDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt4sDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt2fDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt3fDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt4fDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt2fxDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt3fxDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt4fxDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt2dDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt3dDescBase::initMethod(InitPhase ePhase)
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

void KeyframePositionSequencePnt4dDescBase::initMethod(InitPhase ePhase)
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


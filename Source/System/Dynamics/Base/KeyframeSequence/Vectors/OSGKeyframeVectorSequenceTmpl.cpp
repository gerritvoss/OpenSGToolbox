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
KeyframeVectorSequenceVec3sDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3sDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3sDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4sDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4sDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4sDescBase::InterpolationFuncMap();

//Real32
EXPORT_SEQUENCE(KeyframeVectorSequenceVec2fDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec3fDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec4fDescBase)

KeyframeVectorSequenceVec2fDescBase::InterpolationFuncMap KeyframeVectorSequenceVec2fDescBase::_interpolationFuncs = KeyframeVectorSequenceVec2fDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec3fDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3fDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3fDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4fDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4fDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4fDescBase::InterpolationFuncMap();

//Fixed32
EXPORT_SEQUENCE(KeyframeVectorSequenceVec2fxDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec3fxDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec4fxDescBase)

KeyframeVectorSequenceVec2fxDescBase::InterpolationFuncMap KeyframeVectorSequenceVec2fxDescBase::_interpolationFuncs = KeyframeVectorSequenceVec2fxDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec3fxDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3fxDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3fxDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4fxDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4fxDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4fxDescBase::InterpolationFuncMap();

//Real64
EXPORT_SEQUENCE(KeyframeVectorSequenceVec2dDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec3dDescBase)
EXPORT_SEQUENCE(KeyframeVectorSequenceVec4dDescBase)

KeyframeVectorSequenceVec2dDescBase::InterpolationFuncMap KeyframeVectorSequenceVec2dDescBase::_interpolationFuncs = KeyframeVectorSequenceVec2dDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec3dDescBase::InterpolationFuncMap KeyframeVectorSequenceVec3dDescBase::_interpolationFuncs = KeyframeVectorSequenceVec3dDescBase::InterpolationFuncMap();
KeyframeVectorSequenceVec4dDescBase::InterpolationFuncMap KeyframeVectorSequenceVec4dDescBase::_interpolationFuncs = KeyframeVectorSequenceVec4dDescBase::InterpolationFuncMap();

OSG_END_NAMESPACE


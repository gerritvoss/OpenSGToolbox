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

#include "OSGKeyframeColorSequenceTmpl.h"

#include "OSGKeyframeColorSequenceTmplFuncs.ins"
#include "OSGKeyframeColorSequenceTmpl.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//
// Ideas:
// - Fully specialize the _type object

OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(KeyframeColorSequenceTmpl, SequenceDesc)

#define EXPORT_SEQUENCE(TMPL_PARAM)                                         \
   OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(KeyframeColorSequenceTmpl, TMPL_PARAM) \
   OSG_FC_CREATE_SPECIALIZED_TMPL_DEF(KeyframeColorSequenceTmpl, TMPL_PARAM)   \
   template class OSG_DLL_EXPORT KeyframeColorSequenceTmpl<TMPL_PARAM>;
   
//Real32
EXPORT_SEQUENCE(KeyframeColorSequenceColor3fDescBase)
EXPORT_SEQUENCE(KeyframeColorSequenceColor4fDescBase)

KeyframeColorSequenceColor3fDescBase::InterpolationFuncMap KeyframeColorSequenceColor3fDescBase::_interpolationFuncs = KeyframeColorSequenceColor3fDescBase::InterpolationFuncMap();
KeyframeColorSequenceColor4fDescBase::InterpolationFuncMap KeyframeColorSequenceColor4fDescBase::_interpolationFuncs = KeyframeColorSequenceColor4fDescBase::InterpolationFuncMap();

//Fixed32
EXPORT_SEQUENCE(KeyframeColorSequenceColor3fxDescBase)
EXPORT_SEQUENCE(KeyframeColorSequenceColor4fxDescBase)

KeyframeColorSequenceColor3fxDescBase::InterpolationFuncMap KeyframeColorSequenceColor3fxDescBase::_interpolationFuncs = KeyframeColorSequenceColor3fxDescBase::InterpolationFuncMap();
KeyframeColorSequenceColor4fxDescBase::InterpolationFuncMap KeyframeColorSequenceColor4fxDescBase::_interpolationFuncs = KeyframeColorSequenceColor4fxDescBase::InterpolationFuncMap();

//UInt8
EXPORT_SEQUENCE(KeyframeColorSequenceColor3ubDescBase)
EXPORT_SEQUENCE(KeyframeColorSequenceColor4ubDescBase)

KeyframeColorSequenceColor3ubDescBase::InterpolationFuncMap KeyframeColorSequenceColor3ubDescBase::_interpolationFuncs = KeyframeColorSequenceColor3ubDescBase::InterpolationFuncMap();
KeyframeColorSequenceColor4ubDescBase::InterpolationFuncMap KeyframeColorSequenceColor4ubDescBase::_interpolationFuncs = KeyframeColorSequenceColor4ubDescBase::InterpolationFuncMap();

OSG_END_NAMESPACE


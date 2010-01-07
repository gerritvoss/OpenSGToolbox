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

#include "OSGKeyframeBasicSequenceTmpl.h"

#include "OSGKeyframeBasicSequenceTmplFuncs.ins"
#include "OSGKeyframeBasicSequenceTmpl.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//
// Ideas:
// - Fully specialize the _type object

OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(KeyframeBasicSequenceTmpl, SequenceDesc)

#define EXPORT_SEQUENCE(TMPL_PARAM)                                         \
   OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(KeyframeBasicSequenceTmpl, TMPL_PARAM) \
   OSG_FC_CREATE_SPECIALIZED_TMPL_DEF(KeyframeBasicSequenceTmpl, TMPL_PARAM)   \
   template class OSG_DLL_EXPORT KeyframeBasicSequenceTmpl<TMPL_PARAM>;
   
//std::string
EXPORT_SEQUENCE(KeyframeBasicSequenceStringDescBase)

KeyframeBasicSequenceStringDescBase::InterpolationFuncMap KeyframeBasicSequenceStringDescBase::_interpolationFuncs = KeyframeBasicSequenceStringDescBase::InterpolationFuncMap();

//Glenum
EXPORT_SEQUENCE(KeyframeBasicSequenceGLenumDescBase)

KeyframeBasicSequenceGLenumDescBase::InterpolationFuncMap KeyframeBasicSequenceGLenumDescBase::_interpolationFuncs = KeyframeBasicSequenceGLenumDescBase::InterpolationFuncMap();


//BoxVolume
EXPORT_SEQUENCE(KeyframeBasicSequenceBoxVolumeDescBase)

KeyframeBasicSequenceBoxVolumeDescBase::InterpolationFuncMap KeyframeBasicSequenceBoxVolumeDescBase::_interpolationFuncs = KeyframeBasicSequenceBoxVolumeDescBase::InterpolationFuncMap();


OSG_END_NAMESPACE


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

#include "OSGKeyframeRotationSequenceTmpl.h"

#include "OSGKeyframeRotationSequenceTmplFuncs.ins"
#include "OSGKeyframeRotationSequenceTmpl.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//
// Ideas:
// - Fully specialize the _type object

OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(KeyframeRotationSequenceTmpl, SequenceDesc)

#define EXPORT_SEQUENCE(TMPL_PARAM)                                         \
   OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(KeyframeRotationSequenceTmpl, TMPL_PARAM) \
   OSG_FC_CREATE_SPECIALIZED_TMPL_DEF(KeyframeRotationSequenceTmpl, TMPL_PARAM)   \
   template class OSG_DLL_EXPORT KeyframeRotationSequenceTmpl<TMPL_PARAM>;
   
//Real32
EXPORT_SEQUENCE(KeyframeRotationSequenceQuaternionDescBase)

KeyframeRotationSequenceQuaternionDescBase::InterpolationFuncMap KeyframeRotationSequenceQuaternionDescBase::_interpolationFuncs = KeyframeRotationSequenceQuaternionDescBase::InterpolationFuncMap();

//Fixed32
EXPORT_SEQUENCE(KeyframeRotationSequenceQuaternionfxDescBase)

KeyframeRotationSequenceQuaternionfxDescBase::InterpolationFuncMap KeyframeRotationSequenceQuaternionfxDescBase::_interpolationFuncs = KeyframeRotationSequenceQuaternionfxDescBase::InterpolationFuncMap();

//Real64
//EXPORT_SEQUENCE(KeyframeRotationSequenceQuaterniondDescBase)

//KeyframeRotationSequenceQuaterniondDescBase::InterpolationFuncMap KeyframeRotationSequenceQuaterniondDescBase::_interpolationFuncs = KeyframeRotationSequenceQuaterniondDescBase::InterpolationFuncMap();

OSG_END_NAMESPACE


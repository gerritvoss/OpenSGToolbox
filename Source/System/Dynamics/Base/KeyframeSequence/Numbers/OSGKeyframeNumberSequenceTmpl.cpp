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

#include "OSGKeyframeNumberSequenceTmpl.h"

#include "OSGKeyframeNumberSequenceTmplFuncs.ins"
#include "OSGKeyframeNumberSequenceTmpl.ins"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

//
// Ideas:
// - Fully specialize the _type object

OSG_FIELD_CONTAINER_NONINL_TMPL_DEF(KeyframeNumberSequenceTmpl, SequenceDesc)

#define EXPORT_SEQUENCE(TMPL_PARAM)                                         \
   OSG_RC_GET_TYPE_SPECIALIZED_TMPL_DEF(KeyframeNumberSequenceTmpl, TMPL_PARAM) \
   OSG_FC_CREATE_SPECIALIZED_TMPL_DEF(KeyframeNumberSequenceTmpl, TMPL_PARAM)   \
   template class OSG_DLL_EXPORT KeyframeNumberSequenceTmpl<TMPL_PARAM>;
   
//Unsigned Integers
EXPORT_SEQUENCE(KeyframeNumberSequenceUInt8DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceUInt16DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceUInt32DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceUInt64DescBase)

KeyframeNumberSequenceUInt8DescBase::InterpolationFuncMap KeyframeNumberSequenceUInt8DescBase::_interpolationFuncs = KeyframeNumberSequenceUInt8DescBase::InterpolationFuncMap();
KeyframeNumberSequenceUInt16DescBase::InterpolationFuncMap KeyframeNumberSequenceUInt16DescBase::_interpolationFuncs = KeyframeNumberSequenceUInt16DescBase::InterpolationFuncMap();
KeyframeNumberSequenceUInt32DescBase::InterpolationFuncMap KeyframeNumberSequenceUInt32DescBase::_interpolationFuncs = KeyframeNumberSequenceUInt32DescBase::InterpolationFuncMap();
KeyframeNumberSequenceUInt64DescBase::InterpolationFuncMap KeyframeNumberSequenceUInt64DescBase::_interpolationFuncs = KeyframeNumberSequenceUInt64DescBase::InterpolationFuncMap();

//Signed Integers
EXPORT_SEQUENCE(KeyframeNumberSequenceInt8DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceInt16DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceInt32DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceInt64DescBase)

KeyframeNumberSequenceInt8DescBase::InterpolationFuncMap KeyframeNumberSequenceInt8DescBase::_interpolationFuncs = KeyframeNumberSequenceInt8DescBase::InterpolationFuncMap();
KeyframeNumberSequenceInt16DescBase::InterpolationFuncMap KeyframeNumberSequenceInt16DescBase::_interpolationFuncs = KeyframeNumberSequenceInt16DescBase::InterpolationFuncMap();
KeyframeNumberSequenceInt32DescBase::InterpolationFuncMap KeyframeNumberSequenceInt32DescBase::_interpolationFuncs = KeyframeNumberSequenceInt32DescBase::InterpolationFuncMap();
KeyframeNumberSequenceInt64DescBase::InterpolationFuncMap KeyframeNumberSequenceInt64DescBase::_interpolationFuncs = KeyframeNumberSequenceInt64DescBase::InterpolationFuncMap();

//Real Numbers
EXPORT_SEQUENCE(KeyframeNumberSequenceReal16DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceReal32DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceFixed32DescBase)
EXPORT_SEQUENCE(KeyframeNumberSequenceReal64DescBase)

KeyframeNumberSequenceReal16DescBase::InterpolationFuncMap KeyframeNumberSequenceReal16DescBase::_interpolationFuncs = KeyframeNumberSequenceReal16DescBase::InterpolationFuncMap();
KeyframeNumberSequenceReal32DescBase::InterpolationFuncMap KeyframeNumberSequenceReal32DescBase::_interpolationFuncs = KeyframeNumberSequenceReal32DescBase::InterpolationFuncMap();
KeyframeNumberSequenceFixed32DescBase::InterpolationFuncMap KeyframeNumberSequenceFixed32DescBase::_interpolationFuncs = KeyframeNumberSequenceFixed32DescBase::InterpolationFuncMap();
KeyframeNumberSequenceReal64DescBase::InterpolationFuncMap KeyframeNumberSequenceReal64DescBase::_interpolationFuncs = KeyframeNumberSequenceReal64DescBase::InterpolationFuncMap();

OSG_END_NAMESPACE


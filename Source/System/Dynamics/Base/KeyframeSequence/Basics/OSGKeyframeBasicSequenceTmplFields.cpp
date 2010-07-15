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

#include "OSGField.h"

#include "OSGSField.h"
#include "OSGSField.ins"

#include "OSGMField.h"
#include "OSGMField.ins"

#include "OSGKeyframeBasicSequenceTmplFields.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//std::string
OSG_FIELDTRAITS_GETTYPE(KeyframeBasicSequenceString  *)
DataType FieldTraits<KeyframeBasicSequenceString  *>::_type(
    "KeyframeBasicSequenceStringPtr",
    "KeyframeBasicSequencePtr");

//Bool
OSG_FIELDTRAITS_GETTYPE(KeyframeBasicSequenceBool  *)
DataType FieldTraits<KeyframeBasicSequenceBool  *>::_type(
    "KeyframeBasicSequenceBoolPtr",
    "KeyframeBasicSequencePtr");

//GLenum
OSG_FIELDTRAITS_GETTYPE(KeyframeBasicSequenceGLenum  *)
DataType FieldTraits<KeyframeBasicSequenceGLenum  *>::_type(
    "KeyframeBasicSequenceGLenumPtr",
    "KeyframeBasicSequencePtr");

//BoxVolume
OSG_FIELDTRAITS_GETTYPE(KeyframeBasicSequenceBoxVolume  *)
DataType FieldTraits<KeyframeBasicSequenceBoxVolume  *>::_type(
    "KeyframeBasicSequenceBoxVolumePtr",
    "KeyframeBasicSequencePtr");

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//std::string
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeBasicSequenceString *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeBasicSequenceString *, 
                           0);

//Bool
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeBasicSequenceBool *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeBasicSequenceBool *, 
                           0);

//GLenum
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeBasicSequenceGLenum *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeBasicSequenceGLenum *, 
                           0);

//BoxVolume
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeBasicSequenceBoxVolume *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeBasicSequenceBoxVolume *, 
                           0);

OSG_END_NAMESPACE


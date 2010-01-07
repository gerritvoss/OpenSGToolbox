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

#include "OSGKeyframeColorSequenceTmplFields.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//UInt8
OSG_FIELDTRAITS_GETTYPE(KeyframeColorSequenceColor3ub  *)

DataType FieldTraits<KeyframeColorSequenceColor3ub  *>::_type(
    "KeyframeColorSequenceColor3ubPtr",
    "KeyframeColorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeColorSequenceColor4ub  *)
    
DataType FieldTraits<KeyframeColorSequenceColor4ub  *>::_type(
    "KeyframeColorSequenceColor4ubPtr",
    "KeyframeColorSequencePtr");

//Real32
OSG_FIELDTRAITS_GETTYPE(KeyframeColorSequenceColor3f  *)

DataType FieldTraits<KeyframeColorSequenceColor3f  *>::_type(
    "KeyframeColorSequenceColor3fPtr",
    "KeyframeColorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeColorSequenceColor4f  *)
    
DataType FieldTraits<KeyframeColorSequenceColor4f  *>::_type(
    "KeyframeColorSequenceColor4fPtr",
    "KeyframeColorSequencePtr");

//Fixed32
OSG_FIELDTRAITS_GETTYPE(KeyframeColorSequenceColor3fx  *)

DataType FieldTraits<KeyframeColorSequenceColor3fx  *>::_type(
    "KeyframeColorSequenceColor3fxPtr",
    "KeyframeColorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeColorSequenceColor4fx  *)
    
DataType FieldTraits<KeyframeColorSequenceColor4fx  *>::_type(
    "KeyframeColorSequenceColor4fxPtr",
    "KeyframeColorSequencePtr");

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//UInt8
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeColorSequenceColor3ub *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeColorSequenceColor3ub *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeColorSequenceColor4ub *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeColorSequenceColor4ub *, 
                           0);

//Real32
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeColorSequenceColor3f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeColorSequenceColor3f *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeColorSequenceColor4f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeColorSequenceColor4f *, 
                           0);

//Fixed32
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeColorSequenceColor3fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeColorSequenceColor3fx *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeColorSequenceColor4fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeColorSequenceColor4fx *, 
                           0);


OSG_END_NAMESPACE


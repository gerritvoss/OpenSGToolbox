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

#include "OSGKeyframeVectorSequenceTmplFields.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Int16
DataType FieldTraits<KeyframeVectorSequenceVec2s  *>::_type(
    "KeyframeVectorSequenceVec2sPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec3s  *)

DataType FieldTraits<KeyframeVectorSequenceVec3s  *>::_type(
    "KeyframeVectorSequenceVec3sPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec4s  *)
    
DataType FieldTraits<KeyframeVectorSequenceVec4s  *>::_type(
    "KeyframeVectorSequenceVec4sPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec2s  *)

//Real32
OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec1f  *)

DataType FieldTraits<KeyframeVectorSequenceVec1f  *>::_type(
    "KeyframeVectorSequenceVec1fPtr",
    "KeyframeVectorSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec2f  *)

DataType FieldTraits<KeyframeVectorSequenceVec2f  *>::_type(
    "KeyframeVectorSequenceVec2fPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec3f  *)

DataType FieldTraits<KeyframeVectorSequenceVec3f  *>::_type(
    "KeyframeVectorSequenceVec3fPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec4f  *)
    
DataType FieldTraits<KeyframeVectorSequenceVec4f  *>::_type(
    "KeyframeVectorSequenceVec4fPtr",
    "KeyframeVectorSequencePtr");


//Fixed32
DataType FieldTraits<KeyframeVectorSequenceVec2fx  *>::_type(
    "KeyframeVectorSequenceVec2fxPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec3fx  *)

DataType FieldTraits<KeyframeVectorSequenceVec3fx  *>::_type(
    "KeyframeVectorSequenceVec3fxPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec4fx  *)
    
DataType FieldTraits<KeyframeVectorSequenceVec4fx  *>::_type(
    "KeyframeVectorSequenceVec4fxPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec2fx  *)

//Real64
DataType FieldTraits<KeyframeVectorSequenceVec2d  *>::_type(
    "KeyframeVectorSequenceVec2dPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec3d  *)

DataType FieldTraits<KeyframeVectorSequenceVec3d  *>::_type(
    "KeyframeVectorSequenceVec3dPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec4d  *)
    
DataType FieldTraits<KeyframeVectorSequenceVec4d  *>::_type(
    "KeyframeVectorSequenceVec4dPtr",
    "KeyframeVectorSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframeVectorSequenceVec2d  *)
#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Int16
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec2s *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec2s *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec3s *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec3s *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec4s *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec4s *, 
                           0);

//Real32
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec1f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec1f *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec2f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec2f *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec3f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec3f *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec4f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec4f *, 
                           0);

//Fixed32
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec2fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec2fx *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec3fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec3fx *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec4fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec4fx *, 
                           0);

//Real64
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec2d *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec2d *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec3d *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec3d *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeVectorSequenceVec4d *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeVectorSequenceVec4d *, 
                           0);

OSG_END_NAMESPACE


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

#include "OSGKeyframePositionSequenceTmplFields.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Int16
OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt2s  *)

DataType FieldTraits<KeyframePositionSequencePnt2s  *>::_type(
    "KeyframePositionSequencePnt2sPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt3s  *)

DataType FieldTraits<KeyframePositionSequencePnt3s  *>::_type(
    "KeyframePositionSequencePnt3sPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt4s  *)
    
DataType FieldTraits<KeyframePositionSequencePnt4s  *>::_type(
    "KeyframePositionSequencePnt4sPtr",
    "KeyframePositionSequencePtr");


//Real32
OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt2f  *)

DataType FieldTraits<KeyframePositionSequencePnt2f  *>::_type(
    "KeyframePositionSequencePnt2fPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt3f  *)

DataType FieldTraits<KeyframePositionSequencePnt3f  *>::_type(
    "KeyframePositionSequencePnt3fPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt4f  *)
    
DataType FieldTraits<KeyframePositionSequencePnt4f  *>::_type(
    "KeyframePositionSequencePnt4fPtr",
    "KeyframePositionSequencePtr");


//Fixed32
OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt2fx  *)

DataType FieldTraits<KeyframePositionSequencePnt2fx  *>::_type(
    "KeyframePositionSequencePnt2fxPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt3fx  *)

DataType FieldTraits<KeyframePositionSequencePnt3fx  *>::_type(
    "KeyframePositionSequencePnt3fxPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt4fx  *)
    
DataType FieldTraits<KeyframePositionSequencePnt4fx  *>::_type(
    "KeyframePositionSequencePnt4fxPtr",
    "KeyframePositionSequencePtr");


//Real64
OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt2d  *)

DataType FieldTraits<KeyframePositionSequencePnt2d  *>::_type(
    "KeyframePositionSequencePnt2dPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt3d  *)

DataType FieldTraits<KeyframePositionSequencePnt3d  *>::_type(
    "KeyframePositionSequencePnt3dPtr",
    "KeyframePositionSequencePtr");


OSG_FIELDTRAITS_GETTYPE(KeyframePositionSequencePnt4d  *)
    
DataType FieldTraits<KeyframePositionSequencePnt4d  *>::_type(
    "KeyframePositionSequencePnt4dPtr",
    "KeyframePositionSequencePtr");


#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Int16
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt2s *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt2s *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt3s *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt3s *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt4s *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt4s *, 
                           0);

//Real32
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt2f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt2f *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt3f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt3f *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt4f *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt4f *, 
                           0);

//Fixed32
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt2fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt2fx *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt3fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt3fx *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt4fx *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt4fx *, 
                           0);

//Real64
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt2d *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt2d *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt3d *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt3d *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframePositionSequencePnt4d *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframePositionSequencePnt4d *, 
                           0);

OSG_END_NAMESPACE


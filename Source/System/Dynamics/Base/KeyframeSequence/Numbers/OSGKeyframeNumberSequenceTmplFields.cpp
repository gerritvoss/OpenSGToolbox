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

#include "OSGKeyframeNumberSequenceTmplFields.h"

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Unsigned Integers
OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceUInt8  *)
DataType FieldTraits<KeyframeNumberSequenceUInt8  *>::_type(
    "KeyframeNumberSequenceUInt8Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceUInt16  *)
DataType FieldTraits<KeyframeNumberSequenceUInt16  *>::_type(
    "KeyframeNumberSequenceUInt16Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceUInt32  *)
DataType FieldTraits<KeyframeNumberSequenceUInt32  *>::_type(
    "KeyframeNumberSequenceUInt32Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceUInt64  *)
DataType FieldTraits<KeyframeNumberSequenceUInt64  *>::_type(
    "KeyframeNumberSequenceUInt64Ptr",
    "KeyframeNumberSequencePtr");

//Signed Integers
OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceInt8  *)
DataType FieldTraits<KeyframeNumberSequenceInt8  *>::_type(
    "KeyframeNumberSequenceInt8Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceInt16  *)
DataType FieldTraits<KeyframeNumberSequenceInt16  *>::_type(
    "KeyframeNumberSequenceInt16Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceInt32  *)
DataType FieldTraits<KeyframeNumberSequenceInt32  *>::_type(
    "KeyframeNumberSequenceInt32Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceInt64  *)
DataType FieldTraits<KeyframeNumberSequenceInt64  *>::_type(
    "KeyframeNumberSequenceInt64Ptr",
    "KeyframeNumberSequencePtr");

//Real Numbers
OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceReal16  *)
DataType FieldTraits<KeyframeNumberSequenceReal16  *>::_type(
    "KeyframeNumberSequenceReal16Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceReal32  *)
DataType FieldTraits<KeyframeNumberSequenceReal32  *>::_type(
    "KeyframeNumberSequenceReal32Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceFixed32  *)
DataType FieldTraits<KeyframeNumberSequenceFixed32  *>::_type(
    "KeyframeNumberSequenceFixed32Ptr",
    "KeyframeNumberSequencePtr");

OSG_FIELDTRAITS_GETTYPE(KeyframeNumberSequenceReal64  *)
DataType FieldTraits<KeyframeNumberSequenceReal64  *>::_type(
    "KeyframeNumberSequenceReal64Ptr",
    "KeyframeNumberSequencePtr");

#endif //!defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Unsigned Integers
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceUInt8 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceUInt8 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceUInt16 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceUInt16 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceUInt32 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceUInt32 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceUInt64 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceUInt64 *, 
                           0);

//Signed Integers
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceInt8 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceInt8 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceInt16 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceInt16 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceInt32 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceInt32 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceInt64 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceInt64 *, 
                           0);

//Real Numbers
OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceReal16 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceReal16 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceReal32 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceReal32 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceFixed32 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceFixed32 *, 
                           0);

OSG_EXPORT_PTR_SFIELD_FULL(PointerSField, 
                           KeyframeNumberSequenceReal64 *, 
                           0);
OSG_EXPORT_PTR_MFIELD_FULL(PointerMField, 
                           KeyframeNumberSequenceReal64 *, 
                           0);

OSG_END_NAMESPACE


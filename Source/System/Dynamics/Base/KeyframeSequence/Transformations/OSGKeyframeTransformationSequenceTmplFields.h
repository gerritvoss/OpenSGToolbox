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

#ifndef _OSGKEYFRME_TRANSFORMATIONS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_TRANSFORMATIONS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeTransformationSequenceFields.h"
#include "OSGKeyframeTransformationSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//Real32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeTransformationSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeTransformationSequenceMatrix4f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeTransformationSequenceMatrix4f *> : 
    public FieldTraitsFCPtrBase<KeyframeTransformationSequenceMatrix4f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeTransformationSequenceMatrix4f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeTransformationSequenceMatrix4f *, KeyframeTransformationSequenceMatrix4fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeTransformationSequenceMatrix4f *,
                               KeyframeTransformationSequenceMatrix4fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Fixed32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeTransformationSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeTransformationSequenceMatrix4fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeTransformationSequenceMatrix4fx *> : 
    public FieldTraitsFCPtrBase<KeyframeTransformationSequenceMatrix4fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeTransformationSequenceMatrix4fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeTransformationSequenceMatrix4fx *, KeyframeTransformationSequenceMatrix4fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeTransformationSequenceMatrix4fx *,
                               KeyframeTransformationSequenceMatrix4fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real64
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeTransformationSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeTransformationSequenceMatrix4d);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeTransformationSequenceMatrix4d *> : 
    public FieldTraitsFCPtrBase<KeyframeTransformationSequenceMatrix4d *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeTransformationSequenceMatrix4d *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeTransformationSequenceMatrix4d *, KeyframeTransformationSequenceMatrix4dPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeTransformationSequenceMatrix4d *,
                               KeyframeTransformationSequenceMatrix4dPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_TRANSFORMATIONS_SEQUENCE_TMPLFIELDS_H_ */

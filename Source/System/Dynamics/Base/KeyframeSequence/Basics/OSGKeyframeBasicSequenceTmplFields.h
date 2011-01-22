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

#ifndef _OSGKEYFRME_BASICS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_BASICS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeBasicSequenceFields.h"
#include "OSGKeyframeBasicSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//std::string
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeBasicSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeBasicSequenceString);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeBasicSequenceString *> : 
    public FieldTraitsFCPtrBase<KeyframeBasicSequenceString *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeBasicSequenceString *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeBasicSequenceString *, KeyframeBasicSequenceStringPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeBasicSequenceString *,
                               KeyframeBasicSequenceStringPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Bool
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeBasicSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeBasicSequenceBool);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeBasicSequenceBool *> : 
    public FieldTraitsFCPtrBase<KeyframeBasicSequenceBool *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeBasicSequenceBool *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeBasicSequenceBool *, KeyframeBasicSequenceBoolPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeBasicSequenceBool *,
                               KeyframeBasicSequenceBoolPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//GLenum
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeBasicSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeBasicSequenceGLenum);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeBasicSequenceGLenum *> : 
    public FieldTraitsFCPtrBase<KeyframeBasicSequenceGLenum *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeBasicSequenceGLenum *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeBasicSequenceGLenum *, KeyframeBasicSequenceGLenumPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeBasicSequenceGLenum *,
                               KeyframeBasicSequenceGLenumPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//BoxVolume
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeBasicSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeBasicSequenceBoxVolume);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeBasicSequenceBoxVolume *> : 
    public FieldTraitsFCPtrBase<KeyframeBasicSequenceBoxVolume *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeBasicSequenceBoxVolume *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeBasicSequenceBoxVolume *, KeyframeBasicSequenceBoxVolumePtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeBasicSequenceBoxVolume *,
                               KeyframeBasicSequenceBoxVolumePtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_BASICS_SEQUENCE_TMPLFIELDS_H_ */

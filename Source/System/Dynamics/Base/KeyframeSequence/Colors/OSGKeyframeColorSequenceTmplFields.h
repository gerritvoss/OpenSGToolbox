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

#ifndef _OSGKEYFRME_COLORS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_COLORS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeColorSequenceFields.h"
#include "OSGKeyframeColorSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//UInt8

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeColorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor3ub);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeColorSequenceColor3ub *> : 
    public FieldTraitsFCPtrBase<KeyframeColorSequenceColor3ub *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeColorSequenceColor3ub *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeColorSequenceColor3ub *, KeyframeColorSequenceColor3ubPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeColorSequenceColor3ub *,
                               KeyframeColorSequenceColor3ubPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeColorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor4ub);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeColorSequenceColor4ub *> : 
    public FieldTraitsFCPtrBase<KeyframeColorSequenceColor4ub *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeColorSequenceColor4ub *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeColorSequenceColor4ub *, KeyframeColorSequenceColor4ubPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeColorSequenceColor4ub *,
                               KeyframeColorSequenceColor4ubPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real32

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeColorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor3f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeColorSequenceColor3f *> : 
    public FieldTraitsFCPtrBase<KeyframeColorSequenceColor3f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeColorSequenceColor3f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeColorSequenceColor3f *, KeyframeColorSequenceColor3fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeColorSequenceColor3f *,
                               KeyframeColorSequenceColor3fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeColorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor4f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeColorSequenceColor4f *> : 
    public FieldTraitsFCPtrBase<KeyframeColorSequenceColor4f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeColorSequenceColor4f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeColorSequenceColor4f *, KeyframeColorSequenceColor4fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeColorSequenceColor4f *,
                               KeyframeColorSequenceColor4fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Fixed32

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeColorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor3fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeColorSequenceColor3fx *> : 
    public FieldTraitsFCPtrBase<KeyframeColorSequenceColor3fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeColorSequenceColor3fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeColorSequenceColor3fx *, KeyframeColorSequenceColor3fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeColorSequenceColor3fx *,
                               KeyframeColorSequenceColor3fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeColorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeColorSequenceColor4fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeColorSequenceColor4fx *> : 
    public FieldTraitsFCPtrBase<KeyframeColorSequenceColor4fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeColorSequenceColor4fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeColorSequenceColor4fx *, KeyframeColorSequenceColor4fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeColorSequenceColor4fx *,
                               KeyframeColorSequenceColor4fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_COLORS_SEQUENCE_TMPLFIELDS_H_ */

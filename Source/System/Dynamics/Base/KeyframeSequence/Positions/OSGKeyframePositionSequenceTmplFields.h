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

#ifndef _OSGKEYFRME_POSITIONS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_POSITIONS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframePositionSequenceFields.h"
#include "OSGKeyframePositionSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//Int16
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt2s);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt2s *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt2s *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt2s *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt2s *, KeyframePositionSequencePnt2sPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt2s *,
                               KeyframePositionSequencePnt2sPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt3s);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt3s *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt3s *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt3s *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt3s *, KeyframePositionSequencePnt3sPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt3s *,
                               KeyframePositionSequencePnt3sPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt4s);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt4s *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt4s *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt4s *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt4s *, KeyframePositionSequencePnt4sPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt4s *,
                               KeyframePositionSequencePnt4sPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt2f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt2f *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt2f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt2f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt2f *, KeyframePositionSequencePnt2fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt2f *,
                               KeyframePositionSequencePnt2fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt3f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt3f *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt3f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt3f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt3f *, KeyframePositionSequencePnt3fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt3f *,
                               KeyframePositionSequencePnt3fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt4f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt4f *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt4f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt4f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt4f *, KeyframePositionSequencePnt4fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt4f *,
                               KeyframePositionSequencePnt4fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Fixed32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt2fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt2fx *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt2fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt2fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt2fx *, KeyframePositionSequencePnt2fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt2fx *,
                               KeyframePositionSequencePnt2fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt3fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt3fx *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt3fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt3fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt3fx *, KeyframePositionSequencePnt3fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt3fx *,
                               KeyframePositionSequencePnt3fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt4fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt4fx *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt4fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt4fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt4fx *, KeyframePositionSequencePnt4fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt4fx *,
                               KeyframePositionSequencePnt4fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real64
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt2d);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt2d *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt2d *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt2d *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt2d *, KeyframePositionSequencePnt2dPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt2d *,
                               KeyframePositionSequencePnt2dPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt3d);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt3d *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt3d *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt3d *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt3d *, KeyframePositionSequencePnt3dPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt3d *,
                               KeyframePositionSequencePnt3dPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframePositionSequencePtr

OSG_GEN_CONTAINERPTR(KeyframePositionSequencePnt4d);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframePositionSequencePnt4d *> : 
    public FieldTraitsFCPtrBase<KeyframePositionSequencePnt4d *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframePositionSequencePnt4d *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframePositionSequencePnt4d *, KeyframePositionSequencePnt4dPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframePositionSequencePnt4d *,
                               KeyframePositionSequencePnt4dPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_POSITIONS_SEQUENCE_TMPLFIELDS_H_ */

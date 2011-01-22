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

#ifndef _OSGKEYFRME_VECTORS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_VECTORS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeVectorSequenceFields.h"
#include "OSGKeyframeVectorSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//Int16
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2s);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec2s *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec2s *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec2s *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec2s *, KeyframeVectorSequenceVec2sPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec2s *,
                               KeyframeVectorSequenceVec2sPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3s);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec3s *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec3s *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec3s *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec3s *, KeyframeVectorSequenceVec3sPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec3s *,
                               KeyframeVectorSequenceVec3sPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4s);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec4s *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec4s *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec4s *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec4s *, KeyframeVectorSequenceVec4sPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec4s *,
                               KeyframeVectorSequenceVec4sPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec1f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec1f *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec1f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec1f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec1f *, KeyframeVectorSequenceVec1fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec1f *,
                               KeyframeVectorSequenceVec1fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec2f *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec2f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec2f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec2f *, KeyframeVectorSequenceVec2fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec2f *,
                               KeyframeVectorSequenceVec2fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec3f *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec3f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec3f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec3f *, KeyframeVectorSequenceVec3fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec3f *,
                               KeyframeVectorSequenceVec3fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4f);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec4f *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec4f *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec4f *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec4f *, KeyframeVectorSequenceVec4fPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec4f *,
                               KeyframeVectorSequenceVec4fPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Fixed32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec2fx *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec2fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec2fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec2fx *, KeyframeVectorSequenceVec2fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec2fx *,
                               KeyframeVectorSequenceVec2fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec3fx *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec3fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec3fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec3fx *, KeyframeVectorSequenceVec3fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec3fx *,
                               KeyframeVectorSequenceVec3fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4fx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec4fx *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec4fx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec4fx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec4fx *, KeyframeVectorSequenceVec4fxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec4fx *,
                               KeyframeVectorSequenceVec4fxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real64
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec2d);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec2d *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec2d *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec2d *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec2d *, KeyframeVectorSequenceVec2dPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec2d *,
                               KeyframeVectorSequenceVec2dPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec3d);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec3d *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec3d *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec3d *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec3d *, KeyframeVectorSequenceVec3dPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec3d *,
                               KeyframeVectorSequenceVec3dPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeVectorSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeVectorSequenceVec4d);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeVectorSequenceVec4d *> : 
    public FieldTraitsFCPtrBase<KeyframeVectorSequenceVec4d *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeVectorSequenceVec4d *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeVectorSequenceVec4d *, KeyframeVectorSequenceVec4dPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeVectorSequenceVec4d *,
                               KeyframeVectorSequenceVec4dPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_VECTORS_SEQUENCE_TMPLFIELDS_H_ */

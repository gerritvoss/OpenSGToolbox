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

#ifndef _OSGKEYFRME_NUMBERS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_NUMBERS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeNumberSequenceFields.h"
#include "OSGKeyframeNumberSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//Unsigned Integers
//UInt8
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt8);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceUInt8 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceUInt8 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceUInt8 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceUInt8 *, KeyframeNumberSequenceUInt8Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceUInt8 *, KeyframeNumberSequenceUInt8Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//UInt16
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt16);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceUInt16 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceUInt16 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceUInt16 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceUInt16 *, KeyframeNumberSequenceUInt16Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceUInt16 *, KeyframeNumberSequenceUInt16Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//UInt32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt32);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceUInt32 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceUInt32 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceUInt32 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceUInt32 *, KeyframeNumberSequenceUInt32Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceUInt32 *, KeyframeNumberSequenceUInt32Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//UInt64
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceUInt64);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceUInt64 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceUInt64 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceUInt64 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceUInt64 *, KeyframeNumberSequenceUInt64Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceUInt64 *, KeyframeNumberSequenceUInt64Ptr);


#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Signed Integers
//Int8
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt8);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceInt8 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceInt8 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceInt8 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceInt8 *, KeyframeNumberSequenceInt8Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceInt8 *, KeyframeNumberSequenceInt8Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Int16
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt16);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceInt16 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceInt16 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceInt16 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceInt16 *, KeyframeNumberSequenceInt16Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceInt16 *, KeyframeNumberSequenceInt16Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Int32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt32);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceInt32 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceInt32 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceInt32 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceInt32 *, KeyframeNumberSequenceInt32Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceInt32 *, KeyframeNumberSequenceInt32Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Int64
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceInt64);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceInt64 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceInt64 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceInt64 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceInt64 *, KeyframeNumberSequenceInt64Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceInt64 *, KeyframeNumberSequenceInt64Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


//Real Numbers

//Real16
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceReal16);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceReal16 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceReal16 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceReal16 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceReal16 *, KeyframeNumberSequenceReal16Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceReal16 *, KeyframeNumberSequenceReal16Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceReal32);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceReal32 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceReal32 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceReal32 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceReal32 *, KeyframeNumberSequenceReal32Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceReal32 *, KeyframeNumberSequenceReal32Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Fixed32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceFixed32);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceFixed32 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceFixed32 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceFixed32 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceFixed32 *, KeyframeNumberSequenceFixed32Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceFixed32 *, KeyframeNumberSequenceFixed32Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Real64
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeNumberSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeNumberSequenceReal64);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeNumberSequenceReal64 *> : 
    public FieldTraitsFCPtrBase<KeyframeNumberSequenceReal64 *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeNumberSequenceReal64 *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeNumberSequenceReal64 *, KeyframeNumberSequenceReal64Ptr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeNumberSequenceReal64 *, KeyframeNumberSequenceReal64Ptr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_NUMBERS_SEQUENCE_TMPLFIELDS_H_ */

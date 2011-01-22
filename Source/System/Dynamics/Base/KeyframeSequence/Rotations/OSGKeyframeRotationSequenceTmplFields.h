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

#ifndef _OSGKEYFRME_ROTATIONS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_ROTATIONS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeRotationSequenceFields.h"
#include "OSGKeyframeRotationSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//Real32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeRotationSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeRotationSequenceQuaternion);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeRotationSequenceQuaternion *> : 
    public FieldTraitsFCPtrBase<KeyframeRotationSequenceQuaternion *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeRotationSequenceQuaternion *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeRotationSequenceQuaternion *, KeyframeRotationSequenceQuaternionPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeRotationSequenceQuaternion *,
                               KeyframeRotationSequenceQuaternionPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//Fixed32
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeRotationSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeRotationSequenceQuaternionfx);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeRotationSequenceQuaternionfx *> : 
    public FieldTraitsFCPtrBase<KeyframeRotationSequenceQuaternionfx *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeRotationSequenceQuaternionfx *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_TBANIMATION_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeRotationSequenceQuaternionfx *, KeyframeRotationSequenceQuaternionfxPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeRotationSequenceQuaternionfx *,
                               KeyframeRotationSequenceQuaternionfxPtr,
                               GrpAnimationKeyframeSequence,
                               GrpLibOSGTBAnimation);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)



//Real64
//#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
////! KeyframeRotationSequencePtr

//OSG_GEN_CONTAINERPTR(KeyframeRotationSequenceQuaterniond);

//#endif

//#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
//#if !defined(OSG_DOC_DEV_TRAITS)
//[>! \hideinhierarchy <]
//#endif

//template <>
//struct FieldTraits<KeyframeRotationSequenceQuaterniond *> : 
    //public FieldTraitsFCPtrBase<KeyframeRotationSequenceQuaterniond *>
//{
  //private:

    //static DataType             _type;                       

  //public:

    //typedef FieldTraits<KeyframeRotationSequenceQuaterniond *>  Self;

    //enum                        { StringConvertable = 0x00 };

    //static OSG_TBANIMATION_DLLMAPPING 
                     //DataType &getType (void);

    //template<typename RefCountPolicy> inline
    //static const Char8 *getSName(void); 

    //template<typename RefCountPolicy> inline
    //static const Char8 *getMName(void); 
//};


//OSG_FIELD_TRAITS_NAME_INST(KeyframeRotationSequenceQuaterniond *, KeyframeRotationSequenceQuaterniondPtr)

//OSG_FIELDCONTAINER_FIELDS_INST(KeyframeRotationSequenceQuaterniond *,
//KeyframeRotationSequenceQuaterniondPtr,
                               //GrpAnimationKeyframeSequence,
                               //GrpLibOSGTBAnimation);

//#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)




OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_ROTATIONS_SEQUENCE_TMPLFIELDS_H_ */

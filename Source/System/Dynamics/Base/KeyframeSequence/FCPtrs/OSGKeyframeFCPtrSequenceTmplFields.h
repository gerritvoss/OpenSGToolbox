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

#ifndef _OSGKEYFRME_FCPTRS_SEQUENCE_TMPLFIELDS_H_
#define _OSGKEYFRME_FCPTRS_SEQUENCE_TMPLFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGKeyframeFCPtrSequenceFields.h"
#include "OSGKeyframeFCPtrSequenceTmpl.h"

OSG_BEGIN_NAMESPACE

//Image
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeFCPtrSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeFCPtrSequenceImage);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeFCPtrSequenceImage *> : 
    public FieldTraitsFCPtrBase<KeyframeFCPtrSequenceImage *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeFCPtrSequenceImage *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DYNAMICS_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeFCPtrSequenceImage *, KeyframeFCPtrSequenceImagePtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeFCPtrSequenceImage *, KeyframeFCPtrSequenceImagePtr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

//StateChunk
#if !defined(OSG_DO_DOC) // created as a dummy class, remove to prevent doubles
//! KeyframeFCPtrSequencePtr

OSG_GEN_CONTAINERPTR(KeyframeFCPtrSequenceStateChunk);

#endif

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)
/*! \ingroup GrpKeyframeSequences
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraits<KeyframeFCPtrSequenceStateChunk *> : 
    public FieldTraitsFCPtrBase<KeyframeFCPtrSequenceStateChunk *>
{
  private:

    static DataType             _type;                       

  public:

    typedef FieldTraits<KeyframeFCPtrSequenceStateChunk *>  Self;

    enum                        { StringConvertable = 0x00 };

    static OSG_DYNAMICS_DLLMAPPING 
                     DataType &getType (void);

    template<typename RefCountPolicy> inline
    static const Char8 *getSName(void); 

    template<typename RefCountPolicy> inline
    static const Char8 *getMName(void); 
};


OSG_FIELD_TRAITS_NAME_INST(KeyframeFCPtrSequenceStateChunk *, KeyframeFCPtrSequenceStateChunkPtr)

OSG_FIELDCONTAINER_FIELDS_INST(KeyframeFCPtrSequenceStateChunk *, KeyframeFCPtrSequenceStateChunkPtr);

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#endif /* _OSGKEYFRME_FCPTRS_SEQUENCE_TMPLFIELDS_H_ */

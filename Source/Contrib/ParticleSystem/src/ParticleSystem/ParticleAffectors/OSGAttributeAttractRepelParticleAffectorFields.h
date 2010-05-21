/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com), Daniel Guilliams           *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTORFIELDS_H_
#define _OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class AttributeAttractRepelParticleAffector;

OSG_GEN_CONTAINERPTR(AttributeAttractRepelParticleAffector);

/*! \ingroup GrpContribParticleSystemFieldTraits
    \ingroup GrpLibOSGContribParticleSystem
 */
template <>
struct FieldTraits<AttributeAttractRepelParticleAffector *> :
    public FieldTraitsFCPtrBase<AttributeAttractRepelParticleAffector *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<AttributeAttractRepelParticleAffector *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFAttributeAttractRepelParticleAffectorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFAttributeAttractRepelParticleAffectorPtr"; }
};

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecAttributeAttractRepelParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecAttributeAttractRepelParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakAttributeAttractRepelParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdAttributeAttractRepelParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecAttributeAttractRepelParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecAttributeAttractRepelParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakAttributeAttractRepelParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<AttributeAttractRepelParticleAffector *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdAttributeAttractRepelParticleAffectorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<AttributeAttractRepelParticleAffector *,
                      RecordedRefCountPolicy  > SFRecAttributeAttractRepelParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<AttributeAttractRepelParticleAffector *,
                      UnrecordedRefCountPolicy> SFUnrecAttributeAttractRepelParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<AttributeAttractRepelParticleAffector *,
                      WeakRefCountPolicy      > SFWeakAttributeAttractRepelParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<AttributeAttractRepelParticleAffector *,
                      NoRefCountPolicy        > SFUncountedAttributeAttractRepelParticleAffectorPtr;


/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<AttributeAttractRepelParticleAffector *,
                      RecordedRefCountPolicy  > MFRecAttributeAttractRepelParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<AttributeAttractRepelParticleAffector *,
                      UnrecordedRefCountPolicy> MFUnrecAttributeAttractRepelParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<AttributeAttractRepelParticleAffector *,
                      WeakRefCountPolicy      > MFWeakAttributeAttractRepelParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<AttributeAttractRepelParticleAffector *,
                      NoRefCountPolicy        > MFUncountedAttributeAttractRepelParticleAffectorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFRecAttributeAttractRepelParticleAffectorPtr : 
    public PointerSField<AttributeAttractRepelParticleAffector *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUnrecAttributeAttractRepelParticleAffectorPtr : 
    public PointerSField<AttributeAttractRepelParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFWeakAttributeAttractRepelParticleAffectorPtr :
    public PointerSField<AttributeAttractRepelParticleAffector *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUncountedAttributeAttractRepelParticleAffectorPtr :
    public PointerSField<AttributeAttractRepelParticleAffector *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFRecAttributeAttractRepelParticleAffectorPtr :
    public PointerMField<AttributeAttractRepelParticleAffector *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUnrecAttributeAttractRepelParticleAffectorPtr :
    public PointerMField<AttributeAttractRepelParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFWeakAttributeAttractRepelParticleAffectorPtr :
    public PointerMField<AttributeAttractRepelParticleAffector *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUncountedAttributeAttractRepelParticleAffectorPtr :
    public PointerMField<AttributeAttractRepelParticleAffector *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGATTRIBUTEATTRACTREPELPARTICLEAFFECTORFIELDS_H_ */
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


#ifndef _OSGGRAVITYPARTICLEAFFECTORFIELDS_H_
#define _OSGGRAVITYPARTICLEAFFECTORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class GravityParticleAffector;

OSG_GEN_CONTAINERPTR(GravityParticleAffector);

/*! \ingroup GrpContribParticleSystemFieldTraits
    \ingroup GrpLibOSGContribParticleSystem
 */
template <>
struct FieldTraits<GravityParticleAffector *> :
    public FieldTraitsFCPtrBase<GravityParticleAffector *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<GravityParticleAffector *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFGravityParticleAffectorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFGravityParticleAffectorPtr"; }
};

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecGravityParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecGravityParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakGravityParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdGravityParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecGravityParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecGravityParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakGravityParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GravityParticleAffector *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdGravityParticleAffectorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GravityParticleAffector *,
                      RecordedRefCountPolicy  > SFRecGravityParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GravityParticleAffector *,
                      UnrecordedRefCountPolicy> SFUnrecGravityParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GravityParticleAffector *,
                      WeakRefCountPolicy      > SFWeakGravityParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GravityParticleAffector *,
                      NoRefCountPolicy        > SFUncountedGravityParticleAffectorPtr;


/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GravityParticleAffector *,
                      RecordedRefCountPolicy  > MFRecGravityParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GravityParticleAffector *,
                      UnrecordedRefCountPolicy> MFUnrecGravityParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GravityParticleAffector *,
                      WeakRefCountPolicy      > MFWeakGravityParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GravityParticleAffector *,
                      NoRefCountPolicy        > MFUncountedGravityParticleAffectorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFRecGravityParticleAffectorPtr : 
    public PointerSField<GravityParticleAffector *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUnrecGravityParticleAffectorPtr : 
    public PointerSField<GravityParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFWeakGravityParticleAffectorPtr :
    public PointerSField<GravityParticleAffector *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUncountedGravityParticleAffectorPtr :
    public PointerSField<GravityParticleAffector *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFRecGravityParticleAffectorPtr :
    public PointerMField<GravityParticleAffector *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUnrecGravityParticleAffectorPtr :
    public PointerMField<GravityParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFWeakGravityParticleAffectorPtr :
    public PointerMField<GravityParticleAffector *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUncountedGravityParticleAffectorPtr :
    public PointerMField<GravityParticleAffector *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGGRAVITYPARTICLEAFFECTORFIELDS_H_ */
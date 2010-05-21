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


#ifndef _OSGDISTANCEFADEPARTICLEAFFECTORFIELDS_H_
#define _OSGDISTANCEFADEPARTICLEAFFECTORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class DistanceFadeParticleAffector;

OSG_GEN_CONTAINERPTR(DistanceFadeParticleAffector);

/*! \ingroup GrpContribParticleSystemFieldTraits
    \ingroup GrpLibOSGContribParticleSystem
 */
template <>
struct FieldTraits<DistanceFadeParticleAffector *> :
    public FieldTraitsFCPtrBase<DistanceFadeParticleAffector *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<DistanceFadeParticleAffector *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFDistanceFadeParticleAffectorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFDistanceFadeParticleAffectorPtr"; }
};

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecDistanceFadeParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecDistanceFadeParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakDistanceFadeParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdDistanceFadeParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecDistanceFadeParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecDistanceFadeParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakDistanceFadeParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<DistanceFadeParticleAffector *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdDistanceFadeParticleAffectorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<DistanceFadeParticleAffector *,
                      RecordedRefCountPolicy  > SFRecDistanceFadeParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<DistanceFadeParticleAffector *,
                      UnrecordedRefCountPolicy> SFUnrecDistanceFadeParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<DistanceFadeParticleAffector *,
                      WeakRefCountPolicy      > SFWeakDistanceFadeParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<DistanceFadeParticleAffector *,
                      NoRefCountPolicy        > SFUncountedDistanceFadeParticleAffectorPtr;


/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<DistanceFadeParticleAffector *,
                      RecordedRefCountPolicy  > MFRecDistanceFadeParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<DistanceFadeParticleAffector *,
                      UnrecordedRefCountPolicy> MFUnrecDistanceFadeParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<DistanceFadeParticleAffector *,
                      WeakRefCountPolicy      > MFWeakDistanceFadeParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<DistanceFadeParticleAffector *,
                      NoRefCountPolicy        > MFUncountedDistanceFadeParticleAffectorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFRecDistanceFadeParticleAffectorPtr : 
    public PointerSField<DistanceFadeParticleAffector *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUnrecDistanceFadeParticleAffectorPtr : 
    public PointerSField<DistanceFadeParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFWeakDistanceFadeParticleAffectorPtr :
    public PointerSField<DistanceFadeParticleAffector *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUncountedDistanceFadeParticleAffectorPtr :
    public PointerSField<DistanceFadeParticleAffector *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFRecDistanceFadeParticleAffectorPtr :
    public PointerMField<DistanceFadeParticleAffector *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUnrecDistanceFadeParticleAffectorPtr :
    public PointerMField<DistanceFadeParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFWeakDistanceFadeParticleAffectorPtr :
    public PointerMField<DistanceFadeParticleAffector *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUncountedDistanceFadeParticleAffectorPtr :
    public PointerMField<DistanceFadeParticleAffector *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGDISTANCEFADEPARTICLEAFFECTORFIELDS_H_ */
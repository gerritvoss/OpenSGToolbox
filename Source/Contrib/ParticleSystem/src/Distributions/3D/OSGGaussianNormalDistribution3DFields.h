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


#ifndef _OSGGAUSSIANNORMALDISTRIBUTION3DFIELDS_H_
#define _OSGGAUSSIANNORMALDISTRIBUTION3DFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class GaussianNormalDistribution3D;

OSG_GEN_CONTAINERPTR(GaussianNormalDistribution3D);

/*! \ingroup GrpContribParticleSystemFieldTraits
    \ingroup GrpLibOSGContribParticleSystem
 */
template <>
struct FieldTraits<GaussianNormalDistribution3D *> :
    public FieldTraitsFCPtrBase<GaussianNormalDistribution3D *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<GaussianNormalDistribution3D *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFGaussianNormalDistribution3DPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFGaussianNormalDistribution3DPtr"; }
};

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecGaussianNormalDistribution3DPtr"; 
}

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecGaussianNormalDistribution3DPtr"; 
}

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakGaussianNormalDistribution3DPtr"; 
}

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdGaussianNormalDistribution3DPtr"; 
}

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecGaussianNormalDistribution3DPtr"; 
}

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecGaussianNormalDistribution3DPtr"; 
}

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakGaussianNormalDistribution3DPtr"; 
}

template<> inline
const Char8 *FieldTraits<GaussianNormalDistribution3D *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdGaussianNormalDistribution3DPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GaussianNormalDistribution3D *,
                      RecordedRefCountPolicy  > SFRecGaussianNormalDistribution3DPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GaussianNormalDistribution3D *,
                      UnrecordedRefCountPolicy> SFUnrecGaussianNormalDistribution3DPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GaussianNormalDistribution3D *,
                      WeakRefCountPolicy      > SFWeakGaussianNormalDistribution3DPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<GaussianNormalDistribution3D *,
                      NoRefCountPolicy        > SFUncountedGaussianNormalDistribution3DPtr;


/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GaussianNormalDistribution3D *,
                      RecordedRefCountPolicy  > MFRecGaussianNormalDistribution3DPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GaussianNormalDistribution3D *,
                      UnrecordedRefCountPolicy> MFUnrecGaussianNormalDistribution3DPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GaussianNormalDistribution3D *,
                      WeakRefCountPolicy      > MFWeakGaussianNormalDistribution3DPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<GaussianNormalDistribution3D *,
                      NoRefCountPolicy        > MFUncountedGaussianNormalDistribution3DPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFRecGaussianNormalDistribution3DPtr : 
    public PointerSField<GaussianNormalDistribution3D *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUnrecGaussianNormalDistribution3DPtr : 
    public PointerSField<GaussianNormalDistribution3D *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFWeakGaussianNormalDistribution3DPtr :
    public PointerSField<GaussianNormalDistribution3D *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUncountedGaussianNormalDistribution3DPtr :
    public PointerSField<GaussianNormalDistribution3D *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFRecGaussianNormalDistribution3DPtr :
    public PointerMField<GaussianNormalDistribution3D *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUnrecGaussianNormalDistribution3DPtr :
    public PointerMField<GaussianNormalDistribution3D *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFWeakGaussianNormalDistribution3DPtr :
    public PointerMField<GaussianNormalDistribution3D *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUncountedGaussianNormalDistribution3DPtr :
    public PointerMField<GaussianNormalDistribution3D *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGGAUSSIANNORMALDISTRIBUTION3DFIELDS_H_ */
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


#ifndef _OSGVORTEXPARTICLEAFFECTORFIELDS_H_
#define _OSGVORTEXPARTICLEAFFECTORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribParticleSystemDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class VortexParticleAffector;

OSG_GEN_CONTAINERPTR(VortexParticleAffector);

/*! \ingroup GrpContribParticleSystemFieldTraits
    \ingroup GrpLibOSGContribParticleSystem
 */
template <>
struct FieldTraits<VortexParticleAffector *> :
    public FieldTraitsFCPtrBase<VortexParticleAffector *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<VortexParticleAffector *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBPARTICLESYSTEM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFVortexParticleAffectorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFVortexParticleAffectorPtr"; }
};

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecVortexParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecVortexParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakVortexParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdVortexParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecVortexParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecVortexParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakVortexParticleAffectorPtr"; 
}

template<> inline
const Char8 *FieldTraits<VortexParticleAffector *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdVortexParticleAffectorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<VortexParticleAffector *,
                      RecordedRefCountPolicy  > SFRecVortexParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<VortexParticleAffector *,
                      UnrecordedRefCountPolicy> SFUnrecVortexParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<VortexParticleAffector *,
                      WeakRefCountPolicy      > SFWeakVortexParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldSFields */
typedef PointerSField<VortexParticleAffector *,
                      NoRefCountPolicy        > SFUncountedVortexParticleAffectorPtr;


/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<VortexParticleAffector *,
                      RecordedRefCountPolicy  > MFRecVortexParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<VortexParticleAffector *,
                      UnrecordedRefCountPolicy> MFUnrecVortexParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<VortexParticleAffector *,
                      WeakRefCountPolicy      > MFWeakVortexParticleAffectorPtr;
/*! \ingroup GrpContribParticleSystemFieldMFields */
typedef PointerMField<VortexParticleAffector *,
                      NoRefCountPolicy        > MFUncountedVortexParticleAffectorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFRecVortexParticleAffectorPtr : 
    public PointerSField<VortexParticleAffector *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUnrecVortexParticleAffectorPtr : 
    public PointerSField<VortexParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFWeakVortexParticleAffectorPtr :
    public PointerSField<VortexParticleAffector *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldSFields \ingroup GrpLibOSGContribParticleSystem */
struct SFUncountedVortexParticleAffectorPtr :
    public PointerSField<VortexParticleAffector *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFRecVortexParticleAffectorPtr :
    public PointerMField<VortexParticleAffector *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUnrecVortexParticleAffectorPtr :
    public PointerMField<VortexParticleAffector *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFWeakVortexParticleAffectorPtr :
    public PointerMField<VortexParticleAffector *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribParticleSystemFieldMFields \ingroup GrpLibOSGContribParticleSystem */
struct MFUncountedVortexParticleAffectorPtr :
    public PointerMField<VortexParticleAffector *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGVORTEXPARTICLEAFFECTORFIELDS_H_ */

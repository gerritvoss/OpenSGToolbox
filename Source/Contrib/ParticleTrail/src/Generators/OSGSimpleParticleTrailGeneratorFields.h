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


#ifndef _OSGSIMPLEPARTICLETRAILGENERATORFIELDS_H_
#define _OSGSIMPLEPARTICLETRAILGENERATORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribParticleTrailDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class SimpleParticleTrailGenerator;

OSG_GEN_CONTAINERPTR(SimpleParticleTrailGenerator);

/*! \ingroup GrpContribParticleTrailFieldTraits
    \ingroup GrpLibOSGContribParticleTrail
 */
template <>
struct FieldTraits<SimpleParticleTrailGenerator *> :
    public FieldTraitsFCPtrBase<SimpleParticleTrailGenerator *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<SimpleParticleTrailGenerator *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBPARTICLETRAIL_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFSimpleParticleTrailGeneratorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFSimpleParticleTrailGeneratorPtr"; }
};

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecSimpleParticleTrailGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecSimpleParticleTrailGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakSimpleParticleTrailGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdSimpleParticleTrailGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecSimpleParticleTrailGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecSimpleParticleTrailGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakSimpleParticleTrailGeneratorPtr"; 
}

template<> inline
const Char8 *FieldTraits<SimpleParticleTrailGenerator *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdSimpleParticleTrailGeneratorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribParticleTrailFieldSFields */
typedef PointerSField<SimpleParticleTrailGenerator *,
                      RecordedRefCountPolicy  > SFRecSimpleParticleTrailGeneratorPtr;
/*! \ingroup GrpContribParticleTrailFieldSFields */
typedef PointerSField<SimpleParticleTrailGenerator *,
                      UnrecordedRefCountPolicy> SFUnrecSimpleParticleTrailGeneratorPtr;
/*! \ingroup GrpContribParticleTrailFieldSFields */
typedef PointerSField<SimpleParticleTrailGenerator *,
                      WeakRefCountPolicy      > SFWeakSimpleParticleTrailGeneratorPtr;
/*! \ingroup GrpContribParticleTrailFieldSFields */
typedef PointerSField<SimpleParticleTrailGenerator *,
                      NoRefCountPolicy        > SFUncountedSimpleParticleTrailGeneratorPtr;


/*! \ingroup GrpContribParticleTrailFieldMFields */
typedef PointerMField<SimpleParticleTrailGenerator *,
                      RecordedRefCountPolicy  > MFRecSimpleParticleTrailGeneratorPtr;
/*! \ingroup GrpContribParticleTrailFieldMFields */
typedef PointerMField<SimpleParticleTrailGenerator *,
                      UnrecordedRefCountPolicy> MFUnrecSimpleParticleTrailGeneratorPtr;
/*! \ingroup GrpContribParticleTrailFieldMFields */
typedef PointerMField<SimpleParticleTrailGenerator *,
                      WeakRefCountPolicy      > MFWeakSimpleParticleTrailGeneratorPtr;
/*! \ingroup GrpContribParticleTrailFieldMFields */
typedef PointerMField<SimpleParticleTrailGenerator *,
                      NoRefCountPolicy        > MFUncountedSimpleParticleTrailGeneratorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribParticleTrailFieldSFields \ingroup GrpLibOSGContribParticleTrail */
struct SFRecSimpleParticleTrailGeneratorPtr : 
    public PointerSField<SimpleParticleTrailGenerator *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleTrailFieldSFields \ingroup GrpLibOSGContribParticleTrail */
struct SFUnrecSimpleParticleTrailGeneratorPtr : 
    public PointerSField<SimpleParticleTrailGenerator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleTrailFieldSFields \ingroup GrpLibOSGContribParticleTrail */
struct SFWeakSimpleParticleTrailGeneratorPtr :
    public PointerSField<SimpleParticleTrailGenerator *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribParticleTrailFieldSFields \ingroup GrpLibOSGContribParticleTrail */
struct SFUncountedSimpleParticleTrailGeneratorPtr :
    public PointerSField<SimpleParticleTrailGenerator *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribParticleTrailFieldMFields \ingroup GrpLibOSGContribParticleTrail */
struct MFRecSimpleParticleTrailGeneratorPtr :
    public PointerMField<SimpleParticleTrailGenerator *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribParticleTrailFieldMFields \ingroup GrpLibOSGContribParticleTrail */
struct MFUnrecSimpleParticleTrailGeneratorPtr :
    public PointerMField<SimpleParticleTrailGenerator *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribParticleTrailFieldMFields \ingroup GrpLibOSGContribParticleTrail */
struct MFWeakSimpleParticleTrailGeneratorPtr :
    public PointerMField<SimpleParticleTrailGenerator *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribParticleTrailFieldMFields \ingroup GrpLibOSGContribParticleTrail */
struct MFUncountedSimpleParticleTrailGeneratorPtr :
    public PointerMField<SimpleParticleTrailGenerator *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSIMPLEPARTICLETRAILGENERATORFIELDS_H_ */

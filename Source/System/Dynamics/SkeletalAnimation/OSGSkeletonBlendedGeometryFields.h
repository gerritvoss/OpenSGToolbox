/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
 *          David Naylor                                                     *
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


#ifndef _OSGSKELETONBLENDEDGEOMETRYFIELDS_H_
#define _OSGSKELETONBLENDEDGEOMETRYFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGTBAnimationDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class SkeletonBlendedGeometry;

OSG_GEN_CONTAINERPTR(SkeletonBlendedGeometry);

/*! \ingroup GrpTBAnimationFieldTraits
    \ingroup GrpLibOSGTBAnimation
 */
template <>
struct FieldTraits<SkeletonBlendedGeometry *> :
    public FieldTraitsFCPtrBase<SkeletonBlendedGeometry *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<SkeletonBlendedGeometry *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_TBANIMATION_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFSkeletonBlendedGeometryPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFSkeletonBlendedGeometryPtr"; }
};

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecSkeletonBlendedGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecSkeletonBlendedGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakSkeletonBlendedGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdSkeletonBlendedGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecSkeletonBlendedGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecSkeletonBlendedGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakSkeletonBlendedGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<SkeletonBlendedGeometry *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdSkeletonBlendedGeometryPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<SkeletonBlendedGeometry *,
                      RecordedRefCountPolicy  > SFRecSkeletonBlendedGeometryPtr;
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<SkeletonBlendedGeometry *,
                      UnrecordedRefCountPolicy> SFUnrecSkeletonBlendedGeometryPtr;
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<SkeletonBlendedGeometry *,
                      WeakRefCountPolicy      > SFWeakSkeletonBlendedGeometryPtr;
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<SkeletonBlendedGeometry *,
                      NoRefCountPolicy        > SFUncountedSkeletonBlendedGeometryPtr;


/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<SkeletonBlendedGeometry *,
                      RecordedRefCountPolicy  > MFRecSkeletonBlendedGeometryPtr;
/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<SkeletonBlendedGeometry *,
                      UnrecordedRefCountPolicy> MFUnrecSkeletonBlendedGeometryPtr;
/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<SkeletonBlendedGeometry *,
                      WeakRefCountPolicy      > MFWeakSkeletonBlendedGeometryPtr;
/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<SkeletonBlendedGeometry *,
                      NoRefCountPolicy        > MFUncountedSkeletonBlendedGeometryPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFRecSkeletonBlendedGeometryPtr : 
    public PointerSField<SkeletonBlendedGeometry *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFUnrecSkeletonBlendedGeometryPtr : 
    public PointerSField<SkeletonBlendedGeometry *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFWeakSkeletonBlendedGeometryPtr :
    public PointerSField<SkeletonBlendedGeometry *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFUncountedSkeletonBlendedGeometryPtr :
    public PointerSField<SkeletonBlendedGeometry *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFRecSkeletonBlendedGeometryPtr :
    public PointerMField<SkeletonBlendedGeometry *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFUnrecSkeletonBlendedGeometryPtr :
    public PointerMField<SkeletonBlendedGeometry *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFWeakSkeletonBlendedGeometryPtr :
    public PointerMField<SkeletonBlendedGeometry *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFUncountedSkeletonBlendedGeometryPtr :
    public PointerMField<SkeletonBlendedGeometry *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSKELETONBLENDEDGEOMETRYFIELDS_H_ */

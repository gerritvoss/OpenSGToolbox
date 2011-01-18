/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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


#ifndef _OSGMORPHGEOMETRYFIELDS_H_
#define _OSGMORPHGEOMETRYFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGTBAnimationDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class MorphGeometry;

OSG_GEN_CONTAINERPTR(MorphGeometry);

/*! \ingroup GrpTBAnimationFieldTraits
    \ingroup GrpLibOSGTBAnimation
 */
template <>
struct FieldTraits<MorphGeometry *> :
    public FieldTraitsFCPtrBase<MorphGeometry *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<MorphGeometry *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_TBANIMATION_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFMorphGeometryPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFMorphGeometryPtr"; }
};

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecMorphGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecMorphGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakMorphGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdMorphGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecMorphGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecMorphGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakMorphGeometryPtr"; 
}

template<> inline
const Char8 *FieldTraits<MorphGeometry *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdMorphGeometryPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<MorphGeometry *,
                      RecordedRefCountPolicy  > SFRecMorphGeometryPtr;
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<MorphGeometry *,
                      UnrecordedRefCountPolicy> SFUnrecMorphGeometryPtr;
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<MorphGeometry *,
                      WeakRefCountPolicy      > SFWeakMorphGeometryPtr;
/*! \ingroup GrpTBAnimationFieldSFields */
typedef PointerSField<MorphGeometry *,
                      NoRefCountPolicy        > SFUncountedMorphGeometryPtr;


/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<MorphGeometry *,
                      RecordedRefCountPolicy  > MFRecMorphGeometryPtr;
/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<MorphGeometry *,
                      UnrecordedRefCountPolicy> MFUnrecMorphGeometryPtr;
/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<MorphGeometry *,
                      WeakRefCountPolicy      > MFWeakMorphGeometryPtr;
/*! \ingroup GrpTBAnimationFieldMFields */
typedef PointerMField<MorphGeometry *,
                      NoRefCountPolicy        > MFUncountedMorphGeometryPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFRecMorphGeometryPtr : 
    public PointerSField<MorphGeometry *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFUnrecMorphGeometryPtr : 
    public PointerSField<MorphGeometry *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFWeakMorphGeometryPtr :
    public PointerSField<MorphGeometry *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldSFields \ingroup GrpLibOSGTBAnimation */
struct SFUncountedMorphGeometryPtr :
    public PointerSField<MorphGeometry *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFRecMorphGeometryPtr :
    public PointerMField<MorphGeometry *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFUnrecMorphGeometryPtr :
    public PointerMField<MorphGeometry *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFWeakMorphGeometryPtr :
    public PointerMField<MorphGeometry *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpTBAnimationFieldMFields \ingroup GrpLibOSGTBAnimation */
struct MFUncountedMorphGeometryPtr :
    public PointerMField<MorphGeometry *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGMORPHGEOMETRYFIELDS_H_ */

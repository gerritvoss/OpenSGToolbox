/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
 *          David Kabala (djkabala@gmail.com)                                *
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


#ifndef _OSGABSTRACTELEMENTFIELDS_H_
#define _OSGABSTRACTELEMENTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class AbstractElement;

OSG_GEN_CONTAINERPTR(AbstractElement);

/*! \ingroup GrpContribTextDomFieldTraits
    \ingroup GrpLibOSGContribTextDom
 */
template <>
struct FieldTraits<AbstractElement *> :
    public FieldTraitsFCPtrBase<AbstractElement *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<AbstractElement *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTEXTDOM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFAbstractElementPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFAbstractElementPtr"; }
};

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecAbstractElementPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecAbstractElementPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakAbstractElementPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdAbstractElementPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecAbstractElementPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecAbstractElementPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakAbstractElementPtr"; 
}

template<> inline
const Char8 *FieldTraits<AbstractElement *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdAbstractElementPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<AbstractElement *,
                      RecordedRefCountPolicy  > SFRecAbstractElementPtr;
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<AbstractElement *,
                      UnrecordedRefCountPolicy> SFUnrecAbstractElementPtr;
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<AbstractElement *,
                      WeakRefCountPolicy      > SFWeakAbstractElementPtr;
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<AbstractElement *,
                      NoRefCountPolicy        > SFUncountedAbstractElementPtr;


/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<AbstractElement *,
                      RecordedRefCountPolicy  > MFRecAbstractElementPtr;
/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<AbstractElement *,
                      UnrecordedRefCountPolicy> MFUnrecAbstractElementPtr;
/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<AbstractElement *,
                      WeakRefCountPolicy      > MFWeakAbstractElementPtr;
/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<AbstractElement *,
                      NoRefCountPolicy        > MFUncountedAbstractElementPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFRecAbstractElementPtr : 
    public PointerSField<AbstractElement *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFUnrecAbstractElementPtr : 
    public PointerSField<AbstractElement *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFWeakAbstractElementPtr :
    public PointerSField<AbstractElement *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFUncountedAbstractElementPtr :
    public PointerSField<AbstractElement *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFRecAbstractElementPtr :
    public PointerMField<AbstractElement *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFUnrecAbstractElementPtr :
    public PointerMField<AbstractElement *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFWeakAbstractElementPtr :
    public PointerMField<AbstractElement *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFUncountedAbstractElementPtr :
    public PointerMField<AbstractElement *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGABSTRACTELEMENTFIELDS_H_ */

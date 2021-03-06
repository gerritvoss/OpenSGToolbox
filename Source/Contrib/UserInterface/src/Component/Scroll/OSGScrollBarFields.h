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


#ifndef _OSGSCROLLBARFIELDS_H_
#define _OSGSCROLLBARFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class ScrollBar;

OSG_GEN_CONTAINERPTR(ScrollBar);

/*! \ingroup GrpContribUserInterfaceFieldTraits
    \ingroup GrpLibOSGContribUserInterface
 */
template <>
struct FieldTraits<ScrollBar *> :
    public FieldTraitsFCPtrBase<ScrollBar *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ScrollBar *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFScrollBarPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFScrollBarPtr"; }
};

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecScrollBarPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecScrollBarPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakScrollBarPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdScrollBarPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecScrollBarPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecScrollBarPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakScrollBarPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScrollBar *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdScrollBarPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ScrollBar *,
                      RecordedRefCountPolicy  > SFRecScrollBarPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ScrollBar *,
                      UnrecordedRefCountPolicy> SFUnrecScrollBarPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ScrollBar *,
                      WeakRefCountPolicy      > SFWeakScrollBarPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ScrollBar *,
                      NoRefCountPolicy        > SFUncountedScrollBarPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ScrollBar *,
                      RecordedRefCountPolicy  > MFRecScrollBarPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ScrollBar *,
                      UnrecordedRefCountPolicy> MFUnrecScrollBarPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ScrollBar *,
                      WeakRefCountPolicy      > MFWeakScrollBarPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ScrollBar *,
                      NoRefCountPolicy        > MFUncountedScrollBarPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFRecScrollBarPtr : 
    public PointerSField<ScrollBar *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUnrecScrollBarPtr : 
    public PointerSField<ScrollBar *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFWeakScrollBarPtr :
    public PointerSField<ScrollBar *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUncountedScrollBarPtr :
    public PointerSField<ScrollBar *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFRecScrollBarPtr :
    public PointerMField<ScrollBar *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUnrecScrollBarPtr :
    public PointerMField<ScrollBar *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFWeakScrollBarPtr :
    public PointerMField<ScrollBar *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUncountedScrollBarPtr :
    public PointerMField<ScrollBar *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSCROLLBARFIELDS_H_ */

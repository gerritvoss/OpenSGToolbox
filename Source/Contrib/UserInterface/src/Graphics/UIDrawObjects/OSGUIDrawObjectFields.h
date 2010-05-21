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


#ifndef _OSGUIDRAWOBJECTFIELDS_H_
#define _OSGUIDRAWOBJECTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class UIDrawObject;

OSG_GEN_CONTAINERPTR(UIDrawObject);

/*! \ingroup GrpContribUserInterfaceFieldTraits
    \ingroup GrpLibOSGContribUserInterface
 */
template <>
struct FieldTraits<UIDrawObject *> :
    public FieldTraitsFCPtrBase<UIDrawObject *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<UIDrawObject *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFUIDrawObjectPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFUIDrawObjectPtr"; }
};

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecUIDrawObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecUIDrawObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakUIDrawObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdUIDrawObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecUIDrawObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecUIDrawObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakUIDrawObjectPtr"; 
}

template<> inline
const Char8 *FieldTraits<UIDrawObject *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdUIDrawObjectPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<UIDrawObject *,
                      RecordedRefCountPolicy  > SFRecUIDrawObjectPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<UIDrawObject *,
                      UnrecordedRefCountPolicy> SFUnrecUIDrawObjectPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<UIDrawObject *,
                      WeakRefCountPolicy      > SFWeakUIDrawObjectPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<UIDrawObject *,
                      NoRefCountPolicy        > SFUncountedUIDrawObjectPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<UIDrawObject *,
                      RecordedRefCountPolicy  > MFRecUIDrawObjectPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<UIDrawObject *,
                      UnrecordedRefCountPolicy> MFUnrecUIDrawObjectPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<UIDrawObject *,
                      WeakRefCountPolicy      > MFWeakUIDrawObjectPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<UIDrawObject *,
                      NoRefCountPolicy        > MFUncountedUIDrawObjectPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFRecUIDrawObjectPtr : 
    public PointerSField<UIDrawObject *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUnrecUIDrawObjectPtr : 
    public PointerSField<UIDrawObject *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFWeakUIDrawObjectPtr :
    public PointerSField<UIDrawObject *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUncountedUIDrawObjectPtr :
    public PointerSField<UIDrawObject *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFRecUIDrawObjectPtr :
    public PointerMField<UIDrawObject *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUnrecUIDrawObjectPtr :
    public PointerMField<UIDrawObject *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFWeakUIDrawObjectPtr :
    public PointerMField<UIDrawObject *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUncountedUIDrawObjectPtr :
    public PointerMField<UIDrawObject *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGUIDRAWOBJECTFIELDS_H_ */
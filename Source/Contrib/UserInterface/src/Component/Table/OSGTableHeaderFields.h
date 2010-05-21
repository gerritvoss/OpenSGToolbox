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


#ifndef _OSGTABLEHEADERFIELDS_H_
#define _OSGTABLEHEADERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class TableHeader;

OSG_GEN_CONTAINERPTR(TableHeader);

/*! \ingroup GrpContribUserInterfaceFieldTraits
    \ingroup GrpLibOSGContribUserInterface
 */
template <>
struct FieldTraits<TableHeader *> :
    public FieldTraitsFCPtrBase<TableHeader *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<TableHeader *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFTableHeaderPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFTableHeaderPtr"; }
};

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecTableHeaderPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecTableHeaderPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakTableHeaderPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdTableHeaderPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecTableHeaderPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecTableHeaderPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakTableHeaderPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableHeader *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdTableHeaderPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableHeader *,
                      RecordedRefCountPolicy  > SFRecTableHeaderPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableHeader *,
                      UnrecordedRefCountPolicy> SFUnrecTableHeaderPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableHeader *,
                      WeakRefCountPolicy      > SFWeakTableHeaderPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableHeader *,
                      NoRefCountPolicy        > SFUncountedTableHeaderPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableHeader *,
                      RecordedRefCountPolicy  > MFRecTableHeaderPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableHeader *,
                      UnrecordedRefCountPolicy> MFUnrecTableHeaderPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableHeader *,
                      WeakRefCountPolicy      > MFWeakTableHeaderPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableHeader *,
                      NoRefCountPolicy        > MFUncountedTableHeaderPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFRecTableHeaderPtr : 
    public PointerSField<TableHeader *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUnrecTableHeaderPtr : 
    public PointerSField<TableHeader *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFWeakTableHeaderPtr :
    public PointerSField<TableHeader *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUncountedTableHeaderPtr :
    public PointerSField<TableHeader *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFRecTableHeaderPtr :
    public PointerMField<TableHeader *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUnrecTableHeaderPtr :
    public PointerMField<TableHeader *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFWeakTableHeaderPtr :
    public PointerMField<TableHeader *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUncountedTableHeaderPtr :
    public PointerMField<TableHeader *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGTABLEHEADERFIELDS_H_ */
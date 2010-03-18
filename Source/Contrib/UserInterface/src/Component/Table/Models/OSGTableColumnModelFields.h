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


#ifndef _OSGTABLECOLUMNMODELFIELDS_H_
#define _OSGTABLECOLUMNMODELFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class TableColumnModel;

OSG_GEN_CONTAINERPTR(TableColumnModel);

/*! \ingroup GrpContribUserInterfaceFieldTraits
    \ingroup GrpLibOSGContribUserInterface
 */
template <>
struct FieldTraits<TableColumnModel *> :
    public FieldTraitsFCPtrBase<TableColumnModel *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<TableColumnModel *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFTableColumnModelPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFTableColumnModelPtr"; }
};

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecTableColumnModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecTableColumnModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakTableColumnModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdTableColumnModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecTableColumnModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecTableColumnModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakTableColumnModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<TableColumnModel *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdTableColumnModelPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableColumnModel *,
                      RecordedRefCountPolicy  > SFRecTableColumnModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableColumnModel *,
                      UnrecordedRefCountPolicy> SFUnrecTableColumnModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableColumnModel *,
                      WeakRefCountPolicy      > SFWeakTableColumnModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<TableColumnModel *,
                      NoRefCountPolicy        > SFUncountedTableColumnModelPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableColumnModel *,
                      RecordedRefCountPolicy  > MFRecTableColumnModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableColumnModel *,
                      UnrecordedRefCountPolicy> MFUnrecTableColumnModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableColumnModel *,
                      WeakRefCountPolicy      > MFWeakTableColumnModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<TableColumnModel *,
                      NoRefCountPolicy        > MFUncountedTableColumnModelPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFRecTableColumnModelPtr : 
    public PointerSField<TableColumnModel *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUnrecTableColumnModelPtr : 
    public PointerSField<TableColumnModel *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFWeakTableColumnModelPtr :
    public PointerSField<TableColumnModel *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUncountedTableColumnModelPtr :
    public PointerSField<TableColumnModel *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFRecTableColumnModelPtr :
    public PointerMField<TableColumnModel *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUnrecTableColumnModelPtr :
    public PointerMField<TableColumnModel *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFWeakTableColumnModelPtr :
    public PointerMField<TableColumnModel *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUncountedTableColumnModelPtr :
    public PointerMField<TableColumnModel *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGTABLECOLUMNMODELFIELDS_H_ */

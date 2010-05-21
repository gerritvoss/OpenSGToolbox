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


#ifndef _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODELFIELDS_H_
#define _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODELFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class DerivedFieldContainerComboBoxModel;

OSG_GEN_CONTAINERPTR(DerivedFieldContainerComboBoxModel);

/*! \ingroup GrpContribUserInterfaceFieldTraits
    \ingroup GrpLibOSGContribUserInterface
 */
template <>
struct FieldTraits<DerivedFieldContainerComboBoxModel *> :
    public FieldTraitsFCPtrBase<DerivedFieldContainerComboBoxModel *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<DerivedFieldContainerComboBoxModel *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFDerivedFieldContainerComboBoxModelPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFDerivedFieldContainerComboBoxModelPtr"; }
};

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecDerivedFieldContainerComboBoxModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecDerivedFieldContainerComboBoxModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakDerivedFieldContainerComboBoxModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdDerivedFieldContainerComboBoxModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecDerivedFieldContainerComboBoxModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecDerivedFieldContainerComboBoxModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakDerivedFieldContainerComboBoxModelPtr"; 
}

template<> inline
const Char8 *FieldTraits<DerivedFieldContainerComboBoxModel *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdDerivedFieldContainerComboBoxModelPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<DerivedFieldContainerComboBoxModel *,
                      RecordedRefCountPolicy  > SFRecDerivedFieldContainerComboBoxModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<DerivedFieldContainerComboBoxModel *,
                      UnrecordedRefCountPolicy> SFUnrecDerivedFieldContainerComboBoxModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<DerivedFieldContainerComboBoxModel *,
                      WeakRefCountPolicy      > SFWeakDerivedFieldContainerComboBoxModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<DerivedFieldContainerComboBoxModel *,
                      NoRefCountPolicy        > SFUncountedDerivedFieldContainerComboBoxModelPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<DerivedFieldContainerComboBoxModel *,
                      RecordedRefCountPolicy  > MFRecDerivedFieldContainerComboBoxModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<DerivedFieldContainerComboBoxModel *,
                      UnrecordedRefCountPolicy> MFUnrecDerivedFieldContainerComboBoxModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<DerivedFieldContainerComboBoxModel *,
                      WeakRefCountPolicy      > MFWeakDerivedFieldContainerComboBoxModelPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<DerivedFieldContainerComboBoxModel *,
                      NoRefCountPolicy        > MFUncountedDerivedFieldContainerComboBoxModelPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFRecDerivedFieldContainerComboBoxModelPtr : 
    public PointerSField<DerivedFieldContainerComboBoxModel *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUnrecDerivedFieldContainerComboBoxModelPtr : 
    public PointerSField<DerivedFieldContainerComboBoxModel *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFWeakDerivedFieldContainerComboBoxModelPtr :
    public PointerSField<DerivedFieldContainerComboBoxModel *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUncountedDerivedFieldContainerComboBoxModelPtr :
    public PointerSField<DerivedFieldContainerComboBoxModel *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFRecDerivedFieldContainerComboBoxModelPtr :
    public PointerMField<DerivedFieldContainerComboBoxModel *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUnrecDerivedFieldContainerComboBoxModelPtr :
    public PointerMField<DerivedFieldContainerComboBoxModel *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFWeakDerivedFieldContainerComboBoxModelPtr :
    public PointerMField<DerivedFieldContainerComboBoxModel *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUncountedDerivedFieldContainerComboBoxModelPtr :
    public PointerMField<DerivedFieldContainerComboBoxModel *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGDERIVEDFIELDCONTAINERCOMBOBOXMODELFIELDS_H_ */
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


#ifndef _OSGGENERICMULTIFIELDEDITORFIELDS_H_
#define _OSGGENERICMULTIFIELDEDITORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class GenericMultiFieldEditor;

OSG_GEN_CONTAINERPTR(GenericMultiFieldEditor);

/*! \ingroup GrpContribFieldContainerEditorFieldTraits
    \ingroup GrpLibOSGContribFieldContainerEditor
 */
template <>
struct FieldTraits<GenericMultiFieldEditor *> :
    public FieldTraitsFCPtrBase<GenericMultiFieldEditor *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<GenericMultiFieldEditor *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFGenericMultiFieldEditorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFGenericMultiFieldEditorPtr"; }
};

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecGenericMultiFieldEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecGenericMultiFieldEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakGenericMultiFieldEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdGenericMultiFieldEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecGenericMultiFieldEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecGenericMultiFieldEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakGenericMultiFieldEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<GenericMultiFieldEditor *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdGenericMultiFieldEditorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<GenericMultiFieldEditor *,
                      RecordedRefCountPolicy  > SFRecGenericMultiFieldEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<GenericMultiFieldEditor *,
                      UnrecordedRefCountPolicy> SFUnrecGenericMultiFieldEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<GenericMultiFieldEditor *,
                      WeakRefCountPolicy      > SFWeakGenericMultiFieldEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<GenericMultiFieldEditor *,
                      NoRefCountPolicy        > SFUncountedGenericMultiFieldEditorPtr;


/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<GenericMultiFieldEditor *,
                      RecordedRefCountPolicy  > MFRecGenericMultiFieldEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<GenericMultiFieldEditor *,
                      UnrecordedRefCountPolicy> MFUnrecGenericMultiFieldEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<GenericMultiFieldEditor *,
                      WeakRefCountPolicy      > MFWeakGenericMultiFieldEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<GenericMultiFieldEditor *,
                      NoRefCountPolicy        > MFUncountedGenericMultiFieldEditorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFRecGenericMultiFieldEditorPtr : 
    public PointerSField<GenericMultiFieldEditor *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUnrecGenericMultiFieldEditorPtr : 
    public PointerSField<GenericMultiFieldEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFWeakGenericMultiFieldEditorPtr :
    public PointerSField<GenericMultiFieldEditor *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUncountedGenericMultiFieldEditorPtr :
    public PointerSField<GenericMultiFieldEditor *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFRecGenericMultiFieldEditorPtr :
    public PointerMField<GenericMultiFieldEditor *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUnrecGenericMultiFieldEditorPtr :
    public PointerMField<GenericMultiFieldEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFWeakGenericMultiFieldEditorPtr :
    public PointerMField<GenericMultiFieldEditor *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUncountedGenericMultiFieldEditorPtr :
    public PointerMField<GenericMultiFieldEditor *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGGENERICMULTIFIELDEDITORFIELDS_H_ */

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


#ifndef _OSGFOREGROUNDFIELDCONTAINEREDITORFIELDS_H_
#define _OSGFOREGROUNDFIELDCONTAINEREDITORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class ForegroundFieldContainerEditor;

OSG_GEN_CONTAINERPTR(ForegroundFieldContainerEditor);

/*! \ingroup GrpContribFieldContainerEditorFieldTraits
    \ingroup GrpLibOSGContribFieldContainerEditor
 */
template <>
struct FieldTraits<ForegroundFieldContainerEditor *> :
    public FieldTraitsFCPtrBase<ForegroundFieldContainerEditor *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ForegroundFieldContainerEditor *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFForegroundFieldContainerEditorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFForegroundFieldContainerEditorPtr"; }
};

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecForegroundFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecForegroundFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakForegroundFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdForegroundFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecForegroundFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecForegroundFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakForegroundFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ForegroundFieldContainerEditor *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdForegroundFieldContainerEditorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ForegroundFieldContainerEditor *,
                      RecordedRefCountPolicy  > SFRecForegroundFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ForegroundFieldContainerEditor *,
                      UnrecordedRefCountPolicy> SFUnrecForegroundFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ForegroundFieldContainerEditor *,
                      WeakRefCountPolicy      > SFWeakForegroundFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ForegroundFieldContainerEditor *,
                      NoRefCountPolicy        > SFUncountedForegroundFieldContainerEditorPtr;


/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ForegroundFieldContainerEditor *,
                      RecordedRefCountPolicy  > MFRecForegroundFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ForegroundFieldContainerEditor *,
                      UnrecordedRefCountPolicy> MFUnrecForegroundFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ForegroundFieldContainerEditor *,
                      WeakRefCountPolicy      > MFWeakForegroundFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ForegroundFieldContainerEditor *,
                      NoRefCountPolicy        > MFUncountedForegroundFieldContainerEditorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFRecForegroundFieldContainerEditorPtr : 
    public PointerSField<ForegroundFieldContainerEditor *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUnrecForegroundFieldContainerEditorPtr : 
    public PointerSField<ForegroundFieldContainerEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFWeakForegroundFieldContainerEditorPtr :
    public PointerSField<ForegroundFieldContainerEditor *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUncountedForegroundFieldContainerEditorPtr :
    public PointerSField<ForegroundFieldContainerEditor *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFRecForegroundFieldContainerEditorPtr :
    public PointerMField<ForegroundFieldContainerEditor *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUnrecForegroundFieldContainerEditorPtr :
    public PointerMField<ForegroundFieldContainerEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFWeakForegroundFieldContainerEditorPtr :
    public PointerMField<ForegroundFieldContainerEditor *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUncountedForegroundFieldContainerEditorPtr :
    public PointerMField<ForegroundFieldContainerEditor *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGFOREGROUNDFIELDCONTAINEREDITORFIELDS_H_ */

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


#ifndef _OSGSCENEPREVIEWFIELDCONTAINEREDITORFIELDS_H_
#define _OSGSCENEPREVIEWFIELDCONTAINEREDITORFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class ScenePreviewFieldContainerEditor;

OSG_GEN_CONTAINERPTR(ScenePreviewFieldContainerEditor);

/*! \ingroup GrpContribFieldContainerEditorFieldTraits
    \ingroup GrpLibOSGContribFieldContainerEditor
 */
template <>
struct FieldTraits<ScenePreviewFieldContainerEditor *> :
    public FieldTraitsFCPtrBase<ScenePreviewFieldContainerEditor *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ScenePreviewFieldContainerEditor *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFScenePreviewFieldContainerEditorPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFScenePreviewFieldContainerEditorPtr"; }
};

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecScenePreviewFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecScenePreviewFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakScenePreviewFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdScenePreviewFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecScenePreviewFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecScenePreviewFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakScenePreviewFieldContainerEditorPtr"; 
}

template<> inline
const Char8 *FieldTraits<ScenePreviewFieldContainerEditor *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdScenePreviewFieldContainerEditorPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ScenePreviewFieldContainerEditor *,
                      RecordedRefCountPolicy  > SFRecScenePreviewFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ScenePreviewFieldContainerEditor *,
                      UnrecordedRefCountPolicy> SFUnrecScenePreviewFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ScenePreviewFieldContainerEditor *,
                      WeakRefCountPolicy      > SFWeakScenePreviewFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<ScenePreviewFieldContainerEditor *,
                      NoRefCountPolicy        > SFUncountedScenePreviewFieldContainerEditorPtr;


/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ScenePreviewFieldContainerEditor *,
                      RecordedRefCountPolicy  > MFRecScenePreviewFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ScenePreviewFieldContainerEditor *,
                      UnrecordedRefCountPolicy> MFUnrecScenePreviewFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ScenePreviewFieldContainerEditor *,
                      WeakRefCountPolicy      > MFWeakScenePreviewFieldContainerEditorPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<ScenePreviewFieldContainerEditor *,
                      NoRefCountPolicy        > MFUncountedScenePreviewFieldContainerEditorPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFRecScenePreviewFieldContainerEditorPtr : 
    public PointerSField<ScenePreviewFieldContainerEditor *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUnrecScenePreviewFieldContainerEditorPtr : 
    public PointerSField<ScenePreviewFieldContainerEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFWeakScenePreviewFieldContainerEditorPtr :
    public PointerSField<ScenePreviewFieldContainerEditor *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUncountedScenePreviewFieldContainerEditorPtr :
    public PointerSField<ScenePreviewFieldContainerEditor *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFRecScenePreviewFieldContainerEditorPtr :
    public PointerMField<ScenePreviewFieldContainerEditor *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUnrecScenePreviewFieldContainerEditorPtr :
    public PointerMField<ScenePreviewFieldContainerEditor *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFWeakScenePreviewFieldContainerEditorPtr :
    public PointerMField<ScenePreviewFieldContainerEditor *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUncountedScenePreviewFieldContainerEditorPtr :
    public PointerMField<ScenePreviewFieldContainerEditor *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSCENEPREVIEWFIELDCONTAINEREDITORFIELDS_H_ */

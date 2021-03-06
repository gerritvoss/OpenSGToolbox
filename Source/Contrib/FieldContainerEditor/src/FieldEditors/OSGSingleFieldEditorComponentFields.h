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


#ifndef _OSGSINGLEFIELDEDITORCOMPONENTFIELDS_H_
#define _OSGSINGLEFIELDEDITORCOMPONENTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class SingleFieldEditorComponent;

OSG_GEN_CONTAINERPTR(SingleFieldEditorComponent);

/*! \ingroup GrpContribFieldContainerEditorFieldTraits
    \ingroup GrpLibOSGContribFieldContainerEditor
 */
template <>
struct FieldTraits<SingleFieldEditorComponent *> :
    public FieldTraitsFCPtrBase<SingleFieldEditorComponent *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<SingleFieldEditorComponent *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFSingleFieldEditorComponentPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFSingleFieldEditorComponentPtr"; }
};

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecSingleFieldEditorComponentPtr"; 
}

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecSingleFieldEditorComponentPtr"; 
}

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakSingleFieldEditorComponentPtr"; 
}

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdSingleFieldEditorComponentPtr"; 
}

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecSingleFieldEditorComponentPtr"; 
}

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecSingleFieldEditorComponentPtr"; 
}

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakSingleFieldEditorComponentPtr"; 
}

template<> inline
const Char8 *FieldTraits<SingleFieldEditorComponent *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdSingleFieldEditorComponentPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<SingleFieldEditorComponent *,
                      RecordedRefCountPolicy  > SFRecSingleFieldEditorComponentPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<SingleFieldEditorComponent *,
                      UnrecordedRefCountPolicy> SFUnrecSingleFieldEditorComponentPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<SingleFieldEditorComponent *,
                      WeakRefCountPolicy      > SFWeakSingleFieldEditorComponentPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldSFields */
typedef PointerSField<SingleFieldEditorComponent *,
                      NoRefCountPolicy        > SFUncountedSingleFieldEditorComponentPtr;


/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<SingleFieldEditorComponent *,
                      RecordedRefCountPolicy  > MFRecSingleFieldEditorComponentPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<SingleFieldEditorComponent *,
                      UnrecordedRefCountPolicy> MFUnrecSingleFieldEditorComponentPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<SingleFieldEditorComponent *,
                      WeakRefCountPolicy      > MFWeakSingleFieldEditorComponentPtr;
/*! \ingroup GrpContribFieldContainerEditorFieldMFields */
typedef PointerMField<SingleFieldEditorComponent *,
                      NoRefCountPolicy        > MFUncountedSingleFieldEditorComponentPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFRecSingleFieldEditorComponentPtr : 
    public PointerSField<SingleFieldEditorComponent *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUnrecSingleFieldEditorComponentPtr : 
    public PointerSField<SingleFieldEditorComponent *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFWeakSingleFieldEditorComponentPtr :
    public PointerSField<SingleFieldEditorComponent *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldSFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct SFUncountedSingleFieldEditorComponentPtr :
    public PointerSField<SingleFieldEditorComponent *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFRecSingleFieldEditorComponentPtr :
    public PointerMField<SingleFieldEditorComponent *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUnrecSingleFieldEditorComponentPtr :
    public PointerMField<SingleFieldEditorComponent *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFWeakSingleFieldEditorComponentPtr :
    public PointerMField<SingleFieldEditorComponent *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribFieldContainerEditorFieldMFields \ingroup GrpLibOSGContribFieldContainerEditor */
struct MFUncountedSingleFieldEditorComponentPtr :
    public PointerMField<SingleFieldEditorComponent *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGSINGLEFIELDEDITORCOMPONENTFIELDS_H_ */

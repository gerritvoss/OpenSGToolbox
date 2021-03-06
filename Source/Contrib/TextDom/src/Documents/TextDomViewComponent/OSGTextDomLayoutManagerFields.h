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


#ifndef _OSGTEXTDOMLAYOUTMANAGERFIELDS_H_
#define _OSGTEXTDOMLAYOUTMANAGERFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class TextDomLayoutManager;

OSG_GEN_CONTAINERPTR(TextDomLayoutManager);

/*! \ingroup GrpContribTextDomFieldTraits
    \ingroup GrpLibOSGContribTextDom
 */
template <>
struct FieldTraits<TextDomLayoutManager *> :
    public FieldTraitsFCPtrBase<TextDomLayoutManager *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<TextDomLayoutManager *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTEXTDOM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFTextDomLayoutManagerPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFTextDomLayoutManagerPtr"; }
};

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdTextDomLayoutManagerPtr"; 
}


/*! \ingroup GrpContribTextDomFieldTraits
 */
template <>
struct FieldTraits<TextDomLayoutManager *, 1> :
    public FieldTraitsFCPtrBase<TextDomLayoutManager *, 1>
{
  private:

  public:
    typedef FieldTraits<TextDomLayoutManager *, 1>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBTEXTDOM_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);
};

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecChildTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecChildTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakChildTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdChildTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecChildTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecChildTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakChildTextDomLayoutManagerPtr"; 
}

template<> inline
const Char8 *FieldTraits<TextDomLayoutManager *, 1>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdChildTextDomLayoutManagerPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<TextDomLayoutManager *,
                      RecordedRefCountPolicy  > SFRecTextDomLayoutManagerPtr;
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<TextDomLayoutManager *,
                      UnrecordedRefCountPolicy> SFUnrecTextDomLayoutManagerPtr;
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<TextDomLayoutManager *,
                      WeakRefCountPolicy      > SFWeakTextDomLayoutManagerPtr;
/*! \ingroup GrpContribTextDomFieldSFields */
typedef PointerSField<TextDomLayoutManager *,
                      NoRefCountPolicy        > SFUncountedTextDomLayoutManagerPtr;


/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<TextDomLayoutManager *,
                      RecordedRefCountPolicy  > MFRecTextDomLayoutManagerPtr;
/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<TextDomLayoutManager *,
                      UnrecordedRefCountPolicy> MFUnrecTextDomLayoutManagerPtr;
/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<TextDomLayoutManager *,
                      WeakRefCountPolicy      > MFWeakTextDomLayoutManagerPtr;
/*! \ingroup GrpContribTextDomFieldMFields */
typedef PointerMField<TextDomLayoutManager *,
                      NoRefCountPolicy        > MFUncountedTextDomLayoutManagerPtr;



/*! \ingroup GrpContribTextDomFieldSFields */
typedef ChildPointerSField<
          TextDomLayoutManager *, 
          UnrecordedRefCountPolicy,
          1             > SFUnrecChildTextDomLayoutManagerPtr;



#else // these are the doxygen hacks

/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFRecTextDomLayoutManagerPtr : 
    public PointerSField<TextDomLayoutManager *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFUnrecTextDomLayoutManagerPtr : 
    public PointerSField<TextDomLayoutManager *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFWeakTextDomLayoutManagerPtr :
    public PointerSField<TextDomLayoutManager *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFUncountedTextDomLayoutManagerPtr :
    public PointerSField<TextDomLayoutManager *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFRecTextDomLayoutManagerPtr :
    public PointerMField<TextDomLayoutManager *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFUnrecTextDomLayoutManagerPtr :
    public PointerMField<TextDomLayoutManager *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFWeakTextDomLayoutManagerPtr :
    public PointerMField<TextDomLayoutManager *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribTextDomFieldMFields \ingroup GrpLibOSGContribTextDom */
struct MFUncountedTextDomLayoutManagerPtr :
    public PointerMField<TextDomLayoutManager *,
                         NoRefCountPolicy        > {};



/*! \ingroup GrpContribTextDomFieldSFields \ingroup GrpLibOSGContribTextDom */
struct SFUnrecChildTextDomLayoutManagerPtr :
    public ChildPointerSField<
        TextDomLayoutManager *, 
        UnrecordedRefCountPolicy,
        1             > {};


#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGTEXTDOMLAYOUTMANAGERFIELDS_H_ */

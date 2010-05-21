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


#ifndef _OSGACTIONEVENTFIELDS_H_
#define _OSGACTIONEVENTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribUserInterfaceDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class ActionEvent;

OSG_GEN_CONTAINERPTR(ActionEvent);

/*! \ingroup GrpContribUserInterfaceFieldTraits
    \ingroup GrpLibOSGContribUserInterface
 */
template <>
struct FieldTraits<ActionEvent *> :
    public FieldTraitsFCPtrBase<ActionEvent *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ActionEvent *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBUSERINTERFACE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFActionEventPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFActionEventPtr"; }
};

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecActionEventPtr"; 
}

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecActionEventPtr"; 
}

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakActionEventPtr"; 
}

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdActionEventPtr"; 
}

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecActionEventPtr"; 
}

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecActionEventPtr"; 
}

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakActionEventPtr"; 
}

template<> inline
const Char8 *FieldTraits<ActionEvent *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdActionEventPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ActionEvent *,
                      RecordedRefCountPolicy  > SFRecActionEventPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ActionEvent *,
                      UnrecordedRefCountPolicy> SFUnrecActionEventPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ActionEvent *,
                      WeakRefCountPolicy      > SFWeakActionEventPtr;
/*! \ingroup GrpContribUserInterfaceFieldSFields */
typedef PointerSField<ActionEvent *,
                      NoRefCountPolicy        > SFUncountedActionEventPtr;


/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ActionEvent *,
                      RecordedRefCountPolicy  > MFRecActionEventPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ActionEvent *,
                      UnrecordedRefCountPolicy> MFUnrecActionEventPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ActionEvent *,
                      WeakRefCountPolicy      > MFWeakActionEventPtr;
/*! \ingroup GrpContribUserInterfaceFieldMFields */
typedef PointerMField<ActionEvent *,
                      NoRefCountPolicy        > MFUncountedActionEventPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFRecActionEventPtr : 
    public PointerSField<ActionEvent *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUnrecActionEventPtr : 
    public PointerSField<ActionEvent *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFWeakActionEventPtr :
    public PointerSField<ActionEvent *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldSFields \ingroup GrpLibOSGContribUserInterface */
struct SFUncountedActionEventPtr :
    public PointerSField<ActionEvent *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFRecActionEventPtr :
    public PointerMField<ActionEvent *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUnrecActionEventPtr :
    public PointerMField<ActionEvent *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFWeakActionEventPtr :
    public PointerMField<ActionEvent *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribUserInterfaceFieldMFields \ingroup GrpLibOSGContribUserInterface */
struct MFUncountedActionEventPtr :
    public PointerMField<ActionEvent *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGACTIONEVENTFIELDS_H_ */
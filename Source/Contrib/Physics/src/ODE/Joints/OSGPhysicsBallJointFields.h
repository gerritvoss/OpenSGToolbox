/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com),  Behboud Kalantary         *
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


#ifndef _OSGPHYSICSBALLJOINTFIELDS_H_
#define _OSGPHYSICSBALLJOINTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribPhysicsDef.h"

#include "OSGFieldContainerFields.h"
#include "OSGPointerSField.h"
#include "OSGPointerMField.h"


OSG_BEGIN_NAMESPACE

class PhysicsBallJoint;

OSG_GEN_CONTAINERPTR(PhysicsBallJoint);

/*! \ingroup GrpContribPhysicsFieldTraits
    \ingroup GrpLibOSGContribPhysics
 */
template <>
struct FieldTraits<PhysicsBallJoint *> :
    public FieldTraitsFCPtrBase<PhysicsBallJoint *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<PhysicsBallJoint *>  Self;

    enum                        { Convertible = NotConvertible };

    static OSG_CONTRIBPHYSICS_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFPhysicsBallJointPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFPhysicsBallJointPtr"; }
};

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecPhysicsBallJointPtr"; 
}

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecPhysicsBallJointPtr"; 
}

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakPhysicsBallJointPtr"; 
}

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdPhysicsBallJointPtr"; 
}

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecPhysicsBallJointPtr"; 
}

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecPhysicsBallJointPtr"; 
}

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakPhysicsBallJointPtr"; 
}

template<> inline
const Char8 *FieldTraits<PhysicsBallJoint *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdPhysicsBallJointPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpContribPhysicsFieldSFields */
typedef PointerSField<PhysicsBallJoint *,
                      RecordedRefCountPolicy  > SFRecPhysicsBallJointPtr;
/*! \ingroup GrpContribPhysicsFieldSFields */
typedef PointerSField<PhysicsBallJoint *,
                      UnrecordedRefCountPolicy> SFUnrecPhysicsBallJointPtr;
/*! \ingroup GrpContribPhysicsFieldSFields */
typedef PointerSField<PhysicsBallJoint *,
                      WeakRefCountPolicy      > SFWeakPhysicsBallJointPtr;
/*! \ingroup GrpContribPhysicsFieldSFields */
typedef PointerSField<PhysicsBallJoint *,
                      NoRefCountPolicy        > SFUncountedPhysicsBallJointPtr;


/*! \ingroup GrpContribPhysicsFieldMFields */
typedef PointerMField<PhysicsBallJoint *,
                      RecordedRefCountPolicy  > MFRecPhysicsBallJointPtr;
/*! \ingroup GrpContribPhysicsFieldMFields */
typedef PointerMField<PhysicsBallJoint *,
                      UnrecordedRefCountPolicy> MFUnrecPhysicsBallJointPtr;
/*! \ingroup GrpContribPhysicsFieldMFields */
typedef PointerMField<PhysicsBallJoint *,
                      WeakRefCountPolicy      > MFWeakPhysicsBallJointPtr;
/*! \ingroup GrpContribPhysicsFieldMFields */
typedef PointerMField<PhysicsBallJoint *,
                      NoRefCountPolicy        > MFUncountedPhysicsBallJointPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpContribPhysicsFieldSFields \ingroup GrpLibOSGContribPhysics */
struct SFRecPhysicsBallJointPtr : 
    public PointerSField<PhysicsBallJoint *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpContribPhysicsFieldSFields \ingroup GrpLibOSGContribPhysics */
struct SFUnrecPhysicsBallJointPtr : 
    public PointerSField<PhysicsBallJoint *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribPhysicsFieldSFields \ingroup GrpLibOSGContribPhysics */
struct SFWeakPhysicsBallJointPtr :
    public PointerSField<PhysicsBallJoint *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpContribPhysicsFieldSFields \ingroup GrpLibOSGContribPhysics */
struct SFUncountedPhysicsBallJointPtr :
    public PointerSField<PhysicsBallJoint *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpContribPhysicsFieldMFields \ingroup GrpLibOSGContribPhysics */
struct MFRecPhysicsBallJointPtr :
    public PointerMField<PhysicsBallJoint *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpContribPhysicsFieldMFields \ingroup GrpLibOSGContribPhysics */
struct MFUnrecPhysicsBallJointPtr :
    public PointerMField<PhysicsBallJoint *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpContribPhysicsFieldMFields \ingroup GrpLibOSGContribPhysics */
struct MFWeakPhysicsBallJointPtr :
    public PointerMField<PhysicsBallJoint *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpContribPhysicsFieldMFields \ingroup GrpLibOSGContribPhysics */
struct MFUncountedPhysicsBallJointPtr :
    public PointerMField<PhysicsBallJoint *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _OSGPHYSICSBALLJOINTFIELDS_H_ */

/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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
 **     Do not change this file, changes should be done in the derived      **
 **     class PhysicsBallJoint!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &PhysicsBallJointBase::getClassType(void)
{
    return _type;
}

//! access the numerical type of the class
inline
OSG::UInt32 PhysicsBallJointBase::getClassTypeId(void)
{
    return _type.getId();
}

inline
OSG::UInt16 PhysicsBallJointBase::getClassGroupId(void)
{
    return _type.getGroupId();
}

/*------------------------------ get -----------------------------------*/

//! Get the value of the PhysicsBallJoint::_sfAnchor field.

inline
Vec3f &PhysicsBallJointBase::editAnchor(void)
{
    editSField(AnchorFieldMask);

    return _sfAnchor.getValue();
}

//! Get the value of the PhysicsBallJoint::_sfAnchor field.
inline
const Vec3f &PhysicsBallJointBase::getAnchor(void) const
{
    return _sfAnchor.getValue();
}

//! Set the value of the PhysicsBallJoint::_sfAnchor field.
inline
void PhysicsBallJointBase::setAnchor(const Vec3f &value)
{
    editSField(AnchorFieldMask);

    _sfAnchor.setValue(value);
}


#ifdef OSG_MT_CPTR_ASPECT
inline
void PhysicsBallJointBase::execSync (      PhysicsBallJointBase *pFrom,
                                        ConstFieldMaskArg  whichField,
                                        AspectOffsetStore &oOffsets,
                                        ConstFieldMaskArg  syncMode,
                                  const UInt32             uiSyncInfo)
{
    Inherited::execSync(pFrom, whichField, oOffsets, syncMode, uiSyncInfo);

    if(FieldBits::NoField != (AnchorFieldMask & whichField))
        _sfAnchor.syncWith(pFrom->_sfAnchor);
}
#endif


inline
const Char8 *PhysicsBallJointBase::getClassname(void)
{
    return "PhysicsBallJoint";
}
OSG_GEN_CONTAINERPTR(PhysicsBallJoint);

OSG_END_NAMESPACE

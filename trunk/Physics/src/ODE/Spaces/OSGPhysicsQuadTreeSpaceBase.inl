/*---------------------------------------------------------------------------*\
 *                         OpenSG ToolBox Physics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
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
 **     class PhysicsQuadTreeSpace!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &PhysicsQuadTreeSpaceBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 PhysicsQuadTreeSpaceBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
PhysicsQuadTreeSpacePtr PhysicsQuadTreeSpaceBase::create(void) 
{
    PhysicsQuadTreeSpacePtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PhysicsQuadTreeSpacePtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
PhysicsQuadTreeSpacePtr PhysicsQuadTreeSpaceBase::createEmpty(void) 
{ 
    PhysicsQuadTreeSpacePtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the PhysicsQuadTreeSpace::_sfCenter field.
inline
SFPnt3f *PhysicsQuadTreeSpaceBase::getSFCenter(void)
{
    return &_sfCenter;
}

//! Get the PhysicsQuadTreeSpace::_sfExtent field.
inline
SFVec3f *PhysicsQuadTreeSpaceBase::getSFExtent(void)
{
    return &_sfExtent;
}

//! Get the PhysicsQuadTreeSpace::_sfDepth field.
inline
SFInt32 *PhysicsQuadTreeSpaceBase::getSFDepth(void)
{
    return &_sfDepth;
}


//! Get the value of the PhysicsQuadTreeSpace::_sfCenter field.
inline
Pnt3f &PhysicsQuadTreeSpaceBase::getCenter(void)
{
    return _sfCenter.getValue();
}

//! Get the value of the PhysicsQuadTreeSpace::_sfCenter field.
inline
const Pnt3f &PhysicsQuadTreeSpaceBase::getCenter(void) const
{
    return _sfCenter.getValue();
}

//! Set the value of the PhysicsQuadTreeSpace::_sfCenter field.
inline
void PhysicsQuadTreeSpaceBase::setCenter(const Pnt3f &value)
{
    _sfCenter.setValue(value);
}

//! Get the value of the PhysicsQuadTreeSpace::_sfExtent field.
inline
Vec3f &PhysicsQuadTreeSpaceBase::getExtent(void)
{
    return _sfExtent.getValue();
}

//! Get the value of the PhysicsQuadTreeSpace::_sfExtent field.
inline
const Vec3f &PhysicsQuadTreeSpaceBase::getExtent(void) const
{
    return _sfExtent.getValue();
}

//! Set the value of the PhysicsQuadTreeSpace::_sfExtent field.
inline
void PhysicsQuadTreeSpaceBase::setExtent(const Vec3f &value)
{
    _sfExtent.setValue(value);
}

//! Get the value of the PhysicsQuadTreeSpace::_sfDepth field.
inline
Int32 &PhysicsQuadTreeSpaceBase::getDepth(void)
{
    return _sfDepth.getValue();
}

//! Get the value of the PhysicsQuadTreeSpace::_sfDepth field.
inline
const Int32 &PhysicsQuadTreeSpaceBase::getDepth(void) const
{
    return _sfDepth.getValue();
}

//! Set the value of the PhysicsQuadTreeSpace::_sfDepth field.
inline
void PhysicsQuadTreeSpaceBase::setDepth(const Int32 &value)
{
    _sfDepth.setValue(value);
}


OSG_END_NAMESPACE

#define OSGPHYSICSQUADTREESPACEBASE_INLINE_CVSID "@(#)$Id: FCBaseTemplate_inl.h,v 1.20 2002/12/04 14:22:22 dirk Exp $"

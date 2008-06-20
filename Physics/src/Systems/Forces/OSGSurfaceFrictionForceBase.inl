/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
 **     class SurfaceFrictionForce!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &SurfaceFrictionForceBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 SurfaceFrictionForceBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 


/*------------------------------ get -----------------------------------*/

//! Get the SurfaceFrictionForce::_sfFrictionConstant field.
inline
SFReal32 *SurfaceFrictionForceBase::getSFFrictionConstant(void)
{
    return &_sfFrictionConstant;
}

//! Get the SurfaceFrictionForce::_sfNormalForce field.
inline
SFNormalForcePtr *SurfaceFrictionForceBase::getSFNormalForce(void)
{
    return &_sfNormalForce;
}


//! Get the value of the SurfaceFrictionForce::_sfFrictionConstant field.
inline
Real32 &SurfaceFrictionForceBase::getFrictionConstant(void)
{
    return _sfFrictionConstant.getValue();
}

//! Get the value of the SurfaceFrictionForce::_sfFrictionConstant field.
inline
const Real32 &SurfaceFrictionForceBase::getFrictionConstant(void) const
{
    return _sfFrictionConstant.getValue();
}

//! Set the value of the SurfaceFrictionForce::_sfFrictionConstant field.
inline
void SurfaceFrictionForceBase::setFrictionConstant(const Real32 &value)
{
    _sfFrictionConstant.setValue(value);
}

//! Get the value of the SurfaceFrictionForce::_sfNormalForce field.
inline
NormalForcePtr &SurfaceFrictionForceBase::getNormalForce(void)
{
    return _sfNormalForce.getValue();
}

//! Get the value of the SurfaceFrictionForce::_sfNormalForce field.
inline
const NormalForcePtr &SurfaceFrictionForceBase::getNormalForce(void) const
{
    return _sfNormalForce.getValue();
}

//! Set the value of the SurfaceFrictionForce::_sfNormalForce field.
inline
void SurfaceFrictionForceBase::setNormalForce(const NormalForcePtr &value)
{
    _sfNormalForce.setValue(value);
}


OSG_END_NAMESPACE

#define OSGSURFACEFRICTIONFORCEBASE_INLINE_CVSID "@(#)$Id: FCBaseTemplate_inl.h,v 1.20 2002/12/04 14:22:22 dirk Exp $"

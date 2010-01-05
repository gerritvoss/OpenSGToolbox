/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
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
 **     class SphereDistribution3D!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &SphereDistribution3DBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 SphereDistribution3DBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
SphereDistribution3DPtr SphereDistribution3DBase::create(void) 
{
    SphereDistribution3DPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = SphereDistribution3DPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
SphereDistribution3DPtr SphereDistribution3DBase::createEmpty(void) 
{ 
    SphereDistribution3DPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the SphereDistribution3D::_sfCenter field.
inline
const SFPnt3f *SphereDistribution3DBase::getSFCenter(void) const
{
    return &_sfCenter;
}

//! Get the SphereDistribution3D::_sfCenter field.
inline
SFPnt3f *SphereDistribution3DBase::editSFCenter(void)
{
    return &_sfCenter;
}

//! Get the SphereDistribution3D::_sfInnerRadius field.
inline
const SFReal32 *SphereDistribution3DBase::getSFInnerRadius(void) const
{
    return &_sfInnerRadius;
}

//! Get the SphereDistribution3D::_sfInnerRadius field.
inline
SFReal32 *SphereDistribution3DBase::editSFInnerRadius(void)
{
    return &_sfInnerRadius;
}

//! Get the SphereDistribution3D::_sfOuterRadius field.
inline
const SFReal32 *SphereDistribution3DBase::getSFOuterRadius(void) const
{
    return &_sfOuterRadius;
}

//! Get the SphereDistribution3D::_sfOuterRadius field.
inline
SFReal32 *SphereDistribution3DBase::editSFOuterRadius(void)
{
    return &_sfOuterRadius;
}

//! Get the SphereDistribution3D::_sfMinTheta field.
inline
const SFReal32 *SphereDistribution3DBase::getSFMinTheta(void) const
{
    return &_sfMinTheta;
}

//! Get the SphereDistribution3D::_sfMinTheta field.
inline
SFReal32 *SphereDistribution3DBase::editSFMinTheta(void)
{
    return &_sfMinTheta;
}

//! Get the SphereDistribution3D::_sfMaxTheta field.
inline
const SFReal32 *SphereDistribution3DBase::getSFMaxTheta(void) const
{
    return &_sfMaxTheta;
}

//! Get the SphereDistribution3D::_sfMaxTheta field.
inline
SFReal32 *SphereDistribution3DBase::editSFMaxTheta(void)
{
    return &_sfMaxTheta;
}

//! Get the SphereDistribution3D::_sfMinZ field.
inline
const SFReal32 *SphereDistribution3DBase::getSFMinZ(void) const
{
    return &_sfMinZ;
}

//! Get the SphereDistribution3D::_sfMinZ field.
inline
SFReal32 *SphereDistribution3DBase::editSFMinZ(void)
{
    return &_sfMinZ;
}

//! Get the SphereDistribution3D::_sfMaxZ field.
inline
const SFReal32 *SphereDistribution3DBase::getSFMaxZ(void) const
{
    return &_sfMaxZ;
}

//! Get the SphereDistribution3D::_sfMaxZ field.
inline
SFReal32 *SphereDistribution3DBase::editSFMaxZ(void)
{
    return &_sfMaxZ;
}

//! Get the SphereDistribution3D::_sfSurfaceOrVolume field.
inline
const SFUInt32 *SphereDistribution3DBase::getSFSurfaceOrVolume(void) const
{
    return &_sfSurfaceOrVolume;
}

//! Get the SphereDistribution3D::_sfSurfaceOrVolume field.
inline
SFUInt32 *SphereDistribution3DBase::editSFSurfaceOrVolume(void)
{
    return &_sfSurfaceOrVolume;
}


//! Get the value of the SphereDistribution3D::_sfCenter field.
inline
Pnt3f &SphereDistribution3DBase::editCenter(void)
{
    return _sfCenter.getValue();
}

//! Get the value of the SphereDistribution3D::_sfCenter field.
inline
const Pnt3f &SphereDistribution3DBase::getCenter(void) const
{
    return _sfCenter.getValue();
}

//! Set the value of the SphereDistribution3D::_sfCenter field.
inline
void SphereDistribution3DBase::setCenter(const Pnt3f &value)
{
    _sfCenter.setValue(value);
}

//! Get the value of the SphereDistribution3D::_sfInnerRadius field.
inline
Real32 &SphereDistribution3DBase::editInnerRadius(void)
{
    return _sfInnerRadius.getValue();
}

//! Get the value of the SphereDistribution3D::_sfInnerRadius field.
inline
const Real32 &SphereDistribution3DBase::getInnerRadius(void) const
{
    return _sfInnerRadius.getValue();
}

//! Set the value of the SphereDistribution3D::_sfInnerRadius field.
inline
void SphereDistribution3DBase::setInnerRadius(const Real32 &value)
{
    _sfInnerRadius.setValue(value);
}

//! Get the value of the SphereDistribution3D::_sfOuterRadius field.
inline
Real32 &SphereDistribution3DBase::editOuterRadius(void)
{
    return _sfOuterRadius.getValue();
}

//! Get the value of the SphereDistribution3D::_sfOuterRadius field.
inline
const Real32 &SphereDistribution3DBase::getOuterRadius(void) const
{
    return _sfOuterRadius.getValue();
}

//! Set the value of the SphereDistribution3D::_sfOuterRadius field.
inline
void SphereDistribution3DBase::setOuterRadius(const Real32 &value)
{
    _sfOuterRadius.setValue(value);
}

//! Get the value of the SphereDistribution3D::_sfMinTheta field.
inline
Real32 &SphereDistribution3DBase::editMinTheta(void)
{
    return _sfMinTheta.getValue();
}

//! Get the value of the SphereDistribution3D::_sfMinTheta field.
inline
const Real32 &SphereDistribution3DBase::getMinTheta(void) const
{
    return _sfMinTheta.getValue();
}

//! Set the value of the SphereDistribution3D::_sfMinTheta field.
inline
void SphereDistribution3DBase::setMinTheta(const Real32 &value)
{
    _sfMinTheta.setValue(value);
}

//! Get the value of the SphereDistribution3D::_sfMaxTheta field.
inline
Real32 &SphereDistribution3DBase::editMaxTheta(void)
{
    return _sfMaxTheta.getValue();
}

//! Get the value of the SphereDistribution3D::_sfMaxTheta field.
inline
const Real32 &SphereDistribution3DBase::getMaxTheta(void) const
{
    return _sfMaxTheta.getValue();
}

//! Set the value of the SphereDistribution3D::_sfMaxTheta field.
inline
void SphereDistribution3DBase::setMaxTheta(const Real32 &value)
{
    _sfMaxTheta.setValue(value);
}

//! Get the value of the SphereDistribution3D::_sfMinZ field.
inline
Real32 &SphereDistribution3DBase::editMinZ(void)
{
    return _sfMinZ.getValue();
}

//! Get the value of the SphereDistribution3D::_sfMinZ field.
inline
const Real32 &SphereDistribution3DBase::getMinZ(void) const
{
    return _sfMinZ.getValue();
}

//! Set the value of the SphereDistribution3D::_sfMinZ field.
inline
void SphereDistribution3DBase::setMinZ(const Real32 &value)
{
    _sfMinZ.setValue(value);
}

//! Get the value of the SphereDistribution3D::_sfMaxZ field.
inline
Real32 &SphereDistribution3DBase::editMaxZ(void)
{
    return _sfMaxZ.getValue();
}

//! Get the value of the SphereDistribution3D::_sfMaxZ field.
inline
const Real32 &SphereDistribution3DBase::getMaxZ(void) const
{
    return _sfMaxZ.getValue();
}

//! Set the value of the SphereDistribution3D::_sfMaxZ field.
inline
void SphereDistribution3DBase::setMaxZ(const Real32 &value)
{
    _sfMaxZ.setValue(value);
}

//! Get the value of the SphereDistribution3D::_sfSurfaceOrVolume field.
inline
UInt32 &SphereDistribution3DBase::editSurfaceOrVolume(void)
{
    return _sfSurfaceOrVolume.getValue();
}

//! Get the value of the SphereDistribution3D::_sfSurfaceOrVolume field.
inline
const UInt32 &SphereDistribution3DBase::getSurfaceOrVolume(void) const
{
    return _sfSurfaceOrVolume.getValue();
}

//! Set the value of the SphereDistribution3D::_sfSurfaceOrVolume field.
inline
void SphereDistribution3DBase::setSurfaceOrVolume(const UInt32 &value)
{
    _sfSurfaceOrVolume.setValue(value);
}


OSG_END_NAMESPACE
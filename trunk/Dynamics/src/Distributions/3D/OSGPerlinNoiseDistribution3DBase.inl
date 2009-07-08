/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
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
 **     class PerlinNoiseDistribution3D!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &PerlinNoiseDistribution3DBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 PerlinNoiseDistribution3DBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
PerlinNoiseDistribution3DPtr PerlinNoiseDistribution3DBase::create(void) 
{
    PerlinNoiseDistribution3DPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = PerlinNoiseDistribution3DPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
PerlinNoiseDistribution3DPtr PerlinNoiseDistribution3DBase::createEmpty(void) 
{ 
    PerlinNoiseDistribution3DPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the PerlinNoiseDistribution3D::_sfFrequency field.
inline
SFUInt32 *PerlinNoiseDistribution3DBase::getSFFrequency(void)
{
    return &_sfFrequency;
}

//! Get the PerlinNoiseDistribution3D::_sfPersistance field.
inline
SFReal32 *PerlinNoiseDistribution3DBase::getSFPersistance(void)
{
    return &_sfPersistance;
}

//! Get the PerlinNoiseDistribution3D::_sfOctaves field.
inline
SFUInt32 *PerlinNoiseDistribution3DBase::getSFOctaves(void)
{
    return &_sfOctaves;
}

//! Get the PerlinNoiseDistribution3D::_sfAmplitude field.
inline
SFReal32 *PerlinNoiseDistribution3DBase::getSFAmplitude(void)
{
    return &_sfAmplitude;
}

//! Get the PerlinNoiseDistribution3D::_sfInterpolationType field.
inline
SFUInt32 *PerlinNoiseDistribution3DBase::getSFInterpolationType(void)
{
    return &_sfInterpolationType;
}


//! Get the value of the PerlinNoiseDistribution3D::_sfFrequency field.
inline
UInt32 &PerlinNoiseDistribution3DBase::getFrequency(void)
{
    return _sfFrequency.getValue();
}

//! Get the value of the PerlinNoiseDistribution3D::_sfFrequency field.
inline
const UInt32 &PerlinNoiseDistribution3DBase::getFrequency(void) const
{
    return _sfFrequency.getValue();
}

//! Set the value of the PerlinNoiseDistribution3D::_sfFrequency field.
inline
void PerlinNoiseDistribution3DBase::setFrequency(const UInt32 &value)
{
    _sfFrequency.setValue(value);
}

//! Get the value of the PerlinNoiseDistribution3D::_sfPersistance field.
inline
Real32 &PerlinNoiseDistribution3DBase::getPersistance(void)
{
    return _sfPersistance.getValue();
}

//! Get the value of the PerlinNoiseDistribution3D::_sfPersistance field.
inline
const Real32 &PerlinNoiseDistribution3DBase::getPersistance(void) const
{
    return _sfPersistance.getValue();
}

//! Set the value of the PerlinNoiseDistribution3D::_sfPersistance field.
inline
void PerlinNoiseDistribution3DBase::setPersistance(const Real32 &value)
{
    _sfPersistance.setValue(value);
}

//! Get the value of the PerlinNoiseDistribution3D::_sfOctaves field.
inline
UInt32 &PerlinNoiseDistribution3DBase::getOctaves(void)
{
    return _sfOctaves.getValue();
}

//! Get the value of the PerlinNoiseDistribution3D::_sfOctaves field.
inline
const UInt32 &PerlinNoiseDistribution3DBase::getOctaves(void) const
{
    return _sfOctaves.getValue();
}

//! Set the value of the PerlinNoiseDistribution3D::_sfOctaves field.
inline
void PerlinNoiseDistribution3DBase::setOctaves(const UInt32 &value)
{
    _sfOctaves.setValue(value);
}

//! Get the value of the PerlinNoiseDistribution3D::_sfAmplitude field.
inline
Real32 &PerlinNoiseDistribution3DBase::getAmplitude(void)
{
    return _sfAmplitude.getValue();
}

//! Get the value of the PerlinNoiseDistribution3D::_sfAmplitude field.
inline
const Real32 &PerlinNoiseDistribution3DBase::getAmplitude(void) const
{
    return _sfAmplitude.getValue();
}

//! Set the value of the PerlinNoiseDistribution3D::_sfAmplitude field.
inline
void PerlinNoiseDistribution3DBase::setAmplitude(const Real32 &value)
{
    _sfAmplitude.setValue(value);
}

//! Get the value of the PerlinNoiseDistribution3D::_sfInterpolationType field.
inline
UInt32 &PerlinNoiseDistribution3DBase::getInterpolationType(void)
{
    return _sfInterpolationType.getValue();
}

//! Get the value of the PerlinNoiseDistribution3D::_sfInterpolationType field.
inline
const UInt32 &PerlinNoiseDistribution3DBase::getInterpolationType(void) const
{
    return _sfInterpolationType.getValue();
}

//! Set the value of the PerlinNoiseDistribution3D::_sfInterpolationType field.
inline
void PerlinNoiseDistribution3DBase::setInterpolationType(const UInt32 &value)
{
    _sfInterpolationType.setValue(value);
}


OSG_END_NAMESPACE

#define OSGPERLINNOISEDISTRIBUTION3DBASE_INLINE_CVSID "@(#)$Id: FCBaseTemplate_inl.h,v 1.20 2002/12/04 14:22:22 dirk Exp $"


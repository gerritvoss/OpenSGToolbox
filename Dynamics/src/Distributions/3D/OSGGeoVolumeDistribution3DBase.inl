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
 **     class GeoVolumeDistribution3D!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &GeoVolumeDistribution3DBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 GeoVolumeDistribution3DBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
GeoVolumeDistribution3DPtr GeoVolumeDistribution3DBase::create(void) 
{
    GeoVolumeDistribution3DPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = GeoVolumeDistribution3DPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
GeoVolumeDistribution3DPtr GeoVolumeDistribution3DBase::createEmpty(void) 
{ 
    GeoVolumeDistribution3DPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the GeoVolumeDistribution3D::_sfVolume field.
inline
SFGeometryPtr *GeoVolumeDistribution3DBase::getSFVolume(void)
{
    return &_sfVolume;
}


//! Get the value of the GeoVolumeDistribution3D::_sfVolume field.
inline
GeometryPtr &GeoVolumeDistribution3DBase::getVolume(void)
{
    return _sfVolume.getValue();
}

//! Get the value of the GeoVolumeDistribution3D::_sfVolume field.
inline
const GeometryPtr &GeoVolumeDistribution3DBase::getVolume(void) const
{
    return _sfVolume.getValue();
}

//! Set the value of the GeoVolumeDistribution3D::_sfVolume field.
inline
void GeoVolumeDistribution3DBase::setVolume(const GeometryPtr &value)
{
    _sfVolume.setValue(value);
}


OSG_END_NAMESPACE

#define OSGGEOVOLUMEDISTRIBUTION3DBASE_INLINE_CVSID "@(#)$Id: FCBaseTemplate_inl.h,v 1.20 2002/12/04 14:22:22 dirk Exp $"


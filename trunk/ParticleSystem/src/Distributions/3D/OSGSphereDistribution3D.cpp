/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Dynamics                            *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGSphereDistribution3D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SphereDistribution3D
An SphereDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SphereDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f SphereDistribution3D::generate(void) const
{
    Vec3f Result;

    Real32 Radius;
    switch(getSurfaceOrVolume())
    {
    case SURFACE:
        {
            Real32 InnerSphereArea(4.1887902 * getInnerRadius() * getInnerRadius() * getInnerRadius());
            Real32 OuterSphereArea(4.1887902 * getOuterRadius() * getOuterRadius() * getOuterRadius());
            
            Real32 PickSphere(RandomPoolManager::getRandomReal32(0.0,1.0));

            if(PickSphere < InnerSphereArea/(InnerSphereArea+OuterSphereArea))
            {
                Radius = getInnerRadius();
            }
            else
            {
                Radius = getOuterRadius();
            }
            break;
        }
    case VOLUME:
    default:
        {

            Real32 Temp(osgpow(RandomPoolManager::getRandomReal32(osgpow(getInnerRadius()/getOuterRadius(), static_cast<Real32>(3.0)),1.0), static_cast<Real32>(0.3333333333)));

            Radius = Temp*getOuterRadius();

            break;
        }
    }
    Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
    Real32 Z( RandomPoolManager::getRandomReal32(getMinZ(),getMaxZ()) );

    Result[2] = getCenter().z() + Radius*Z;
    Real32 Phi( osgacos( (Result.z()-getCenter().z()) / Radius) );

    Result[0] = getCenter().x() + Radius*osgsin(Phi)*osgcos(Theta);
    Result[1] = getCenter().y() + Radius*osgsin(Phi)*osgsin(Theta);

    return Result;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SphereDistribution3D::SphereDistribution3D(void) :
    Inherited()
{
}

SphereDistribution3D::SphereDistribution3D(const SphereDistribution3D &source) :
    Inherited(source)
{
}

SphereDistribution3D::~SphereDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SphereDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & InnerRadiusFieldMask ||
       whichField & OuterRadiusFieldMask) &&
       getInnerRadius() > getOuterRadius())
    {
        Real32 Min(osgMin(getInnerRadius(), getOuterRadius()));
        Real32 Max(osgMax(getInnerRadius(), getOuterRadius()));
        beginEditCP(SphereDistribution3DPtr(this), InnerRadiusFieldMask | OuterRadiusFieldMask);
            setInnerRadius(Min);
            setOuterRadius(Max);
        endEditCP(SphereDistribution3DPtr(this), InnerRadiusFieldMask | OuterRadiusFieldMask);
    }
    
    if((whichField & MinThetaFieldMask ||
       whichField & MaxThetaFieldMask) &&
       osgabs(getMaxTheta() - getMinTheta()) - 6.283185 > 0.000001)
    {
        beginEditCP(SphereDistribution3DPtr(this), MaxThetaFieldMask);
            setMaxTheta(getMinTheta() + 6.283185);
        endEditCP(SphereDistribution3DPtr(this), MaxThetaFieldMask);
    }
    
    if((whichField & MinZFieldMask ||
       whichField & MaxZFieldMask))
    {
        if(getMinZ() < -1.0)
        {
            beginEditCP(SphereDistribution3DPtr(this), MinZFieldMask);
                setMinZ(-1.0);
            endEditCP(SphereDistribution3DPtr(this), MinZFieldMask);
        }
        if(getMaxZ() > 1.0)
        {
            beginEditCP(SphereDistribution3DPtr(this), MaxZFieldMask);
                setMaxZ(1.0);
            endEditCP(SphereDistribution3DPtr(this), MaxZFieldMask);
        }

        if(getMinZ() > getMaxZ())
        {
            Real32 Min(osgMin(getMinZ(), getMaxZ()));
            Real32 Max(osgMax(getMinZ(), getMaxZ()));
            beginEditCP(SphereDistribution3DPtr(this), MinZFieldMask | MaxZFieldMask);
                setMinZ(Min);
                setMaxZ(Max);
            endEditCP(SphereDistribution3DPtr(this), MinZFieldMask | MaxZFieldMask);
        }

    }
}

void SphereDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump SphereDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE


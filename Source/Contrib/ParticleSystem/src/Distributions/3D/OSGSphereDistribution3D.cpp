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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGSphereDistribution3D.h"
#include "OSGRandomPoolManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSphereDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGSphereDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SphereDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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

            Real32 Temp(osgPow(RandomPoolManager::getRandomReal32(osgPow(getInnerRadius()/getOuterRadius(), static_cast<Real32>(3.0)),1.0), static_cast<Real32>(0.3333333333)));

            Radius = Temp*getOuterRadius();

            break;
        }
    }
    Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
    Real32 Z( RandomPoolManager::getRandomReal32(getMinZ(),getMaxZ()) );

    Result[2] = getCenter().z() + Radius*Z;
    Real32 Phi( osgACos( (Result.z()-getCenter().z()) / Radius) );

    Result[0] = getCenter().x() + Radius*osgSin(Phi)*osgCos(Theta);
    Result[1] = getCenter().y() + Radius*osgSin(Phi)*osgSin(Theta);

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

void SphereDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & InnerRadiusFieldMask ||
       whichField & OuterRadiusFieldMask) &&
       getInnerRadius() > getOuterRadius())
    {
        Real32 Min(osgMin(getInnerRadius(), getOuterRadius()));
        Real32 Max(osgMax(getInnerRadius(), getOuterRadius()));
        setInnerRadius(Min);
        setOuterRadius(Max);
    }
    
    if((whichField & MinThetaFieldMask ||
       whichField & MaxThetaFieldMask) &&
       osgAbs(getMaxTheta() - getMinTheta()) - 6.283185 > 0.000001)
    {
        setMaxTheta(getMinTheta() + 6.283185);
    }
    
    if((whichField & MinZFieldMask ||
       whichField & MaxZFieldMask))
    {
        if(getMinZ() < -1.0)
        {
            setMinZ(-1.0);
        }
        if(getMaxZ() > 1.0)
        {
            setMaxZ(1.0);
        }

        if(getMinZ() > getMaxZ())
        {
            Real32 Min(osgMin(getMinZ(), getMaxZ()));
            Real32 Max(osgMax(getMinZ(), getMaxZ()));
            setMinZ(Min);
            setMaxZ(Max);
        }

    }
}

void SphereDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SphereDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE

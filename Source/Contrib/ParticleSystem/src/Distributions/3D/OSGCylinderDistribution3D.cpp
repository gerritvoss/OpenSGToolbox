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

#include "OSGCylinderDistribution3D.h"
#include "OSGRandomPoolManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGCylinderDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGCylinderDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CylinderDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f CylinderDistribution3D::generate(void) const
{
    Vec3f Result;

    switch(getSurfaceOrVolume())
    {
    case SURFACE:
        {
            std::vector<Real32> Areas;
            //Min Cap
            Areas.push_back(0.5*osgAbs(getMaxTheta() - getMinTheta())*(getOuterRadius()*getOuterRadius() - getInnerRadius()*getInnerRadius()));
            //Max Cap
            Areas.push_back(Areas.back() + 0.5*osgAbs(getMaxTheta() - getMinTheta())*(getOuterRadius()*getOuterRadius() - getInnerRadius()*getInnerRadius()));
            //Inner Tube
            Areas.push_back(Areas.back() + getInnerRadius()*osgAbs(getMaxTheta() - getMinTheta()) * getHeight());
            //Outer Tube
            Areas.push_back(Areas.back() + getOuterRadius()*osgAbs(getMaxTheta() - getMinTheta()) * getHeight());

            bool HasTubeSides(osgAbs(getMaxTheta() - getMinTheta()) - 6.283185 < -0.000001);
            if(HasTubeSides)
            {
                //MinTheta Tube Side
                Areas.push_back(Areas.back() + (getOuterRadius() - getInnerRadius()) * getHeight());

                //MaxTheta Tube Side
                Areas.push_back(Areas.back() + (getOuterRadius() - getInnerRadius()) * getHeight());
            }

            Real32 PickEdge(RandomPoolManager::getRandomReal32(0.0,1.0));
            if(PickEdge < Areas[0]/Areas.back())
            {
                //Max Cap
                Real32 Temp(osgSqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Result = getCenter().subZero()
                    + (Radius*osgSin(Theta))*getTangent()
                    + (Radius*osgCos(Theta))*getBinormal()
                    + (getHeight()/static_cast<Real32>(2.0))*getNormal();
            }
            else if(PickEdge < Areas[1]/Areas.back())
            {
                //Min Cap
                Real32 Temp(osgSqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Result = getCenter().subZero()
                    + (Radius*osgSin(Theta))*getTangent()
                    + (Radius*osgCos(Theta))*getBinormal()
                    + (-getHeight()/static_cast<Real32>(2.0))*getNormal();
            }
            else if(PickEdge < Areas[2]/Areas.back())
            {
                //Inner Tube
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result =  getCenter().subZero()
                    + getInnerRadius()*osgSin(Theta)*getTangent()
                    + getInnerRadius()*osgCos(Theta)*getBinormal()
                    + Height*getNormal();
            }
            else if(PickEdge < Areas[3]/Areas.back())
            {
                //Outer Tube
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result =  getCenter().subZero()
                    + getOuterRadius()*osgSin(Theta)*getTangent()
                    + getOuterRadius()*osgCos(Theta)*getBinormal()
                    + Height*getNormal();
            }
            else if(HasTubeSides && PickEdge < Areas[4]/Areas.back())
            {
                //MinTheta Tube Side
                Real32 Temp(osgSqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result = getCenter().subZero()
                    + (Radius*osgSin(getMinTheta()))*getTangent()
                    + (Radius*osgCos(getMinTheta()))*getBinormal()
                    + Height*getNormal();
            }
            else if(HasTubeSides && PickEdge < Areas[5]/Areas.back())
            {
                //MaxTheta Tube Side
                Real32 Temp(osgSqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result = getCenter().subZero()
                    + (Radius*osgSin(getMaxTheta()))*getTangent()
                    + (Radius*osgCos(getMaxTheta()))*getBinormal()
                    + Height*getNormal();
            }
            else
            {
                assert(false && "Should never reach this point");
            }
            break;
        }
    case VOLUME:
    default:
        {
            //To get a uniform distribution across the disc get a uniformly distributed allong 0.0 - 1.0
            //Then Take the square root of that.  This gives a square root distribution from 0.0 - 1.0
            //This square root distribution is used for the random radius because the area of a disc is 
            //dependant on the square of the radius, i.e it is a quadratic function
            Real32 Temp(osgSqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
            Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
            Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
            Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
            Result = getCenter().subZero()
                   + (Radius*osgSin(Theta))*getTangent()
                   + (Radius*osgCos(Theta))*getBinormal()
                   + Height*getNormal();
            break;
        }
    }

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CylinderDistribution3D::CylinderDistribution3D(void) :
    Inherited()
{
}

CylinderDistribution3D::CylinderDistribution3D(const CylinderDistribution3D &source) :
    Inherited(source)
{
}

CylinderDistribution3D::~CylinderDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CylinderDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void CylinderDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CylinderDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE

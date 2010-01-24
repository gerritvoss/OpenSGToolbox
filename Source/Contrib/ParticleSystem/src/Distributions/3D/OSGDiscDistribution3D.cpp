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

#include "OSGDiscDistribution3D.h"
#include "OSGRandomPoolManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDiscDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGDiscDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DiscDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f DiscDistribution3D::generate(void) const
{
    Vec3f Result;

    switch(getSurfaceOrEdge())
    {
    case EDGE:
        {
            Real32 OuterCircumference(getOuterRadius() * (getMaxTheta() - getMinTheta()));
            Real32 InnerCircumference(getInnerRadius() * (getMaxTheta() - getMinTheta()));
            Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );

            Real32 PickEdge(RandomPoolManager::getRandomReal32(0.0,1.0));
            if(PickEdge < InnerCircumference/(OuterCircumference + InnerCircumference))
            {
                Result =  getCenter().subZero() + getInnerRadius()*osgSin(Theta)*getTangent() + getInnerRadius()*osgCos(Theta)*getBinormal();
            }
            else
            {
                Result =  getCenter().subZero() + getOuterRadius()*osgSin(Theta)*getTangent() + getOuterRadius()*osgCos(Theta)*getBinormal();
            }
            break;
        }
    case SURFACE:
    default:
        {
            //To get a uniform distribution across the disc get a uniformly distributed allong 0.0 - 1.0
            //Then Take the square root of that.  This gives a square root distribution from 0.0 - 1.0
            //This square root distribution is used for the random radius because the area of a disc is 
            //dependant on the square of the radius, i.e it is a quadratic function
            Real32 Temp(osgSqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
            Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
            Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
            Result = getCenter().subZero() + (Radius*osgSin(Theta))*getTangent() + (Radius*osgCos(Theta))*getBinormal();
            break;
        }
    }

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DiscDistribution3D::DiscDistribution3D(void) :
    Inherited()
{
}

DiscDistribution3D::DiscDistribution3D(const DiscDistribution3D &source) :
    Inherited(source)
{
}

DiscDistribution3D::~DiscDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DiscDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DiscDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DiscDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE

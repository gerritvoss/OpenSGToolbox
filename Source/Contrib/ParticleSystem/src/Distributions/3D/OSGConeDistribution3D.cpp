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

#include "OSGConeDistribution3D.h"
#include "OSGQuaternion.h"
#include "OSGRandomPoolManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGConeDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGConeDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ConeDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f ConeDistribution3D:: generate(void) const
{
	
	Vec3f Result = getPosition().subZero();
	Real32 radius = 0.0;
	
	switch(getSurfaceOrVolume())
	{
	case SURFACE:
		{	// get either max or min for radius
			if(RandomPoolManager::getRandomInt32(0,100)%2 == 0) radius = getMax();
			else radius = getMin();
			break;
		}
	case VOLUME:
		{	// get random val. between max and min for radius
			if((getMax() > 0.0f) && (getMax() > getMin())) 
				radius = RandomPoolManager::getRandomReal32(getMin(),getMax());
			else radius = getMax();
			break;
		}
	}
	Vec3f normal = getDirection(); 
	normal.normalize();
	Real32 theta = (getSpread() > 0.0) ? RandomPoolManager::getRandomReal32(0,getSpread()/2) : 0.0;
	Real32 phi = (getSpread() > 0.0) ? RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) : 0.0;

	Vec3f SpherePoint( osgCos(phi)*osgSin(theta)*radius, osgSin(theta)*osgSin(phi)*radius, osgCos(theta)*radius );

	Quaternion DirectionRotation(Vec3f(0.0f,0.0f,1.0f), normal);
	DirectionRotation.multVec(SpherePoint, SpherePoint);

	Result += SpherePoint;

	return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ConeDistribution3D::ConeDistribution3D(void) :
    Inherited()
{
}

ConeDistribution3D::ConeDistribution3D(const ConeDistribution3D &source) :
    Inherited(source)
{
}

ConeDistribution3D::~ConeDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ConeDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void ConeDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ConeDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE

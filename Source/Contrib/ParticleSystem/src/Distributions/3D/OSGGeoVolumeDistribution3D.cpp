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

#include "OSGGeoVolumeDistribution3D.h"
#include "OSGTriangleIterator.h"
#include "OSGRandomPoolManager.h"
#include "OSGVector.h"
#include <set>
#include "OSGDistributionUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGGeoVolumeDistribution3DBase.cpp file.
// To modify it, please change the .fcd file (OSGGeoVolumeDistribution3D.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoVolumeDistribution3D::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec3f GeoVolumeDistribution3D::generate(void) const
{
   //TODO:Implement
   if(getVolume() != NULL && mVolumeVector.size() > 0)
	{
	    Real32 Volume( RandomPoolManager::getRandomReal32(0.0f, mVolumeVector.back()) );
	   
	    UInt32 index = stlLowerBound(mVolumeVector, 0, mVolumeVector.size() - 1, Volume);
	   
	    TriangleIterator ti(getVolume());
	    ti.seek(index);
	    Pnt3f p1 = ti.getPosition(0);
	    Pnt3f p2 = ti.getPosition(1);
		Pnt3f p3 = ti.getPosition(2);
		
		Real32 s(RandomPoolManager::getRandomReal32(0.0,1.0)),
			   t(RandomPoolManager::getRandomReal32(0.0,1.0)),
			   u(RandomPoolManager::getRandomReal32(0.0,1.0));

		if( s + t > 1.0 )
		{
			s = 1.0f - s;
			t = 1.0f - t;
		}
		
		if( s + t + u > 1.0)
		{
			if ( t + u > 1.0)
			{
				t = 1.0f - u;
				u = 1.0f - s - t;
			}
			else
			{
				s = 1.0f - t - u;
				u = s + t + u - 1.0f;
			}
		}

		Vec3f Result = Centroid.subZero()
			     	+ s*(Centroid - p1)
					+ t*(Centroid - p2)
					+ u*(Centroid - p3);
		
        return Result;
	}
	else
	{
        return Vec3f(0.0f,0.0f,0.0f);
	}
}

void GeoVolumeDistribution3D::updateVolume(void)
{
	mVolumeVector.clear();
	Centroid = Pnt3f(0.0f,0.0f,0.0f);
	std::set<Pnt3f> uniquePositions;
	
	//Eliminate duplicate points
	for(UInt32 i(0) ; i<getVolume()->getPositions()->size() ; ++i)
	{
		//if(uniquePositions.find(getVolume()->getPositions()->getValue(i)) == uniquePositions.end())
		//{
			uniquePositions.insert(getVolume()->getPositions()->getValue<Pnt3f>(i));
		//}
		/*bool isUnique = true;
		
		for(UInt32 j(0) ; j<uniquePositions.size() ; ++j)
		{
			if(getVolume()->getPositions()->getValue(i) == uniquePositions[j])
			{
				isUnique = false;
			}
		}
		
		if (isUnique)
		{
			uniquePositions.push_back(getVolume()->getPositions()->getValue(i));
		}*/
	}
	
	//Find Centroid
	for(std::set<Pnt3f>::iterator i(uniquePositions.begin()) ; i!=uniquePositions.end() ; ++i)
	{
		Centroid += Vec3f(*i); //how to get values out one by one?
	}
	Centroid /= uniquePositions.size();
	
	//Add volumes to volume vector
	if(getVolume() != NULL)
	{
		TriangleIterator ti(getVolume());

		while(!ti.isAtEnd())
		{
			//Find surface vertices of tetrahedron
			Pnt3f p1 = ti.getPosition(0);
			Pnt3f p2 = ti.getPosition(1);
			Pnt3f p3 = ti.getPosition(2);
			
			//Find volume of tetrahedron
			Vec3f vec1 = p1 - Centroid;
			Vec3f vec2 = p2 - Centroid;
			Vec3f vec3 = p3 - Centroid;
			
			Real32 volume = osgAbs(vec1.dot((vec2.cross(vec3)))) / 6;
						
			//Add new volume to volume vector
			if(mVolumeVector.size() == 0)
			{
				mVolumeVector.push_back(volume);
			}
			else
			{
				mVolumeVector.push_back(mVolumeVector.back() + volume);
			}
			++ti;
		}
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoVolumeDistribution3D::GeoVolumeDistribution3D(void) :
    Inherited()
{
}

GeoVolumeDistribution3D::GeoVolumeDistribution3D(const GeoVolumeDistribution3D &source) :
    Inherited(source)
{
}

GeoVolumeDistribution3D::~GeoVolumeDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoVolumeDistribution3D::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
	
	if(whichField & VolumeFieldMask)
	{
		//Update Volume Vector
		updateVolume();
	}
}

void GeoVolumeDistribution3D::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump GeoVolumeDistribution3D NI" << std::endl;
}

OSG_END_NAMESPACE

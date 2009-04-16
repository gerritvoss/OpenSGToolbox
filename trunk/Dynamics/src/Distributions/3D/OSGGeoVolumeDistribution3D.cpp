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

#include "OSGGeoVolumeDistribution3D.h"
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGTriangleIterator.h>
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>
#include <OpenSG/OSGVector.h>
#include <set>
#include "Utils/OSGDynamicsUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GeoVolumeDistribution3D
An GeoVolumeDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoVolumeDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector GeoVolumeDistribution3D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_GEO_VOLUME_3D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector GeoVolumeDistribution3D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector GeoVolumeDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != 0)
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_GEO_VOLUME_3D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_GEO_VOLUME_3D_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Pnt3f GeoVolumeDistribution3D::generate(void)
{
   //TODO:Implement
   if(getVolume() != NullFC && mVolumeVector.size() > 0)
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

		Pnt3f Result = Centroid
			     	+ s*(Centroid - p1)
					+ t*(Centroid - p2)
					+ u*(Centroid - p3);
		
        return Pnt3f(Result);
	}
	else
	{
        return Pnt3f(0.0f,0.0f,0.0f);
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
			uniquePositions.insert(getVolume()->getPositions()->getValue(i));
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
	if(getVolume() != NullFC)
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
			
			Real32 volume = osgabs(vec1.dot((vec2.cross(vec3)))) / 6;
						
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

void GeoVolumeDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
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


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGGEOVOLUMEDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOVOLUMEDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEOVOLUMEDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

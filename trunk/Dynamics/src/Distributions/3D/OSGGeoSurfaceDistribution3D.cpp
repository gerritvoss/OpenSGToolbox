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

#include "OSGGeoSurfaceDistribution3D.h"
#include <OpenSG/OSGVecFieldDataType.h>
#include <OpenSG/OSGTriangleIterator.h>
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>
#include "Utils/OSGDynamicsUtils.h"

#include <algorithm>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GeoSurfaceDistribution3D
An GeoSurfaceDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GeoSurfaceDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector GeoSurfaceDistribution3D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS));
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(1,OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS));
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(2,OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector GeoSurfaceDistribution3D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector GeoSurfaceDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != 0)
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS));
	Pnt3f Position;
	Vec3f Normal,Tangent;
	generate(Position,Normal,Tangent);

    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS, Position));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(1,OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS, Normal));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(2,OSG_GEO_SURFACE_3D_DIST_OUTPUTPARAMETERS, Tangent));

    return ResultVector;
}

void GeoSurfaceDistribution3D::generate(Pnt3f& Pos, Vec3f& Normal, Vec3f& Tangent)
{

	if(getSurface() != NullFC && mAreaVector.size() > 0)
	{
	    Real32 Area( RandomPoolManager::getRandomReal32(0.0f, mAreaVector.back()) );
	   
	    UInt32 index = stlLowerBound(mAreaVector, 0, mAreaVector.size() - 1, Area);//std::lower_bound(&mAreaVector.front(), &mAreaVector.back(), Area);
	   
	    TriangleIterator ti(getSurface());
	    ti.seek(index);
		
		Real32 s(RandomPoolManager::getRandomReal32(0.0,1.0)),
			   t(RandomPoolManager::getRandomReal32(0.0,1.0));

		if(s+t > 1.0)
		{
			s = 1.0f - s;
			t = 1.0f - t;
		}

	    Pnt3f p1 = ti.getPosition(0),
			  p2 =  ti.getPosition(1),
			  p3 =  ti.getPosition(2);

		Pos = p1
	     	+ s*(p2 - p1)
			+ t*(p3 - p1);

	    Vec3f n1 = ti.getNormal(0),
			  n2 = ti.getNormal(1),
			  n3 = ti.getNormal(2);

		Normal = n1
	     	+ s*(n2 - n1)
			+ t*(n3 - n1);


	    Vec3f t1 = ti.getTexCoords7(0),
			  t2 = ti.getTexCoords7(1),
			  t3 = ti.getTexCoords7(2);

		Tangent = t1
	     	+ s*(t2 - t1)
			+ t*(t3 - t1);
	}
	else
	{
        Pos.setValues(0.0f,0.0f,0.0f);
        Normal.setValues(0.0f,0.0f,0.0f);
        Tangent.setValues(0.0f,0.0f,0.0f);
	}
}

void GeoSurfaceDistribution3D::updateSurfaceArea(void)
{
	mAreaVector.clear();
	
	if(getSurface() != NullFC)
	{
		TriangleIterator ti(getSurface());

		while(!ti.isAtEnd())
		{
			//Calculate Area and add to previous Area
			Pnt3f p1 = ti.getPosition(0);
			Pnt3f p2 = ti.getPosition(1);
			Pnt3f p3 = ti.getPosition(2);
			
			//Find lengths of sides
			Real32 sideA = p1.dist(p2);//  osgsqrt((p1.x() - p2.x())*(p1.x() - p2.x()) + (p1.y() - p2.y())*(p1.y() - p2.y()) + (p1.z() - p2.z())*(p1.z() - p2.z()));
			Real32 sideB =  p2.dist(p3); //osgsqrt((p2.x() - p3.x())*(p2.x() - p3.x()) + (p2.y() - p3.y())*(p2.y() - p3.y()) + (p2.z() - p3.z())*(p2.z() - p3.z()));
			Real32 sideC =  p3.dist(p1); //osgsqrt((p3.x() - p1.x())*(p3.x() - p1.x()) + (p3.y() - p1.y())*(p3.y() - p1.y()) + (p3.z() - p1.z())*(p3.z() - p1.z()));
			
			//Heron's formula
			Real32 area = (osgsqrt((sideA + sideB + sideC)*(sideA + sideB - sideC)*(sideB + sideC - sideA)*(sideC + sideA - sideB)))/4.0;
			
			if(mAreaVector.size() ==0)
			{
				mAreaVector.push_back(area);
			}
			else
			{
				mAreaVector.push_back(mAreaVector.back() + area);
			}
			++ti;
		}
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GeoSurfaceDistribution3D::GeoSurfaceDistribution3D(void) :
    Inherited()
{
}

GeoSurfaceDistribution3D::GeoSurfaceDistribution3D(const GeoSurfaceDistribution3D &source) :
    Inherited(source)
{
}

GeoSurfaceDistribution3D::~GeoSurfaceDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GeoSurfaceDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
	if(whichField & SurfaceFieldMask)
	{
		//Update Surface Area Vector
		updateSurfaceArea();
	}
}

void GeoSurfaceDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GeoSurfaceDistribution3D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGEOSURFACEDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGEOSURFACEDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGEOSURFACEDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

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
#include <OpenSG/OSGQuaternion.h>

#include "OSGConeDistribution3D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ConeDistribution3D
An BoxDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ConeDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector ConeDistribution3D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_CONE3D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector ConeDistribution3D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector ConeDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != 0)
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_CONE3D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_CONE3D_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}


Pnt3f ConeDistribution3D:: generate(void)
{
	
	Pnt3f Result = getPosition();
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
	Real32 theta = (getSpread() > 0.0) ? RandomPoolManager::getRandomReal32(-getSpread()/2,getSpread()/2) : 0.0;
	Real32 phi = (getSpread() > 0.0) ? RandomPoolManager::getRandomReal32(0.0,3.141597*2) : 0.0;

	Vec3f SpherePoint( osgcos(phi)*osgsin(theta)*radius, osgsin(theta)*osgsin(phi)*radius, osgcos(theta)*radius );

	Quaternion DirectionRotation(Vec3f(0.0f,0.0f,1.0f), normal);;
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

void ConeDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ConeDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ConeDistribution3D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCONEDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCONEDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCONEDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


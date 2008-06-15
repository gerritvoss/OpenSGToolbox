/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include "OSGDiscDistribution3D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DiscDistribution3D
An DiscDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DiscDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector DiscDistribution3D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_DISC3D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector DiscDistribution3D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector DiscDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_DISC3D_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_DISC3D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_DISC3D_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Pnt3f DiscDistribution3D::generate(void)
{
    Pnt3f Result;

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
                Result =  getCenter() + getInnerRadius()*osgsin(Theta)*getTangent() + getInnerRadius()*osgcos(Theta)*getBinormal();
            }
            else
            {
                Result =  getCenter() + getOuterRadius()*osgsin(Theta)*getTangent() + getOuterRadius()*osgcos(Theta)*getBinormal();
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
            Real32 Temp(osgsqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
            Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
            Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
            Result = getCenter() + (Radius*osgsin(Theta))*getTangent() + (Radius*osgcos(Theta))*getBinormal();
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

void DiscDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & NormalFieldMask)
    {
        //Determine the Normal, Tangent, Binormal Vectors
        getNormal().normalize();

        Vec3f TempVec(getNormal());
        if(getNormal().x() == 0.0f)
        {
            TempVec[0] += osgMax(osgabs(TempVec.y()), osgabs(TempVec.z()));
        }
        else
        {
            TempVec[1] += osgMax(osgabs(TempVec.x()), osgMax(osgabs(TempVec.y()), osgabs(TempVec.z())));
        }

        beginEditCP(DiscDistribution3DPtr(this), TangentFieldMask | BinormalFieldMask);
            setTangent(getNormal().cross(TempVec));
            getTangent().normalize();
            setBinormal(getTangent().cross(getNormal()));
            getBinormal().normalize();
        endEditCP(DiscDistribution3DPtr(this), TangentFieldMask | BinormalFieldMask);
    }
}

void DiscDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DiscDistribution3D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDISCDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISCDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISCDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


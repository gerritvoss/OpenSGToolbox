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

#include "OSGCylinderDistribution3D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CylinderDistribution3D
An CylinderDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CylinderDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector CylinderDistribution3D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_CYLINDER_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector CylinderDistribution3D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector CylinderDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_CYLINDER_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_CYLINDER_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_CYLINDER_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Pnt3f CylinderDistribution3D::generate(void)
{
    Pnt3f Result;

    switch(getSurfaceOrVolume())
    {
    case SURFACE:
        {
            std::vector<Real32> Areas;
            //Min Cap
            Areas.push_back(0.5*osgabs(getMaxTheta() - getMinTheta())*(getOuterRadius()*getOuterRadius() - getInnerRadius()*getInnerRadius()));
            //Max Cap
            Areas.push_back(Areas.back() + 0.5*osgabs(getMaxTheta() - getMinTheta())*(getOuterRadius()*getOuterRadius() - getInnerRadius()*getInnerRadius()));
            //Inner Tube
            Areas.push_back(Areas.back() + getInnerRadius()*osgabs(getMaxTheta() - getMinTheta()) * getHeight());
            //Outer Tube
            Areas.push_back(Areas.back() + getOuterRadius()*osgabs(getMaxTheta() - getMinTheta()) * getHeight());

            bool HasTubeSides(osgabs(getMaxTheta() - getMinTheta()) - 6.283185 < -0.000001);
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
                Real32 Temp(osgsqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Result = getCenter()
                    + (Radius*osgsin(Theta))*getTangent()
                    + (Radius*osgcos(Theta))*getBinormal()
                    + (getHeight()/static_cast<Real32>(2.0))*getNormal();
            }
            else if(PickEdge < Areas[1]/Areas.back())
            {
                //Min Cap
                Real32 Temp(osgsqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Result = getCenter()
                    + (Radius*osgsin(Theta))*getTangent()
                    + (Radius*osgcos(Theta))*getBinormal()
                    + (-getHeight()/static_cast<Real32>(2.0))*getNormal();
            }
            else if(PickEdge < Areas[2]/Areas.back())
            {
                //Inner Tube
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result =  getCenter()
                    + getInnerRadius()*osgsin(Theta)*getTangent()
                    + getInnerRadius()*osgcos(Theta)*getBinormal()
                    + Height*getNormal();
            }
            else if(PickEdge < Areas[3]/Areas.back())
            {
                //Outer Tube
                Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result =  getCenter()
                    + getOuterRadius()*osgsin(Theta)*getTangent()
                    + getOuterRadius()*osgcos(Theta)*getBinormal()
                    + Height*getNormal();
            }
            else if(HasTubeSides && PickEdge < Areas[4]/Areas.back())
            {
                //MinTheta Tube Side
                Real32 Temp(osgsqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result = getCenter()
                    + (Radius*osgsin(getMinTheta()))*getTangent()
                    + (Radius*osgcos(getMinTheta()))*getBinormal()
                    + Height*getNormal();
            }
            else if(HasTubeSides && PickEdge < Areas[5]/Areas.back())
            {
                //MaxTheta Tube Side
                Real32 Temp(osgsqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
                Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
                Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
                Result = getCenter()
                    + (Radius*osgsin(getMaxTheta()))*getTangent()
                    + (Radius*osgcos(getMaxTheta()))*getBinormal()
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
            Real32 Temp(osgsqrt(RandomPoolManager::getRandomReal32(0.0,1.0)));
            Real32 Radius(getInnerRadius() + Temp*(getOuterRadius() - getInnerRadius()));
            Real32 Height(RandomPoolManager::getRandomReal32(-getHeight()/2.0,getHeight()/2.0));
            Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
            Result = getCenter()
                   + (Radius*osgsin(Theta))*getTangent()
                   + (Radius*osgcos(Theta))*getBinormal()
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

void CylinderDistribution3D::changed(BitVector whichField, UInt32 origin)
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

        beginEditCP(CylinderDistribution3DPtr(this), TangentFieldMask | BinormalFieldMask);
            setTangent(getNormal().cross(TempVec));
            getTangent().normalize();
            setBinormal(getTangent().cross(getNormal()));
            getBinormal().normalize();
        endEditCP(CylinderDistribution3DPtr(this), TangentFieldMask | BinormalFieldMask);
    }

    if((whichField & InnerRadiusFieldMask ||
       whichField & OuterRadiusFieldMask) &&
       getInnerRadius() > getOuterRadius())
    {
        Real32 Min(osgMin(getInnerRadius(), getOuterRadius()));
        Real32 Max(osgMax(getInnerRadius(), getOuterRadius()));
        beginEditCP(CylinderDistribution3DPtr(this), InnerRadiusFieldMask | OuterRadiusFieldMask);
            setInnerRadius(Min);
            setOuterRadius(Max);
        endEditCP(CylinderDistribution3DPtr(this), InnerRadiusFieldMask | OuterRadiusFieldMask);
    }
    
    if((whichField & MinThetaFieldMask ||
       whichField & MaxThetaFieldMask) &&
       osgabs(getMaxTheta() - getMinTheta()) - 6.283185 > 0.000001)
    {
        beginEditCP(CylinderDistribution3DPtr(this), MaxThetaFieldMask);
            setMaxTheta(getMinTheta() + 6.283185);
        endEditCP(CylinderDistribution3DPtr(this), MaxThetaFieldMask);
    }
}

void CylinderDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CylinderDistribution3D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCYLINDERDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCYLINDERDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCYLINDERDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


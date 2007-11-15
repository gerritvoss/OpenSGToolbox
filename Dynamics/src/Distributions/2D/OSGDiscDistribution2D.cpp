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

#include "OSGDiscDistribution2D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DiscDistribution2D
An DiscDistribution2D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DiscDistribution2D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

DiscDistribution2D::FunctionIOTypeVector DiscDistribution2D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_DISC2D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

DiscDistribution2D::FunctionIOTypeVector DiscDistribution2D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

DiscDistribution2D::FunctionIOParameterVector DiscDistribution2D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_DISC2D_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_DISC2D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_DISC2D_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Pnt2f DiscDistribution2D::generate(void)
{
    Pnt2f Result;

    switch(getSurfaceOrEdge())
    {
    case EDGE:
        {
            Real32 OuterCircumference(getMaxRadius() * (getMaxTheta() - getMinTheta()));
            Real32 InnerCircumference(getMinRadius() * (getMaxTheta() - getMinTheta()));
            Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );

            Real32 PickEdge(RandomPoolManager::getRandomReal32(0.0,1.0));
            if(PickEdge < InnerCircumference/(OuterCircumference + InnerCircumference))
            {
                Result =  getCenter() + Vec2f(getMinRadius()*osgcos(Theta), getMinRadius()*osgsin(Theta));
            }
            else
            {
                Result =  getCenter() + Vec2f(getMaxRadius()*osgcos(Theta), getMaxRadius()*osgsin(Theta));
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
            Real32 Radius(getMinRadius() + Temp*(getMaxRadius() - getMinRadius()));
            Real32 Theta( RandomPoolManager::getRandomReal32(getMinTheta(),getMaxTheta()) );
            Result = getCenter() + Vec2f(Radius*osgcos(Theta), Radius*osgsin(Theta));
            break;
        }
    }

    return Result;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DiscDistribution2D::DiscDistribution2D(void) :
    Inherited()
{
}

DiscDistribution2D::DiscDistribution2D(const DiscDistribution2D &source) :
    Inherited(source)
{
}

DiscDistribution2D::~DiscDistribution2D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DiscDistribution2D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DiscDistribution2D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DiscDistribution2D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDISCDISTRIBUTION2DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISCDISTRIBUTION2DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISCDISTRIBUTION2DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


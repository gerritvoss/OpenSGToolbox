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

#include "OSGBoxDistribution3D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BoxDistribution3D
An BoxDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void BoxDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

BoxDistribution3D::FunctionIOTypeVector BoxDistribution3D::getOutputTypes(FunctionIOParameterVector& InputParameters) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_BOX3D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

BoxDistribution3D::FunctionIOTypeVector BoxDistribution3D::getInputTypes(FunctionIOParameterVector& InputParameters) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

BoxDistribution3D::FunctionIOParameterVector BoxDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != 0)
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_BOX3D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_BOX3D_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Pnt3f BoxDistribution3D::generate(void)
{
    Pnt3f Result;

    switch(getSurfaceOrVolume())
    {
    case SURFACE:
        {
            std::vector<Real32> Areas;
            Vec3f SideLengths(getMaxPoint() - getMinPoint());

            Areas.push_back(SideLengths.x() * SideLengths.y());                 //Min Z
            Areas.push_back(Areas.back() + SideLengths.x() * SideLengths.y());  //Max Z
            Areas.push_back(Areas.back() + SideLengths.x() * SideLengths.z());  //Min Y
            Areas.push_back(Areas.back() + SideLengths.x() * SideLengths.z());  //Max Y
            Areas.push_back(Areas.back() + SideLengths.z() * SideLengths.y());  //Min X
            Areas.push_back(Areas.back() + SideLengths.z() * SideLengths.y());  //Max X

            Real32 PickSide(RandomPoolManager::getRandomReal32(0.0,1.0));
            if(PickSide >= 0.0 && PickSide <Areas[0]/Areas.back())  //Min Z
            {
                Result = Pnt3f(getMinPoint()) +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               0.0);
            }
            else if(PickSide >= Areas[0]/Areas.back() && PickSide <Areas[1]/Areas.back())  //Max Z
            {
                Result = Pnt3f(getMinPoint().x(), getMinPoint().y(), getMaxPoint().z()) +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               0.0);
            }
            else if(PickSide >= Areas[1]/Areas.back() && PickSide <Areas[2]/Areas.back())  //Min Y
            {
                Result = Pnt3f(getMinPoint()) +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else if(PickSide >= Areas[2]/Areas.back() && PickSide <Areas[3]/Areas.back())  //Max Y
            {
                Result = Pnt3f(getMinPoint().x(), getMaxPoint().y(), getMinPoint().z()) +
                         Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.x(),
                               0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else if(PickSide >= Areas[3]/Areas.back() && PickSide <Areas[4]/Areas.back())  //Min X
            {
                Result = Pnt3f(getMinPoint()) +
                         Vec3f(0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else if(PickSide >= Areas[4]/Areas.back() && PickSide <Areas[5]/Areas.back())  //Max Y
            {
                Result = Pnt3f(getMaxPoint().x(), getMinPoint().y(), getMinPoint().z()) +
                         Vec3f(0.0,
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.y(),
                               RandomPoolManager::getRandomReal32(0.0,1.0)*SideLengths.z());
            }
            else
            {
                assert(false && "Should never reach this point");
            }
        
        break;
        }
    case VOLUME:
    default:

        Result = getMinPoint() + Vec3f(RandomPoolManager::getRandomReal32(0.0,1.0)*(getMaxPoint().x() - getMinPoint().x()),
            RandomPoolManager::getRandomReal32(0.0,1.0)*(getMaxPoint().y() - getMinPoint().y()),
            RandomPoolManager::getRandomReal32(0.0,1.0)*(getMaxPoint().z() - getMinPoint().z()));
        
        break;
    }

    return Result;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BoxDistribution3D::BoxDistribution3D(void) :
    Inherited()
{
}

BoxDistribution3D::BoxDistribution3D(const BoxDistribution3D &source) :
    Inherited(source)
{
}

BoxDistribution3D::~BoxDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void BoxDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void BoxDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump BoxDistribution3D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGBOXDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBOXDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBOXDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


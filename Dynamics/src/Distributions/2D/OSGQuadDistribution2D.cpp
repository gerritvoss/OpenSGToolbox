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

#include "OSGQuadDistribution2D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::QuadDistribution2D
An QuadDistribution2D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void QuadDistribution2D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector QuadDistribution2D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_QUAD2D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector QuadDistribution2D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector QuadDistribution2D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_QUAD2D_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_QUAD2D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_QUAD2D_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}
Pnt2f QuadDistribution2D::generate(void)
{
    Pnt2f Result;

    switch(getSurfaceOrEdge())
    {
    case EDGE:
        {
            Vec2f Side1(getPoint2() - getPoint1()),
                  Side2(getPoint3() - getPoint2()),
                  Side3(getPoint4() - getPoint3()),
                  Side4(getPoint1() - getPoint4());

            Real32 Side1Length(Side1.length()),
                   Side2Length(Side2.length()),
                   Side3Length(Side3.length()),
                   Side4Length(Side4.length());

            Real32 TotalLength(Side1Length + Side2Length + Side3Length + Side4Length);

            Real32 Rand(RandomPoolManager::getRandomReal32(0.0,1.0));

            Real32 PickEdge(RandomPoolManager::getRandomReal32(0.0,1.0));
            if(Rand < Side1Length/TotalLength)
            {
                Result = getPoint1() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side1;
            }
            else if(Rand < (Side1Length+Side2Length)/TotalLength)
            {
                Result = getPoint2() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side2;
            }
            else if(Rand < (Side1Length+Side2Length+Side3Length)/TotalLength)
            {
                Result = getPoint3() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side3;
            }
            else
            {
                Result = getPoint4() + RandomPoolManager::getRandomReal32(0.0,1.0)*Side4;
            }
            break;
        }
    case SURFACE:
    default:
        {
            Real32 s(RandomPoolManager::getRandomReal32(0.0,1.0)),
                   t(RandomPoolManager::getRandomReal32(0.0,1.0));

            if(s+t > 1.0)
            {
                s = 1.0f - s;
                t = 1.0f - t;
                Result = getPoint3()
                    + s*(getPoint2() - getPoint3())
                    + t*(getPoint4() - getPoint3());
            }
            else
            {
                Result = getPoint1()
                    + s*(getPoint2() - getPoint1())
                    + t*(getPoint4() - getPoint1());
            }

            break;
        }
    }

    return Result;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

QuadDistribution2D::QuadDistribution2D(void) :
    Inherited()
{
}

QuadDistribution2D::QuadDistribution2D(const QuadDistribution2D &source) :
    Inherited(source)
{
}

QuadDistribution2D::~QuadDistribution2D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void QuadDistribution2D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void QuadDistribution2D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump QuadDistribution2D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGQUADDISTRIBUTION2DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGQUADDISTRIBUTION2DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGQUADDISTRIBUTION2DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox Particle System                        *
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

#define OSG_COMPILEPARTICLESYSTEMLIB

#include <OpenSG/OSGConfig.h>

#include "OSGParticleDistribution3D.h"
#include <OpenSG/Toolbox/OSGRandomPoolManager.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ParticleDistribution3D
An ParticleDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ParticleDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector ParticleDistribution3D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PARTICLE3D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector ParticleDistribution3D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    return InputTypes;
}

FunctionIOParameterVector ParticleDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != 0)
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PARTICLE3D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_PARTICLE3D_DIST_OUTPUTPARAMETERS, generate()));

    return ResultVector;
}

Pnt3f ParticleDistribution3D::generate(void)
{
    Pnt3f Result;
	if(getSystem() != NullFC && getSystem()->getNumParticles() != 0)
	{
		Result = getSystem()->getPosition(RandomPoolManager::getRandomInt32(0,getSystem()->getNumParticles()));
	}

	return Result;
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ParticleDistribution3D::ParticleDistribution3D(void) :
    Inherited()
{
}

ParticleDistribution3D::ParticleDistribution3D(const ParticleDistribution3D &source) :
    Inherited(source)
{
}

ParticleDistribution3D::~ParticleDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ParticleDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ParticleDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ParticleDistribution3D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPARTICLEDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPARTICLEDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPARTICLEDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


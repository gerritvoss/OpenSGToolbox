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

#define OSG_COMPILEDYNAMICSLIB

#include <OpenSG/OSGConfig.h>

#include "OSGPerlinNoiseDistribution2D.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PerlinNoiseDistribution2D
A PerlinNoiseDistribution2D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PerlinNoiseDistribution2D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector PerlinNoiseDistribution2D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PERLINNOISE2D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector PerlinNoiseDistribution2D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    InputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PERLINNOISE2D_DIST_INPUTPARAMETERS));
    return InputTypes;
}

FunctionIOParameterVector PerlinNoiseDistribution2D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PERLINNOISE2D_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PERLINNOISE2D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_PERLINNOISE2D_DIST_OUTPUTPARAMETERS, 
		generate(dynamic_cast<const FunctionIOData<Pnt2f>* >(InputParameters[0].getDataPtr())->getData())));

    return ResultVector;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

Real32 PerlinNoiseDistribution2D::generate(Pnt2f t) const
{	
	Real32 total(0.0f), amplitude(getAmplitude()), frequency(getFrequency());
	Pnt2f pos(t + getPhase());
	for(unsigned int i(0); i < getOctaves(); ++i)
	{
		if(i > 0)
		{
		  frequency *= 2;
		  amplitude *= getPersistance();
		}

		total += interpolatedNoise(pos * frequency, i) * amplitude;
	}

	return total;
}

Real32 PerlinNoiseDistribution2D::interpolatedNoise(Pnt2f t, UInt32 & octave) const
{
	Real32 intX(osgfloor(t[0])), intY(osgfloor(t[1]));
	Real32 fractionX = t[0] - intX;
	Real32 fractionY = t[1] - intY;

	Real32 i1(0.0f), i2(0.0f), returnValue(0.0f);
	if(getUseSmoothing())
	{
		if(getInterpolationType() == PerlinNoiseDistribution2D::COSINE)
		{
			i1 = interpolateCosine(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateCosine(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateCosine(i1 , i2 , fractionY);
		}
		else if (getInterpolationType() == PerlinNoiseDistribution2D::LINEAR)
		{
			i1 = interpolateLinear(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateLinear(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateLinear(i1 , i2 , fractionY);
		}
	} else
	{
		if(getInterpolationType() == PerlinNoiseDistribution2D::COSINE)
		{
			i1 = interpolateCosine(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateCosine(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateCosine(i1 , i2 , fractionY);
		}
		else if (getInterpolationType() == PerlinNoiseDistribution2D::LINEAR)
		{
			i1 = interpolateLinear(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateLinear(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateLinear(i1 , i2 , fractionY);
		}
	}

	return returnValue;
}

Real32 PerlinNoiseDistribution2D::smoothNoise(Real32 x, Real32 y, UInt32 & octave) const
{
	Real32 corners = (getNoise(x-1, y-1, octave) + getNoise(x+1, y-1, octave) + getNoise(x-1, y+1, octave) + getNoise(x+1, y+1, octave)) / 16;
	Real32 edges   = (getNoise(x-1, y, octave) + getNoise(x+1, y, octave) + getNoise(x, y-1, octave) + getNoise(x, y+1, octave)) / 8;
	Real32 center  =  getNoise(x, y, octave) / 4;

	return corners + edges + center;
}

Real32 PerlinNoiseDistribution2D::interpolateCosine(Real32 a, Real32 b, Real32 t) const
{	// returns cosine interpolation of t between a and b
	Real32 f = (1 - std::cos(t * 3.1415927)) * .5;
	return  a*(1-f) + b*f;
}

Real32 PerlinNoiseDistribution2D::interpolateLinear(Real32 a, Real32 b, Real32 t) const
{
	return  a*(1-t) + b*t;
}


Real32 PerlinNoiseDistribution2D::getNoise(Int32 t1, Int32 t2, UInt32 & octave) const
{
	Real32 noiseVal(0.0f);
	Int32 n(0);
	switch(octave%6)
	{
		case 0:
			n = t1 + t2*53;
			n = (n<<13) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312579) & 0x7fffffff) / 1073741824.0); 
			break;

		case 1:
			n = t1 + t2*61;
			n = (n<<11) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15683 + 789017) + 1376311273) & 0x7fffffff) / 1073741824.0); 
			break;

		case 2:
			n = t1 + t2*47;
			n = (n<<15) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15733 + 789121) + 1376313067) & 0x7fffffff) / 1073741824.0); 
			break;

		case 3:
			n = t1 + t2*67;
			n = (n<<17) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15761 + 789673) + 1376318989) & 0x7fffffff) / 1073741824.0); 
			break;

		case 4:
			n = t1 + t2*43;
			n = (n<<13) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15787 + 789251) + 1376312689) & 0x7fffffff) / 1073741824.0); 
			break;

		case 5:
			n = t1 + t2*59;
			n = (n<<7) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15667 + 789323) + 1376313793) & 0x7fffffff) / 1073741824.0); 
			break;

	}

	return noiseVal;
}

/*----------------------- constructors & destructors ----------------------*/

PerlinNoiseDistribution2D::PerlinNoiseDistribution2D(void) :
    Inherited()
{
}

PerlinNoiseDistribution2D::PerlinNoiseDistribution2D(const PerlinNoiseDistribution2D &source) :
    Inherited(source)
{
}

PerlinNoiseDistribution2D::~PerlinNoiseDistribution2D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PerlinNoiseDistribution2D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PerlinNoiseDistribution2D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PerlinNoiseDistribution2D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPERLINNOISEDISTRIBUTION2DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPERLINNOISEDISTRIBUTION2DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPERLINNOISEDISTRIBUTION2DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


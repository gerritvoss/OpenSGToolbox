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

#include "OSGPerlinNoiseDistribution3D.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PerlinNoiseDistribution3D
A PerlinNoiseDistribution3D. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PerlinNoiseDistribution3D::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

FunctionIOTypeVector PerlinNoiseDistribution3D::getOutputTypes(FunctionIOTypeVector& InputTypes) const
{
    FunctionIOTypeVector OutputTypes;
    OutputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PERLINNOISE3D_DIST_OUTPUTPARAMETERS));
    return OutputTypes;
}

FunctionIOTypeVector PerlinNoiseDistribution3D::getInputTypes(FunctionIOTypeVector& OutputTypes) const
{
    FunctionIOTypeVector InputTypes;
    InputTypes.push_back(OSG_FUNC_INST_FUNCTIONIOTYPE(0,OSG_PERLINNOISE3D_DIST_INPUTPARAMETERS));
    return InputTypes;
}

FunctionIOParameterVector PerlinNoiseDistribution3D::evaluate(FunctionIOParameterVector& InputParameters)
{
    //The Input Paremeters must be the correct number
    if(InputParameters.size() != OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PERLINNOISE3D_DIST_INPUTPARAMETERS))
    {
        throw FunctionInputException();
    }
    FunctionIOParameterVector ResultVector;
    ResultVector.reserve(OSG_FUNC_IOPARAMETERARRAY_SIZE(OSG_PERLINNOISE3D_DIST_OUTPUTPARAMETERS));
    ResultVector.push_back(OSG_FUNC_INST_FUNCTIONIOPARAMETER(0,OSG_PERLINNOISE3D_DIST_OUTPUTPARAMETERS, 
		generate(dynamic_cast<const FunctionIOData<Pnt3f>* >(InputParameters[0].getDataPtr())->getData())));

    return ResultVector;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

Real32 PerlinNoiseDistribution3D::generate(Pnt3f t) const
{
	
	Real32 total(0.0f), amplitude(getAmplitude()), frequency(getFrequency());
	Pnt3f pos(t + getPhase());
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

Real32 PerlinNoiseDistribution3D::interpolatedNoise(Pnt3f t, UInt32 & octave) const
{
	Real32 intX(osgfloor(t[0])), intY(osgfloor(t[1])), intZ(osgfloor(t[2]));
	Real32 fractionX = t[0] - intX;
	Real32 fractionY = t[1] - intY;
	Real32 fractionZ = t[2] - intZ;

	Real32 v1,v2,v3,v4,v5,v6,v7,v8,i1,i2,i3,i4, returnValue(0.0f);
	
	if(getUseSmoothing())
	{
		v1 = smoothNoise(intX,intY,intZ,octave);
		v2 = smoothNoise(intX + 1.0f,intY,intZ,octave);
		v3 = smoothNoise(intX,intY + 1.0f,intZ,octave);
		v4 = smoothNoise(intX + 1.0f,intY + 1.0f,intZ,octave);
		v5 = smoothNoise(intX,intY,intZ + 1.0f,octave);
		v6 = smoothNoise(intX + 1.0f,intY,intZ + 1.0f,octave);
		v7 = smoothNoise(intX,intY + 1.0f,intZ + 1.0f,octave);
		v8 = smoothNoise(intX + 1.0f,intY + 1.0f,intZ + 1.0f,octave);

		if(getInterpolationType() == PerlinNoiseDistribution3D::COSINE)
		{
			i1 = interpolateCosine(v1,v2,fractionX);
			i2 = interpolateCosine(v3,v4,fractionX);
			i3 = interpolateCosine(v5,v6,fractionX);
			i4 = interpolateCosine(v7,v8,fractionX);

			i1 = interpolateCosine(i1,i2,fractionY);
			i2 = interpolateCosine(i3,i4,fractionY);

			returnValue = interpolateCosine(i1,i2,fractionZ);

		} else if (getInterpolationType() == PerlinNoiseDistribution3D::LINEAR)
		{
			i1 = interpolateLinear(v1,v2,fractionX);
			i2 = interpolateLinear(v3,v4,fractionX);
			i3 = interpolateLinear(v5,v6,fractionX);
			i4 = interpolateLinear(v7,v8,fractionX);

			i1 = interpolateLinear(i1,i2,fractionY);
			i2 = interpolateLinear(i3,i4,fractionY);

			returnValue = interpolateLinear(i1,i2,fractionZ);

		}
	} else
	{
		v1 = getNoise(intX,intY,intZ,octave);
		v2 = getNoise(intX + 1.0f,intY,intZ,octave);
		v3 = getNoise(intX,intY + 1.0f,intZ,octave);
		v4 = getNoise(intX + 1.0f,intY + 1.0f,intZ,octave);
		v5 = getNoise(intX,intY,intZ + 1.0f,octave);
		v6 = getNoise(intX + 1.0f,intY,intZ + 1.0f,octave);
		v7 = getNoise(intX,intY + 1.0f,intZ + 1.0f,octave);
		v8 = getNoise(intX + 1.0f,intY + 1.0f,intZ + 1.0f,octave);

		if(getInterpolationType() == PerlinNoiseDistribution3D::COSINE)
		{
			i1 = interpolateCosine(v1,v2,fractionX);
			i2 = interpolateCosine(v3,v4,fractionX);
			i3 = interpolateCosine(v5,v6,fractionX);
			i4 = interpolateCosine(v7,v8,fractionX);

			i1 = interpolateCosine(i1,i2,fractionY);
			i2 = interpolateCosine(i3,i4,fractionY);

			returnValue = interpolateCosine(i1,i2,fractionZ);

		} else if (getInterpolationType() == PerlinNoiseDistribution3D::LINEAR)
		{
			i1 = interpolateLinear(v1,v2,fractionX);
			i2 = interpolateLinear(v3,v4,fractionX);
			i3 = interpolateLinear(v5,v6,fractionX);
			i4 = interpolateLinear(v7,v8,fractionX);

			i1 = interpolateLinear(i1,i2,fractionY);
			i2 = interpolateLinear(i3,i4,fractionY);

			returnValue = interpolateLinear(i1,i2,fractionZ);
		}
	}

	return returnValue;
}

Real32 PerlinNoiseDistribution3D::interpolateCosine(Real32 a, Real32 b, Real32 t) const
{	
	Real32 f = (1 - std::cos(t * 3.1415927)) * .5;
	return  a*(1-f) + b*f;
}

Real32 PerlinNoiseDistribution3D::interpolateLinear(Real32 a, Real32 b, Real32 t) const
{
	return  a*(1-t) + b*t;
}

Real32 PerlinNoiseDistribution3D::smoothNoise(Real32 x, Real32 y, Real32 z, UInt32 & octave) const
{	// averages out the values from the corners, center of the sides, and the center of a 1x1 cube, centered @ (x,y,z)
	// where each side weighs 1/24, each corner weighs 1/16, and the center weighs 1/4.
	Real32 center = getNoise(x,y,z,octave)/4;
	
	Real32 corners = (getNoise(x+1,y-1,z-1,octave) + getNoise(x-1,y-1,z-1,octave) + getNoise(x+1,y+1,z-1,octave) + getNoise(x-1,y+1,z-1,octave) 
					+ getNoise(x+1,y-1,z+1,octave) + getNoise(x-1,y-1,z+1,octave) + getNoise(x+1,y+1,z+1,octave) + getNoise(x-1,y+1,z+1,octave))/16;
	
	Real32 sides = (getNoise(x+1,y,z,octave) + getNoise(x-1,y,z,octave) + getNoise(x,y+1,z,octave) 
					+ getNoise(x,y-1,z,octave) + getNoise(x,y,z+1,octave) + getNoise(x,y,z-1,octave))/24;
		
	return center + corners + sides;
}

Real32 PerlinNoiseDistribution3D::getNoise(Int32 t1, Int32 t2, Int32 t3, UInt32 & octave) const
{
		Real32 noiseVal(0.0f);
	Int32 n(0);
	switch(octave%6)
	{
		case 0:
			n = t1*23 + t2*53 + t3*31;
			n = (n<<13) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15731 + 789221) + 1376312579) & 0x7fffffff) / 1073741824.0); 
			break;

		case 1:
			n = t1*71 + t2*53 + t3*3;
			n = (n<<11) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15683 + 789017) + 1376311273) & 0x7fffffff) / 1073741824.0); 
			break;

		case 2:
			n = t1 + t2*47 - t3*17;
			n = (n<<15) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15733 + 789121) + 1376313067) & 0x7fffffff) / 1073741824.0); 
			break;

		case 3:
			n = t1*29 + t2*67 - t3*61;
			n = (n<<17) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15761 + 789673) + 1376318989) & 0x7fffffff) / 1073741824.0); 
			break;

		case 4:
			n = t1 + t2*43 + t3*11;
			n = (n<<13) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15787 + 789251) + 1376312689) & 0x7fffffff) / 1073741824.0); 
			break;

		case 5:
			n = t1*17 + t2*59 + t3;
			n = (n<<7) ^ n;
			noiseVal = ( 1.0 - ( (n * (n * n * 15667 + 789323) + 1376313793) & 0x7fffffff) / 1073741824.0); 
			break;

	}

	return noiseVal;
}



/*----------------------- constructors & destructors ----------------------*/

PerlinNoiseDistribution3D::PerlinNoiseDistribution3D(void) :
    Inherited()
{
}

PerlinNoiseDistribution3D::PerlinNoiseDistribution3D(const PerlinNoiseDistribution3D &source) :
    Inherited(source)
{
}

PerlinNoiseDistribution3D::~PerlinNoiseDistribution3D(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PerlinNoiseDistribution3D::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PerlinNoiseDistribution3D::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PerlinNoiseDistribution3D NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGPERLINNOISEDISTRIBUTION3DBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPERLINNOISEDISTRIBUTION3DBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPERLINNOISEDISTRIBUTION3DFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
#include "OSGPerlinNoise.h"

OSG_BEGIN_NAMESPACE


Real32 calcPerlinNoise(Real32 t, Real32 Amplitude, Real32 Frequency, Real32 Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType, bool Smoothing)
{
	Real32 total(0.0f), amplitude(Amplitude), frequency(Frequency), pos(t + Phase);
	
	for(unsigned int i(0); i < Octaves; ++i)
	{
		if(i > 0)
		{
		  frequency *= 2.0f;
		  amplitude *= Persistance;
		}

		total += interpolatedNoise(pos * frequency, i, InterpolationType, Smoothing) * amplitude;
	}

	return total;
}


Real32 interpolateCosine(Real32 a, Real32 b, Real32 t)
{	// returns cosine interpolation of t between a and b
	Real32 f = (1 - std::cos(t * 3.1415927f)) * .5f;
	return  a*(1.0f-f) + b*f;
}

Real32 interpolateLinear(Real32 a, Real32 b, Real32 t)
{
	return  a*(1.0f-t) + b*t;
}

Real32 interpolatedNoise(Real32 t, UInt32 octave, UInt32 InterpolationType, bool Smoothing)
{
	Real32 intT(osgfloor(t));
	Real32 fractionT = t - intT;
	Real32 v1,v2;
	if(Smoothing)
	{
		v1 = getNoise(intT,octave)/2.0f + getNoise(intT - 1.0f, octave)/4.0f + getNoise(intT + 1.0f, octave)/4.0f;
		intT += 1.0f;
		v2 = getNoise(intT,octave)/2.0f + getNoise(intT - 1.0f, octave)/4.0f + getNoise(intT + 1.0f, octave)/4.0f;
	} else
	{
		v1 = getNoise(intT,octave);
		v2 = getNoise(intT + 1.0f,octave);
	}

	Real32 returnValue(0.0);
	if(InterpolationType == PERLIN_INTERPOLATE_COSINE) returnValue = interpolateCosine(v1 , v2 , fractionT);
	else if(InterpolationType == PERLIN_INTERPOLATE_LINEAR) returnValue = interpolateLinear(v1 , v2 , fractionT);
	
	return returnValue;
}

Real32 getNoise(Int32 t, UInt32 octave)
{
	Real32 noiseVal(0.0f);
	switch(octave%6)
	{
		case 0:
			t = (t<<13) ^ t;
			noiseVal = ( 1.0 - ( (t * (t * t * 15731 + 789221) + 1376312579) & 0x7fffffff) / 1073741824.0); 
			break;

		case 1:
			t = (t<<11) ^ t;
			noiseVal = ( 1.0 - ( (t * (t * t * 15683 + 789017) + 1376311273) & 0x7fffffff) / 1073741824.0); 
			break;

		case 2:
			t = (t<<15) ^ t;
			noiseVal = ( 1.0 - ( (t * (t * t * 15733 + 789121) + 1376313067) & 0x7fffffff) / 1073741824.0); 
			break;

		case 3:
			t = (t<<17) ^ t;
			noiseVal = ( 1.0 - ( (t * (t * t * 15761 + 789673) + 1376318989) & 0x7fffffff) / 1073741824.0); 
			break;

		case 4:
			t = (t<<13) ^ t;
			noiseVal = ( 1.0 - ( (t * (t * t * 15787 + 789251) + 1376312689) & 0x7fffffff) / 1073741824.0); 
			break;

		case 5:
			t = (t<<7) ^ t;
			noiseVal = ( 1.0 - ( (t * (t * t * 15667 + 789323) + 1376313793) & 0x7fffffff) / 1073741824.0); 
			break;

	}

	return noiseVal;
}

Real32 calcPerlinNoise(const Pnt2f& t, Real32 Amplitude, Real32 Frequency, Real32 Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType, bool Smoothing)
{	
	Real32 total(0.0f), amplitude(Amplitude), frequency(Frequency);
	Pnt2f pos(t + Phase);
	for(unsigned int i(0); i < Octaves; ++i)
	{
		if(i > 0)
		{
		  frequency *= 2;
		  amplitude *= Persistance;
		}

		total += interpolatedNoise(pos * frequency, i, InterpolationType, Smoothing) * amplitude;
	}

	return total;
}

Real32 interpolatedNoise(const Pnt2f& t, UInt32 & octave, UInt32 InterpolationType, bool Smoothing)
{
	Real32 intX(osgfloor(t[0])), intY(osgfloor(t[1]));
	Real32 fractionX = t[0] - intX;
	Real32 fractionY = t[1] - intY;

	Real32 i1(0.0f), i2(0.0f), returnValue(0.0f);
	if(Smoothing)
	{
		if(InterpolationType == PERLIN_INTERPOLATE_COSINE)
		{
			i1 = interpolateCosine(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateCosine(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateCosine(i1 , i2 , fractionY);
		}
		else if (InterpolationType == PERLIN_INTERPOLATE_LINEAR)
		{
			i1 = interpolateLinear(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateLinear(smoothNoise(intX, intY, octave),smoothNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateLinear(i1 , i2 , fractionY);
		}
	} else
	{
		if(InterpolationType == PERLIN_INTERPOLATE_COSINE)
		{
			i1 = interpolateCosine(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateCosine(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateCosine(i1 , i2 , fractionY);
		}
		else if (InterpolationType == PERLIN_INTERPOLATE_LINEAR)
		{
			i1 = interpolateLinear(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			intY += 1.0f;
			i2 = interpolateLinear(getNoise(intX, intY, octave),getNoise(intX + 1.0f, intY, octave), fractionX);
			returnValue = interpolateLinear(i1 , i2 , fractionY);
		}
	}

	return returnValue;
}

Real32 smoothNoise(Real32 x, Real32 y, UInt32 & octave)
{
	Real32 corners = (getNoise(x-1, y-1, octave) + getNoise(x+1, y-1, octave) + getNoise(x-1, y+1, octave) + getNoise(x+1, y+1, octave)) / 16;
	Real32 edges   = (getNoise(x-1, y, octave) + getNoise(x+1, y, octave) + getNoise(x, y-1, octave) + getNoise(x, y+1, octave)) / 8;
	Real32 center  =  getNoise(x, y, octave) / 4;

	return corners + edges + center;
}

Real32 getNoise(Int32 t1, Int32 t2, UInt32 & octave)
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

Real32 calcPerlinNoise(const Pnt3f& t, Real32 Amplitude, Real32 Frequency, Real32 Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType, bool Smoothing)
{
	
	Real32 total(0.0f), amplitude(Amplitude), frequency(Frequency);
	Pnt3f pos(t + Phase);
	for(unsigned int i(0); i < Octaves ; ++i)
	{
		if(i > 0)
		{
		  frequency *= 2;
		  amplitude *= Persistance;
		}

		total += interpolatedNoise(pos * frequency, i, InterpolationType,Smoothing) * amplitude;
	}

	return total;
}

Real32 interpolatedNoise(const Pnt3f& t, UInt32 & octave, UInt32 InterpolationType, bool Smoothing)
{
	Real32 intX(osgfloor(t[0])), intY(osgfloor(t[1])), intZ(osgfloor(t[2]));
	Real32 fractionX = t[0] - intX;
	Real32 fractionY = t[1] - intY;
	Real32 fractionZ = t[2] - intZ;

	Real32 v1,v2,v3,v4,v5,v6,v7,v8,i1,i2,i3,i4, returnValue(0.0f);
	
	if(Smoothing)
	{
		v1 = smoothNoise(intX,intY,intZ,octave);
		v2 = smoothNoise(intX + 1.0f,intY,intZ,octave);
		v3 = smoothNoise(intX,intY + 1.0f,intZ,octave);
		v4 = smoothNoise(intX + 1.0f,intY + 1.0f,intZ,octave);
		v5 = smoothNoise(intX,intY,intZ + 1.0f,octave);
		v6 = smoothNoise(intX + 1.0f,intY,intZ + 1.0f,octave);
		v7 = smoothNoise(intX,intY + 1.0f,intZ + 1.0f,octave);
		v8 = smoothNoise(intX + 1.0f,intY + 1.0f,intZ + 1.0f,octave);

		if(InterpolationType == PERLIN_INTERPOLATE_COSINE)
		{
			i1 = interpolateCosine(v1,v2,fractionX);
			i2 = interpolateCosine(v3,v4,fractionX);
			i3 = interpolateCosine(v5,v6,fractionX);
			i4 = interpolateCosine(v7,v8,fractionX);

			i1 = interpolateCosine(i1,i2,fractionY);
			i2 = interpolateCosine(i3,i4,fractionY);

			returnValue = interpolateCosine(i1,i2,fractionZ);

		} else if (InterpolationType == PERLIN_INTERPOLATE_LINEAR)
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

		if(InterpolationType == PERLIN_INTERPOLATE_COSINE)
		{
			i1 = interpolateCosine(v1,v2,fractionX);
			i2 = interpolateCosine(v3,v4,fractionX);
			i3 = interpolateCosine(v5,v6,fractionX);
			i4 = interpolateCosine(v7,v8,fractionX);

			i1 = interpolateCosine(i1,i2,fractionY);
			i2 = interpolateCosine(i3,i4,fractionY);

			returnValue = interpolateCosine(i1,i2,fractionZ);

		} else if (InterpolationType == PERLIN_INTERPOLATE_LINEAR)
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

Real32 smoothNoise(Real32 x, Real32 y, Real32 z, UInt32 octave)
{	// averages out the values from the corners, center of the sides, and the center of a 1x1 cube, centered @ (x,y,z)
	// where each side weighs 1/24, each corner weighs 1/16, and the center weighs 1/4.
	Real32 center = getNoise(x,y,z,octave)/4;
	
	Real32 corners = (getNoise(x+1,y-1,z-1,octave) + getNoise(x-1,y-1,z-1,octave) + getNoise(x+1,y+1,z-1,octave) + getNoise(x-1,y+1,z-1,octave) 
					+ getNoise(x+1,y-1,z+1,octave) + getNoise(x-1,y-1,z+1,octave) + getNoise(x+1,y+1,z+1,octave) + getNoise(x-1,y+1,z+1,octave))/16;
	
	Real32 sides = (getNoise(x+1,y,z,octave) + getNoise(x-1,y,z,octave) + getNoise(x,y+1,z,octave) 
					+ getNoise(x,y-1,z,octave) + getNoise(x,y,z+1,octave) + getNoise(x,y,z-1,octave))/24;
		
	return center + corners + sides;
}

Real32 getNoise(Int32 t1, Int32 t2, Int32 t3, UInt32 octave)
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

ImagePtr createPerlinImage(const Vec2s& Size, const Vec2f& Range, Real32 Amplitude, Real32 Frequency, Real32 Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType, bool Smoothing, Image::PixelFormat pixelformat, Image::Type  type)
{
	ImagePtr PerlinImage = Image::create();

	std::vector<Real32> ImageData(Size.x() * Size.y());

	bool shouldTranslate(false);
	
	switch(type)
	{
	case Image::OSG_UINT8_IMAGEDATA:
	case Image::OSG_UINT16_IMAGEDATA:
	case Image::OSG_UINT32_IMAGEDATA:
		shouldTranslate = true;
		break;
	default:
		shouldTranslate = false;
		break;
	}

	for(UInt32 i(0) ; i<Size.x() ; ++i)
	{
		for(UInt32 j(0) ; j<Size.y() ; ++j)
		{
			ImageData[i*Size.x()+j] = osgClamp(-0.5f, calcPerlinNoise(Pnt2f(Range.x()*static_cast<Real32>(i)/static_cast<Real32>(Size.x()), Range.y()*static_cast<Real32>(j)/static_cast<Real32>(Size.y())),
				Amplitude,
				Frequency,
				Phase,
				Persistance,
				Octaves,
				InterpolationType,
				Smoothing),0.5f);

			if(shouldTranslate)
			{
				ImageData[i*Size.x()+j] += 0.5f;

			}
		}
	}

	if(PerlinImage->set(Image::OSG_I_PF, Size.x(), Size.y(),1,1,1,0.0f,reinterpret_cast<UInt8*>(&ImageData[0]),Image::OSG_FLOAT32_IMAGEDATA))
	{
		if(type != Image::OSG_FLOAT32_IMAGEDATA)
		{
			if(!PerlinImage->convertDataTypeTo(type))
			{
				return NullFC;
			}
		}

		if(pixelformat != Image::OSG_I_PF)
		{
			if(!PerlinImage->reformat(pixelformat))
			{
				return NullFC;
			}
		}

		return PerlinImage;
	}
	else
	{
		return NullFC;
	}
}


ImagePtr createPerlinImage(const Vec3s& Size, const Vec3f& Range, Real32 Amplitude, Real32 Frequency, Real32 Phase, Real32 Persistance, UInt32 Octaves, UInt32 InterpolationType, bool Smoothing, Image::PixelFormat pixelformat, Image::Type  type)
{
	ImagePtr PerlinImage = Image::create();

	std::vector<Real32> ImageData(Size.x() * Size.y() * Size.z());

	bool shouldTranslate(false);
	
	switch(type)
	{
	case Image::OSG_UINT8_IMAGEDATA:
	case Image::OSG_UINT16_IMAGEDATA:
	case Image::OSG_UINT32_IMAGEDATA:
		shouldTranslate = true;
		break;
	default:
		shouldTranslate = false;
		break;
	}

	for(UInt32 i(0) ; i<Size.x() ; ++i)
	{
		for(UInt32 j(0) ; j<Size.y() ; ++j)
		{
			for(UInt32 k(0) ; k<Size.z() ; ++k)
			{
				ImageData[i*Size.x()*Size.y()+j*Size.y()+k] = osgClamp(-0.5f, 
					calcPerlinNoise(Pnt2f(Range.x()*static_cast<Real32>(i)/static_cast<Real32>(Size.x()), Range.y()*static_cast<Real32>(j)/static_cast<Real32>(Size.y()), Range.z()*static_cast<Real32>(k)/static_cast<Real32>(Size.z())),
						Amplitude,
						Frequency,
						Phase,
						Persistance,
						Octaves,
						InterpolationType,
						Smoothing),
					0.5f);

				if(shouldTranslate)
				{
					ImageData[i*Size.x()*Size.y()+j*Size.y()+k] += 0.5f;

				}
			}
		}
	}

	if(PerlinImage->set(Image::OSG_I_PF, Size.x(), Size.y(),1,1,1,0.0f,reinterpret_cast<UInt8*>(&ImageData[0]),Image::OSG_FLOAT32_IMAGEDATA))
	{
		if(type != Image::OSG_FLOAT32_IMAGEDATA)
		{
			if(!PerlinImage->convertDataTypeTo(type))
			{
				return NullFC;
			}
		}

		if(pixelformat != Image::OSG_I_PF)
		{
			if(!PerlinImage->reformat(pixelformat))
			{
				return NullFC;
			}
		}

		return PerlinImage;
	}
	else
	{
		return NullFC;
	}
}
OSG_END_NAMESPACE


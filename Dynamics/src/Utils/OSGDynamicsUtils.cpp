#include "OSGDynamicsUtils.h"

#include <OpenSG/OSGBaseFunctions.h>

OSG_BEGIN_NAMESPACE


UInt32 stlBinarySearch(std::vector<Real32> vector, UInt32 lowerBound, UInt32 upperBound, Real32 value)
{
	UInt32 hi, mid, lo;
	hi = upperBound;
	lo = lowerBound;
	mid = (lo + hi) / 2;
	
	if(lo == hi)
	{
		return -1;
	}
	
	if (value == vector[mid])
	{
		return mid;
	}
	else
	{
		if (value < vector[mid])
		{
			return stlBinarySearch(vector, lo, mid - 1, value);
		}
		else
		{
			return stlBinarySearch(vector, mid, hi, value);
		}
	}
}

UInt32 stlLowerBound(std::vector<Real32> vector, UInt32 lowerBound, UInt32 upperBound, Real32 value)
{
	UInt32 hi, mid, lo;
	hi = upperBound;
	lo = lowerBound;
	mid = static_cast<UInt32>(osgceil(static_cast<Real32>(lo + hi) / 2.0f));
	
	if (lo == hi)
	{
		return mid;
	}
	
	if (value >= vector[mid])
	{
			return stlLowerBound(vector, mid, hi, value);
	}
	else
	{
		return stlLowerBound(vector, lo, mid - 1, value);
	}
}

OSG_END_NAMESPACE


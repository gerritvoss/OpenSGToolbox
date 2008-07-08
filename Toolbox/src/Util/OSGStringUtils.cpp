#include "OSGStringUtils.h"
#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE


std::string addStringBetweenUpperCaseChange(const std::string& Source, const std::string& Pad)
{
	std::string Result(Source);
	
	for (UInt32 i(0); i < Result.size() - 2; ++i)
	{
		if ((97 <= Result[i] && Result[i] <= 122) && (65 <= Result[i + 1] && Result[i + 1] <= 90))
		{
			Result.insert(i+1, Pad);
		}
	}
	
	return Result;
}

OSG_END_NAMESPACE


#ifndef _OPENSG_DYNAMICS_UTILS_H_
#define _OPENSG_DYNAMICS_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGDynamicsDef.h"
#include <OpenSG/OSGBaseTypes.h>
#include <vector>

OSG_BEGIN_NAMESPACE


UInt32 OSG_DYNAMICSLIB_DLLMAPPING stlBinarySearch(std::vector<Real32> vector, UInt32 lowerBound, UInt32 upperBound, Real32 value);
UInt32 OSG_DYNAMICSLIB_DLLMAPPING stlLowerBound(std::vector<Real32> vector, UInt32 lowerBound, UInt32 upperBound, Real32 value);

std::string OSG_DYNAMICSLIB_DLLMAPPING addStringBetweenUpperCaseChange(const std::string& Source, const std::string& Pad);

OSG_END_NAMESPACE

#endif

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


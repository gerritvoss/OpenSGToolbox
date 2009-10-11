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
#include "OSGTextUtils.h"
#include <OpenSG/OSGBaseTypes.h>
#include <sstream>

OSG_BEGIN_NAMESPACE

void getLine(const std::string& Text, UInt32 TextPos, Int32& LineNumber, Int32& LineStartPos)
{
    std::istringstream InStream(Text);

    std::string Line;
    LineNumber = 1;
    LineStartPos = 0;
    while(std::getline(InStream, Line) && TextPos > LineStartPos+Line.size())
    {
        LineStartPos += Line.size() + 1;
        ++LineNumber;
    }
}

OSG_END_NAMESPACE


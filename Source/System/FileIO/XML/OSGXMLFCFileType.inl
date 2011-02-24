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
#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

inline 
void XMLFCFileType::operator =(const XMLFCFileType& source)
{
	SWARNING << "In XMLFCFileType operator =" << std::endl;
}

inline 
std::pair<XMLFCFileType::BasicFCIdMapper::MapType::iterator, bool> XMLFCFileType::BasicFCIdMapper::insert(const MapType::value_type& x)
{
    return _IdMap.insert(x);
}

inline 
XMLFCFileType::BasicFCIdMapper::MapType::size_type XMLFCFileType::BasicFCIdMapper::erase(const MapType::key_type& k)
{
    return _IdMap.erase(k);
}

OSG_END_NAMESPACE

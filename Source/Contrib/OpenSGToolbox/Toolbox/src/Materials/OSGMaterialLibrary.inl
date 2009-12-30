/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                Authors: David Kabala, Daniel Guilliams                    *
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

#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE


inline
UInt32 MaterialLibrary::getNumMaterials(void) const
{
	return _Materials.size();
}

inline
UInt32 MaterialLibrary::getNumFuncMaterials(void) const
{
	return _MaterialFuncs.size();
}

inline
MaterialLibrary::MaterialMapConstItor MaterialLibrary::getMaterialBeginItor(void) const
{
	return _Materials.begin();
}

inline
MaterialLibrary::MaterialMapConstItor MaterialLibrary::getMaterialEndItor(void) const
{
	return _Materials.end();
}

inline
MaterialLibrary::MaterialFunctionMapConstItor MaterialLibrary::getMaterialFunctionBeginItor(void) const
{
	return _MaterialFuncs.begin();
}

inline
MaterialLibrary::MaterialFunctionMapConstItor MaterialLibrary::getMaterialFunctionEndItor(void) const
{
	return _MaterialFuncs.end();
}

OSG_END_NAMESPACE




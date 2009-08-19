/*---------------------------------------------------------------------------*\
 *                             OpenSG Toolbox                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                 Authors: David Kabala, Daniel Guilliams                   *
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
#include <OpenSG/OSGSimpleMaterial.h>

#include "OSGMaterialLibrary.h"

OSG_USING_NAMESPACE



MaterialLibrary *MaterialLibrary::_the = NULL;

MaterialLibrary *MaterialLibrary::the(void)
{
    if(_the == NULL)
        _the = new MaterialLibrary;

    return _the;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MaterialLibrary::MaterialLibrary(void)
{
}
    
/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MaterialLibrary::~MaterialLibrary(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */


/*==========================  PUBLIC  =================================*/


bool MaterialLibrary::addMaterial(const std::string& MaterialName, MaterialPtr TheMaterial)
{
	std::pair<std::string, MaterialPtr> materialToAdd(MaterialName, TheMaterial);
	std::pair<MaterialMapItor, bool> returnPair = _Materials.insert(materialToAdd);
	
	return returnPair.second;
}

bool MaterialLibrary::removeMaterial(const std::string& MaterialName)
{
	bool removed(false);
	MaterialMapItor Itor = _Materials.find(MaterialName);

	if(Itor != _Materials.end())
	{
		_Materials.erase(Itor);
		removed = true;
	}
	
	return removed;
}

// TODO: rework this function
MaterialPtr MaterialLibrary::getMaterial(const std::string& MaterialName) const
{
	MaterialMapConstItor MatItor = _Materials.find(MaterialName);
	if(MatItor != _Materials.end())
	{
		return (*MatItor).second;
	}

	return NullFC;
}

bool MaterialLibrary::addMaterialFunction(const std::string& MaterialName, MaterialFunction TheMaterialFunction)
{
	std::pair<std::string, MaterialFunction> materialToAdd(MaterialName, TheMaterialFunction);
	std::pair<MaterialFunctionMapItor, bool> returnPair = _MaterialFuncs.insert(materialToAdd);
	
	return returnPair.second;
}

bool MaterialLibrary::removeMaterialFunction(const std::string& MaterialName)
{
	bool removed(false);
	MaterialFunctionMapItor Itor = _MaterialFuncs.find(MaterialName);

	if(Itor != _MaterialFuncs.end())
	{
		_MaterialFuncs.erase(Itor);
		removed = true;
	}
	
	return removed;
}


MaterialLibrary::MaterialFunction MaterialLibrary::getMaterialFunction(const std::string& MaterialName) const
{
	MaterialFunctionMapConstItor FuncItor = _MaterialFuncs.find(MaterialName);

	if(FuncItor != _MaterialFuncs.end())
	{
		return (*FuncItor).second;
	}

	return MaterialFunction(); 
}

MaterialPtr MaterialLibrary::createMaterial(const std::string& MaterialName) const
{
	MaterialMapConstItor MatItor = _Materials.find(MaterialName);

	if(MatItor != _Materials.end())
	{
		return (*MatItor).second;
	}

	MaterialFunctionMapConstItor FuncItor = _MaterialFuncs.find(MaterialName);

	if(FuncItor != _MaterialFuncs.end())
	{
		MaterialFunction f = (*FuncItor).second;
		return f();
	}

	return NullFC; 
}


bool MaterialLibrary::isDefined(const std::string& MaterialName) const
{ // check if material is defined in either map
	bool defined(false);
	
	MaterialMapConstItor MatItor = _Materials.find(MaterialName);

	if(MatItor != _Materials.end())
	{
		defined = true;
	}

	MaterialFunctionMapConstItor FuncItor = _MaterialFuncs.find(MaterialName);

	if(!defined && FuncItor != _MaterialFuncs.end())
	{
		defined = true;
	}

	return defined; 
}


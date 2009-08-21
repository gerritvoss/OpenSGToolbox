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

#ifndef _OSGMATERIAL_LIBRARY_H_
#define _OSGMATERIAL_LIBRARY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"
#include <OpenSG/OSGMaterial.h>
#include <boost/function.hpp>


OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING MaterialLibrary 
{
    /*==========================  PUBLIC  =================================*/

  public :
	typedef boost::function<MaterialPtr (void)> MaterialFunction;
	
	typedef std::map<std::string, MaterialPtr> MaterialMap;
	typedef std::map<std::string, MaterialPtr>::iterator MaterialMapItor;
	typedef std::map<std::string, MaterialPtr>::const_iterator MaterialMapConstItor;

	typedef std::map<std::string, MaterialFunction> MaterialFunctionMap;
	typedef std::map<std::string, MaterialFunction>::iterator MaterialFunctionMapItor;
	typedef std::map<std::string, MaterialFunction>::const_iterator MaterialFunctionMapConstItor;

    static MaterialLibrary *the(void);

	bool addMaterial(const std::string& MaterialName, MaterialPtr TheMaterial);
	bool removeMaterial(const std::string& MaterialName);
	MaterialPtr getMaterial(const std::string& MaterialName) const;
	UInt32 getNumMaterials(void) const;

	bool addMaterialFunction(const std::string& MaterialName, MaterialFunction TheMaterialFunction);
	bool removeMaterialFunction(const std::string& MaterialName);
	MaterialFunction getMaterialFunction(const std::string& MaterialName) const;
	UInt32 getNumFuncMaterials(void) const;

	MaterialMapConstItor getMaterialBeginItor(void) const;
	MaterialMapConstItor getMaterialEndItor(void) const;

	MaterialFunctionMapConstItor getMaterialFunctionBeginItor(void) const;
	MaterialFunctionMapConstItor getMaterialFunctionEndItor(void) const;

	MaterialPtr createMaterial(const std::string& MaterialName) const;
	bool isDefined(const std::string& MaterialName) const;

    /*=========================  PROTECTED  ===============================*/

  protected:
    MaterialLibrary(void);
    
    /*---------------------------------------------------------------------*/
    virtual ~MaterialLibrary(void);
    
    static MaterialLibrary   *_the;

	MaterialMap _Materials; 
	std::map<std::string, MaterialFunction> _MaterialFuncs; 
    
    /*==========================  PRIVATE  ================================*/
  private:
    MaterialLibrary(const MaterialLibrary &source);
    void operator =(const MaterialLibrary &source);
};

typedef MaterialLibrary *MaterialLibraryP;

OSG_END_NAMESPACE

#include "OSGMaterialLibrary.inl"

#endif /* _OSGMATERIAL_LIBRARY_H_ */

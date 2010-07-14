/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEUSERINTERFACELIB

#include "OSGConfig.h"

#include "OSGColladaFCFileType.h"

#include "OSGColladaGlobal.h"
<<<<<<< HEAD
#include "OSGImageFileHandler.h"
=======
>>>>>>> 3cb0bb4abf2dfbc5a107cbc860389880f6a65bab

OSG_BEGIN_NAMESPACE

/*----------------------- constructors & destructors ----------------------*/

ColladaFCFileType::ColladaFCFileType(void) : Inherited(FCFileType::ExtensionVector(1, std::string("dae")),
        false,
        50,
        FCFileType::OSG_READ_SUPPORTED)
{
}

<<<<<<< HEAD
ColladaFCFileType::ColladaFCFileType(const ColladaFCFileType &obj) 
		: Inherited(obj)
=======
ColladaFCFileType::ColladaFCFileType(const ColladaFCFileType &obj) : Inherited(obj)
>>>>>>> 3cb0bb4abf2dfbc5a107cbc860389880f6a65bab
{
}

ColladaFCFileType::~ColladaFCFileType(void)
{
}

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::XMLFCFileType
A XMLFCFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

<<<<<<< HEAD
ColladaFCFileType*  ColladaFCFileType::_the(new ColladaFCFileType());
=======

>>>>>>> 3cb0bb4abf2dfbc5a107cbc860389880f6a65bab

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

 
 /*---------------------------------------------------------------------*/
ColladaFCFileType::FCPtrStore ColladaFCFileType::read(std::istream &is,
	                     const std::string& fileNameOrExtension) const
{
	ColladaGlobal::ObjTransitPtr colladaReader = ColladaGlobal::create();
<<<<<<< HEAD
	ColladaOptionsRefPtr colOpts   = ColladaOptions::create();
	colOpts->setInvertTransparency(false);
	colOpts->setCreateNameAttachments(false);
	colOpts->setFlattenNodeXForms(false);
	colOpts->setReadAnimations(true);
	colladaReader->setOptions(colOpts);

	//NodeTransitPtr colRoot = colladaReader->read(is,fileNameOrExtension);
	//FCPtrStore store;
	//store.insert(colRoot);
	//return store;
	
	return colladaReader->readAll(is,fileNameOrExtension);
=======
	NodeTransitPtr colRoot = colladaReader->read(is,fileNameOrExtension);
	FCPtrStore store;
	store.insert(colRoot);
	return store;
>>>>>>> 3cb0bb4abf2dfbc5a107cbc860389880f6a65bab
}

 /*---------------------------------------------------------------------*/

bool ColladaFCFileType::write(const FCPtrStore &Containers, std::ostream &os,
                    const std::string& fileNameOrExtension, const FCTypeVector& IgnoreTypes) const
{
	SWARNING << "In ColladaFCFileType: Write support for COLLADA files NIY." << std::endl;
	return false;
}


std::string ColladaFCFileType::getName(void) const
{
	return std::string("ColladaFCFileType");
}

<<<<<<< HEAD


=======
>>>>>>> 3cb0bb4abf2dfbc5a107cbc860389880f6a65bab
OSG_END_NAMESPACE


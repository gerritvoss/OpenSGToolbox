/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <OpenSG/OSGConfig.h>

#include "OSGBinFCFileType.h"
#include "OSGFCFileHandler.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::BinFCFileType
A BinFCFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

BinFCFileType*  BinFCFileType::_the(new BinFCFileType());

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

BinFCFileType *BinFCFileType::the(void)
{
	return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string BinFCFileType::getName(void) const
{
	return std::string("BinFCFileType");
}

 BinFCFileType::FCPtrStore BinFCFileType::read(std::istream &is,
	                     const std::string& fileNameOrExtension) const
{
	FCPtrStore Result;

	return Result;
}

 bool BinFCFileType::write(const FCPtrStore &Containers, std::ostream &os,
                    const std::string& fileNameOrExtension) const
 {

	return false;
 }
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

BinFCFileType::BinFCFileType(void) : Inherited(FCFileType::ExtensionVector(1, std::string("fcb")), FCFileType::OSG_READ_SUPPORTED | FCFileType::OSG_WRITE_SUPPORTED)
{
}

BinFCFileType::BinFCFileType(const BinFCFileType &obj) : Inherited(obj)
{
}

BinFCFileType::~BinFCFileType(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE


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

#include "OSGFCFileType.h"
#include "OSGFCFileHandler.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FCFileType
A FCFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

 FCFileType::FCPtrStore FCFileType::read(std::istream &is,
	                     const std::string& fileNameOrExtension) const
{
	FWARNING (("STREAM INTERFACE NOT IMPLEMENTED!\n"));
	FCPtrStore Result;

	return Result;
}

 bool FCFileType::write(const FCPtrStore &Containers, std::ostream &os,
                    const std::string& fileNameOrExtension) const
 {
	FWARNING (("STREAM INTERFACE NOT IMPLEMENTED!\n"));

	return false;
 }
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FCFileType::FCFileType(const ExtensionVector  suffixArray,
                 //bool    override,
                 //UInt32  overridePriority,
				 UInt32  flags) : _SuffixList(suffixArray),
				 _Flags(flags)
{
	SINFO << "Init " << _SuffixList.front() << " Field Container File Type " << std::endl;

	FCFileHandler::addFCFileType(FCFileTypeP(this));
}

FCFileType::FCFileType(const FCFileType &obj)
{
	SWARNING << "In FCFileType copy constructor" << std::endl;
}

FCFileType::~FCFileType(void)
{
	FCFileHandler::subFCFileType(FCFileTypeP(this));
}

/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


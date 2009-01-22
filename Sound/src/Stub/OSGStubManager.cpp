/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILESOUNDLIB

#include <OpenSG/OSGConfig.h>

#include "OSGStubManager.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StubManager
A Stub SoundManager Interface.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StubManager::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StubManager::StubManager(void) :
    Inherited()
{
}

StubManager::StubManager(const StubManager &source) :
    Inherited(source)
{
}

StubManager::~StubManager(void)
{
}


/**
	* default initialization with out loading the .FEV file, 
	* to load .FEV and set the path to the file and .FSB file
	* typical use: init(const char* mediaPath, const char* mediaFile, const int maxChannel);
	*/
void StubManager::init(const char* arg, ...){}

	/**
	* release the fmod eventsystem object
	*/
void StubManager::uninit(void){}

	/**
	* create and return an Fmod event wrapper object found in the .FEV and .FSB file
	* @param path, the path in the .FEV file to locate the specific FMod event instance
	*/
SoundPtr StubManager::getSound(const char* name){
	return (SoundPtr)NULL;
}

	/**
	* create and return an Fmod event wrapper object found in the .FEV and .FSB file
	* @param id, id from the Fmod designer, which can be found in the optional output .h and text file
	*/
SoundPtr StubManager::getSound(const int id){
	return (SoundPtr)NULL;
}
	

void StubManager::update(const Real32& elps){}

/*----------------------------- class specific ----------------------------*/

void StubManager::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void StubManager::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump StubManager NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGSTUBMANAGERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSTUBMANAGERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSTUBMANAGERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


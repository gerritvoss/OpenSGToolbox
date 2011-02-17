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

#define OSG_COMPILETEXTDOMLIB

#include "OSGConfig.h"

#include "OSGSyntaxHighlighter.h"

#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::SyntaxHighlighterBase
A SyntaxHighlighterBase. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_SINGLETON_INST(SyntaxHighlighterBase, addPostFactoryExitFunction)

template class SingletonHolder<SyntaxHighlighterBase>;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


std::vector<UInt32> SyntaxHighlighterBase::processInput(std::string inputString)
{
	std::vector<UInt32> indices;
	UInt32 index = 0;
	std::istringstream iss(inputString);
	std::string theString;
	while(iss>>theString)
	{
		if(theKeywordsList.isKeyword(theString))
		{
			UInt32 loc = inputString.find( theString, index );
			indices.push_back(loc);
			index = loc + theString.size();
			indices.push_back(index);
		}
	};
	return indices;
}

void SyntaxHighlighterBase::loadFromFile(BoostPath& FilePath)
{
	if(!boost::filesystem::exists(FilePath))
	{
		SWARNING << "SyntaxHighlighterBase::loadFromFile(): " << FilePath.string() << " does not exists." << std::endl;
		return;
	}
	std::ifstream input(FilePath.string().c_str());
	std::string keyword;
	while(input>>keyword)
	{
		theKeywordsList.addKeyword(keyword);
	}
}

void SyntaxHighlighterBase::initializeKeywordsList(void)
{
	theKeywordsList.initialize();
	//displayKeywordsList();
}

void SyntaxHighlighterBase::displayKeywordsList(void)
{
	theKeywordsList.displayAll();
}
/*----------------------- constructors & destructors ----------------------*/

SyntaxHighlighterBase::SyntaxHighlighterBase(void)
{
	initializeKeywordsList();
}

SyntaxHighlighterBase::SyntaxHighlighterBase(const SyntaxHighlighterBase &obj)
{
	SWARNING << "In SyntaxHighlighterBase copy constructor" << std::endl;
}

SyntaxHighlighterBase::~SyntaxHighlighterBase(void)
{
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


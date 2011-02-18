/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
 *          David Kabala (djkabala@gmail.com)                                *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>
#include "OSGKeywordsList.h";

#include <set>
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void KeywordsList::addKeyword(const std::string& keyword)
{
    theKeywords.insert(keyword);
}

void KeywordsList::removeKeyword(const std::string& keyword)
{
    theKeywords.erase(keyword);
}

bool KeywordsList::isKeyword(const std::string& keyword) const
{
    return (theKeywords.find(keyword) != theKeywords.end());
}

void KeywordsList::displayAll(void) const
{
    SLOG << "Displaying dictionary..." << std::endl;

    for(std::set<std::string>::const_iterator theKeywords_itr(theKeywords.begin());
        theKeywords_itr!=theKeywords.end();
        ++theKeywords_itr)
    {
        SLOG << *theKeywords_itr << std::endl;
    }
    SLOG << std::endl;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void KeywordsList::initialize(void)
{
    //addKeyword("int");
    //addKeyword("void");
    ////addKeyword("main");
    //addKeyword("while");
    //addKeyword("for");
    //addKeyword("next");
    //addKeyword("do");
    //addKeyword("if");
    //addKeyword("then");
    //addKeyword("else");
    //addKeyword("endif");
    //addKeyword("elif");
    //addKeyword("end");

    //Lua keywords
    addKeyword("and");
    addKeyword("break");
    addKeyword("do");
    addKeyword("else");
    addKeyword("elseif");
    addKeyword("end");
    addKeyword("false");
    addKeyword("for");
    addKeyword("in");
    addKeyword("repeat");
    addKeyword("function");
    addKeyword("if");
    addKeyword("local");
    addKeyword("nil");
    addKeyword("return");
    addKeyword("then");
    addKeyword("not");
    addKeyword("true");
    addKeyword("or");
    addKeyword("until");
    addKeyword("while");
}

/*----------------------- constructors & destructors ----------------------*/

KeywordsList::KeywordsList(void)
{
    initialize();
}

KeywordsList::KeywordsList(const KeywordsList &source) :
    theKeywords(source.theKeywords)
{
}

KeywordsList::~KeywordsList(void)
{
}

/*----------------------------- class specific ----------------------------*/


OSG_END_NAMESPACE

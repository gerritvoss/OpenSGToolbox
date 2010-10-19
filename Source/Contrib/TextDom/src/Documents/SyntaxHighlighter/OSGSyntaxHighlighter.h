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

#ifndef _OSGSYNTAXHIGHLIGHTER_H_
#define _OSGSYNTAXHIGHLIGHTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <fstream>

#include "OSGSingletonHolder.h"

#include "OSGDocument.h"
#include <map>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTEXTDOM_DLLMAPPING SyntaxHighlighterBase
{
     /*==========================  PUBLIC  =================================*/
   public:
 
     virtual ~SyntaxHighlighterBase(void);

	 std::vector<UInt32> processInput(std::string inputString);

 
     /*=========================  PROTECTED  ===============================*/
   protected:
 
	 DocumentRefPtr inputFile;
	 DocumentRefPtr outputFile;

	 void loadDictionary(void);
	 void displayDictionary(void);
	
	 std::map<std::string,bool> dictionary;
	 std::map<std::string,bool>::const_iterator dictionary_it;

     SyntaxHighlighterBase(void);
     SyntaxHighlighterBase(const SyntaxHighlighterBase &obj);
 
     /*==========================  PRIVATE  ================================*/
   private:
 
    template <class SingletonT>
    friend class SingletonHolder;
    
     friend class OSG_CONTRIBTEXTDOM_DLLMAPPING TextFileType;
     
     void operator =(const SyntaxHighlighterBase &source);
 
  
};

typedef SingletonHolder<SyntaxHighlighterBase> SyntaxHighlighter;

typedef SyntaxHighlighter* SyntaxHighlighterP;

OSG_END_NAMESPACE

#include "OSGSyntaxHighlighter.inl"

#endif /* _OSGSyntaxHighlighter_H_ */



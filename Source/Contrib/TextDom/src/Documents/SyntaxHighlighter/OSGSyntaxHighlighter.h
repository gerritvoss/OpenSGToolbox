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

#ifndef _OSGSYNTAXHIGHLIGHTER_H_
#define _OSGSYNTAXHIGHLIGHTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include "OSGSingletonHolder.h"
#include "OSGPathType.h"

#include "OSGKeywordsList.h"

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBTEXTDOM_DLLMAPPING SyntaxHighlighterBase
{
     /*==========================  PUBLIC  =================================*/
   public:
 
     virtual ~SyntaxHighlighterBase(void);

	 std::vector<UInt32> processInput(std::string inputString);
	 void loadFromFile(BoostPath& FilePath);
 
     /*=========================  PROTECTED  ===============================*/
   protected:


	 void displayKeywordsList(void) const;
	 KeywordsList theKeywordsList;

     //Keywords
     
     //Literals
     
     //Operators

     //Comments
	 

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



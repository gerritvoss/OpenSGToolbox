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
#ifndef _OSGSTYLEDTEXTFILETYPE_H_
#define _OSGSTYLEDTEXTFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include <boost/function.hpp>
#include <utility>

#include "OSGTextFileType.h"
#include "OSGTextFileHandler.h"

#include "OSGStyledDocumentFields.h"
#include "OSGStyledDocumentBranchElementFields.h"
#include "OSGStyledDocumentLeafElementFields.h"

OSG_BEGIN_NAMESPACE


class OSG_CONTRIBTEXTDOM_DLLMAPPING StyledTextFileType : public TextFileType
{
/*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    static StyledTextFileType *the(void);

    /*---------------------------------------------------------------------*/
    virtual std::string getName(void) const;

    /*---------------------------------------------------------------------*/
    virtual ~StyledTextFileType(void);

    /*---------------------------------------------------------------------*/
     virtual DocumentTransitPtr read(std::istream &is,
		                     const std::string& FileNameOrExtension);

    /*---------------------------------------------------------------------*/
     virtual bool write(Document* const Doc, std::ostream &os,
                        const std::string& FileNameOrExtension);

    
    /*=========================  PROTECTED  ===============================*/
protected:


    typedef TextFileType Inherited;
    static       StyledTextFileType*  _the;

    /*---------------------------------------------------------------------*/
    StyledTextFileType(void);

    StyledTextFileType(const StyledTextFileType &obj);

    /*==========================  PRIVATE  ================================*/
private:

	 std::vector<std::string> _FontFaces;
	 std::vector<Color3f> _Colors;
	 std::vector<DocumentElementAttribute> _DocumentElementAttribute;  

	  //function declarations
	 void rtfreader(std::istream &InputStream,StyledDocumentRefPtr &Result);
	 Int32 findNextRed(Int32 index,std::string& sentence);
	 Int32 findNextGreen(Int32 index,std::string& sentence);
	 Int32 findNextBlue(Int32 index,std::string& sentence);
	 Int32 findNextSem(Int32 index,std::string& sentence);
	 void processSentence(std::string &sentence,DocumentElementAttribute& textStructure);
	 void rtfwriter(std::ostream &ofs,
                    std::vector<DocumentElementAttribute>& _TextWithProperties,
                    std::vector<std::string>& _FontFaces,
                    std::vector<Color3f> &_Colors);


    void operator =(const StyledTextFileType &source);
};

typedef StyledTextFileType* StyledTextFileTypeP;

OSG_END_NAMESPACE

#include "OSGStyledTextFileType.inl"

#endif /* _OSGSTYLEDTEXTFILETYPE_H_ */



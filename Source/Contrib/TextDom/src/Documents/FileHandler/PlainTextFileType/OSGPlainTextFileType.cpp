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

#include "OSGPlainTextFileType.h"
#include "windows.h"
 

OSG_BEGIN_NAMESPACE


SYSTEMTIME now;

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PlainTextFileType
A PlainTextFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

PlainTextFileType*  PlainTextFileType::_the(new PlainTextFileType());

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

PlainTextFileType *PlainTextFileType::the(void)
{
	return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string PlainTextFileType::getName(void) const
{
	return std::string("PlainTextFileType");
}

void PlainTextFileType::removeSlashRandSlashN(std::string &word)
{
	std::string temp="";
	for(UInt32 i=0;i<word.length();i++)
	{
		if(word[i]!='\r' && word[i]!='\n' && word[i]!='\t')
		{
			temp+=word[i];
		}
		else if(word[i]=='\t')
		{
			temp+="    ";
		}
	}
	word = temp;
}

DocumentRefPtr PlainTextFileType::read(std::istream &InputStream,
	                     const std::string& FileNameOrExtension)
{
	PlainDocumentRefPtr Result = PlainDocument::create();
	//std::string sentence="";
	TextWithProps props;
	std::string word;
	bool firstTime = true;
	
	GetSystemTime(&now);
	unsigned int t1 = now.wSecond * 1000 + now.wMilliseconds;

	while(std::getline(InputStream,word))
	{
		removeSlashRandSlashN(word);
		Result->addTextAsNewElementToDocument(word+"\r\n",props,firstTime);
		if(firstTime)firstTime=!firstTime;
	}

	GetSystemTime(&now);
	unsigned int t2 = now.wSecond * 1000 + now.wMilliseconds;

	std::cout<<"\nduration for reading:"<<t2-t1<<std::endl;		// end time in milliseconds


/*	std::string sentence="";
	TextWithProps props;
	char chara;
	while(InputStream.get(chara))
	{
		
		if(chara == '\n')
		{
			sentence +="\\n";
		}
		else if(chara == '\r')
		{
		}
		else
		{
			sentence += chara ;
		}
	}
*/
/*	GetSystemTime(&now);
	t1 = now.wSecond * 1000 + now.wMilliseconds;

	Result->insertString(UInt32(-1),sentence,props);

	GetSystemTime(&now);
	t2 = now.wSecond * 1000 + now.wMilliseconds;

	std::cout<<"\nduration for inserting:"<<t2-t1<<std::endl;		// end time in milliseconds
*/
	return Result;
}

bool PlainTextFileType::write(DocumentRefPtr Doc, std::ostream &OutputStream,
                    const std::string& FileNameOrExtension)
{
	PlainDocumentRefPtr pdoc = dynamic_pointer_cast<PlainDocument>(Doc);
	std::vector<ElementRefPtr> genericRoots;
	genericRoots = pdoc->getRootElements();
	for(UInt32 i=0;i<genericRoots.size();i++)
	{
		PlainDocumentBranchElementRefPtr RootElement;
		RootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(genericRoots[i]);	
		
		for(UInt32 j=0;j<RootElement->getElementCount()-1;j++)
		{	
			PlainDocumentLeafElementRefPtr LeafElement;
			LeafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(RootElement->getElement(j));
			OutputStream<<LeafElement->getText();

			/*
			std::string text = LeafElement->getText();

			for(int i=0;i<text.size();i++)
			{
				if(text[i]=='\n')
				{
					OutputStream<<'\r';
					OutputStream<<'\n';
				}
				else	
				{
					OutputStream.put(text[i]);
				}
			}*/
		}
		PlainDocumentLeafElementRefPtr LeafElement;
		LeafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(RootElement->getElement(RootElement->getElementCount()-1));
		OutputStream<<LeafElement->getText().substr(0,LeafElement->getTextLength()-2);

	}
	return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PlainTextFileType::PlainTextFileType(void) : Inherited(TextFileType::ExtensionVector(1, std::string("txt")),
        TextFileType::OSG_READ_SUPPORTED | TextFileType::OSG_WRITE_SUPPORTED)
{
}

PlainTextFileType::PlainTextFileType(const PlainTextFileType &obj) : Inherited(obj)
{
}

PlainTextFileType::~PlainTextFileType(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE


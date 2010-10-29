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

#include "OSGStyledTextFileType.h"
#include "OSGStyledDocument.h"
#include "OSGStyledDocumentBranchElement.h"
#include "OSGStyledDocumentLeafElement.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StyledTextFileType
A StyledTextFileType. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StyledTextFileType*  StyledTextFileType::_the(new StyledTextFileType());

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

StyledTextFileType *StyledTextFileType::the(void)
{
	return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

std::string StyledTextFileType::getName(void) const
{
	return std::string("StyledTextFileType");
}


DocumentTransitPtr StyledTextFileType::read(std::istream &InputStream,
	                     const std::string& FileNameOrExtension)
{
	//PlainDocumentRefPtr Result = PlainDocument::create();
	//std::string sentence="";
	//std::map<std::string,UInt32> props;
	//char chara;
	//while(InputStream.get(chara))
	//{
	//	
	//	if(chara == '\n')
	//	{
	//		sentence +="\\n";
	//	}
	//	else if(chara == '\r')
	//	{
	//	}
	//	else
	//	{
	//		sentence += chara ;
	//	}
	//}

	//Result->insertString(UInt32(-1),sentence,props);

	StyledDocumentRefPtr Result = StyledDocument::create();

	rtfreader(InputStream,Result);

	for(Int32 i=_DocumentElementAttribute.size()-1;i>=0;i--)
	{
		_DocumentElementAttribute[i].processed = true;
		Result->insertString(0,_DocumentElementAttribute[i].text,_DocumentElementAttribute[i]);
	}


	return DocumentTransitPtr(Result);
}


void StyledTextFileType::rtfreader(std::istream &ifs,StyledDocumentRefPtr &Result)
{
	std::string sentence;
	Int32 count = 1;
	
	while(getline(ifs,sentence))
	{
		if(sentence.find("rtf")!= std::string::npos)
		{
			continue;
		}
		if(sentence.find("fonttbl")!= std::string::npos)
		{
			std::string slashf = "\\f";
			Int32 count = -1;
			while(1)
			{
				char countstr[100];
				sprintf(countstr,"%d",(count+1));
				if(sentence.find(slashf+countstr)!= std::string::npos)
				{
					Int32 index = sentence.find(slashf+(countstr));
					bool nospaceyet= true;
					std::string font = "";
					for(Int32 i = index;i<sentence.size();i++)
					{
						if(sentence[i]==';')break;
						if(sentence[i]==' ' && nospaceyet){
							nospaceyet = false;
							continue;
						}
						if(!nospaceyet)font+=sentence[i];
					}
					_FontFaces.push_back(font);
					count++;
				}
				else break;
			}
			Result->setFonts(_FontFaces);
			continue;
		}
		if(sentence.find("colortbl")!= std::string::npos)
		{
			
			Color3f _DefaultColor(0.0f,0.0f,0.0f);
			_Colors.push_back(_DefaultColor);

			Int32 index = findNextSem(0,sentence);
			while(index < sentence.size())
			{
				Color3f col(static_cast<Real32>(findNextRed(index,sentence))/255.0f,
                            static_cast<Real32>(findNextGreen(index,sentence))/255.0f,
                            static_cast<Real32>(findNextBlue(index,sentence))/255.0f);
				index		= findNextSem(index,sentence);
				if(col.red()>=0.0f && col.green()>=0.0f && col.blue()>=0.0f)
                {
                    _Colors.push_back(col);
                }
			}
			Result->setColors(_Colors);
			continue;
		}
		if(sentence[0]=='}')
		{
			break; 
		}
		DocumentElementAttribute _TextStructure;
		processSentence(sentence,_TextStructure);
		_DocumentElementAttribute.push_back(_TextStructure);
		count++;
	}

}

Int32 StyledTextFileType::findNextRed(Int32 index,std::string& sentence)
{
	for(Int32 i=index;i<sentence.size();i++)
	{
		if(sentence[i] == 'r' && sentence[i+1] == 'e' && sentence[i+2] == 'd')
		{
			Int32 num=0;
			for(Int32 j=i+3;sentence[j]!='\\';j++)
			{
				num=num*10+(sentence[j]-'0');
			}
			return num;
		}
	}
	return -1;
}

Int32 StyledTextFileType::findNextGreen(Int32 index,std::string& sentence)
{
	for(Int32 i=index;i<sentence.size();i++)
	{
		if(sentence[i] == 'e' && sentence[i+1] == 'e' && sentence[i+2] == 'n')
		{
			Int32 num=0;
			for(Int32 j=i+3;sentence[j]!='\\';j++)
			{
				num=num*10+(sentence[j]-'0');
			}
			return num;
		}
	}
	return 0;
}

Int32 StyledTextFileType::findNextBlue(Int32 index,std::string& sentence)
{
	
	for(Int32 i=index;i<sentence.size();i++)
	{
		if(sentence[i] == 'l' && sentence[i+1] == 'u' && sentence[i+2] == 'e')
		{
			Int32 num=0;
			for(Int32 j=i+3;sentence[j]!=';';j++)
			{
				num=num*10+(sentence[j]-'0');
			}
			return num;
		}
	}
	return 0;

}
Int32 StyledTextFileType::findNextSem(Int32 index,std::string& sentence)
{
	for(Int32 i=index+1;i<sentence.size();i++)
	{
		if(sentence[i] == ';') return i;
	}
	return sentence.size();
}

void StyledTextFileType::processSentence(std::string &sentence,DocumentElementAttribute& textStructure)
{
	textStructure.ends = (sentence.find("\\par")!= std::string::npos)?true:false;

	Int32 fontsize=0;
	Int32 j;
	for(j=3;sentence[j]!='\\';j++)
	{
		fontsize=fontsize*10+(sentence[j]-'0');
	}
	textStructure.fontsize = fontsize;

	while(sentence[j]!='b')j++;
	j++;
	textStructure.bold = sentence[j]-'0';

	while(sentence[j]!='i')j++;
	j++;
	textStructure.italics = sentence[j]-'0';

	Int32 font=0;
	while(sentence[j]!='f')j++;
	j++;
	for(j;sentence[j]!='\\';j++)
	{
		font=font*10+(sentence[j]-'0');
	}
	textStructure.fontfaceindex = font;
	textStructure.fontface = _FontFaces[textStructure.fontfaceindex];

	textStructure.underlined = (sentence.find("\\ulnone")!= std::string::npos)?false:true;

	Int32 fgcolorindex=0;
	while(sentence[j]!='f')j++;
	j++;
	for(j;sentence[j]!='\\';j++)
	{
		fgcolorindex=fgcolorindex*10+(sentence[j]-'0');
	}
	textStructure.foregroundindex = fgcolorindex;
	textStructure.foreground = _Colors[textStructure.foregroundindex];

	Int32 bgcolorindex=0;
	while(sentence[j]!='b')j++;
	j++;
	for(j;sentence[j]!=' ';j++)
	{
		bgcolorindex=bgcolorindex*10+(sentence[j]-'0');
	}
	textStructure.backgroundindex= bgcolorindex;
	textStructure.background = _Colors[textStructure.backgroundindex];

	std::string text="";
	j++;
	for(;j<sentence.size();j++)
	{	
		text+=sentence[j];
	}
	if(text.find("\\par")!=std::string::npos)
	{
		text = text.substr(0,text.length()-5);
	}
	else
	{
		text = text.substr(0,text.length()-1);
	}
	textStructure.text = text;

	//return textStructure;
}

////////////////////////////////////////////////////////////////////////////////

bool StyledTextFileType::write(Document* const Doc, std::ostream &OutputStream,
                    const std::string& FileNameOrExtension)
{
	//PlainDocumentRefPtr pdoc = dynamic_pointer_cast<PlainDocument>(Doc);
	//std::vector<ElementRefPtr> genericRoots;
	//genericRoots = pdoc->getRootElements();
	//for(UInt32 i=0;i<genericRoots.size();i++)
	//{
	//	PlainDocumentBranchElementRefPtr RootElement;
	//	RootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(genericRoots[i]);	
	//	
	//	for(UInt32 j=0;j<RootElement->getElementCount();j++)
	//	{	
	//		PlainDocumentLeafElementRefPtr LeafElement;
	//		LeafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(RootElement->getElement(j));
	//		std::string text = LeafElement->getText();
	//		for(int i=0;i<text.size();i++)
	//		{
	//			if(text[i]=='\n')
	//			{
	//				OutputStream<<'\r';
	//				OutputStream<<'\n';
	//			}
	//			else	
	//			{
	//				OutputStream.put(text[i]);
	//			}
	//		}
	//	}
	//}
	
	StyledDocumentRefPtr pdoc = dynamic_cast<StyledDocument* const>(Doc);
	
	if(pdoc==NULL)
    {
		SWARNING << "Document pointer is NULL" << std::endl;
		return false;
	}
	
	_FontFaces = pdoc->getFonts();
	_Colors = pdoc->getColors();
	_DocumentElementAttribute.clear();

	std::vector<Element*> genericRoots;
	genericRoots = pdoc->getRootElements();
	for(UInt32 i=0;i<genericRoots.size();i++)
	{
		StyledDocumentBranchElementRefPtr RootElement;
		RootElement = dynamic_cast<StyledDocumentBranchElement*>(genericRoots[i]);	
		
		for(UInt32 j=0;j<RootElement->getElementCount();j++)
		{	
			StyledDocumentLeafElementRefPtr LeafElement;
			LeafElement = dynamic_cast<StyledDocumentLeafElement*>(RootElement->getElement(j));
			
			DocumentElementAttribute propTable = LeafElement->getProperties();

			_DocumentElementAttribute.push_back(propTable);		

		}
	}
	rtfwriter(OutputStream,_DocumentElementAttribute,_FontFaces,_Colors);
	return false;
}


void StyledTextFileType::rtfwriter(std::ostream &ofs,
                                   std::vector<DocumentElementAttribute>& _TextWithProperties,
                                   std::vector<std::string>& _FontFaces,
                                   std::vector<Color3f>& _Colors)
{
	/*std::ofstream ofs;
	ofs.open("sample_output.rtf");*/
	if(!ofs)
	{
        SWARNING << "Error opening output file" << std::endl;
		return;
	}

	// first line

	ofs<<"{\\rtf1\\ansi\\ansicpg1252\\deff0\\deflang1033";
	ofs<<'\r';
	ofs<<'\n';

	// font table definition
	if(_FontFaces.size()>0)
	{
		ofs<<"{\\fonttbl";
		for(Int32 i = 0; i<_FontFaces.size();i++)
		{
			ofs<<"{\\f"<<i<<" "<<_FontFaces[i]<<";}";
		}
		ofs<<"}";
		ofs<<'\r';
		ofs<<'\n';
	}

	// color table definition
	
	if(_Colors.size()>1)
	{
		ofs<<"{\\colortbl ;";
		for(Int32 i = 1; i<_Colors.size();i++)
		{
			ofs << "\\red"   << static_cast<Int32>(_Colors[i].red()  *255.0f)
                << "\\green" << static_cast<Int32>(_Colors[i].green()*255.0f)
                << "\\blue"  << static_cast<Int32>(_Colors[i].blue() *255.0f) << ";";
		}
		ofs<<"}";
		ofs<<'\r';
		ofs<<'\n';
	}
	
	for(Int32 i=0;i<_TextWithProperties.size();i++)
	{
		ofs<<"\\fs"<<_TextWithProperties[i].fontsize;
		ofs<<"\\b"<<_TextWithProperties[i].bold?1:0;
		ofs<<"\\i"<<_TextWithProperties[i].italics?1:0;
		ofs<<"\\ul";
		if(!_TextWithProperties[i].underlined)ofs<<"none";
		ofs<<"\\f"<<_TextWithProperties[i].fontfaceindex;
		ofs<<"\\cf"<<_TextWithProperties[i].foregroundindex;
		ofs<<"\\cb"<<_TextWithProperties[i].backgroundindex;
		ofs<<" "<<_TextWithProperties[i].text;
		if(_TextWithProperties[i].ends)ofs<<"\\par";
		ofs<<'\r';
		ofs<<'\n';
	}
	ofs<<"}";
//	ofs.close();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StyledTextFileType::StyledTextFileType(void) : Inherited(TextFileType::ExtensionVector(1, std::string("rtf")),
        TextFileType::OSG_READ_SUPPORTED | TextFileType::OSG_WRITE_SUPPORTED)
{
}

StyledTextFileType::StyledTextFileType(const StyledTextFileType &obj) : Inherited(obj)
{
}

StyledTextFileType::~StyledTextFileType(void)
{
}

/*----------------------------- class specific ----------------------------*/

OSG_END_NAMESPACE


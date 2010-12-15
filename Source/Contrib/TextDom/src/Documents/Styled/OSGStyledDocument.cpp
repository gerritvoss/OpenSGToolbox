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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGStyledDocument.h"
#include "OSGStyledDocumentBranchElement.h"
#include "OSGStyledDocumentLeafElement.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGStyledDocumentBase.cpp file.
// To modify it, please change the .fcd file (OSGStyledDocument.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StyledDocument::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

// assuming the document starts off form index 0 and document size is the number of characters in the document.
void  StyledDocument::displayDebugInfo(void)
{
	StyledDocumentBranchElementRefPtr rootElement = dynamic_cast<StyledDocumentBranchElement*>(getDefaultRootElement());
	if(rootElement==NULL) {
		std::cout<<"displayDebugInfo(void):rootElement is NullFC";
		return;
	}
	for(UInt32 i=0;i<rootElement->getElementCount();i++)
	{
		StyledDocumentLeafElementRefPtr leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i));
		if(leafElement!=NULL)
		{
			DocumentElementAttribute temp = leafElement->getProperties();
			std::cout<<"LE "<<i<<":"<<temp.text<<"::"<<" b:"<<temp.bold<<" i:"<<temp.italics<<" u:"<<temp.underlined<<" ends:"<<temp.ends<<" fsize:"<<temp.fontsize<<std::endl;
		}

	}
	
}

void StyledDocument::addTextAsNewElementToDocument(const std::string& str, DocumentElementAttribute& properties,bool createFreshDocument)
{

}

void StyledDocument::insertCharacter(UInt32 offsetInElement,UInt32 elementIndex, const char character, DocumentElementAttribute& properties)
{

}

void StyledDocument::deleteCharacter(UInt32 elementIndex,UInt32 offsetInChild)
{

}

void StyledDocument::deleteCharacters(UInt32 lesserIndex,UInt32 lesserOffset,UInt32 greaterIndex,UInt32 greaterOffset)
{

}

UInt32 StyledDocument::createPosition(Int32 offs)
{
	if(offs < 0) // reading document from back so , (documents length + offset) would be the position
	{
		if(_DocumentSize + offs<0) // offs out of range
		{
			return 0;
		}
		else 
		{
			return (_DocumentSize + offs); // within range
		}
	}
	else
	{
		if(offs > _DocumentSize)	// positive offset out of range
		{
			return _DocumentSize;	
		}
		else	// positive offset within range
		{
			return offs;
		}
	}

}

Element* StyledDocument::getDefaultRootElement(void) const
{
	if(getMFRootElements()->size()!=0)
	{
		return StyledDocumentBase::getRootElements(0);
	}
	else	// root element does not exist
	{
		return NULL;
	}
}

UInt32 StyledDocument::getEndPosition(void) const
{
	return this->getLength();
}

UInt32 StyledDocument::getLength(void) const
{
	UInt32 length=0;

//	for(UInt32 i=0;i<_RootElements.size();i++)
//	{
		ElementRefPtr rootElement = dynamic_cast<StyledDocumentBranchElement*>(this->getDefaultRootElement());
		if(rootElement==NULL)return 0;//continue;	
		UInt32 elementCount = rootElement->getElementCount();
		for(UInt32 i=0;i<elementCount;i++)
		{
			length+=dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i))->getTextLength();
		}
	//}
	return length;
}

std::vector<Element*> StyledDocument::getRootElements(void)
{
    std::vector<Element*> Result;

    for(UInt32 i(0) ; i<getMFRootElements()->size() ; ++i)
    {
        Result.push_back(StyledDocumentBase::getRootElements(i));
    }

	return Result;
}

UInt64 StyledDocument::getStartPosition(void) const		/// whats the idea?!
{
	return 0;
}

std::string StyledDocument::getText(Int32 offset, Int32 length) const
{
	std::string stringToReturn="";

	if(offset<0 || offset >= getEndPosition() || length == 0)
	{
		SWARNING<<"This call to getText returns empty string"<<std::endl;
		return stringToReturn;
	}
	else
	{
		
		if(length < 0 || (offset + length) > getEndPosition())
		{
			length = getLength();
		}
		ElementRefPtr defaultRoot=getDefaultRootElement();
		if(defaultRoot == NULL)
		{
			SWARNING<<"StyledDocument::getText(Int32 offset, UInt32 length)::cant read into empty document"<<std::endl;
			return "";	
		}
		StyledDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<StyledDocumentBranchElement>(defaultRoot);
		UInt32 count=0;
		UInt32 locationToReadFrom; 
		UInt32	theLeafElementIndex; // theLeafElement is the leaf element that holds the beginning offset value


		//UInt32 elementCount = rootElement->getElementCount();
//		std::vector<std::string> names;
//
//		for(UInt32 i=0;i<elementCount;i++)
//		{
//			names.push_back(dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i))->getText());	
///*			std::cout<<"----------------"<<std::endl;
//			std::cout<<"Element:"<<StyledDocumentLeafElementPtr::dcast(rootElement->getElement(i))->getText()<<"Length:"<<StyledDocumentLeafElementPtr::dcast(rootElement->getElement(i))->getTextLength()<<std::endl;
//			std::cout<<"----------------"<<std::endl;
//*/		}

		for(UInt32 i=0;i<rootElement->getElementCount();i++)
		{
			StyledDocumentLeafElementRefPtr	leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i));
			if((count+leafElement->getTextLength())<=offset) // 
			{
				count+=leafElement->getTextLength();
				continue;
			}
			else // the current leaf element holds the start position
			{	
				locationToReadFrom = offset - count;
				theLeafElementIndex = i;
				break;
			}
		}
		UInt32 howManyMoreCharactersToRead = length;
		std::string subString="";
		while(howManyMoreCharactersToRead>0 && theLeafElementIndex < rootElement->getElementCount())
		{
			StyledDocumentLeafElementRefPtr	leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(theLeafElementIndex));
			std::string textOfCurrentLeaf = leafElement->getText();
			if(textOfCurrentLeaf.size()-locationToReadFrom >= howManyMoreCharactersToRead) // this leaf element would be the last to be accessed
			{	
				stringToReturn+= textOfCurrentLeaf.substr(locationToReadFrom,howManyMoreCharactersToRead);
				return stringToReturn+"\0";
			}
			else	// this leaf element would NOT be the last to be accessed
			{
				subString= textOfCurrentLeaf.substr(locationToReadFrom);
				//UInt32 tempsize = textOfCurrentLeaf.size();
				stringToReturn+=subString;
				howManyMoreCharactersToRead -= subString.size();
				locationToReadFrom=0;
			}
			theLeafElementIndex++;
		}
		return stringToReturn;
	}
}

void StyledDocument::getText(Int32 offset, Int32 length, std::string& txt) const
{
	txt = getText(offset, length);
}

void StyledDocument::getDocumentElementAttribute(Int32 offset, Int32 length, std::vector<DocumentElementAttribute>& txt) const
{
	txt = getDocumentElementAttribute(offset, length);
}

std::vector<DocumentElementAttribute> StyledDocument::getDocumentElementAttribute(Int32 offset, Int32 length) const
{
	std::vector<DocumentElementAttribute> result;
	std::string stringToReturn="";

	if(offset<0 || offset > getEndPosition() || length == 0)
	{
		SWARNING<<"This call to getText returns empty string"<<std::endl;
		return result;
	}
	else
	{
		
		if(length < 0|| (offset + length) > getEndPosition())
		{
			length = getLength();
		}
		ElementRefPtr defaultRoot=getDefaultRootElement();
		if(defaultRoot == NULL)
		{
			SWARNING<<"StyledDocument::getText(Int32 offset, UInt32 length)::cant read into empty document"<<std::endl;
			return result;	
		}
		StyledDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<StyledDocumentBranchElement>(defaultRoot);
		UInt32 count=0;
		UInt32 locationToReadFrom; 
		UInt32 theLeafElementIndex; // theLeafElement is the leaf element that holds the beginning offset value
	
//		UInt32 elementCount = rootElement->getElementCount();
//		std::vector<std::string> names;
//
//		for(UInt32 i=0;i<elementCount;i++)
//		{
//			names.push_back(dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i))->getText());	
///*			std::cout<<"----------------"<<std::endl;
//			std::cout<<"Element:"<<StyledDocumentLeafElementPtr::dcast(rootElement->getElement(i))->getText()<<"Length:"<<StyledDocumentLeafElementPtr::dcast(rootElement->getElement(i))->getTextLength()<<std::endl;
//			std::cout<<"----------------"<<std::endl;
//*/		}

		for(UInt32 i=0;i<rootElement->getElementCount();i++)
		{
			StyledDocumentLeafElementRefPtr	leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i));
			if((count+leafElement->getTextLength())<=offset) // 
			{
				count+=leafElement->getTextLength();
				continue;
			}
			else // the current leaf element holds the start position
			{	
				locationToReadFrom = offset - count;
				theLeafElementIndex = i;
				break;
			}
		}

		

		UInt32 howManyMoreCharactersToRead = length;
		while(howManyMoreCharactersToRead>0 && theLeafElementIndex < rootElement->getElementCount())
		{
			StyledDocumentLeafElementRefPtr	leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(theLeafElementIndex));
			std::string textOfCurrentLeaf = leafElement->getText();
			if(textOfCurrentLeaf.size()-locationToReadFrom >= howManyMoreCharactersToRead) // this leaf element would be the last to be accessed
			{	
				stringToReturn= textOfCurrentLeaf.substr(locationToReadFrom,howManyMoreCharactersToRead);
				DocumentElementAttribute theString;
				theString = leafElement->getProperties();
				theString.text = stringToReturn;
				result.push_back(theString);
				return result;
			}
			else	// this leaf element would NOT be the last to be accessed
			{
				stringToReturn= textOfCurrentLeaf.substr(locationToReadFrom);
				DocumentElementAttribute theString;
				theString = leafElement->getProperties();
				theString.text = stringToReturn;
				result.push_back(theString);
				//UInt32 tempsize = textOfCurrentLeaf.size();
				howManyMoreCharactersToRead -= textOfCurrentLeaf.size();
				locationToReadFrom=0;
			}
			theLeafElementIndex++;
		}
	}
}


void StyledDocument::tokenize(std::string sentence,std::vector<std::string> & setOfWords)
{
	std::string word="";
	Int32 sentsize = sentence.size();
	sentsize = sentence.length();
	for(UInt32 i=0;i<sentence.size();i++)
	{
		if(i+1<sentence.size() && sentence[i] == '\\' && sentence[i+1] == 'n')
		{
			word=word+"\n";
			setOfWords.push_back(word);
			Int32 sizeofword = word.size();
			word="";
			i++;
		}
		else
		{
			word=word+sentence[i];
		}
	}
	if(word!="")
	{
		setOfWords.push_back(word);
	}
}

void StyledDocument::insertCharacter(UInt32 offset, const char character, DocumentElementAttribute& properties)
{
	insertString(offset,std::string(1,character),properties);
}

void StyledDocument::insertString(UInt32 offset, const std::string& str, DocumentElementAttribute& properties)
{

	UInt32 endPos=getEndPosition();
	if(offset>endPos)offset = endPos;
	
	std::vector<std::string> setOfWords;
	std::string word;
	
	if(properties.processed == false)tokenize(str,setOfWords);	// split the str based on the number of '\n' s in it.
	else setOfWords.push_back(str);
	
	StyledDocumentBranchElementRefPtr defaultRoot,rootElement;

	if(getDefaultRootElement()!=NULL)
	{
		defaultRoot=dynamic_cast<StyledDocumentBranchElement*>(getDefaultRootElement());
	}
	else
	{
		defaultRoot = StyledDocumentBranchElement::create();	
		pushToRootElements(defaultRoot);
	}
	
	rootElement = defaultRoot;

	UInt32 count=0;
	UInt32 locationToWriteFrom=0; 
	Int32 theLeafElementIndex=-1; // theLeafElement is the leaf element that holds the beginning offset value
	std::string theCharactersAfter="";
	std::string theCharactersBefore="";
	DocumentElementAttribute oldProps = properties;

	for(UInt32 i=0;i<rootElement->getElementCount();i++)
	{
		StyledDocumentLeafElementRefPtr	leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i));
		if((count+leafElement->getTextLength())<=offset) 
		{
			count+=leafElement->getTextLength();
			continue;
		}
		else // the current leaf element holds the start position
		{	
			locationToWriteFrom = offset - count;
			theLeafElementIndex = i;
			std::string stringOfLeafElement = leafElement->getText();
			oldProps = leafElement->getProperties();
			theCharactersAfter = stringOfLeafElement.substr(locationToWriteFrom,std::string::npos);
			theCharactersBefore = stringOfLeafElement.substr(0,locationToWriteFrom);
			break;
		}
	}
	

	if(rootElement->getElementCount() !=0 && theLeafElementIndex == -1)	
	{
		theLeafElementIndex = rootElement->getElementCount();
	}

	if(rootElement->getElementCount()>0 && theLeafElementIndex<rootElement->getElementCount()) // when there is some leaf element already for the root
	{
		removeElement(theLeafElementIndex,rootElement);
	}

	addElements(theLeafElementIndex,theCharactersBefore,theCharactersAfter,setOfWords,rootElement,oldProps,properties);
		
	return;
}


void StyledDocument::removeElement(UInt32 theLeafElementIndex,
                                   StyledDocumentBranchElement* const rootElement)
{
	rootElement->removeChildElement(theLeafElementIndex);
}


bool StyledDocument::equals(DocumentElementAttribute &oldProps,DocumentElementAttribute &operand)
{
	if(oldProps.fontsize != operand.fontsize)return false;
	if(oldProps.bold != operand.bold)return false;
	if(oldProps.italics != operand.italics)return false;
	if(oldProps.underlined != operand.underlined)return false;
	if(oldProps.fontface != operand.fontface)return false;
	if(oldProps.fontfaceindex != operand.fontfaceindex)return false;
	//if(oldProps.foreground != operand.foreground)return false;
	if(oldProps.foregroundindex != operand.foregroundindex)return false;
	//if(oldProps.background != operand.background)return false;
	if(oldProps.backgroundindex != operand.backgroundindex)return false;
	return true;
}

void StyledDocument::addElements(Int32 theLeafElementIndex,
                                 const std::string& theCharactersBefore,
                                 const std::string& theCharactersAfter,
                                 std::vector<std::string> &setOfWords,
                                 StyledDocumentBranchElement* const rootElement,
                                 DocumentElementAttribute &oldProps,
                                 DocumentElementAttribute &newProps)
{

	if(theLeafElementIndex<0)theLeafElementIndex=0;
	if(equals(oldProps,newProps))	// if the inserted text is of the same style as the previously existing text
	{
		setOfWords[0]=theCharactersBefore+ setOfWords[0];

		if(setOfWords.size()==1 && (setOfWords[0])[setOfWords[0].size()-1] != '\n' ) // means that setOfWords has just one word and that does not end with a "\n"
		{
			setOfWords[0]+=theCharactersAfter;
		}
		else if( setOfWords[setOfWords.size()-1][setOfWords[setOfWords.size()-1].size()-1]!='\n' )	// accessing the last character of the last string in the vector of strings
		{
			setOfWords[setOfWords.size()-1]+=theCharactersAfter;
		}
		else
		{
			if(theCharactersAfter!="")
				setOfWords.push_back(theCharactersAfter);
		}

		for(Int32 i=setOfWords.size()-1;i>=0;i--) // now every word in the vector setOfWords corresponds to an element that needs to be created
		{
			/*StyledDocumentLeafElementPtr newPtr = StyledDocumentLeafElement::create();
			newPtr->setProperties(oldProps);
			removeTheSlashN(setOfWords[i]);
			newPtr->setText(setOfWords[i]);
			rootElement->addChildElement(theLeafElementIndex,newPtr);*/
			if(newProps.processed == false)
			{
				if(i == setOfWords.size()-1) 
				{
					newProps.ends = oldProps.ends;					
				}
				else
				{
					newProps.ends = true;
				}
			}
			removeTheSlashN(setOfWords[i]);
			StyledDocumentLeafElementRefPtr newPtr = StyledDocumentLeafElement::create();
			newPtr->setProperties(newProps);
			newPtr->setText(setOfWords[i]);
			rootElement->addChildElement(theLeafElementIndex,newPtr);
		}
	}
	else	// inserted text has a different style
	{

		// inserting "theCharactersAfter"
		if(theCharactersAfter!="")
		{
			StyledDocumentLeafElementRefPtr newPtr = StyledDocumentLeafElement::create();
			newPtr->setText(theCharactersAfter);
			newPtr->setProperties(oldProps);
			rootElement->addChildElement(theLeafElementIndex,newPtr);
		}

		for(Int32 i=setOfWords.size()-1;i>=0;i--) // now every word in the vector setOfWords corresponds to an element that needs to be created
		{
			if(newProps.processed == false)
			{
				if(i == setOfWords.size()-1) 
				{
					if( setOfWords[i][setOfWords[i].size()-1]=='\n')
					{
						newProps.ends = true;					
					}
					else newProps.ends = false;
				}
				else
				{
					newProps.ends = true;
				}
			}
			removeTheSlashN(setOfWords[i]);
			StyledDocumentLeafElementRefPtr newPtr = StyledDocumentLeafElement::create();
			newPtr->setProperties(newProps);
			newPtr->setText(setOfWords[i]);
			rootElement->addChildElement(theLeafElementIndex,newPtr);
		}
		
		// inserting "theCharactersBefore"
		if(theCharactersBefore!="")
		{
			StyledDocumentLeafElementRefPtr newPtr = StyledDocumentLeafElement::create();
			oldProps.ends = false;
			newPtr->setProperties(oldProps);
			newPtr->setText(theCharactersBefore);
			rootElement->addChildElement(theLeafElementIndex,newPtr);
		}

	}
	return;
}

void StyledDocument::removeTheSlashN(std::string& stringWithSlashN)
{
	//if(i+1<sentence.size() && sentence[i] == '\\' && sentence[i+1] == 'n')
	std::string t="";
	for(UInt32 i=0;i<stringWithSlashN.size();i++)
	{
		UInt32 asciiVal = stringWithSlashN[i];
		if((i+1<stringWithSlashN.size() && stringWithSlashN[i]=='\\' && stringWithSlashN[i+1]=='n' )|| asciiVal==10 || asciiVal==13 )
		{
			break;
		}
		else t+=stringWithSlashN[i];
	}
	stringWithSlashN = t;
}

void StyledDocument::replace(Int32 offset, Int32 length, const std::string& str, DocumentElementAttribute& properties)
{
	remove(offset, length);
	insertString(offset,str,properties);
	return;
}

void StyledDocument::remove(Int32 offset, Int32 len)
{
	if(offset>=getEndPosition())return;
	if(offset<0)return;
	

	ElementRefPtr defaultRoot=getDefaultRootElement();
	if(defaultRoot == NULL)
	{
		SWARNING<<"Nothing to delete"<<std::endl;
		return;
	}
	
	StyledDocumentBranchElementRefPtr rootElement = dynamic_cast<StyledDocumentBranchElement*>(getDefaultRootElement());
	UInt32 count=0;
	UInt32 locationToRemoveFrom=0; 
	UInt32 theLeafElementIndex=-1; // theLeafElement is the leaf element that holds the beginning offset value
	std::string theCharactersAfter="";
	std::string theCharactersBefore="";

	for(UInt32 i=0;i<rootElement->getElementCount();i++)
	{
		StyledDocumentLeafElementRefPtr	leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(i));
		if((count+leafElement->getTextLength())<=offset) // 
		{
			count+=leafElement->getTextLength();
			continue;
		}
		else // the current leaf element holds the start position
		{	
			locationToRemoveFrom = offset - count;
			theLeafElementIndex = i;
			std::string stringOfLeafElement = leafElement->getText();
			theCharactersBefore = stringOfLeafElement.substr(0,locationToRemoveFrom);
			break;
		}
	}

	if(theLeafElementIndex == -1) // no leaf found that contains the offset location.
	{
		SWARNING << "no leaf found that contains the offset location."<<std::endl;
		return;
	}
	else
	{
		UInt32 rootElementCount = rootElement->getElementCount();
		if(len < 0 )
		{
			for(UInt32 i = theLeafElementIndex+1;i<rootElementCount;i++)
			{
				this->removeElement(theLeafElementIndex+1,rootElement);
			}
			if(rootElement->getElementCount()>0)
			{
				if(theCharactersBefore!="")
				{
					(dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(theLeafElementIndex)))->setText(theCharactersBefore);
					DocumentElementAttribute temp;
					temp = (dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(theLeafElementIndex)))->getProperties();
					temp.ends = false;
					(dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(theLeafElementIndex)))->setProperties(temp);
				}

				else
					this->removeElement(theLeafElementIndex,rootElement);
			}
			return;
		}
		//UInt32 theStartLeafElementIndex = theLeafElementIndex;
		DocumentElementAttribute startProps,endProps;
		startProps = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(theLeafElementIndex))->getProperties();

		while(len>0 && theLeafElementIndex<rootElement->getElementCount())
		{
		
			StyledDocumentLeafElementRefPtr	leafElement = dynamic_cast<StyledDocumentLeafElement*>(rootElement->getElement(theLeafElementIndex));

			if(locationToRemoveFrom + len >= leafElement->getTextLength()) // if all the remaining characters in the current leaf needs to be removed
			{
				if(locationToRemoveFrom == 0)	// removing from the beginning
				{
					
					len-=leafElement->getTextLength();
					// delete the current leaf
					removeElement(theLeafElementIndex,rootElement);
				}
				else	// current node needs to remain . this can happen only for the leaf element in which the offset was initially located 
				{
					if(theLeafElementIndex < rootElement->getElementCount() - 1) // if  the leaf is not the last child 
					{
						
						len -= (leafElement->getTextLength() - locationToRemoveFrom); // decrease len by the number of characters deleted

						startProps = leafElement->getProperties();
						startProps.ends = false;
						leafElement->setProperties(startProps);
						leafElement->setText(theCharactersBefore);

						theCharactersBefore = "";
						if(len != 0) // when  more characters need to be deleted.
						{
							//removeElement(theLeafElementIndex,rootElement);
							theLeafElementIndex++;
							locationToRemoveFrom = 0;
							continue;
						}
						else return; // nothing more to do!
					}
					else
					{
						startProps = leafElement->getProperties();
						startProps.ends = false;
						leafElement->setProperties(startProps);
						leafElement->setText(theCharactersBefore);
						return;
					}
				}
			}
			else // if all the remaining characters in the current leaf need NOT be removed 
			{
				std::string stringOfLeafElement = leafElement->getText();
				theCharactersAfter = stringOfLeafElement.substr(locationToRemoveFrom+len);
				removeTheSlashN(theCharactersAfter);
				
				
				if(theCharactersBefore!="")	leafElement->setText(theCharactersBefore+theCharactersAfter);
				else	leafElement->setText(theCharactersAfter);

				return;
			}
			locationToRemoveFrom = 0;
			
		}
	}
	return;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

StyledDocument::StyledDocument(void) :
    Inherited()
{
}

StyledDocument::StyledDocument(const StyledDocument &source) :
    Inherited(source)
{
}

StyledDocument::~StyledDocument(void)
{
}

/*----------------------------- class specific ----------------------------*/

void StyledDocument::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void StyledDocument::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump StyledDocument NI" << std::endl;
}

OSG_END_NAMESPACE

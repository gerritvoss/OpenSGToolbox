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

#include "OSGPlainDocument.h"

#include "OSGPlainDocumentBranchElement.h"
#include "OSGPlainDocumentLeafElement.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGPlainDocumentBase.cpp file.
// To modify it, please change the .fcd file (OSGPlainDocument.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void PlainDocument::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


bool PlainDocument::isA(std::string name)
{
	if(name == "PlainDocument")return true;
	return false;
}


// assuming the document starts off form index 0 and document size is the number of characters in the document.

UInt32 PlainDocument::createPosition(Int32 offs)
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



ElementRefPtr PlainDocument::getDefaultRootElement(void) const
{
	if(_RootElements.size()!=0)
	{
		return _RootElements[0];
	}
	else	// root element does not exist
	{
		return NULL;
	}
}

std::string PlainDocument::getText(Int32 offset, Int32 length) const
{
	std::string stringToReturn="";

	if(offset<0 || offset > getEndPosition() || length == 0)
	{
		SWARNING<<"This call to getText returns empty string"<<std::endl;
		return stringToReturn;
	}
	else
	{
		
		if(length <0 || (offset + length) > getEndPosition())
		{
			length = getLength();
		}
		ElementRefPtr defaultRoot=getDefaultRootElement();
		if(defaultRoot == NULL)
		{
			SWARNING<<"PlainDocument::getText(Int32 offset, UInt32 length)::cant read into empty document"<<std::endl;
			return "";	
		}
		PlainDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(defaultRoot);
		UInt32 count=0;
		UInt32 locationToReadFrom; 
		UInt32	theLeafElementIndex; // theLeafElement is the leaf element that holds the beginning offset value


		UInt32 elementCount = rootElement->getElementCount();
//		std::vector<std::string> names;
//
//		for(UInt32 i=0;i<elementCount;i++)
//		{
//			PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
//			names.push_back(temp->getText());	
///*			std::cout<<"----------------"<<std::endl;
//			std::cout<<"Element:"<<dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i))->getText()<<"Length:"<<PlainDocumentLeafElementRefPtr::dcast(rootElement->getElement(i))->getTextLength()<<std::endl;
//			std::cout<<"----------------"<<std::endl;
//*/		}

		for(UInt32 i=0;i<rootElement->getElementCount();i++)
		{

			PlainDocumentLeafElementRefPtr	leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
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
			PlainDocumentLeafElementRefPtr	leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(theLeafElementIndex));
			std::string textOfCurrentLeaf = leafElement->getText();
			if(textOfCurrentLeaf.size()-locationToReadFrom >= howManyMoreCharactersToRead) // this leaf element would be the last to be accessed
			{	
				stringToReturn+= textOfCurrentLeaf.substr(locationToReadFrom,howManyMoreCharactersToRead);
				return stringToReturn;
			}
			else	// this leaf element would NOT be the last to be accessed
			{
				stringToReturn+= textOfCurrentLeaf.substr(locationToReadFrom);
				//UInt32 tempsize = textOfCurrentLeaf.size();
				howManyMoreCharactersToRead -= textOfCurrentLeaf.size();
				locationToReadFrom=0;
			}
			theLeafElementIndex++;
		}
		return stringToReturn;
	}
}

void PlainDocument::getText(Int32 offset, Int32 length, std::string& txt) const
{
	txt = getText(offset, length);
}


void PlainDocument::replace(Int32 offset, Int32 length, const std::string& str, TextWithProps& properties)
{
	remove(offset, length);
	insertString(offset,str,properties);
	return;
}

void PlainDocument::remove(Int32 offset, Int32 len)
{
	if(offset>=getEndPosition())return;
	if(offset<0)return;
	

	ElementRefPtr defaultRoot=getDefaultRootElement();
	if(defaultRoot == NULL)
	{
		SWARNING<<"Nothing to delete"<<std::endl;
		return;
	}
	
	PlainDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(getDefaultRootElement());
	UInt32 count=0;
	UInt32 locationToRemoveFrom=0; 
	UInt32 theLeafElementIndex=-1; // theLeafElement is the leaf element that holds the beginning offset value
	std::string theCharactersAfter="";
	std::string theCharactersBefore="";

	for(UInt32 i=0;i<rootElement->getElementCount();i++)
	{
		PlainDocumentLeafElementRefPtr	leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
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
		if(len < 0)
		{
			for(UInt32 i = theLeafElementIndex+1;i<rootElementCount;i++)
			{
				this->removeElement(theLeafElementIndex+1,rootElement);
			}
			if(rootElement->getElementCount()>0)
			{
				if(theCharactersBefore!="")
				{
					PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(theLeafElementIndex));
					temp->setText(theCharactersBefore);
				}
				else
					this->removeElement(theLeafElementIndex,rootElement);
			}
			return;
		}
		//UInt32 theStartLeafElementIndex = theLeafElementIndex;
		while(len>0 && theLeafElementIndex<rootElement->getElementCount())
		{
			PlainDocumentLeafElementRefPtr	leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(theLeafElementIndex));

			if(locationToRemoveFrom + len >= leafElement->getTextLength()) // if all the remaining characters in the current leaf needs to be removed
			{
				if(locationToRemoveFrom == 0)	// removing from the beginning
				{
					// delete the current leaf
					removeElement(theLeafElementIndex,rootElement);
					len-=leafElement->getTextLength();
					//theLeafElementIndex--;
				}
				else	// current node needs to remain . this can happen only for the leaf element in which the offset was initially located 
				{
					if(rootElement->getElementCount() > 1)
					{
						removeElement(theLeafElementIndex,rootElement);// code to delete current leaf ***
						
						len -= (leafElement->getTextLength() - locationToRemoveFrom); // decrease len by the number of characters deleted
						if(theCharactersBefore!="" && len == 0) // special case : when no more characters need to be deleted.
						{
							leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(theLeafElementIndex));
							leafElement->setText(theCharactersBefore+leafElement->getText());
								
						}
					}
					else
					{
						std::string textOfLeafElement = leafElement->getText();
						textOfLeafElement = textOfLeafElement.substr(0,locationToRemoveFrom);
						leafElement->setText(textOfLeafElement);
						len = 0;
					}
					//theLeafElementIndex--;
				}
			}
			else // if all the remaining characters in the current leaf need NOT be removed 
			{
				std::string stringOfLeafElement = leafElement->getText();
				theCharactersAfter = stringOfLeafElement.substr(locationToRemoveFrom+len,std::string::npos);
				std::string combinedString = theCharactersBefore + theCharactersAfter;
			
				leafElement->setText(combinedString);

				/*removeElement(theLeafElementIndex,rootElement);// code to delete current leaf ***

				
				std::vector<std::string> temp; // create and insert a leaf element containing the combinedString at theStartLeafElementIndex
				temp.push_back(combinedString);
				addElements(theStartLeafElementIndex,"","",temp,rootElement);*/
				len = 0;
				break;
			}
			locationToRemoveFrom = 0;
			//theLeafElementIndex++;
			
		}
	}
	this->produceRemoveUpdate(NULL);
	return;
}

void PlainDocument::tokenize(std::string sentence,std::vector<std::string> & setOfWords)
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

void PlainDocument::insertCharacter(UInt32 offsetInElement,UInt32 elementIndex, const char character, TextWithProps& properties)
{

	// for faster access, the element index and offset are assumed to be valid

	PlainDocumentBranchElementRefPtr rootElement;

	rootElement =dynamic_pointer_cast<PlainDocumentBranchElement>(getDefaultRootElement());

	PlainDocumentLeafElementRefPtr leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(elementIndex));

	std::string theCharactersAfter="";
	std::string theCharactersBefore="";
	
	theCharactersAfter = leafElement->getText().substr(offsetInElement,std::string::npos);
	theCharactersBefore = leafElement->getText().substr(0,offsetInElement);

	if(character == '\n')
	{
		leafElement->setText(theCharactersBefore+"\n");
		PlainDocumentLeafElementRefPtr newPtr = PlainDocumentLeafElement::create();
		newPtr->setText(theCharactersAfter);
		rootElement->addChildElement(elementIndex+1,newPtr);
		
		produceInsertUpdate(NULL);
	}
	else
	{
		leafElement->setText(theCharactersBefore+character+ theCharactersAfter);

		produceChangedUpdate(NULL);
	}
	return;

}

//void PlainDocument::insertString(UInt32 offset, const std::string& str, TextWithProps& properties)
void PlainDocument::insertCharacter(UInt32 offset, const char character, TextWithProps& properties)
{

	UInt32 endPos=getEndPosition();
	if(offset>endPos)offset = endPos;
	

	PlainDocumentBranchElementRefPtr defaultRoot,rootElement;

	if(getDefaultRootElement()!=NULL)
	{
		defaultRoot=dynamic_pointer_cast<PlainDocumentBranchElement>(getDefaultRootElement());
	}
	else
	{
		defaultRoot = PlainDocumentBranchElement::create();	// problem here.. defaultroot is a badptr. check y!
		_RootElements.push_back(defaultRoot);
	}
	
	rootElement = defaultRoot;

	UInt32 count=0;
	UInt32 locationToWriteFrom=0; 
	Int32 theLeafElementIndex=-1; // theLeafElement is the leaf element that holds the beginning offset value
	std::string theCharactersAfter="";
	std::string theCharactersBefore="";
	std::string stringOfLeafElement;
	PlainDocumentLeafElementRefPtr	leafElement;

	for(UInt32 i=0;i<rootElement->getElementCount();i++)
	{
		leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
		if((count+leafElement->getTextLength())<=offset) 
		{
			count+=leafElement->getTextLength();
			continue;
		}
		else // the current leaf element holds the start position
		{	
			locationToWriteFrom = offset - count;
			theLeafElementIndex = i;
			stringOfLeafElement = leafElement->getText();
			theCharactersAfter = stringOfLeafElement.substr(locationToWriteFrom,std::string::npos);
			theCharactersBefore = stringOfLeafElement.substr(0,locationToWriteFrom);
			break;
		}
	}
	

	if(rootElement->getElementCount() !=0 && theLeafElementIndex == -1)	
	{
		theLeafElementIndex = rootElement->getElementCount();
	}

	if(character == '\n')
	{
		leafElement->setText(theCharactersBefore+"\n");
		PlainDocumentLeafElementRefPtr newPtr = PlainDocumentLeafElement::create();
		newPtr->setText(theCharactersAfter);
		rootElement->addChildElement(theLeafElementIndex+1,newPtr);
		
		produceInsertUpdate(NULL);
	}
	else
	{
		leafElement->setText(theCharactersBefore+character+ theCharactersAfter);

		produceChangedUpdate(NULL);
	}
	return;
}
void PlainDocument::deleteCharacter(UInt32 elementIndex,UInt32 offsetInChild)
{
	PlainDocumentBranchElementRefPtr rootElement;

	rootElement =dynamic_pointer_cast<PlainDocumentBranchElement>(getDefaultRootElement());

	PlainDocumentLeafElementRefPtr leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(elementIndex));
	PlainDocumentLeafElementRefPtr leafElement2;
	std::string charactersBefore = "";
	charactersBefore += leafElement->getText().substr(0,offsetInChild);
	std::string charactersAfter = "";
	charactersAfter += leafElement->getText().substr(offsetInChild,std::string::npos);

	if(offsetInChild == leafElement->getTextLength()-2)
	{
		if(elementIndex+1<rootElement->getElementCount())
		{
			leafElement2 = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(elementIndex+1));
			charactersAfter = leafElement2->getText();
			removeElement(elementIndex+1,rootElement);
			leafElement->setText(charactersBefore + charactersAfter);
			this->produceRemoveUpdate(NULL);
			return;
		}
	}
	else
	{
		charactersAfter = charactersAfter.substr(1);
		leafElement->setText(charactersBefore + charactersAfter);
		return;
	}
}

void PlainDocument::deleteCharacters(UInt32 lesserIndex,UInt32 lesserOffset,UInt32 greaterIndex,UInt32 greaterOffset)
{

	PlainDocumentBranchElementRefPtr rootElement=dynamic_pointer_cast<PlainDocumentBranchElement>(getDefaultRootElement());
	PlainDocumentLeafElementRefPtr leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(lesserIndex));
	PlainDocumentLeafElementRefPtr leafElement2;

	if(lesserIndex == greaterIndex)
	{
		std::string charactersBefore = "";
		charactersBefore += leafElement->getText().substr(0,lesserOffset);
		std::string charactersAfter = "";
		charactersAfter += leafElement->getText().substr(greaterOffset);
		leafElement->setText(charactersBefore+charactersAfter);
		return;
	}
	
	for(UInt32 i=lesserIndex+1;i<greaterIndex;i++)
	{
		removeElement(lesserIndex+1,rootElement);	// delete intermediate elements
	}

	std::string temp = "";
	temp += leafElement->getText().substr(0,lesserOffset);	// modify the first element
	
	leafElement2 = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(lesserIndex+1)); // get the last element

	/*if(greaterOffset<leafElement2->getTextLength())
	{*/
		leafElement->setText(temp + leafElement2->getText().substr(greaterOffset));		// modify the last element
	//}

	removeElement(lesserIndex+1,rootElement);

	produceRemoveUpdate(NULL);
}

void PlainDocument::addTextAsNewElementToDocument(const std::string& str, TextWithProps& properties,bool createFreshDocument)
{

	PlainDocumentBranchElementRefPtr rootElement;

	if(getDefaultRootElement()!=NULL)
	{
		rootElement=dynamic_pointer_cast<PlainDocumentBranchElement>(getDefaultRootElement());
	}
	else
	{
		rootElement = PlainDocumentBranchElement::create();	
		_RootElements.push_back(rootElement);
	}

	PlainDocumentLeafElementRefPtr newPtr = PlainDocumentLeafElement::create();
	newPtr->setText(str);
	rootElement->addChildElement(rootElement->getElementCount(),newPtr);
}

void PlainDocument::insertString(UInt32 offset, const std::string& str, TextWithProps& properties)
{

	UInt32 endPos=getEndPosition();
	if(offset>endPos)offset = endPos;
	
	std::vector<std::string> setOfWords;
	std::string word;
	
	tokenize(str,setOfWords);	// split the str based on the number of '\n' s in it.
	
	PlainDocumentBranchElementRefPtr defaultRoot,rootElement;

	if(getDefaultRootElement()!=NULL)
	{
		defaultRoot=dynamic_pointer_cast<PlainDocumentBranchElement>(getDefaultRootElement());
	}
	else
	{
		defaultRoot = PlainDocumentBranchElement::create();	// problem here.. defaultroot is a badptr. check y!
		_RootElements.push_back(defaultRoot);
	}
	
	rootElement = defaultRoot;

	UInt32 count=0;
	UInt32 locationToWriteFrom=0; 
	Int32 theLeafElementIndex=-1; // theLeafElement is the leaf element that holds the beginning offset value
	std::string theCharactersAfter="";
	std::string theCharactersBefore="";

	for(UInt32 i=0;i<rootElement->getElementCount();i++)
	{
		PlainDocumentLeafElementRefPtr	leafElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
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
			theCharactersAfter = stringOfLeafElement.substr(locationToWriteFrom,std::string::npos);
			theCharactersBefore = stringOfLeafElement.substr(0,locationToWriteFrom);
			break;
		}
	}
	

	if(rootElement->getElementCount() !=0 && theLeafElementIndex == -1)	// to be on the safer side
	{
		theLeafElementIndex = rootElement->getElementCount();
	}

	if(rootElement->getElementCount()>0 && theLeafElementIndex<rootElement->getElementCount()) // when there is some leaf element already for the root
	{
		removeElement(theLeafElementIndex,rootElement);
	}

	addElements(theLeafElementIndex,theCharactersBefore,theCharactersAfter,setOfWords,rootElement);
	
	this->produceInsertUpdate(NULL);

	return;
}

void PlainDocument::removeElement(UInt32 theLeafElementIndex,PlainDocumentBranchElementRefPtr rootElement)
{

	rootElement->removeChildElement(theLeafElementIndex);
	
	return;
}


UInt32 PlainDocument::getLength(void) const
{
	UInt32 length=0;

	ElementRefPtr rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(this->getDefaultRootElement());

	if(rootElement==NULL) return 0;

	UInt32 elementCount = rootElement->getElementCount();

	for(int i=0;i<elementCount;i++)
	{
		PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
		length+= temp->getTextLength();
	}

	return length;
}

void PlainDocument::addElements(Int32 theLeafElementIndex,std::string theCharactersBefore,std::string theCharactersAfter,std::vector<std::string> &setOfWords,PlainDocumentBranchElementRefPtr rootElement)
{
	if(theLeafElementIndex<0)theLeafElementIndex=0;
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
		PlainDocumentLeafElementRefPtr newPtr = PlainDocumentLeafElement::create();
		newPtr->setText(setOfWords[i]);
		UInt32 tempsize = newPtr->getTextLength();
		rootElement->addChildElement(theLeafElementIndex,newPtr);

			//rootElement->getMFChildElements().insert(rootElement->getMFChildElements().begin()+theLeafElementIndex,newPtr);

	}

				
	return;
}
//void PlainDocument::putProperty(const std::string& key, UInt32 value)
//{
//	// PlainDocument has no property to put!
//	return;
//}
//
//const std::map<std::string,UInt32>& PlainDocument::getDocumentProperties(void) const
//{
//	std::map<std::string,UInt32> temp;
//	return temp;
//}

//ElementRefPtr PlainDocument::getParagraphElement(UInt32 pos) const
//{
//	// there are not paragraph elements in plain document!
//	return NULL;
//}
//void PlainDocument::readLock(void)
//{
//	// TODO:X
//	return;
//}
//
//void PlainDocument::readUnlock(void)
//{
//	// TODO:X
//	return;
//}
//void PlainDocument::setDocumentProperties(const std::map<std::string,UInt32>& properties)
//{
//	// no document properties to set!
//	return;
//}


//ElementRefPtr PlainDocument::createBranchElement(ElementRefPtr parent, const std::map<std::string,UInt32>& a) const
//{
//	//TODO:X
//	//PlainDocumentLeafElementRefPtr par = PlainDocumentLeafElementRefPtr::dcast(parent);
//	PlainDocumentBranchElementRefPtr newBranchElementRefPtr = PlainDocumentBranchElement::create();
//	//par->getMFChildElements().push_back(newBranchElementRefPtr);
//	return newBranchElementRefPtr;
//
//}
//
//ElementRefPtr PlainDocument::createLeafElement(ElementRefPtr parent, const std::map<std::string,UInt32>& a, Int32 p0, Int32 p1) const
//{
//	//TODO:X
////	PlainDocumentBranchElementRefPtr par = PlainDocumentBranchElementRefPtr::dcast(parent);
////	PlainDocumentLeafElementRefPtr newLeafElementRefPtr = PlainDocumentLeafElement::create();
////	par->editMFChildElements()->push_back(newLeafElementRefPtr);
//	return NULL;
//}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

PlainDocument::PlainDocument(void) :
    Inherited()
{
}

PlainDocument::PlainDocument(const PlainDocument &source) :
    Inherited(source)
{
}

PlainDocument::~PlainDocument(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PlainDocument::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void PlainDocument::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump PlainDocument NI" << std::endl;
}

OSG_END_NAMESPACE

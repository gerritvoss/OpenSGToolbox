/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
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

#include <cstdlib>
#include <cstdio>

#define OSG_COMPILECONTRIBTEXTDOMLIB

#include <OSGConfig.h>

#include "OSGFixedHeightLayoutManager.h"
#include "OSGUIViewport.h"
#include "OSGStringUtils.h"
#include "OSGAdvancedTextDomArea.h"

#define LINEHEIGHT 15.0;
#define CHARACTERWIDTH 3.0;

#define HSL _HighlightStartLine
#define HSI _HighlightStartIndex
#define HEL _HighlightEndLine
#define HEI _HighlightEndIndex

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGFixedHeightLayoutManagerBase.cpp file.
// To modify it, please change the .fcd file (OSGFixedHeightLayoutManager.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


void FixedHeightLayoutManager::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}

void FixedHeightLayoutManager::setTheClipBounds(Pnt2f topLeft,Pnt2f bottomRight)
{
	_TheClipBoundsTopLeft = topLeft;
	_TheClipBoundsBottomRight = bottomRight;
	updateViews();
}

void FixedHeightLayoutManager::deleteCharacters(UInt32 lesserLine,UInt32 lesserIndex,UInt32 greaterLine,UInt32 greaterIndex)
{
	getTextDomArea()->getDocumentModel()->deleteCharacters(lesserLine,lesserIndex,greaterLine,greaterIndex);
	HSL = HEL = _CaretLine = lesserLine;
	HSI = HEI = _CaretIndex = lesserIndex;
	recalculateCaretPositions();
}

void FixedHeightLayoutManager::selectAll(void)
{
	HSL = 0;
	HSI = 0;
	HEL = rootElement->getElementCount()-1;
	PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(HEL));
	HEI = temp->getTextLength()-2;

	_CaretLine = HEL;
	_CaretIndex = HEI;
	
	recalculateCaretPositions();
}

void FixedHeightLayoutManager::deleteSelected(void)
{
	if(isStartLocationBeforeEndLocation())
		deleteCharacters(HSL,HSI,HEL,HEI);
	else
		deleteCharacters(HEL,HEI,HSL,HSI);
}



bool FixedHeightLayoutManager::isLastCharacterOfDocument() const
{
	if(_CaretLine == rootElement->getElementCount()-1)
	{
		PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
		if(_CaretIndex >= temp->getTextLength()-2) return true;
	}
	return  false;
}


UInt32 FixedHeightLayoutManager::getTopmostVisibleLineNumber() const
{
	Pnt2f topLeft,bottomRight;
	/*if(getTextDomArea()->getParentContainer() && !getTextDomArea()->getParentContainer()->getType().isDerivedFrom(AdvancedTextDomArea::getClassType()))
	{*/
		getTextDomArea()->getClipBounds(topLeft,bottomRight);
	/*}
	else
	{
		topLeft = _TheClipBoundsTopLeft;
		bottomRight = _TheClipBoundsBottomRight;
	}*/
	UInt32 topmostVisibleLineNumber = UInt32(floor((topLeft.y()) / heightOfLine));
	return topmostVisibleLineNumber; 
}

UInt32 FixedHeightLayoutManager::getLinesToBeDisplayed() const
{
	Pnt2f topLeft,bottomRight;
	/*if(getTextDomArea()->getParentContainer() && !getTextDomArea()->getParentContainer()->getType().isDerivedFrom(AdvancedTextDomArea::getClassType()))
	{*/
		getTextDomArea()->getClipBounds(topLeft,bottomRight);
	/*}
	else
	{
		topLeft = _TheClipBoundsTopLeft;
		bottomRight = _TheClipBoundsBottomRight;
	}*/

	UInt32 linesToBeDisplayed = 0;
	if(bottomRight.x() == 0 && bottomRight.y() == 0 )
		linesToBeDisplayed = (UInt32(ceil(getTextDomArea()->getPreferredSize().y()/ heightOfLine)));
	else
		linesToBeDisplayed = (UInt32(ceil((bottomRight.y() - topLeft.y())/heightOfLine)));

	return linesToBeDisplayed;
}


void FixedHeightLayoutManager::updateSize()
{
	_preferredHeight = rootElement->getElementCount() * heightOfLine;
}

void FixedHeightLayoutManager::initializeRootElement() 
{
	if(getTextDomArea()->getDocumentModel())
	{
		defaultRoot=getTextDomArea()->getDocumentModel()->getDefaultRootElement();
		rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(defaultRoot);
	}
}

void FixedHeightLayoutManager::updateViews(void)
{
	if(rootElement)
	{
		Pnt2f init = getTextDomArea()->getPosition();

		UInt32 lineNumber = getTopmostVisibleLineNumber();
		UInt32 linesToBeDisplayed = getLinesToBeDisplayed();

		clearVisibleViews();
		
		if(getTextDomArea()->getWrapStyleWord())
		{
			if(linesToElements.size()==0)
			{
				SWARNING<<"FixedHeightLayoutManager::updateViews_orig(void) : Cache is empty"<<std::endl;
				return;
			}

			UInt32 initLineNumber = lineNumber;
			for(UInt32 i=0;i<linesToBeDisplayed;i++,lineNumber++)
			{
				if(lineNumber<linesToElements.size())
				{
					if( lineNumber == initLineNumber || (lineNumber != initLineNumber && linesToElements[lineNumber]!= linesToElements[lineNumber-1]))
					{
						GlyphViewRefPtr view = GlyphView::create();
						view->setElement(rootElement->getElement(linesToElements[lineNumber]));
						view->setLines(getNumberOfLines(getFirstLineOfElement(lineNumber)));
						view->setLineHeight(heightOfLine);
						view->setLineWidth(/*init.x()+*/getTextDomArea()->getPreferredSize().x());
						view->setFont(getTextDomArea()->getFont());
					

						if(lineNumber == initLineNumber)	// get the linenumber where the element corresponding to this line was first drawn
							view->setInitialPosition(Pnt2f(0,/*init.y()+*/getFirstLineOfElement(lineNumber)*heightOfLine));
						else
							view->setInitialPosition(Pnt2f(0,/*init.y()+*/lineNumber*heightOfLine));

						pushToVisibleViews(view);
			
					}
				}
				else break;
				
			}
		}
		else
		{
			for(UInt32 i=0;i<linesToBeDisplayed;i++)
			{
				if(lineNumber<rootElement->getElementCount())
				{
					GlyphViewRefPtr view = GlyphView::create();
					view->setElement(rootElement->getElement(lineNumber));
					view->setInitialPosition(Pnt2f(/*init.x()+*/_GutterSpace+_GutterSeparation,/*init.y()+*/lineNumber*heightOfLine));
					view->setFont(getTextDomArea()->getFont());
					view->setLineNumber(lineNumber+1);
					pushToVisibleViews(view);
					lineNumber++;
				}
				else break;
			}
		}
	//Vec2f temp = getTextDomArea()->getPreferredSize();
	//temp.setValues(temp.x(),rootElement->getElementCount() * heightOfLine);
	//getTextDomArea()->setPreferredSize(temp);
	}
}



UInt32 FixedHeightLayoutManager::getFirstLineOfElement(UInt32 lineNumber)
{
	UInt32 initElement = linesToElements[lineNumber];
	while(lineNumber >= 1 && linesToElements[lineNumber-1]==initElement)lineNumber--;
	return lineNumber;
}


UInt32 FixedHeightLayoutManager::totalNumberOfLines(void)
{
	if(getTextDomArea()->getWrapStyleWord()) return linesToElements.size();
	else 
	{
		ElementRefPtr defaultRoot=getTextDomArea()->getDocumentModel()->getDefaultRootElement();
		PlainDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(defaultRoot);
		return rootElement->getElementCount();
	}
}
UInt32 FixedHeightLayoutManager::getNumberOfLines(UInt32 lineNumber)
{
	UInt32 noOfLines = 0;
	UInt32 initialValue = linesToElements[lineNumber];
	while(lineNumber<linesToElements.size() && linesToElements[lineNumber] == initialValue)
	{
	lineNumber++;
	noOfLines++;
	}
	return noOfLines;
}

void FixedHeightLayoutManager::calculatePreferredSize(void)
{
	if(getTextDomArea()->getWrapStyleWord())
	{
		Pnt2f topLeft,bottomRight;
		/*if(getTextDomArea()->getParentContainer() && !getTextDomArea()->getParentContainer()->getType().isDerivedFrom(AdvancedTextDomArea::getClassType()))
		{*/
			getTextDomArea()->getClipBounds(topLeft,bottomRight);
		/*}
		else
		{
			topLeft = _TheClipBoundsTopLeft;
			bottomRight = _TheClipBoundsBottomRight;
		}*/
		//getTextDomArea()->getClipBounds(topLeft,bottomRight);

		if(topLeft.x() == 0 && topLeft.y() == 0)
		{
			_preferredWidth = getTextDomArea()->getPreferredSize().x();
		}
		else
		{
			_preferredWidth = bottomRight.x()-topLeft.x();
		}

		_preferredHeight = linesToElements.size() * heightOfLine;
	}
	else
	{	
		if(getTextDomArea()->getDocumentModel())
		{
			ElementRefPtr defaultRoot=getTextDomArea()->getDocumentModel()->getDefaultRootElement();
			PlainDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(defaultRoot);

			_preferredWidth = osgMax(getTextDomArea()->getSize().x(),calculateWidthOfLongestLine(rootElement));
			_preferredHeight =  rootElement->getElementCount() * heightOfLine;
		}
		else // do not know how this reaches here.. but it does reach here.
		{
			_preferredWidth = getTextDomArea()->getSize().x();
			_preferredHeight =  getTextDomArea()->getSize().y();
		}
	}
}

Vec2f  FixedHeightLayoutManager::getContentRequestedSize(void) const
{
	return Vec2f(_preferredWidth,_preferredHeight);
}

void FixedHeightLayoutManager::printDebugInformation(void) const
{
	//std::cout<<"printing line height..."<< heightOfLine<<std::endl;
//	std::cout<<"printing width of character..."<< widthOfCharacter<<std::endl;
//	std::cout<<"_CaretLine: "<<_CaretLine<<" _CaretIndex: "<<_CaretIndex<<std::endl;
//	std::cout<<"HSL: "<<HSL<<" HSI: "<<HSI<<" HEL: "<<HEL<<" HEI: "<<HEI<<std::endl;
}


void FixedHeightLayoutManager::calculateLineHeight(void)
{
		// calculating the character height using 'Q' as the standard character
		heightOfLine = LINEHEIGHT;
		
		UInt32 lineSpacing = getTextDomArea()->getLineSpacing();

		Vec2f topLeft(0,0),bottomRight(0,0);

		if(getTextDomArea()->getFont())
		{
			getTextDomArea()->getFont()->getBounds("A",topLeft,bottomRight);
			heightOfLine = bottomRight.y() - topLeft.y();
		}

		//heightOfLine +=  lineSpacing;

}

Real32 FixedHeightLayoutManager::calculateWidthOfLongestLine(PlainDocumentBranchElementRefPtr rootElement) const
{
	Real32 finalWidth=0.0;
	Real32 currentWidth;

	for(UInt32 i=0;i<rootElement->getElementCount();i++)
	{
		PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));

		Pnt2f TopLeft, BottomRight;
		getTextDomArea()->getFont()->getBounds(temp->getText(), TopLeft, BottomRight);
		
		currentWidth = BottomRight.x() - TopLeft.x();

		if(currentWidth > finalWidth)finalWidth = currentWidth;
	}
	return finalWidth + 15.0;
}

bool FixedHeightLayoutManager::insideGutterRegion(Real32 PointOnComponentX)const
{
	Pnt2f topLeft,bottomRight;
	/*if(getTextDomArea()->getParentContainer() && !getTextDomArea()->getParentContainer()->getType().isDerivedFrom(AdvancedTextDomArea::getClassType()))
	{*/
		getTextDomArea()->getClipBounds(topLeft,bottomRight);
	/*}
	else
	{
		topLeft = _TheClipBoundsTopLeft;
		bottomRight = _TheClipBoundsBottomRight;
	}*/
	return ((PointOnComponentX - topLeft.x())<=(_GutterSpace + _GutterSeparation));
}

UInt32 FixedHeightLayoutManager::calculateCaretPosition(Pnt2f PointOnComponent,bool isDragging)
{
	if(!insideGutterRegion(PointOnComponent.x()))
	{

		UInt32 pos = 0, noOfCharacters =0;
		UInt32 row = (UInt32(floor((PointOnComponent.y()/* - getTextDomArea()->getPosition().y() */) / heightOfLine)));

		_CaretLine = row;
		// calculating the caret line and caret y position
		_CaretYPosition = /*getTextDomArea()->getPosition().y() +*/ row * heightOfLine;
		
		Real32 xpos = PointOnComponent.x()/* - getTextDomArea()->getPosition().x()*/ - _GutterSpace - _GutterSeparation ;

		if(row>=rootElement->getElementCount())
		{
			_CaretLine = rootElement->getElementCount()-1;
			PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
			_CaretIndex = temp->getTextLength()-2;

			recalculateCaretPositions();

			HEL = _CaretLine;
			HEI = _CaretIndex;

			if(!isDragging)
			{
				HSL = HEL;
				HSI = HEI;
			}

			printDebugInformation();

			getTextDomArea()->setCaretPosition(getTextDomArea()->getDocumentModel()->getEndPosition()-2);
			return 0;	// returning not the correct value. 
		}
		for(UInt32 i=0;i<_CaretLine;i++)
		{
			PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
			noOfCharacters= temp->getTextLength();
			pos += noOfCharacters;
		}
		PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(row));

		noOfCharacters = 0;

		std::string temptext = temp->getText();
		Pnt2f topLeft,bottomRight;

		std::string ttemp = ""; 

		Real32 widthSoFar = 0.0;
		_CaretIndex = 0;

		for(UInt32 i=0;i<temp->getTextLength()-2;i++)
		{
			ttemp = temptext[i];
			getTextDomArea()->getFont()->getBounds(ttemp,topLeft,bottomRight);

			if(widthSoFar + bottomRight.x() <= xpos) 
			{
				noOfCharacters++;
				widthSoFar += bottomRight.x();
				_CaretIndex++;
			}
			else
			{
				break;
			}
			
		}

		_CaretXPosition = _GutterSpace + _GutterSeparation /*+ getTextDomArea()->getPosition().x()*/ + widthSoFar;
		pos += noOfCharacters;

		HEL = _CaretLine;
		HEI = _CaretIndex;

		if(!isDragging)
		{
			HSL = HEL;
			HSI = HEI;
		}

		printDebugInformation();

		getTextDomArea()->setCaretPosition(pos);
		return pos;
	}
}


void FixedHeightLayoutManager::DoIfLineLongerThanPreferredSize() const
{
	PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));

	Pnt2f topLeft,bottomRight;
	getTextDomArea()->getFont()->getBounds(temp->getText(),topLeft,bottomRight);
	
	Vec2f preferredSize = getTextDomArea()->getPreferredSize(); 

	if(bottomRight.x() > preferredSize.x())preferredSize.setValues(bottomRight.x(),preferredSize.y());
	
	getTextDomArea()->setPreferredSize(preferredSize);

}



void FixedHeightLayoutManager::moveCaretLeft(void)
{
	PlainDocumentLeafElementRefPtr theElement; 
	if(_CaretIndex>0)
	{
		// set caret line
		// set caret index

		_CaretIndex--;
		// set caret x,y position
		recalculateCaretPositions();
		// set the caret position wrt DOM
		getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()-1);
	}
	else
	{
		if(_CaretLine>0)
		{
			_CaretLine--;
			theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
			_CaretIndex = theElement->getTextLength()-2;
			if(_CaretIndex<0)_CaretIndex = 0;
			recalculateCaretPositions();
			getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()-2);
		}
	}
}

void FixedHeightLayoutManager::moveCaretRight(void)
{
	PlainDocumentLeafElementRefPtr theElement; 
	theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
	if(_CaretIndex>=theElement->getTextLength()-2) 
	{
		if(_CaretLine<rootElement->getElementCount()-1)
		{
			_CaretLine++;
			_CaretIndex = 0;
			recalculateCaretPositions();
			getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+2);
		}
	}
	else 
	{
		_CaretIndex++;
		recalculateCaretPositions();
		getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+1);
	}
}

void FixedHeightLayoutManager::moveAndHighlightWord(UInt32 dir)
{
	Int32 prevIndex= _CaretIndex;
	Int32 prevLine= _CaretLine;
	bool fromPrevElement = false;
	PlainDocumentLeafElementRefPtr theElement; 
	std::string theString;

	switch(dir)
	{

	case LEFT:
		
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(prevLine));

		if(prevIndex == 0)
		{
			if(prevLine>0)
			{
				prevLine--;
				theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(prevLine));
				prevIndex = theElement->getTextLength()-2;
				_CaretLine = prevLine;
				_CaretIndex = prevIndex;
				fromPrevElement = true;
				getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()-2);
			}
			else break;
		}

		theString = theElement->getText();

		if(prevIndex>0 && isWordChar(theString[prevIndex-1]) == false)fromPrevElement = true;

		for(Int32 i=prevIndex-1; i>=0;)
		{
			if(isWordChar(theString[i]) != fromPrevElement) // this means that when prevIndex is 0, it would indicate the beginning of the line and hence, the ctrl action should take the cursor until a wordchar is found
			{
				_CaretLine = prevLine;
				_CaretIndex = i;	
				getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()-1);
				i--;
			}
			else
			{
				break;
			}
		}
		recalculateCaretPositions();
		break;	// case left complete.

	case RIGHT:
		
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(prevLine));

		if(prevIndex >=theElement->getTextLength()-2)
		{
			if(prevLine<rootElement->getElementCount()-1)
			{
				prevLine++;
				prevIndex = 0;
				_CaretLine = prevLine;
				_CaretIndex = prevIndex;
				fromPrevElement = true;
				theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(prevLine));
				getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+2);
			}
			else break;
		}

		theString = theElement->getText();

		if(isWordChar(theString[prevIndex]) == false)fromPrevElement = true;

		for(UInt32 i=prevIndex; i<theElement->getTextLength()-2;)
		{
			if(isWordChar(theString[i]) != fromPrevElement) // this means that when prevIndex is 0, it would indicate the beginning of the line and hence, the ctrl action should take the cursor until a wordchar is found
			{
				i++;
				_CaretLine = prevLine;
				_CaretIndex = i;	
				getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+1);
			}
			else
			{
				break;
			}
		}
		recalculateCaretPositions();
		break;	// Case Right complete.
	}
}

void FixedHeightLayoutManager::moveCaretUp(void)
{
	PlainDocumentLeafElementRefPtr theElement;
	
	if(_CaretLine > 0) 
	{
		UInt32 prevIndex = _CaretIndex;
		UInt32 prevLine = _CaretLine;
		_CaretLine--;
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
		if(_CaretIndex> theElement->getTextLength()-2)_CaretIndex = theElement->getTextLength()-2;
		if(_CaretIndex<0)_CaretIndex=0;
		recalculateCaretPositions();
		UInt32 charactersToBeRewinded=0;
		charactersToBeRewinded += prevIndex;
		charactersToBeRewinded += (theElement->getTextLength() - _CaretIndex);
		getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()-charactersToBeRewinded);
	}
}

void FixedHeightLayoutManager::moveCaretDown(void)
{
	PlainDocumentLeafElementRefPtr theElement;
	if(_CaretLine < rootElement->getElementCount()-1)
	{
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
		UInt32 prevIndex = _CaretIndex;
		UInt32 prevLineLength = theElement->getTextLength();
		_CaretLine++;
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
		if(_CaretIndex> theElement->getTextLength()-2)_CaretIndex = theElement->getTextLength()-2;
		if(_CaretIndex<0)_CaretIndex=0;
		recalculateCaretPositions();
		UInt32 charactersToBeForwarded=0;
		charactersToBeForwarded += _CaretIndex;
		charactersToBeForwarded += (prevLineLength - prevIndex);
		getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+charactersToBeForwarded);
	}
}

void FixedHeightLayoutManager::moveCaretHome(bool isControlPressed)
{
	if(isControlPressed)
	{
		_CaretLine = 0;
		_CaretIndex = 0;
		getTextDomArea()->setCaretPosition(0);
	}
	else
	{
		PlainDocumentLeafElementRefPtr theElement;
		UInt32 prevIndex = _CaretIndex;
		_CaretIndex = 0;
		getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()-(prevIndex - _CaretIndex));
	}
	recalculateCaretPositions();
}

void FixedHeightLayoutManager::moveCaretEnd(bool isControlPressed)
{
	PlainDocumentLeafElementRefPtr theElement;

	if(isControlPressed)
	{
		_CaretLine = rootElement->getElementCount()-1;
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
		_CaretIndex = theElement->getTextLength()-2;
		getTextDomArea()->setCaretPosition(getTextDomArea()->getDocumentModel()->getEndPosition()-2);
		recalculateCaretPositions();
	}
	else
	{
		UInt32 prevIndex = _CaretIndex;
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
		_CaretIndex = theElement->getTextLength()-2;
		if(_CaretIndex<0)
		{
			SWARNING << "_CaretIndex < 0 .. Setting it to 0"<<std::endl;
			_CaretIndex = 0;
		}
		if(_CaretIndex>prevIndex)
			recalculateCaretPositions();
		getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+ (_CaretIndex - prevIndex));
	}
}

inline bool FixedHeightLayoutManager::isStartLocationBeforeEndLocation(void) const
{
	return (HSL<HEL || (HSL==HEL && HSI<HEI));
}

void FixedHeightLayoutManager::moveTheCaret(UInt32 dir,bool isShiftPressed,bool isControlPressed)
{

	if(!rootElement || !rootElement->getElementCount()) return;
	UInt32 charactersToBeForwarded;
	PlainDocumentLeafElementRefPtr theElement;
	Int32 tempIndex;
	Int32 tempLine;
	switch(dir)
	{
	case LEFT:
		if(!isShiftPressed)
		{
			if(HSL != HEL || HSI != HEI) // something was highlighted before this
			{
				if(isStartLocationBeforeEndLocation())	
				{					
					_CaretLine = HSL;					// set caret position to the Highlight Starting position
					_CaretIndex = HSI;
					HEI = HSI;
					HEL = HSL;
				}
				else
				{
					_CaretLine = HEL;					// set caret position to the Highlight Ending position
					_CaretIndex = HEI;
					HSI = HEI;
					HSL = HEL;
				}
				recalculateCaretPositions();
			}
			else	// nothing was highlighted before this
			{
				if(!isControlPressed)moveCaretLeft();
				else	moveAndHighlightWord(LEFT);

				HSI = HEI = _CaretIndex;
				HSL = HEL = _CaretLine;
			}
		}
		else	// if shift is pressed
		{
			if(!isControlPressed)moveCaretLeft();
			else	moveAndHighlightWord(LEFT);

			HEI = _CaretIndex;
			HEL = _CaretLine;
		}
		break;
	case RIGHT:	
		if(!isShiftPressed)
		{
			if(HSL != HEL || HSI != HEI) // something was highlighted before this
			{
				if(isStartLocationBeforeEndLocation())	
				{					
					_CaretLine = HEL;					// set caret position to the Highlight Starting position
					_CaretIndex = HEI;
					HSI = HEI;
					HSL = HEL;
				}
				else
				{
					_CaretLine = HSL;					// set caret position to the Highlight Ending position
					_CaretIndex = HSI;
					HEI = HSI;
					HEL = HSL;
				}
				recalculateCaretPositions();
			}
			else	// nothing was highlighted before this
			{
				if(!isControlPressed)moveCaretRight();
				else	moveAndHighlightWord(RIGHT);

				HSI = HEI = _CaretIndex;
				HSL = HEL = _CaretLine;
			}
		}
		else	// if shift is pressed
		{
			if(!isControlPressed)moveCaretRight();
			else	moveAndHighlightWord(RIGHT);

			HEI = _CaretIndex;
			HEL = _CaretLine;
		}
		break;

	case UP:
		if(!isShiftPressed && !isControlPressed)
		{
			if(HSL != HEL || HSI != HEI) // something was highlighted before this
			{
				if(isStartLocationBeforeEndLocation())	
				{					
					_CaretLine = HSL;					// set caret position to the Highlight Starting position
					_CaretIndex = HSI;
					HEI = HSI;
					HEL = HSL;
				}
				else
				{
					_CaretLine = HEL;					// set caret position to the Highlight Ending position
					_CaretIndex = HEI;
					HSI = HEI;
					HSL = HEL;
				}
				moveCaretUp();
			}
			else	// nothing was highlighted before this
			{
				moveCaretUp();
				HSI = HEI = _CaretIndex;
				HSL = HEL = _CaretLine;
			}
		}
		else if(isShiftPressed && !isControlPressed)	// if shift is pressed
		{
			moveCaretUp();
			HEI = _CaretIndex;
			HEL = _CaretLine;
		}
		break;

	case DOWN:	

		if(!isShiftPressed && !isControlPressed)
		{
			if(HSL != HEL || HSI != HEI) // something was highlighted before this
			{
				if(isStartLocationBeforeEndLocation())	
				{					
					_CaretLine = HEL;					// set caret position to the Highlight Starting position
					_CaretIndex = HEI;
					HSI = HEI;
					HSL = HEL;
				}
				else
				{
					_CaretLine = HSL;					// set caret position to the Highlight Ending position
					_CaretIndex = HSI;
					HEI = HSI;
					HEL = HSL;
				}
				moveCaretDown();
			}
			else // nothing was highlighted before this
			{
				moveCaretDown();
				HSI = HEI = _CaretIndex;
				HSL = HEL = _CaretLine;
			}
		}
		else if(isShiftPressed && !isControlPressed)	// if shift is pressed
		{
			moveCaretDown();
			HEI = _CaretIndex;
			HEL = _CaretLine;
		}
		break;

	case HOME:
		moveCaretHome(isControlPressed);
		HEI = _CaretIndex;
		HEL = _CaretLine;
		if(!isShiftPressed)
		{
			HSI = HEI;
			HSL = HEL;
		}
		break;

	case HOMEOFNEXTLINE:
		
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
		 charactersToBeForwarded = theElement->getTextLength()-_CaretIndex;
		_CaretIndex = 0;
		_CaretLine++;
		recalculateCaretPositions();
		getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+ charactersToBeForwarded);

		break;

	case END:
		moveCaretEnd(isControlPressed);
		HEI = _CaretIndex;
		HEL = _CaretLine;
		if(!isShiftPressed)
		{
			HSI = HEI;
			HSL = HEL;
		}
		break;

	case PAGEUP:
		tempIndex = _CaretIndex;
		tempLine = _CaretLine;
		tempLine -= getLinesToBeDisplayed();
		if(tempLine<0)tempLine = 0;
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(tempLine));
		if(tempIndex > theElement->getTextLength()-2)tempIndex = theElement->getTextLength()-2;

		HEI = tempIndex;
		HEL = tempLine;
		if(!isShiftPressed)
		{
			HSI = HEI;
			HSL = HEL;
		}
		_CaretLine = HEL;					// set caret position to the Highlight Ending position
		_CaretIndex = HEI;
		recalculateCaretPositions();

		break;

	case PAGEDOWN:
		tempIndex = _CaretIndex;
		tempLine = _CaretLine;
		tempLine += getLinesToBeDisplayed();
		if(tempLine>=rootElement->getElementCount())tempLine = rootElement->getElementCount()-1;
		theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(tempLine));
		if(tempIndex > theElement->getTextLength()-2)tempIndex = theElement->getTextLength()-2;

		HEI = tempIndex;
		HEL = tempLine;
		if(!isShiftPressed)
		{
			HSI = HEI;
			HSL = HEL;
		}
		_CaretLine = HEL;					// set caret position to the Highlight Ending position
		_CaretIndex = HEI;
		recalculateCaretPositions();

		break;
	}
	checkCaretVisibility(dir);
}

UInt32 FixedHeightLayoutManager::getNumberOfLeadingSpaces(UInt32 line)
{
	if(line>=rootElement->getElementCount())return 0;
	UInt32 count = 0;
	PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(line));
	std::string theString = theElement->getText();
	
	for(UInt32 i=0;i<theString.size(),theString[i]==' ';i++)count++;
	
	return count;
}

void FixedHeightLayoutManager::checkCaretVisibility(UInt32 dir)
{
	if(!isCaretVisible())makeCaretVisible(dir);
}

void FixedHeightLayoutManager::tabHandler(bool isShiftPressed)
{
	UInt32 lesserLine,greaterLine,lesserIndex;
	TextWithProps temp;
	UInt32 oldHSI = HSI;
	UInt32 oldHSL = HSL;
	UInt32 oldHEI = HEI;
	UInt32 oldHEL = HEL;

	PlainDocumentLeafElementRefPtr theElement;
	if(HSL<=HEL)
	{
		lesserLine = HSL;
		lesserIndex = HSI;
		greaterLine = HEL;
	}
	else
	{
		lesserLine = HEL;
		lesserIndex = HEI;
		greaterLine = HSL;
	}

	UInt32 count=0;
	if(isSomethingSelected())
	{
		if(!isShiftPressed)
		{
			for(UInt32 caretLine = lesserLine;caretLine<=greaterLine;caretLine++)
			{
				for(UInt32 i=0;i<getTextDomArea()->getTabSize();i++)
				{
					getTextDomArea()->getDocumentModel()->insertCharacter(0,caretLine,' ',temp);
				}
				DoIfLineLongerThanPreferredSize();
			}
			
		}
		else
		{
			for(UInt32 caretLine = lesserLine;caretLine<=greaterLine;caretLine++)
			{
				theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(caretLine));
				std::string theString = theElement->getText();
				Int32 i;
				for(i=0;i<theElement->getTextLength()-2,i<getTextDomArea()->getTabSize();i++)
				{
					if(theString[i]!=' ')break;
					if(caretLine == _CaretLine)moveTheCaret(LEFT,false,false);
					if(caretLine == lesserLine)count--;
				}
				theString = theString.substr(i);
				theElement->setText(theString);
			}
			HSI = 0;
			HSL = lesserLine;
			HEI = 0;
			HEL = greaterLine;
		}
	}
	else
	{
		if(!isShiftPressed)
		{
			for(UInt32 i=0;i<getTextDomArea()->getTabSize();i++)
			{
				getTextDomArea()->getDocumentModel()->insertCharacter(getCaretIndex(),getCaretLine(),' ',temp);
				moveTheCaret(RIGHT,false,false);
			}
			DoIfLineLongerThanPreferredSize();	
		}
		else
		{
			theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
			std::string theString = theElement->getText();
			Int32 i,count=0;
			Int32 initIndex = _CaretIndex;
			for(i=_CaretIndex-1;i>=0,count<getTextDomArea()->getTabSize();i--,count++)
			{
				if(i<0 || theString[i]!=' ')break;
				moveTheCaret(LEFT,false,false);
			}
			theString = theString.substr(0,_CaretIndex)+theString.substr(initIndex);
			theElement->setText(theString);
		}
	}
}

bool FixedHeightLayoutManager::isCaretInWidthRange()
{

	Pnt2f topLeft,bottomRight;
	/*if(getTextDomArea()->getParentContainer() && !getTextDomArea()->getParentContainer()->getType().isDerivedFrom(AdvancedTextDomArea::getClassType()))
	{*/
		getTextDomArea()->getClipBounds(topLeft,bottomRight);
	/*}
	else
	{
		topLeft = _TheClipBoundsTopLeft;
		bottomRight = _TheClipBoundsBottomRight;
	}*/
	return (_CaretXPosition>=topLeft.x() && _CaretXPosition<=bottomRight.x());
}

bool FixedHeightLayoutManager::isCaretVisible(void)
{
	return (_CaretLine>=getTopmostVisibleLineNumber() && _CaretLine<getTopmostVisibleLineNumber()+ getLinesToBeDisplayed() && isCaretInWidthRange());
}

void FixedHeightLayoutManager::doubleClickHandler(void)
{
	UInt32 initIndex = _CaretIndex;
	PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
	std::string theString = theElement->getText();

	//Int32 Position(0);
	Int32 BeginWord = 0;
	Int32 EndWord = theElement->getTextLength();

	if(isPunctuationChar(theString[_CaretIndex]))
	{
		EndWord = _CaretIndex + 1;
		BeginWord = _CaretIndex;
	}
	else
	{
		for(Int32 i = _CaretIndex; i < theElement->getTextLength(); i++)
		{
			if(!isWordChar(theString[i]))
			{
				EndWord = i;
				break;
			}
		}
		for(Int32 i = _CaretIndex; i >= 0; i--)
		{
			if(!isWordChar(theString[i]))
			{
				BeginWord = i + 1;
				break;
			}
		}
	}

	HEL = HSL = _CaretLine;
	HSI = BeginWord;
	HEI = EndWord;

	_CaretIndex = EndWord;

	recalculateCaretPositions();

	getTextDomArea()->setCaretPosition(getTextDomArea()->getCaretPosition()+ (EndWord - initIndex));

}



void FixedHeightLayoutManager::makeCaretVisible(UInt32 dir)
{

	//PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
	
	Pnt2f TempTopLeft, TempBottomRight;
	/*Vec2f Offset(getTextDomArea()->getPosition().x(),_CaretLine * heightOfLine);
	getTextDomArea()->getFont()->getBounds(theElement->getText(), TempTopLeft, TempBottomRight);*/

	TempTopLeft = Pnt2f(_CaretXPosition,_CaretYPosition);//TempTopLeft + Offset;
	TempBottomRight = Pnt2f(_CaretXPosition + 25 + 2,_CaretYPosition+heightOfLine);//25 here denotes the gutterwidth .. should not hardcode here

	if(getTextDomArea()->getParentContainer() != NULL && getTextDomArea()->getParentContainer()->getType().isDerivedFrom(UIViewport::getClassType()))
	{
		//Get the bounds of this line
		dynamic_cast<UIViewport*>(getTextDomArea()->getParentContainer())->maximizeVisibility(TempTopLeft, TempBottomRight);
	}
	else if(getTextDomArea()->getParentContainer() != NULL && 
		getTextDomArea()->getParentContainer()->getParentContainer() != NULL && 
		getTextDomArea()->getParentContainer()->getParentContainer()->getType().isDerivedFrom(UIViewport::getClassType()))
	{
		dynamic_cast<UIViewport*>(getTextDomArea()->getParentContainer()->getParentContainer())->maximizeVisibility(TempTopLeft, TempBottomRight);
	}
	updateViews();


	//Pnt2f topLeft,bottomRight;
	//getTextDomArea()->getClipBounds(topLeft,bottomRight);
/*
	switch(dir)
	{
	case DOWN:
		//getTextDomArea()->setClipBounds(Pnt4f(topLeft.x(),topLeft.y()+heightOfLine,bottomRight.x(),bottomRight.y()+heightOfLine));
		getTextDomArea()->setPosition(Pnt2f(getTextDomArea()->getPosition().x(),getTextDomArea()->getPosition().y()+heightOfLine));
		break;
	case UP:
		//getTextDomArea()->setClipBounds(Pnt4f(topLeft.x(),topLeft.y()-heightOfLine,bottomRight.x(),bottomRight.y()-heightOfLine));
		getTextDomArea()->setPosition(Pnt2f(getTextDomArea()->getPosition().x(),getTextDomArea()->getPosition().y()-heightOfLine));
		break;
	}*/
}

bool FixedHeightLayoutManager::isLastCharacter(void)
{
	PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
	return (_CaretIndex == theElement->getTextLength()-2);
}

void FixedHeightLayoutManager::recalculateCaretPositions(void)
{
	// this function assumes that the caret index and line values are valid and computes the caret x and y positions directly
	_CaretYPosition = /*getTextDomArea()->getPosition().y() + */_CaretLine * heightOfLine;
	PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(_CaretLine));
	Pnt2f topLeft,bottomRight;
	std::string theSubstring = theElement->getText();
	theSubstring = theSubstring.substr(0,_CaretIndex);
	getTextDomArea()->getFont()->getBounds(theSubstring,topLeft,bottomRight);
	_CaretXPosition = _GutterSpace + _GutterSeparation + /*getTextDomArea()->getPosition().x() + */bottomRight.x();
}

Pnt2f FixedHeightLayoutManager::getXYPosition(UInt32 lineNumber,UInt32 index,bool isBeginning) const
{
	PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(lineNumber));

	std::string substring = theElement->getText();
	substring = substring.substr(0,index);

	Pnt2f topLeft,bottomRight;
	getTextDomArea()->getFont()->getBounds(substring,topLeft,bottomRight);

	if(isBeginning)return Pnt2f(/*getTextDomArea()->getPosition().x() +*/ _GutterSpace + _GutterSeparation + bottomRight.x(),/*getTextDomArea()->getPosition().y()+*/lineNumber*heightOfLine);
	return Pnt2f(/*getTextDomArea()->getPosition().x() + */_GutterSpace + _GutterSeparation + bottomRight.x(),/*getTextDomArea()->getPosition().y()+*/(lineNumber+1)*heightOfLine);

}

Pnt2f FixedHeightLayoutManager::getStartXYPosition(UInt32 lineNumber) const
{
	return Pnt2f(/*getTextDomArea()->getPosition().x() + */_GutterSpace + _GutterSeparation,/*getTextDomArea()->getPosition().y()+*/lineNumber*heightOfLine);
}

Pnt2f FixedHeightLayoutManager::getEndXYPosition(UInt32 lineNumber) const
{
	PlainDocumentLeafElementRefPtr theElement = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(lineNumber));
	Pnt2f topLeft,bottomRight;
	getTextDomArea()->getFont()->getBounds(theElement->getText(),topLeft,bottomRight);
	return Pnt2f(/*getTextDomArea()->getPosition().x() + */_GutterSpace + _GutterSeparation + bottomRight.x(),/*getTextDomArea()->getPosition().y()+*/(lineNumber+1)*heightOfLine);
}


void FixedHeightLayoutManager::setStartingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine)
{
	_BracesHighlightFlag = true;
	_StartingBraceIndex = CaretIndex;
	_StartingBraceLine = CaretLine;
	_EndingBraceIndex = CaretIndex;
	_EndingBraceLine = CaretLine;
	findBrace(theChar,AFTER);
}

void FixedHeightLayoutManager::setEndingBraces(char theChar,UInt32 CaretIndex,UInt32 CaretLine)
{
	_BracesHighlightFlag = true;
	_StartingBraceIndex = CaretIndex;
	_StartingBraceLine = CaretLine;
	_EndingBraceIndex = CaretIndex;
	_EndingBraceLine = CaretLine;
	findBrace(theChar,BEFORE);
}

char FixedHeightLayoutManager::oppositeBrace(char val)
{
	switch(val)
	{
	case '{': return '}';
	case '}': return '{';
	case '[': return ']';
	case ']': return '[';
	case '(': return ')';
	case ')': return '(';
	case '<': return '>';
	case '>': return '<';
	}
}

void FixedHeightLayoutManager::findBrace(char theChar,UInt32 direction)
{
	bool found = false;
	Int32 currentLine;
	
	switch(direction)
	{
		case AFTER:
		{
			currentLine = _StartingBraceLine;
			UInt32 val = 1;
			while(currentLine<rootElement->getElementCount())
			{
				PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(currentLine));
				std::string theString = temp->getText();
				if(currentLine == _StartingBraceLine)
				{
					theString = theString.substr(_StartingBraceIndex);
				}
				if(find(theString.begin(),theString.end(),theChar) == theString.end() && find(theString.begin(),theString.end(),oppositeBrace(theChar)) == theString.end())
				{
					currentLine++;
					continue;
				}
				else 
				{
					for(UInt32 i=0;i<theString.size();i++)
					{
						if(theString[i]==theChar)
						{
							val++;
						}						
						else if(theString[i]==oppositeBrace(theChar))
						{
							val--;
							if(val <= 0)
							{
								_EndingBraceIndex = (currentLine == _StartingBraceLine)?(_StartingBraceIndex+i):i;
								_EndingBraceLine = currentLine;
								return;
							}
						}
					}
				}
				currentLine++;
			}
		break;
		}
		case BEFORE:
		{
			currentLine = _EndingBraceLine;
			UInt32 val = 1;
			while(currentLine>=0)
			{
				PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(currentLine));
				std::string theString = temp->getText();
				if(currentLine == _EndingBraceLine)
				{
					theString = theString.substr(0,_EndingBraceIndex);
				}
				if(find(theString.begin(),theString.end(),theChar) == theString.end() && find(theString.begin(),theString.end(),oppositeBrace(theChar)) == theString.end())
				{
					currentLine--;
					continue;
				}
				else 
				{
					for(Int32 i=theString.size()-1;i>=0;i--)
					{
						if(theString[i]==theChar)
						{
							val++;
						}						
						else if(theString[i]==oppositeBrace(theChar))
						{
							val--;
							if(val <= 0)
							{
								_StartingBraceIndex = i;
								_StartingBraceLine = currentLine;
								return;
							}
						}
					}
				}
				currentLine--;
			}
		break;
		}
	}
}

void FixedHeightLayoutManager::removeBracesHighlightIndices()
{
	_BracesHighlightFlag = false;
}

bool FixedHeightLayoutManager::isStartingBraces(char value)
{
	if(value == '{' || value == '[' || value == '(' || value == '<') return true;
	return false;
}

bool FixedHeightLayoutManager::isEndingBraces(char value)
{
	if(value == '}' || value == ']' || value == ')' || value == '>') return true;
	return false;
}

//
//void FixedHeightLayoutManager::drawGutter(const GraphicsWeakPtr Graphics, Real32 Opacity) const
//{
//	Pnt2f topLeft,bottomRight;
//	getTextDomArea()->getClipBounds(topLeft,bottomRight);
//
//	bottomRight.setValues(topLeft.x() + _GutterSpace,bottomRight.y());
//
//	Graphics->drawRect(topLeft,bottomRight,Color4f(1,1,0,1),Opacity);
//
//	UInt32 topMostVisibleLine = getTopmostVisibleLineNumber();
//	UInt32 linesToBeDisplayed = getLinesToBeDisplayed();
//
//	std::ostringstream o;
//	for(UInt32 i=topMostVisibleLine ; i<topMostVisibleLine + linesToBeDisplayed;i++)
//	{
//		o<<(i+1);
//		Graphics->drawText(Pnt2f(topLeft.x(),/*getTextDomArea()->getPosition().y() + */i*heightOfLine),o.str(),getTextDomArea()->getFont(),Color4f(0.2,0.2,0.2,1.0),Opacity);
//		o.str("");
//		o.clear();
//	}
//}


//**********************************************************************************************************************************************


// needs to be updated**************************************************************************************************************************



void FixedHeightLayoutManager::populateCache(void)
{
	// cache exists only when the word wrap is enabled
	if(getTextDomArea()->getWrapStyleWord()) 
	{
		linesToElements.clear();

		if(getTextDomArea()->getDocumentModel())
		{
			ElementRefPtr defaultRoot=getTextDomArea()->getDocumentModel()->getDefaultRootElement();
			if(defaultRoot)
			{
				PlainDocumentBranchElementRefPtr rootElement = dynamic_pointer_cast<PlainDocumentBranchElement>(defaultRoot);

				Pnt2f init = getTextDomArea()->getPosition();
				Vec2f dimensions = getTextDomArea()->getPreferredSize();
				
			
				for(UInt32 i=0;i<rootElement->getElementCount();i++)
				{
					//GlyphViewRefPtr view = GlyphView::create();
					PlainDocumentLeafElementRefPtr temp = dynamic_pointer_cast<PlainDocumentLeafElement>(rootElement->getElement(i));
					//view->setElement(ElementRefPtr(temp));
					UInt32 noOfCharacters= temp->getTextLength();

					/* to be edited............
					Real32 totalLengthOfAllCharacters = noOfCharacters * widthOfCharacter;
					UInt32 noOfLines = UInt32(ceil(totalLengthOfAllCharacters / dimensions.x()));

					for(UInt32 j=0;j<noOfLines;j++)
						linesToElements.push_back(i);
					*/
				}
			}
		}

	}
}
//**********************************************************************************************************************************************



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FixedHeightLayoutManager::FixedHeightLayoutManager(void) :
	_CaretLine(0),
	_CaretIndex(0),
	_CaretXPosition(0),
	_CaretYPosition(0),
	_HighlightStartLine(0),
	_HighlightStartIndex(0),
	_HighlightEndLine(0),
	_HighlightEndIndex(0),
	_preferredHeight(0.0),
	_preferredWidth(0.0),
	_GutterSpace(0.0),
	_GutterSeparation(0.0),
	_StartingBraceLine(-1),
	_StartingBraceIndex(-1),
	_EndingBraceLine(-1),
	_EndingBraceIndex(-1),
	_BracesHighlightFlag(false),
    Inherited()
{
}

FixedHeightLayoutManager::FixedHeightLayoutManager(const FixedHeightLayoutManager &source) :
    Inherited(source)
{
	_CaretLine = source._CaretLine;
	_CaretIndex = source._CaretIndex;
	_CaretXPosition = source._CaretXPosition;
	_CaretYPosition = source._CaretYPosition;
	_HighlightStartLine = source._HighlightStartLine; 
	_HighlightStartIndex = source._HighlightStartIndex; 
	_HighlightEndLine = source._HighlightEndLine; 
	_HighlightEndIndex = source._HighlightEndIndex; 
	_preferredHeight = source._preferredHeight;
	_preferredWidth = source._preferredWidth;
	_GutterSpace = source._GutterSpace;
	_GutterSeparation = source._GutterSeparation;
	_StartingBraceLine = source._StartingBraceLine;
	_StartingBraceIndex = source._StartingBraceIndex;
	_EndingBraceLine = source._EndingBraceLine;
	_EndingBraceIndex = source._EndingBraceIndex;
	_BracesHighlightFlag = source._BracesHighlightFlag;
}

FixedHeightLayoutManager::~FixedHeightLayoutManager(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FixedHeightLayoutManager::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
	if(whichField & FixedHeightLayoutManager::TextDomAreaFieldMask)
	{
		initializeRootElement();
	}

    Inherited::changed(whichField, origin, details);
}

void FixedHeightLayoutManager::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FixedHeightLayoutManager NI" << std::endl;
}

OSG_END_NAMESPACE

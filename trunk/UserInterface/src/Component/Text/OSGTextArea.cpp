/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#include <stdlib.h>
#include <stdio.h>


#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGTextArea.h"

#include "Component/Container/Window/OSGInternalWindow.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include <OpenSG/Input/OSGStringUtils.h>
#include "Util/OSGUIDrawUtils.h"
#include "Component/Scroll/OSGScrollBar.h"
#include "Component/Container/OSGUIViewport.h"

#include "LookAndFeel/OSGLookAndFeelManager.h"
OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TextArea
A UI TextArea 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextArea::initMethod (void)
{
}

void TextArea::drawInternal(const GraphicsPtr TheGraphics) const
{	
    //Text Color
    Color4f TextColor = getDrawnTextColor();
	for(Int32 i = 0; i < _LineContents.size(); i++)//draw each line seperately
	{	
        if(getFont() != NullFC)
        {
            if(_LineContents[i]._VerticalOffset > getClipBottomRight().y() || ( i+1<_LineContents.size() && _LineContents[i+1]._VerticalOffset < getClipTopLeft().y()))
            {
                continue;
            }
		    //draw like normal if not selected
		    if(_LineContents[i]._StartPosition >= _TextSelectionEnd || _LineContents[i]._EndPosition <= _TextSelectionStart || _TextSelectionStart >= _TextSelectionEnd)
		    {

			    TheGraphics->drawText(Pnt2f(_LineContents[i]._LeftHorizontalOffset, _LineContents[i]._VerticalOffset), getWrappedLine(i), getFont(), TextColor, getOpacity());
		    }


		    else if(_TextSelectionStart < _TextSelectionEnd) //if text is only on this line
		    {
			    Int32 StartSelection = 0;
			    Int32 EndSelection = getWrappedLine(i).size();
			    if(_TextSelectionStart > _LineContents[i]._StartPosition)
			    {
				    StartSelection = _TextSelectionStart-_LineContents[i]._StartPosition;
			    }
			    if(_TextSelectionEnd <= _LineContents[i]._EndPosition)
			    {
				    if(_TextSelectionEnd-_LineContents[i]._StartPosition > 0)
				    {
				    EndSelection = _TextSelectionEnd-_LineContents[i]._StartPosition;
				    }
				    else
				    {
					    EndSelection = 0;
				    }
			    }
			    std::string drawnText = getWrappedLine(i);
			    Pnt2f offset = Pnt2f(_LineContents[i]._LeftHorizontalOffset, _LineContents[i]._VerticalOffset);
			    TheGraphics->drawText(offset,drawnText.substr(0, StartSelection), getFont(), TextColor, getOpacity());//draw before selection text
			    TheGraphics->drawRect(offset+Vec2f(getFont()->getBounds(drawnText.substr(0, StartSelection)).x(), 0), //draw selection rect
				    getFont()->getBounds(drawnText.substr(0, EndSelection))+Vec2f(offset),
				    getSelectionBoxColor(), getOpacity());
			    TheGraphics->drawText(offset+Vec2f(getFont()->getBounds(drawnText.substr(0, StartSelection)).x(), 0), //draw selected text
				    drawnText.substr(StartSelection, EndSelection-StartSelection), getFont(), getSelectionTextColor(), getOpacity());
			    TheGraphics->drawText(offset+Vec2f(getFont()->getBounds(drawnText.substr(0, EndSelection)).x(), 0), //draw after selection text
				    drawnText.substr(EndSelection, drawnText.size()-EndSelection), getFont(), TextColor, getOpacity());
		    }
        }

		//draw Caret
		if(getEnabled() && getEditable() && (getCaretPosition() >= _LineContents[i]._StartPosition && getCaretPosition() <= _LineContents[i]._EndPosition ) && _TextSelectionStart >= _TextSelectionEnd &&
			 _CurrentCaretBlinkElps <= 0.5*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate() &&
			 getFocused())
		{
			Pnt2f TempTopLeft, TempBottomRight;
			getFont()->getBounds(getWrappedLine(i).substr(0, getCaretPosition()-_LineContents[i]._StartPosition), TempTopLeft, TempBottomRight);
			TheGraphics->drawLine(Pnt2f(_LineContents[i]._LeftHorizontalOffset+TempBottomRight.x(), _LineContents[i]._VerticalOffset),
				Pnt2f(_LineContents[i]._LeftHorizontalOffset+TempBottomRight.x(), _LineContents[i]._VerticalOffset+TempBottomRight.y()),
				.5, TextColor, getOpacity());
		}
	}
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Int32 TextArea::getCaretLine(void) const
{
	for(Int32 i = 0; i < _LineContents.size(); i++)//draw each line seperately
	{
		if((getCaretPosition() >= _LineContents[i]._StartPosition && getCaretPosition() <= _LineContents[i]._EndPosition) ||
			(i == _LineContents.size()-1 && getCaretPosition() == getText().size()))
		{
			return i;
		}
	}

	return -1;
}

Int32 TextArea::getCaretColumn(void) const
{
    return getCaretPosition() - _LineContents[getCaretLine()]._StartPosition;
}

bool TextArea::isLineVisible(const UInt32& line) const
{
	//Get the bounds of this line
	Pnt2f TempTopLeft, TempBottomRight;
	Vec2f Offset = Pnt2f(_LineContents[line]._LeftHorizontalOffset, _LineContents[line]._VerticalOffset);
	getFont()->getBounds(getWrappedLine(line), TempTopLeft, TempBottomRight);

	TempTopLeft = TempTopLeft + Offset;
	TempBottomRight = TempBottomRight + Offset;

	Pnt2f ClipTopLeft, ClipBottomRight;
	getClipBounds(ClipTopLeft, ClipBottomRight);

	return (TempTopLeft.x() >= ClipTopLeft.x() &&
		    TempTopLeft.y() >= ClipTopLeft.y() &&
		    TempBottomRight.x() <= ClipBottomRight.x() &&
		    TempBottomRight.y() <= ClipBottomRight.y());
}

void TextArea::scrollToLine(const UInt32& line)
{
	if(getParentContainer() != NullFC && getParentContainer()->getType().isDerivedFrom(UIViewport::getClassType()))
	{
		//Get the bounds of this line
		Pnt2f TempTopLeft, TempBottomRight;
		Vec2f Offset = Pnt2f(_LineContents[line]._LeftHorizontalOffset, _LineContents[line]._VerticalOffset);
		getFont()->getBounds(getWrappedLine(line), TempTopLeft, TempBottomRight);

		TempTopLeft = TempTopLeft + Offset;
		TempBottomRight = TempBottomRight + Offset;

		UIViewportPtr::dcast(getParentContainer())->maximizeVisibility(TempTopLeft, TempBottomRight);
	}
}

void TextArea::focusGained(const FocusEvent& e)
{
	if( getParentWindow() != NullFC &&
		getParentWindow()->getDrawingSurface() != NullFC &&
		getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_CaretUpdateListener);
	}
	Inherited::focusGained(e);
}

void TextArea::focusLost(const FocusEvent& e)
{
	if( getParentWindow() != NullFC &&
		getParentWindow()->getDrawingSurface() != NullFC &&
		getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
    {
		getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&_CaretUpdateListener);
	}
	Inherited::focusLost(e);
}

void TextArea::keyTyped(const KeyEvent& e)//broken
{
	if(getEnabled() && getEditable())
	{
		if(e.getKey() == e.KEY_ENTER)
		{
            if(hasSelection())
            {
                deleteSelectedText();
                setCaretPosition(_TextSelectionStart+1);
            }
            insert(std::string( 1,'\n' ), _TextSelectionStart);
            //moveCaret(1);
            _TextSelectionStart = getCaretPosition();
            _TextSelectionEnd = _TextSelectionStart;
		}
	}

    switch(e.getKey())
    {
    case KeyEvent::KEY_HOME:
        moveCaretToBeginOfLine();
        break;
    case KeyEvent::KEY_END:
        moveCaretToEndOfLine();
        break;
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_KEYPAD_UP:
        moveCaretLine(-1);
        break;
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_KEYPAD_DOWN:
        moveCaretLine(1);
        break;
    case KeyEvent::KEY_PAGE_UP:
        moveCaretLine(-static_cast<Int32>(numVisibleLines()));
        break;
    case KeyEvent::KEY_PAGE_DOWN:
        moveCaretLine(numVisibleLines());
        break;
	}
	Inherited::keyTyped(e);
}

void TextArea::moveCaretLine(Int32 delta)
{
    if(delta!=0)
    {
	    Int32 OriginalPosition = getCaretPosition();
	    Int32 OriginalLine = getCaretLine();

	    Int32 NewLine = osgClamp<Int32>(0,OriginalLine+delta,numLines()-1);
        
        if(OriginalLine != NewLine)
        {
            Pnt2f TempTopLeft, TempBottomRight;
            getFont()->getBounds(getWrappedLine(OriginalLine).substr(0,getCaretPosition()-_LineContents[OriginalLine]._StartPosition),TempTopLeft, TempBottomRight);
            Int32 NewPosition(findTextPosition(Pnt2f(_LineContents[NewLine]._LeftHorizontalOffset + TempBottomRight.x(),_LineContents[NewLine]._VerticalOffset)));
            if(OriginalPosition != NewPosition)
            {
                beginEditCP(TextAreaPtr(this), TextArea::CaretPositionFieldMask);
                    setCaretPosition(NewPosition);
                endEditCP(TextAreaPtr(this), TextArea::CaretPositionFieldMask);
            }
            if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&&getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC 
                && getParentWindow()->getDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
            {
                if(OriginalPosition == _TextSelectionEnd)
                {
                    _TextSelectionEnd = getCaretPosition();
                }
                else
                {
                    _TextSelectionStart = getCaretPosition();
                }
            }
            else
            {
                _TextSelectionStart = getCaretPosition();
                _TextSelectionEnd = getCaretPosition();
            }
        }
    }
}

UInt32 TextArea::numVisibleLines(void) const
{
	
    Pnt2f ClipTopLeft, ClipBottomRight;
	getClipBounds(ClipTopLeft, ClipBottomRight);
    
    Pnt2f TopLeft, BottomRight;
	getFont()->getBounds("A", TopLeft, BottomRight);

    return static_cast<Int32>(ClipBottomRight.y() - ClipTopLeft.y())/static_cast<Int32>(BottomRight.y() - TopLeft.y());
}

void TextArea::moveCaretToEndOfLine(void)
{
	//Move the caret to the end of the line
    Int32 CaretLine(getCaretLine());
	if(CaretLine >= 0 && 
        CaretLine < numLines() && 
        getCaretPosition() != _LineContents[CaretLine]._EndPosition)
	{
		beginEditCP(EditableTextComponentPtr(this), CaretPositionFieldMask);
			setCaretPosition(_LineContents[CaretLine]._EndPosition);
		endEditCP(EditableTextComponentPtr(this), CaretPositionFieldMask);
	}
}

void TextArea::moveCaretToBeginOfLine(void)
{
	//Move the caret to the beginning of the line
    Int32 CaretLine(getCaretLine());
	if(CaretLine >= 0 && 
        CaretLine < numLines() && 
        getCaretPosition() != _LineContents[CaretLine]._StartPosition)
	{
		beginEditCP(EditableTextComponentPtr(this), CaretPositionFieldMask);
			setCaretPosition(_LineContents[CaretLine]._StartPosition);
		endEditCP(EditableTextComponentPtr(this), CaretPositionFieldMask);
	}
}

UInt32 TextArea::numLines(void) const
{
    return _LineContents.size();
}

void TextArea::mouseClicked(const MouseEvent& e)
{	
	Int32 Position(0);
	Int32 BeginWord = 0;
	Int32 EndWord = getText().size();
	if(e.getButton() == e.BUTTON1)
	{

		if(e.getClickCount() == 2)
		{

			//set caret position to proper place
			Position = findTextPosition(DrawingSurfaceToComponent(e.getLocation(), TextAreaPtr(this)));
			if(isPunctuationChar(getText()[Position]))
			{
				EndWord = Position + 1;
				BeginWord = Position;
			}
			else{
				for(Int32 i = Position; i < getText().size(); i++)
				{
					if(!isWordChar(getText()[i]))
					{
						EndWord = i;
						break;
					}
				}
				for(Int32 i = Position; i >= 0; i--)
				{
					if(!isWordChar(getText()[i]))
					{
						BeginWord = i + 1;
						break;
					}
				}
			}
			_TextSelectionEnd = EndWord;
			_TextSelectionStart = BeginWord;
			beginEditCP(TextAreaPtr(this),TextArea::CaretPositionFieldMask);
				setCaretPosition(EndWord);
			endEditCP(TextAreaPtr(this),TextArea::CaretPositionFieldMask);
		}
	}
	Inherited::mouseClicked(e);

}

void TextArea::mousePressed(const MouseEvent& e)
{
	if(e.getButton() == e.BUTTON1)
	{
		//set caret position to proper place
		beginEditCP(TextAreaPtr(this),TextArea::CaretPositionFieldMask);
			setCaretPosition( findTextPosition(DrawingSurfaceToComponent(e.getLocation(), TextAreaPtr(this))));
		endEditCP(TextAreaPtr(this),TextArea::CaretPositionFieldMask);

		_TextSelectionEnd = getCaretPosition();
		_TextSelectionStart = getCaretPosition();
	}
	if(getParentWindow() != NullFC && getParentWindow()->getDrawingSurface()!=NullFC&& getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
        getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseListener(&_MouseDownListener);
        getParentWindow()->getDrawingSurface()->getEventProducer()->addKeyListener(&_MouseDownListener);
        getParentWindow()->getDrawingSurface()->getEventProducer()->addMouseMotionListener(&_MouseDownListener);
    }
	Inherited::mousePressed(e);
}

void TextArea::mouseDraggedAfterArming(const MouseEvent& e)
{
	Int32 OriginalPosition = getCaretPosition();
	if(e.getButton() == e.BUTTON1)
	{
		//set caret position to proper place
		
		beginEditCP(TextAreaPtr(this),TextArea::CaretPositionFieldMask);
			setCaretPosition( findTextPosition(DrawingSurfaceToComponent(e.getLocation(), TextAreaPtr(this))));
		endEditCP(TextAreaPtr(this),TextArea::CaretPositionFieldMask);
		if(getCaretPosition() < OriginalPosition)
		{
			if(getCaretPosition() < _TextSelectionStart)
			{
				_TextSelectionStart = getCaretPosition();
			}
			else
			{
				_TextSelectionEnd = getCaretPosition();
			}
		}
		else if(getCaretPosition() > OriginalPosition)
		{
			if(getCaretPosition() > _TextSelectionEnd)
			{
				_TextSelectionEnd = getCaretPosition();
			}
			else
			{
				_TextSelectionStart = getCaretPosition();
			}
		}
	}
}



Int32 TextArea::findTextPosition(osg::Pnt2f Input)
{
	//find row it belongs in
	Int32 row(0);
	for(Int32 i = 0; i < _LineContents.size(); ++i)
	{
		if(Input.y() >= _LineContents[i]._VerticalOffset)
		{
			row = i;
		}
	}
	//find column it belongs in
	Int32 column(0);
	Pnt2f TempTopLeft,  TempBottomRight, TempTopLeft1,  TempBottomRight1;
    std::string Line(getWrappedLine(row));
	for(Int32 i = 1; i <= Line.size(); ++i)
	{
		getFont()->getBounds(Line.substr(0, i), TempTopLeft, TempBottomRight);
		getFont()->getBounds(Line.substr(0, i-1), TempTopLeft1, TempBottomRight1);
		if(Input.x()> (TempBottomRight.x()-TempBottomRight1.x())/2.0+.5+TempBottomRight1.x()+_LineContents[row]._LeftHorizontalOffset &&
           Line[i-1] != '\n')
		{
			column = i;
		}
	}

	Int32 output(0);
	for(Int32 i = 0; i < row; ++i)
	{
		output+=getWrappedLine(i).size();
	}
	output+=column;
	return output;
}

Int32 TextArea::getScrollableBlockIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    UInt16 MajorAxis;
    if(orientation == ScrollBar::VERTICAL_ORIENTATION)
    {
        MajorAxis = 1;
    }
    else
    {
        MajorAxis = 0;
    }
    
    return direction * (VisibleRectBottomRight[MajorAxis] - VisibleRectTopLeft[MajorAxis]);
}

bool TextArea::getScrollableTracksViewportHeight(void)
{
    return false;
}

bool TextArea::getScrollableTracksViewportWidth(void)
{
    return true;
}

Int32 TextArea::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    if(getFont() != NullFC)
    {
        UInt16 MajorAxis;
        if(orientation == ScrollBar::VERTICAL_ORIENTATION)
        {
            MajorAxis = 1;
        }
        else
        {
            MajorAxis = 0;
        }
        Pnt2f TopLeft, BottomRight;
		getFont()->getBounds("A", TopLeft, BottomRight);
        return BottomRight[MajorAxis] - TopLeft[MajorAxis];
    }
    else
    {
        return Inherited::getScrollableUnitIncrement(VisibleRectTopLeft, VisibleRectBottomRight, orientation, direction);
    }
    
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextArea::TextArea(void) :
    Inherited(),
		_CurrentCaretBlinkElps(0.0),
	    _CaretUpdateListener(TextAreaPtr(this)),
		_MouseDownListener(TextAreaPtr(this))
{
}

TextArea::TextArea(const TextArea &source) :
    Inherited(source),
		_CurrentCaretBlinkElps(0.0),
	    _CaretUpdateListener(TextAreaPtr(this)),
		_MouseDownListener(TextAreaPtr(this))
{
}

TextArea::~TextArea(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextArea::CaretUpdateListener::update(const UpdateEvent& e)
{
   _TextArea->_CurrentCaretBlinkElps += e.getElapsedTime();
   if(_TextArea->_CurrentCaretBlinkElps > LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
   {
       Int32 Div = _TextArea->_CurrentCaretBlinkElps/LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
	   _TextArea->_CurrentCaretBlinkElps -= static_cast<osg::Time>(Div)*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
   }
}

void TextArea::changed(BitVector whichField, UInt32 origin)
{

    if((whichField & TextFieldMask ||
       whichField & LineWrapFieldMask ||
       whichField & WrapStyleWordFieldMask ||
       whichField & TabSizeFieldMask ||
       whichField & FontFieldMask ||
       whichField & SizeFieldMask) &&
	   getFont() != NullFC)
    {
        _LineContents.clear();
	    Pnt2f TopLeft, BottomRight, TempPos;
	    Pnt2f TempTopLeft, TempBottomRight;
	    Vec2f FullTextSize;
	    getInsideBorderBounds(TopLeft, BottomRight);
	    Int32 XPosition = 0;
	    Int32 YPosition = 0;
	    Int32 Backtrack = 0;
	    bool brokeAtWord = false;

	    //take care of tabs
	    //Set the contents of the lines (assuming letter by letter go down right now (which is wrong))
	    _LineContents.push_back(TextLine());
	    _LineContents[0]._StartPosition = 0;
	    for(Int32 i = 0; i < getText().size(); ++i)
	    {

			//while(getText() == ' ')
			//{
				//i++;
			//}
			//getFont()->getBounds(getText().substr(XPosition, i-XPosition+1), TempTopLeft, TempBottomRight);
		    if(getText()[i] == '\n')
		    {
			    XPosition = i;
			    _LineContents[YPosition]._EndPosition = i;
			    _LineContents.push_back(TextLine());
			    ++YPosition;
			    _LineContents[YPosition]._StartPosition = _LineContents[YPosition-1]._EndPosition+1;
		    }
			//if(TempBottomRight.x() > BottomRight.x())
			//{
				//if(!getWrapStyleWord())
				//{
					//XPosition = i;
					//_LineContents[YPosition]._EndPosition = i;
					//_LineContents.push_back(TextLine());
					//++YPosition;
					//_LineContents[YPosition]._StartPosition = i;
				//}
				//else
				//{
					//Int32 j;
					//brokeAtWord = false; 
					//for(j = i; j > _LineContents[YPosition]._StartPosition; --j)
					//{
						//if(!isWordChar(getText()[j])&& !isPunctuationChar(getText()[j]))
						//{
							//brokeAtWord = true;
							//break;
						//}
					//}
					//if(!brokeAtWord)
					//{
						//XPosition = i;
						//_LineContents[YPosition]._EndPosition = i;
						//_LineContents.push_back(TextLine());
						//++YPosition;
						//_LineContents[YPosition]._StartPosition = i;
					//}
					//else
					//{
						//i = j;		
						//while(getText[i] == ' ')
						//{
							//i++;
						//}
						//XPosition = i;
						//_LineContents[YPosition]._EndPosition = i;
						//_LineContents.push_back(TextLine());
						//++YPosition;
						//_LineContents[YPosition]._StartPosition = i;
					//}
				//}

			//}
	    }
	    _LineContents[YPosition]._EndPosition = getText().size();

	    //calculate offsets
	    //begin with first line
	    getFont()->getBounds(getWrappedLine(0), TempTopLeft, TempBottomRight);
	    FullTextSize.setValues(TempBottomRight.x(), _LineContents.size()*TempBottomRight.y());
	    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, FullTextSize, (Real32)0.0, (Real32)0.0);//eventually the alignments will be get horz/vert al
	    _LineContents[0]._LeftHorizontalOffset = TempPos.x();
	    _LineContents[0]._VerticalOffset = TempPos.y();
	    for(Int32 i = 1; i < _LineContents.size(); i++)
	    {						
		    getFont()->getBounds(getWrappedLine(i), TempTopLeft, TempBottomRight);
		    FullTextSize.setValues(TempBottomRight.x(), _LineContents.size()*TempBottomRight.y());
		    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, FullTextSize, (Real32)0.0, (Real32)0.0);//eventually the alignments will be get horz/vert al
		    _LineContents[i]._LeftHorizontalOffset = TempPos.x();
		    _LineContents[i]._VerticalOffset = TempPos.y()+TempBottomRight.y()*i;
	    }
        
        //Update my PreferredSize based on text
        Vec2f PreferredSize;
		getFont()->getBounds(getWrappedLine(_LineContents.size()-1), TempTopLeft, TempBottomRight);
        PreferredSize[0] = getPreferredSize().x();
        PreferredSize[1] = osgMax<UInt32>(getMinSize().y(), _LineContents.back()._VerticalOffset + TempBottomRight.y());
        if(getPreferredSize() != PreferredSize)
        {
            beginEditCP(TextAreaPtr(this), PreferredSizeFieldMask);
                setPreferredSize(PreferredSize);
            endEditCP(TextAreaPtr(this), PreferredSizeFieldMask);
        }
    }
    
	if(whichField & CaretPositionFieldMask)
	{
		//Check to see if the caret is visible
		Int32 CaretLine(getCaretLine());
		if(CaretLine>=0 && !isLineVisible(CaretLine))
		{
			scrollToLine(CaretLine);
		}
	}

	Inherited::changed(whichField, origin);
}

void TextArea::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TextArea NI" << std::endl;
}



void TextArea::MouseDownListener::keyTyped(const KeyEvent& e)
{
    if(e.getKey() == KeyEvent::KEY_ESCAPE)
    {
	    if(_TextArea->getParentWindow() != NullFC && _TextArea->getParentWindow()->getDrawingSurface()!=NullFC&& _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	    {
            _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
            _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
            _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
        }
    }
}

void TextArea::MouseDownListener::mouseReleased(const MouseEvent& e)
{
	if(_TextArea->getParentWindow() != NullFC && _TextArea->getParentWindow()->getDrawingSurface()!=NullFC&& _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer() != NullFC)
	{
        _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
        _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer()->removeKeyListener(this);
        _TextArea->getParentWindow()->getDrawingSurface()->getEventProducer()->removeMouseMotionListener(this);
    }
}

void TextArea::MouseDownListener::mouseDragged(const MouseEvent& e)
{
    _TextArea->mouseDraggedAfterArming(e);
}
/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGTEXTAREABASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTEXTAREABASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTEXTAREAFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

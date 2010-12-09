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

#include "OSGTextArea.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGStringUtils.h"
#include "OSGUIDrawUtils.h"
#include "OSGScrollBar.h"
#include "OSGUIViewport.h"

#include "OSGLookAndFeelManager.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextAreaBase.cpp file.
// To modify it, please change the .fcd file (OSGTextArea.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextArea::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void TextArea::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{	
    //Text Color
    Color4f TextColor = getDrawnTextColor();
	for(Int32 i = 0; i < _LineContents.size(); i++)//draw each line seperately
	{	
        if(getFont() != NULL)
        {
            if(_LineContents[i]._VerticalOffset > getClipBottomRight().y() || ( i+1<_LineContents.size() && _LineContents[i+1]._VerticalOffset < getClipTopLeft().y()))
            {
                continue;
            }
		    //draw like normal if not selected
		    if(_LineContents[i]._StartPosition >= _TextSelectionEnd || _LineContents[i]._EndPosition <= _TextSelectionStart || _TextSelectionStart >= _TextSelectionEnd)
		    {

			    TheGraphics->drawText(Pnt2f(_LineContents[i]._LeftHorizontalOffset, _LineContents[i]._VerticalOffset), getWrappedLine(i), getFont(), TextColor, getOpacity()*Opacity);
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
			    TheGraphics->drawText(offset,drawnText.substr(0, StartSelection), getFont(), TextColor, getOpacity()*Opacity);//draw before selection text
			    TheGraphics->drawRect(offset+Vec2f(getFont()->getBounds(drawnText.substr(0, StartSelection)).x(), 0), //draw selection rect
				    getFont()->getBounds(drawnText.substr(0, EndSelection))+Vec2f(offset),
				    getSelectionBoxColor(), getOpacity()*Opacity);
			    TheGraphics->drawText(offset+Vec2f(getFont()->getBounds(drawnText.substr(0, StartSelection)).x(), 0), //draw selected text
				    drawnText.substr(StartSelection, EndSelection-StartSelection), getFont(), getSelectionTextColor(), getOpacity()*Opacity);
			    TheGraphics->drawText(offset+Vec2f(getFont()->getBounds(drawnText.substr(0, EndSelection)).x(), 0), //draw after selection text
				    drawnText.substr(EndSelection, drawnText.size()-EndSelection), getFont(), TextColor, getOpacity()*Opacity);
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
				.5, TextColor, getOpacity()*Opacity);
		}
	}
}

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
	Vec2f Offset(_LineContents[line]._LeftHorizontalOffset, _LineContents[line]._VerticalOffset);
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
	if(getParentContainer() != NULL && getParentContainer()->getType().isDerivedFrom(UIViewport::getClassType()))
	{
		//Get the bounds of this line
		Pnt2f TempTopLeft, TempBottomRight;
		Vec2f Offset(_LineContents[line]._LeftHorizontalOffset, _LineContents[line]._VerticalOffset);
		getFont()->getBounds(getWrappedLine(line), TempTopLeft, TempBottomRight);

		TempTopLeft = TempTopLeft + Offset;
		TempBottomRight = TempBottomRight + Offset;

		dynamic_cast<UIViewport*>(getParentContainer())->maximizeVisibility(TempTopLeft, TempBottomRight);
	}
}

void TextArea::focusGained(FocusEventDetails* const e)
{
	if( getParentWindow() != NULL &&
		getParentWindow()->getParentDrawingSurface() != NULL &&
		getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        _CaretUpdateConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&TextArea::handleCaretUpdate, this, _1));
	}
	Inherited::focusGained(e);
}

void TextArea::focusLost(FocusEventDetails* const e)
{
    _CaretUpdateConnection.disconnect();
	Inherited::focusLost(e);
}

void TextArea::keyTyped(KeyEventDetails* const e)//broken
{
	if(getEnabled() && getEditable())
	{
		if(e->getKey() == e->KEY_ENTER)
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

    switch(e->getKey())
    {
    case KeyEventDetails::KEY_HOME:
        moveCaretToBeginOfLine();
        break;
    case KeyEventDetails::KEY_END:
        moveCaretToEndOfLine();
        break;
    case KeyEventDetails::KEY_UP:
    case KeyEventDetails::KEY_KEYPAD_UP:
        moveCaretLine(-1);
        break;
    case KeyEventDetails::KEY_DOWN:
    case KeyEventDetails::KEY_KEYPAD_DOWN:
        moveCaretLine(1);
        break;
    case KeyEventDetails::KEY_PAGE_UP:
        moveCaretLine(-static_cast<Int32>(numVisibleLines()));
        break;
    case KeyEventDetails::KEY_PAGE_DOWN:
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
                    setCaretPosition(NewPosition);
            }
            if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!=NULL&&getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL 
                && getParentWindow()->getParentDrawingSurface()->getEventProducer()->getKeyModifiers() & KeyEventDetails::KEY_MODIFIER_SHIFT)
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
			setCaretPosition(_LineContents[CaretLine]._EndPosition);
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
			setCaretPosition(_LineContents[CaretLine]._StartPosition);
	}
}

UInt32 TextArea::numLines(void) const
{
    return _LineContents.size();
}

void TextArea::mouseClicked(MouseEventDetails* const e)
{	
	Int32 Position(0);
	Int32 BeginWord = 0;
	Int32 EndWord = getText().size();
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{

		if(e->getClickCount() == 2)
		{

			//set caret position to proper place
			Position = findTextPosition(DrawingSurfaceToComponent(e->getLocation(), this));
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
		    setCaretPosition(EndWord);
		}
	}
	Inherited::mouseClicked(e);

}

void TextArea::mousePressed(MouseEventDetails* const e)
{
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{
		//set caret position to proper place
			setCaretPosition( findTextPosition(DrawingSurfaceToComponent(e->getLocation(), this)));

		_TextSelectionEnd = getCaretPosition();
		_TextSelectionStart = getCaretPosition();
	}
	if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!=NULL&& getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
	{
        _MouseDownKeyTypedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyTyped(boost::bind(&TextArea::handleMouseDownKeyTyped, this, _1));
        _MouseDownMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&TextArea::handleMouseDownMouseReleased, this, _1));
        _MouseDownMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&TextArea::handleMouseDownMouseDragged, this, _1));
    }
	Inherited::mousePressed(e);
}

Int32 TextArea::findTextPosition(OSG::Pnt2f Input)
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


bool TextArea::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool TextArea::getScrollableWidthMinTracksViewport(void)
{
    return false;
}

Int32 TextArea::getScrollableUnitIncrement(const Pnt2f& VisibleRectTopLeft, const Pnt2f& VisibleRectBottomRight, const UInt32& orientation, const Int32& direction)
{
    if(getFont() != NULL)
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

void TextArea::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _CaretUpdateConnection.disconnect();
    _MouseDownKeyTypedConnection.disconnect();
    _MouseDownMouseReleasedConnection.disconnect();
    _MouseDownMouseDraggedConnection.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TextArea::TextArea(void) :
    Inherited(),
		_CurrentCaretBlinkElps(0.0)
{
}

TextArea::TextArea(const TextArea &source) :
    Inherited(source),
		_CurrentCaretBlinkElps(0.0)
{
}

TextArea::~TextArea(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextArea::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    if((whichField & TextFieldMask ||
       whichField & LineWrapFieldMask ||
       whichField & WrapStyleWordFieldMask ||
       whichField & TabSizeFieldMask ||
       whichField & FontFieldMask ||
       whichField & SizeFieldMask) &&
	   getFont() != NULL)
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

			while(getText()[i] == ' ')
			{
				i++;
			}
			getFont()->getBounds(getText().substr(XPosition, i-XPosition+1), TempTopLeft, TempBottomRight);
		    if(getText()[i] == '\n')
		    {
			    XPosition = i;
			    _LineContents[YPosition]._EndPosition = i;
			    _LineContents.push_back(TextLine());
			    ++YPosition;
			    _LineContents[YPosition]._StartPosition = _LineContents[YPosition-1]._EndPosition+1;
		    }
			if(TempBottomRight.x() > BottomRight.x())
			{
				if(!getWrapStyleWord())
				{
					XPosition = i;
					_LineContents[YPosition]._EndPosition = i;
					_LineContents.push_back(TextLine());
					++YPosition;
					_LineContents[YPosition]._StartPosition = i;
				}
				else
				{
					Int32 j;
					brokeAtWord = false; 
					for(j = i; j > _LineContents[YPosition]._StartPosition; --j)
					{
						if(!isWordChar(getText()[j])&& !isPunctuationChar(getText()[j]))
						{
							brokeAtWord = true;
							break;
						}
					}
					if(!brokeAtWord)
					{
						XPosition = i;
						_LineContents[YPosition]._EndPosition = i-1;
						_LineContents.push_back(TextLine());
						++YPosition;
						_LineContents[YPosition]._StartPosition = i;
					}
					else
					{
						i = j;		
						while(getText()[i] == ' ')
						{
							i++;
						}
						XPosition = i;
						_LineContents[YPosition]._EndPosition = i-1;
						_LineContents.push_back(TextLine());
						++YPosition;
						_LineContents[YPosition]._StartPosition = i;
					}
				}

			}
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
            setPreferredSize(PreferredSize + getBorderingLength());
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

    Inherited::changed(whichField, origin, details);
}

void TextArea::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextArea NI" << std::endl;
}

void TextArea::handleCaretUpdate(UpdateEventDetails* const e)
{
   _CurrentCaretBlinkElps += e->getElapsedTime();
   if(_CurrentCaretBlinkElps > LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
   {
       Int32 Div = _CurrentCaretBlinkElps/LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
	   _CurrentCaretBlinkElps -= static_cast<OSG::Time>(Div)*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
   }
}

void TextArea::handleMouseDownKeyTyped(KeyEventDetails* const e)
{
    if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        _MouseDownKeyTypedConnection.disconnect();
        _MouseDownMouseReleasedConnection.disconnect();
        _MouseDownMouseDraggedConnection.disconnect();
    }
}

void TextArea::handleMouseDownMouseReleased(MouseEventDetails* const e)
{
    _MouseDownKeyTypedConnection.disconnect();
    _MouseDownMouseReleasedConnection.disconnect();
    _MouseDownMouseDraggedConnection.disconnect();
}

void TextArea::handleMouseDownMouseDragged(MouseEventDetails* const e)
{
	Int32 OriginalPosition = getCaretPosition();
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{
		//set caret position to proper place
		setCaretPosition( findTextPosition(DrawingSurfaceToComponent(e->getLocation(), this)));
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

OSG_END_NAMESPACE

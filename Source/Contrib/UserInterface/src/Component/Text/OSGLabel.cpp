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

#include "OSGLabel.h"
#include "OSGUIDrawUtils.h"
#include "OSGStringUtils.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLabelBase.cpp file.
// To modify it, please change the .fcd file (OSGLabel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Label::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f Label::getContentRequestedSize(void) const
{
    Pnt2f TextTopLeft(0.0f,0.0f), TextBottomRight(0.0f,0.0f);
    if(getFont() != NULL)
    {
        getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
    }

	return (TextBottomRight - TextTopLeft) + Vec2f(2.0,2.0);
}

void Label::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    if(getText() != "" && getFont() != NULL)
    {
        Pnt2f TopLeft, BottomRight;
        Pnt2f TempPos;
        getInsideBorderBounds(TopLeft, BottomRight);
        TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, getFont()->getBounds(getText()), getAlignment().y(), getAlignment().x());
        
        //Text Color
        Color4f TextColor = getDrawnTextColor();

	    if(_TextSelectionStart >= _TextSelectionEnd)
	    {
	        TheGraphics->drawText(TempPos, getText(), getFont(), TextColor, getOpacity()*Opacity);
	    }
	    else
	    {
            //Draw Text Befor the Selection
		    TheGraphics->drawText(TempPos, getText().substr(0, _TextSelectionStart), getFont(), TextColor, getOpacity()*Opacity);

		    //Draw Selection
            Pnt2f TextTopLeft, TextBottomRight;
            getFont()->getBounds(getText().substr(0, _TextSelectionStart), TextTopLeft, TextBottomRight);

		    TheGraphics->drawQuad(TempPos + Vec2f(TextBottomRight.x(),0),
			    TempPos + Vec2f(getFont()->getBounds(getText().substr(0, _TextSelectionEnd)).x(), 0),
			    TempPos + Vec2f(getFont()->getBounds(getText().substr(0, _TextSelectionEnd))),
			    TempPos + Vec2f(TextBottomRight),
			    getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(), getOpacity()*Opacity);

            //Draw Selected Text
		    TheGraphics->drawText(TempPos + Vec2f(TextBottomRight.x(), 0), 
			    getText().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart), getFont(), getSelectionTextColor(), getOpacity()*Opacity);

		    //Draw Text After selection
            getFont()->getBounds(getText().substr(0, _TextSelectionEnd), TextTopLeft, TextBottomRight);
		    TheGraphics->drawText(TempPos + Vec2f(TextBottomRight.x(), 0),
			    getText().substr(_TextSelectionEnd, getText().size()-_TextSelectionEnd), getFont(), TextColor, getOpacity()*Opacity);
	    }
    }
}

void Label::calculateTextBounds(const UInt32 StartIndex, const UInt32 EndIndex, Pnt2f& TopLeft, Pnt2f& BottomRight)
{
    Pnt2f ComponentTopLeft, ComponentBottomRight;
    getInsideBorderBounds(ComponentTopLeft, ComponentBottomRight);

    Pnt2f AlignmentOffset = calculateAlignment(ComponentTopLeft, ComponentBottomRight-ComponentTopLeft, getFont()->getBounds(getText()), getAlignment().y(), getAlignment().x());

	getFont()->getBounds(getText().substr(StartIndex, EndIndex), TopLeft, BottomRight);
	TopLeft = TopLeft + Vec2f(AlignmentOffset);
	BottomRight = BottomRight + Vec2f(AlignmentOffset);
}

void Label::mouseClicked(MouseEventDetails* const e)
{	
    if(getTextSelectable())
    {
	    Int32 Position(0);
	    Int32 BeginWord = 0;
	    Int32 EndWord = getText().size();
	    if(e->getButton() == MouseEventDetails::BUTTON1)
	    {

		    if(e->getClickCount() == 2)
		    {
			    Pnt2f TopLeftText, BottomRightText, TempPos;
			    Pnt2f TopLeftText1, BottomRightText1;
			    Pnt2f TopLeft, BottomRight;
			    getFont()->getBounds(getText(), TopLeftText, BottomRightText);
			    getInsideBorderBounds(TopLeft, BottomRight);
                TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getAlignment().y(), getAlignment().x());

			    //set caret position to proper place
			    //if the mouse is to the left of the text, set it to the begining.
			    Pnt2f temp = DrawingSurfaceToComponent(e->getLocation(), this);
			    if(DrawingSurfaceToComponent(e->getLocation(), this).x() <= TempPos.x())
			    {
				    Position = 0;
			    }//if the mouse is to the right of the text, set it to the end
			    else if(DrawingSurfaceToComponent(e->getLocation(), this).x() >= TempPos.x()+BottomRightText.x())
			    {
				    Position = getText().size();
			    }
			    else
			    {
				    for(UInt32 i = 0; i <getText().size(); i++)
				    {		
					    calculateTextBounds(0,i, TopLeftText, BottomRightText);
					    calculateTextBounds(0,i+1, TopLeftText1, BottomRightText1);
					    if(DrawingSurfaceToComponent(e->getLocation(), this).x()>BottomRightText.x()
					       && DrawingSurfaceToComponent(e->getLocation(), this).x() <= BottomRightText1.x())//check to see if it's in the right spot
					    {
						    Position = i;
						    break;
					    }
				    }
			    }
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
    }
	Inherited::mouseClicked(e);

}


void Label::mousePressed(MouseEventDetails* const e)
{
    if(getTextSelectable())
    {
	    Pnt2f TopLeftText, BottomRightText, TempPos;
	    Pnt2f TopLeftText1, BottomRightText1;
	    Pnt2f TopLeft, BottomRight;
	    getFont()->getBounds(getText(), TopLeftText, BottomRightText);
        getInsideBorderBounds(TopLeft, BottomRight);
        TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getAlignment().y(), getAlignment().x());
	    if(e->getButton() == MouseEventDetails::BUTTON1)
	    {
		    //set caret position to proper place
		    //if the mouse is to the left of the text, set it to the begining.
		    Pnt2f temp = DrawingSurfaceToComponent(e->getLocation(), this);
		    if(DrawingSurfaceToComponent(e->getLocation(), this).x() <= TempPos.x())
		    {
			    setCaretPosition(0);
		    }		//if the mouse is to the right of the text, set it to the end
		    else if(DrawingSurfaceToComponent(e->getLocation(), this).x() >= TempPos.x()+BottomRightText.x())
		    {
			    setCaretPosition(getText().size());
		    }
		    else
		    {
			    for(UInt32 i = 0; i <getText().size(); i++)
			    {		
				    calculateTextBounds(0,i, TopLeftText, BottomRightText);
				    calculateTextBounds(0,i+1, TopLeftText1, BottomRightText1);
				    if(DrawingSurfaceToComponent(e->getLocation(), this).x()>BottomRightText.x()
				       && DrawingSurfaceToComponent(e->getLocation(), this).x() <= BottomRightText1.x())//check to see if it's in the right spot
				    {
					    if(DrawingSurfaceToComponent(e->getLocation(), this).x() <= (BottomRightText1.x()-BottomRightText.x())/2.0+0.5 + BottomRightText.x())
					    {
						    setCaretPosition(i);
						    break;
					    }
					    else
					    {
						    setCaretPosition(i+1);
						    break;
					    }
				    }
			    }
		    }

		    _TextSelectionEnd = getCaretPosition();
		    _TextSelectionStart = getCaretPosition();
	    }
    }
	Inherited::mousePressed(e);
}

void Label::mouseDragged(MouseEventDetails* const e)
{
    if(getTextSelectable())
    {
	    Pnt2f TopLeftText, BottomRightText, TempPos;
	    Pnt2f TopLeftText1, BottomRightText1;
	    Pnt2f TopLeft, BottomRight;
	    Int32 OriginalPosition = getCaretPosition();
	    getFont()->getBounds(getText(), TopLeftText, BottomRightText);
        getInsideBorderBounds(TopLeft, BottomRight);
        TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getAlignment().y(), getAlignment().x());
	    if(e->getButton() == MouseEventDetails::BUTTON1)
	    {
		    //set caret position to proper place
		    //if the mouse is to the left of the text, set it to the begining.
		    Pnt2f temp = DrawingSurfaceToComponent(e->getLocation(), this);
		    if(DrawingSurfaceToComponent(e->getLocation(), this).x() <= TempPos.x())
		    {
			    setCaretPosition(0);
		    }		//if the mouse is to the right of the text, set it to the end
		    else if(DrawingSurfaceToComponent(e->getLocation(), this).x() >= TempPos.x()+BottomRightText.x())
		    {
			    setCaretPosition(getText().size());
		    }
		    else
		    {
			    //check letter by letter for the mouse's position
			    for(UInt32 i = 0; i <getText().size(); i++)
			    {		
				    calculateTextBounds(0,i, TopLeftText, BottomRightText);
				    calculateTextBounds(0,i+1, TopLeftText1, BottomRightText1);
				    if(DrawingSurfaceToComponent(e->getLocation(), this).x()>BottomRightText.x()
				       && DrawingSurfaceToComponent(e->getLocation(), this).x() <= BottomRightText1.x())//check to see if it's in the right spot
				    {
					    if(DrawingSurfaceToComponent(e->getLocation(), this).x() < (BottomRightText1.x()-BottomRightText.x())/2.0 + BottomRightText.x())
					    {

						    setCaretPosition(i);
						    break;
					    }
					    else
					    {

						    setCaretPosition(i+1);
						    break;
					    }
				    }
			    }
		    }
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
	

	Inherited::mouseDragged(e);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Label::Label(void) :
    Inherited()
{
}

Label::Label(const Label &source) :
    Inherited(source)
{
}

Label::~Label(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Label::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Label::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Label NI" << std::endl;
}

OSG_END_NAMESPACE

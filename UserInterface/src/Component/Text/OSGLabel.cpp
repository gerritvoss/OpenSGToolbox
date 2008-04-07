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

#include <OpenSG/OSGConfig.h>

#include "OSGLabel.h"
#include "Util/OSGUIDrawUtils.h"
#include <OpenSG/Input/OSGStringUtils.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Label
A UI Label. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Label::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f Label::getContentRequestedSize(void) const
{
    Pnt2f TextTopLeft, TextBottomRight;
    getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

	return (TextBottomRight - TextTopLeft) + Vec2f(2.0,2.0);
}

void Label::drawInternal(const GraphicsPtr TheGraphics) const
{
    Pnt2f TopLeft, BottomRight;
    Pnt2f TempPos;
    getInsideBorderBounds(TopLeft, BottomRight);
    TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, getFont()->getBounds(getText()), getVerticalAlignment(), getHorizontalAlignment());
    
    //Text Color
    Color4f TextColor = getDrawnTextColor();
    if(getText() != "" && getFont() != NullFC)
    {

	    if(_TextSelectionStart >= _TextSelectionEnd)
	    {
	        TheGraphics->drawText(TempPos, getText(), getFont(), TextColor, getOpacity());
	    }
	    else
	    {
            //Draw Text Befor the Selection
		    TheGraphics->drawText(TempPos, getText().substr(0, _TextSelectionStart), getFont(), TextColor, getOpacity());

		    //Draw Selection
            Pnt2f TextTopLeft, TextBottomRight;
            getFont()->getBounds(getText().substr(0, _TextSelectionStart), TextTopLeft, TextBottomRight);

		    TheGraphics->drawQuad(TempPos + Vec2f(TextBottomRight.x(),0),
			    TempPos + Vec2f(getFont()->getBounds(getText().substr(0, _TextSelectionEnd)).x(), 0),
			    TempPos + Vec2f(getFont()->getBounds(getText().substr(0, _TextSelectionEnd))),
			    TempPos + Vec2f(TextBottomRight),
			    getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(), getOpacity());

            //Draw Selected Text
		    TheGraphics->drawText(TempPos + Vec2f(TextBottomRight.x(), 0), 
			    getText().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart), getFont(), getSelectionTextColor(), getOpacity());

		    //Draw Text After selection
            getFont()->getBounds(getText().substr(0, _TextSelectionEnd), TextTopLeft, TextBottomRight);
		    TheGraphics->drawText(TempPos + Vec2f(TextBottomRight.x(), 0),
			    getText().substr(_TextSelectionEnd, getText().size()-_TextSelectionEnd), getFont(), TextColor, getOpacity());
	    }
    }
}

void Label::calculateTextBounds(const UInt32 StartIndex, const UInt32 EndIndex, Pnt2f& TopLeft, Pnt2f& BottomRight)
{
    Pnt2f ComponentTopLeft, ComponentBottomRight;
    getInsideBorderBounds(ComponentTopLeft, ComponentBottomRight);

    Pnt2f AlignmentOffset = calculateAlignment(ComponentTopLeft, ComponentBottomRight-ComponentTopLeft, getFont()->getBounds(getText()), getVerticalAlignment(), getHorizontalAlignment());

	getFont()->getBounds(getText().substr(StartIndex, EndIndex), TopLeft, BottomRight);
	TopLeft = TopLeft + Vec2f(AlignmentOffset);
	BottomRight = BottomRight + Vec2f(AlignmentOffset);
}

void Label::mouseClicked(const MouseEvent& e)
{	
    if(getTextSelectable())
    {
	    Int32 Position(0);
	    Int32 BeginWord = 0;
	    Int32 EndWord = getText().size();
	    if(e.getButton() == e.BUTTON1)
	    {

		    if(e.getClickCount() == 2)
		    {
			    Pnt2f TopLeftText, BottomRightText, TempPos;
			    Pnt2f TopLeftText1, BottomRightText1;
			    Pnt2f TopLeft, BottomRight;
			    getFont()->getBounds(getText(), TopLeftText, BottomRightText);
			    getInsideBorderBounds(TopLeft, BottomRight);
                TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getVerticalAlignment(), getHorizontalAlignment());

			    //set caret position to proper place
			    //if the mouse is to the left of the text, set it to the begining.
			    Pnt2f temp = DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this));
			    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() <= TempPos.x())
			    {
				    Position = 0;
			    }//if the mouse is to the right of the text, set it to the end
			    else if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() >= TempPos.x()+BottomRightText.x())
			    {
				    Position = getText().size();
			    }
			    else
			    {
				    for(UInt32 i = 0; i <getText().size(); i++)
				    {		
					    calculateTextBounds(0,i, TopLeftText, BottomRightText);
					    calculateTextBounds(0,i+1, TopLeftText1, BottomRightText1);
					    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x()>BottomRightText.x()
					       && DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
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


void Label::mousePressed(const MouseEvent& e)
{
    if(getTextSelectable())
    {
	    Pnt2f TopLeftText, BottomRightText, TempPos;
	    Pnt2f TopLeftText1, BottomRightText1;
	    Pnt2f TopLeft, BottomRight;
	    getFont()->getBounds(getText(), TopLeftText, BottomRightText);
        getInsideBorderBounds(TopLeft, BottomRight);
        TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getVerticalAlignment(), getHorizontalAlignment());
	    if(e.getButton() == e.BUTTON1)
	    {
		    //set caret position to proper place
		    //if the mouse is to the left of the text, set it to the begining.
		    Pnt2f temp = DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this));
		    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() <= TempPos.x())
		    {
			    setCaretPosition(0);
		    }		//if the mouse is to the right of the text, set it to the end
		    else if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() >= TempPos.x()+BottomRightText.x())
		    {
			    setCaretPosition(getText().size());
		    }
		    else
		    {
			    for(UInt32 i = 0; i <getText().size(); i++)
			    {		
				    calculateTextBounds(0,i, TopLeftText, BottomRightText);
				    calculateTextBounds(0,i+1, TopLeftText1, BottomRightText1);
				    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x()>BottomRightText.x()
				       && DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
				    {
					    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() <= (BottomRightText1.x()-BottomRightText.x())/2.0+0.5 + BottomRightText.x())
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

void Label::mouseDragged(const MouseEvent& e)
{
    if(getTextSelectable())
    {
	    Pnt2f TopLeftText, BottomRightText, TempPos;
	    Pnt2f TopLeftText1, BottomRightText1;
	    Pnt2f TopLeft, BottomRight;
	    Int32 OriginalPosition = getCaretPosition();
	    getFont()->getBounds(getText(), TopLeftText, BottomRightText);
        getInsideBorderBounds(TopLeft, BottomRight);
        TempPos = calculateAlignment(TopLeft, BottomRight-TopLeft, BottomRightText-TopLeftText, getVerticalAlignment(), getHorizontalAlignment());
	    if(e.getButton() == e.BUTTON1)
	    {
		    //set caret position to proper place
		    //if the mouse is to the left of the text, set it to the begining.
		    Pnt2f temp = DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this));
		    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() <= TempPos.x())
		    {
			    setCaretPosition(0);
		    }		//if the mouse is to the right of the text, set it to the end
		    else if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() >= TempPos.x()+BottomRightText.x())
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
				    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x()>BottomRightText.x()
				       && DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() <= BottomRightText1.x())//check to see if it's in the right spot
				    {
					    if(DrawingSurfaceToComponent(e.getLocation(), LabelPtr(this)).x() < (BottomRightText1.x()-BottomRightText.x())/2.0 + BottomRightText.x())
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

void Label::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Label::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Label NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLABELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLABELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLABELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


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

#include "OSGTextField.h"
#include "OSGUIDrawUtils.h"

#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGWindowEventProducer.h"
#include "OSGStringUtils.h"

#include "OSGLookAndFeelManager.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGTextFieldBase.cpp file.
// To modify it, please change the .fcd file (OSGTextField.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TextField::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f TextField::getContentRequestedSize(void) const
{
    Pnt2f TextTopLeft, TextBottomRight;
    getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

	return (TextBottomRight - TextTopLeft) + Vec2f(2.0,2.0);
}

std::string TextField::getDrawnText(void) const
{
	return getText();
}

void TextField::drawInternal(Graphics* const TheGraphics, Real32 Opacity) const
{
    Pnt2f Alignment;
    Pnt2f TopLeft, BottomRight;
    getInsideBorderBounds(TopLeft, BottomRight);

    //Text Color
    Color4f TextColor = getDrawnTextColor();

    if(getDrawnText() != "" && getFont() != NULL)
    {
        Alignment = calculateAlignment(TopLeft, BottomRight-TopLeft, getFont()->getBounds(getDrawnText()), getAlignment().y(), getAlignment().x());


        if(_TextSelectionStart >= _TextSelectionEnd)
        {
            TheGraphics->drawText(Alignment, getDrawnText(), getFont(), TextColor, getOpacity()*Opacity);
        }
        else
        {
            //Draw Text Befor the Selection
            TheGraphics->drawText(Alignment, getDrawnText().substr(0, _TextSelectionStart), getFont(), TextColor, getOpacity()*Opacity);

            //Draw Selection
            Pnt2f TextTopLeft, TextBottomRight;
            getFont()->getBounds(getDrawnText().substr(0, _TextSelectionStart), TextTopLeft, TextBottomRight);

            TheGraphics->drawQuad(Alignment + Vec2f(TextBottomRight.x(),0),
                                  Alignment + Vec2f(getFont()->getBounds(getDrawnText().substr(0, _TextSelectionEnd)).x(), 0),
                                  Alignment + Vec2f(getFont()->getBounds(getDrawnText().substr(0, _TextSelectionEnd))),
                                  Alignment + Vec2f(TextBottomRight),
                                  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(),  getSelectionBoxColor(), getOpacity());

            //Draw Selected Text
            TheGraphics->drawText(Alignment + Vec2f(TextBottomRight.x(), 0), 
                                  getDrawnText().substr(_TextSelectionStart, _TextSelectionEnd-_TextSelectionStart), getFont(), getSelectionTextColor(), getOpacity()*Opacity);

            //Eraw Text After selection
            getFont()->getBounds(getDrawnText().substr(0, _TextSelectionEnd), TextTopLeft, TextBottomRight);
            TheGraphics->drawText(Alignment + Vec2f(TextBottomRight.x(), 0),
                                  getDrawnText().substr(_TextSelectionEnd, getDrawnText().size()-_TextSelectionEnd), getFont(), TextColor, getOpacity()*Opacity);
        }
    }
    else
    {
        Alignment = calculateAlignment(TopLeft, BottomRight-TopLeft, getFont()->getBounds("|"), getAlignment().y(), getAlignment().x());
    }

    if(getEnabled() && getEditable() && getFocused() && _CurrentCaretBlinkElps <= 0.5*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
    {
        //Draw the caret
        TheGraphics->drawLine(Alignment+Vec2f(getFont()->getBounds(getDrawnText().substr(0, getCaretPosition())).x(), 0),
                              Alignment + Vec2f(getFont()->getBounds(getDrawnText().substr(0, getCaretPosition())).x(),  getFont()->getBounds(getDrawnText()).y()), 
                              .5, TextColor, getOpacity()*Opacity);
    }

    //Draw the Descriptive text if empty
    if(getDrawnText().empty() && !getEmptyDescText().empty()  && getEmptyDescTextFont() != NULL)
    {
        Alignment = calculateAlignment(TopLeft, BottomRight-TopLeft, getEmptyDescTextFont()->getBounds(getEmptyDescText()), getAlignment().y(), getAlignment().x());
        TheGraphics->drawText(Alignment, getEmptyDescText(), getEmptyDescTextFont(), getEmptyDescTextColor(), getOpacity()*Opacity);
    }
}

void TextField::keyTyped(KeyEventDetails* const e)
{
	if(getEnabled())
	{
		switch(e->getKey())
        {
        case KeyEventDetails::KEY_ENTER:
			produceActionPerformed();
        case KeyEventDetails::KEY_TAB:
	        Component::keyTyped(e); //Tab should not be inserted in a TextField
            break;
        default:
	        Inherited::keyTyped(e);
            break;
        }
	}
    else
    {
	    Inherited::keyTyped(e);
    }
}

void TextField::mouseClicked(MouseEventDetails* const e)
{	
	Int32 Position(0);
	Int32 BeginWord = 0;
	Int32 EndWord = getDrawnText().size();
	if(e->getButton() == MouseEventDetails::BUTTON1)
	{

		if(e->getClickCount() == 2)
		{
			Pnt2f TopLeftText, BottomRightText, TempPos;
			Pnt2f TopLeftText1, BottomRightText1;
			Pnt2f TopLeft, BottomRight;
			getFont()->getBounds(getDrawnText(), TopLeftText, BottomRightText);
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
				Position = getDrawnText().size();
			}
			else
			{
				for(UInt32 i = 0; i <getDrawnText().size(); i++)
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
			if(isPunctuationChar(getDrawnText()[Position]))
			{
				EndWord = Position + 1;
				BeginWord = Position;
			}
			else{
				for(Int32 i = Position; i < getDrawnText().size(); i++)
				{
					if(!isWordChar(getDrawnText()[i]))
					{
						EndWord = i;
						break;
					}
				}
				for(Int32 i = Position; i >= 0; i--)
				{
					if(!isWordChar(getDrawnText()[i]))
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


void TextField::mousePressed(MouseEventDetails* const e)
{
	Pnt2f TopLeftText, BottomRightText, TempPos;
	Pnt2f TopLeftText1, BottomRightText1;
	Pnt2f TopLeft, BottomRight;
	getFont()->getBounds(getDrawnText(), TopLeftText, BottomRightText);
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
			setCaretPosition(getDrawnText().size());
		}
		else
		{
			for(UInt32 i = 0; i <getDrawnText().size(); i++)
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
	if(getParentWindow() != NULL && getParentWindow()->getParentDrawingSurface()!=NULL&& getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
	{
        _MouseDownKeyTypedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectKeyTyped(boost::bind(&TextField::handleMouseDownKeyTyped, this, _1));
        _MouseDownMouseReleasedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseReleased(boost::bind(&TextField::handleMouseDownMouseReleased, this, _1));
        _MouseDownMouseDraggedConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectMouseDragged(boost::bind(&TextField::handleMouseDownMouseDragged, this, _1));
    }
	Inherited::mousePressed(e);
}

void TextField::calculateTextBounds(const UInt32 StartIndex, const UInt32 EndIndex, Pnt2f& TopLeft, Pnt2f& BottomRight)
{
    Pnt2f ComponentTopLeft, ComponentBottomRight;
    getInsideBorderBounds(ComponentTopLeft, ComponentBottomRight);

    Pnt2f AlignmentOffset = calculateAlignment(ComponentTopLeft, ComponentBottomRight-ComponentTopLeft, getFont()->getBounds(getDrawnText()), getAlignment().y(), getAlignment().x());

	getFont()->getBounds(getDrawnText().substr(StartIndex, EndIndex), TopLeft, BottomRight);
	TopLeft = TopLeft + Vec2f(AlignmentOffset);
	BottomRight = BottomRight + Vec2f(AlignmentOffset);
}


void TextField::produceActionPerformed(void)
{
    ActionEventDetailsUnrecPtr Details(ActionEventDetails::create(this, getTimeStamp()));

    Inherited::produceActionPerformed(Details);
}

void TextField::focusGained(FocusEventDetails* const e)
{
	if( getParentWindow() != NULL &&
		getParentWindow()->getParentDrawingSurface() != NULL &&
		getParentWindow()->getParentDrawingSurface()->getEventProducer() != NULL)
    {
        _CaretUpdateConnection = getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&TextField::handleCaretUpdate, this, _1));
	}
	Inherited::focusGained(e);
}

void TextField::focusLost(FocusEventDetails* const e)
{
    _CaretUpdateConnection.disconnect();

	Inherited::focusLost(e);
}

void TextField::detachFromEventProducer(void)
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

TextField::TextField(void) :
    Inherited(),
		_CurrentCaretBlinkElps(0.0)
{
}

TextField::TextField(const TextField &source) :
    Inherited(source),
		_CurrentCaretBlinkElps(0.0)
{
}

TextField::~TextField(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TextField::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void TextField::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump TextField NI" << std::endl;
}

void TextField::handleCaretUpdate(UpdateEventDetails* const e)
{
   _CurrentCaretBlinkElps += e->getElapsedTime();
   if(_CurrentCaretBlinkElps > LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate())
   {
       Int32 Div = _CurrentCaretBlinkElps/LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
	   _CurrentCaretBlinkElps -= static_cast<OSG::Time>(Div)*LookAndFeelManager::the()->getLookAndFeel()->getTextCaretRate();
   }
}

void TextField::handleMouseDownKeyTyped(KeyEventDetails* const e)
{
    if(e->getKey() == KeyEventDetails::KEY_ESCAPE)
    {
        _MouseDownKeyTypedConnection.disconnect();
        _MouseDownMouseReleasedConnection.disconnect();
        _MouseDownMouseDraggedConnection.disconnect();
    }
}

void TextField::handleMouseDownMouseReleased(MouseEventDetails* const e)
{
    _MouseDownKeyTypedConnection.disconnect();
    _MouseDownMouseReleasedConnection.disconnect();
    _MouseDownMouseDraggedConnection.disconnect();
}

void TextField::handleMouseDownMouseDragged(MouseEventDetails* const e)
{
	Pnt2f TopLeftText, BottomRightText, TempPos;
	Pnt2f TopLeftText1, BottomRightText1;
	Pnt2f TopLeft, BottomRight;
	Int32 OriginalPosition = getCaretPosition();
	getFont()->getBounds(getDrawnText(), TopLeftText, BottomRightText);
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
			setCaretPosition(getDrawnText().size());
		}
		else
		{
			//check letter by letter for the mouse's position
			for(UInt32 i = 0; i <getDrawnText().size(); i++)
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

OSG_END_NAMESPACE

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

#include "OSGButton.h"
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Button
A UI Button.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Button::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

BorderPtr Button::getDrawnBorder(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getActive())
        {
            return getActiveBorder();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverBorder();
        }
        else
        {
            return getBorder();
        }
    }
    else
    {
        return getDisabledBorder();
    }
}

UIBackgroundPtr Button::getDrawnBackground(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getActive())
        {
            return getActiveBackground();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverBackground();
        }
        else
        {
            return getBackground();
        }
    }
    else
    {
        return getDisabledBackground();
    }
}

Color4f Button::getDrawnTextColor(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getActive())
        {
            return getActiveTextColor();
        }
        else if(_MouseInComponentLastMouse)
        {
            return getRolloverTextColor();
        }
        else
        {
            return getTextColor();
        }
    }
    else
    {
        return getDisabledTextColor();
    }
}
void Button::drawInternal(const GraphicsPtr TheGraphics) const
{
   Pnt2s TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);
   //If I have Text Then Draw it
   if(getText() != "" && getFont() != NullFC)
   {
      //Calculate Alignment
      Pnt2s AlignedPosition;
      Pnt2s TextTopLeft, TextBottomRight;
      getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

      AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),getVerticalAlignment(), getHorizontalAlignment());

	  //Draw the Text
      TheGraphics->drawText(AlignedPosition, getText(), getFont(), getDrawnTextColor(), getOpacity());
   }
}

void Button::actionPreformed(const ActionEvent& e)
{
}

void Button::mouseClicked(const MouseEvent& e)
{
	Component::mouseClicked(e);
}

void Button::mouseEntered(const MouseEvent& e)
{
	if(_Armed)
	{
	    beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
		    ButtonPtr(this)->setActive(true);
	    endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
	}

	Component::mouseEntered(e);
}

void Button::mouseExited(const MouseEvent& e)
{
	if(_Armed)
	{
	    beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
		    ButtonPtr(this)->setActive(false);
	    endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
	}

	Component::mouseExited(e);
}

void Button::mousePressed(const MouseEvent& e)
{
	if(e.getButton()==MouseEvent::BUTTON1){
		beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
			ButtonPtr(this)->setActive(true);
		endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
        _Armed = true;
        
		if(getParentFrame() != NullFC && getParentFrame()->getDrawingSurface()!=NullFC&& getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
		{
            getParentFrame()->getDrawingSurface()->getEventProducer()->addMouseListener(&_ButtonArmedListener);
            if(getEnableActionOnMouseDownTime())
            {
                _ButtonArmedListener.reset();
                getParentFrame()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_ButtonArmedListener);
            }
        }
	}
	Component::mousePressed(e);
}

void Button::mouseReleased(const MouseEvent& e)
{	
	if(e.getButton() == MouseEvent::BUTTON1 && _Armed)
	{
		beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
			ButtonPtr(this)->setActive(false);
		endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
	   produceActionPerformed(ActionEvent(ButtonPtr(this), e.getTimeStamp()));
       _Armed = false;
	}
	Component::mouseReleased(e);
}

void Button::produceActionPerformed(const ActionEvent& e)
{
    actionPreformed(e);
    for(ActionListenerSetConstItor SetItor(_ActionListeners.begin()) ; SetItor != _ActionListeners.end() ; ++SetItor)
    {
	    (*SetItor)->actionPerformed(e);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Button::Button(void) :
    Inherited(),
		_ButtonArmedListener(ButtonPtr(this)),
        _Armed(false)
{
}

Button::Button(const Button &source) :
    Inherited(source),
		_ButtonArmedListener(ButtonPtr(this)),
        _Armed(false)
{
}

Button::~Button(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Button::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Button::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Button NI" << std::endl;
}

void Button::ButtonArmedListener::mouseReleased(const MouseEvent& e)
{
	if(e.getButton() == MouseEvent::BUTTON1)
	{
		Pnt2s MousePos = ViewportToDrawingSurface(e.getLocation(), _Button->getParentFrame()->getDrawingSurface(), e.getViewport());
        //If the Mouse is not within the button
        if(!_Button->isContained(MousePos))
        {
            //Then Disarm the button
            _Button->_Armed = false;
        }

		//Remove myself from the listener
        _Button->getParentFrame()->getDrawingSurface()->getEventProducer()->removeMouseListener(this);
        if(_Button->getEnableActionOnMouseDownTime())
        {
            _Button->getParentFrame()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
        }
	}
}

void Button::ButtonArmedListener::update(const UpdateEvent& e)
{
    if(_Button->isContained(_Button->getParentFrame()->getDrawingSurface()->getMousePosition()))
    {
        _ActionFireElps += e.getElapsedTime();
    }
    if(_ActionFireElps >= _Button->getActionOnMouseDownRate())
    {
        _Button->produceActionPerformed(ActionEvent(_Button, e.getTimeStamp()));
        _ActionFireElps -= osgfloor<Time>(_ActionFireElps/_Button->getActionOnMouseDownRate()) * _Button->getActionOnMouseDownRate();
    }
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
    static Char8 cvsid_hpp       [] = OSGBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


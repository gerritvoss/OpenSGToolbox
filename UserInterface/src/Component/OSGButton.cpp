/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGButton.h"

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

void Button::draw(const GraphicsPtr Graphics) const
{
	if (!getVisible())
		return;

    //Translate to my position
    glTranslatef(getPosition().x(), getPosition().y(), 0);

	if(!setupClipping(Graphics))
	{
		//Translate to my position
		glTranslatef(-getPosition().x(), -getPosition().y(), 0);
		return;
	}

	if(getActive())
	{
		//Draw My Border
		drawBorder(Graphics, getActiveBorder());

		//Draw My Background
		drawBackground(Graphics, getActiveBackground());
	}
	else
	{
		if(getEnabled())
		{
			//Draw My Border
			drawBorder(Graphics, getBorder());

			//Draw My Background
			drawBackground(Graphics, getBackground());
		}
		else
		{
			//Draw My Border
			drawBorder(Graphics, getDisabledBorder());

			//Draw My Background
			drawBackground(Graphics, getDisabledBackground());
		}
	}

    //Draw Internal
    drawInternal(Graphics);
    glTranslatef(-getPosition().x(), -getPosition().y(), 0);
    
    //Set Clipping to initial settings
    if(getClipping())
    {
		//TODO:Fix
        //if(!WasClippPlane0Enabled){glDisable(GL_CLIP_PLANE0);}
        //if(!WasClippPlane1Enabled){glDisable(GL_CLIP_PLANE1);}
        //if(!WasClippPlane2Enabled){glDisable(GL_CLIP_PLANE2);}
        //if(!WasClippPlane3Enabled){glDisable(GL_CLIP_PLANE3);}
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
      Vec2s TextBounds( TheGraphics->getTextBounds(getText(), getFont()));
      if(getVerticalAlignment() == VERTICAL_TOP)
      {
         //VerticalTop
         AlignedPosition[1] = TopLeft[1];
      }
      else if(getVerticalAlignment() == VERTICAL_BOTTOM)
      {
         //VerticalBottom
         AlignedPosition[1] = BottomRight[1]-TextBounds[1];
      }
      else if(getVerticalAlignment() == VERTICAL_CENTER)
      {
         //VerticalCenter
         AlignedPosition[1] = TopLeft[1]+0.5*(BottomRight[1]-TopLeft[1]-TextBounds[1]);
      }

      if(getHorizontalAlignment() == HORIZONTAL_LEFT)
      {
         //HorizontalLeft
         AlignedPosition[0] = TopLeft[0];
      }
      else if(getHorizontalAlignment() == HORIZONTAL_RIGHT)
      {
         //HorizontalRight
         AlignedPosition[0] = BottomRight[0]-TextBounds[0];
      }
      else if(getHorizontalAlignment() == HORIZONTAL_CENTER)
      {
         //HorizontalCenter
         AlignedPosition[0] = TopLeft[0]+0.5*(BottomRight[0]-TopLeft[0]-TextBounds[0]);
      }

	  //Foreground Color
	  Color4f ForeColor;
	  if(getEnabled())
	  {
		  ForeColor = getForegroundColor();
	  }
	  else
	  {
		  ForeColor = getDisabledForegroundColor();
	  }
      TheGraphics->drawText(AlignedPosition, getText(), getFont(), ForeColor, getOpacity());
   }
}

void Button::mouseClicked(const MouseEvent& e)
{
	Component::mouseClicked(e);
}

void Button::mouseEntered(const MouseEvent& e)
{

	Component::mouseEntered(e);
}

void Button::mouseExited(const MouseEvent& e)
{
	/*if(getActive())
	{
		if(getParentFrame() != NullFC &&
				   getParentFrame()->getDrawingSurface() != NullFC &&
				   getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
				{
	            }
	}*/
	beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
		ButtonPtr(this)->setActive(false);
	endEditCP(ButtonPtr(this), Button::ActiveFieldMask);

	Component::mouseExited(e);
}

void Button::mousePressed(const MouseEvent& e)
{
	if(e.getButton()==MouseEvent::BUTTON1){
		beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
			ButtonPtr(this)->setActive(true);
		endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
	}
	Component::mousePressed(e);
}

void Button::mouseReleased(const MouseEvent& e)
{	
	if(getActive())
	{
	   produceActionPerformed(ActionEvent(ButtonPtr(this), e.getTimeStamp()));
	}
	if(e.getButton() == MouseEvent::BUTTON1){
		beginEditCP(ButtonPtr(this), Button::ActiveFieldMask);
			ButtonPtr(this)->setActive(false);
		endEditCP(ButtonPtr(this), Button::ActiveFieldMask);
	}
	Component::mouseReleased(e);
}

void Button::produceActionPerformed(const ActionEvent& e)
{
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
		_ButtonMouseListener(ButtonPtr(this))
{
}

Button::Button(const Button &source) :
    Inherited(source),
		_ButtonMouseListener(ButtonPtr(this))
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


Button::ButtonMouseListener::ButtonMouseListener(ButtonPtr TheButton) :
_Button(TheButton)
{
}

void Button::ButtonMouseListener::mouseClicked(const MouseEvent& e)
{
}

void Button::ButtonMouseListener::mouseEntered(const MouseEvent& e)
{
}

void Button::ButtonMouseListener::mouseExited(const MouseEvent& e)
{
}

void Button::ButtonMouseListener::mousePressed(const MouseEvent& e)
{
}

void Button::ButtonMouseListener::mouseReleased(const MouseEvent& e)
{
	if(e.getButton() == MouseEvent::BUTTON1)
	{
		beginEditCP(_Button, Button::ActiveFieldMask);
	        _Button->setActive(false);
		endEditCP(_Button, Button::ActiveFieldMask);
		//Remove myself from the listener
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


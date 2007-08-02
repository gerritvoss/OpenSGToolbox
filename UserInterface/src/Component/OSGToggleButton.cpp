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

#include "OSGToggleButton.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ToggleButton
A UI Button. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ToggleButton::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ToggleButton::ToggleButton(void) :
    Inherited()
{
}

ToggleButton::ToggleButton(const ToggleButton &source) :
    Inherited(source)
{
}

ToggleButton::~ToggleButton(void)
{
}


void ToggleButton::draw(const GraphicsPtr Graphics) const
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

	if(getSelected())
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

void  ToggleButton::produceButtonSelected(const ButtonSelectedEvent& e)
{
   for(ButtonSelectedListenerSetConstItor SetItor(_ButtonSelectedListeners.begin()) ; SetItor != _ButtonSelectedListeners.end() ; ++SetItor)
   {
      (*SetItor)->buttonSelected(e);
   }
}

void  ToggleButton::produceButtonDeselected(const ButtonSelectedEvent& e)
{
   for(ButtonSelectedListenerSetConstItor SetItor(_ButtonSelectedListeners.begin()) ; SetItor != _ButtonSelectedListeners.end() ; ++SetItor)
   {
      (*SetItor)->buttonDeselected(e);
   }
}
/*----------------------------- class specific ----------------------------*/

void ToggleButton::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    if( (whichField & SelectedFieldMask) )
    {
        if(getSelected())
        {
			produceButtonSelected( ButtonSelectedEvent(ComponentPtr(this),getSystemTime(),ButtonSelectedEvent::BUTTONSELECTED, ButtonPtr(this)) );    
        }
        else
        {
            produceButtonDeselected( ButtonSelectedEvent(ComponentPtr(this),getSystemTime(),ButtonSelectedEvent::BUTTONDESELECTED, ButtonPtr(this)) );    
        }
     }
}

void ToggleButton::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ToggleButton NI" << std::endl;
}

void ToggleButton::mouseReleased(const MouseEvent& e)
{
	if(e.getButton()==MouseEvent::BUTTON1){
		if(getActive()){
			if(getSelected())
			{
				beginEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
					setSelected(false);
				endEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
			}
			else
			{
				beginEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
					setSelected(true);
				endEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
			}
		}
		beginEditCP(ToggleButtonPtr(this), ToggleButton::ActiveFieldMask);
			setActive(false);
		endEditCP(ToggleButtonPtr(this), ToggleButton::ActiveFieldMask);
	}
	Component::mouseReleased(e);
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
    static Char8 cvsid_hpp       [] = OSGTOGGLEBUTTONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTOGGLEBUTTONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTOGGLEBUTTONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


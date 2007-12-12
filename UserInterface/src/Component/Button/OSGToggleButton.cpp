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
#include "Util/OSGUIDrawUtils.h"

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

void ToggleButton::drawInternal(const GraphicsPtr TheGraphics) const
{
   Pnt2s TopLeft, BottomRight;
   getInsideBorderBounds(TopLeft, BottomRight);
   
   //If I have a DrawObject then Draw it
   UIDrawObjectCanvasPtr DrawnDrawObject = getDrawnDrawObject();
   if(DrawnDrawObject != NullFC)
   {
      //Calculate Alignment
      Pnt2s AlignedPosition;
      Pnt2s DrawObjectTopLeft, DrawObjectBottomRight;
      DrawnDrawObject->getBounds(DrawObjectTopLeft, DrawObjectBottomRight);

      AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (DrawObjectBottomRight - DrawObjectTopLeft),getVerticalAlignment(), getHorizontalAlignment());

      //If active then translate the Text by the Active Offset
      if(getActive())
      {
          AlignedPosition = AlignedPosition + getActiveOffset();
      }

	  //Draw the DrawnDrawObject
        beginEditCP(DrawnDrawObject, PositionFieldMask);
            DrawnDrawObject->setPosition( AlignedPosition );
        endEditCP(DrawnDrawObject, PositionFieldMask);

        DrawnDrawObject->draw(TheGraphics);

   }

   //If I have Text Then Draw it
   if(getText() != "" && getFont() != NullFC)
   {
      //Calculate Alignment
      Pnt2s AlignedPosition;
      Pnt2s TextTopLeft, TextBottomRight;
      getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

      AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),getVerticalAlignment(), getHorizontalAlignment());

      //If active then translate the Text by the Active Offset
      if(getSelected() || getActive())
      {
          AlignedPosition = AlignedPosition + getActiveOffset();
      }

	  //Draw the Text
      TheGraphics->drawText(AlignedPosition, getText(), getFont(), getDrawnTextColor(), getOpacity());
   }
}

BorderPtr ToggleButton::getDrawnBorder(void) const
{
	if(getSelected() || getActive())
	{
		return getActiveBorder();
	}
	else
	{
	    if(getEnabled())
	    {
            return getBorder();
        }
        else
        {
            return getDisabledBorder();
        }
    }
}

UIBackgroundPtr ToggleButton::getDrawnBackground(void) const
{
	if(getSelected() || getActive())
	{
		return getActiveBackground();
	}
	else
	{
	    if(getEnabled())
	    {
            return getBackground();
        }
        else
        {
            return getDisabledBackground();
        }
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

void ToggleButton::actionPreformed(const ActionEvent& e)
{
    beginEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
	    setSelected(!getSelected());
    endEditCP(ToggleButtonPtr(this), ToggleButton::SelectedFieldMask);
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


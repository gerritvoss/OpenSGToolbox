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

#include "OSGLabelMenuItem.h"
#include "Util/OSGUIDrawUtils.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LabelMenuItem
A UI LabelMenuItem. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LabelMenuItem::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void LabelMenuItem::drawInternal(const GraphicsPtr TheGraphics) const
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

      AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),0.5, 0.0);

	  //Draw the Text
      TheGraphics->drawText(AlignedPosition, getText(), getFont(), getDrawnTextColor(), getOpacity());

      //Draw the Accelerator Text
      if(getAcceleratorText().compare("") != 0)
      {
          Pnt2s AcceleratorTextTopLeft, AcceleratorTextBottomRight;
          getFont()->getBounds(getAcceleratorText(), AcceleratorTextTopLeft, AcceleratorTextBottomRight);
          Pnt2s AcceleratorAlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (AcceleratorTextBottomRight - AcceleratorTextTopLeft),0.5, 1.0);

          TheGraphics->drawText(AcceleratorAlignedPosition, getAcceleratorText(), getFont(), getDrawnTextColor(), getOpacity());
      }
   }
}

Color4f LabelMenuItem::getDrawnTextColor(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getSelected())
        {
            return getSelectedTextColor();
        }
        if(_MouseInComponentLastMouse)
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

BorderPtr LabelMenuItem::getDrawnBorder(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getSelected())
        {
            return getSelectedBorder();
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

UIBackgroundPtr LabelMenuItem::getDrawnBackground(void) const
{
    if(getEnabled())
    {
        //if(getFocused())
        //{
        //    return getFocusedTextColor();
        //}
        if(getSelected())
        {
            return getSelectedBackground();
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

void LabelMenuItem::actionPreformed(const ActionEvent& e)
{
}

void LabelMenuItem::mouseReleased(const MouseEvent& e)
{
    if(getSelected() && getEnabled())
    {
	   produceActionPerformed(ActionEvent(MenuItemPtr(this), e.getTimeStamp()));
       getParentFrame()->destroyPopupMenu();
       beginEditCP(MenuItemPtr(this), SelectedFieldMask);
          setSelected(false);
       endEditCP(MenuItemPtr(this), SelectedFieldMask);
    }
    
    MenuItem::mouseReleased(e);
}

/*void LabelMenuItem::mouseEntered(const MouseEvent& e)
{
    beginEditCP(MenuItemPtr(this), SelectedFieldMask);
        setSelected(true);
    endEditCP(MenuItemPtr(this), SelectedFieldMask);
    
    MenuItem::mouseEntered(e);
}

void LabelMenuItem::mouseExited(const MouseEvent& e)
{
    beginEditCP(MenuItemPtr(this), SelectedFieldMask);
        setSelected(false);
    endEditCP(MenuItemPtr(this), SelectedFieldMask);
    
    MenuItem::mouseExited(e);
}*/

void LabelMenuItem::produceActionPerformed(const ActionEvent& e)
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

LabelMenuItem::LabelMenuItem(void) :
    Inherited()
{
}

LabelMenuItem::LabelMenuItem(const LabelMenuItem &source) :
    Inherited(source)
{
}

LabelMenuItem::~LabelMenuItem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LabelMenuItem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void LabelMenuItem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LabelMenuItem NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLABELMENUITEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLABELMENUITEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLABELMENUITEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


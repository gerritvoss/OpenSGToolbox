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
#include "Component/Container/Window/OSGInternalWindow.h"
#include "LookAndFeel/OSGLookAndFeelManager.h"
#include "Component/Menu/OSGMenu.h"

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

      //Draw the Mnemonic Underline
      if(getMnemonicTextPosition() != -1)
      {
          TheGraphics->drawTextUnderline(AlignedPosition, getText().substr(getMnemonicTextPosition(),1), getFont(), getDrawnTextColor(), getOpacity());
      }
      
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
        if(getSelected() || _DrawAsThoughSelected)
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
        if(getSelected() || _DrawAsThoughSelected)
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
        if(getSelected() || _DrawAsThoughSelected)
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
       getParentWindow()->destroyPopupMenu();
       beginEditCP(MenuItemPtr(this), SelectedFieldMask);
          setSelected(false);
       endEditCP(MenuItemPtr(this), SelectedFieldMask);
    }
    
    MenuItem::mouseReleased(e);
}

void LabelMenuItem::produceActionPerformed(const ActionEvent& e)
{
    actionPreformed(e);
    for(ActionListenerSetConstItor SetItor(_ActionListeners.begin()) ; SetItor != _ActionListeners.end() ; ++SetItor)
    {
	    (*SetItor)->actionPerformed(e);
    }
}

MenuPtr LabelMenuItem::getTopLevelMenu(void) const
{
    MenuPtr c(getParentMenu());
    while(c != NullFC)
    {
        if(c->getTopLevelMenu())
        {
            return c;
        }
        c = c->getParentMenu();
    }
    return NullFC;
}

void LabelMenuItem::activate(void)
{
    produceActionPerformed(ActionEvent(LabelMenuItemPtr(this), getSystemTime()));
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LabelMenuItem::LabelMenuItem(void) :
    Inherited(),
    _LabelMenuItemKeyAcceleratorListener(LabelMenuItemPtr(this)),
    _KeyAcceleratorMenuFlashUpdateListener(LabelMenuItemPtr(this)),
    _DrawAsThoughSelected(false)
{
}

LabelMenuItem::LabelMenuItem(const LabelMenuItem &source) :
    Inherited(source),
    _LabelMenuItemKeyAcceleratorListener(LabelMenuItemPtr(this)),
    _KeyAcceleratorMenuFlashUpdateListener(LabelMenuItemPtr(this)),
    _DrawAsThoughSelected(false)
{
}

LabelMenuItem::~LabelMenuItem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void LabelMenuItem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if((whichField & ParentWindowFieldMask) &&
        getParentWindow() != NullFC &&
        getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE
        )
    {
        getParentWindow()->addKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers(), &_LabelMenuItemKeyAcceleratorListener);
    }
    if((whichField & EnabledFieldMask) &&
        getParentWindow() != NullFC &&
        !getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE)
    {
        getParentWindow()->removeKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers());
    }

    if(whichField & AcceleratorKeyFieldMask ||
       whichField & AcceleratorModifiersFieldMask)
    {
        std::string AcceleratorText("");
        if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            AcceleratorText += KeyEvent::getStringFromKey(KeyEvent::KEY_CONTROL, 0) + "+";
        }
        if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_ALT)
        {
            AcceleratorText += KeyEvent::getStringFromKey(KeyEvent::KEY_ALT, 0) + "+";
        }
        if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
        {
            AcceleratorText += KeyEvent::getStringFromKey(KeyEvent::KEY_SHIFT, 0) + "+";
        }
        AcceleratorText += KeyEvent::getStringFromKey(static_cast<KeyEvent::Key>(getAcceleratorKey()), KeyEvent::KEY_MODIFIER_CAPS_LOCK);

        //Set my preferred size
        Pnt2s TextTopLeft, TextBottomRight;
        getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
        Pnt2s AcceleratorTextTopLeft, AcceleratorTextBottomRight;
        getFont()->getBounds(AcceleratorText, AcceleratorTextTopLeft, AcceleratorTextBottomRight);
        
        beginEditCP(LabelMenuItemPtr(this), AcceleratorTextFieldMask | PreferredSizeFieldMask);
            setAcceleratorText(AcceleratorText);
            setPreferredSize(Vec2s((TextBottomRight.x() - TextTopLeft.x()) + (AcceleratorTextBottomRight.x() - AcceleratorTextTopLeft.x()) + 50, getPreferredSize().y()));
        endEditCP(LabelMenuItemPtr(this), AcceleratorTextFieldMask | PreferredSizeFieldMask);
    }
    if(whichField & TextFieldMask ||
       whichField & MnemonicKeyFieldMask)
    {
        Int32 Pos(-1);
        if(getMnemonicKey() != KeyEvent::KEY_NONE &&
           getText() != "")
        {
            //Get the Character representation of the key
            UChar8 MnemonicCharLower(KeyEvent::getCharFromKey(static_cast<KeyEvent::Key>(getMnemonicKey()),0));
            UChar8 MnemonicCharUpper(KeyEvent::getCharFromKey(static_cast<KeyEvent::Key>(getMnemonicKey()),KeyEvent::KEY_MODIFIER_CAPS_LOCK));
            
            //Find the first occurance of this character in the text case-insensitive
            std::string::size_type MnemonicCharLowerPos;
            std::string::size_type MnemonicCharUpperPos;
            MnemonicCharLowerPos = getText().find_first_of(MnemonicCharLower);
            MnemonicCharUpperPos = getText().find_first_of(MnemonicCharUpper);

            if(MnemonicCharLowerPos == std::string::npos)
            {
                if(MnemonicCharUpperPos == std::string::npos)
                {
                    Pos = -1;
                }
                else
                {
                    Pos = MnemonicCharUpperPos;
                }
            }
            else
            {
                if(MnemonicCharUpperPos == std::string::npos)
                {
                    Pos = MnemonicCharLowerPos;
                }
                else
                {
                    Pos = osgMin(MnemonicCharLowerPos, MnemonicCharUpperPos);
                }
            }
        }
        
        beginEditCP(LabelMenuItemPtr(this), MnemonicTextPositionFieldMask);
            setMnemonicTextPosition(Pos);
        endEditCP(LabelMenuItemPtr(this), MnemonicTextPositionFieldMask);
    }
}

void LabelMenuItem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LabelMenuItem NI" << std::endl;
}

void LabelMenuItem::LabelMenuItemKeyAcceleratorListener::acceleratorTyped(const KeyAcceleratorEvent& e)
{
    //Set TopLevelMenu
    MenuPtr TopMenu(_LabelMenuItem->getTopLevelMenu());
    if(TopMenu != NullFC)
    {
        TopMenu->setDrawAsThoughSelected(true);

        _LabelMenuItem->_KeyAcceleratorMenuFlashUpdateListener.reset();
        _LabelMenuItem->getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&(_LabelMenuItem->_KeyAcceleratorMenuFlashUpdateListener));
    }
    _LabelMenuItem->produceActionPerformed(ActionEvent(_LabelMenuItem, e.getTimeStamp()));
}

void LabelMenuItem::KeyAcceleratorMenuFlashUpdateListener::update(const UpdateEvent& e)
{
    _FlashElps += e.getElapsedTime();
    if(_FlashElps > LookAndFeelManager::the()->getLookAndFeel()->getKeyAcceleratorMenuFlashTime())
    {
        MenuPtr TopMenu(_LabelMenuItem->getTopLevelMenu());
        if(TopMenu != NullFC)
        {
            TopMenu->setDrawAsThoughSelected(false);
        }
		_LabelMenuItem->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
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
    static Char8 cvsid_hpp       [] = OSGLABELMENUITEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLABELMENUITEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLABELMENUITEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


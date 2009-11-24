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

#include "OSGMenuItem.h"
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "LookAndFeel/OSGLookAndFeelManager.h"
#include "Component/Menu/OSGMenu.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::MenuItem
A UI MenuItem. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MenuItem::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection MenuItem::addActionListener(ActionListenerPtr Listener)
{
   _ActionListeners.insert(Listener);
   return EventConnection(
       boost::bind(&MenuItem::isActionListenerAttached, this, Listener),
       boost::bind(&MenuItem::removeActionListener, this, Listener));
}

void MenuItem::drawText(const GraphicsPtr TheGraphics, const Pnt2f& TopLeft, Real32 Opacity) const
{
   //If I have Text Then Draw it
   if(getText() != "" && getFont() != NullFC)
   {
       Pnt2f b, BottomRight;
       getInsideBorderBounds(b, BottomRight);
      //Calculate Alignment
      Pnt2f AlignedPosition;
      Pnt2f TextTopLeft, TextBottomRight;
      getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);

      AlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (TextBottomRight - TextTopLeft),0.5, 0.0);

	  //Draw the Text
      TheGraphics->drawText(AlignedPosition, getText(), getFont(), getDrawnTextColor(), getOpacity()*Opacity);

      //Draw the Mnemonic Underline
      if(getMnemonicTextPosition() != -1)
      {
          TheGraphics->drawTextUnderline(AlignedPosition, getText().substr(getMnemonicTextPosition(),1), getFont(), getDrawnTextColor(), getOpacity()*Opacity);
      }
      
      //Draw the Accelerator Text
      if(getAcceleratorText().compare("") != 0)
      {
          Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
          getFont()->getBounds(getAcceleratorText(), AcceleratorTextTopLeft, AcceleratorTextBottomRight);
          Pnt2f AcceleratorAlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (AcceleratorTextBottomRight - AcceleratorTextTopLeft),0.5, 1.0);

          TheGraphics->drawText(AcceleratorAlignedPosition, getAcceleratorText(), getFont(), getDrawnTextColor(), getOpacity()*Opacity);
      }

   }
}

void MenuItem::mouseReleased(const MouseEventPtr e)
{
    if(getSelected() && getEnabled())
    {
	   produceActionPerformed(ActionEvent::create(MenuItemPtr(this), e->getTimeStamp()));
       getParentWindow()->destroyPopupMenu();
       beginEditCP(MenuItemPtr(this), SelectedFieldMask);
          setSelected(false);
       endEditCP(MenuItemPtr(this), SelectedFieldMask);
    }
    
	if(getEnabled())
	{
		if(e->getButton() == MouseEvent::BUTTON1 && _Armed)
		{
			ButtonPtr(this)->setActive(false);
			_Armed = false;
		}
	}
	Component::mouseReleased(e);
}

MenuPtr MenuItem::getTopLevelMenu(void) const
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

void MenuItem::activate(void)
{
    produceActionPerformed(ActionEvent::create(MenuItemPtr(this), getSystemTime()));
}

Vec2f MenuItem::getContentRequestedSize(void) const
{
    Pnt2f TextTopLeft, TextBottomRight;
    getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
    Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
    getFont()->getBounds(getAcceleratorText(), AcceleratorTextTopLeft, AcceleratorTextBottomRight);
    
	Vec2f RequestedSize((TextBottomRight.x() - TextTopLeft.x()) + (AcceleratorTextBottomRight.x() - AcceleratorTextTopLeft.x()), getPreferredSize().y());

	if(!getAcceleratorText().empty())
	{
		RequestedSize[0] += 50.0f;
	}
	else
	{
		RequestedSize[0] += 25.0f;
	}

	return RequestedSize;
}

void MenuItem::actionPreformed(const ActionEventPtr e)
{
}

void MenuItem::produceActionPerformed(const ActionEventPtr e)
{
    actionPreformed(e);
    for(ActionListenerSetConstItor SetItor(_ActionListeners.begin()) ; SetItor != _ActionListeners.end() ; ++SetItor)
    {
	    (*SetItor)->actionPerformed(e);
    }
   _Producer.produceEvent(ActionPerformedMethodId,e);
}

void MenuItem::removeActionListener(ActionListenerPtr Listener)
{
   ActionListenerSetItor EraseIter(_ActionListeners.find(Listener));
   if(EraseIter != _ActionListeners.end())
   {
      _ActionListeners.erase(EraseIter);
   }
}

void MenuItem::detachFromEventProducer(void)
{
    Inherited::detachFromEventProducer();
    _KeyAcceleratorMenuFlashUpdateListener.disconnect();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MenuItem::MenuItem(void) :
    Inherited(),
    _MenuItemKeyAcceleratorListener(MenuItemPtr(this)),
    _KeyAcceleratorMenuFlashUpdateListener(MenuItemPtr(this)),
    _DrawAsThoughSelected(false)
{
}

MenuItem::MenuItem(const MenuItem &source) :
    Inherited(source),
    _MenuItemKeyAcceleratorListener(MenuItemPtr(this)),
    _KeyAcceleratorMenuFlashUpdateListener(MenuItemPtr(this)),
    _DrawAsThoughSelected(false)
{
}

MenuItem::~MenuItem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MenuItem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    if((whichField & ParentWindowFieldMask) &&
        getParentWindow() != NullFC &&
        getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE
        )
    {
        getParentWindow()->addKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers(), &_MenuItemKeyAcceleratorListener);
    }
    if((whichField & EnabledFieldMask) &&
        getParentWindow() != NullFC &&
        !getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE)
    {
        getParentWindow()->removeKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers());
    }

    if(whichField & TextFieldMask ||
	   whichField & AcceleratorKeyFieldMask ||
       whichField & AcceleratorModifiersFieldMask)
    {
        std::string AcceleratorText("");
        if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
        {
            AcceleratorText += KeyEvent::getKeynameStringFromKey(KeyEvent::KEY_CONTROL, 0) + "+";
        }
        if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_ALT)
        {
            AcceleratorText += KeyEvent::getKeynameStringFromKey(KeyEvent::KEY_ALT, 0) + "+";
        }
        if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
        {
            AcceleratorText += KeyEvent::getKeynameStringFromKey(KeyEvent::KEY_SHIFT, 0) + "+";
        }
		if(getAcceleratorKey() == KeyEvent::KEY_TAB)
        {
		    AcceleratorText += "Tab";
        }
		if(getAcceleratorKey() == KeyEvent::KEY_SPACE)
        {
			AcceleratorText += "Space";
        }
		AcceleratorText += KeyEvent::getKeynameStringFromKey(static_cast<KeyEvent::Key>(getAcceleratorKey()), KeyEvent::KEY_MODIFIER_CAPS_LOCK);
		
        //Set my preferred size
        Pnt2f TextTopLeft, TextBottomRight;
        getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
        Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
        getFont()->getBounds(AcceleratorText, AcceleratorTextTopLeft, AcceleratorTextBottomRight);
        
		Vec2f RequestedSize((TextBottomRight.x() - TextTopLeft.x()) + (AcceleratorTextBottomRight.x() - AcceleratorTextTopLeft.x()), getPreferredSize().y());

		if(!AcceleratorText.empty())
		{
			RequestedSize[0] += 50.0f;
		}
		else
		{
			RequestedSize[0] += 25.0f;
		}

        beginEditCP(MenuItemPtr(this), AcceleratorTextFieldMask);
            setAcceleratorText(AcceleratorText);
        endEditCP(MenuItemPtr(this), AcceleratorTextFieldMask);
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

			//Update Parent Menu
			if(getParentContainer() != NullFC)
			{
				getParentContainer()->updateLayout();
			}
        }
        
        beginEditCP(MenuItemPtr(this), MnemonicTextPositionFieldMask);
            setMnemonicTextPosition(Pos);
        endEditCP(MenuItemPtr(this), MnemonicTextPositionFieldMask);
    }
}

void MenuItem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump MenuItem NI" << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */
void MenuItem::MenuItemKeyAcceleratorListener::acceleratorTyped(const KeyAcceleratorEventPtr e)
{
    //Set TopLevelMenu
    MenuPtr TopMenu(_MenuItem->getTopLevelMenu());
    if(TopMenu != NullFC)
    {
        TopMenu->setDrawAsThoughSelected(true);

        _MenuItem->_KeyAcceleratorMenuFlashUpdateListener.reset();
        _MenuItem->getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&(_MenuItem->_KeyAcceleratorMenuFlashUpdateListener));
    }
    _MenuItem->produceActionPerformed(ActionEvent::create(_MenuItem, e->getTimeStamp()));
}

void MenuItem::KeyAcceleratorMenuFlashUpdateListener::disconnect(void)
{
    _MenuItem->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
}

void MenuItem::KeyAcceleratorMenuFlashUpdateListener::update(const UpdateEventPtr e)
{
    _FlashElps += e->getElapsedTime();
    if(_FlashElps > LookAndFeelManager::the()->getLookAndFeel()->getKeyAcceleratorMenuFlashTime())
    {
        MenuPtr TopMenu(_MenuItem->getTopLevelMenu());
        if(TopMenu != NullFC)
        {
            TopMenu->setDrawAsThoughSelected(false);
        }
        disconnect();
    }
}
#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.20 2006/03/16 17:01:53 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGMENUITEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMENUITEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMENUITEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


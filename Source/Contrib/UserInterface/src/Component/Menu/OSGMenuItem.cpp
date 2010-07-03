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

#include "OSGMenuItem.h"
#include "OSGUIDrawUtils.h"
#include "OSGInternalWindow.h"
#include "OSGLookAndFeelManager.h"
#include "OSGMenu.h"
#include "OSGUIDrawingSurface.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMenuItemBase.cpp file.
// To modify it, please change the .fcd file (OSGMenuItem.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MenuItem::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
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

void MenuItem::drawText(Graphics* const TheGraphics, const Pnt2f& TopLeft, Real32 Opacity) const
{
   //If I have Text Then Draw it
   if(getText() != "" && getFont() != NULL)
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
      if(_MnemonicTextPosition != -1)
      {
          TheGraphics->drawTextUnderline(AlignedPosition, getText().substr(_MnemonicTextPosition,1), getFont(), getDrawnTextColor(), getOpacity()*Opacity);
      }
      
      //Draw the Accelerator Text
      if(_AcceleratorText.compare("") != 0)
      {
          Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
          getFont()->getBounds(_AcceleratorText, AcceleratorTextTopLeft, AcceleratorTextBottomRight);
          Pnt2f AcceleratorAlignedPosition = calculateAlignment(TopLeft, (BottomRight-TopLeft), (AcceleratorTextBottomRight - AcceleratorTextTopLeft),0.5, 1.0);

          TheGraphics->drawText(AcceleratorAlignedPosition, _AcceleratorText, getFont(), getDrawnTextColor(), getOpacity()*Opacity);
      }

   }
}

void MenuItem::mouseReleased(const MouseEventUnrecPtr e)
{
    if(getSelected() && getEnabled())
    {
	   produceActionPerformed(ActionEvent::create(this, e->getTimeStamp()));
       getParentWindow()->destroyPopupMenu();
          setSelected(false);
    }
    
	if(getEnabled())
	{
		if(e->getButton() == MouseEvent::BUTTON1 && _Armed)
		{
			this->setActive(false);
			_Armed = false;
		}
	}
	Component::mouseReleased(e);
}

Menu* MenuItem::getTopLevelMenu(void) const
{
    MenuRefPtr c(getParentMenu());
    while(c != NULL)
    {
        if(c->getTopLevelMenu())
        {
            return c;
        }
        c = c->getParentMenu();
    }
    return NULL;
}

void MenuItem::activate(void)
{
    produceActionPerformed(ActionEvent::create(this, getSystemTime()));
}

Vec2f MenuItem::getContentRequestedSize(void) const
{
    Pnt2f TextTopLeft, TextBottomRight;
    getFont()->getBounds(getText(), TextTopLeft, TextBottomRight);
    Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
    getFont()->getBounds(_AcceleratorText, AcceleratorTextTopLeft, AcceleratorTextBottomRight);
    
	Vec2f RequestedSize((TextBottomRight.x() - TextTopLeft.x()) + (AcceleratorTextBottomRight.x() - AcceleratorTextTopLeft.x()), getPreferredSize().y());

	if(!_AcceleratorText.empty())
	{
		RequestedSize[0] += 50.0f;
	}
	else
	{
		RequestedSize[0] += 25.0f;
	}

	return RequestedSize;
}

void MenuItem::actionPreformed(const ActionEventUnrecPtr e)
{
}

void MenuItem::produceActionPerformed(const ActionEventUnrecPtr e)
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

void MenuItem::updateAcceleratorText(void)
{
    _AcceleratorText.clear();
    if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_CONTROL)
    {
        _AcceleratorText += KeyEvent::getKeynameStringFromKey(KeyEvent::KEY_CONTROL, 0) + "+";
    }
    
    if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_META)
    {
        _AcceleratorText += KeyEvent::getKeynameStringFromKey(KeyEvent::KEY_META, 0) + "+";
    }
    if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_ALT)
    {
        _AcceleratorText += KeyEvent::getKeynameStringFromKey(KeyEvent::KEY_ALT, 0) + "+";
    }
    if(getAcceleratorModifiers() & KeyEvent::KEY_MODIFIER_SHIFT)
    {
        _AcceleratorText += KeyEvent::getKeynameStringFromKey(KeyEvent::KEY_SHIFT, 0) + "+";
    }
    _AcceleratorText += KeyEvent::getKeynameStringFromKey(static_cast<KeyEvent::Key>(getAcceleratorKey()), KeyEvent::KEY_MODIFIER_CAPS_LOCK);
}

void MenuItem::setParentWindow(InternalWindow* const parent)
{
    if(getParentWindow() != NULL &&
        getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE)
    {
        getParentWindow()->removeKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers());
    }
    Inherited::setParentWindow(parent);
    if(getParentWindow() != NULL &&
        getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE)
    {
        getParentWindow()->addKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers(), &_MenuItemKeyAcceleratorListener);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

MenuItem::MenuItem(void) :
    Inherited(),
    _MenuItemKeyAcceleratorListener(this),
    _KeyAcceleratorMenuFlashUpdateListener(this),
    _DrawAsThoughSelected(false),
    _AcceleratorText(""),
    _MnemonicTextPosition(-1)
{
}

MenuItem::MenuItem(const MenuItem &source) :
    Inherited(source),
    _MenuItemKeyAcceleratorListener(this),
    _KeyAcceleratorMenuFlashUpdateListener(this),
    _DrawAsThoughSelected(false),
    _AcceleratorText(source._AcceleratorText),
    _MnemonicTextPosition(source._MnemonicTextPosition)
{
}

MenuItem::~MenuItem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MenuItem::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if((whichField & EnabledFieldMask) &&
        getParentWindow() != NULL &&
        !getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE)
    {
        getParentWindow()->removeKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers());
    }

    if(whichField & TextFieldMask ||
	   whichField & AcceleratorKeyFieldMask ||
       whichField & AcceleratorModifiersFieldMask)
    {
        updateAcceleratorText();
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
			if(getParentContainer() != NULL)
			{
				getParentContainer()->updateLayout();
			}
        }
        
        _MnemonicTextPosition =Pos;
    }
}

void MenuItem::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MenuItem NI" << std::endl;
}

void MenuItem::MenuItemKeyAcceleratorListener::acceleratorTyped(const KeyAcceleratorEventUnrecPtr e)
{
    //Set TopLevelMenu
    MenuRefPtr TopMenu(_MenuItem->getTopLevelMenu());
    if(TopMenu != NULL)
    {
        TopMenu->setDrawAsThoughSelected(true);

        _MenuItem->_KeyAcceleratorMenuFlashUpdateListener.reset();
        _MenuItem->getParentWindow()->getParentDrawingSurface()->getEventProducer()->addUpdateListener(&(_MenuItem->_KeyAcceleratorMenuFlashUpdateListener));
    }
    _MenuItem->produceActionPerformed(ActionEvent::create(_MenuItem, e->getTimeStamp()));
}

void MenuItem::KeyAcceleratorMenuFlashUpdateListener::disconnect(void)
{
    _MenuItem->getParentWindow()->getParentDrawingSurface()->getEventProducer()->removeUpdateListener(this);
}

void MenuItem::KeyAcceleratorMenuFlashUpdateListener::update(const UpdateEventUnrecPtr e)
{
    _FlashElps += e->getElapsedTime();
    if(_FlashElps > LookAndFeelManager::the()->getLookAndFeel()->getKeyAcceleratorMenuFlashTime())
    {
        MenuRefPtr TopMenu(_MenuItem->getTopLevelMenu());
        if(TopMenu != NULL)
        {
            TopMenu->setDrawAsThoughSelected(false);
        }
        disconnect();
    }
}

OSG_END_NAMESPACE

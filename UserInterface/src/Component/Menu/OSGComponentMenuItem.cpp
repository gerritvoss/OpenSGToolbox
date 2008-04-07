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

#include "OSGComponentMenuItem.h"
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "LookAndFeel/OSGLookAndFeelManager.h"
#include "Component/Menu/OSGMenu.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ComponentMenuItem
A UI ComponentMenuItem. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentMenuItem::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ComponentMenuItem::drawInternal(const GraphicsPtr TheGraphics) const
{
	if(getComponent() != NullFC)
	{
		getComponent()->draw(TheGraphics);
	}
}

BorderPtr ComponentMenuItem::getDrawnBorder(void) const
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

UIBackgroundPtr ComponentMenuItem::getDrawnBackground(void) const
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

void ComponentMenuItem::actionPreformed(const ActionEvent& e)
{
}

void ComponentMenuItem::mouseReleased(const MouseEvent& e)
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

MenuPtr ComponentMenuItem::getTopLevelMenu(void) const
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

void ComponentMenuItem::activate(void)
{
    produceActionPerformed(ActionEvent(ComponentMenuItemPtr(this), getSystemTime()));
}

Vec2f ComponentMenuItem::getContentRequestedSize(void) const
{
	if(getComponent() != NullFC)
	{
		Vec2f ComponentRequestedSize(0.0,0.0);
		if(getComponent() != NullFC)
		{
			ComponentRequestedSize = getComponent()->getRequestedSize();
		}

        Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
        getFont()->getBounds(getAcceleratorText(), AcceleratorTextTopLeft, AcceleratorTextBottomRight);
        
		Vec2f RequestedSize((ComponentRequestedSize.x()) + (AcceleratorTextBottomRight.x() - AcceleratorTextTopLeft.x()), osgMax(getPreferredSize().y(), ComponentRequestedSize.y()));

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
	else
	{
		return Inherited::getContentRequestedSize();
	}
}

void ComponentMenuItem::updateComponentBounds(void)
{
	if(getComponent() != NullFC)
	{
		Pnt2f InsideBorderTopLeft, InsideBorderBottomRight;
		getInsideBorderBounds(InsideBorderTopLeft, InsideBorderBottomRight);

		beginEditCP(getComponent(), Component::PositionFieldMask | Component::SizeFieldMask);
			getComponent()->setPosition(InsideBorderTopLeft);
			getComponent()->setSize(InsideBorderBottomRight - InsideBorderTopLeft);
		endEditCP(getComponent(), Component::PositionFieldMask | Component::SizeFieldMask);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComponentMenuItem::ComponentMenuItem(void) :
    Inherited(),
    _ComponentMenuItemKeyAcceleratorListener(ComponentMenuItemPtr(this)),
    _KeyAcceleratorMenuFlashUpdateListener(ComponentMenuItemPtr(this)),
    _DrawAsThoughSelected(false)
{
}

ComponentMenuItem::ComponentMenuItem(const ComponentMenuItem &source) :
    Inherited(source),
    _ComponentMenuItemKeyAcceleratorListener(ComponentMenuItemPtr(this)),
    _KeyAcceleratorMenuFlashUpdateListener(ComponentMenuItemPtr(this)),
    _DrawAsThoughSelected(false)
{
}

ComponentMenuItem::~ComponentMenuItem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComponentMenuItem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & SizeFieldMask) ||
		(whichField & ComponentFieldMask))
	{
		updateComponentBounds();
	}
	
    if((whichField & ParentWindowFieldMask) &&
        getParentWindow() != NullFC &&
        getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE
        )
    {
        getParentWindow()->addKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers(), &_ComponentMenuItemKeyAcceleratorListener);
    }
    if((whichField & EnabledFieldMask) &&
        getParentWindow() != NullFC &&
        !getEnabled() && 
        getAcceleratorKey() != KeyEvent::KEY_NONE)
    {
        getParentWindow()->removeKeyAccelerator(static_cast<KeyEvent::Key>(getAcceleratorKey()), getAcceleratorModifiers());
    }

    if(whichField & ComponentFieldMask ||
		whichField & AcceleratorKeyFieldMask ||
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

        beginEditCP(ComponentMenuItemPtr(this), AcceleratorTextFieldMask);
            setAcceleratorText(AcceleratorText);
        endEditCP(ComponentMenuItemPtr(this), AcceleratorTextFieldMask);
    }

}

void ComponentMenuItem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ComponentMenuItem NI" << std::endl;
}

void ComponentMenuItem::ComponentMenuItemKeyAcceleratorListener::acceleratorTyped(const KeyAcceleratorEvent& e)
{
    //Set TopLevelMenu
    MenuPtr TopMenu(_ComponentMenuItem->getTopLevelMenu());
    if(TopMenu != NullFC)
    {
        TopMenu->setDrawAsThoughSelected(true);

        _ComponentMenuItem->_KeyAcceleratorMenuFlashUpdateListener.reset();
        _ComponentMenuItem->getParentWindow()->getDrawingSurface()->getEventProducer()->addUpdateListener(&(_ComponentMenuItem->_KeyAcceleratorMenuFlashUpdateListener));
    }
    _ComponentMenuItem->produceActionPerformed(ActionEvent(_ComponentMenuItem, e.getTimeStamp()));
}

void ComponentMenuItem::KeyAcceleratorMenuFlashUpdateListener::update(const UpdateEvent& e)
{
    _FlashElps += e.getElapsedTime();
    if(_FlashElps > LookAndFeelManager::the()->getLookAndFeel()->getKeyAcceleratorMenuFlashTime())
    {
        MenuPtr TopMenu(_ComponentMenuItem->getTopLevelMenu());
        if(TopMenu != NullFC)
        {
            TopMenu->setDrawAsThoughSelected(false);
        }
		_ComponentMenuItem->getParentWindow()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
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
    static Char8 cvsid_hpp       [] = OSGCOMPONENTMENUITEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMPONENTMENUITEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMPONENTMENUITEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


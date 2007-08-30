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

#include "OSGMenu.h"
#include "LookAndFeel/OSGLookAndFeelManager.h"
#include "Component/Container/OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include <OpenSG/Input/OSGWindowEventProducer.h>
#include "OSGPopupMenu.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Menu
A UI Menu. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Menu::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Menu::drawInternal(const GraphicsPtr Graphics) const
{
    LabelMenuItem::drawInternal(Graphics);

    //If my popup Menu is visible then tell it to draw
    if(getInternalPopupMenu()->getVisible())
    {
        getInternalPopupMenu()->draw(Graphics);
    }
}

void Menu::mouseEntered(const MouseEvent& e)
{
    getParentFrame()->getDrawingSurface()->getEventProducer()->addUpdateListener(&_PopupUpdateListener);
    LabelMenuItem::mouseEntered(e);
}

void Menu::mouseReleased(const MouseEvent& e)
{
    Component::mouseReleased(e);
}

void Menu::setPopupVisible(bool Visible)
{
    //Set the Submenu's position to the correct place
    //Make the Submenu visible
    beginEditCP(getInternalPopupMenu(), PopupMenu::VisibleFieldMask | PopupMenu::PositionFieldMask);
        getInternalPopupMenu()->setVisible(Visible);
        getInternalPopupMenu()->setPosition(Pnt2s(getSize().x(),0));
    endEditCP(getInternalPopupMenu(), PopupMenu::VisibleFieldMask | PopupMenu::PositionFieldMask);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Menu::Menu(void) :
    Inherited(),
    _PopupUpdateListener(MenuPtr(this))
{
    setInternalPopupMenu(PopupMenu::create());
    getInternalPopupMenu()->setVisible(false);
}

Menu::Menu(const Menu &source) :
    Inherited(source),
    _PopupUpdateListener(MenuPtr(this))
{
    setInternalPopupMenu(PopupMenu::create());
    getInternalPopupMenu()->setVisible(false);
}

Menu::~Menu(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Menu::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & ParentFrameFieldMask)
    {
        beginEditCP(getInternalPopupMenu(), ParentFrameFieldMask);
            getInternalPopupMenu()->setParentFrame(getParentFrame());
        endEditCP(getInternalPopupMenu(), ParentFrameFieldMask);
    }
    
    if(whichField & ArmedFieldMask &&
       !getArmed()
       )
    {
        setPopupVisible(false);
        if(getParentFrame() != NullFC &&
        getParentFrame()->getDrawingSurface() != NullFC &&
        getParentFrame()->getDrawingSurface()->getEventProducer() != NullFC)
        {
            getParentFrame()->getDrawingSurface()->getEventProducer()->removeUpdateListener(&_PopupUpdateListener);
        }
    }

}

void Menu::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Menu NI" << std::endl;
}


void Menu::PopupUpdateListener::update(const UpdateEvent& e)
{
    _PopupElps += e.getElapsedTime();
    if(_PopupElps > LookAndFeelManager::the()->getLookAndFeel()->getSubMenuPopupTime())
    {
        //Tell the menu to popup the submenu
        _Menu->setPopupVisible(true);
        //Remove myself from the update
		_Menu->getParentFrame()->getDrawingSurface()->getEventProducer()->removeUpdateListener(this);
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
    static Char8 cvsid_hpp       [] = OSGMENUBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGMENUBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGMENUFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


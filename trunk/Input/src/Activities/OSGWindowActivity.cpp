/*---------------------------------------------------------------------------*\
 *                          OpenSG ToolBox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEINPUTLIB

#include <OpenSG/OSGConfig.h>

#include "OSGWindowActivity.h"
#include "WindowSystem/OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::WindowActivity

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void WindowActivity::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


void WindowActivity::eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId)
{
    switch(getActivityType())
    {
    case WINDOW_CLOSE:
        getWindowEventProducer()->closeWindow();
        break;
    case WINDOW_FOCUS:
        getWindowEventProducer()->setFocused(true);
        break;
    case WINDOW_UNFOCUS:
        getWindowEventProducer()->setFocused(false);
        break;
    case WINDOW_FOCUS_TOGGLE:
        getWindowEventProducer()->setFocused(!getWindowEventProducer()->getFocused());
        break;
    case WINDOW_VISIBLE:
        getWindowEventProducer()->setVisible(true);
        break;
    case WINDOW_HIDDEN:
        getWindowEventProducer()->setVisible(false);
        break;
    case WINDOW_VISIBLE_TOGGLE:
        getWindowEventProducer()->setVisible(!getWindowEventProducer()->getVisible());
        break;
    case WINDOW_ICONIFY:
        getWindowEventProducer()->setIconify(true);
        break;
    case WINDOW_DEICONIFY:
        getWindowEventProducer()->setIconify(false);
        break;
    case WINDOW_ICONIFY_TOGGLE:
        getWindowEventProducer()->setIconify(!getWindowEventProducer()->getIconify());
        break;
    case WINDOW_FULLSCREEN:
        getWindowEventProducer()->setFullscreen(true);
        break;
    case WINDOW_DEFULLSCREEN:
        getWindowEventProducer()->setFullscreen(false);
        break;
    case WINDOW_FULLSCREEN_TOGGLE:
        getWindowEventProducer()->setFullscreen(!getWindowEventProducer()->getFullscreen());
        break;
    default:
        SWARNING << "WindowActivity::eventProduced(): Unknown Activity Type: " << getActivityType() << std::endl;
        break;
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

WindowActivity::WindowActivity(void) :
    Inherited()
{
}

WindowActivity::WindowActivity(const WindowActivity &source) :
    Inherited(source)
{
}

WindowActivity::~WindowActivity(void)
{
}

/*----------------------------- class specific ----------------------------*/

void WindowActivity::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void WindowActivity::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump WindowActivity NI" << std::endl;
}


OSG_END_NAMESPACE


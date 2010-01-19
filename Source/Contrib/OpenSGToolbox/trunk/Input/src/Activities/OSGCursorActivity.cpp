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

#include "OSGCursorActivity.h"
#include "WindowSystem/OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CursorActivity

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CursorActivity::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CursorActivity::eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId)
{
    switch(getActivityType())
    {
    case CURSOR_HIDE:
        getWindowEventProducer()->setShowCursor(false);
        break;
    case CURSOR_SHOW:
        getWindowEventProducer()->setShowCursor(true);
        break;
    case CURSOR_SHOW_TOGGLE:
        getWindowEventProducer()->setShowCursor(!getWindowEventProducer()->getShowCursor());
        break;
    case CURSOR_ATTACH_MOUSE_TO_CURSOR:
        getWindowEventProducer()->setAttachMouseToCursor(true);
        break;
    case CURSOR_DETACH_MOUSE_FROM_CURSOR:
        getWindowEventProducer()->setAttachMouseToCursor(false);
        break;
    case CURSOR_ATTACH_MOUSE_TO_CURSOR_TOGGLE:
        getWindowEventProducer()->setAttachMouseToCursor(!getWindowEventProducer()->getAttachMouseToCursor());
        break;
    case CURSOR_SET_TYPE:
        getWindowEventProducer()->setCursorType(getCursorType());
        break;
    default:
        SWARNING << "CursorActivity::eventProduced(): Unknown Activity Type: " << getActivityType() << std::endl;
        break;
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CursorActivity::CursorActivity(void) :
    Inherited()
{
}

CursorActivity::CursorActivity(const CursorActivity &source) :
    Inherited(source)
{
}

CursorActivity::~CursorActivity(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CursorActivity::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CursorActivity::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CursorActivity NI" << std::endl;
}


OSG_END_NAMESPACE


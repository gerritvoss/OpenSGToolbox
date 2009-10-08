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

#include "OSGDialogWindow.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DialogWindow
A UI Dialog Window. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DialogWindow::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection DialogWindow::addDialogListener(DialogListenerPtr Listener)
{
   _DialogListeners.insert(Listener);
   return EventConnection(
       boost::bind(&DialogWindow::isDialogListenerAttached, this, Listener),
       boost::bind(&DialogWindow::removeDialogListener, this, Listener));
}

EventConnection DialogWindow::addEventListener(EventListenerPtr Listener)
{
    _EventListeners.insert(Listener);
   return EventConnection(
       boost::bind(&DialogWindow::isEventListenerAttached, this, Listener),
       boost::bind(&DialogWindow::removeEventListener, this, Listener));
}

void DialogWindow::removeEventListener(EventListenerPtr Listener)
{
   EventListenerSetItor EraseIter(_EventListeners.find(Listener));
   if(EraseIter != _EventListeners.end())
   {
      _EventListeners.erase(EraseIter);
   }
}

void DialogWindow::removeDialogListener(DialogListenerPtr Listener)
{
   DialogListenerSetItor EraseIter(_DialogListeners.find(Listener));
   if(EraseIter != _DialogListeners.end())
   {
      _DialogListeners.erase(EraseIter);
   }
}

void DialogWindow::produceDialogInput(const DialogEventPtr e)
{
	DialogListenerSet Listeners(_DialogListeners);
    for(DialogListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->dialogInput(e);
    }
    _Producer.produceEvent(DialogInputMethodId,e);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DialogWindow::DialogWindow(void) :
    Inherited()
{
}

DialogWindow::DialogWindow(const DialogWindow &source) :
    Inherited(source)
{
}

DialogWindow::~DialogWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DialogWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DialogWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DialogWindow NI" << std::endl;
}

OSG_END_NAMESPACE


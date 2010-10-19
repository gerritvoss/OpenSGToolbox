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

#include <boost/bind.hpp>

#include "OSGAbstractDocument.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGAbstractDocumentBase.cpp file.
// To modify it, please change the .fcd file (OSGAbstractDocument.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractDocument::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractDocument::addDocumentListener(DocumentListenerPtr Listener)
{
   _DocumentListeners.insert(Listener);
   return EventConnection(
       boost::bind(&AbstractDocument::isDocumentListenerAttached, this, Listener),
       boost::bind(&AbstractDocument::removeDocumentListener, this, Listener));
   
}

bool AbstractDocument::isDocumentListenerAttached(DocumentListenerPtr Listener) const
{
    return _DocumentListeners.find(Listener) != _DocumentListeners.end();
}

void AbstractDocument::removeDocumentListener(DocumentListenerPtr Listener)
{
   DocumentListenerSetItor EraseIter(_DocumentListeners.find(Listener));
   if(EraseIter != _DocumentListeners.end())
   {
      _DocumentListeners.erase(EraseIter);
   }
}

EventConnection AbstractDocument::addUndoableEditListener(UndoableEditListenerPtr Listener)
{
   _UndoableEditListeners.insert(Listener);
   return EventConnection(
       boost::bind(&AbstractDocument::isUndoableEditListenerAttached, this, Listener),
       boost::bind(&AbstractDocument::removeUndoableEditListener, this, Listener));
}

bool AbstractDocument::isUndoableEditListenerAttached(UndoableEditListenerPtr Listener) const
{
    return _UndoableEditListeners.find(Listener) != _UndoableEditListeners.end();
}

void AbstractDocument::removeUndoableEditListener(UndoableEditListenerPtr Listener)
{
   UndoableEditListenerSetItor EraseIter(_UndoableEditListeners.find(Listener));
   if(EraseIter != _UndoableEditListeners.end())
   {
      _UndoableEditListeners.erase(EraseIter);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


void AbstractDocument::produceChangedUpdate(const DocumentEventP e)
{
	DocumentListenerSet Listeners(_DocumentListeners);
    for(DocumentListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->changedUpdate(e);
    }
    _Producer.produceEvent(ChangedUpdateMethodId,e);
}

void AbstractDocument::produceInsertUpdate(const DocumentEventP e)
{
	DocumentListenerSet Listeners(_DocumentListeners);
    for(DocumentListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->insertUpdate(e);
    }
    _Producer.produceEvent(InsertUpdateMethodId,e);
}

void AbstractDocument::produceRemoveUpdate(const DocumentEventP e)
{
	DocumentListenerSet Listeners(_DocumentListeners);
    for(DocumentListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->removeUpdate(e);
    }
    _Producer.produceEvent(RemoveUpdateMethodId,e);
}

void AbstractDocument::produceUndoableEditHappened(const UndoableEditEventUnrecPtr e)
{
	UndoableEditListenerSet Listeners(_UndoableEditListeners);
    for(UndoableEditListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->undoableEditHappened(e);
    }
    _Producer.produceEvent(UndoableEditHappenedMethodId,e);
}


/*----------------------- constructors & destructors ----------------------*/

AbstractDocument::AbstractDocument(void) :
    Inherited()
{
}

AbstractDocument::AbstractDocument(const AbstractDocument &source) :
    Inherited(source)
{
}

AbstractDocument::~AbstractDocument(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractDocument::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void AbstractDocument::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump AbstractDocument NI" << std::endl;
}

OSG_END_NAMESPACE

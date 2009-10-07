/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
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

#define OSG_COMPILEUSERINTERFACELIB

#include <OpenSG/OSGConfig.h>

#include "OSGAbstractDocument.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractDocument
UI AbstractDocument. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractDocument::initMethod (void)
{
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


UInt32 AbstractDocument::createPosition(Int32 offs)
{
    //TODO: Implement
    return 0;
}

ElementPtr AbstractDocument::getDefaultRootElement(void) const
{
    return getRootElement();
}

UInt32 AbstractDocument::getEndPosition(void) const
{
    //TODO: Implement
    return 0;
}

UInt32 AbstractDocument::getLength(void) const
{
    //TODO: Implement
    return 0;
}

UInt32 AbstractDocument::getProperty(const std::string& key) const
{
    //TODO: Implement
    return 0;
}

std::vector<ElementPtr> AbstractDocument::getRootElements(void)
{
    //TODO: Implement
    return std::vector<ElementPtr>();
}

UInt64 AbstractDocument::getStartPosition(void) const
{
    //TODO: Implement
    return 0;
}

std::string AbstractDocument::getText(Int32 offset, UInt32 length) const
{
    //TODO: Implement
    return std::string("");
}

void AbstractDocument::getText(Int32 offset, UInt32 length, std::string& txt) const
{
    //TODO: Implement
}

void AbstractDocument::insertString(Int32 offset, const std::string& str, std::map<std::string,UInt32> properties)
{
    //TODO: Implement
}

void AbstractDocument::putProperty(const std::string& key, UInt32 value)
{
    //TODO: Implement
}

void AbstractDocument::remove(Int32 offs, UInt32 len)
{
    //TODO: Implement
}

//int AbstractDocument::getAsynchronousLoadPriority(void);

//Element AbstractDocument::getBidiRootElement(void);

//DocumentFilter AbstractDocument::getDocumentFilter(void);

const std::map<std::string,UInt32>& AbstractDocument::getDocumentProperties(void) const
{
    //TODO: Implement
    return std::map<std::string,UInt32>();
}

void AbstractDocument::readLock(void)
{
    //TODO: Implement
}

void AbstractDocument::readUnlock(void)
{
    //TODO: Implement
}

void AbstractDocument::replace(Int32 offset, UInt32 length, const std::string& str, const std::map<std::string,UInt32>& properties)
{
    //TODO: Implement
}

//void AbstractDocument::setAsynchronousLoadPriority(int p);

//void AbstractDocument::setDocumentFilter(DocumentFilter filter);

void AbstractDocument::setDocumentProperties(const std::map<std::string,UInt32>& properties)
{
    //TODO: Implement
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/


ElementPtr AbstractDocument::createBranchElement(ElementPtr parent, const std::map<std::string,UInt32>& a) const
{
    //TODO: Implement
    return NullFC;
}

ElementPtr AbstractDocument::createLeafElement(ElementPtr parent, const std::map<std::string,UInt32>& a, Int32 p0, Int32 p1) const
{
    //TODO: Implement
    return NullFC;
}

void AbstractDocument::produceChangedUpdate(const DocumentEventPtr e)
{
	DocumentListenerSet Listeners(_DocumentListeners);
    for(DocumentListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->changedUpdate(e);
    }
    produceEvent(ChangedUpdateMethodId,e);
}

void AbstractDocument::produceInsertUpdate(const DocumentEventPtr e)
{
	DocumentListenerSet Listeners(_DocumentListeners);
    for(DocumentListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->insertUpdate(e);
    }
    produceEvent(InsertUpdateMethodId,e);
}

void AbstractDocument::produceRemoveUpdate(const DocumentEventPtr e)
{
	DocumentListenerSet Listeners(_DocumentListeners);
    for(DocumentListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->removeUpdate(e);
    }
    produceEvent(RemoveUpdateMethodId,e);
}

void AbstractDocument::produceUndoableEditHappened(const UndoableEditEventPtr e)
{
	UndoableEditListenerSet Listeners(_UndoableEditListeners);
    for(UndoableEditListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->undoableEditHappened(e);
    }
    produceEvent(UndoableEditHappenedMethodId,e);
}

void AbstractDocument::writeLock(void)
{
    //TODO: Implement
}

void AbstractDocument::writeUnlock(void)
{
    //TODO: Implement
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

void AbstractDocument::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractDocument::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractDocument NI" << std::endl;
}


OSG_END_NAMESPACE


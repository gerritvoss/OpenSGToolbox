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

#include "OSGAbstractCellEditor.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractCellEditor
A UI Abstract Cell Editor. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractCellEditor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbstractCellEditor::cancelCellEditing(void)
{
    produceEditingCanceled();
}

bool AbstractCellEditor::isCellEditable(const EventPtr anEvent) const
{
    return true;
}

bool AbstractCellEditor::shouldSelectCell(const EventPtr anEvent) const
{
    return true;
}

bool AbstractCellEditor::stopCellEditing(void)
{
    produceEditingStopped();
    return true;
}

EventConnection AbstractCellEditor::addCellEditorListener(CellEditorListenerPtr l)
{
   _CellEditorListeners.insert(l);
   return EventConnection(
       boost::bind(&AbstractCellEditor::isCellEditorListenerAttached, this, l),
       boost::bind(&AbstractCellEditor::removeCellEditorListener, this, l));
}

void AbstractCellEditor::removeCellEditorListener(CellEditorListenerPtr l)
{
   CellEditorListenerSetItor EraseIter(_CellEditorListeners.find(l));
   if(EraseIter != _CellEditorListeners.end())
   {
      _CellEditorListeners.erase(EraseIter);
   }
}

void AbstractCellEditor::produceEditingCanceled(void)
{
   const ChangeEventPtr TheEvent = ChangeEvent::create(NullFC, getSystemTime());
   CellEditorListenerSet CellEditorListenerSet(_CellEditorListeners);
   for(CellEditorListenerSetConstItor SetItor(CellEditorListenerSet.begin()) ; SetItor != CellEditorListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->editingCanceled(TheEvent);
   }
   _Producer.produceEvent(EditingCanceledMethodId,TheEvent);
}

void AbstractCellEditor::produceEditingStopped(void)
{
   const ChangeEventPtr TheEvent = ChangeEvent::create(NullFC, getSystemTime());
   CellEditorListenerSet CellEditorListenerSet(_CellEditorListeners);
   for(CellEditorListenerSetConstItor SetItor(CellEditorListenerSet.begin()) ; SetItor != CellEditorListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->editingStopped(TheEvent);
   }
   _Producer.produceEvent(EditingStoppedMethodId,TheEvent);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractCellEditor::AbstractCellEditor(void) :
    Inherited()
{
}

AbstractCellEditor::AbstractCellEditor(const AbstractCellEditor &source) :
    Inherited(source)
{
}

AbstractCellEditor::~AbstractCellEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractCellEditor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractCellEditor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractCellEditor NI" << std::endl;
}

OSG_END_NAMESPACE


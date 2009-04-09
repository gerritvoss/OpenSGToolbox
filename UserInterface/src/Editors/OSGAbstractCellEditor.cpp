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

bool AbstractCellEditor::isCellEditable(const Event& anEvent) const
{
    return true;
}

bool AbstractCellEditor::shouldSelectCell(const Event& anEvent) const
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
   ChangeEvent TheEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED);
   CellEditorListenerSet CellEditorListenerSet(_CellEditorListeners);
   for(CellEditorListenerSetConstItor SetItor(CellEditorListenerSet.begin()) ; SetItor != CellEditorListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->editingCanceled(TheEvent);
   }
}

void AbstractCellEditor::produceEditingStopped(void)
{
   ChangeEvent TheEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED);
   CellEditorListenerSet CellEditorListenerSet(_CellEditorListeners);
   for(CellEditorListenerSetConstItor SetItor(CellEditorListenerSet.begin()) ; SetItor != CellEditorListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->editingStopped(TheEvent);
   }
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTCELLEDITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTCELLEDITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTCELLEDITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


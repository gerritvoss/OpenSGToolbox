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

#include "OSGAbstractTableModel.h"
#include "OSGTableModelListener.h"
#include "OSGTableModelEvent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractListModel
A AbstractListModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*std::string AbstractTableModel::getColumnName(UInt32 columnIndex) const
{
    //Defaults to A, B, C, ..., Y, Z, AA, BB, ...
    UInt32 ColumnMod(columnIndex%24u);
    UInt32 LetterRepeats(columnIndex/24u + 1);

    //Now get the Character
    UChar8 Letter('A' + ColumnMod);

    //Now make a string with LetterRepeats number of the Character
    return std::string(LetterRepeats,Letter);
    
}*/

bool AbstractTableModel::isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const
{
    //Abstract Model defaults to not allow editing
    return false;
}

void AbstractTableModel::setValueAt(SharedFieldPtr aValue, UInt32 rowIndex, UInt32 columnIndex)
{
    //Abstract Model defaults to not allow editing
    //So do nothing
}

void AbstractTableModel::addTableModelListener(TableModelListenerPtr l)
{
   _ModelListeners.insert(l);
}

void AbstractTableModel::removeTableModelListener(TableModelListenerPtr l)
{
   TableModelListenerSetItor EraseIter(_ModelListeners.find(l));
   if(EraseIter != _ModelListeners.end())
   {
      _ModelListeners.erase(EraseIter);
   }
}

void AbstractTableModel::produceContentsHeaderRowChanged(UInt32 FirstColumn, UInt32 LastColumn)
{
   TableModelEvent TheEvent(NullFC, getSystemTime(), FirstColumn, LastColumn, 0,0, TableModelEvent::HEADER_ROW_CHANGED, TableModelPtr(this));
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->contentsHeaderRowChanged(TheEvent);
   }
}

void AbstractTableModel::produceContentsChanged(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
   TableModelEvent TheEvent(NullFC, getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow, TableModelEvent::CONTENTS_CHANGED, TableModelPtr(this));
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->contentsChanged(TheEvent);
   }
}

void AbstractTableModel::produceIntervalAdded(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
   TableModelEvent TheEvent(NullFC, getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow, TableModelEvent::INTERVAL_ADDED, TableModelPtr(this));
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->intervalAdded(TheEvent);
   }
}

void AbstractTableModel::produceIntervalRemoved(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
   TableModelEvent TheEvent(NullFC, getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow, TableModelEvent::INTERVAL_REMOVED, TableModelPtr(this));
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->intervalRemoved(TheEvent);
   }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

/*----------------------------- class specific ----------------------------*/

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


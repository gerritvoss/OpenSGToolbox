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
#include "Component/Table/OSGTableModelEvent.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractTableModel
A UI AbstractTableModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTableModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool AbstractTableModel::isCellEditable(UInt32 rowIndex, UInt32 columnIndex) const
{
    //Abstract Model defaults to not allow editing
    return false;
}

void AbstractTableModel::setValueAt(const boost::any& aValue, UInt32 rowIndex, UInt32 columnIndex)
{
    //Abstract Model defaults to not allow editing
    //So do nothing
}

EventConnection AbstractTableModel::addTableModelListener(TableModelListenerPtr l)
{
   _ModelListeners.insert(l);
   return EventConnection(
       boost::bind(&AbstractTableModel::isTableModelListenerAttached, this, l),
       boost::bind(&AbstractTableModel::removeTableModelListener, this, l));
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
   const TableModelEventPtr TheEvent = TableModelEvent::create(TableModelPtr(this), getSystemTime(), FirstColumn, LastColumn, 0,0);
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->contentsHeaderRowChanged(TheEvent);
   }
   produceEvent(ContentsHeaderRowChangedMethodId,TheEvent);
}

void AbstractTableModel::produceContentsChanged(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
   const TableModelEventPtr TheEvent = TableModelEvent::create(TableModelPtr(this), getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow);
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->contentsChanged(TheEvent);
   }
   produceEvent(ContentsChangedMethodId,TheEvent);
}

void AbstractTableModel::produceIntervalAdded(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
   const TableModelEventPtr TheEvent = TableModelEvent::create(TableModelPtr(this), getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow);
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->intervalAdded(TheEvent);
   }
   produceEvent(IntervalAddedMethodId,TheEvent);
}

void AbstractTableModel::produceIntervalRemoved(UInt32 FirstColumn, UInt32 LastColumn, UInt32 FirstRow, UInt32 LastRow)
{
   const TableModelEventPtr TheEvent = TableModelEvent::create(TableModelPtr(this), getSystemTime(), FirstColumn, LastColumn, FirstRow,LastRow);
   TableModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->intervalRemoved(TheEvent);
   }
   produceEvent(IntervalRemovedMethodId,TheEvent);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractTableModel::AbstractTableModel(void) :
    Inherited()
{
}

AbstractTableModel::AbstractTableModel(const AbstractTableModel &source) :
    Inherited(source)
{
}

AbstractTableModel::~AbstractTableModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTableModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractTableModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractTableModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTTABLEMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTTABLEMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTTABLEMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


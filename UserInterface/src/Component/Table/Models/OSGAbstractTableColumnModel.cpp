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

#include "OSGAbstractTableColumnModel.h"
#include "Component/Table/OSGTableColumnModelEvent.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractTableColumnModel
A UI AbstractTableColumnModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractTableColumnModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractTableColumnModel::addColumnModelListener(TableColumnModelListenerPtr l)
{
   _ModelListeners.insert(l);
   return EventConnection(
       boost::bind(&AbstractTableColumnModel::isColumnModelListenerAttached, this, l),
       boost::bind(&AbstractTableColumnModel::removeColumnModelListener, this, l));
}

void AbstractTableColumnModel::removeColumnModelListener(TableColumnModelListenerPtr l)
{
   TableColumnModelListenerSetItor EraseIter(_ModelListeners.find(l));
   if(EraseIter != _ModelListeners.end())
   {
      _ModelListeners.erase(EraseIter);
   }
}

void AbstractTableColumnModel::produceColumnAdded(const UInt32& ToIndex)
{
    TableColumnModelEvent TheEvent(NullFC, getSystemTime(), 0, ToIndex, TableColumnModelEvent::COLUMN_ADDED, TableColumnModelPtr(this));
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnAdded(TheEvent);
   }
}
void AbstractTableColumnModel::produceColumnMoved(const UInt32& ToIndex,const UInt32& FromIndex)
{
    TableColumnModelEvent TheEvent(NullFC, getSystemTime(), FromIndex, ToIndex, TableColumnModelEvent::COLUMN_MOVED, TableColumnModelPtr(this));
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnMoved(TheEvent);
   }
}

void AbstractTableColumnModel::produceColumnRemoved(const UInt32& FromIndex)
{
    TableColumnModelEvent TheEvent(NullFC, getSystemTime(), FromIndex, 0, TableColumnModelEvent::COLUMN_REMOVED, TableColumnModelPtr(this));
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnRemoved(TheEvent);
   }
}

void AbstractTableColumnModel::produceColumnMarginChanged(void)
{
   ChangeEvent TheEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED);
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnMarginChanged(TheEvent);
   }
}

void AbstractTableColumnModel::produceColumnSelectionChanged(const ListSelectionEvent& e)
{
   TableColumnModelListenerSet ModelListenerSet(_ModelListeners);
   for(TableColumnModelListenerSetConstItor SetItor(ModelListenerSet.begin()) ; SetItor != ModelListenerSet.end() ; ++SetItor)
   {
      (*SetItor)->columnSelectionChanged(e);
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractTableColumnModel::AbstractTableColumnModel(void) :
    Inherited()
{
}

AbstractTableColumnModel::AbstractTableColumnModel(const AbstractTableColumnModel &source) :
    Inherited(source)
{
}

AbstractTableColumnModel::~AbstractTableColumnModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractTableColumnModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractTableColumnModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractTableColumnModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTTABLECOLUMNMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTTABLECOLUMNMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTTABLECOLUMNMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


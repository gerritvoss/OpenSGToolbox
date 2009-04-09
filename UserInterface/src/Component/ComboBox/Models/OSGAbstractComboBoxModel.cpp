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

#include "OSGAbstractComboBoxModel.h"
#include "Component/List/OSGListDataListener.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractComboBoxModel
A UI AbstractComboBoxModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractComboBoxModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractComboBoxModel::addListDataListener(ListDataListenerPtr l)
{
    _DataListeners.insert(l);
   return EventConnection(
       boost::bind(&AbstractComboBoxModel::isListDataListenerAttached, this, l),
       boost::bind(&AbstractComboBoxModel::removeListDataListener, this, l));
}

void AbstractComboBoxModel::removeListDataListener(ListDataListenerPtr l)
{
   ListDataListenerSetIter EraseIter(_DataListeners.find(l));
   if(EraseIter != _DataListeners.end())
   {
      _DataListeners.erase(EraseIter);
   }
}

void AbstractComboBoxModel::produceListDataContentsChanged(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
	ListDataEvent e(Source, getSystemTime(), index0, index1, ListDataEvent::CONTENTS_CHANGED, AbstractComboBoxModelPtr(this));
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->contentsChanged(e);
   }
}

void AbstractComboBoxModel::produceListDataIntervalAdded(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
	ListDataEvent e(Source, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_ADDED, AbstractComboBoxModelPtr(this));
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->intervalAdded(e);
   }
}

void AbstractComboBoxModel::produceListDataIntervalRemoved(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
	ListDataEvent e(Source, getSystemTime(), index0, index1, ListDataEvent::INTERVAL_REMOVED, AbstractComboBoxModelPtr(this));
   ListDataListenerSet DataListenerSet(_DataListeners);
   for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
   {
		(*SetItor)->intervalRemoved(e);
   }
}

EventConnection AbstractComboBoxModel::addSelectionListener(ComboBoxSelectionListenerPtr l)
{
    _SelectionListeners.insert(l);
   return EventConnection(
       boost::bind(&AbstractComboBoxModel::isSelectionListenerAttached, this, l),
       boost::bind(&AbstractComboBoxModel::removeSelectionListener, this, l));
}

void AbstractComboBoxModel::removeSelectionListener(ComboBoxSelectionListenerPtr l)
{
   ComboBoxSelectionListenerSetIter EraseIter(_SelectionListeners.find(l));
   if(EraseIter != _SelectionListeners.end())
   {
      _SelectionListeners.erase(EraseIter);
   }
}

void AbstractComboBoxModel::produceSelectionChanged(FieldContainerPtr Source, const Int32& CurrentIndex, const Int32& PreviousIndex)
{
	ComboBoxSelectionEvent e(Source, getSystemTime(), CurrentIndex, PreviousIndex);
	ComboBoxSelectionListenerSet SelectionListenerSet(_SelectionListeners);
	for(ComboBoxSelectionListenerSetConstIter SetItor(SelectionListenerSet.begin()) ; SetItor != SelectionListenerSet.end() ; ++SetItor)
	{
		(*SetItor)->selectionChanged(e);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractComboBoxModel::AbstractComboBoxModel(void) :
    Inherited()
{
}

AbstractComboBoxModel::AbstractComboBoxModel(const AbstractComboBoxModel &source) :
    Inherited(source)
{
}

AbstractComboBoxModel::~AbstractComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractComboBoxModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractComboBoxModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractComboBoxModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTCOMBOBOXMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTCOMBOBOXMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTCOMBOBOXMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


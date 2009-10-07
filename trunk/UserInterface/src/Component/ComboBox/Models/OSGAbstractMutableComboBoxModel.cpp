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

#include "OSGAbstractMutableComboBoxModel.h"
#include "Component/List/OSGListDataListener.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractMutableComboBoxModel
A UI AbstractMutableComboBoxModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractMutableComboBoxModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractMutableComboBoxModel::addListDataListener(ListDataListenerPtr l)
{
    _DataListeners.insert(l);
    return EventConnection(
            boost::bind(&AbstractMutableComboBoxModel::isListDataListenerAttached, this, l),
            boost::bind(&AbstractMutableComboBoxModel::removeListDataListener, this, l));
}

void AbstractMutableComboBoxModel::removeListDataListener(ListDataListenerPtr l)
{
    ListDataListenerSetIter EraseIter(_DataListeners.find(l));
    if(EraseIter != _DataListeners.end())
    {
        _DataListeners.erase(EraseIter);
    }
}

void AbstractMutableComboBoxModel::produceListDataContentsChanged(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->contentsChanged(e);
    }
    produceEvent(ListDataContentsChangedMethodId,e);
}

void AbstractMutableComboBoxModel::produceListDataIntervalAdded(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalAdded(e);
    }
    produceEvent(ListDataIntervalAddedMethodId,e);
}

void AbstractMutableComboBoxModel::produceListDataIntervalRemoved(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalRemoved(e);
    }
    produceEvent(ListDataIntervalRemovedMethodId,e);
}

EventConnection AbstractMutableComboBoxModel::addSelectionListener(ComboBoxSelectionListenerPtr l)
{
    _SelectionListeners.insert(l);
    return EventConnection(
            boost::bind(&AbstractMutableComboBoxModel::isSelectionListenerAttached, this, l),
            boost::bind(&AbstractMutableComboBoxModel::removeSelectionListener, this, l));
}

void AbstractMutableComboBoxModel::removeSelectionListener(ComboBoxSelectionListenerPtr l)
{
    ComboBoxSelectionListenerSetIter EraseIter(_SelectionListeners.find(l));
    if(EraseIter != _SelectionListeners.end())
    {
        _SelectionListeners.erase(EraseIter);
    }
}

void AbstractMutableComboBoxModel::produceSelectionChanged(FieldContainerPtr Source, const Int32& CurrentIndex, const Int32& PreviousIndex)
{
    const ComboBoxSelectionEventPtr e = ComboBoxSelectionEvent::create(Source, getSystemTime(), CurrentIndex, PreviousIndex);
    ComboBoxSelectionListenerSet SelectionListenerSet(_SelectionListeners);
    for(ComboBoxSelectionListenerSetConstIter SetItor(SelectionListenerSet.begin()) ; SetItor != SelectionListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->selectionChanged(e);
    }
    produceEvent(SelectionChangedMethodId,e);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractMutableComboBoxModel::AbstractMutableComboBoxModel(void) :
    Inherited()
{
}

AbstractMutableComboBoxModel::AbstractMutableComboBoxModel(const AbstractMutableComboBoxModel &source) :
    Inherited(source)
{
}

AbstractMutableComboBoxModel::~AbstractMutableComboBoxModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractMutableComboBoxModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractMutableComboBoxModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractMutableComboBoxModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTMUTABLECOMBOBOXMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTMUTABLECOMBOBOXMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTMUTABLECOMBOBOXMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


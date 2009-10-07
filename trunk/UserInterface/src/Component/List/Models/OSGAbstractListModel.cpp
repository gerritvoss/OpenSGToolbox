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

#include "OSGAbstractListModel.h"
#include "Component/List/OSGListDataListener.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbstractListModel
A UI AbstractListModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbstractListModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection AbstractListModel::addListDataListener(ListDataListenerPtr l)
{
    _DataListeners.insert(l);
    return EventConnection(
            boost::bind(&AbstractListModel::isListDataListenerAttached, this, l),
            boost::bind(&AbstractListModel::removeListDataListener, this, l));
}

void AbstractListModel::removeListDataListener(ListDataListenerPtr l)
{
    ListDataListenerSetIter EraseIter(_DataListeners.find(l));
    if(EraseIter != _DataListeners.end())
    {
        _DataListeners.erase(EraseIter);
    }
}

void AbstractListModel::produceListDataContentsChanged(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->contentsChanged(e);
    }
    produceEvent(ListDataContentsChangedMethodId,e);
}

void AbstractListModel::produceListDataIntervalAdded(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalAdded(e);
    }
    produceEvent(ListDataIntervalAddedMethodId,e);
}

void AbstractListModel::produceListDataIntervalRemoved(FieldContainerPtr Source, UInt32 index0, UInt32 index1)
{
    const ListDataEventPtr e = ListDataEvent::create(Source, getSystemTime(), index0, index1);
    ListDataListenerSet DataListenerSet(_DataListeners);
    for(ListDataListenerSetConstIter SetItor(DataListenerSet.begin()) ; SetItor != DataListenerSet.end() ; ++SetItor)
    {
        (*SetItor)->intervalRemoved(e);
    }
    produceEvent(ListDataIntervalRemovedMethodId,e);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbstractListModel::AbstractListModel(void) :
    Inherited()
{
}

AbstractListModel::AbstractListModel(const AbstractListModel &source) :
    Inherited(source)
{
}

AbstractListModel::~AbstractListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbstractListModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbstractListModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbstractListModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSTRACTLISTMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSTRACTLISTMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSTRACTLISTMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


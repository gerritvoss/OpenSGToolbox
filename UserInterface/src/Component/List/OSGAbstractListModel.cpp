/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

void AbstractListModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 AbstractListModel::getSize(void)
{
	return _FieldList.size();
}

Field* AbstractListModel::getElementAt(UInt32 index)
{
   return _FieldList[index];
}


void AbstractListModel::addListDataListener(ListDataListenerPtr l)
{
   if(std::find(_DataListeners.begin(), _DataListeners.end(), l) != _DataListeners.end())
   {
	   _DataListeners.push_back(l);
   }
}

void AbstractListModel::removeListDataListener(ListDataListenerPtr l)
{
   if(std::find(_DataListeners.begin(), _DataListeners.end(), l) != _DataListeners.end())
   {
	   _DataListeners.remove(l);
   }
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

void AbstractListModel::fireListDataContentsChanged(void)
{
	ListDataEvent e(AbstractListModelPtr(this), getSystemTime(), 0, _FieldList.size()-1, ListDataEvent::CONTENTS_CHANGED);
	ListDataListenerListIter Iter;
	for(Iter = _DataListeners.begin() ; Iter != _DataListeners.end() ; ++Iter)
	{
		(*Iter)->contentsChanged(e);
	}
}

void AbstractListModel::fireListDataIntervalAdded(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(AbstractListModelPtr(this), getSystemTime(), index0, index1, ListDataEvent::INTERVAL_ADDED);
	ListDataListenerListIter Iter;
	for(Iter = _DataListeners.begin(); Iter != _DataListeners.end(); ++Iter)
	{
		(*Iter)->intervalAdded(e);
	}
}

void AbstractListModel::fireListDataIntervalRemoved(UInt32 index0, UInt32 index1)
{
	ListDataEvent e(AbstractListModelPtr(this), getSystemTime(), index0, index1, ListDataEvent::INTERVAL_REMOVED);
	ListDataListenerListIter Iter;
	for(Iter = _DataListeners.begin(); Iter != _DataListeners.end(); ++Iter)
	{
		(*Iter)->intervalRemoved(e);
	}
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


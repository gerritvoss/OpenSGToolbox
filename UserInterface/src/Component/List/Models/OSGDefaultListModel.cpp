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

#include "OSGDefaultListModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultListModel
A UI DefaultListModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultListModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 DefaultListModel::getSize(void) const
{
	return _FieldList.size();
}

SharedFieldPtr DefaultListModel::getElementAt(UInt32 index) const
{
	if(index < _FieldList.size())
	{
		FieldList::const_iterator SearchItor(_FieldList.begin());
		for(UInt32 i(0) ; i<index ; ++i) {++SearchItor;}
		return (*SearchItor);
	}
	else
	{
		return SharedFieldPtr();
	}
}
 
void DefaultListModel::pushBack(SharedFieldPtr f)
{
	_FieldList.push_back(f);
	produceListDataIntervalAdded(DefaultListModelPtr(this),_FieldList.size()-1,_FieldList.size()-1);
}

void DefaultListModel::clear(void)
{
	UInt32 Size(_FieldList.size());
	_FieldList.clear();
	produceListDataIntervalRemoved(DefaultListModelPtr(this),0,Size-1);
}

void DefaultListModel::popBack(void)
{
	_FieldList.pop_back();
	produceListDataIntervalRemoved(DefaultListModelPtr(this),_FieldList.size(),_FieldList.size());
}

void DefaultListModel::pushFront(SharedFieldPtr f)
{
	_FieldList.push_front(f);
	produceListDataIntervalAdded(DefaultListModelPtr(this),0,0);
}

void DefaultListModel::popFront(void)
{
	_FieldList.pop_front();
	produceListDataIntervalRemoved(DefaultListModelPtr(this),0,0);
}

void DefaultListModel::insert(UInt32 Index, SharedFieldPtr f)
{
	if(Index < _FieldList.size())
	{
		FieldList::iterator SearchItor(_FieldList.begin());
		for(UInt32 i(0) ; i<Index ; ++i) {++SearchItor;}
		_FieldList.insert(SearchItor, f);
		produceListDataIntervalAdded(DefaultListModelPtr(this),Index,Index);
	}
	else
	{
		pushBack(f);
	}
}

void DefaultListModel::erase(UInt32 Index)
{
	if(Index < _FieldList.size())
	{
		FieldList::iterator SearchItor(_FieldList.begin());
		for(UInt32 i(0) ; i<Index ; ++i) {++SearchItor;}
		_FieldList.erase(SearchItor);
		produceListDataIntervalRemoved(DefaultListModelPtr(this),Index,Index);
	}
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListModel::DefaultListModel(void) :
    Inherited()
{
}

DefaultListModel::DefaultListModel(const DefaultListModel &source) :
    Inherited(source)
{
}

DefaultListModel::~DefaultListModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultListModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultListModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultListModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTLISTMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTLISTMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTLISTMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


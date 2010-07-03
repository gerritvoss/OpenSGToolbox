/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGDefaultListModel.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGDefaultListModelBase.cpp file.
// To modify it, please change the .fcd file (OSGDefaultListModel.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultListModel::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

UInt32 DefaultListModel::getSize(void) const
{
    return _FieldList.size();
}

boost::any DefaultListModel::getElementAt(UInt32 index) const
{
    if(index < _FieldList.size())
    {
        return (*(_FieldList.begin() + index));
    }
    else
    {
        return boost::any();
    }
}

void DefaultListModel::set(UInt32 Index, const boost::any& v)
{
    if(Index < _FieldList.size())
    {
        _FieldList[Index] = v;
        produceListDataContentsChanged(this,Index,Index);
    }
}

void DefaultListModel::pushBack(const boost::any& f)
{
    _FieldList.push_back(f);
    produceListDataIntervalAdded(this,_FieldList.size()-1,_FieldList.size()-1);
}

void DefaultListModel::clear(void)
{
    UInt32 Size(_FieldList.size());
    _FieldList.clear();
    produceListDataIntervalRemoved(this,0,Size-1);
}

void DefaultListModel::popBack(void)
{
    _FieldList.pop_back();
    produceListDataIntervalRemoved(this,_FieldList.size(),_FieldList.size());
}

void DefaultListModel::pushFront(const boost::any& f)
{
    _FieldList.push_front(f);
    produceListDataIntervalAdded(this,0,0);
}

void DefaultListModel::popFront(void)
{
    _FieldList.pop_front();
    produceListDataIntervalRemoved(this,0,0);
}

void DefaultListModel::insert(UInt32 Index, const boost::any& f)
{
    if(Index < _FieldList.size())
    {
        _FieldList.insert(_FieldList.begin() + Index, f);
        produceListDataIntervalAdded(this,Index,Index);
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
        produceListDataIntervalRemoved(this,Index,Index);
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

void DefaultListModel::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void DefaultListModel::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump DefaultListModel NI" << std::endl;
}

OSG_END_NAMESPACE

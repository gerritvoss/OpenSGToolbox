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

#include "OSGDefaultSingleSelectionModel.h"

#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultSingleSelectionModel
A UI DefaultSingleSelectionModel. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultSingleSelectionModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

EventConnection DefaultSingleSelectionModel::addSelectionListener(SelectionListenerPtr listener)
{
   _SelectionListeners.insert(listener);
   return EventConnection(
       boost::bind(&DefaultSingleSelectionModel::isSelectionListenerAttached, this, listener),
       boost::bind(&DefaultSingleSelectionModel::removeSelectionListener, this, listener));
}

void DefaultSingleSelectionModel::removeSelectionListener(SelectionListenerPtr Listener)
{
   SelectionListenerSetItor EraseIter(_SelectionListeners.find(Listener));
   if(EraseIter != _SelectionListeners.end())
   {
      _SelectionListeners.erase(EraseIter);
   }
}


void DefaultSingleSelectionModel::clearSelection(void)
{
    if(getInternalSelectedIndex() != -1)
    {
        setSelectedIndex(-1);
    }
}

Int32 DefaultSingleSelectionModel::getSelectedIndex(void)
{
    return getInternalSelectedIndex();
}

bool DefaultSingleSelectionModel::isSelected(void)
{
    return getInternalSelectedIndex() != -1;
}

void DefaultSingleSelectionModel::setSelectedIndex(Int32 index)
{
    if(getInternalSelectedIndex() != index)
    {
        Int32 PreviousSelection(getSelectedIndex());
        beginEditCP(DefaultSingleSelectionModelPtr(this), InternalSelectedIndexFieldMask);
            setInternalSelectedIndex(index);
        endEditCP(DefaultSingleSelectionModelPtr(this), InternalSelectedIndexFieldMask);

        produceSelectionChanged(getSelectedIndex(), PreviousSelection);
    }
}

void DefaultSingleSelectionModel::produceSelectionChanged(const Int32& SelectedIndex, const Int32& PreviouslySelectedIndex)
{
    std::vector<Int32> Selected;
    if(SelectedIndex != -1)
    {
        Selected.push_back(SelectedIndex);
    }
    std::vector<Int32> PreviouslySelected;
    if(PreviouslySelectedIndex != -1)
    {
        PreviouslySelected.push_back(PreviouslySelectedIndex);
    }

    SelectionEvent TheEvent(DefaultSingleSelectionModelPtr(this), getTimeStamp(), Selected, PreviouslySelected, false);

    SelectionListenerSet Listeners(_SelectionListeners);
   for(SelectionListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
   {
	   (*SetItor)->selectionChanged(TheEvent);
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultSingleSelectionModel::DefaultSingleSelectionModel(void) :
    Inherited()
{
}

DefaultSingleSelectionModel::DefaultSingleSelectionModel(const DefaultSingleSelectionModel &source) :
    Inherited(source)
{
}

DefaultSingleSelectionModel::~DefaultSingleSelectionModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultSingleSelectionModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultSingleSelectionModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultSingleSelectionModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTSINGLESELECTIONMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTSINGLESELECTIONMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTSINGLESELECTIONMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


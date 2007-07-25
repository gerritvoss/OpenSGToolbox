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

#include "OSGDefaultListSelectionModel.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultListSelectionModel
A DefaultListSelectionModel. 
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

void 	DefaultListSelectionModel::addSelectionInterval(UInt32 index0, UInt32 index1)
{
   //TODO:Implement
}

void 	DefaultListSelectionModel::clearSelection(void)
{
   //TODO:Implement
}

UInt32 	DefaultListSelectionModel::getAnchorSelectionIndex(void) const
{
   //TODO:Implement
   return 0;
}

UInt32 	DefaultListSelectionModel::getLeadSelectionIndex(void) const
{
   //TODO:Implement
   return 0;
}

UInt32 	DefaultListSelectionModel::getMaxSelectionIndex(void) const
{
   //TODO:Implement
   return 0;
}

UInt32 	DefaultListSelectionModel::getMinSelectionIndex(void) const
{
   //TODO:Implement
   return 0;
}

Int32 	DefaultListSelectionModel::getSelectionMode(void) const
{
   //TODO:Implement
   return 0;
}

bool 	DefaultListSelectionModel::getValueIsAdjusting(void) const
{
   //TODO:Implement
   return false;
}

void 	DefaultListSelectionModel::insertIndexInterval(UInt32 index, UInt32 length, bool before)
{
   //TODO:Implement
}

bool 	DefaultListSelectionModel::isSelectedIndex(UInt32 index) const
{
   //TODO:Implement
   return false;
}

bool 	DefaultListSelectionModel::isSelectionEmpty(void) const
{
   //TODO:Implement
   return true;
}

void 	DefaultListSelectionModel::removeIndexInterval(UInt32 index0, UInt32 index1)
{
   //TODO:Implement
}

void 	DefaultListSelectionModel::removeSelectionInterval(UInt32 index0, UInt32 index1)
{
   //TODO:Implement
}

void 	DefaultListSelectionModel::setAnchorSelectionIndex(UInt32 index)
{
   //TODO:Implement
}

void 	DefaultListSelectionModel::setLeadSelectionIndex(UInt32 index)
{
   //TODO:Implement
}

void 	DefaultListSelectionModel::setSelectionInterval(UInt32 index0, UInt32 index1)
{
   //TODO:Implement
}

void 	DefaultListSelectionModel::setSelectionMode(Int32 selectionMode)
{
   //TODO:Implement
}

void 	DefaultListSelectionModel::setValueIsAdjusting(bool valueIsAdjusting)
{
   //TODO:Implement
}

void DefaultListSelectionModel::produceSelectionChanged(const ListSelectionEvent& e)
{
   for(ListSelectionListenerSetConstItor SetItor(_ListSelectionListeners.begin()) ; SetItor != _ListSelectionListeners.end() ; ++SetItor)
   {
	   (*SetItor)->selectionChanged(e);
   }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListSelectionModel::DefaultListSelectionModel(void) :
_SelectionMode(SINGLE_SELECTION)
{
}

DefaultListSelectionModel::~DefaultListSelectionModel(void)
{
}

OSG_END_NAMESPACE


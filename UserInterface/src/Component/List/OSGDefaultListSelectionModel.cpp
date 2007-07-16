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

void DefaultListSelectionModel::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void 	DefaultListSelectionModel::addListSelectionListener(ListSelectionListenerPtr x)
{
   //TODO:Implement
}

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

void 	DefaultListSelectionModel::removeListSelectionListener(ListSelectionListenerPtr x)
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
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultListSelectionModel::DefaultListSelectionModel(void) :
    Inherited()
{
}

DefaultListSelectionModel::DefaultListSelectionModel(const DefaultListSelectionModel &source) :
    Inherited(source)
{
}

DefaultListSelectionModel::~DefaultListSelectionModel(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultListSelectionModel::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultListSelectionModel::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultListSelectionModel NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTLISTSELECTIONMODELBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTLISTSELECTIONMODELBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTLISTSELECTIONMODELFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEGAMELIB

#include <OpenSG/OSGConfig.h>

#include <OpenSG/Game/OSGInventory.h>
#include <OpenSG/Game/OSGInventoryItem.h>
#include <string>

#include "OSGInventoryListComparitor.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::InventoryListComparitor
A InventoryListModel.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void InventoryListComparitor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool InventoryListComparitor::operator()(UInt32 LeftIndex, UInt32 RightIndex)
{
	bool ret;

	ret = getCurrentInventory()->getInventoryItems(LeftIndex)->getName().compare(getCurrentInventory()->getInventoryItems(RightIndex)->getName()) < 0;

	return ret;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InventoryListComparitor::InventoryListComparitor(void) :
    Inherited()
{
}

InventoryListComparitor::InventoryListComparitor(const InventoryListComparitor &source) :
    Inherited(source)
{
}

InventoryListComparitor::~InventoryListComparitor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InventoryListComparitor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void InventoryListComparitor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump InventoryListComparitor NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGINVENTORYLISTCOMPARITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGINVENTORYLISTCOMPARITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGINVENTORYLISTCOMPARITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


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

#include "OSGDefaultInventoryListComparitor.h"

#include "Inventory/Models/OSGInventoryListModel.h"
#include "Inventory/OSGInventoryItem.h"
#include <boost/bind.hpp>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultInventoryListComparitor
A DefaultInventoryListModel.   
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultInventoryListComparitor::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool DefaultInventoryListComparitor::operator()(const UInt32& LeftIndex, const UInt32& RightIndex)
{
	bool ret;

	ret = getModel()->getCurrentInventory()->getInventoryItems(LeftIndex)->getName().compare(getModel()->getCurrentInventory()->getInventoryItems(RightIndex)->getName()) < 0;

	return ret;
}

DefaultInventoryListComparitor::ComparitorFunc DefaultInventoryListComparitor::getComparitorFunc(void) const
{
	return boost::bind(&DefaultInventoryListComparitor::operator(), const_cast<DefaultInventoryListComparitor*>(this),_1, _2);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultInventoryListComparitor::DefaultInventoryListComparitor(void) :
    Inherited()
{
}

DefaultInventoryListComparitor::DefaultInventoryListComparitor(const DefaultInventoryListComparitor &source) :
    Inherited(source)
{
}

DefaultInventoryListComparitor::~DefaultInventoryListComparitor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultInventoryListComparitor::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultInventoryListComparitor::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultInventoryListComparitor NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTINVENTORYLISTCOMPARITORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTINVENTORYLISTCOMPARITORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTINVENTORYLISTCOMPARITORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


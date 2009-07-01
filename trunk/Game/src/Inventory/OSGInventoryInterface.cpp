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

#include "OSGInventoryInterface.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::InventoryInterface
A Inventory. 	 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void InventoryInterface::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void InventoryInterface::setInventory()
{
}
void InventoryInterface::InventoryInterfaceListener::itemAdded(const InventoryEvent& e)
{
}
void InventoryInterface::InventoryInterfaceListener::itemRemoved(const InventoryEvent& e)
{
}
void InventoryInterface::InventoryInterfaceListener::inventorySorted(const InventoryEvent& e)
{
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

InventoryInterface::InventoryInterface(void) :
    Inherited(),
    _InventoryInterfaceListener(InventoryInterfacePtr(this))
{
}

InventoryInterface::InventoryInterface(const InventoryInterface &source) :
    Inherited(source),
    _InventoryInterfaceListener(InventoryInterfacePtr(this))
{
}

InventoryInterface::~InventoryInterface(void)
{
}

/*----------------------------- class specific ----------------------------*/

void InventoryInterface::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if(whichField & SourceInventoryFieldMask && getSourceInventory() != NullFC)
    {
        setInventory();
    }
}

void InventoryInterface::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump InventoryInterface NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGINVENTORYINTERFACEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGINVENTORYINTERFACEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGINVENTORYINTERFACEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


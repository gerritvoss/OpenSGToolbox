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

#include "OSGDefaultInventoryListComponentGenerator.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DefaultInventoryListComponentGenerator
A UI Default Inventory List ComponentGenerator. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DefaultInventoryListComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr DefaultInventoryListComponentGenerator::getListComponent(ListPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus)
{
    return Inherited::getListComponent(Parent,Value,Index,IsSelected,HasFocus);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DefaultInventoryListComponentGenerator::DefaultInventoryListComponentGenerator(void) :
    Inherited()
{
}

DefaultInventoryListComponentGenerator::DefaultInventoryListComponentGenerator(const DefaultInventoryListComponentGenerator &source) :
    Inherited(source)
{
}

DefaultInventoryListComponentGenerator::~DefaultInventoryListComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DefaultInventoryListComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void DefaultInventoryListComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump DefaultInventoryListComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGDEFAULTINVENTORYLISTCOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEFAULTINVENTORYLISTCOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDEFAULTINVENTORYLISTCOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


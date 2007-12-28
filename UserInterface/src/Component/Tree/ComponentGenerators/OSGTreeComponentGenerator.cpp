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

#include "OSGTreeComponentGenerator.h"
#include "Component/Tree/OSGTree.h"
#include "Component/OSGComponent.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TreeComponentGenerator
A UI Tree ComponentGenerator. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void TreeComponentGenerator::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

ComponentPtr TreeComponentGenerator::getComponent(ComponentPtr Parent, SharedFieldPtr Value, bool IsSelected, bool HasFocus)
{
    if(Parent->getType().isDerivedFrom(Tree::getClassType()))
    {
        return getTreeComponent(Tree::Ptr::dcast(Parent), Value, IsSelected, false, true, 0, HasFocus);
    }
    else
    {
        return getTreeComponent(NullFC, Value, IsSelected, false, true, 0, HasFocus);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

TreeComponentGenerator::TreeComponentGenerator(void) :
    Inherited()
{
}

TreeComponentGenerator::TreeComponentGenerator(const TreeComponentGenerator &source) :
    Inherited(source)
{
}

TreeComponentGenerator::~TreeComponentGenerator(void)
{
}

/*----------------------------- class specific ----------------------------*/

void TreeComponentGenerator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void TreeComponentGenerator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump TreeComponentGenerator NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGTREECOMPONENTGENERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGTREECOMPONENTGENERATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGTREECOMPONENTGENERATORFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


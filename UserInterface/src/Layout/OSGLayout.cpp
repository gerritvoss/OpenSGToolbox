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

#include <OpenSG/OSGConfig.h>

#include "OSGLayout.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Layout
A UI Layout Interface.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Layout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
Vec2f Layout::minimumLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return minimumContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::requestedLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return requestedContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::preferredLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return preferredContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::maximumLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return maximumContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::getComponentSize(ComponentPtr TheComponent, SizeType TheSizeType)
{
    switch(TheSizeType)
    {
    case MIN_SIZE:
        return TheComponent->getMinSize();
        break;
    case MAX_SIZE:
        return TheComponent->getMaxSize();
        break;
    case PREFERRED_SIZE:
        return TheComponent->getPreferredSize();
        break;
    case REQUESTED_SIZE:
    default:
        return TheComponent->getRequestedSize();
        break;
    }
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Layout::Layout(void) :
    Inherited()
{
}

Layout::Layout(const Layout &source) :
    Inherited(source)
{
}

Layout::~Layout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Layout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(getParentContainer() != NullFC)
    {
        Container::Ptr::dcast(getParentContainer())->updateLayout();
    }
}

void Layout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Layout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


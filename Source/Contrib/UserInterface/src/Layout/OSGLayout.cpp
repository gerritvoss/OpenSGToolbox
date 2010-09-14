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

#include "OSGLayout.h"
#include "OSGComponentContainer.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGLayoutBase.cpp file.
// To modify it, please change the .fcd file (OSGLayout.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Layout::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
ComponentContainer* Layout::getParentContainer(UInt32 index) const
{
    return dynamic_cast<ComponentContainer*>(_mfParentContainers[index]);
}

UInt32 Layout::getNumParentContainers(void) const
{
    return _mfParentContainers.size();
}

Vec2f Layout::minimumLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return minimumContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::requestedLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return requestedContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::preferredLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return preferredContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::maximumLayoutSize(const MFUnrecChildComponentPtr* Components, const Component* ParentComponent) const
{
    return maximumContentsLayoutSize(Components,ParentComponent) + ParentComponent->getBorderingLength();
}

Vec2f Layout::getComponentSize(const Component* TheComponent, SizeType TheSizeType)
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

void Layout::updateParentContainers(void)
{
    for(UInt32 i(0) ; i<_mfParentContainers.size() ; ++i)
    {
        getParentContainer(i)->updateLayout();
    }
}

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

void Layout::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void Layout::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump Layout NI" << std::endl;
}

OSG_END_NAMESPACE

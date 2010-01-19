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

#include "OSGOverlayLayout.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::OverlayLayout
A UI OverlayLayout. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void OverlayLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void OverlayLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
	Pnt2f borderTopLeft, borderBottomRight;
	Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(borderTopLeft, borderBottomRight);
	Vec2f borderSize(borderBottomRight-borderTopLeft);

	int maxX = 0;
	int maxY = 0;
	for(UInt32 i = 0; i < Components.size(); i++){
		beginEditCP(Components[i], Component::SizeFieldMask);
		   Components[i]->setSize(Components[i]->getPreferredSize());
		endEditCP(Components[i], Component::SizeFieldMask);
		if(Components[i]->getSize().x()>maxX)
			maxX = Components[i]->getSize().x();
		if(Components[i]->getSize().y()>maxY)
			maxY = Components[i]->getSize().y();
	}
	//overlay layout simply draws all the components on top of each other, with the reference point for all the components being the same
	for(UInt32 i = 0; i <Components.size(); i++){
		//Components[i]->setSize(Components[i]->getPreferredSize());
		beginEditCP(Components[i], Component::PositionFieldMask);
		Components[i]->setPosition(borderTopLeft + 
            Vec2f((maxX-Components[i]->getSize().x())/2.0,
			(maxY-Components[i]->getSize().y())/2.0));
		endEditCP(Components[i], Component::PositionFieldMask);
	}
}

Vec2f OverlayLayout::layoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent, SizeType TheSizeType) const
{
    Vec2f Result(0.0,0.0);

    Vec2f ComponentSize;
    for(UInt32 i(0) ; i<Components.size() ; ++i)
    {
        ComponentSize = getComponentSize(Components[i],TheSizeType);
        if(ComponentSize.x() > Result.x())
        {
            Result[0] = ComponentSize.x();
        }
        if(ComponentSize.y() > Result.y())
        {
            Result[1] = ComponentSize.y();
        }
    }

    return Result;
}

Vec2f OverlayLayout::minimumContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MIN_SIZE);
}

Vec2f OverlayLayout::requestedContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, REQUESTED_SIZE);
}

Vec2f OverlayLayout::preferredContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, PREFERRED_SIZE);
}

Vec2f OverlayLayout::maximumContentsLayoutSize(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
    return layoutSize(Components, ParentComponent, MAX_SIZE);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

OverlayLayout::OverlayLayout(void) :
    Inherited()
{
}

OverlayLayout::OverlayLayout(const OverlayLayout &source) :
    Inherited(source)
{
}

OverlayLayout::~OverlayLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void OverlayLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void OverlayLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump OverlayLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGOVERLAYLAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGOVERLAYLAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGOVERLAYLAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


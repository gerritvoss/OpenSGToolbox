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

#include "OSGAbsoluteLayout.h"
#include "OSGAbsoluteLayoutConstraints.h"
#include "Component/Container/OSGContainer.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::AbsoluteLayout
A UI AbsoluteLayout.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void AbsoluteLayout::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void AbsoluteLayout::updateLayout(const MFComponentPtr Components,const ComponentPtr ParentComponent) const
{
	Pnt2f ParentInsetsTopLeft, ParentInsetBottomRight;
    Container::Ptr::dcast(ParentComponent)->getInsideInsetsBounds(ParentInsetsTopLeft, ParentInsetBottomRight);
	for(UInt32 i = 0 ; i<Components.size(); ++i)
	{
		//Calculate the Components Size
		beginEditCP(Components[i], Component::PositionFieldMask|Component::SizeFieldMask);
			Components[i]->setSize(Components[i]->getPreferredSize());
			if(Components[i]->getConstraints() != NullFC)
			{
				//Get the Components Position
				Pnt2f pos = AbsoluteLayoutConstraintsPtr::dcast(Components[i]->getConstraints())->getPosition();
				
				Components[i]->setPosition(ParentInsetsTopLeft + Vec2f(pos));
			}
			else
			{
			   Components[i]->setPosition(ParentInsetsTopLeft);
			}
		endEditCP(Components[i], Component::PositionFieldMask|Component::SizeFieldMask);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

AbsoluteLayout::AbsoluteLayout(void) :
    Inherited()
{
}

AbsoluteLayout::AbsoluteLayout(const AbsoluteLayout &source) :
    Inherited(source)
{
}

AbsoluteLayout::~AbsoluteLayout(void)
{
}

/*----------------------------- class specific ----------------------------*/

void AbsoluteLayout::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void AbsoluteLayout::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump AbsoluteLayout NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGABSOLUTELAYOUTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGABSOLUTELAYOUTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGABSOLUTELAYOUTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


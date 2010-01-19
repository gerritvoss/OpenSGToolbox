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

#include "OSGComponentMenuItem.h"
#include "Util/OSGUIDrawUtils.h"
#include "Component/Container/Window/OSGInternalWindow.h"
#include "LookAndFeel/OSGLookAndFeelManager.h"
#include "Component/Menu/OSGMenu.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ComponentMenuItem
A UI ComponentMenuItem. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ComponentMenuItem::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void ComponentMenuItem::drawInternal(const GraphicsPtr TheGraphics, Real32 Opacity) const
{
	if(getComponent() != NullFC)
	{
		getComponent()->draw(TheGraphics, getOpacity()*Opacity);
	}
}

Vec2f ComponentMenuItem::getContentRequestedSize(void) const
{
	if(getComponent() != NullFC)
	{
		Vec2f ComponentRequestedSize(0.0,0.0);
		if(getComponent() != NullFC)
		{
			ComponentRequestedSize = getComponent()->getRequestedSize();
		}

        Pnt2f AcceleratorTextTopLeft, AcceleratorTextBottomRight;
        getFont()->getBounds(_AcceleratorText, AcceleratorTextTopLeft, AcceleratorTextBottomRight);
        
		Vec2f RequestedSize((ComponentRequestedSize.x()) + (AcceleratorTextBottomRight.x() - AcceleratorTextTopLeft.x()), osgMax(getPreferredSize().y(), ComponentRequestedSize.y()));

		if(!_AcceleratorText.empty())
		{
			RequestedSize[0] += 50.0f;
		}
		else
		{
			RequestedSize[0] += 25.0f;
		}

		return RequestedSize;
	}
	else
	{
		return Inherited::getContentRequestedSize();
	}
}

void ComponentMenuItem::updateComponentBounds(void)
{
	if(getComponent() != NullFC)
	{
		Pnt2f InsideBorderTopLeft, InsideBorderBottomRight;
		getInsideBorderBounds(InsideBorderTopLeft, InsideBorderBottomRight);

		beginEditCP(getComponent(), Component::PositionFieldMask | Component::SizeFieldMask);
			getComponent()->setPosition(InsideBorderTopLeft);
			getComponent()->setSize(InsideBorderBottomRight - InsideBorderTopLeft);
		endEditCP(getComponent(), Component::PositionFieldMask | Component::SizeFieldMask);
	}
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ComponentMenuItem::ComponentMenuItem(void) :
    Inherited()
{
}

ComponentMenuItem::ComponentMenuItem(const ComponentMenuItem &source) :
    Inherited(source)
{
}

ComponentMenuItem::~ComponentMenuItem(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ComponentMenuItem::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

	if((whichField & SizeFieldMask) ||
		(whichField & ComponentFieldMask))
	{
		updateComponentBounds();
	}

    if(whichField & ComponentFieldMask ||
		whichField & AcceleratorKeyFieldMask ||
       whichField & AcceleratorModifiersFieldMask)
    {
        updateAcceleratorText();
    }

}

void ComponentMenuItem::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ComponentMenuItem NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGCOMPONENTMENUITEMBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOMPONENTMENUITEMBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOMPONENTMENUITEMFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


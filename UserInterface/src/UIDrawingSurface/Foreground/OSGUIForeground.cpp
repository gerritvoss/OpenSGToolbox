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
#include <OpenSG/OSGViewport.h>
#include <OpenSG/OSGMFVecTypes.h>

#include "UIDrawingSurface/OSGUIDrawingSurface.h" // DrawingSurface type

#include "UIDrawingSurface/Foreground/OSGUIForegroundMouseTransformFunctor.h"
#include "Component/Container/Window/OSGInternalWindow.h"

#include "OSGUIForeground.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIForeground
A Foreground for rendering a UI on.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIForeground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void UIForeground::draw( DrawActionBase * action, Viewport * port )
{
	if(getDrawingSurface()->getSize().x() != port->getPixelWidth() ||
	   getDrawingSurface()->getSize().y() != port->getPixelHeight())
	{
		beginEditCP(getDrawingSurface(), UIDrawingSurface::SizeFieldMask);
			getDrawingSurface()->setSize(Vec2s(port->getPixelWidth(), port->getPixelHeight()));
		endEditCP(getDrawingSurface(), UIDrawingSurface::SizeFieldMask);
	}

	glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
     
    glOrtho(0, port->getPixelWidth(), port->getPixelHeight(), 0 , 0, 1);
	
	glMatrixMode(GL_MODELVIEW);

	//Render the UI to the Foreground
    getDrawingSurface()->getGraphics()->setDrawAction(action);
	//Call The PreDraw on the Graphics
	getDrawingSurface()->getGraphics()->preDraw();

	//Draw all of the InternalWindows
	for(UInt32 i(0) ; i<getDrawingSurface()->getInternalWindows().size() ; ++i)
	{
		getDrawingSurface()->getInternalWindows().getValue(i)->draw(getDrawingSurface()->getGraphics());
	}

	//Call the PostDraw on the Graphics
	getDrawingSurface()->getGraphics()->postDraw();

	glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIForeground::UIForeground(void) :
    Inherited()
{
	if(getMouseTransformFunctor() != NullFC)
	{
		beginEditCP(getMouseTransformFunctor(), UIForegroundMouseTransformFunctor::ParentFieldMask);
			getMouseTransformFunctor()->setParent(UIForegroundPtr(this));
		endEditCP(getMouseTransformFunctor(), UIForegroundMouseTransformFunctor::ParentFieldMask);
	}
}

UIForeground::UIForeground(const UIForeground &source) :
    Inherited(source)
{
	if(getMouseTransformFunctor() != NullFC)
	{
		beginEditCP(getMouseTransformFunctor(), UIForegroundMouseTransformFunctor::ParentFieldMask);
			getMouseTransformFunctor()->setParent(UIForegroundPtr(this));
		endEditCP(getMouseTransformFunctor(), UIForegroundMouseTransformFunctor::ParentFieldMask);
	}
}

UIForeground::~UIForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIForeground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
	
	if( (whichField & DrawingSurfaceFieldMask) &&
		getDrawingSurface() != NullFC)
    {
	}
}

void UIForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIForeground NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIFOREGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIFOREGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIFOREGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


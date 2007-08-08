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

#include "OSGFrame.h"
#include "UIDrawingSurface/OSGUIDrawingSurface.h"
#include "Component/Misc/OSGToolTip.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Frame
A UI Frame. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Frame::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void Frame::keyPressed(const KeyEvent& e)
{
	//Send Key event to Component that has Focus
	//If there is not Focused Component then do nothing
	if(getFocusedComponent() != NullFC &&
	   getFocusedComponent() != ComponentPtr(this))
	{
		getFocusedComponent()->keyPressed(e);
		ContainerPtr ParentContainer(getFocusedComponent()->getParentContainer());
		while(ParentContainer != NullFC &&
			ParentContainer != ContainerPtr(this))
		{
			ParentContainer->keyPressed(e);
			ParentContainer = Container::Ptr::dcast(ParentContainer->getParentContainer());
		}
	}
    Component::keyPressed(e);
}

void Frame::keyReleased(const KeyEvent& e)
{
	//Send Key event to Component that has Focus
	//If there is not Focused Component then do nothing
	if(getFocusedComponent() != NullFC &&
	   getFocusedComponent() != ComponentPtr(this))
	{
		getFocusedComponent()->keyReleased(e);
		ContainerPtr ParentContainer(getFocusedComponent()->getParentContainer());
		while(ParentContainer != NullFC &&
			ParentContainer != ContainerPtr(this))
		{
			ParentContainer->keyReleased(e);
			ParentContainer = Container::Ptr::dcast(ParentContainer->getParentContainer());
		}
	}
    Component::keyReleased(e);
}

void Frame::keyTyped(const KeyEvent& e)
{
	//Send Key event to Component that has Focus
	//If there is not Focused Component then do nothing
	if(getFocusedComponent() != NullFC &&
	   getFocusedComponent() != ComponentPtr(this))
	{
		getFocusedComponent()->keyTyped(e);
		ContainerPtr ParentContainer(getFocusedComponent()->getParentContainer());
		while(ParentContainer != NullFC &&
			ParentContainer != ContainerPtr(this))
		{
			ParentContainer->keyTyped(e);
			ParentContainer = Container::Ptr::dcast(ParentContainer->getParentContainer());
		}
	}
    Component::keyTyped(e);
}

FramePtr &Frame::getParentFrame(void)
{
    if(Component::getParentFrame() == NullFC)
    {
		beginEditCP(FramePtr(this), Component::ParentFrameFieldMask);
		setParentFrame(FramePtr(this));
		endEditCP(FramePtr(this), Component::ParentFrameFieldMask);
    }
    return Component::getParentFrame();
}

const FramePtr &Frame::getParentFrame(void) const
{
    if(Component::getParentFrame() == NullFC)
    {
		  beginEditCP(FramePtr(this), Component::ParentFrameFieldMask);
		  const_cast<Frame*>(this)->setParentFrame(FramePtr(this));
		  endEditCP(FramePtr(this), Component::ParentFrameFieldMask);
    }
    return Component::getParentFrame();
}

void Frame::drawInternal(const GraphicsPtr TheGraphics) const
{
    Inherited::drawInternal(TheGraphics);
        
    //If I have an active tooltip then draw it
    if(getActiveToolTip() != NullFC)
    {
        getActiveToolTip()->draw(TheGraphics);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Frame::Frame(void) :
    Inherited()
{
}

Frame::Frame(const Frame &source) :
    Inherited(source)
{
}

Frame::~Frame(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Frame::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if( (whichField & ActiveToolTipFieldMask) &&
        getActiveToolTip() != NullFC)
    {
        getActiveToolTip()->updateClipBounds();
    }
}

void Frame::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Frame NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGFRAMEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFRAMEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFRAMEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


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

#include "OSGUIViewport.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIViewport
A UI UIViewport 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIViewport::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIViewport::updateLayout(void)
{
    if(getViewComponent() != NullFC)
    {
        Vec2s Size;
        if(getViewSize() != Vec2s(-1,-1))
        {
            Size = getViewSize();
        }
        else
        {
            Size = getViewComponent()->getPreferredSize();
        }
        
        beginEditCP(getViewComponent(), Component::SizeFieldMask | Component::PositionFieldMask);
            getViewComponent()->setSize(Size);
            getViewComponent()->setPosition(-getViewPosition());
        endEditCP(getViewComponent(), Component::SizeFieldMask | Component::PositionFieldMask);
        
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void UIViewport::produceStateChanged(const ChangeEvent& e)
{
    ChangeListenerSet ListenerSet(_ChangeListeners);
    for(ChangeListenerSetConstItor SetItor(ListenerSet.begin()) ; SetItor != ListenerSet.end() ; ++SetItor)
    {
	    (*SetItor)->stateChanged(e);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIViewport::UIViewport(void) :
    Inherited()
{
}

UIViewport::UIViewport(const UIViewport &source) :
    Inherited(source)
{
}

UIViewport::~UIViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIViewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);

    if(whichField & ViewComponentFieldMask)
    {
        beginEditCP(UIViewportPtr(this), ChildrenFieldMask);
            getChildren().clear();
            if(getViewComponent() != NullFC)
            {
                getChildren().push_back(getViewComponent());
            }
        endEditCP(UIViewportPtr(this), ChildrenFieldMask);
    }

    if((whichField & ViewSizeFieldMask) ||
        (whichField & ViewPositionFieldMask))
    {
        updateLayout();
    }

    if((whichField & ViewSizeFieldMask) ||
        (whichField & ViewPositionFieldMask) ||
        (whichField & SizeFieldMask))
    {
        produceStateChanged(ChangeEvent(NullFC, getSystemTime(), ChangeEvent::STATE_CHANGED));
    }
}

void UIViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIViewport NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIVIEWPORTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIVIEWPORTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

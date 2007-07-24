/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGSimpleGeometry.h>

#include "UIDrawingSurface/OSGUIDrawingSurface.h"

#include "OSGUIRectangle.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::UIRectangle
A UI Rectangle. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIRectangle::initMethod (void)
{
    DrawAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, UIRectanglePtr,
              CNodePtr, Action *>(&UIRectangle::drawActionHandler));

    IntersectAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, UIRectanglePtr,
              CNodePtr, Action *>(&UIRectangle::intersect));

    RenderAction::registerEnterDefault(getClassType(),
        osgTypedMethodFunctor2BaseCPtrRef<Action::ResultE, UIRectanglePtr,
              CNodePtr, Action *>(&UIRectangle::renderActionHandler));
}

Action::ResultE UIRectangle::drawPrimitives (DrawActionBase *action)
{
    glPushMatrix();
    glTranslatef(0.0,getSide2().length(),0.0);
    glScalef(1.0,-1.0,1.0);
	//Render the UI to the Rectangle
    getDrawingSurface()->getGraphics()->setDrawAction(action);
	//Call The PreDraw on the Graphics
	getDrawingSurface()->getGraphics()->preDraw();

	//Draw The Component
	getDrawingSurface()->getRootFrame()->draw(getDrawingSurface()->getGraphics());

	//Call the PostDraw on the Graphics
	getDrawingSurface()->getGraphics()->postDraw();
    glPopMatrix();
    return Action::Continue;
}

Action::ResultE UIRectangle::drawActionHandler( Action* action )
{
    return drawPrimitives(dynamic_cast<DrawAction *>(action));
}

Action::ResultE UIRectangle::renderActionHandler( Action* action )
{

    dynamic_cast<RenderAction *>(action)->dropFunctor(osgTypedMethodFunctor1ObjPtr(this, 
                                        &UIRectangle::drawPrimitives), getDefaultUnlitMaterial().getCPtr());
    return Action::Continue;
}

Action::ResultE UIRectangle::intersect( Action* action )
{
    return Action::Continue;
}

void UIRectangle::adjustVolume(Volume & volume)
{
    volume.setValid();
    volume.setEmpty();

    volume.extendBy(getPoint());
    volume.extendBy(getPoint()+ getSide1());
    volume.extendBy(getPoint()+ getSide1()+ getSide2());
    volume.extendBy(getPoint()+ getSide2());
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void UIRectangle::updateFrameBounds(void)
{
    if(getDrawingSurface() == NullFC)
    {
        return;
    }
	Vec2s Size(getSide1().length(),getSide2().length());
	
	//Translate to the Frames Position
    //Calculate Alignment
    Pnt2s AlignedPosition(0,0);

    if(getDrawingSurface()->getRootFrame()->getSize() != Size ||
       getDrawingSurface()->getRootFrame()->getPosition() != AlignedPosition)
    {
        beginEditCP(getDrawingSurface()->getRootFrame(), Frame::SizeFieldMask | Frame::PositionFieldMask);
		    getDrawingSurface()->getRootFrame()->setSize(Size);
		    getDrawingSurface()->getRootFrame()->setPosition(AlignedPosition);
	    endEditCP(getDrawingSurface()->getRootFrame(), Frame::SizeFieldMask | Frame::PositionFieldMask);
    }
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIRectangle::UIRectangle(void) :
    Inherited()
{
}

UIRectangle::UIRectangle(const UIRectangle &source) :
    Inherited(source)
{
}

UIRectangle::~UIRectangle(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIRectangle::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if( (whichField & Side1FieldMask) ||
        (whichField & Side2FieldMask) ||
        (whichField & DrawingSurfaceFieldMask) )
    {
        updateFrameBounds();
    }
}

void UIRectangle::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump UIRectangle NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGUIRECTANGLEBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGUIRECTANGLEBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGUIRECTANGLEFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


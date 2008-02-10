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
#include <OpenSG/OSGRenderAction.h>
#include <OpenSG/OSGDrawAction.h>
#include <OpenSG/OSGIntersectAction.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGColorMaskChunk.h>
#include <OpenSG/OSGPolygonChunk.h>

#include "UIDrawingSurface/OSGUIDrawingSurface.h"

#include "OSGUIRectangle.h"
#include "UIDrawingSurface/NodeCore/OSGUIRectangleMouseTransformFunctor.h"   // MouseTransformFunctor default header
#include "Component/Container/Window/OSGInternalWindow.h"

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

    glTranslatef(getPoint().x(),getPoint().y()+getHeight(),getPoint().z());

    glScalef(1.0,-1.0,1.0);
	//Render the UI to the Rectangle
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
	
	getRectColorMask()->activate(action);
	getRectPolygon()->activate(action);
	glBegin(GL_QUADS);
	   glVertex3fv(getPoint().getValues());
	   glVertex3f(getPoint().x(), getPoint().y()+getHeight(), getPoint().z());
	   glVertex3f(getPoint().x()+getWidth(), getPoint().y()+getHeight(), getPoint().z());
	   glVertex3f(getPoint().x()+getWidth(), getPoint().y(), getPoint().z());
	glEnd();
	getRectPolygon()->deactivate(action);
	getRectColorMask()->deactivate(action);

    return Action::Continue;
}

Action::ResultE UIRectangle::drawActionHandler( Action* action )
{
    return drawPrimitives(dynamic_cast<DrawAction *>(action));
}

Action::ResultE UIRectangle::renderActionHandler( Action* action )
{
    Material::DrawFunctor func;
    func = osgTypedMethodFunctor1ObjPtr(this,
                                                  &UIRectangle::drawPrimitives);
    dynamic_cast<RenderAction *>(action)->dropFunctor(func, getDefaultUnlitMaterial().getCPtr());
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
    volume.extendBy(getPoint()+ Vec3f(getWidth(),0.0,0.0));
    volume.extendBy(getPoint()+ Vec3f(getWidth(),0.0,0.0)+ Vec3f(0.0,getHeight(),0.0));
    volume.extendBy(getPoint()+ Vec3f(0.0,getHeight(),0.0));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

UIRectangle::UIRectangle(void) :
    Inherited()
{
	setRectColorMask(ColorMaskChunk::create());
	getRectColorMask()->setMaskR(false);
	getRectColorMask()->setMaskG(false);
	getRectColorMask()->setMaskB(false);
	getRectColorMask()->setMaskA(false);

	setRectPolygon(PolygonChunk::create());
	getRectPolygon()->setOffsetFactor(1.0);
	getRectPolygon()->setOffsetBias(1.0);
	getRectPolygon()->setOffsetFill(true); 
}

UIRectangle::UIRectangle(const UIRectangle &source) :
    Inherited(source)
{
	if(getMouseTransformFunctor() != NullFC)
	{
		beginEditCP(getMouseTransformFunctor(), UIRectangleMouseTransformFunctor::ParentFieldMask);
			getMouseTransformFunctor()->setParent(UIRectanglePtr(this));
		endEditCP(getMouseTransformFunctor(), UIRectangleMouseTransformFunctor::ParentFieldMask);
	}
}

UIRectangle::~UIRectangle(void)
{
	if(getMouseTransformFunctor() != NullFC)
	{
		beginEditCP(getMouseTransformFunctor(), UIRectangleMouseTransformFunctor::ParentFieldMask);
			getMouseTransformFunctor()->setParent(UIRectanglePtr(this));
		endEditCP(getMouseTransformFunctor(), UIRectangleMouseTransformFunctor::ParentFieldMask);
	}
}

/*----------------------------- class specific ----------------------------*/

void UIRectangle::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if( (whichField & HeightFieldMask) ||
        (whichField & WidthFieldMask) ||
        (whichField & DrawingSurfaceFieldMask) )
    {
		invalidateVolume();
		
		if(getDrawingSurface()->getSize().x() != static_cast<Real32>(getWidth()) ||
		   getDrawingSurface()->getSize().y() != static_cast<Real32>(getHeight()))
		{
			beginEditCP(getDrawingSurface(), UIDrawingSurface::SizeFieldMask);
				getDrawingSurface()->setSize(Vec2f(static_cast<Real32>(getWidth()), static_cast<Real32>(getHeight())));
			endEditCP(getDrawingSurface(), UIDrawingSurface::SizeFieldMask);
		}
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


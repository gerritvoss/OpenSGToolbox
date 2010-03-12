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

#include "OSGUIRectangle.h"
#include "OSGRenderAction.h"
#include "OSGIntersectAction.h"
#include "OSGSimpleGeometry.h"
#include "OSGColorMaskChunk.h"
#include "OSGPolygonChunk.h"

#include "OSGUIDrawingSurface.h"

#include "OSGUIRectangleMouseTransformFunctor.h"   // MouseTransformFunctor default header
#include "OSGInternalWindow.h"
#include "OSGGL.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIRectangleBase.cpp file.
// To modify it, please change the .fcd file (OSGUIRectangle.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIRectangle::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        RenderAction::registerEnterDefault(
            UIRectangle::getClassType(),
            reinterpret_cast<Action::Callback>(
                &UIRectangle::renderActionEnterHandler));

        RenderAction::registerLeaveDefault(
            UIRectangle::getClassType(),
            reinterpret_cast<Action::Callback>(
                &UIRectangle::renderActionLeaveHandler));
#ifndef OSG_EMBEDDED
        IntersectAction::registerEnterDefault(
            UIRectangle::getClassType(),
            reinterpret_cast<Action::Callback>(
                &UIRectangle::intersect));
#endif
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Action::ResultE UIRectangle::renderActionEnterHandler(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);

    Material::DrawFunctor func;

    func = boost::bind(&UIRectangle::drawPrimitives, this, _1);

    a->dropFunctor(func, _State, 0, false);

    if(a->pushVisibility())
    {
        if(a->selectVisibles() == 0)
        {
            a->popVisibility();
            return Action::Skip;
        }
    }
    
    return Action::Continue;
}

Action::ResultE UIRectangle::renderActionLeaveHandler(Action *action)
{
    RenderAction *a = dynamic_cast<RenderAction *>(action);
    
    a->popVisibility();
    
    return Action::Continue;
}

Action::ResultE UIRectangle::drawPrimitives          (DrawEnv *pEnv  )
{
    glPushMatrix();

    glTranslatef(getPoint().x(),getPoint().y()+getHeight(),getPoint().z());

    glScalef(1.0,-1.0,1.0);
	//Render the UI to the Rectangle
    getDrawingSurface()->getGraphics()->setDrawEnv(pEnv);
	//Call The PreDraw on the Graphics
	getDrawingSurface()->getGraphics()->preDraw();

	//Draw all of the InternalWindows
	for(UInt32 i(0) ; i<getDrawingSurface()->getMFInternalWindows()->size() ; ++i)
	{
		getDrawingSurface()->getInternalWindows(i)->draw(getDrawingSurface()->getGraphics());
	}

	//Call the PostDraw on the Graphics
	getDrawingSurface()->getGraphics()->postDraw();
    glPopMatrix();
	
	getRectColorMask()->activate(pEnv);
	getRectPolygon()->activate(pEnv);
	glBegin(GL_QUADS);
	   glVertex3fv(getPoint().getValues());
	   glVertex3f(getPoint().x(), getPoint().y()+getHeight(), getPoint().z());
	   glVertex3f(getPoint().x()+getWidth(), getPoint().y()+getHeight(), getPoint().z());
	   glVertex3f(getPoint().x()+getWidth(), getPoint().y(), getPoint().z());
	glEnd();
	getRectPolygon()->deactivate(pEnv);
	getRectColorMask()->deactivate(pEnv);

    return Action::Continue;
}

Action::ResultE UIRectangle::intersect( Action* action )
{
    //TODO: Implement
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

void UIRectangle::fill(DrawableStatsAttachment *pStat)
{
    if(pStat == NULL)
    {
        FINFO(("UIRectangle::fill(DrawableStatsAttachment *): "
               "No attachment given.\n"));

        return;
    }

    //Determine the stats of the UI
    //pStat->setVertices(vertices);
    //pStat->setPoints(point);
    //pStat->setLines(line);
    //pStat->setTriangles(triangle);
    //pStat->setStoredAttributeBytes(storedAttBytes);
    //pStat->setProcessedAttributeBytes(procAttBytes);
    //pStat->setValid(true);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void UIRectangle::onCreate(const UIRectangle * Id)
{
	Inherited::onCreate(Id);

    ColorMaskChunkUnrecPtr TheMask(ColorMaskChunk::create());
	setRectColorMask(TheMask);
	getRectColorMask()->setMaskR(false);
	getRectColorMask()->setMaskG(false);
	getRectColorMask()->setMaskB(false);
	getRectColorMask()->setMaskA(false);

    PolygonChunkUnrecPtr ThePolyChunk(PolygonChunk::create());
	setRectPolygon(ThePolyChunk);
	getRectPolygon()->setOffsetFactor(1.0);
	getRectPolygon()->setOffsetBias(1.0);
	getRectPolygon()->setOffsetFill(true); 

    UIRectangleMouseTransformFunctorUnrecPtr TheTransFunc(UIRectangleMouseTransformFunctor::create());
	setMouseTransformFunctor(TheTransFunc);
    if(getMouseTransformFunctor() != NULL)
    {
        getMouseTransformFunctor()->setParent(this);
    }

	
	_State = State::create();
}

void UIRectangle::onDestroy()
{
}

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

void UIRectangle::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
    
    if( ((whichField & HeightFieldMask) ||
        (whichField & WidthFieldMask) ||
        (whichField & DrawingSurfaceFieldMask))
        && getDrawingSurface() != NULL)
    {
		invalidateVolume();
		
		if(getDrawingSurface()->getSize().x() != static_cast<Real32>(getWidth()) ||
		   getDrawingSurface()->getSize().y() != static_cast<Real32>(getHeight()))
		{
            getDrawingSurface()->setSize(Vec2f(static_cast<Real32>(getWidth()), static_cast<Real32>(getHeight())));
		}
    }
	
	if( (whichField & DrawingSurfaceFieldMask) &&
		getDrawingSurface() != NULL)
    {
        getDrawingSurface()->setMouseTransformFunctor(getMouseTransformFunctor());
	}
}

void UIRectangle::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIRectangle NI" << std::endl;
}

OSG_END_NAMESPACE

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

#include "OSGUIForeground.h"
#include "OSGUIForegroundMouseTransformFunctor.h"
#include "OSGInternalWindow.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGUIForegroundBase.cpp file.
// To modify it, please change the .fcd file (OSGUIForeground.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void UIForeground::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void UIForeground::draw(DrawEnv * env, Viewport * port)
{
    if(!getDrawingSurface() ||
       !getDrawingSurface()->getGraphics() ||
       !getActive())
    {
        return;
    }

    if(getDrawingSurface()->getSize().x() != port->getPixelWidth() ||
       getDrawingSurface()->getSize().y() != port->getPixelHeight())
    {
        getDrawingSurface()->setSize(Vec2f(port->getPixelWidth(), port->getPixelHeight()));
    }

	glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
     
    glOrtho(0, port->getPixelWidth(), port->getPixelHeight(), 0 , 0, 1);
	
	glMatrixMode(GL_MODELVIEW);

	//Render the UI to the Foreground
    getDrawingSurface()->getGraphics()->setDrawEnv(env);

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
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void UIForeground::onCreate(const UIForeground * Id)
{
	Inherited::onCreate(Id);

    UIForegroundMouseTransformFunctorUnrecPtr TheTransFunc(UIForegroundMouseTransformFunctor::create());
	setMouseTransformFunctor(TheTransFunc);
    if(getMouseTransformFunctor() != NULL)
    {
        getMouseTransformFunctor()->setParent(this);
    }
}

void UIForeground::onDestroy()
{
}

/*----------------------- constructors & destructors ----------------------*/

UIForeground::UIForeground(void) :
    Inherited()
{
}

UIForeground::UIForeground(const UIForeground &source) :
    Inherited(source)
{
}

UIForeground::~UIForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void UIForeground::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
	
	if( (whichField & DrawingSurfaceFieldMask) &&
		getDrawingSurface() != NULL)
    {
        getDrawingSurface()->setMouseTransformFunctor(getMouseTransformFunctor());
	}
	if((whichField & (ActiveFieldMask | DrawingSurfaceFieldMask)) && 
        getDrawingSurface() != NULL &&
        getDrawingSurface()->getActive() != getActive())
    {
        getDrawingSurface()->setActive(getActive());
    }
}

void UIForeground::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump UIForeground NI" << std::endl;
}

OSG_END_NAMESPACE

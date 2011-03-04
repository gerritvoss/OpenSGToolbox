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
void UIForeground::draw(DrawEnv * env)
{
    if(!getDrawingSurface() ||
       !getDrawingSurface()->getGraphics() ||
       !getActive())
    {
        return;
    }

    if(getDrawingSurface()->getSize().x() != env->getPixelWidth() ||
       getDrawingSurface()->getSize().y() != env->getPixelHeight())
    {
        if(env->getTileFullSize()[0] != 0)
        {
            getDrawingSurface()->setSize(Vec2f(env->getTileFullSize()[0], env->getTileFullSize()[1]));
        }
        else
        {
            getDrawingSurface()->setSize(Vec2f(env->getPixelWidth(), env->getPixelHeight()));
        }
    }

    //Setup the orthographic projection
    UInt32 fullWidth;
    UInt32 fullHeight;
    beginOrthoRender(env, fullWidth, fullHeight);

    //Give the draw environment to the Graphics of the drawing surface
    getDrawingSurface()->getGraphics()->setDrawEnv(env);

    //Draw the drawing surface
    getDrawingSurface()->draw();

    //reset the matrices
    endOrthoRender(env);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*! Sets up an ortho projection for rendering. It handles tiling
    when a TileCameraDecorator is in use. When done you need to call
    endOrthoRender to clean up changes to the OpenGL matrix stacks.

    \param pEnv DrawEnv being used for rendering
    \param normX Wether x coordinates are going to be normalized.
    \param normY Wether y coordinates are going to be normalized.
    \param[out] fullWidth width of the viewport
    \param[out] fullHeight height of the viewport

    \note When the TileCameraDecorator is in use, the width and height of the
          viewport (fullWidth, fullHeight) are defined by the TileCameraDecorator.
 */
void UIForeground::beginOrthoRender(DrawEnv *pEnv,
                                    UInt32  &fullWidth,
                                    UInt32  &fullHeight)
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    UInt32               width   = pEnv->getPixelWidth ();
    UInt32               height  = pEnv->getPixelHeight();

    fullWidth  = pEnv->getTileFullSize()[0];
    fullHeight = pEnv->getTileFullSize()[1];

    if(fullWidth == 0)
    {
        fullWidth  = width;
        fullHeight = height;
    }
    else if(!getTile())
    {
        Matrix sm = pEnv->calcTileDecorationMatrix();

        glLoadMatrixf(sm.getValues());
    }

    glOrtho(0 - 0.375,
            static_cast<Real32>(fullWidth) - 0.375,
            static_cast<Real32>(fullHeight) - 0.375,
            0 - 0.375,
            0,
            1);

    glMatrixMode(GL_MODELVIEW);
}

/*! Clean up changes to the OpenGL matrix stacks done by beginOrthoRender
 */
void UIForeground::endOrthoRender(DrawEnv *pEnv)
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

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

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

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

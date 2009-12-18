/*---------------------------------------------------------------------------*\
 *                       OpenSG ToolBox ImageProcessing                      *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#define OSG_COMPILEIMAGEPROCESSINGLIB

#include <OpenSG/OSGConfig.h>

#include "OSGImageProcessedForeground.h"
#include "TextureFilter/OSGTextureFilter.h"
#include <OpenSG/OSGTextureChunk.h>
#include <OpenSG/OSGViewport.h>

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ImageProcessedForeground

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ImageProcessedForeground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
void ImageProcessedForeground::draw( DrawActionBase * action, Viewport * port )
{
    Int32 Width(port->getPixelWidth()),Height(port->getPixelHeight());
    getFilter()->setDirty(true);

    //Update the Filter graph upstream from the filter this foreground is using
    getFilter()->update(dynamic_cast<RenderActionBase*>(action), Vec2f(Width, Height));

    //Activate the initial viewport
    port->activate();

    //Remove Any Modelview transformations
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    glLoadIdentity();

    //Setup a Orothographic projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
     
    glOrtho(0, Width, 0, Height , 0, 1);

    //Activate the Texture
    TextureChunkPtr TheTexture(getFilter()->pullTexture(getOutputSlot()));
    TheTexture->activate(action);
    glDisable(GL_DEPTH_TEST);

    //Draw a viewport sized quad
    glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f,1.0f,1.0f,1.0f);

        glTexCoord2i(0,0);
        glVertex2i(0,0);

        glTexCoord2i(0,1);
        glVertex2i(0,Height);

        glTexCoord2i(1,1);
        glVertex2i(Width,Height);

        glTexCoord2i(1,0);
        glVertex2i(Width,0);
	glEnd();

    //Dectivate the Texture
    TheTexture->deactivate(action);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ImageProcessedForeground::ImageProcessedForeground(void) :
    Inherited()
{
}

ImageProcessedForeground::ImageProcessedForeground(const ImageProcessedForeground &source) :
    Inherited(source)
{
}

ImageProcessedForeground::~ImageProcessedForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ImageProcessedForeground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ImageProcessedForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ImageProcessedForeground NI" << std::endl;
}


OSG_END_NAMESPACE


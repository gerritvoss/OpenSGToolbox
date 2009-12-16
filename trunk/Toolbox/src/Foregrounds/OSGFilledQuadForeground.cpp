/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
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

#define OSG_COMPILETOOLBOXLIB

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGMaterial.h>

#include "OSGFilledQuadForeground.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FilledQuadForeground

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FilledQuadForeground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void FilledQuadForeground::draw( DrawActionBase * action, Viewport * port )
{
    glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
     
    glOrtho(0, 1, 0, 1 , 0, 1);

    //Activate the Material
    getMaterial()->getState()->activate(action);

    //Draw a viewport sized quad
    glBegin(GL_TRIANGLE_FAN);
        glColor4f(1.0f,1.0f,1.0f,1.0f);

        glNormal3i(0,0,1);

        glTexCoord2i(0,0);
        glVertex2i(0,0);

        glTexCoord2i(0,1);
        glVertex2i(0,1);

        glTexCoord2i(1,1);
        glVertex2i(1,1);

        glTexCoord2i(1,0);
        glVertex2i(1,0);
	glEnd();

    //Dectivate the Material
    getMaterial()->getState()->deactivate(action);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FilledQuadForeground::FilledQuadForeground(void) :
    Inherited()
{
}

FilledQuadForeground::FilledQuadForeground(const FilledQuadForeground &source) :
    Inherited(source)
{
}

FilledQuadForeground::~FilledQuadForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void FilledQuadForeground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FilledQuadForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FilledQuadForeground NI" << std::endl;
}


OSG_END_NAMESPACE


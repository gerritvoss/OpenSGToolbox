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

#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGGLUTWindow.h>

#include "OSGGLUTWindowEventProducer.h"
#include "WindowSystem/OSGWindowEventProducerFactory.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GLUTWindowEventProducer
GLUTWindowEventProducer Class.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void GLUTWindowEventProducer::initMethod (void)
{
	//Register this WindowEventProducer As the GLUTWindow WindowEventProducer with the factory
	WindowEventProducerFactory::the()->registerProducer(&GLUTWindow::getClassType(), &GLUTWindowEventProducer::getClassType());
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

//Set the Window Position
void GLUTWindowEventProducer::setPosition(Pnt2s Pos)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //Position the Window
   glutPositionWindow(Pos.x(), Pos.y());
}

//Set the Window Position
Pnt2s GLUTWindowEventProducer::getPosition(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //Return the Window's position
   return Pnt2s(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y));
}

//Set the Window size
void GLUTWindowEventProducer::setSize(Vec2us Size)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //Resize the Window
   glutReshapeWindow(Size.x(), Size.y());

   //Resize the OpenGL Viewports
   getWindow()->resize(Size.x(), Size.y());
}

//Get the Window size
Vec2s GLUTWindowEventProducer::getSize(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //Return the Window's Size
   return Vec2s(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

//Focused
//Set the Window Focus
void GLUTWindowEventProducer::setFocused(bool Focused)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::setFocused(bool Focused): GLUT Does not define a function for setting its focus." << std::endl;
   
}

//Get the Window Focus
bool GLUTWindowEventProducer::getFocused(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getFocused(void): GLUT Does not define a query for Focus." << std::endl;
   
   return false;
}

//Visible / Iconify / Normal
//Set the Window Visible
void GLUTWindowEventProducer::setVisible(bool Visible)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   if(Visible)
   {
      glutShowWindow();
   }
   else
   {
      glutHideWindow();
   }
}

//Get the Window Visible
bool GLUTWindowEventProducer::getVisible(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getVisible(void): GLUT Does not define a query for Visibility." << std::endl;
   
   return false;
}

//Set the Window Iconify
void GLUTWindowEventProducer::setIconify(bool Iconify)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   if(Iconify)
   {
      glutIconifyWindow();
   }
   else
   {
      glutShowWindow();
   }
}

//Get the Window Iconify
bool GLUTWindowEventProducer::getIconify(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getIconify(void): GLUT Does not define a query for Iconify." << std::endl;
   
   return false;
}

//Fullscreen
void GLUTWindowEventProducer::setFullscreen(bool Fullscreen)
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   if(Fullscreen)
   {
      glutFullScreen();
   }
   else
   {
      //Reset Position and Size to Initial
      setPosition(Pnt2s(glutGet( GLUT_INIT_WINDOW_X),glutGet( GLUT_INIT_WINDOW_Y)));
      setSize(Vec2us(glutGet( GLUT_INIT_WINDOW_WIDTH),glutGet( GLUT_INIT_WINDOW_HEIGHT)));
   }
}

//Get the Window Fullscreen
bool GLUTWindowEventProducer::getFullscreen(void) const
{
   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   //This query is not really implemented in GLUT
   //Print a Warning
   SWARNING << "GLUTWindowEventProducer::getFullscreen(void): GLUT Does not define a query for Fullscreen." << std::endl;
   
   return false;
}

void GLUTWindowEventProducer::setDisplayCallback(DisplayCallbackFunc Callback)
{
   WindowEventProducer::setDisplayCallback(Callback);

   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );
   
   glutDisplayFunc(_DisplayCallbackFunc);
}

void GLUTWindowEventProducer::setReshapeCallback(ReshapeCallbackFunc Callback)
{
   WindowEventProducer::setReshapeCallback(Callback);

   //Set the correct GLUT Window
   glutSetWindow( GLUTWindow::Ptr::dcast(getWindow())->getId() );

   glutReshapeFunc(_ReshapeCallbackFunc);
}
/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

GLUTWindowEventProducer::GLUTWindowEventProducer(void) :
    Inherited()
{
}

GLUTWindowEventProducer::GLUTWindowEventProducer(const GLUTWindowEventProducer &source) :
    Inherited(source)
{
}

GLUTWindowEventProducer::~GLUTWindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void GLUTWindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void GLUTWindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GLUTWindowEventProducer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGGLUTWINDOWEVENTPRODUCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGGLUTWINDOWEVENTPRODUCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGGLUTWINDOWEVENTPRODUCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


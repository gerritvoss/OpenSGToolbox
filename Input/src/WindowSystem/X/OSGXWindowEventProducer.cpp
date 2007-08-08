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

#define OSG_COMPILEINPUTLIB

#include <OpenSG/OSGConfig.h>

#include "OSGXWindowEventProducer.h"

#include <OpenSG/OSGXWindow.h>
OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::XWindowEventProducer
XWindowEventProducer Class. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void XWindowEventProducer::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void XWindowEventProducer::setPosition(Pnt2s Pos)
{
    //TODO:Implement
}

Pnt2s XWindowEventProducer::getPosition(void) const
{
   //TODO:Implement
   return Pnt2s(0,0);
}

void XWindowEventProducer::setSize(Vec2us Size)
{
   //TODO:Implement
}

Vec2s XWindowEventProducer::getSize(void) const
{
   //TODO:Implement
   return Vec2s(0,0);
}

void XWindowEventProducer::setFocused(bool Focused)
{
   //TODO:Implement
}

bool XWindowEventProducer::getFocused(void) const
{
   //TODO:Implement
   return false;
}

void XWindowEventProducer::setVisible(bool Visible)
{
   //TODO:Implement
}

bool XWindowEventProducer::getVisible(void) const
{
   //TODO:Implement
   return false;
}

void XWindowEventProducer::setIconify(bool Iconify)
{
   //TODO:Implement
}

bool XWindowEventProducer::getIconify(void) const
{
   //TODO:Implement
   return false;
}

void XWindowEventProducer::setFullscreen(bool Fullscreen)
{
   //TODO:Implement
}

bool XWindowEventProducer::getFullscreen(void) const
{
   //TODO:Implement
   return false;
}

UInt32 XWindowEventProducer::getKeyModifiers(void) const
{
   //TODO:Implement
   return 0;
}

Pnt2s XWindowEventProducer::getMousePosition(void) const
{
   //TODO:Implement
   return Pnt2s(0,0);
}

std::string XWindowEventProducer::getClipboard(void) const
{
   //TODO:Implement
   return std::string("");
}

void XWindowEventProducer::putClipboard(const std::string Value)
{
   //TODO:Implement
}

void XWindowEventProducer::handleEvents(void)
{
   XEvent event;
   do
   {
      XNextEvent(XWindow::Ptr::dcast(getWindow())->getDisplay(), &event);
      switch (event.type) 
      {
         case KeyPress:
            break;

         case ButtonPress:
            {
               MouseEvent::MouseButton OSGButton;
               switch(event.xbutton.button)
               {
               case  1:
                  OSGButton = MouseEvent::BUTTON1;
                  break;
               case  2:
                  OSGButton = MouseEvent::BUTTON2;
                  break;
               case   3:
                  OSGButton = MouseEvent::BUTTON3;
                  break;
               case   4:
                  OSGButton = MouseEvent::BUTTON4;
                  break;
               case   5:
                  OSGButton = MouseEvent::BUTTON5;
                  break;
               default:
                  break;
               }
               produceMousePressed(OSGButton, Pnt2s(event.xbutton.x, event.xbutton.y));
               break;
            }

         case ButtonRelease:
            {
                  MouseEvent::MouseButton OSGButton;
                  switch(event.xbutton.button)
                  {
                  case  1:
                     OSGButton = MouseEvent::BUTTON1;
                     break;
                  case  2:
                     OSGButton = MouseEvent::BUTTON2;
                     break;
                  case   3:
                     OSGButton = MouseEvent::BUTTON3;
                     break;
                  case   4:
                     OSGButton = MouseEvent::BUTTON4;
                     break;
                  case   5:
                     OSGButton = MouseEvent::BUTTON5;
                     break;
                  default:
                     break;
                  }
                  produceMouseReleased(OSGButton, Pnt2s(event.xbutton.x, event.xbutton.y));
                  break;
            }
         case ConfigureNotify:
            if ( ! getWindow()->isResizePending() )
            {
               getWindow()->resize( event.xconfigure.width,
                            event.xconfigure.height );
               _ReshapeCallbackFunc(Vec2s(event.xconfigure.width, event.xconfigure.height));
               _DisplayCallbackFunc();
            }
            break;
         case Expose:
            _DisplayCallbackFunc();
            break;
      }
   }  
   while ( XPending(XWindow::Ptr::dcast(getWindow())->getDisplay()) );
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void XWindowEventProducer::setCursor(void)
{
   //TODO:Implement
}
/*----------------------- constructors & destructors ----------------------*/

XWindowEventProducer::XWindowEventProducer(void) :
    Inherited()
{
}

XWindowEventProducer::XWindowEventProducer(const XWindowEventProducer &source) :
    Inherited(source)
{
}

XWindowEventProducer::~XWindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void XWindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void XWindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump XWindowEventProducer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGXWINDOWEVENTPRODUCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGXWINDOWEVENTPRODUCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGXWINDOWEVENTPRODUCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


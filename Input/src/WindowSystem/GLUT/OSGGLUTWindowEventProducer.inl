/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#include <OpenSG/OSGConfig.h>

#include <OpenSG/OSGGLUT.h>

OSG_BEGIN_NAMESPACE

inline
void GLUTWindowEventProducer::glutDisplay(void)
{
   _DisplayCallbackFunc();
}

inline
void GLUTWindowEventProducer::glutReshape(Vec2s Size)
{
   _ReshapeCallbackFunc(Size);
}

inline
void GLUTWindowEventProducer::glutKeyboardUp(UChar8 key, Pnt2s MousePos)
{
   produceKeyReleased(determineKey(key),0);
}

inline
void GLUTWindowEventProducer::glutKeyboard(UChar8 key, Pnt2s MousePos)
{
   produceKeyPressed(determineKey(key),0);
}

inline
void GLUTWindowEventProducer::glutSpecialUp(UChar8 key,Pnt2s MousePos)
{
   produceKeyReleased(determineSpecialKey(key),0);
}

inline
void GLUTWindowEventProducer::glutSpecial(UChar8 key,Pnt2s MousePos)
{
   produceKeyPressed(determineSpecialKey(key),0);
}

inline
void GLUTWindowEventProducer::glutMouse(Int32 Button, Int32 State, Pnt2s MousePos)
{
   MouseEvent::MouseButton OSGButton;
   switch(Button)
   {
   case  GLUT_LEFT_BUTTON:
      OSGButton = MouseEvent::BUTTON1;
      break;
   case  GLUT_MIDDLE_BUTTON:
      OSGButton = MouseEvent::BUTTON2;
      break;
   case   GLUT_RIGHT_BUTTON:
      OSGButton = MouseEvent::BUTTON3;
      break;
   default:
      break;
   }

   switch(State)
   {
   case GLUT_UP:
      produceMouseReleased(OSGButton, MousePos);
      //produceMouseClicked(OSGButton, MousePos);
      break;
   case GLUT_DOWN:
      produceMousePressed(OSGButton, MousePos);
      break;
   default:
      break;
   }
}

inline
void GLUTWindowEventProducer::glutMotion(Pnt2s MousePos)
{
}

inline
void GLUTWindowEventProducer::glutPassiveMotion(Pnt2s MousePos)
{
   produceMouseMoved(MousePos);
}

OSG_END_NAMESPACE

#define OSGGLUTWINDOWEVENTPRODUCER_INLINE_CVSID "@(#)$Id: FCTemplate_inl.h,v 1.8 2002/12/04 14:22:22 dirk Exp $"


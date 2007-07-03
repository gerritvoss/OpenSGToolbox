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
#include <OpenSG/OSGWin32Window.h>

#include "OSGWin32WindowEventProducer.h"
#include "WindowSystem/OSGWindowEventProducerFactory.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Win32WindowEventProducer
Win32WindowEventProducer Class.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void Win32WindowEventProducer::initMethod (void)
{
	//Register this WindowEventProducer As the WIN32Window WindowEventProducer with the factory
	WindowEventProducerFactory::the()->registerProducer(&WIN32Window::getClassType(), &Win32WindowEventProducer::getClassType());
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

//Set the Window Position
void Win32WindowEventProducer::setPosition(Pnt2s Pos)
{
}

//Set the Window Position
Pnt2s Win32WindowEventProducer::getPosition(void) const
{
   return Pnt2s();
}

//Set the Window size
void Win32WindowEventProducer::setSize(Vec2us Size)
{
}

//Get the Window size
Vec2s Win32WindowEventProducer::getSize(void) const
{
   return Vec2s();
}

//Focused
//Set the Window Focus
void Win32WindowEventProducer::setFocused(bool Focused)
{
}

//Get the Window Focus
bool Win32WindowEventProducer::getFocused(void) const
{
   return false;
}

//Visible / Iconify / Normal
//Set the Window Visible
void Win32WindowEventProducer::setVisible(bool Visible)
{
}

//Get the Window Visible
bool Win32WindowEventProducer::getVisible(void) const
{
   return false;
}

//Set the Window Iconify
void Win32WindowEventProducer::setIconify(bool Iconify)
{
}

//Get the Window Iconify
bool Win32WindowEventProducer::getIconify(void) const
{
   return false;
}

//Fullscreen
void Win32WindowEventProducer::setFullscreen(bool Fullscreen)
{
}

//Get the Window Fullscreen
bool Win32WindowEventProducer::getFullscreen(void) const
{
   return false;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

Win32WindowEventProducer::Win32WindowEventProducer(void) :
    Inherited()
{
}

Win32WindowEventProducer::Win32WindowEventProducer(const Win32WindowEventProducer &source) :
    Inherited(source)
{
}

Win32WindowEventProducer::~Win32WindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void Win32WindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void Win32WindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump Win32WindowEventProducer NI" << std::endl;
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
    static Char8 cvsid_hpp       [] = OSGWIN32WINDOWEVENTPRODUCERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGWIN32WINDOWEVENTPRODUCERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGWIN32WINDOWEVENTPRODUCERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE


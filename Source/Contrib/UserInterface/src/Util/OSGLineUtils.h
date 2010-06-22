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

#ifndef _OSG_UI_DEFINES_H_
#define _OSG_UI_DEFINES_H_

#ifdef __sgi
#pragma once
#endif
 
#include "OSGConfig.h"
#include "OSGLine.h"
#include "OSGVector.h"
#include "OSGContribUserInterfaceDef.h"

OSG_BEGIN_NAMESPACE

bool intersectLineRect ( const Line& l,
                         const Pnt3f & RectPoint1,
                         const Pnt3f & RectPoint2,
                         const Pnt3f & RectPoint3,
                         const Pnt3f & RectPoint4,
                         Real32 &t
                       );
	 
OSG_END_NAMESPACE

#endif /* _OSG_UI_DEFINES_H_ */



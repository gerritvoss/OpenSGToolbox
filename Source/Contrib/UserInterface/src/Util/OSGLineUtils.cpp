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
#include "OSGLineUtils.h"


OSG_BEGIN_NAMESPACE

bool intersectLineRect ( const Line& l,
                         const Pnt3f & RectPoint1,
                         const Pnt3f & RectPoint2,
                         const Pnt3f & RectPoint3,
                         const Pnt3f & RectPoint4,
                         Real32 &t
                       )
{
    // Eps (1E-6f) didn't work with very small geometries!
    static const Real32 sEps = 1E-10f;

    Vec3f RectSide1(RectPoint2-RectPoint1);
    Vec3f RectSide2(RectPoint4-RectPoint1);
    Vec3f n = RectSide1.cross(RectSide2);

    Vec3f w(RectPoint1-l.getPosition());

    t = -(-n.dot(w)) / (n.dot(l.getDirection()));

    return true;
}

OSG_END_NAMESPACE

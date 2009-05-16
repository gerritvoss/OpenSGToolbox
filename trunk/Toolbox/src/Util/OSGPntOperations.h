/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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
#ifndef _OPENSG_POINT_OPERATIONS_H_
#define _OPENSG_POINT_OPERATIONS_H_

#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT, UInt32 SizeI>
osg::Point<ValueTypeT, SizeI> operator+(const osg::Point<ValueTypeT, SizeI>& lValue, const osg::Point<ValueTypeT, SizeI>& rValue)
{
   osg::Point<ValueTypeT, SizeI> Result(lValue);
   for(osg::UInt8 i(0) ; i<SizeI ; ++i)
   {
      Result[i] += rValue[i];
   }
   return Result;
}

template<class ScalarValueTypeT, class ValueTypeT, UInt32 SizeI>
osg::Point<ValueTypeT, SizeI> operator*(const ScalarValueTypeT& lValue, const osg::Point<ValueTypeT, SizeI>& rValue)
{
   return rValue * static_cast<ValueTypeT>(lValue);
}

OSG_END_NAMESPACE

#endif

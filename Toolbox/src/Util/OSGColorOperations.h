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
#ifndef _OPENSG_COLOR_OPERATIONS_H_
#define _OPENSG_COLOR_OPERATIONS_H_

#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

/**
 * \brief Adds two colors together by component.
 */
template<class ValueTypeT>
osg::Color3<ValueTypeT> operator+(const osg::Color3<ValueTypeT>& lValue, const osg::Color3<ValueTypeT>& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() + rValue.red(),
                                  lValue.green() + rValue.green(),
                                  lValue.blue() + rValue.blue()
                                  );
   return Result;
}

/**
 * \brief Subtracts two colors together by component.
 */
template<class ValueTypeT>
osg::Color3<ValueTypeT> operator-(const osg::Color3<ValueTypeT>& lValue, const osg::Color3<ValueTypeT>& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() - rValue.red(),
                                  lValue.green() - rValue.green(),
                                  lValue.blue() - rValue.blue()
                                  );
   return Result;
}


/**
 * \brief Multiplies two colors together by component.
 */
template<class ValueTypeT>
osg::Color3<ValueTypeT> operator*(const osg::Color3<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() * rValue,
                                  lValue.green() * rValue,
                                  lValue.blue() * rValue
                                  );
   return Result;
}

/**
 * \brief Multiplies a Color by a scalar value.
 */
template<class ValueTypeT>
inline osg::Color3<ValueTypeT> operator*(const ValueTypeT& lValue, const osg::Color3<ValueTypeT>& rValue)
{
   return rValue * lValue;
}

/**
 * \brief Divides a Color by a scalar value.
 */
template<class ValueTypeT>
osg::Color3<ValueTypeT> operator/(const osg::Color3<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() / rValue,
                                  lValue.green() / rValue,
                                  lValue.blue() / rValue
                                  );
   return Result;
}

/**
 * \brief Adds two colors together by component.
 */
template<class ValueTypeT>
osg::Color4<ValueTypeT> operator+(const osg::Color4<ValueTypeT>& lValue, const osg::Color4<ValueTypeT>& rValue)
{
   osg::Color4<ValueTypeT> Result(lValue.red() + rValue.red(),
                                  lValue.green() + rValue.green(),
                                  lValue.blue() + rValue.blue(),
                                  lValue.alpha() + rValue.alpha()
                                  );
   return Result;
}

/**
 * \brief Subtracts two colors together by component.
 */
template<class ValueTypeT>
osg::Color4<ValueTypeT> operator-(const osg::Color4<ValueTypeT>& lValue, const osg::Color4<ValueTypeT>& rValue)
{
   osg::Color4<ValueTypeT> Result(lValue.red() - rValue.red(),
                                  lValue.green() - rValue.green(),
                                  lValue.blue() - rValue.blue(),
                                  lValue.alpha() - rValue.alpha()
                                  );
   return Result;
}


/**
 * \brief Multiplies a color by a scalar value.
 */
template<class ValueTypeT>
osg::Color4<ValueTypeT> operator*(const osg::Color4<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::Color4<ValueTypeT> Result(lValue.red() * rValue,
                                  lValue.green() * rValue,
                                  lValue.blue() * rValue,
                                  lValue.alpha() * rValue
                                  );
   return Result;
}

/**
 * \brief Multiplies a color by a scalar value.
 */
template<class ValueTypeT>
inline osg::Color4<ValueTypeT> operator*(const ValueTypeT& lValue, const osg::Color4<ValueTypeT>& rValue)
{
   return rValue * lValue;
}

/**
 * \brief Divides a color by a scalar value.
 */
template<class ValueTypeT>
osg::Color4<ValueTypeT> operator/(const osg::Color4<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::Color4<ValueTypeT> Result(lValue.red() / rValue,
                                  lValue.green() / rValue,
                                  lValue.blue() / rValue,
                                  lValue.alpha() / rValue
                                  );
   return Result;
}

OSG_END_NAMESPACE

#endif

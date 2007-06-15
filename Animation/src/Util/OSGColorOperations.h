#ifndef _OPENSG_COLOR_OPERATIONS_H_
#define _OPENSG_COLOR_OPERATIONS_H_

#include <OpenSG/OSGColor.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//Color3
template<class ValueTypeT>
osg::Color3<ValueTypeT> operator+(const osg::Color3<ValueTypeT>& lValue, const osg::Color3<ValueTypeT>& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() + rValue.red(),
                                  lValue.green() + rValue.green(),
                                  lValue.blue() + rValue.blue()
                                  );
   return Result;
}

template<class ValueTypeT>
osg::Color3<ValueTypeT> operator-(const osg::Color3<ValueTypeT>& lValue, const osg::Color3<ValueTypeT>& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() - rValue.red(),
                                  lValue.green() - rValue.green(),
                                  lValue.blue() - rValue.blue()
                                  );
   return Result;
}


template<class ValueTypeT>
osg::Color3<ValueTypeT> operator*(const osg::Color3<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() * rValue,
                                  lValue.green() * rValue,
                                  lValue.blue() * rValue
                                  );
   return Result;
}

template<class ValueTypeT>
inline osg::Color3<ValueTypeT> operator*(const ValueTypeT& lValue, const osg::Color3<ValueTypeT>& rValue)
{
   return rValue * lValue;
}

template<class ValueTypeT>
osg::Color3<ValueTypeT> operator/(const osg::Color3<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::Color3<ValueTypeT> Result(lValue.red() / rValue,
                                  lValue.green() / rValue,
                                  lValue.blue() / rValue
                                  );
   return Result;
}

//Color4
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

template<class ValueTypeT>
inline osg::Color4<ValueTypeT> operator*(const ValueTypeT& lValue, const osg::Color4<ValueTypeT>& rValue)
{
   return rValue * lValue;
}

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

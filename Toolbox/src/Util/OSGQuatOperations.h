#ifndef _OPENSG_QUATERNION_OPERATIONS_H_
#define _OPENSG_QUATERNION_OPERATIONS_H_

#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGBaseFunctions.h>
#include <OpenSG/OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> operator*(const osg::QuaternionBase<ValueTypeT>& lValue, const osg::QuaternionBase<ValueTypeT>& rValue)
{
   osg::QuaternionBase<ValueTypeT> Result(lValue);
   Result *= rValue;
   return Result;
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> operator+(const osg::QuaternionBase<ValueTypeT>& lValue, const osg::QuaternionBase<ValueTypeT>& rValue)
{
   osg::QuaternionBase<ValueTypeT> Result;
   Result.setValueAsQuat(lValue.x() + rValue.x(),
                         lValue.y() + rValue.y(),
                         lValue.z() + rValue.z(),
                         lValue.w() + rValue.w()
                         );
   return Result;
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> operator-(const osg::QuaternionBase<ValueTypeT>& lValue, const osg::QuaternionBase<ValueTypeT>& rValue)
{
   osg::QuaternionBase<ValueTypeT> Result;
   Result.setValueAsQuat(lValue.x() - rValue.x(),
                         lValue.y() - rValue.y(),
                         lValue.z() - rValue.z(),
                         lValue.w() - rValue.w()
                         );
   return Result;
}


template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> operator*(const osg::QuaternionBase<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::QuaternionBase<ValueTypeT> Result;
   Result.setValueAsQuat(lValue.x() * rValue,
                         lValue.y() * rValue,
                         lValue.z() * rValue,
                         lValue.w() * rValue
                         );
   return Result;
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> operator*(const ValueTypeT& lValue, const osg::QuaternionBase<ValueTypeT>& rValue)
{
   return rValue * lValue;
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> operator/(const osg::QuaternionBase<ValueTypeT>& lValue, const ValueTypeT& rValue)
{
   osg::QuaternionBase<ValueTypeT> Result;
   Result.setValueAsQuat(lValue.x() / rValue,
                         lValue.y() / rValue,
                         lValue.z() / rValue,
                         lValue.w() / rValue
                         );
   return Result;
}

template<class ValueTypeT>
void conj(  const osg::QuaternionBase<ValueTypeT>& Value, osg::QuaternionBase<ValueTypeT>& Result )
{
   Result.setValueAsQuat( -Value.x(),
                          -Value.y(),
                          -Value.z(),
                           Value.w() );
}

template<class ValueTypeT>
void conj(osg::QuaternionBase<ValueTypeT>& Result )
{
   osg::conj(Result, Result);
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> conj(  const osg::QuaternionBase<ValueTypeT>& Value )
{
   osg::QuaternionBase<ValueTypeT> Result;
   osg::conj(Value, Result);
   
   return Result;
}

template<class ValueTypeT>
ValueTypeT lengthSquared(const osg::QuaternionBase<ValueTypeT>& Value )
{
   return (Value.x() * Value.x() +
           Value.y() * Value.y() +
           Value.z() * Value.z() +
           Value.w() * Value.w());
}

template<class ValueTypeT>
void inverse(  const osg::QuaternionBase<ValueTypeT>& Value, osg::QuaternionBase<ValueTypeT>& Result )
{
   osg::conj(Value, Result);
   
   ValueTypeT LengthSqr = lengthSquared(Value);
   
   if(LengthSqr < static_cast<ValueTypeT>(osg::Eps))  { return; }
   
   
   ValueTypeT LengthSqrInv = static_cast<ValueTypeT>(1.0)/LengthSqr;
   
   Result.setValueAsQuat(Result.x() * LengthSqrInv,
                         Result.y() * LengthSqrInv,
                         Result.z() * LengthSqrInv,
                         Result.w() * LengthSqrInv
                         );
}

template<class ValueTypeT>
void inverse(osg::QuaternionBase<ValueTypeT>& Result )
{
   osg::inverse(Result, Result);
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> inverse(  const osg::QuaternionBase<ValueTypeT>& Value )
{
   osg::QuaternionBase<ValueTypeT> Result;
   osg::inverse(Value, Result);
   
   return Result;
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> operator/(const osg::QuaternionBase<ValueTypeT>& lValue, const osg::QuaternionBase<ValueTypeT>& rValue)
{
   osg::QuaternionBase<ValueTypeT> Result(lValue);
   Result *= inverse(rValue);
   return Result;
}

template<class ValueTypeT>
void exp(  const osg::QuaternionBase<ValueTypeT>& Value, osg::QuaternionBase<ValueTypeT>& Result )
{
   ValueTypeT Length1 = osg::osgsqrt( Value.x() * Value.x() +
                                      Value.y() * Value.y() +
                                      Value.z() * Value.z() );
   ValueTypeT Length2;
   
   if( Length1 > static_cast<ValueTypeT>(0.0) )
   {
      Length2 = osg::osgsin( Length1 )/Length1;
   }
   else
   {
      Length2 = static_cast<ValueTypeT>(1.0);
   }
   
   Result.setValueAsQuat(
         Value.x() * Length2,
         Value.y() * Length2,
         Value.z() * Length2,
         osg::osgcos(Length1) );
}

template<class ValueTypeT>
void exp(osg::QuaternionBase<ValueTypeT>& Result )
{
   osg::exp(Result, Result);
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> exp(  const osg::QuaternionBase<ValueTypeT>& Value )
{
   osg::QuaternionBase<ValueTypeT> Result;
   osg::exp(Value, Result);
   
   return Result;
}

template<class ValueTypeT>
void log(  const osg::QuaternionBase<ValueTypeT>& Value, osg::QuaternionBase<ValueTypeT>& Result )
{
   ValueTypeT Length = osg::osgsqrt( Value.x() * Value.x() +
                                     Value.y() * Value.y() +
                                     Value.z() * Value.z() );
   
   if( osg::osgabs(Value.w()) > osg::Eps )
   {
      Length = osg::osgatan( Length/Value.w() );
   }
   else
   {
      Length = osg::Pi/2.0;
   }
   
   Result.setValueAsQuat(
         Value.x() * Length,
         Value.y() * Length,
         Value.z() * Length,
         static_cast<ValueTypeT>(0.0) );
}

template<class ValueTypeT>
void log(osg::QuaternionBase<ValueTypeT>& Result )
{
   osg::log(Result, Result);
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> log(  const osg::QuaternionBase<ValueTypeT>& Value )
{
   osg::QuaternionBase<ValueTypeT> Result;
   osg::log(Value, Result);
   
   return Result;
}

template<class ValueTypeT>
osg::QuaternionBase<ValueTypeT> slerp(const osg::QuaternionBase<ValueTypeT>& lValue, const osg::QuaternionBase<ValueTypeT>& rValue, ValueTypeT t)
{
   osg::QuaternionBase<ValueTypeT> Result( osg::QuaternionBase<ValueTypeT>::slerp(lValue, rValue, t) );
   return Result;
}

OSG_END_NAMESPACE

#endif

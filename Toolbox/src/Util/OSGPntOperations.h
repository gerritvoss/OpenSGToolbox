#ifndef _OPENSG_POINT_OPERATIONS_H_
#define _OPENSG_POINT_OPERATIONS_H_

#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

template<class ValueTypeT, class StorageInterfaceT>
osg::PointInterface<ValueTypeT, StorageInterfaceT> operator+(const osg::PointInterface<ValueTypeT, StorageInterfaceT>& lValue, const osg::PointInterface<ValueTypeT, StorageInterfaceT>& rValue)
{
   osg::PointInterface<ValueTypeT, StorageInterfaceT> Result(lValue);
   for(osg::UInt8 i(0) ; i<StorageInterfaceT::_iSize ; ++i)
   {
      Result[i] += rValue[i];
   }
   return Result;
}

OSG_END_NAMESPACE

#endif

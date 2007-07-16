
#ifndef _OSGBASELISTTYPES_H_
#define _OSGBASELISTTYPES_H_
#ifdef __sgi
#pragma once
#endif

#include "VSEConfig.h"

#include <list>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGColor.h>

OSG_BEGIN_NAMESPACE

typedef std::list<Vec3f> Vec3fList;

typedef std::list<Pnt3f> Pnt3fList;

typedef std::list<Color4f> Color4fList;

typedef std::list<Real32> Real32List;

typedef std::list<UInt64> UInt64List;

OSG_END_NAMESPACE

#endif /* _OSGBASELISTTYPES_H_ */
      

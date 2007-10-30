#ifndef _OSG_TOOLBOX_SHARED_FIELD_PTR_H_
#define _OSG_TOOLBOX_SHARED_FIELD_PTR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGField.h>
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"

OSG_BEGIN_NAMESPACE

typedef ::boost::shared_ptr<Field> SharedFieldPtr;
typedef ::boost::weak_ptr<Field> WeakFieldPtr;

OSG_END_NAMESPACE

#endif /* _OSG_TOOLBOX_SHARED_FIELD_PTR_H_ */

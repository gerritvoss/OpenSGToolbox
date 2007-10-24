#ifndef _OPENSG_GLENUM_UTILS_H_
#define _OPENSG_GLENUM_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGGL.h>

#include <string>

OSG_BEGIN_NAMESPACE

std::string OSG_TOOLBOXLIB_DLLMAPPING toString(const GLenum& value);

OSG_END_NAMESPACE

#endif

#ifndef _OPENSG_CAMERA_UTILS_H_
#define _OPENSG_CAMERA_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGCamera.h>
#include <OpenSG/OSGPerspectiveCamera.h>
#include <OpenSG/OSGNode.h>

OSG_BEGIN_NAMESPACE

/**
 * This function creates a string representation of a GLenum
 * @param[in] value A GLenum
 * @return The string representation of the the GLenum
 */
void OSG_TOOLBOXLIB_DLLMAPPING showAll(PerspectiveCameraPtr TheCamera, NodePtr Scene, Vec3f Up = Vec3f(0.0,1.0,0.0));
void OSG_TOOLBOXLIB_DLLMAPPING showAll(CameraPtr TheCamera, NodePtr Scene, Vec3f Up = Vec3f(0.0,1.0,0.0));

OSG_END_NAMESPACE

#endif

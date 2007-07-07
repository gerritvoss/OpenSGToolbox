#ifndef _OPENSG_WINDOW_UTILS_H_
#define _OPENSG_WINDOW_UTILS_H_

#include "OSGToolboxConfig.h"

#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGVector.h>

OSG_BEGIN_NAMESPACE

WindowPtr OSG_TOOLBOX_FUNC_API createWindow(const FieldContainerType WindowType, 
                       const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName);

WindowPtr OSG_TOOLBOX_FUNC_API createDefaultWindow(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName);

void OSG_TOOLBOX_FUNC_API openWindow(WindowPtr TheWindow);

OSG_END_NAMESPACE

#endif

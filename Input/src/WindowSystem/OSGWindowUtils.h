#ifndef _OPENSG_WINDOW_UTILS_H_
#define _OPENSG_WINDOW_UTILS_H_

#include "OSGInputConfig.h"

#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGVector.h>

#include "OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

void OSG_INPUT_FUNC_API createWindow(const FieldContainerType WindowType, 
                       const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName,
                       WindowPtr& ResultWindow,
                       WindowEventProducerPtr& ResultWindowEventProducer);

void OSG_INPUT_FUNC_API createDefaultWindow(const Pnt2s& ScreenPosition,
                       const Vec2s& Size,
                       const std::string& WindowName,
                       WindowPtr& ResultWindow,
                       WindowEventProducerPtr& ResultWindowEventProducer);

void OSG_INPUT_FUNC_API openWindow(WindowEventProducerPtr TheWindowEventProducer);

OSG_END_NAMESPACE

#endif

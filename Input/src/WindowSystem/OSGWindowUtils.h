#ifndef _OPENSG_WINDOW_UTILS_H_
#define _OPENSG_WINDOW_UTILS_H_

#include <OpenSG/OSGConfig.h>
#include "OSGInputDef.h"

#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGFieldContainerType.h>
#include <OpenSG/OSGVector.h>

#include "OSGWindowEventProducer.h"

OSG_BEGIN_NAMESPACE

WindowEventProducerPtr OSG_INPUTLIB_DLLMAPPING createDefaultWindowEventProducer(void);

WindowEventProducerPtr OSG_INPUTLIB_DLLMAPPING createWindowEventProducer(const FieldContainerType WindowType);

OSG_END_NAMESPACE

#endif

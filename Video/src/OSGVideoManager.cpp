#include "OSGVideoManager.h"

#ifdef darwin
#include "WindowSystem/Carbon/OSGCarbonWindowEventProducer.h"
#endif

#ifdef WIN32
#include "OSGDirectShowManager.h"
#endif

#ifdef __linux
#include <OpenSG/OSGXWindow.h>
#include "WindowSystem/X/OSGXWindowEventProducer.h"
#include <GL/glx.h>
#endif

OSG_BEGIN_NAMESPACE

VideoManagerPtr getDefaultVideoManager(void)
{
#ifdef darwin
    return NULL;
#elif defined(WIN32)
    return DirectShowManager::the();
#elif defined(__linux)
    return NULL;
#endif
}

OSG_END_NAMESPACE
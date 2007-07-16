
#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void EventDispatchThread::setEventDispatchThreadFinish(void)
{
   _EventDispatchThreadFinish = true;
}

inline
EventDispatchThread::EventDispatchThread(const Char8 *szName, UInt32 uiId) : Thread(szName, uiId),
_EventDispatchThreadFinish(false)
{
}

inline
EventDispatchThread::~EventDispatchThread(void)
{
   _EventDispatchThreadFinish = false;
   Thread::join(this);
}

OSG_END_NAMESPACE

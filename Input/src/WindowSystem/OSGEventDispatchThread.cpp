#include "OSGEventDispatchThread.h"


OSG_BEGIN_NAMESPACE

MPThreadType EventDispatchThread::_type("OSGEventDispatchThread", 
                            "OSGThread", 
                            (CreateThreadF)  EventDispatchThread::create,
                            (InitThreadingF) Thread::initThreading);

void EventDispatchThread::workProc(void)
{
   _EventDispatchThreadFinish = false;
   while(!_EventDispatchThreadFinish)
   {
      //std::cout << "bla" << std::endl;
   }
}
EventDispatchThread *EventDispatchThread::create(const Char8 *szName, UInt32 uiId)
{
    return new EventDispatchThread(szName, uiId);
}

OSG_END_NAMESPACE

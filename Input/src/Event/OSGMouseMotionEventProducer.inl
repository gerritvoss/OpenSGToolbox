#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void MouseMotionEventProducer::addMouseMotionListener(MouseMotionListenerPtr Listener)
{
   _MouseMotionListeners.insert(Listener);
}

inline
void MouseMotionEventProducer::removeMouseMotionListener(MouseMotionListenerPtr Listener)
{
   MouseMotionListenerSetItor EraseIter(_MouseMotionListeners.find(Listener));
   if(EraseIter != _MouseMotionListeners.end())
   {
      _MouseMotionListeners.erase(EraseIter);
   }
}

inline
MouseMotionEventProducer::MouseMotionEventProducer(void) : EventProducer()
{
}
  
OSG_END_NAMESPACE

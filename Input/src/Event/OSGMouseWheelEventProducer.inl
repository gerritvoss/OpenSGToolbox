#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void MouseWheelEventProducer::addMouseWheelListener(MouseWheelListenerPtr Listener)
{
   _MouseWheelListeners.insert(Listener);
}

inline
void MouseWheelEventProducer::removeMouseWheelListener(MouseWheelListenerPtr Listener)
{
   MouseWheelListenerSetItor EraseIter(_MouseWheelListeners.find(Listener));
   if(EraseIter != _MouseWheelListeners.end())
   {
      _MouseWheelListeners.erase(EraseIter);
   }
}

inline
MouseWheelEventProducer::MouseWheelEventProducer(void) : EventProducer()
{
}
  
OSG_END_NAMESPACE

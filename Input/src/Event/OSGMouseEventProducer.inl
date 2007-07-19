#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void MouseEventProducer::addMouseListener(MouseListenerPtr Listener)
{
   _MouseListeners.insert(Listener);
}

inline
void MouseEventProducer::removeMouseListener(MouseListenerPtr Listener)
{
   MouseListenerSetItor EraseIter(_MouseListeners.find(Listener));
   if(EraseIter != _MouseListeners.end())
   {
      _MouseListeners.erase(EraseIter);
   }
}

inline
MouseEventProducer::MouseEventProducer(void) : EventProducer()
{
}
  
OSG_END_NAMESPACE

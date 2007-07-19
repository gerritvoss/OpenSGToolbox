#include <OpenSG/OSGConfig.h>

OSG_BEGIN_NAMESPACE

inline
void KeyEventProducer::addKeyListener(KeyListenerPtr Listener)
{
   _KeyListeners.insert(Listener);
}

inline
void KeyEventProducer::removeKeyListener(KeyListenerPtr Listener)
{
   KeyListenerSetItor EraseIter(_KeyListeners.find(Listener));
   if(EraseIter != _KeyListeners.end())
   {
      _KeyListeners.erase(EraseIter);
   }
}

inline
KeyEventProducer::KeyEventProducer(void) : EventProducer()
{
}
  
OSG_END_NAMESPACE

#include "OSGKeyEventProducer.h"


OSG_BEGIN_NAMESPACE

void KeyEventProducer::produceKeyPressed(const KeyEvent& e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyPressed(e);
   }
}

void KeyEventProducer::produceKeyReleased(const KeyEvent& e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyReleased(e);
   }
}

void KeyEventProducer::produceKeyTyped(const KeyEvent& e)
{
   for(KeyListenerSetConstItor SetItor(_KeyListeners.begin()) ; SetItor != _KeyListeners.end() ; ++SetItor)
   {
      (*SetItor)->keyTyped(e);
   }
}

OSG_END_NAMESPACE

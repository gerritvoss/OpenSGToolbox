#include "OSGMouseWheelEventProducer.h"


OSG_BEGIN_NAMESPACE

void MouseWheelEventProducer::produceMouseWheelMoved(const MouseWheelEvent& e)
{
   for(MouseWheelListenerSetConstItor SetItor(_MouseWheelListeners.begin()) ; SetItor != _MouseWheelListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseWheelMoved(e);
   }
}

OSG_END_NAMESPACE

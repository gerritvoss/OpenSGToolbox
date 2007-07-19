#include "OSGMouseMotionEventProducer.h"


OSG_BEGIN_NAMESPACE

void MouseMotionEventProducer::produceMouseMoved(const MouseEvent& e)
{
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
	   (*SetItor)->mouseMoved(e);
   }
}

void MouseMotionEventProducer::produceMouseDragged(const MouseEvent& e)
{
   for(MouseMotionListenerSetConstItor SetItor(_MouseMotionListeners.begin()) ; SetItor != _MouseMotionListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseDragged(e);
   }
}

OSG_END_NAMESPACE

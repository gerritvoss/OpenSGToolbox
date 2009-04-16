#include "OSGMouseEventProducer.h"


OSG_BEGIN_NAMESPACE

void MouseEventProducer::produceMouseClicked(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseClicked(e);
   }
}

void MouseEventProducer::produceMouseEntered(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseEntered(e);
   }
}

void MouseEventProducer::produceMouseExited(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseExited(e);
   }
}

void MouseEventProducer::produceMousePressed(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mousePressed(e);
   }
}

void MouseEventProducer::produceMouseReleased(const MouseEvent& e)
{
   for(MouseListenerSetConstItor SetItor(_MouseListeners.begin()) ; SetItor != _MouseListeners.end() ; ++SetItor)
   {
      (*SetItor)->mouseReleased(e);
   }
}

OSG_END_NAMESPACE

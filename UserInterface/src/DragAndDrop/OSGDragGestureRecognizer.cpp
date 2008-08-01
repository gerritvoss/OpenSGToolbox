#include "OSGDragGestureRecognizer.h"
#include "Event/OSGDragGestureEvent.h"

OSG_BEGIN_NAMESPACE

void DragGestureRecognizer::removeDragGestureListener(DragGestureListenerPtr Listener)
{
   DragGestureListenerSetItor EraseIter(_DragGestureListeners.find(Listener));
   if(EraseIter != _DragGestureListeners.end())
   {
      _DragGestureListeners.erase(EraseIter);
   }
}

void DragGestureRecognizer::produceDragGestureRecognized(ComponentPtr TheComponent, const Pnt2f &DragLocation) const
{
    DragGestureEvent e(TheComponent, getSystemTime(), TheComponent, DragLocation);
	DragGestureListenerSet Listeners(_DragGestureListeners);
    for(DragGestureListenerSetConstItor SetItor(Listeners.begin()) ; SetItor != Listeners.end() ; ++SetItor)
    {
	    (*SetItor)->draqGestureRecognized(e);
    }
}

OSG_END_NAMESPACE
